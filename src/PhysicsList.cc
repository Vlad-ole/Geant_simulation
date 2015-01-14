#include <iostream>
using namespace std;

#include "PhysicsList.hh"

#include "PhysListEmStandard.hh"
#include "PhysListEmLivermore.hh"
#include "PhysListEmPenelope.hh"

#include "G4LossTableManager.hh"
#include "G4UnitsTable.hh"

#include "G4Region.hh"
#include "G4RegionStore.hh"

#include <G4SystemOfUnits.hh> // this has appeared in GEANT4_10


PhysicsList::PhysicsList() : G4VModularPhysicsList()
{
	G4LossTableManager::Instance();

	//// EM physics
	emPhysicsList = new PhysListEmLivermore();
	//emPhysicsList = new PhysListEmStandard();
	defaultCutValue = 0.01*mm;
	cutForGamma     = defaultCutValue;
	cutForElectron  = defaultCutValue;

	SetVerboseLevel(1);
}


PhysicsList::~PhysicsList()
{
	delete emPhysicsList; 
}


void PhysicsList::AddPhysicsList(const G4String& name)
{
	if (verboseLevel>1) 
	{
		cout << "PhysicsList::AddPhysicsList: <" << name << ">" << endl;
	}

	if (name == emName) return;

	if (name == "standard") 
	{

	  emName = name;
	  delete emPhysicsList;
	  emPhysicsList = new PhysListEmStandard(name);
	      
	} 
	else if (name == "livermore") 
	{

	  emName = name;
	  delete emPhysicsList;
	  emPhysicsList = new PhysListEmLivermore(name);
	  
	} 
	else if (name == "penelope") 
	{

	  emName = name;
	  delete emPhysicsList;
	  emPhysicsList = new PhysListEmPenelope(name);

	} 
	else 
	{

	  cout << "PhysicsList::AddPhysicsList: <" << name << ">" << " is not defined" << endl;
	}
}


// Bosons
#include "G4ChargedGeantino.hh"
#include "G4Geantino.hh"
#include "G4Gamma.hh"
#include "G4OpticalPhoton.hh"

// leptons
#include "G4Electron.hh"
#include "G4Positron.hh"


// Nuclei
#include "G4Deuteron.hh"
#include "G4Triton.hh"
#include "G4Alpha.hh"
#include "G4GenericIon.hh"

void PhysicsList::ConstructParticle()
{
	// pseudo-particles
	//G4Geantino::GeantinoDefinition();
	//G4ChargedGeantino::ChargedGeantinoDefinition();

	// gamma
	G4Gamma::GammaDefinition();

	// optical photon
	G4OpticalPhoton::OpticalPhotonDefinition();

	// leptons
	G4Electron::ElectronDefinition();
	G4Positron::PositronDefinition();

	// ions
	G4Deuteron::DeuteronDefinition();
	G4Triton::TritonDefinition();
	G4Alpha::AlphaDefinition();
	G4GenericIon::GenericIonDefinition();
}


#include "G4EmProcessOptions.hh"

void PhysicsList::ConstructProcess()
{
  AddTransportation();
  ConstructOptical();
  emPhysicsList->ConstructProcess();
  //AddStepMax();
}

#include "Scintillation.hh"
#include <G4Cerenkov.hh>
#include <G4OpAbsorption.hh>
#include <G4OpRayleigh.hh>
#include <G4OpBoundaryProcess.hh>
#include <G4OpWLS.hh>
#include <G4ProcessManager.hh>

void PhysicsList::ConstructOptical()
{
  G4OpAbsorption* theAbsorptionProcess = new G4OpAbsorption();
  /*G4OpRayleigh* theRayleighScattering=new G4OpRayleigh();*/

  G4OpBoundaryProcess* theBoundaryProcess = new G4OpBoundaryProcess();
 
  G4ProcessManager * pManager = G4OpticalPhoton::OpticalPhoton()->GetProcessManager();

  pManager->AddDiscreteProcess(theAbsorptionProcess);
  //pManager->AddDiscreteProcess(theRayleighScattering);
  pManager->AddDiscreteProcess(theBoundaryProcess);

  Scintillation* theScintProcess = new Scintillation();
  theScintProcess->SetScintillationYieldFactor(1.);
	// The ‘YieldFactor’ allows for different scintillation yields depending
	// on the particle type – in such case, separate scintillation processes
	// must be attached to the various particles.

  //theScintProcess->SetScintillationExcitationRatio(0.0);
  theScintProcess->SetTrackSecondariesFirst(true);

   // // Use Birks Correction in the Scintillation process
 // //G4EmSaturation* emSaturation = G4LossTableManager::Instance()->EmSaturation();
 // //theScintProcess->AddSaturation(emSaturation);

  
 
  G4Cerenkov* theCerenkovProcess = new G4Cerenkov("Cerenkov");
  theCerenkovProcess->SetMaxNumPhotonsPerStep(300);
  theCerenkovProcess->SetMaxBetaChangePerStep(10.0);
  theCerenkovProcess->SetTrackSecondariesFirst(true);

  theParticleIterator->reset();
  while( (*theParticleIterator)() )
  {
		G4ParticleDefinition* particle = theParticleIterator->value();
		pManager = particle->GetProcessManager();
		if(theCerenkovProcess->IsApplicable(*particle)){
		  pManager->AddProcess(theCerenkovProcess);
		  pManager->SetProcessOrdering(theCerenkovProcess,idxPostStep);
		}
		if(theScintProcess->IsApplicable(*particle)){
		  pManager->AddProcess(theScintProcess);
		  pManager->SetProcessOrderingToLast(theScintProcess,idxAtRest);
		  pManager->SetProcessOrderingToLast(theScintProcess,idxPostStep);
		}
  }
}



#include "G4ProcessManager.hh"
#include "StepMax.hh"

void PhysicsList::AddStepMax()
{
	// Step limitation seen as a process
	StepMax* stepMaxProcess = new StepMax();

	theParticleIterator->reset();
	while ((*theParticleIterator)())
	{
		G4ParticleDefinition* particle = theParticleIterator->value();
		G4ProcessManager* pmanager = particle->GetProcessManager();

		if (stepMaxProcess->IsApplicable(*particle) && !particle->IsShortLived())
		{
			pmanager ->AddDiscreteProcess(stepMaxProcess);
		}
	}
}


void PhysicsList::SetCuts()
{
	if (verboseLevel >0){
		cout << "PhysicsList::SetCuts:";
		cout << "CutLength : " << G4BestUnit(defaultCutValue,"Length") << endl;
	}

	// set cut values for gamma at first and for e- second and next for e+,
	// because some processes for e+/e- need cut values for gamma
	SetCutValue(cutForGamma, "gamma");
	SetCutValue(cutForElectron, "e-");
	SetCutValue(cutForElectron, "e+");

	// Set specific production cut for the region
	G4Region* aRegion = G4RegionStore::GetInstance()->GetRegion("MyRegion");
	if(aRegion)
	{
		// Define cuts object for the new region and set values
		G4ProductionCuts* cuts = new G4ProductionCuts;
		cuts->SetProductionCut(0.1*um); // for gamma, e+, e-
		// Assign cuts to region
		aRegion->SetProductionCuts(cuts);
	}

	if (verboseLevel>0) DumpCutValuesTable();
}


void PhysicsList::SetCutForGamma(G4double cut)
{
	cutForGamma = cut;
	SetParticleCuts(cutForGamma, G4Gamma::Gamma());
}


void PhysicsList::SetCutForElectron(G4double cut)
{
	cutForElectron = cut;
	SetParticleCuts(cutForElectron, G4Electron::Electron());
	SetParticleCuts(cutForElectron, G4Positron::Positron());
}

