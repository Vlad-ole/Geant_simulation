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

//#include <time.h>

using namespace std;
Singleton* Singleton::single = NULL;

int  nEvents       = 0; 
int  nUsefulEvents = 0;




int main(int argc, char** argv)
{
	long t1 = clock();

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

	string temp_string = g()->path_read + "x_ray\\Analytical_model_out.dat";
	runManager->SetUserAction( new PrimaryGeneratorAction( /*temp_string.c_str() */) );
	
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

	
   
	//for(g()->abs_index = 200; g()->abs_index > 1; g()->abs_index -= 5)
	{
		for (g()->CathRefl_index = 0.0; g()->CathRefl_index < 1; g()->CathRefl_index += 0.1)
		{
			g()->SigmaAlpha_index = 0.0741;
			detector->ChangeDetectorConstruction(g()->SigmaAlpha_index);
			detector->ChangeCathRefl();

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

	cout << "\a \a \a \a" ;

	long t2 = clock();

	cout << endl;
	cout << "Lead time is " << (t2 - t1)/1000.0 << " seconds " << " (or " << (t2 - t1)/60000.0 << " minutes)" << endl;
	cout << endl;

	system("pause");

	return 0;
}


