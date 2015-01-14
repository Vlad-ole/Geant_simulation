#include <iostream>
#include <fstream>
//#include <string>
#include "interpolate.h"
#include "Singleton.h"

#include "Math\Interpolator.h"
#include "Math/GSLMinimizer.h"
#include "Math/Functor.h"

using namespace std;
Singleton* Singleton::single = NULL;


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
	for(int i=10; i<150; i++)
	{
		dose+=spec_i.Eval_Data(i) * i * (*g()->mu_a).Eval_Data(i) / (dose_const_new)  ;	
		//cout << i << "\t" << i * (*g()->mu_a).Eval_Data(i) / (dose_const_new) << endl;
	}

	return dose;
}


double pho_PMMA=1.18;
double pho_Cu=8.92;
double pho_Al=2.765;

int main()
{
	ofstream out_file("F:\\Geant_simulation\\data\\x_ray\\Analytical_model_out.dat");

	cout << g()->x << endl;
	cout << g()->solution_path << endl;
	//interpolate* x_ray_1 = new interpolate(*g()->x_60, *g()->mu_Al, pho_Al*0.15);
	//interpolate* x_ray_2 = new interpolate(*x_ray_1);
	//	
	//for(double i=10; i<150; i+=1)
	//{
	//	out_file << i << "\t" << (*x_ray_2).Eval_Data(i) << endl;
	//}
	
	//interpolate* x_60 = new interpolate("F:\\Geant_simulation\\data\\x_ray\\test2.dat", "default");	

	int xvv[] = { 10, 20, 30, 40, 50 };
	int yvv[] = { 1, 2, 3, 4, 5 };
	std::vector<double> xv(begin(xvv), end(xvv));
	std::vector<double> yv(begin(yvv), end(yvv));

	ROOT::Math::Interpolator* interpolator = new ROOT::Math::Interpolator(xv, yv);

	system("PAUSE");
	return 0;
}


