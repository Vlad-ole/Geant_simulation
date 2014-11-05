#ifndef EventAction_h
#define EventAction_h 1

#include "G4UserEventAction.hh"
#include "G4ThreeVector.hh"
#include "globals.hh"

class G4Event;

class EventAction : public G4UserEventAction
{
  public:
    EventAction();
    virtual ~EventAction();

  public:
    virtual void   BeginOfEventAction(const G4Event*);
    virtual void   EndOfEventAction(const G4Event*);

	void AddtotDetector(G4ThreeVector pos, G4double val);

};

#endif


