#pragma once
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#define g() (Singleton::get())

class Singleton
{

private:

	static Singleton *single;
	Singleton();

public:

	static Singleton* get(); 
	
	ofstream file_num_of_photons;
	ofstream file_num_of_reg_photons;
	ofstream file_ph_coll;
	ofstream file_xy;
		
	//LYSO:Ce
	string string_lyso_ce_energies;
	string string_lyso_ce_rindex;
	string string_lyso_ce_absorption_length;

	//LuYAG:Pr
	string string_LuYAG_Pr_energies;
	string string_LuYAG_Pr_rindex;
	string string_LuYAG_Pr_absorption_length;

	//grease
	string string_polydimethylsiloxane_RINDEX;
	string string_polydimethylsiloxane_absorption_length;

	//glass
	string string_fusedsilica_RINDEX;
	string string_fusedsilica_ABSLENGTH;

	//MgO
	string string_MgO_REFLECTIVITY;
	string string_MgO_RINDEX;

	//TiO2
	string string_TiO2_REFLECTIVITY;
	string string_TiO2_RINDEX;

	double summ_number_of_photons;

};