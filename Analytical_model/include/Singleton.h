#pragma once
#include <iostream>
#include "interpolate.h"
using namespace std;
#define g() (Singleton::get())
//#define Mat(x) (G4NistManager::Instance()->FindOrBuildMaterial(x)) //example

class Singleton
{

private:

	static Singleton *single;

	Singleton()
	{
		solution_path = "D:\\git_repositories\\Geant_simulation\\";

				
		mu_a = new interpolate((solution_path + "data\\mu\\air_paper_and_nist.dat").c_str());
		mu_s = new interpolate((solution_path + "data\\mu\\soft.dat").c_str());
		mu_b = new interpolate((solution_path + "data\\mu\\bone.dat").c_str());
		mu_f = new interpolate((solution_path + "data\\mu\\adipose_xop.dat").c_str());
		mu_Sm = new interpolate((solution_path + "data\\mu\\Sm_xop.dat").c_str(), "default","linear");
		mu_Y = new interpolate((solution_path + "data\\mu\\Y_xop.dat").c_str(), "default","linear");
		mu_PMMA = new interpolate((solution_path + "data\\mu\\PMMA_xop.dat").c_str(), "default","linear");

		mu_C = new interpolate((solution_path + "data\\mu\\C_xop.dat").c_str(), "default","linear");
		mu_Cu = new interpolate((solution_path + "data\\mu\\Cu_xop.dat").c_str(), "default","linear");
		mu_Al = new interpolate((solution_path + "data\\mu\\Al_xop.dat").c_str(), "default", "linear");
		mu_O = new interpolate((solution_path + "data\\mu\\O_xop.dat").c_str(), "default","linear");
		mu_Gd = new interpolate((solution_path + "data\\mu\\Gd_xop.dat").c_str(), "default","linear");
		mu_Lu = new interpolate((solution_path + "data\\mu\\Lu_xop.dat").c_str(), "default","linear");
		mu_Si = new interpolate((solution_path + "data\\mu\\Si_xop.dat").c_str(), "default","linear");
		
		
		x_150 = new interpolate((solution_path + "data\\x_ray\\150.dat").c_str(), "default","linear");
		x_120 = new interpolate((solution_path + "data\\x_ray\\120.dat").c_str(), "default","linear");
		x_110 = new interpolate((solution_path + "data\\x_ray\\110.dat").c_str(), "default","linear");
		x_100 = new interpolate((solution_path + "data\\x_ray\\100.dat").c_str(), "default","linear");
		x_90 = new interpolate((solution_path + "data\\x_ray\\90.dat").c_str(), "default","linear");
		x_80 = new interpolate((solution_path + "data\\x_ray\\80.dat").c_str(), "default","linear");
		x_70 = new interpolate((solution_path + "data\\x_ray\\70.dat").c_str(), "default","linear");
		x_60 = new interpolate((solution_path + "data\\x_ray\\60.dat").c_str(), "default", "linear");
		

		intrinsic_resolution_YAP_Ce = new interpolate((solution_path + "data\\intrinsic_resolution\\yap_ce_keV_1.dat").c_str());
		
		//eta=pow(10.0,-2);
		////eta=0;
		//dose_0=pow(10.0, -3);
	}

public:

	static Singleton* get() 
	{

		if(Singleton::single==NULL)
		{
			single = new Singleton();
		}
		return single;

	}

	string solution_path;

	
	interpolate* mu_a;
	interpolate* mu_s;
	interpolate* mu_b;
	interpolate* mu_f;
	interpolate* mu_Sm;
	interpolate* mu_Y;
	interpolate* mu_Al;
	interpolate* mu_O;
	interpolate* mu_Gd;
	interpolate* mu_Lu;
	interpolate* mu_Si;
	interpolate* mu_Cu;
	interpolate* mu_PMMA;
	interpolate* pmt_cathode_eff;
	interpolate* mu_C;


	interpolate* pho_L;

	interpolate* x_150;
	interpolate* x_120;
	interpolate* x_110;
	interpolate* x_100;
	interpolate* x_90;
	interpolate* x_60;
	interpolate* x_60_real;
	interpolate* x_70;
	interpolate* x_80;

	interpolate* counting_curve;

	interpolate* intrinsic_resolution_YAP_Ce;
	interpolate* convolution;

	double eta;
	double dose_0;

	//interpolate* after_filter;

};


