#include "DetectorConstruction.hh"
#include <G4NistManager.hh>
#include <G4SystemOfUnits.hh> // this has appeared in GEANT4_10

#include "ReadConstants.h"
#include <vector>
#include "Singleton.h"
using namespace std;

void DetectorConstruction::defineMaterials()
{

	//--------- Material definition ---------

	G4NistManager* man = G4NistManager::Instance();

	G4Element *C = man->FindOrBuildElement("C");
	G4Element *H = man->FindOrBuildElement("H");
	G4Element *Si = man->FindOrBuildElement("Si");
	G4Element *O = man->FindOrBuildElement("O");
	G4Element *Sb = man->FindOrBuildElement("Sb");
	G4Element *Rb = man->FindOrBuildElement("Rb");
	G4Element *Cs = man->FindOrBuildElement("Cs");
	G4Element *Lu = man->FindOrBuildElement("Lu");
	G4Element *Y = man->FindOrBuildElement("Y");
	G4Element *Ce = man->FindOrBuildElement("Ce");
	G4Element *La = man->FindOrBuildElement("La");
	G4Element *Br = man->FindOrBuildElement("Br");
	G4Element *Na = man->FindOrBuildElement("Na");
	G4Element *I = man->FindOrBuildElement("I");
	G4Element *Tl = man->FindOrBuildElement("Tl");
	G4Element *Gd = man->FindOrBuildElement("Gd");
	G4Element *Al = man->FindOrBuildElement("Al");
	G4Element *Pr = man->FindOrBuildElement("Pr");

	//------------------------------
	// Air
	G4Material* Air = man->FindOrBuildMaterial("G4_AIR");
	Air->SetName("Air");
	const G4int numentries = 2;
	G4double energies[numentries] = { 0.1*eV, 10.0*eV };
	G4double vacrindices[numentries] = { 1., 1. };
	G4double airabsorpti[numentries] = { 10*m, 10*m }; // avoid infinite light-paths
	G4MaterialPropertiesTable* airprop = new G4MaterialPropertiesTable();
	airprop->AddProperty("ABSLENGTH", energies, airabsorpti, numentries);
	airprop->AddProperty("RINDEX", energies, vacrindices, numentries);
	Air->SetMaterialPropertiesTable(airprop);
	//------------------------------



	//---------------------------------------------------------------------------------------
	//создание материала LFS-3
	G4Material* LFS_3 = new G4Material("LFS-3", 7.35*g/cm3, 5, kStateSolid);
	LFS_3->AddElement(Lu, 16.28*perCent);// LYSO:Ce model is used
	LFS_3->AddElement(Y, 58.47*perCent);
	LFS_3->AddElement(Si, 6.53*perCent);
	LFS_3->AddElement(O, 18.51*perCent);
	LFS_3->AddElement(Ce, 0.2*perCent); 



	G4MaterialPropertiesTable* LFS_3_prop = new G4MaterialPropertiesTable();
	LFS_3_prop->AddProperty("FASTCOMPONENT", energies, vacrindices, 2);
	LFS_3_prop->AddProperty("RINDEX", energies, vacrindices, 2);
	LFS_3_prop->AddProperty("ABSLENGTH", energies, airabsorpti, 2);
	LFS_3_prop->AddConstProperty("SCINTILLATIONYIELD", 32.0/keV);
	LFS_3_prop->AddConstProperty("RESOLUTIONSCALE",1.0);
	LFS_3_prop->AddConstProperty("FASTTIMECONSTANT",41.0*ns);
	LFS_3_prop->AddConstProperty("YIELDRATIO",1.0);
	LFS_3->SetMaterialPropertiesTable(LFS_3_prop);
	//--------------------------------------------------------------------------------------

	
}


