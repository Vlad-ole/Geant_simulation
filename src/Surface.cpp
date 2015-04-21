#include "DetectorConstruction.hh"
#include <G4OpticalSurface.hh>
#include <G4SystemOfUnits.hh> // this has appeared in GEANT4_10
#include "ReadConstants.h"
#include "Singleton.h"

void DetectorConstruction::defineSurfaces()
{
	
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
	
	G4MaterialPropertiesTable* polishedAir_property = new G4MaterialPropertiesTable();
	
	polishedAir_property->AddProperty("SPECULARLOBECONSTANT", ener, specular_lobe,2);
	polishedAir_property->AddProperty("SPECULARSPIKECONSTANT", ener, specular_spike,2);
	polishedAir_property->AddProperty("BACKSCATTERCONSTANT", ener, back_scatter,2);
	polishedAir->SetMaterialPropertiesTable(polishedAir_property);
		
}

