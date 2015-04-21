#include "DetectorConstruction.hh"
#include "Messenger.hh" 
#include "CathodeSD.hh"
#include "PrimaryGeneratorAction.hh"

#include <string>
#include <sstream>
#include <limits>

#include <G4Material.hh>
#include <G4Box.hh>
#include <G4Trap.hh>
#include <G4Tubs.hh>
#include <G4Cons.hh>
#include <G4Ellipsoid.hh>
#include <G4SubtractionSolid.hh>
#include <G4UnionSolid.hh>
#include <G4LogicalVolume.hh>
#include <G4PVPlacement.hh>
#include <G4PVParameterised.hh>
#include <G4SDManager.hh>
#include <G4GeometryTolerance.hh>
#include <G4GeometryManager.hh>
#include <G4NistManager.hh>
#include <G4RunManager.hh>
#include <G4PhysicalVolumeStore.hh>
#include <G4LogicalVolumeStore.hh>
#include <G4SolidStore.hh>
#include <G4LogicalSkinSurface.hh>
#include <G4LogicalBorderSurface.hh>
#include <G4SurfaceProperty.hh>
#include <G4UImanager.hh>
#include <G4OpticalSurface.hh>
#include <G4UserLimits.hh>
#include <G4VisAttributes.hh>
#include <G4Colour.hh>
#include <G4ios.hh>
#include <G4GeneralParticleSource.hh>
#include <G4RegionStore.hh>
#include <G4Trd.hh>
#include <G4Para.hh>

#include <G4SystemOfUnits.hh> // this has appeared in GEANT4_10
#include <string>


using namespace std;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::DetectorConstruction()
{
	messenger = new Messenger(this); 
}

DetectorConstruction::~DetectorConstruction()
{
	delete messenger; 
}


G4VPhysicalVolume * DetectorConstruction::Construct()
{
	G4UImanager* UI = G4UImanager::GetUIpointer();

	defineMaterials(); 
	defineSurfaces(); 

		
	G4double HalfWorldLength = 3*cm;

		
	const double scintillator_length_x = 3.5*mm; 	
	const double scintillator_length_y = 3.5*mm;
	const double scintillator_height = 8.95*mm; 
	
	
	const G4ThreeVector &scintillator_position = G4ThreeVector(0, 0, scintillator_height/2.0);

	//----------------------------------------------------------------------------------
	// create World
	solidWorld= new G4Box("sworld", HalfWorldLength, HalfWorldLength, HalfWorldLength);
	logicWorld= new G4LogicalVolume( solidWorld, G4Material::GetMaterial("Air"), "lWorld", 0, 0, 0);

	//  Must place the World Physical volume unrotated at (0,0,0).
	//
	physiWorld = new G4PVPlacement(0,               // no rotation
		G4ThreeVector(), // at (0,0,0)
		logicWorld,      // its logical volume
		"pWorld",         // its name
		0,               // its mother  volume
		false,           // no boolean operations
		0);              // copy number

	// Set user cuts to avoid deadlocks
	G4double maxStep = 10.0*m, maxLength = 10.0*m, maxTime = 100.0*ns, minEkin = 0.5*eV;
	logicWorld->SetUserLimits(new G4UserLimits(maxStep,maxLength,maxTime,minEkin));
	//-------------------------------------------------------------------------------



	//--------------------------------------------------------------------------------
	// create scintillator
	
	//no problems
	//G4Box* solid = new G4Box("sscintillator", scintillator_length_x / 2.0, scintillator_length_y / 2.0, scintillator_height / 2.0);


	//no problems too
	//G4Para* solid = new G4Para("sscintillator", scintillator_length_x / 2.0, scintillator_length_y / 2.0, scintillator_height / 2.0, 0 * degree, 0 * degree, 0 * degree);
	

	//error if alpha > 0 && < 45*degree
	G4Para* solid = new G4Para("solid_para", scintillator_length_x / 2.0, scintillator_length_y / 2.0, scintillator_height / 2.0, 1 * degree, 0 * degree, 0 * degree);

	


	logicScint = new G4LogicalVolume(solid, G4Material::GetMaterial("LFS-3"), "lScintillator", 0, 0, 0);

	physiScint = new G4PVPlacement(0,               
		scintillator_position,  // at (x,y,z)
		logicScint,     // its logical volume
		"pScintillator",        // its name
		logicWorld,      // its mother  volume
		false,           // no boolean operations
		0); 



	return physiWorld;
}

