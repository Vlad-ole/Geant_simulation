#ifndef SteppingAction_h
#define SteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"

class DetectorConstruction;
class EventAction;

class SteppingAction : public G4UserSteppingAction
{
  public:
    SteppingAction(DetectorConstruction* myDC, EventAction* myEA);
    virtual ~SteppingAction(){};

    virtual void UserSteppingAction(const G4Step*);
    
  private:
    DetectorConstruction* myDetector;
    EventAction* eventAction;
};

#endif
