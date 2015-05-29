#include <iostream>
using namespace std;

// Make this appear first!
#include "G4Timer.hh"

#include "RunAction.hh"
#include "G4Run.hh"
#include "G4UImanager.hh"
#include "G4ios.hh"
#include "Singleton.h"


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
	cout << endl;
	cout << "RunAction::BeginOfRunAction. Run " << aRun->GetRunID() << " start." << endl;
	timer->Start();

	(g()->LightCollection).clear();
	g()->NumberOfReflections = 0;
	g()->NumberOfBornPhotons = 0;
	g()->NumberOfRegPhotons = 0;
}

void RunAction::EndOfRunAction(const G4Run* aRun)
{
	timer->Stop();
	cout << "RunAction::EndOfRunAction. number of event = " << aRun->GetNumberOfEvent() << endl;
	
	double sum_lc = 0;
	for (int i = 0; i < (g()->LightCollection).size(); i++)
	{
		sum_lc += g()->LightCollection[i];
	}

	
	cout << sum_lc / (g()->LightCollection).size() << endl;
	g()->file_run_lc << /*g()->abs_index << "\t" << */ g()->CathRefl_index << "\t" << sum_lc / (g()->LightCollection).size() << endl;
	//g()->file_boundary_process << g()->SigmaAlpha_index << "\t" << ((double) g()->NumberOfReflections) / g()->NumberOfBornPhotons << endl;
	//g()->file_boundary_process << g()->NumberOfRegPhotons << "\t" << ((double) g()->NumberOfReflections) <<  endl;
		
	
	cout << " " << *timer << endl;
}

