#include "Singleton.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

Singleton::Singleton()
{
	summ_number_of_photons = 0;

	//определение пути файлов
	string path_out = "F:\\Geant_simulation\\experiment\\";
	string path_read = "F:\\Geant_simulation\\data\\";

	// файлы на запись
	file_num_of_photons.open(path_out + "num_of_photons.dat");
	file_num_of_reg_photons.open(path_out + "num_of_reg_photons.dat");
	file_ph_coll.open(path_out + "ph_coll.dat");
	file_xy.open(path_out + "xy.dat");

	// файлы на чтение
	string_lyso_ce_energies = path_read + "energy_spectrum\\lyso_ce_energies_eV_1.dat";
	string_lyso_ce_rindex = path_read + "refractive_index\\lyso_ce_rindex_eV_1.dat";	
	string_lyso_ce_absorption_length = path_read + "absorption_length\\lyso_ce_absorption_length_eV_mm.dat";

	string_LuYAG_Pr_energies = path_read + "energy_spectrum\\luyag_pr_energies_eV_1.dat";
	string_LuYAG_Pr_rindex = path_read + "refractive_index\\luyag_pr_RINDEX_eV_1.dat";
	string_LuYAG_Pr_absorption_length = path_read  + "absorption_length\\luyag_pr_absorption_length_eV_mm.dat";
	
	string_polydimethylsiloxane_RINDEX =  path_read + "refractive_index\\polydimethylsiloxane_RINDEX_eV_1.dat";
	string_polydimethylsiloxane_absorption_length = path_read + "absorption_length\\polydimethylsiloxane_absorption_length_eV_mm.dat";

	string_fusedsilica_RINDEX = path_read + "refractive_index\\fusedsilica_RINDEX_eV_1.dat";
	string_fusedsilica_ABSLENGTH = path_read + "absorption_length\\fusedsilica_absorption_length_eV_mm.dat";

	string_MgO_REFLECTIVITY = path_read + "reflectivity\\MgO_REFLECTIVITY_eV_1.dat";
	string_MgO_RINDEX = path_read + "refractive_index\\MgO_RINDEX_eV_1.dat";

	string_TiO2_REFLECTIVITY = path_read + "reflectivity\\TiO2_REFLECTIVITY_eV_1.dat";
	string_TiO2_RINDEX = path_read + "refractive_index\\TiO2_RINDEX_eV_1.dat";

}

Singleton* Singleton::get() 
{

	if(Singleton::single==NULL)
	{
		single = new Singleton();
	}

	return single;

}
