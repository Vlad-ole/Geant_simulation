#include "CathodeSD.hh"

#include <G4HCofThisEvent.hh>
#include <G4Step.hh>
#include <G4ThreeVector.hh>
#include <G4Track.hh>
#include <G4DynamicParticle.hh>
#include <G4SDManager.hh>
#include <G4ios.hh>
#include "G4ParticleTypes.hh"
#include "G4ParticleDefinition.hh"


#include "Singleton.h"

#include <iostream>
#include <fstream>

#define DEBAG_MODE

CathodeSD::CathodeSD(G4String name, G4VPhysicalVolume *cathode) : G4VSensitiveDetector(name), _cathode(cathode)
{
}

CathodeSD::~CathodeSD()
{
}

void CathodeSD::Initialize(G4HCofThisEvent* HCE)
{
	_nHits = 0;
}

G4bool CathodeSD::ProcessHits(G4Step*, G4TouchableHistory*)
{
	return true;
}

//Generates a hit and uses the postStepPoint's mother volume replica number
//PostStepPoint because the hit is generated manually when the photon is
//absorbed by the photocathode

G4bool CathodeSD::ProcessHits_Optical(const G4Step* aStep, G4TouchableHistory* )
{

	//need to know if this is an optical photon
	if(aStep->GetTrack()->GetDefinition()!= G4OpticalPhoton::OpticalPhotonDefinition()) return false;

	//add information about hit to collection
	_nHits++;

	/*G4StepPoint * thePrePoint  = aStep->GetPostStepPoint();
	G4ThreeVector pos    = thePrePoint->GetPosition();
	G4double energy = thePrePoint->GetTotalEnergy();
	g()->file_energy << energy << endl;*/

	return true;
}

void CathodeSD::EndOfEvent(G4HCofThisEvent*)
{
	//.. print info about collection of hits
	

	
#ifdef DEBAG_MODE
	if (g()->summ_number_of_photons)
		g()->file_num_of_photons << g()->summ_number_of_photons << G4endl;
	//cout << "num_of_photons =\t" << g()->summ_number_of_photons <<  endl;

	g()->file_num_of_reg_photons << _nHits << G4endl;
	//cout << "num_of_reg_photons =\t" << _nHits << endl;
#endif

	if (_nHits!=0)
	{

		#ifdef DEBAG_MODE
		g()->file_ph_coll << _nHits/g()->summ_number_of_photons << G4endl;
		//cout << "ph_coll =\t" << _nHits/g()->summ_number_of_photons << endl;
		#endif
		
		(g()->LightCollection).push_back(_nHits/g()->summ_number_of_photons);
	}

	g()->NumberOfRegPhotons += _nHits;
	g()->NumberOfBornPhotons += g()->summ_number_of_photons;
	g()->summ_number_of_photons=0;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

