#include <iostream>
#include <fstream>
//#include <string>
#include "interpolate.h"
#include "Singleton.h"
#include "Errors.h"

#include "Math\Interpolator.h"
#include "Math/GSLMinimizer.h"
#include "Math/Functor.h"

#include "Math/Minimizer.h"
#include "Math/Factory.h"
#include "Math/Functor.h"
#include "TRandom2.h"
#include "TError.h"

using namespace std;
Singleton* Singleton::single = NULL;

interpolate* x_ray_3;
double tau[3];
int tau_size = 3;

const double pho_Al=2.765;
const double pho_Cu=8.92;
const double pho_PMMA=1.18;
const double pho_Sm = 7.520;


const double dose_const_new=33.97*(2.58E-4)/( (1.6022E-19)*1E8 );

double f(double E, double ratio)
{
	return -((*g()->pho_L).Eval_Data(E) - ratio);
}

double get_area(interpolate& spec_i)
{
	double area=0;
	for(int i=10; i<150; i++)
	{
		area+=spec_i.Eval_Data(i);
	}
	return area;
}

double get_dose(interpolate& spec_i)
{
	double dose=0;

	double E_min = spec_i.GetXVectorMin();
	double E_max = spec_i.GetXVectorMax();
	int N = 1000;
	double E_step = (E_max - E_min)/N;

	/*cout << "E_min = \t" << spec_i.GetXVectorMin() << endl;
	cout << "E_max = \t" << spec_i.GetXVectorMax() << endl;
	cout << "E_step = \t" << E_step << endl;*/


	for (int i=0; i<N; i++)
	{
		double E = E_min + E_step*i + E_step/2.0;
		dose += spec_i.Eval_Data(E) * E * (*g()->mu_a).Eval_Data(E) / (dose_const_new);	
	}


	return dose*E_step;
}

double MLE_Error_wrapper(const double *xx)
{
	tau[0] = 12;
	tau[1] = xx[0]; 
	tau[2] = 118;

	cout << "tau[0] = " << tau[0] << " tau[1] = " << tau[1] << " tau[2] = " << tau[2] << "\t" << sqrt(Errors::Var_t(x_ray_3, g()->mu_b, g()->mu_s, 1, 20, tau, tau_size)) << endl; 


	return sqrt(Errors::Var_t(x_ray_3, g()->mu_b, g()->mu_s, 1, 20, tau, tau_size));

	//cout << "xx[0] = \t" << xx[0] << endl;
	//return pow((xx[0] - 15), 2.0) + 44;

}


int main()
{
	ofstream out_file_filter("F:\\Geant_simulation\\data\\x_ray\\Analytical_model_filter.dat");
	ofstream out_file_object("F:\\Geant_simulation\\data\\x_ray\\Analytical_model_object.dat");
	ofstream out_file_debug_inf("F:\\Geant_simulation\\debug_inf.dat");


	interpolate* x_ray_1 = new interpolate(*g()->x_120);
	//interpolate* x_ray_2 = new interpolate(*x_ray_1, 60000); // 1mA, 1m, 10ms, 1kW (max current - 8mA, max power - 18kW for tube with rotating anode)
	interpolate* x_ray_2 = new interpolate(*x_ray_1, 60000 * 8 * 2 * 5);
	x_ray_3 = new interpolate(*x_ray_2, *g()->mu_Sm, pho_Sm*0.02);

	interpolate* x_ray_4 = new interpolate(*x_ray_3, *g()->mu_b, 1);
	interpolate* x_ray_5 = new interpolate(*x_ray_4, *g()->mu_s, 20);

	for(int i = 0 ; i <= 150; i += 1)
	{
		if ( ((int)(x_ray_5->GetXVectorMin()) + 1) > i || (x_ray_5->GetXVectorMax() < i) )
			out_file_object << i << "\t" << 0 << endl;
		else
			out_file_object << i << "\t" << (*x_ray_5).Eval_Data(i) << endl;
	}


	cout << "BetaRelativeError = \t " << 
		Errors::BetaRelativeError(x_ray_5->average(12, 50), x_ray_5->average(60, 118),
		x_ray_3->summ_particles(11, 50), x_ray_3->summ_particles(60, 119), 
		x_ray_5->summ_particles(12, 50), x_ray_5->summ_particles(60, 118), *g()->mu_s) << endl;

	for (int i = 0; i < 70; i++)
	{
		tau[0] = 11;
		tau[1] = 30 + i;
		tau[2] = 118;


		out_file_debug_inf << tau[1] << "\t" << sqrt(Errors::Var_t(x_ray_3, g()->mu_b, g()->mu_s, 1, 20, tau, tau_size)) << endl;
	}


	//-------------------------------------------------------------------------------
	//https://root.cern.ch/root/html534/tutorials/fit/NumericalMinimization.C.html
	// minimization

	//ROOT::Math::Minimizer* min = ROOT::Math::Factory::CreateMinimizer("Minuit2", "Migrad");
	ROOT::Math::Minimizer* min = ROOT::Math::Factory::CreateMinimizer("Minuit2", "Simplex"); //ok
	//   ROOT::Math::Minimizer* min = ROOT::Math::Factory::CreateMinimizer("Minuit2", "Combined");
	//   ROOT::Math::Minimizer* min = ROOT::Math::Factory::CreateMinimizer("Minuit2", "Scan");
	//   ROOT::Math::Minimizer* min = ROOT::Math::Factory::CreateMinimizer("Minuit2", "Fumili");
	
	//   ROOT::Math::Minimizer* min = ROOT::Math::Factory::CreateMinimizer("GSLMultiMin", "ConjugateFR");
	//   ROOT::Math::Minimizer* min = ROOT::Math::Factory::CreateMinimizer("GSLMultiMin", "ConjugatePR");
	//   ROOT::Math::Minimizer* min = ROOT::Math::Factory::CreateMinimizer("GSLMultiMin", "BFGS");
	//   ROOT::Math::Minimizer* min = ROOT::Math::Factory::CreateMinimizer("GSLMultiMin", "BFGS2");
	//   ROOT::Math::Minimizer* min = ROOT::Math::Factory::CreateMinimizer("GSLMultiMin", "SteepestDescent");
	//   ROOT::Math::Minimizer* min = ROOT::Math::Factory::CreateMinimizer("GSLMultiFit", "");
	 //  ROOT::Math::Minimizer* min = ROOT::Math::Factory::CreateMinimizer("GSLSimAn", "");

	min->SetMaxFunctionCalls(1E5); // for Minuit/Minuit2 
	min->SetMaxIterations(10000);  // for GSL 
	min->SetTolerance(0.001);
	min->SetPrintLevel(1);

	ROOT::Math::Functor f(&MLE_Error_wrapper, 1); 

	min->SetFunction(f);

	//Estimated Distance to Minimum = edm

	// Set the free variables to be minimized!
	//min->SetVariable(0,"x", 90, 0.5);
	min->SetLimitedVariable(0, "x", 30, 1, 12, 118);


	// do the minimization
	min->Minimize(); 

	const double *xs = min->X();
	std::cout << "Minimum: f(" << xs[0] << "): " << min->MinValue() << std::endl;

	//------------------------------------------------------------------------

	//cout << "N particles \t" << (11.0/36 * 1E-4)/get_dose(*x_ray_2) << endl;

	system("PAUSE");
	return 0;
}


