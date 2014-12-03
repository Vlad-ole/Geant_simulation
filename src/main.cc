#include <time.h>
#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4UIterminal.hh"

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

#include "Randomize.hh"
#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "RunAction.hh"
#include "PrimaryGeneratorAction.hh"

#include "EventAction.hh"
#include "SteppingAction.hh"


#include <conio.h>
#include <iostream>
#include "Singleton.h"



using namespace std;
Singleton* Singleton::single = NULL;

int  nEvents       = 0; 
int  nUsefulEvents = 0;



int main(int argc,char** argv)
{

	// Choose the Random engine
	CLHEP::HepRandom::setTheEngine(new CLHEP::RanecuEngine);

	// Seed the random number generator manually
	// -----------------------------------------
	G4long myseed = time(NULL);
	CLHEP::HepRandom::setTheSeed(myseed);
	cout << "Current time used as seed: " << myseed << G4endl;
	CLHEP::HepRandom::showEngineStatus();


	// Construct the default run manager
	G4RunManager * runManager = new G4RunManager;

	//	// set mandatory initialization classes
	DetectorConstruction* detector = new DetectorConstruction;
	runManager->SetUserInitialization(detector);
	runManager->SetUserInitialization(new PhysicsList);

	// set user action classes
	runManager->SetUserAction(new RunAction);
	runManager->SetUserAction(new PrimaryGeneratorAction());
	EventAction* eventAction = new EventAction;
	runManager->SetUserAction(eventAction);
	runManager->SetUserAction(new SteppingAction(detector,eventAction));
	//
	//Initialize G4 kernel
	runManager->Initialize();

	// visualization manager
#ifdef G4VIS_USE
	G4VisManager* visManager = new G4VisExecutive;
	visManager -> Initialize ();
#endif


	// get the pointer to the User Interface manager 
	G4UImanager* UI = G4UImanager::GetUIpointer();  

	for(g()->abs_index = 200; g()->abs_index > 1; g()->abs_index -= 5)
	{
		for (g()->SigmaAlpha_index = 0; g()->SigmaAlpha_index < 50; g()->SigmaAlpha_index += 1)
		{
			detector->ChangeDetectorConstruction(g()->SigmaAlpha_index);

			if(argc==1)
			{
				UI->ApplyCommand("/control/execute slava.mac");  
			}
			else
			{ 
				// Batch mode
				G4String command = "/control/execute ";
				G4String fileName = argv[1];
				UI->ApplyCommand(command+fileName);
			}
		}
	}


#ifdef G4VIS_USE
	delete visManager;
#endif

	// job termination
	delete runManager;

	system("pause");

	return 0;
}


