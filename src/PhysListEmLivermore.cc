//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
// $Id: PhysListEmLivermore.cc,v 1.3 2009/11/19 18:46:04 maire Exp $
// GEANT4 tag $Name: geant4-09-03-patch-02 $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo...... 

#include "PhysListEmLivermore.hh"
#include "G4ParticleDefinition.hh"
#include "G4ProcessManager.hh"

// gamma

#include "G4PhotoElectricEffect.hh"
#include "G4LivermorePhotoElectricModel.hh"

#include "G4ComptonScattering.hh"
#include "G4LivermoreComptonModel.hh"

#include "G4GammaConversion.hh"
#include "G4LivermoreGammaConversionModel.hh"

#include "G4RayleighScattering.hh" 
#include "G4LivermoreRayleighModel.hh"

// e-
#include "G4eMultipleScattering.hh"
#include "G4GoudsmitSaundersonMscModel.hh"
#include "G4WentzelVIModel.hh"
#include "G4UrbanMscModel.hh"

#include "G4eIonisation.hh"
#include "G4LivermoreIonisationModel.hh"
#include "G4UniversalFluctuation.hh"

#include "G4eBremsstrahlung.hh"
#include "G4LivermoreBremsstrahlungModel.hh"

#include "G4MollerBhabhaModel.hh"

// hadrons, ions

#include "G4ionIonisation.hh"

#include "G4EmProcessOptions.hh"
#include "G4MscStepLimitType.hh"

#include "G4LossTableManager.hh"
#include "G4UAtomicDeexcitation.hh"

#include <G4SystemOfUnits.hh> // this has appeared in GEANT4_10


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PhysListEmLivermore::PhysListEmLivermore(const G4String& name)
  :  G4VPhysicsConstructor(name)
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PhysListEmLivermore::~PhysListEmLivermore()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PhysListEmLivermore::ConstructProcess()
{
  // Add standard EM Processes

  aParticleIterator->reset(); // theParticleIterator has been changed to aParticleIterator
  while( (*aParticleIterator)() ){
    G4ParticleDefinition* particle = aParticleIterator->value();
    G4ProcessManager* pmanager = particle->GetProcessManager();
    G4String particleName = particle->GetParticleName();

    //Applicability range for Livermore models
    //for higher energies, the Standard models are used   
	G4double highEnergyLimit = 150*keV;
         
    if (particleName == "gamma") {
      // gamma         

      G4PhotoElectricEffect* phot = new G4PhotoElectricEffect();
      G4LivermorePhotoElectricModel* photModel = new G4LivermorePhotoElectricModel();
      photModel->SetHighEnergyLimit(highEnergyLimit);
      phot->AddEmModel(0, photModel);
      pmanager->AddDiscreteProcess(phot);

      G4ComptonScattering* compt = new G4ComptonScattering();
      G4LivermoreComptonModel* comptModel = new G4LivermoreComptonModel();
      comptModel->SetHighEnergyLimit(highEnergyLimit);
      compt->AddEmModel(0, comptModel);
      pmanager->AddDiscreteProcess(compt);


      G4RayleighScattering* rayl = new G4RayleighScattering();
      G4LivermoreRayleighModel* raylModel = new G4LivermoreRayleighModel();
      raylModel->SetHighEnergyLimit(highEnergyLimit);
      rayl->AddEmModel(0, raylModel);
      pmanager->AddDiscreteProcess(rayl);
      
    } else if (particleName == "e-")  {
      //electron

      G4eMultipleScattering* msc = new G4eMultipleScattering();
      msc->SetStepLimitType(fUseDistanceToBoundary);
      //msc->AddEmModel(1, new G4GoudsmitSaundersonMscModel);  //There is possibility to change models...
	  //msc->AddEmModel(1, new G4WentzelVIModel()); 
      pmanager->AddProcess(msc, -1, 1, 1);

      G4eIonisation* eIoni = new G4eIonisation();
      G4LivermoreIonisationModel* eIoniModel = new G4LivermoreIonisationModel();
	  //G4MollerBhabhaModel* eIoniModel = new G4MollerBhabhaModel();
	  eIoniModel->SetHighEnergyLimit(highEnergyLimit); 
      eIoni->AddEmModel(0, eIoniModel, new G4UniversalFluctuation() );
      pmanager->AddProcess(eIoni, -1, 2, 2);
      
      G4eBremsstrahlung* eBrem = new G4eBremsstrahlung();
      G4LivermoreBremsstrahlungModel* eBremModel = new G4LivermoreBremsstrahlungModel();
      eBremModel->SetHighEnergyLimit(highEnergyLimit);
      eBrem->AddEmModel(0, eBremModel);
      pmanager->AddProcess(eBrem,                   -1, -3, 3);
      	    
    } 

  }


  // Em options
  //
  // Main options and setting parameters are shown here.
  // Several of them have default values.
  //
  G4EmProcessOptions emOptions;
  
  //physics tables
  //
  emOptions.SetMinEnergy(10*eV);	//default 100 eV   
  emOptions.SetMaxEnergy(150*keV);	//default 100 TeV 
  emOptions.SetDEDXBinning(12*10);	//default=12*7
  emOptions.SetLambdaBinning(12*10);	//default=12*7
  
  //multiple coulomb scattering
  //
  emOptions.SetMscStepLimitation(fUseSafety);  //default
   
  // Deexcitation
  //
  G4VAtomDeexcitation* de = new G4UAtomicDeexcitation();
  de->SetFluo(true);
  de->SetAuger(true);   
  de->SetPIXE(false);  
  G4LossTableManager::Instance()->SetAtomDeexcitation(de);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

