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


double pho_PMMA=1.18;
double pho_Cu=8.92;
double pho_Al=2.765;

int main()
{
	ofstream out_file("F:\\Geant_simulation\\data\\x_ray\\Analytical_model_out.dat");

		
	interpolate* x_ray_1 = new interpolate(*g()->x_120);
	interpolate* x_ray_2 = new interpolate(*x_ray_1, *g()->mu_Al, pho_Al*0.25);
	

	//for(int i = ((int)(x_ray_1->GetXVectorMin()) + 1) ; i <= x_ray_1->GetXVectorMax(); i += 1)
	//{
	//	out_file << i << "\t" << (*x_ray_1).Eval_Data(i) << endl;
	//}

	cout << "dose = " <<  get_dose(*x_ray_2) << endl;

	cout << endl;

	cout << "N particles \t" << (11.0/36 * 1E-4)/get_dose(*x_ray_2) << endl;

	system("PAUSE");
	return 0;
}


