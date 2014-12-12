#include "EventAction.hh"

#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4VVisManager.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4UImanager.hh"
#include "G4ios.hh"


#include "Scintillation.hh"
#include "Singleton.h"

#include <iostream>
#include <fstream>


EventAction::EventAction()
{
}


EventAction::~EventAction()
{
}

void EventAction::AddtotDetector(G4ThreeVector pos, G4double val)
{
	//file_4 << pos.x()/mm << "\t" << pos.y()/mm << endl;
}


void EventAction::BeginOfEventAction(const G4Event* event)
{
	G4int eventNb = event->GetEventID();

	if(eventNb < 10)
	{		
		G4cout << "\n---> Begin of event: " << eventNb << G4endl;
	}
	else
	{
		if(eventNb % 10 == 0)
			G4cout << "\n---> Begin of event: " << eventNb << G4endl;
	}
}


void EventAction::EndOfEventAction(const G4Event* evt)
{
	
}

