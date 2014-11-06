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
	G4double airabsorpti[numentries] = { 100.*m, 100.*m }; // avoid infinite light-paths
	G4MaterialPropertiesTable* airprop = new G4MaterialPropertiesTable();
	airprop->AddProperty("ABSLENGTH", energies, airabsorpti, numentries);
	airprop->AddProperty("RINDEX", energies, vacrindices, numentries);
	Air->SetMaterialPropertiesTable(airprop);
	//------------------------------



	//---------------------------------------------------------------------------------------
	//создание материала LYSO:Ce
	G4Material* LYSO = new G4Material("LYSO_Ce", 7.1*g/cm3, 5, kStateSolid);
	LYSO->AddElement(Lu, 71.43*perCent);
	LYSO->AddElement(Y, 4.03*perCent);
	LYSO->AddElement(Si, 6.37*perCent);
	LYSO->AddElement(O, 18.14*perCent);
	LYSO->AddElement(Ce, 0.02*perCent); // cooke2000

	ReadConstants *lyso_ce_FASTCOMPONENT = new ReadConstants(g()->string_lyso_ce_energies, 1*eV, 1);
	ReadConstants *lyso_ce_RINDEX = new ReadConstants(g()->string_lyso_ce_rindex, 1*eV, 1);
	ReadConstants *lyso_ce_ABSLENGTH = new ReadConstants(g()->string_lyso_ce_absorption_length, 1*eV, 1*mm);


	G4MaterialPropertiesTable* lyso_ce = new G4MaterialPropertiesTable();
	lyso_ce->AddProperty("FASTCOMPONENT", lyso_ce_FASTCOMPONENT->get_x_array(), lyso_ce_FASTCOMPONENT->get_y_array(), lyso_ce_FASTCOMPONENT->get_array_size());
	lyso_ce->AddProperty("RINDEX",        lyso_ce_RINDEX->get_x_array(), lyso_ce_RINDEX->get_y_array(), lyso_ce_RINDEX->get_array_size());
	lyso_ce->AddProperty("ABSLENGTH",     lyso_ce_ABSLENGTH->get_x_array(), lyso_ce_ABSLENGTH->get_y_array(),  lyso_ce_ABSLENGTH->get_array_size());
	lyso_ce->AddConstProperty("SCINTILLATIONYIELD", 32.0/keV);
	lyso_ce->AddConstProperty("RESOLUTIONSCALE",1.0);
	lyso_ce->AddConstProperty("FASTTIMECONSTANT",41.0*ns);
	lyso_ce->AddConstProperty("YIELDRATIO",1.0);
	LYSO->SetMaterialPropertiesTable(lyso_ce);
	//--------------------------------------------------------------------------------------


	//---------------------------------------------------------------------------------------
	//создание материала LuYAG:Pr
	G4Material* LuYAG_Pr = new G4Material("LuYAG_Pr", 6.2*g/cm3, 5, kStateSolid);
	LuYAG_Pr->AddElement(Lu, 49.96*perCent); // Winicjusz Drozdowski33000 photons per MeV from mixed  (Lu0.75Y0.25)3Al5O12:Pr scintillator crystals 
	LuYAG_Pr->AddElement(Y, 8.43*perCent); 
	LuYAG_Pr->AddElement(Al, 17.10*perCent);
	LuYAG_Pr->AddElement(O, 24.35*perCent);
	LuYAG_Pr->AddElement(Pr, 0.16*perCent); 
	
	//Lu[part] = ( N(Lu)*m(Lu) ) / (  N(Lu)*m(Lu) + ... + N(O)*m(O) )

	//from porosev vysheclav (porosev@gmail.com)
	ReadConstants *LuYAG_Pr_FASTCOMPONENT = new ReadConstants(g()->string_LuYAG_Pr_energies, 1*eV, 1);
	
	//Performance of thin long scintillator strips of GSO:Ce, LGSO:Ce and LuAG:Pr for low energy g-rays
	//Single crystalline LuAG fibers for homogeneous dual-readout calorimeters
	ReadConstants *LuYAG_Pr_RINDEX = new ReadConstants(g()->string_LuYAG_Pr_rindex, 1*eV, 1); 	
	
	ReadConstants *LuYAG_Pr_ABSLENGTH = new ReadConstants(g()->string_LuYAG_Pr_absorption_length, 1*eV, 1*mm);


	G4MaterialPropertiesTable* luyag_pr = new G4MaterialPropertiesTable();
	luyag_pr->AddProperty("FASTCOMPONENT", LuYAG_Pr_FASTCOMPONENT->get_x_array(), LuYAG_Pr_FASTCOMPONENT->get_y_array(), LuYAG_Pr_FASTCOMPONENT->get_array_size());
	luyag_pr->AddProperty("RINDEX",        LuYAG_Pr_RINDEX->get_x_array(), LuYAG_Pr_RINDEX->get_y_array(), LuYAG_Pr_RINDEX->get_array_size());
	luyag_pr->AddProperty("ABSLENGTH",     LuYAG_Pr_ABSLENGTH->get_x_array(), LuYAG_Pr_ABSLENGTH->get_y_array(),  LuYAG_Pr_ABSLENGTH->get_array_size());
	luyag_pr->AddConstProperty("SCINTILLATIONYIELD", 32.0/keV);
	luyag_pr->AddConstProperty("RESOLUTIONSCALE",1.0);
	luyag_pr->AddConstProperty("FASTTIMECONSTANT",41.0*ns);
	luyag_pr->AddConstProperty("YIELDRATIO",1.0);
	LuYAG_Pr->SetMaterialPropertiesTable(luyag_pr);
	//--------------------------------------------------------------------------------------



	//--------------------------------------------------------------------------------------
	//оптическая мазка (Grease BC-630)
	G4Material* Polydimethylsiloxane = new G4Material("Polydimethylsiloxane", 0.97*g/cm3, 4, kStateLiquid);
	Polydimethylsiloxane->AddElement(Si, 1);
	Polydimethylsiloxane->AddElement(O, 1);
	Polydimethylsiloxane->AddElement(C, 2);
	Polydimethylsiloxane->AddElement(H, 6);

	ReadConstants *polydimethylsiloxane_RINDEX = new ReadConstants(g()->string_polydimethylsiloxane_RINDEX, 1*eV, 1);
	ReadConstants *polydimethylsiloxane_ABSLENGTH = new ReadConstants(g()->string_polydimethylsiloxane_absorption_length, 1*eV, 1*mm);

	G4MaterialPropertiesTable* polydimethylsiloxane = new G4MaterialPropertiesTable();
	polydimethylsiloxane->AddProperty("RINDEX", polydimethylsiloxane_RINDEX->get_x_array(), polydimethylsiloxane_RINDEX->get_y_array(), polydimethylsiloxane_RINDEX->get_array_size());
	polydimethylsiloxane->AddProperty("ABSLENGTH", polydimethylsiloxane_ABSLENGTH->get_x_array(), polydimethylsiloxane_ABSLENGTH->get_y_array(), polydimethylsiloxane_ABSLENGTH->get_array_size());
	Polydimethylsiloxane->SetMaterialPropertiesTable(polydimethylsiloxane);
	//--------------------------------------------------------------------------------------


	//--------------------------------------------------------------------------------------
	//Стекло ФЭУ (k8)
	G4Material* FusedSilica = new G4Material("FusedSilica", 2.201*g/cm3, 2, kStateSolid);
	FusedSilica->AddElement(Si, 1);
	FusedSilica->AddElement(O, 2);

	ReadConstants *fusedsilica_RINDEX = new ReadConstants(g()->string_fusedsilica_RINDEX, 1*eV, 1);
	ReadConstants *fusedsilica_ABSLENGTH = new ReadConstants(g()->string_fusedsilica_ABSLENGTH, 1*eV, 1*mm);
	
	G4MaterialPropertiesTable* fusedsilicaprop = new G4MaterialPropertiesTable();
	fusedsilicaprop->AddProperty("RINDEX", fusedsilica_RINDEX->get_x_array(), fusedsilica_RINDEX->get_y_array(), fusedsilica_RINDEX->get_array_size());
	fusedsilicaprop->AddProperty("ABSLENGTH", fusedsilica_ABSLENGTH->get_x_array(), fusedsilica_ABSLENGTH->get_y_array(), fusedsilica_ABSLENGTH->get_array_size());
	FusedSilica->SetMaterialPropertiesTable(fusedsilicaprop);
	//--------------------------------------------------------------------------------------


	//-------------------------------------------------------------------------------------
	// Bialkali Cathode (dummy)
	G4Material* BialkaliCathode = new G4Material("BialkaliCathode", 3*g/cm3, 3, kStateSolid);
	BialkaliCathode->AddElement(Sb, 1);
	BialkaliCathode->AddElement(Rb, 1);
	BialkaliCathode->AddElement(Cs, 1);

	G4MaterialPropertiesTable* bialkalicathodeprop = new G4MaterialPropertiesTable();
	BialkaliCathode->SetMaterialPropertiesTable(bialkalicathodeprop);
	//--------------------------------------------------------------------------------------

}

