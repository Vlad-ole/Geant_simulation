#ifndef RunAction_h
#define RunAction_h 1

#include "globals.hh"
#include "G4UserRunAction.hh"

class G4Timer;
class G4Run;

class RunAction : public G4UserRunAction
{
  public:
     RunAction();
    ~RunAction();

  public:
    void BeginOfRunAction(const G4Run* aRun);
    void EndOfRunAction(const G4Run* aRun);

  private:
    G4Timer* timer;
};

#endif

