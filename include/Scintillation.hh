#ifndef SCINTILLATION_H
#define SCINTILLATION_H

#include <G4Scintillation.hh>


class Scintillation : public G4Scintillation
{
public:
    Scintillation(const G4String &processName="Scintillation", G4ProcessType type=fElectromagnetic);
    virtual ~Scintillation();
	
    G4VParticleChange* PostStepDoIt(const G4Track& aTrack, const G4Step&  aStep);
};



#endif // SCINTILLATION_H
