#include "G4Material.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4SteppingManager.hh"
#include "G4Step.hh"
#include "G4StepPoint.hh"
#include "G4ProcessManager.hh"
#include "G4SDManager.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4OpBoundaryProcess.hh"

#include "SteppingAction.hh"
#include "DetectorConstruction.hh"
#include "EventAction.hh"
#include "CathodeSD.hh"
#include "Singleton.h"


SteppingAction::SteppingAction(DetectorConstruction* myDC, EventAction* myEA)
:myDetector(myDC), eventAction(myEA)
{
}

void SteppingAction::UserSteppingAction(const G4Step* theStep)
{
  G4Track* theTrack = theStep->GetTrack();
 
  G4StepPoint* thePrePoint = theStep->GetPreStepPoint();
  G4VPhysicalVolume* thePrePV = thePrePoint->GetPhysicalVolume();

  G4StepPoint* thePostPoint = theStep->GetPostStepPoint();
  G4VPhysicalVolume* thePostPV = thePostPoint->GetPhysicalVolume();

  //---------------------


  //---------------------


  //find the boundary process only once
  static G4OpBoundaryProcess* boundary=NULL;
  if(!boundary)
  {
    G4ProcessManager* pm = theStep->GetTrack()->GetDefinition()->GetProcessManager();
    G4int nprocesses     = pm->GetProcessListLength();
    G4ProcessVector* pv  = pm->GetProcessList();

	for(G4int i=0;i<nprocesses;i++)
	{
      if((*pv)[i]->GetProcessName()=="OpBoundary")
	  {
        boundary = (G4OpBoundaryProcess*)(*pv)[i];
        break;
      }
    }
  }


  //For Optical photon only
  G4ParticleDefinition* particleType = theTrack->GetDefinition();
  if(particleType==G4OpticalPhoton::OpticalPhotonDefinition())
  {

    //Check to see if the partcile was actually at a boundary
    //Otherwise the boundary status may not be valid
    //Prior to Geant4.6.0-p1 this would not have been enough to check
    if(thePostPoint->GetStepStatus() == fGeomBoundary)
	{
		if(boundary)
		{
			G4OpBoundaryProcessStatus boundaryStatus = boundary->GetStatus();

			if(boundaryStatus == FresnelReflection)
				g()->NumberOfReflections++;
			
			
			//--------------------------------------------------------------------
			//G4ThreeVector v_temp_poz = theTrack->GetPosition();
			//G4ThreeVector v_temp_mom = theTrack->GetMomentumDirection();
			//
			//if( boundaryStatus != 12  && (v_temp_poz.getZ() > 0) && (v_temp_mom.getZ() > 0) )
			//{
			//	
			//	g()->file_boundary_process << boundaryStatus /*<< "\t" << v_temp_poz.getZ() << "\t" << v_temp_mom.getZ()*/  << endl;
			//}
			//--------------------------------------------------------------------
			

			switch(boundaryStatus)
			{
				case Detection://Note, this assumes that the volume causing detection
								//is the photocathode because it is the only one with
								//non-zero efficiency

								//Triger sensitive detector manually since photon is
								//absorbed but status was Detection
								{
									G4SDManager* SDman = G4SDManager::GetSDMpointer();
									G4String sdName="/detector/sensitiveDetector";
									CathodeSD* pmtSD = (CathodeSD*)SDman->FindSensitiveDetector(sdName);
									if(pmtSD)pmtSD->ProcessHits_Optical(theStep,NULL);
								}
								break;

				case Absorption:
				case FresnelReflection:
				case TotalInternalReflection:
				case LambertianReflection:
				case LobeReflection:
				case SpikeReflection:
				case BackScattering:
				break;

				default:
				break;
			}
		}
    }//if Boundary
  }//if opt photons
}


