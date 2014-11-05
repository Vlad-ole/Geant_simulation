#include "StepMax.hh"


StepMax::StepMax(const G4String& processName)
 : G4VDiscreteProcess(processName),MaxChargedStep(DBL_MAX)
{
}
 

StepMax::~StepMax() {  }


G4bool StepMax::IsApplicable(const G4ParticleDefinition& particle) 
{ 
  return (particle.GetPDGCharge() != 0.);
}

    
void StepMax::SetMaxStep(G4double step) {MaxChargedStep = step;}


G4double StepMax::PostStepGetPhysicalInteractionLength(const G4Track&,
                                                  G4double,
                                                  G4ForceCondition* condition )
{
  // condition is set to "Not Forced"
  *condition = NotForced;
  
  return MaxChargedStep;
}


G4VParticleChange* StepMax::PostStepDoIt(const G4Track& aTrack, const G4Step&)
{
   // do nothing
   aParticleChange.Initialize(aTrack);
   return &aParticleChange;
}



