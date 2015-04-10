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
	
	//YAP:Ce property is used
	ReadConstants *LuYAG_Pr_ABSLENGTH = new ReadConstants(g()->string_LuYAG_Pr_absorption_length, 1*eV, 1*mm);


	luyag_pr = new G4MaterialPropertiesTable();
	luyag_pr->AddProperty("FASTCOMPONENT", LuYAG_Pr_FASTCOMPONENT->get_x_array(), LuYAG_Pr_FASTCOMPONENT->get_y_array(), LuYAG_Pr_FASTCOMPONENT->get_array_size());
	luyag_pr->AddProperty("RINDEX",        LuYAG_Pr_RINDEX->get_x_array(), LuYAG_Pr_RINDEX->get_y_array(), LuYAG_Pr_RINDEX->get_array_size());
	luyag_pr->AddProperty("ABSLENGTH",     LuYAG_Pr_ABSLENGTH->get_x_array(), LuYAG_Pr_ABSLENGTH->get_y_array(),  LuYAG_Pr_ABSLENGTH->get_array_size());
	luyag_pr->AddConstProperty("SCINTILLATIONYIELD", 32.0/keV);
	luyag_pr->AddConstProperty("RESOLUTIONSCALE",1.0);
	luyag_pr->AddConstProperty("FASTTIMECONSTANT",41.0*ns);
	luyag_pr->AddConstProperty("YIELDRATIO",1.0);
	LuYAG_Pr->SetMaterialPropertiesTable(luyag_pr);
	//--------------------------------------------------------------------------------------


	//---------------------------------------------------------------------------------------
	//создание материала LGSO:Ce
	G4Material* LGSO = new G4Material("LGSO_Ce", 7.3*g/cm3, 5, kStateSolid);
	LGSO->AddElement(Lu, 16.28*perCent);
	LGSO->AddElement(Y, 58.47*perCent);
	LGSO->AddElement(Si, 6.53*perCent);
	LGSO->AddElement(O, 18.51*perCent);
	LGSO->AddElement(Ce, 0.2*perCent); // cooke2000

	// LYSO:Ce properties is used
	ReadConstants *LGSO_ce_FASTCOMPONENT = new ReadConstants(g()->string_LGSO_ce_energies, 1*eV, 1);
	ReadConstants *LGSO_ce_RINDEX = new ReadConstants(g()->string_LGSO_ce_rindex, 1*eV, 1);
	ReadConstants *LGSO_ce_ABSLENGTH = new ReadConstants(g()->string_LGSO_ce_absorption_length, 1*eV, 1*mm);


	G4MaterialPropertiesTable* LGSO_ce = new G4MaterialPropertiesTable();
	LGSO_ce->AddProperty("FASTCOMPONENT", LGSO_ce_FASTCOMPONENT->get_x_array(), LGSO_ce_FASTCOMPONENT->get_y_array(), LGSO_ce_FASTCOMPONENT->get_array_size());
	LGSO_ce->AddProperty("RINDEX",        LGSO_ce_RINDEX->get_x_array(), LGSO_ce_RINDEX->get_y_array(), LGSO_ce_RINDEX->get_array_size());
	LGSO_ce->AddProperty("ABSLENGTH",     LGSO_ce_ABSLENGTH->get_x_array(), LGSO_ce_ABSLENGTH->get_y_array(),  LGSO_ce_ABSLENGTH->get_array_size());
	LGSO_ce->AddConstProperty("SCINTILLATIONYIELD", 32.0/keV);
	LGSO_ce->AddConstProperty("RESOLUTIONSCALE",1.0);
	LGSO_ce->AddConstProperty("FASTTIMECONSTANT",41.0*ns);
	LGSO_ce->AddConstProperty("YIELDRATIO",1.0);
	LGSO->SetMaterialPropertiesTable(LGSO_ce);
	//--------------------------------------------------------------------------------------




	//---------------------------------------------------------------------------------------
	//создание материала LFS-3
	G4Material* LFS_3 = new G4Material("LFS-3", 7.35*g/cm3, 5, kStateSolid);
	LFS_3->AddElement(Lu, 16.28*perCent);// LYSO:Ce model is used
	LFS_3->AddElement(Y, 58.47*perCent);
	LFS_3->AddElement(Si, 6.53*perCent);
	LFS_3->AddElement(O, 18.51*perCent);
	LFS_3->AddElement(Ce, 0.2*perCent); 

	// LYSO:Ce properties is used
	ReadConstants *LFS_3_FASTCOMPONENT = new ReadConstants(g()->string_LFS_3_energies, 1*eV, 1);
	ReadConstants *LFS_3_RINDEX = new ReadConstants(g()->string_LFS_3_rindex, 1*eV, 1);
	ReadConstants *LFS_3_ABSLENGTH = new ReadConstants(g()->string_LFS_3_absorption_length, 1*eV, 1*mm);


	G4MaterialPropertiesTable* LFS_3_prop = new G4MaterialPropertiesTable();
	LFS_3_prop->AddProperty("FASTCOMPONENT", LFS_3_FASTCOMPONENT->get_x_array(), LFS_3_FASTCOMPONENT->get_y_array(), LFS_3_FASTCOMPONENT->get_array_size());
	LFS_3_prop->AddProperty("RINDEX",        LFS_3_RINDEX->get_x_array(), LFS_3_RINDEX->get_y_array(), LFS_3_RINDEX->get_array_size());
	LFS_3_prop->AddProperty("ABSLENGTH",     LFS_3_ABSLENGTH->get_x_array(), LFS_3_ABSLENGTH->get_y_array(),  LFS_3_ABSLENGTH->get_array_size());
	LFS_3_prop->AddConstProperty("SCINTILLATIONYIELD", 32.0/keV);
	LFS_3_prop->AddConstProperty("RESOLUTIONSCALE",1.0);
	LFS_3_prop->AddConstProperty("FASTTIMECONSTANT",41.0*ns);
	LFS_3_prop->AddConstProperty("YIELDRATIO",1.0);
	LFS_3->SetMaterialPropertiesTable(LFS_3_prop);
	//--------------------------------------------------------------------------------------


	//---------------------------------------------------------------------------------------
	//создание материала YAP:Ce
	G4Material* YAP_Ce = new G4Material("YAP_Ce", 5.35*g/cm3, 3, kStateSolid);
	YAP_Ce->AddElement(Y, 54.25*perCent);
	YAP_Ce->AddElement(Al, 16.46*perCent);
	YAP_Ce->AddElement(O, 29.29*perCent);
	

	ReadConstants *YAP_Ce_FASTCOMPONENT = new ReadConstants(g()->string_YAP_Ce_energies, 1*eV, 1);
	ReadConstants *YAP_Ce_RINDEX = new ReadConstants(g()->string_YAP_Ce_rindex, 1*eV, 1);
	ReadConstants *YAP_Ce_ABSLENGTH = new ReadConstants(g()->string_YAP_Ce_absorption_length, 1*eV, 1*mm);


	G4double dummy_ABSLENGTH[numentries] = { 0.1*mm, 0.1*mm };

	G4MaterialPropertiesTable* YAP_Ce_prop = new G4MaterialPropertiesTable();
	YAP_Ce_prop->AddProperty("FASTCOMPONENT", YAP_Ce_FASTCOMPONENT->get_x_array(), YAP_Ce_FASTCOMPONENT->get_y_array(), YAP_Ce_FASTCOMPONENT->get_array_size());
	YAP_Ce_prop->AddProperty("RINDEX",        YAP_Ce_RINDEX->get_x_array(), YAP_Ce_RINDEX->get_y_array(), YAP_Ce_RINDEX->get_array_size());
	
	//YAP_Ce_prop->AddProperty("ABSLENGTH",     energies, dummy_ABSLENGTH, 2);
	YAP_Ce_prop->AddProperty("ABSLENGTH", YAP_Ce_ABSLENGTH->get_x_array(), YAP_Ce_ABSLENGTH->get_y_array(), YAP_Ce_ABSLENGTH->get_array_size());

	YAP_Ce_prop->AddConstProperty("SCINTILLATIONYIELD", 32.0/keV);
	YAP_Ce_prop->AddConstProperty("RESOLUTIONSCALE", 4.55);
	YAP_Ce_prop->AddConstProperty("FASTTIMECONSTANT",41.0*ns);
	YAP_Ce_prop->AddConstProperty("YIELDRATIO",1.0);
	YAP_Ce->SetMaterialPropertiesTable(YAP_Ce_prop);
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

	ReadConstants *BorosilicateGlass_RINDEX = new ReadConstants(g()->string_BorosilicateGlass_RINDEX, 1*eV, 1);
	ReadConstants *BorosilicateGlass_ABSLENGTH = new ReadConstants(g()->string_BorosilicateGlass_ABSLENGTH, 1*eV, 1*mm);
	
	G4MaterialPropertiesTable* BorosilicateGlassprop = new G4MaterialPropertiesTable();
	BorosilicateGlassprop->AddProperty("RINDEX", BorosilicateGlass_RINDEX->get_x_array(), BorosilicateGlass_RINDEX->get_y_array(), BorosilicateGlass_RINDEX->get_array_size());
	BorosilicateGlassprop->AddProperty("ABSLENGTH", BorosilicateGlass_ABSLENGTH->get_x_array(), BorosilicateGlass_ABSLENGTH->get_y_array(), BorosilicateGlass_ABSLENGTH->get_array_size());
	FusedSilica->SetMaterialPropertiesTable(BorosilicateGlassprop);
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

void DetectorConstruction::ChangeMaterials()
{
	
	//G4double energies[2] = { 0.1*eV, 10.0*eV };
	//G4double abs_len[2] = { (g()->abs_index)*mm, (g()->abs_index)*mm };

	//luyag_pr->AddProperty("ABSLENGTH", energies, abs_len,  2);
}

