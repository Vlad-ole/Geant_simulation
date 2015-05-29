#ifndef DetectorConstruction_h
#define DetectorConstruction_h

#include <globals.hh>
#include <G4ThreeVector.hh>
#include <G4VUserDetectorConstruction.hh>
#include "CathodeSD.hh"


class G4Trap;
class G4Trd;
class G4Box;
class G4Tubs;
class G4Cons;
class G4Ellipsoid;
class G4SubtractionSolid;
class G4UnionSolid;
class G4BooleanSolid;
class G4LogicalVolume;
class G4VPhysicalVolume;
class G4Material;
class G4VPVParameterisation;
class G4UserLimits;
class Messenger;
class G4OpticalSurface;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class DetectorConstruction : public G4VUserDetectorConstruction
{
public:

	DetectorConstruction();
	~DetectorConstruction();

public:

	G4VPhysicalVolume* Construct();
	void ChangeDetectorConstruction(double parametr);
	void ChangeSurface(double parametr);
	void ChangeMaterials();

	void ChangeCathRefl();

private:

	G4Box*             solidWorld;    // pointer to the solid envelope 
	G4LogicalVolume*   logicWorld;    // pointer to the logical envelope
	G4VPhysicalVolume* physiWorld;    // pointer to the physical envelope

	//G4Box* solidBoxScint;
	G4Cons*            solidConicalScint;   // pointer to the conic solid Scintillator
	G4LogicalVolume*   logicScint;   // pointer to the logical Scintillator
	G4VPhysicalVolume* physiScint;   // pointer to the physical Scintillator

	G4LogicalVolume*   logicBox;   // pointer to the logical Scintillator
	G4VPhysicalVolume* physiBox;   // pointer to the physical Scintillator

	G4Trd* solidTrdScint;
	G4Box*            solid_scintillator;   // pointer to the conic solid Scintillator


	G4Cons*             solidConicalShellShaft;  // pointer to the conic solid Shell
	G4Cons*             solidConicalShellCap;  // pointer to the solid Cap
	G4BooleanSolid*     solidShell; // pointer to the ellipsoidal solid Shell
	G4LogicalVolume*    logicShell;  // pointer to the logical Shell
	G4VPhysicalVolume*  physiShell;  // pointer to the physical Shell
	G4Cons*             solidAirCap;  // pointer to the solid Air between Scint and Cap
	G4LogicalVolume*    logicAirCap;  // pointer to the logical Air between Scint and Cap
	G4VPhysicalVolume*  physiAirCap;  // pointer to the physical Air between Scint and Cap

	G4Box*             Box_solidGrease;
	G4Tubs*            solid_grease;
	G4LogicalVolume*   logic_grease;
	G4VPhysicalVolume* physi_grease;

	G4Tubs*            solid_glass;
	G4Tubs*            solidShaft;
	G4UnionSolid*      solidEnvelope;
	G4LogicalVolume*   logic_glass;
	G4VPhysicalVolume* physi_glass;

	G4LogicalVolume*   logicWindow;
	G4VPhysicalVolume* physiWindow;


	G4Tubs*            solidCathode;  // pointer to the solid Cathode
	G4LogicalVolume*   logicCathode;  // pointer to the logical Cathode
	G4VPhysicalVolume* physiCathode;  // pointer to the physical Cathode

	G4Tubs*            solidCase;     // pointer to the solid Case
	G4LogicalVolume*   logicCase;     // pointer to the logical Case
	G4VPhysicalVolume* physiCase;     // pointer to the physical Case


	
	G4LogicalVolume*   logicAbs;     // pointer to the logical Case
	G4VPhysicalVolume* physiAbs;     // pointer to the physical Case


	Messenger* messenger;  // pointer to the Messenger

	G4String sScintillationMaterial;
	G4String sScintillatorFaceSurface;
	G4String sScintillatorLateralSurface;

	// surfaces
	G4OpticalSurface *world_scintillator;
	G4OpticalSurface *scintillator_grease;
	G4OpticalSurface *grease_glass;
	G4OpticalSurface *glass_cathode;


	// arbitraryly valued variables (not changeable by user)
	G4double fWorldLength;            // Full length of the world volume
	G4double fPMTLength;
	G4double fCathodeThickness;

	G4double fScint_x;
	G4double fScint_y;

	CathodeSD* theCathodeSD;
	G4Region*  fRegion;

	G4OpticalSurface *BGOPolishedAirTeflon; // polished BGO surface wrapped with teflon
	G4OpticalSurface *BGOGroundAirTeflon;   // ground BGO surface wrapped with teflon
	G4OpticalSurface *polishedAir;          // polished crystal surface, not wrapped
	G4OpticalSurface *groundAir;            // ground crystal surface, not wrapped
	 
	G4OpticalSurface *groundWhitePainted;   // ground crystal surface painted white
	G4OpticalSurface *polishedBlackPainted; // polished crystal surface painted black
	G4OpticalSurface *groundBlackPainted;   // ground crystal surface painted black
	G4OpticalSurface *Polished_Air_TiO2;
	G4OpticalSurface *Ground_Air_TiO2;
	G4OpticalSurface *airGroundAluminum; // ground aluminm surface
	G4OpticalSurface *silicaCathodeMaterial; // surface between window and cathode
	G4OpticalSurface *AbsorberMaterial;

	G4OpticalSurface *teflon_unified;
	G4OpticalSurface *MgO_unified;
	G4OpticalSurface *TiO2_unified;

	G4OpticalSurface *Glass_surface;

	G4MaterialPropertiesTable* luyag_pr;


	void defineMaterials();
	void defineSurfaces();

	G4MaterialPropertiesTable *silicaCathodeMaterialProperty;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
