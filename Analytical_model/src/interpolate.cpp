#include "interpolate.h"
#include "Singleton.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include "Errors.h"
using namespace std;

interpolate::interpolate() //пустой конструктор
{	 

}

interpolate::interpolate(const char F[], char type[], char linear_or_spline[]) //главный конструктор
{	 
	cout << F <<"\t" << type << "\t" << linear_or_spline <<endl;
	FILE *f = fopen(F,"r");
	if(f == NULL)
	{
		cout << "Error opening file \t" << F << endl;
	}
	else
	{
		double x,y;

		while (!feof(f))
		{
			fscanf(f,"%lf %lf\n", &x, &y);

			if (!strcmp(type,"default")) 
			{
				xv.push_back(x);
				yv.push_back(y);
			}
			if (!strcmp(type,"x_log"))
			{
				xv.push_back(log(x));
				yv.push_back(y);
			}
			if (!strcmp(type,"xy_log"))
			{
				xv.push_back(log(x));
				yv.push_back(log(y));
			}


		}
		fclose(f);

		if (!strcmp(linear_or_spline,"linear")) 
			interpolator = new ROOT::Math::Interpolator(1, ROOT::Math::Interpolation::kLINEAR);
		if (!strcmp(linear_or_spline,"spline")) 
			interpolator = new ROOT::Math::Interpolator(1);

		interpolator->SetData(xv, yv);
	}

}


interpolate::interpolate(vector<double> const& temp_x, vector<double> const& temp_y, char type[], char linear_or_spline[]) //главный конструктор, передача вектора
{	 
	//cout << "vector is transferred \t" << type << "\t" << linear_or_spline <<endl;

	double x,y;

	for(int i=0; i < temp_x.size(); i++)
	{
		x=temp_x[i];
		y=temp_y[i];

		if (!strcmp(type,"default")) 
		{
			xv.push_back(x);
			yv.push_back(y);
		}
		if (!strcmp(type,"x_log"))
		{
			xv.push_back(log(x));
			yv.push_back(y);
		}
		if (!strcmp(type,"xy_log"))
		{
			xv.push_back(log(x));
			yv.push_back(log(y));
		}


	}

	if (!strcmp(linear_or_spline,"linear")) 
		interpolator = new ROOT::Math::Interpolator(1, ROOT::Math::Interpolation::kLINEAR);
	if (!strcmp(linear_or_spline,"spline")) 
		interpolator = new ROOT::Math::Interpolator(1);

	interpolator->SetData(xv, yv);
}


interpolate::interpolate(interpolate* spec_i, interpolate* mu_filter, const double rho_l) // конструктор-фильтр
{
	//vector<double> xv;
	//vector<double> yv;

	double E_min = max(spec_i->GetXVectorMin(), mu_filter->GetXVectorMin());
	double E_max = min(spec_i->GetXVectorMax(), mu_filter->GetXVectorMax());

	//cout << E_min << "\t" << E_max << endl;

	
	int N=100;
	double E_step = (E_max - E_min)/N;
	double E;

	//cout << "E_step" << E_step << endl;

	for (int i=0; i<N; i++)
	{

		E = E_min + E_step*i + E_step/2.0;
		xv.push_back(E);
		yv.push_back(spec_i->Eval_Data(E)*exp(-mu_filter->Eval_Data(E)*rho_l));

		//cout << "E = \t" << E << "\t I = \t" << spec_i.Eval_Data(E)*exp(-mu_filter.Eval_Data(E)*rho_l) << endl;
	}

	interpolator = new ROOT::Math::Interpolator(1, ROOT::Math::Interpolation::kLINEAR);
	//interpolator = new ROOT::Math::Interpolator(1);
	interpolator->SetData(xv, yv);
}

interpolate::interpolate(interpolate* spec_i, const double norm_const) //конструктор-нормировщик
{
	//vector<double> xv;
	//vector<double> yv;

	double E_min = spec_i->GetXVectorMin();
	double E_max = spec_i->GetXVectorMax();
	int N=1000;
	double E_step=(E_max - E_min)/N;

	for (int i=0; i<=N; i++)
	{
		xv.push_back(E_min+E_step*i);
		yv.push_back(spec_i->Eval_Data(E_min + E_step*i)*norm_const);
	}
	interpolator = new ROOT::Math::Interpolator(1);
	interpolator->SetData(xv, yv);
}


interpolate::interpolate(interpolate* spec_i) //конструктор-самонормировщик
{
	//vector<double> xv;
	//vector<double> yv;

	double E_min = spec_i->GetXVectorMin();
	double E_max = spec_i->GetXVectorMax();

	int N=1000;
	double E_step=(E_max - E_min)/N;

	double norm_const=0;
	for (int i=0; i<N; i++)
	{
		double E = E_min+E_step*i + E_step/2.0;
		norm_const += spec_i->Eval_Data(E);
	}

	norm_const = 1/(norm_const*E_step);

	for (int i=0; i<=N; i++)
	{
		xv.push_back(E_min+E_step*i);
		yv.push_back(spec_i->Eval_Data(E_min + E_step*i)*norm_const);
	}
	interpolator = new ROOT::Math::Interpolator(1);
	interpolator->SetData(xv, yv);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////

double interpolate::Eval_Data(double value, char type[]) //функци€ интерпол€ции
{

	if (!strcmp(type,"default")) 
	{
		return interpolator->Eval(value);
	}
	if (!strcmp(type,"x_log"))
	{
		return interpolator->Eval(log(value));
	}
	if (!strcmp(type,"xy_log"))
	{
		return exp(interpolator->Eval(log(value)));
	}
}



double interpolate::GetXVectorMin()
{
	double temp = 1E100;

	for (int i = 0; i < xv.size(); i++)
	{
		//cout << xv[i] << "\t" << temp << endl;
		if( xv[i] < temp)
			temp = xv[i];
	}

	return temp;
}

double interpolate::GetXVectorMax()
{
	double temp = -1E100;

	for (int i = 0; i < xv.size(); i++)
	{
		//cout << xv[i] << "\t" << temp << endl;
		if( xv[i] > temp)
			temp = xv[i];
	}

	return temp;
}

double interpolate::summ_particles(const double E_min, const double E_max)
{
	double temp = 0;
	double E;

	int N = 1000;
	double E_step = (E_max - E_min)/N;

	for (int i = 0; i < N; i++)
	{
		E = E_min + E_step*i + E_step/2.0;
		temp += this->Eval_Data(E);
		//cout << E << "\t" <<  this->Eval_Data(E) << "\t" << temp << endl;
	}

	return temp*E_step;
}


double interpolate::average(const double E_min, const double E_max)
{
	double temp = 0;
	double E;

	int N = 1000;
	double E_step = (E_max - E_min)/N;

	for (int i = 0; i < N; i++)
	{
		E = E_min + E_step*i + E_step/2.0;
		temp += (this->Eval_Data(E))*E;
		//cout << E << "\t" <<  this->Eval_Data(E) << "\t" << temp << endl;
	}

	return (temp*E_step) / ( summ_particles(E_min, E_max) );
}

interpolate::interpolate(interpolate* spec_i, double (*func)(const double value, const double energy))
{
	//int index = 0;
	
	for (int i = 23; i < 148; i++)
	{
		//cout << i << "\t" << Errors::GetConvolution(spec_i, Errors::func, i) << endl;

		xv.push_back(i);
		yv.push_back(Errors::GetConvolution(spec_i, Errors::func, i));
		//index++;
	}

	interpolator = new ROOT::Math::Interpolator(1, ROOT::Math::Interpolation::kLINEAR);
	interpolator->SetData(xv, yv);
}


void interpolate::print(string file_output_name)
{
	
	ofstream output_file(file_output_name);
	
	for (int i = 0; i <= 150; i += 1)
	{
		if (((int)(this->GetXVectorMin()) + 1) > i || (this->GetXVectorMax() < i))
			output_file << i << "\t" << 0 << endl;
		else
			output_file << i << "\t" << this->Eval_Data(i) << endl;
	}

}