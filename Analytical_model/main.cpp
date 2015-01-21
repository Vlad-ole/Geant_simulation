#include <iostream>
#include <fstream>
//#include <string>
#include "interpolate.h"
#include "Singleton.h"
#include "Errors.h"

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

const double pho_Al=2.765;
const double pho_Cu=8.92;
const double pho_PMMA=1.18;
const double pho_Sm = 7.520;


int main()
{
	ofstream out_file_filter("F:\\Geant_simulation\\data\\x_ray\\Analytical_model_filter.dat");
	ofstream out_file_object("F:\\Geant_simulation\\data\\x_ray\\Analytical_model_object.dat");


	interpolate* x_ray_1 = new interpolate(*g()->x_120);
	//interpolate* x_ray_2 = new interpolate(*x_ray_1, 60000); // 1mA, 1m, 10ms, 1kW (max current - 8mA, max power - 18kW for tube with rotating anode)
	interpolate* x_ray_2 = new interpolate(*x_ray_1, 60000 * 8 * 2 * 5);
	interpolate* x_ray_3 = new interpolate(*x_ray_2, *g()->mu_Sm, pho_Sm*0.02);


	for(int i = 0 ; i <= 150; i += 1)
	{
		if ( ((int)(x_ray_3->GetXVectorMin()) + 1) > i || (x_ray_3->GetXVectorMax() < i) )
			out_file_filter << i << "\t" << 0 << endl;
		else
			out_file_filter << i << "\t" << (*x_ray_3).Eval_Data(i) << endl;
	}

	cout << "after filter ---- start ------------------------------------------" << endl;
	cout << "dose = " << scientific <<  get_dose(*x_ray_3) << endl;

	cout << "N_low = \t" << x_ray_3->summ_particles(11, 50) << "\t E_low =\t" << x_ray_3->average(11, 50) << endl;
	cout << "N_high = \t" << x_ray_3->summ_particles(60, 119) << "\t E_high =\t" << x_ray_3->average(60, 119) << endl;

	cout << "after filter ---- end ------------------------------------------" << endl;


	cout << endl << endl << endl;



	interpolate* x_ray_4 = new interpolate(*x_ray_3, *g()->mu_b, 1);
	interpolate* x_ray_5 = new interpolate(*x_ray_4, *g()->mu_s, 20);

	for(int i = 0 ; i <= 150; i += 1)
	{
		if ( ((int)(x_ray_5->GetXVectorMin()) + 1) > i || (x_ray_5->GetXVectorMax() < i) )
			out_file_object << i << "\t" << 0 << endl;
		else
			out_file_object << i << "\t" << (*x_ray_5).Eval_Data(i) << endl;
	}

	cout << "after object ---- start ------------------------------------------" << endl;
	cout << "dose = " << scientific <<  get_dose(*x_ray_5) << endl;

	cout << "N_low = \t" << x_ray_5->summ_particles(12, 50) << "\t E_low =\t" << x_ray_5->average(12, 50) << endl;
	cout << "N_high = \t" << x_ray_5->summ_particles(60, 118) << "\t E_high =\t" << x_ray_5->average(60, 118) << endl;

	cout << "after object ---- end ------------------------------------------" << endl;

	cout << endl << endl << endl;

	cout << "BetaRelativeError = \t " << 
		Errors::BetaRelativeError(x_ray_5->average(12, 50), x_ray_5->average(60, 118),
		x_ray_3->summ_particles(11, 50), x_ray_3->summ_particles(60, 119), 
		x_ray_5->summ_particles(12, 50), x_ray_5->summ_particles(60, 118), *g()->mu_s) << endl;

	
	//cout << "N particles \t" << (11.0/36 * 1E-4)/get_dose(*x_ray_2) << endl;

	system("PAUSE");
	return 0;
}


