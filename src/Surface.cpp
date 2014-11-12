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
	
	//-------------------------------------------------------------------------------
	//polishedAir
	polishedAir = new G4OpticalSurface("polishedAir");
	polishedAir->SetModel(glisur);
	polishedAir->SetType(dielectric_dielectric);	
	polishedAir->SetFinish(ground); // ground necessary even for polished surfaces to enable UNIFIED code
	//polishedAir->SetSigmaAlpha(10 * degree); // Janecek2010
	//-------------------------------------------------------------------------------
	
	
	
	//---------------------------------------------------------------------------
	//teflon
	G4double ener[2] = {.1*eV, 10.*eV};
	G4double specular_lobe[2] = {1.0, 1.0};
	G4double specular_spike[2] = {0.0, 0.0};
	G4double back_scatter[2] = {0.0, 0.0};

	G4double teflon_rindex[2] = {1.35, 1.35}; //wiki (Optical properties of materials for concentrator photovoltaic systems) [1.35-1.38]
	G4double teflon_refl[2] = {0.99, 0.99}; // Janecek2010

	teflon_unified = new G4OpticalSurface("polishedWhitePainted", unified);
	teflon_unified->SetType(dielectric_dielectric);
	teflon_unified->SetModel(unified);
	teflon_unified->SetFinish(groundbackpainted);
	teflon_unified->SetSigmaAlpha(1.3 * degree); // Janecek2010

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
	
	
	//-----------------------------------------------------------------------------
	// �������� ����������� ����������
	silicaCathodeMaterial = new G4OpticalSurface("silicaCathodeMaterial", unified);
	silicaCathodeMaterial->SetType(dielectric_metal);
	silicaCathodeMaterial->SetModel(unified);
	silicaCathodeMaterial->SetFinish(polished);
	silicaCathodeMaterial->SetSigmaAlpha(0.);

	G4MaterialPropertiesTable *silicaCathodeMaterialProperty = new G4MaterialPropertiesTable();
	G4double cathoderefl[2] = {0., 0.};
	G4double cathodeeff[2] = {1., 1.};
	silicaCathodeMaterialProperty->AddProperty("REFLECTIVITY", ener, cathoderefl, 2);
	silicaCathodeMaterialProperty->AddProperty("EFFICIENCY", ener, cathodeeff, 2);
	silicaCathodeMaterial->SetMaterialPropertiesTable(silicaCathodeMaterialProperty);
	//--------------------------------------------------------------------------------

	//*********************************************************************************
}