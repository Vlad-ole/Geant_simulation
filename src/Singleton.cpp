#include "Singleton.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

Singleton::Singleton()
{
	summ_number_of_photons = 0;

	string solution_path = "C:\\diplom\\Geant_simulation\\";

	//определение пути файлов
	string path_out = solution_path + "experiment\\";
	string path_read = solution_path + "data\\";

	// файлы на запись
	file_num_of_photons.open(path_out + "num_of_photons.dat");
	file_num_of_reg_photons.open(path_out + "num_of_reg_photons.dat");
	file_ph_coll.open(path_out + "ph_coll.dat");
	file_xy.open(path_out + "xy.dat");
	file_energy.open(path_out + "energy.dat");
	file_run_lc.open(path_out + "run_lc.dat");
	file_boundary_process.open(path_out + "boundary_process.dat");

	// файлы на чтение
	string_lyso_ce_energies = path_read + "energy_spectrum\\lyso_ce_energies_eV_1.dat";
	string_lyso_ce_rindex = path_read + "refractive_index\\lyso_ce_rindex_eV_1.dat";	
	string_lyso_ce_absorption_length = path_read + "absorption_length\\lyso_ce_absorption_length_eV_mm.dat";

	string_LuYAG_Pr_energies = path_read + "energy_spectrum\\luyag_pr_energies_eV_1.dat";
	string_LuYAG_Pr_rindex = path_read + "refractive_index\\luyag_pr_RINDEX_eV_1.dat";
	string_LuYAG_Pr_absorption_length = path_read  + "absorption_length\\luyag_pr_absorption_length_eV_mm.dat";

	string_LGSO_ce_energies = path_read + "energy_spectrum\\lgso_ce_energies_eV_1.dat";
	string_LGSO_ce_rindex = path_read + "refractive_index\\lgso_ce_rindex_eV_1.dat";	
	string_LGSO_ce_absorption_length = path_read + "absorption_length\\lgso_ce_absorption_length_eV_mm.dat";

	string_LFS_3_energies = path_read + "energy_spectrum\\LFS_3_energies_eV_1.dat";
	string_LFS_3_rindex = path_read + "refractive_index\\LFS_3_rindex_eV_1.dat";	
	string_LFS_3_absorption_length = path_read + "absorption_length\\LFS_3_absorption_length_eV_mm.dat";

	string_YAP_Ce_energies = path_read + "energy_spectrum\\YAP_Ce_energies_eV_1.dat";
	string_YAP_Ce_rindex = path_read + "refractive_index\\YAP_Ce_rindex_eV_1.dat";	
	string_YAP_Ce_absorption_length = path_read + "absorption_length\\YAP_Ce_absorption_length_eV_mm.dat";
	
	string_polydimethylsiloxane_RINDEX =  path_read + "refractive_index\\polydimethylsiloxane_RINDEX_eV_1.dat";
	string_polydimethylsiloxane_absorption_length = path_read + "absorption_length\\polydimethylsiloxane_absorption_length_eV_mm.dat";

	string_fusedsilica_RINDEX = path_read + "refractive_index\\fusedsilica_RINDEX_eV_1.dat";
	string_fusedsilica_ABSLENGTH = path_read + "absorption_length\\fusedsilica_absorption_length_eV_mm.dat";

	string_silicaCathodeMaterial_EFFICIENCY = path_read + "detector_efficiency\\pmt_r10233(big).dat";

	string_MgO_REFLECTIVITY = path_read + "reflectivity\\MgO_REFLECTIVITY_eV_1.dat";
	string_MgO_RINDEX = path_read + "refractive_index\\MgO_RINDEX_eV_1.dat";

	string_TiO2_REFLECTIVITY = path_read + "reflectivity\\TiO2_REFLECTIVITY_eV_1.dat";
	string_TiO2_RINDEX = path_read + "refractive_index\\TiO2_RINDEX_eV_1.dat";

	//
	string_Cathode_REFLECTIVITY = path_read + "reflectivity\\Cathode_REFLECTIVITY_eV_1.dat";

}

Singleton* Singleton::get() 
{

	if(Singleton::single==NULL)
	{
		single = new Singleton();
	}

	return single;

}
