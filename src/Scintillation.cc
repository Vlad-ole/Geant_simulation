#include "Scintillation.hh"
#include <G4VParticleChange.hh>
#include "Singleton.h"

Scintillation::Scintillation(const G4String &processName, G4ProcessType type)
  : G4Scintillation(processName, type)
{
}

Scintillation::~Scintillation()
{
}

G4VParticleChange* Scintillation::PostStepDoIt(const G4Track& aTrack, const G4Step&  aStep)
{
  G4VParticleChange *result =  G4Scintillation::PostStepDoIt(aTrack, aStep);
  G4double depenergy = aStep.GetTotalEnergyDeposit();

  if (depenergy > 0.0) 
  {
    G4ThreeVector pos = aStep.GetPreStepPoint()->GetPosition();

	/*
      G4cout << "scintillating: " << aStep.GetTotalEnergyDeposit()/keV << " keV of "
             << aStep.GetPreStepPoint()->GetKineticEnergy()/keV << " keV "
             << "from parent ID " << aTrack.GetTrackID() << " "
             << "deposited at (" << pos.x()/mm << " mm, " << pos.y()/mm << " mm, " << pos.z()/mm << " mm)"
             << " producing " << result->GetNumberOfSecondaries() << " optical photons"
             << G4endl;
	*/
	
	g()->summ_number_of_photons += result->GetNumberOfSecondaries();

  }

  return result;
}