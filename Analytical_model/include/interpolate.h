#pragma once
#include "Math\Interpolator.h"
using namespace std;


class interpolate
{

public:

	//interpolate(char F[]);
	//interpolate(char F[], int flag);
	interpolate();
	interpolate(const char F[], char type[]="default", char linear_or_spline[]="spline");
	interpolate(interpolate* spec_i, const double norm_const);
	interpolate(interpolate* spec_i);
	interpolate(interpolate* spec_i, interpolate* mu_filter,const double rho_l);
	
	interpolate(vector<double> const& temp_x, vector<double> const& temp_y, char type[], char linear_or_spline[]);

	interpolate(interpolate* spec_i, double (*func)(const double value, const double energy)); // convolution constructor

	void print(string file_output_name);

	double Eval_Data(double value, char type[]="default");
	//double Eval_Data(double value, int flag);
	//double Eval_Data(double value, int flag1, int flag2);

	double GetXVectorMin();
	double GetXVectorMax();

	double summ_particles(const double E_min, const double E_max);
	double average(const double E_min, const double E_max);

private:

	//ROOT::Math::Interpolator interpolator(100, ROOT::Math::Interpolation::kPOLYNOMIAL);
	ROOT::Math::Interpolator* interpolator;
	vector<double> xv;
	vector<double> yv;
	//vector<double> C;
};
