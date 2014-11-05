#include <iostream>
using namespace std;

// Make this appear first!
#include "G4Timer.hh"

#include "RunAction.hh"
#include "G4Run.hh"
#include "G4UImanager.hh"
#include "G4ios.hh"


RunAction::RunAction()
{
  timer = new G4Timer;
}

RunAction::~RunAction()
{
  delete timer;
}

void RunAction::BeginOfRunAction(const G4Run* aRun)
{
  cout << "RunAction::BeginOfRunAction. Run " << aRun->GetRunID() << " start." << endl;
  timer->Start();
}

void RunAction::EndOfRunAction(const G4Run* aRun)
{
  timer->Stop();
  cout << "RunAction::EndOfRunAction. number of event = " << aRun->GetNumberOfEvent() << endl;
  cout << " " << *timer << endl;
}

