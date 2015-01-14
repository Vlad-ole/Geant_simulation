#include "interpolate.h"
#include "Singleton.h"
#include <iostream>
#include <fstream>
using namespace std;

interpolate::interpolate() //������ �����������
{	 

}

interpolate::interpolate(const char F[], char type[], char linear_or_spline[]) //������� �����������
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


interpolate::interpolate(vector<double> const& temp_x, vector<double> const& temp_y, char type[], char linear_or_spline[]) //������� �����������, �������� �������
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


interpolate::interpolate(interpolate& spec_i, interpolate& mu_filter, double rho_l) // �����������-������
{
	vector<double> xv;
	vector<double> yv;

	double E_min=10;
	double E_max=150;
	int N=100;
	double E_step=(E_max - E_min)/N;
	double E;


	for (int i=0; i<=N; i++)
	{

		E=E_min+E_step*i;
		xv.push_back(E);
		yv.push_back(spec_i.Eval_Data(E)*exp(-mu_filter.Eval_Data(E)*rho_l));
		//cout << "x=\t" << E << "\t y=\t" << spec_i.Eval_Data(E)*exp(-mu_filter.Eval_Data(E)*rho*l) << endl;
	}

	interpolator = new ROOT::Math::Interpolator(1, ROOT::Math::Interpolation::kLINEAR);
	//interpolator = new ROOT::Math::Interpolator(1);
	interpolator->SetData(xv, yv);
}

interpolate::interpolate(interpolate& spec_i, double norm_const) //�����������-�����������
{
	vector<double> xv;
	vector<double> yv;

	double E_min=10;
	double E_max=150;
	int N=1000;
	double E_step=(E_max - E_min)/N;

	for (int i=0; i<=N; i++)
	{
		xv.push_back(E_min+E_step*i);
		yv.push_back(spec_i.Eval_Data(E_min+E_step*i)*norm_const);
	}
	interpolator = new ROOT::Math::Interpolator(1);
	interpolator->SetData(xv, yv);
}


interpolate::interpolate(interpolate& spec_i) //�����������-���������������
{
	vector<double> xv;
	vector<double> yv;

	double E_min=10;
	double E_max=150;
	int N=1000;
	double E_step=(E_max - E_min)/N;

	double norm_const=0;
	for (int i=0; i<N; i++)
	{
		double E = E_min+E_step*i + E_step/2.0;
		norm_const+=spec_i.Eval_Data(E);
	}

	norm_const = 1/(norm_const*E_step);

	for (int i=0; i<=N; i++)
	{
		xv.push_back(E_min+E_step*i);
		yv.push_back(spec_i.Eval_Data(E_min+E_step*i)*norm_const);
	}
	interpolator = new ROOT::Math::Interpolator(1);
	interpolator->SetData(xv, yv);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////

double interpolate::Eval_Data(double value, char type[]) //������� ������������
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
