#include "DetectorConstruction.hh"
#include <G4OpticalSurface.hh>
#include <G4SystemOfUnits.hh> // this has appeared in GEANT4_10
#include "ReadConstants.h"
#include "Singleton.h"

void DetectorConstruction::defineSurfaces()
{
	//*********************************************************************************
	//LUT model
	BGOPolishedAirTeflon = new G4OpticalSurface("BGOPolishedAirTeflon", unified);
	BGOPolishedAirTeflon->SetType(dielectric_LUT);
	BGOPolishedAirTeflon->SetModel(LUT);
	BGOPolishedAirTeflon->SetFinish(polishedteflonair);

	BGOGroundAirTeflon = new G4OpticalSurface("BGOGroundAirTeflon", unified);
	BGOGroundAirTeflon->SetType(dielectric_LUT);
	BGOGroundAirTeflon->SetModel(LUT);
	BGOGroundAirTeflon->SetFinish(groundteflonair);

	Polished_Air_TiO2 = new G4OpticalSurface("Polished_Air_TiO2", unified);
	Polished_Air_TiO2->SetType(dielectric_LUT);
	Polished_Air_TiO2->SetModel(LUT);
	Polished_Air_TiO2->SetFinish(polishedtioair);

	Ground_Air_TiO2 = new G4OpticalSurface("Ground_Air_TiO2", unified);
	Ground_Air_TiO2->SetType(dielectric_LUT);
	Ground_Air_TiO2->SetModel(LUT);
	Ground_Air_TiO2->SetFinish(groundtioair);
	//*********************************************************************************



	//*********************************************************************************
	//unifed model
	G4double ener[2] = {.1*eV, 10.*eV};
	G4double specular_lobe[2] = {1.0, 1.0};
	G4double specular_spike[2] = {0.0, 0.0};
	G4double back_scatter[2] = {0.0, 0.0};

	//-------------------------------------------------------------------------------
	//polishedAir
	polishedAir = new G4OpticalSurface("polishedAir");
	polishedAir->SetModel(unified);
	polishedAir->SetType(dielectric_dielectric);	
	polishedAir->SetFinish(ground); // ground necessary even for polished surfaces to enable UNIFIED code
	polishedAir->SetSigmaAlpha(g()->SigmaAlpha_index * degree); // Janecek2010

	G4MaterialPropertiesTable* polishedAir_property = new G4MaterialPropertiesTable();
	//polishedAir_property->AddProperty("RINDEX", ener, teflon_rindex, 2);
	polishedAir_property->AddProperty("SPECULARLOBECONSTANT", ener, specular_lobe,2);
	polishedAir_property->AddProperty("SPECULARSPIKECONSTANT", ener, specular_spike,2);
	polishedAir_property->AddProperty("BACKSCATTERCONSTANT", ener, back_scatter,2);
	//polishedAir_property->AddProperty("REFLECTIVITY", ener, teflon_refl, 2);
	polishedAir->SetMaterialPropertiesTable(polishedAir_property);
	//-------------------------------------------------------------------------------
	
	
	
	//---------------------------------------------------------------------------
	//teflon
	

	G4double teflon_rindex[2] = {1.35, 1.35}; //wiki (Optical properties of materials for concentrator photovoltaic systems) [1.35-1.38]
	G4double teflon_refl[2] = {0.99, 0.99}; // Janecek2010

	teflon_unified = new G4OpticalSurface("polishedWhitePainted", unified);
	teflon_unified->SetType(dielectric_dielectric);
	teflon_unified->SetModel(unified);
	teflon_unified->SetFinish(groundbackpainted);
	teflon_unified->SetSigmaAlpha(0.0741 * degree); // Janecek2010

	G4MaterialPropertiesTable* teflon_unified_property = new G4MaterialPropertiesTable();
	teflon_unified_property->AddProperty("RINDEX", ener, teflon_rindex, 2);
	teflon_unified_property->AddProperty("SPECULARLOBECONSTANT", ener, specular_lobe,2);
	teflon_unified_property->AddProperty("SPECULARSPIKECONSTANT", ener, specular_spike,2);
	teflon_unified_property->AddProperty("BACKSCATTERCONSTANT", ener, back_scatter,2);
	teflon_unified_property->AddProperty("REFLECTIVITY", ener, teflon_refl, 2);
	teflon_unified->SetMaterialPropertiesTable(teflon_unified_property);
	//-------------------------------------------------------------------------------

	
	
	//---------------------------------------------------------------------------
	//MgO
	ReadConstants *MgO_RINDEX = new ReadConstants(g()->string_MgO_RINDEX, 1*eV, 1);
	ReadConstants *MgO_REFLECTIVITY = new ReadConstants(g()->string_MgO_REFLECTIVITY, 1*eV, 1);

	MgO_unified = new G4OpticalSurface("polishedWhitePainted", unified);
	MgO_unified->SetType(dielectric_dielectric);
	MgO_unified->SetModel(unified);
	MgO_unified->SetFinish(groundbackpainted);
	MgO_unified->SetSigmaAlpha(1.3 * degree); // Janecek2010

	G4MaterialPropertiesTable* MgO_unified_property = new G4MaterialPropertiesTable();
	MgO_unified_property->AddProperty("RINDEX", MgO_RINDEX->get_x_array(), MgO_RINDEX->get_y_array(), MgO_RINDEX->get_array_size());
	MgO_unified_property->AddProperty("SPECULARLOBECONSTANT", ener, specular_lobe,2);
	MgO_unified_property->AddProperty("SPECULARSPIKECONSTANT", ener, specular_spike,2);
	MgO_unified_property->AddProperty("BACKSCATTERCONSTANT", ener, back_scatter,2);
	MgO_unified_property->AddProperty("REFLECTIVITY", MgO_REFLECTIVITY->get_x_array(), MgO_REFLECTIVITY->get_y_array(), MgO_REFLECTIVITY->get_array_size());
	MgO_unified->SetMaterialPropertiesTable(MgO_unified_property);
	//-------------------------------------------------------------------------------

	
	//---------------------------------------------------------------------------
	//TiO2
	ReadConstants *TiO2_RINDEX = new ReadConstants(g()->string_TiO2_RINDEX, 1*eV, 1);
	ReadConstants *TiO2_REFLECTIVITY = new ReadConstants(g()->string_TiO2_REFLECTIVITY, 1*eV, 1);

	TiO2_unified = new G4OpticalSurface("polishedWhitePainted", unified);
	TiO2_unified->SetType(dielectric_dielectric);
	TiO2_unified->SetModel(unified);
	TiO2_unified->SetFinish(groundbackpainted);
	TiO2_unified->SetSigmaAlpha(1.3 * degree); // Janecek2010

	G4MaterialPropertiesTable* TiO2_unified_property = new G4MaterialPropertiesTable();
	TiO2_unified_property->AddProperty("RINDEX", TiO2_RINDEX->get_x_array(), TiO2_RINDEX->get_y_array(), TiO2_RINDEX->get_array_size());
	TiO2_unified_property->AddProperty("SPECULARLOBECONSTANT", ener, specular_lobe,2);
	TiO2_unified_property->AddProperty("SPECULARSPIKECONSTANT", ener, specular_spike,2);
	TiO2_unified_property->AddProperty("BACKSCATTERCONSTANT", ener, back_scatter,2);
	TiO2_unified_property->AddProperty("REFLECTIVITY", TiO2_REFLECTIVITY->get_x_array(), TiO2_REFLECTIVITY->get_y_array(), TiO2_REFLECTIVITY->get_array_size());
	TiO2_unified->SetMaterialPropertiesTable(TiO2_unified_property);
	//------------------------------------------------------------------------------
	
	//-------------------------------------------------------------------------------
	//описание поверхности стекла ‘Ё”
	Glass_surface = new G4OpticalSurface("Glass_surface");
	Glass_surface->SetModel(unified);
	Glass_surface->SetType(dielectric_dielectric);	
	Glass_surface->SetFinish(ground); // ground necessary even for polished surfaces to enable UNIFIED code
	Glass_surface->SetSigmaAlpha(0.0 * degree); // Janecek2010

	G4MaterialPropertiesTable* Glass_surface_property = new G4MaterialPropertiesTable();
	//polishedAir_property->AddProperty("RINDEX", ener, teflon_rindex, 2);
	Glass_surface_property->AddProperty("SPECULARLOBECONSTANT", ener, specular_lobe,2);
	Glass_surface_property->AddProperty("SPECULARSPIKECONSTANT", ener, specular_spike,2);
	Glass_surface_property->AddProperty("BACKSCATTERCONSTANT", ener, back_scatter,2);
	//polishedAir_property->AddProperty("REFLECTIVITY", ener, teflon_refl, 2);
	Glass_surface->SetMaterialPropertiesTable(Glass_surface_property);
	//-------------------------------------------------------------------------------

	
	//-----------------------------------------------------------------------------
	// описание поверхности фотокатода
	silicaCathodeMaterial = new G4OpticalSurface("silicaCathodeMaterial", unified);
	silicaCathodeMaterial->SetType(dielectric_metal);
	silicaCathodeMaterial->SetModel(unified);
	silicaCathodeMaterial->SetFinish(polished);
	silicaCathodeMaterial->SetSigmaAlpha(0.);

	

	silicaCathodeMaterialProperty = new G4MaterialPropertiesTable();
	//G4double cathoderefl[2] = {0.25, 0.25};
	//G4double cathodeeff[2] = {1, 1};

	ReadConstants *silicaCathodeMaterial_EFFICIENCY = new ReadConstants(g()->string_silicaCathodeMaterial_EFFICIENCY, 1*eV, 1);
	ReadConstants *Cathode_REFLECTIVITY = new ReadConstants(g()->string_Cathode_REFLECTIVITY, 1*eV, 1);

	
	//silicaCathodeMaterialProperty->AddProperty("REFLECTIVITY", Cathode_REFLECTIVITY->get_x_array(), Cathode_REFLECTIVITY->get_y_array(), Cathode_REFLECTIVITY->get_array_size());
	//silicaCathodeMaterialProperty->AddProperty("EFFICIENCY", silicaCathodeMaterial_EFFICIENCY->get_x_array(), silicaCathodeMaterial_EFFICIENCY->get_y_array(), silicaCathodeMaterial_EFFICIENCY->get_array_size());
	

	//silicaCathodeMaterialProperty->AddProperty("REFLECTIVITY", ener, cathoderefl, 2);
	//silicaCathodeMaterialProperty->AddProperty("EFFICIENCY", ener, cathodeeff, 2);

	silicaCathodeMaterial->SetMaterialPropertiesTable(silicaCathodeMaterialProperty);
	//--------------------------------------------------------------------------------


	//-----------------------------------------------------------------------------
	// описание поверхности поглотител€
	AbsorberMaterial = new G4OpticalSurface("Absorber", unified);
	AbsorberMaterial->SetType(dielectric_metal);
	AbsorberMaterial->SetModel(unified);
	AbsorberMaterial->SetFinish(polished);
	AbsorberMaterial->SetSigmaAlpha(0.);



	G4MaterialPropertiesTable *AbsorberMaterialProperty = new G4MaterialPropertiesTable();
	G4double AbsorberMaterialrefl[2] = { 0.0, 0.0 };
	G4double AbsorberMaterialeff[2] = { 0, 0 };
		
	AbsorberMaterialProperty->AddProperty("REFLECTIVITY", ener, AbsorberMaterialrefl, 2);
	AbsorberMaterialProperty->AddProperty("EFFICIENCY", ener, AbsorberMaterialeff, 2);

	AbsorberMaterial->SetMaterialPropertiesTable(AbsorberMaterialProperty);
	//--------------------------------------------------------------------------------



	//*********************************************************************************
}

void DetectorConstruction::ChangeSurface(double parametr)
{
	polishedAir->SetSigmaAlpha(parametr * degree);
}

void DetectorConstruction::ChangeCathRefl()
{
	G4double ener[2] = { .1*eV, 10.*eV };
	G4double cathoderefl[2] = { g()->CathRefl_index, g()->CathRefl_index };

	G4double factory_eff = 0.25;
	G4double cathodeeff[2] = { factory_eff / (1 - g()->CathRefl_index), factory_eff / (1 - g()->CathRefl_index) };
	
	silicaCathodeMaterialProperty->AddProperty("REFLECTIVITY", ener, cathoderefl, 2);
	silicaCathodeMaterialProperty->AddProperty("EFFICIENCY", ener, cathodeeff, 2);
}