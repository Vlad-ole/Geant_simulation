#include "Errors.h"
#include <iostream>
#include "Singleton.h"
using namespace std;

Errors::Errors(void)
{
}


Errors::~Errors(void)
{
}


double Errors::BetaRelativeError(const double E_i, const double E_j, const unsigned int I_0_i, const unsigned int I_0_j, const unsigned int I_i, const unsigned int I_j, interpolate& mu_soft)
{
	const double T_i = log(I_0_i / I_i);
	const double T_j = log(I_0_j / I_j);

	//cout << T_i << endl;
	//cout << T_j << endl;

	const double DeltaBetaSquare = pow(mu_soft.Eval_Data(E_i), 2.0) / I_j + pow(mu_soft.Eval_Data(E_j), 2.0) / I_i;
	const double DetBetaSquare = pow(mu_soft.Eval_Data(E_i) * T_j - mu_soft.Eval_Data(E_j) * T_i, 2.0);


	return sqrt(DeltaBetaSquare / DetBetaSquare);
}

double Errors::Var_t(interpolate* spec_after_filter, interpolate* mu_1, interpolate* mu_2, const double t1, const double t2, double* tau, int tau_size)
{

	//cout << "sizeof(tau) = \t" <<  tau_size << endl;	

	//------------------------------------------------------
	// calculate gammas and matrix parameters
	double gamma;
	double gamma_1;
	double gamma_2;

	double temp;

	double a = 0;
	double b = 0;
	double c = 0;

	for (int i = 1; i < tau_size; i++)
	{
		gamma = 0;
		gamma_1 = 0;
		gamma_2 = 0;

		for (int j = tau[i - 1] + 1; j <= tau[i]; j++)
		{
			temp = spec_after_filter->Eval_Data(j) * exp(-(t1 * mu_1->Eval_Data(j) + t2 * mu_2->Eval_Data(j)));

			gamma += temp;
			gamma_1 += temp * mu_1->Eval_Data(j);
			gamma_2 += temp * mu_2->Eval_Data(j);
		}

		a += pow(gamma_1, 2.0) / gamma;
		b += (gamma_1 * gamma_2) / gamma;
		c += pow(gamma_2, 2.0) / gamma;

		/*cout << "gamma = \t" << gamma << endl;*/
	}

	//cout << "a =\t " << a << endl;
	//cout << "b =\t " << b << endl;
	//cout << "c =\t " << c << endl;
	//cout << endl;

	//-------------------------------------------------------



	//------------------------------------------------------
	//calculate Var(t_1)

	double Var = 0;
	
	for (int i = 1; i < tau_size; i++)
	{
		gamma = 0;
		gamma_1 = 0;
		gamma_2 = 0;

		for (int j = tau[i - 1] + 1; j <= tau[i]; j++)
		{
			temp = spec_after_filter->Eval_Data(j) * exp(-(t1 * mu_1->Eval_Data(j) + t2 * mu_2->Eval_Data(j)));

			gamma += temp;
			gamma_1 += temp * mu_1->Eval_Data(j);
			gamma_2 += temp * mu_2->Eval_Data(j);
		}

		Var += pow(gamma_1 / gamma * c - gamma_2 / gamma * b, 2.0) * gamma;
	}


	//------------------------------------------------------


	return Var / pow(a*c - b*b, 2.0);
}



double Errors::Var_t_correlate(interpolate* spec_after_filter, interpolate* mu_1, interpolate* mu_2, const double t1, const double t2, double* tau, int tau_size, interpolate* convolution)
{
	//cout << "tau[0] = \t" << tau[0] << endl; 
	//cout << "tau[1] = \t" << tau[1] << endl; 
	//cout << "tau[2] = \t" << tau[2] << endl; 

	//------------------------------------------------------
	// calculate gammas and matrix parameters
	double gamma;
	double gamma_1;
	double gamma_2;

	double temp;

	double a = 0;
	double b = 0;
	double c = 0;

	for (int i = 1; i < tau_size; i++)
	{

		gamma = 0;
		gamma_1 = 0;
		gamma_2 = 0;

		for (int j = tau[i - 1] + 1; j <= tau[i]; j++)
		{

			temp = spec_after_filter->Eval_Data(j) * exp(-(t1 * mu_1->Eval_Data(j) + t2 * mu_2->Eval_Data(j)));

			gamma += temp;
			gamma_1 += temp * mu_1->Eval_Data(j);
			gamma_2 += temp * mu_2->Eval_Data(j);
		}

		a += pow(gamma_1, 2.0) / gamma;
		b += (gamma_1 * gamma_2) / gamma;
		c += pow(gamma_2, 2.0) / gamma;

	}

	/*cout << "a =\t " << a << endl;
	cout << "b =\t " << b << endl;
	cout << "c =\t " << c << endl;
	cout << endl;*/

	//-------------------------------------------------------




	//-------------------------------------------------------
	//calculate cov(dk, dl) = Var(dk)
	double* cov = new double[tau_size - 1];

	double x;

	for (int i = 1; i < tau_size; i++)
	{
		x = 0;
		
		for (int j = tau[i - 1] + 1; j <= tau[i]; j++)
		{
			temp = spec_after_filter->Eval_Data(j) * exp(-(t1 * mu_1->Eval_Data(j) + t2 * mu_2->Eval_Data(j)));

			x += temp;
			
		}

		cov[i - 1] = x * p[][];
	}


	//-------------------------------------------------------


	//------------------------------------------------------
	//calculate Var(t_1)

	double Var = 0;
	for (int i = 1; i < tau_size; i++)
	{
		gamma = 0;
		gamma_1 = 0;
		gamma_2 = 0;

		for (int j = tau[i - 1] + 1; j <= tau[i]; j++)
		{
			temp = spec_after_filter->Eval_Data(j) * exp(-(t1 * mu_1->Eval_Data(j) + t2 * mu_2->Eval_Data(j)));

			gamma += temp;
			gamma_1 += temp * mu_1->Eval_Data(j);
			gamma_2 += temp * mu_2->Eval_Data(j);
		}

		Var += pow(gamma_1 / gamma * c - gamma_2 / gamma * b, 2.0) * cov[i];
	}


	//------------------------------------------------------


	return Var / pow(a*c - b*b, 2.0);
}



//
//double Errors::Cov_dk_dl(const double dk, const double dl)
//{
//	return 0;
//}


double Errors::GetConvolution(interpolate* spec_i, double(*func)(const double value, const double energy), const double x)
{
	double summ = 0;

	for (int y = 23; y < 118; y++)
	{
		//cout << y << "\t" << spec_i.Eval_Data(y) * func(x - y) << endl;
		summ += spec_i->Eval_Data(y) * func(x - y, y);
	}

	return summ;
}


double Errors::func(const double value, const double energy)
{
	//const double sigma = 10; // [keV]

	const double eff = 0.45;
	const double yield = 32; // [ph/keV]
	const double light_coll = 0.5;

	const double sigma = sqrt(pow((*g()->intrinsic_resolution_YAP_Ce).Eval_Data(energy) / 2.355, 2.0) + (1 - eff) / (eff * light_coll * energy * yield)) * energy;

	return 1 / (sigma * sqrt(2 * 3.1416)) * exp(-pow(value, 2.0) / (2 * sigma * sigma));
}