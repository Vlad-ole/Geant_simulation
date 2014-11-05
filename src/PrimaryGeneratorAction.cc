#include <iostream>
using namespace std;

#include "PrimaryGeneratorAction.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "globals.hh"
#include "Randomize.hh"

#include <G4SystemOfUnits.hh> // this has appeared in GEANT4_10


void PrimaryGeneratorAction::CommonPart()
{
	G4int n_particle = 1;
	particleGun  = new G4ParticleGun(n_particle);

	// default particle kinematic
	G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
	G4String particleName;
	G4ParticleDefinition* particle = particleTable->FindParticle(particleName="gamma");

	particleGun->SetParticleDefinition(particle);


	particleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));
	//particleGun->SetParticlePosition(G4ThreeVector(0.*mm, 0.*mm, -3.*mm));

}

PrimaryGeneratorAction::PrimaryGeneratorAction()
{
	CommonPart();
	xrType = MONO;
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
	delete particleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
	double r1;
	double r2;
	double x=0, z=0, y=0;

	//-------------------------------------
	switch(xrType)
	{
	case MONO:
		r1=59.5; //original value
		//r1=1; //trst value
		break;

	case SPECTER:
		break;
	}

	particleGun->SetParticleEnergy(r1*keV);

	//-------------------------------------
	x = 3.0*(G4UniformRand() - 0.5)*mm; 
	y = 3.0*(G4UniformRand() - 0.5)*mm; 

	particleGun->SetParticlePosition(G4ThreeVector(x, y, -3*mm));
	particleGun->GeneratePrimaryVertex(anEvent);
	
	G4int  n_event = anEvent->GetEventID();
	if((n_event%1000)==0)
	{
		cout << "New event started! " << anEvent->GetEventID() << " Particle energy: "  << r1 << " keV. "<< endl; 
	} 

}


