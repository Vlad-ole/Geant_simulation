#ifndef PhysicsList_h
#define PhysicsList_h 1

#include "G4VModularPhysicsList.hh"
#include "globals.hh"

class G4ProductionCuts;
class G4VPhysicsConstructor;


class PhysicsList: public G4VModularPhysicsList
{
  public:
    PhysicsList();
   ~PhysicsList();

    void ConstructParticle();
	void ConstructOptical();

    void ConstructProcess(); 
 //              
    void AddPhysicsList(const G4String& name);
    void AddStepMax();       
 //   
    void SetCuts();
    void SetCutForGamma(G4double);
    void SetCutForElectron(G4double);
    void SetCutForPositron(G4double);
 //     
  private:
  
    G4String emName;
    G4VPhysicsConstructor*  emPhysicsList;
    
    G4double cutForGamma;
    G4double cutForElectron;
};

#endif



