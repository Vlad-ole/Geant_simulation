#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"

#define  MAX_SPECTER_DATALINES  150

enum XRAY_TYPE
{
	MONO,
	SPECTER
};


class G4ParticleGun;
class G4Event;


class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    PrimaryGeneratorAction();              //mono
	PrimaryGeneratorAction(const char* fname);   //specter
   ~PrimaryGeneratorAction();

  public:
    void GeneratePrimaries(G4Event* anEvent);

  private:
    void CommonPart();
    G4ParticleGun* particleGun;
	
	XRAY_TYPE xrType;
    int       nMaxDataLines;
    double    dEnergy[MAX_SPECTER_DATALINES];
    double    dWeight[MAX_SPECTER_DATALINES];
    double    dMaxWeight;
};

#endif


