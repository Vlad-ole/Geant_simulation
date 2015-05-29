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

#include <G4SystemOfUnits.hh> // this has appeared in GEANT4_10
#include <string>


using namespace std;

//#define CHAMFER //It is not so important



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::DetectorConstruction()
{
	messenger = new Messenger(this); 
}

DetectorConstruction::~DetectorConstruction()
{
	delete messenger; 
}


// это основной метод
G4VPhysicalVolume * DetectorConstruction::Construct()
{
	G4UImanager* UI = G4UImanager::GetUIpointer();

	defineMaterials(); // внешн€€ функци€. «десь определ€ютс€ различные материалы.
	defineSurfaces(); // внешн€€ функци€. «десь определ€ютс€ различные типы поверхностей.

	//--------------------------------------------------------------------------------
	//выставление размеров объектов
	G4double HalfWorldLength = 3*cm;

	const G4double alpha = 0 * degree;
	const double scintillator_length_x = 3.5*mm; // full length (or the narrower side)	
	const double scintillator_height = 8.95*mm; // full length

	const double scintillator_length_y = 3.5; // full length (or the wider side)
	//double scintillator_height = 2*mm + 0.5*mm; // for YAP:Ce 2x10 only

	cout << "scintillator_length_y = scintillator_height*tan(alpha) + 3.5 = " << scintillator_length_y << endl;
	
	const double grease_diameter = 1.5*max(scintillator_length_x, scintillator_length_y);
	const double grease_height = 0.1*mm  /*0.0*mm*/;

	const double absorber_diameter = grease_diameter;
	const double absorber_height = 1 * um;

	const double glass_diameter = 5 * cm;
	const double glass_height = 2 * mm;

	const double cathode_diameter = glass_diameter;
	const double cathode_height = 1 * um;
	//--------------------------------------------------------------------------------

	//const G4double shift = scintillator_height / 2.0 + scintillator_length_x / 4.0 * tan(alpha);
	const G4double shift = scintillator_height / 2.0;

	//--------------------------------------------------------------------------------
	//определение взаимного расположени€ объектов
	const G4ThreeVector &scintillator_position = G4ThreeVector(0, 0, shift);
	//const G4ThreeVector &absorber_position = G4ThreeVector(0, 0, scintillator_height * 0.99);
	const G4ThreeVector &grease_position = G4ThreeVector(0, 0, 2*shift + grease_height / 2.0);
	const G4ThreeVector &glass_position = G4ThreeVector(0, 0, 2*shift + grease_height + glass_height / 2.0);
	const G4ThreeVector &cathode_position = G4ThreeVector(0, 0, 2*shift + grease_height + glass_height + cathode_height / 2.0);


#ifdef CHAMFER

	G4ThreeVector &chamfer_top_left_longitudinal_1 = G4ThreeVector(-scintillator_length_x/2.0, 0, -scintillator_height/2.0);
	G4ThreeVector &chamfer_top_right_longitudinal_1 = G4ThreeVector(scintillator_length_x/2.0, 0, -scintillator_height/2.0);
	G4ThreeVector &chamfer_bottom_left_longitudinal_1 = G4ThreeVector(-scintillator_length_x/2.0, 0, scintillator_height/2.0);
	G4ThreeVector &chamfer_bottom_right_longitudinal_1 = G4ThreeVector(scintillator_length_x/2.0, 0, scintillator_height/2.0);

	G4ThreeVector &chamfer_top_left_longitudinal_2 = G4ThreeVector(0, -scintillator_length_y/2.0, -scintillator_height/2.0);
	G4ThreeVector &chamfer_top_right_longitudinal_2 = G4ThreeVector(0, scintillator_length_y/2.0, -scintillator_height/2.0);
	G4ThreeVector &chamfer_bottom_left_longitudinal_2 = G4ThreeVector(0, -scintillator_length_y/2.0, scintillator_height/2.0);
	G4ThreeVector &chamfer_bottom_right_longitudinal_2 = G4ThreeVector(0, scintillator_length_y/2.0, scintillator_height/2.0);

	G4ThreeVector &chamfer_a_vertical = G4ThreeVector(scintillator_length_x/2.0, scintillator_length_y/2.0, 0);
	G4ThreeVector &chamfer_b_vertical = G4ThreeVector(scintillator_length_x/2.0, -scintillator_length_y/2.0, 0);
	G4ThreeVector &chamfer_c_vertical = G4ThreeVector(-scintillator_length_x/2.0, scintillator_length_y/2.0, 0);
	G4ThreeVector &chamfer_d_vertical = G4ThreeVector(-scintillator_length_x/2.0, -scintillator_length_y/2.0, 0);
#endif
	//--------------------------------------------------------------------------------





	//----------------------------------------------------------------------------------
	// создание мира
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
	// создание кристалла



	////// for any crystall
	solid_scintillator = new G4Box("sscintillator", scintillator_length_x/2.0, scintillator_length_y/2.0, scintillator_height/2.0);
	//G4Trap* solid_scintillator = new G4Trap("sTrapscintillator", scintillator_length_x, scintillator_length_x, scintillator_length_x*tan(alpha) + scintillator_height, scintillator_height);
	G4RotationMatrix* yRot90deg = new G4RotationMatrix;
	//yRot90deg->rotateY(-90 * degree);
	//yRot90deg->rotateY(180 * degree);

	//++++++++++++++++++++++++++++++++++++++++++++++
	//create chamfer
#ifdef CHAMFER



	G4double chamfer_parameter =  0.1*mm; // full length of 

	G4Box*  box_longitudinal_1 = new G4Box("Box", chamfer_parameter/2.0, scintillator_length_y/2.0 + 1*mm, chamfer_parameter/2.0);
	G4Box*  box_longitudinal_2 = new G4Box("Box", scintillator_length_x/2.0, chamfer_parameter/2.0, chamfer_parameter/2.0);
	G4Box*  box_vertical = new G4Box("Box", chamfer_parameter/2.0, chamfer_parameter/2.0, scintillator_height/2.0);

	G4RotationMatrix* yRot = new G4RotationMatrix;
	yRot->rotateY(3.1416/4.*rad);

	G4RotationMatrix* xRot = new G4RotationMatrix();
	xRot->rotateX(3.1416/4.*rad);

	G4RotationMatrix* zRot = new G4RotationMatrix();
	zRot->rotateZ(3.1416/4.*rad);

	G4SubtractionSolid* subtraction_top_left_longitudinal_1 = new G4SubtractionSolid("Box-Cylinder1", solid_scintillator, box_longitudinal_1, yRot, chamfer_top_left_longitudinal_1);
	G4SubtractionSolid* subtraction_top_right_longitudinal_1 = new G4SubtractionSolid("Box-Cylinder2", subtraction_top_left_longitudinal_1, box_longitudinal_1, yRot, chamfer_top_right_longitudinal_1);
	G4SubtractionSolid* subtraction_bottom_left_longitudinal_1 = new G4SubtractionSolid("Box-Cylinder3", subtraction_top_right_longitudinal_1, box_longitudinal_1, yRot, chamfer_bottom_left_longitudinal_1);
	G4SubtractionSolid* subtraction_bottom_right_longitudinal_1 = new G4SubtractionSolid("Box-Cylinder4", subtraction_bottom_left_longitudinal_1, box_longitudinal_1, yRot, chamfer_bottom_right_longitudinal_1);

	/*G4SubtractionSolid* subtraction_top_left_longitudinal_2 = new G4SubtractionSolid("Box-Cylinder", subtraction_bottom_right_longitudinal_1, box_longitudinal_2, xRot, chamfer_top_left_longitudinal_2);
	G4SubtractionSolid* subtraction_top_right_longitudinal_2 = new G4SubtractionSolid("Box-Cylinder", subtraction_top_left_longitudinal_2, box_longitudinal_2, xRot, chamfer_top_right_longitudinal_2);
	G4SubtractionSolid* subtraction_bottom_left_longitudinal_2 = new G4SubtractionSolid("Box-Cylinder", subtraction_top_right_longitudinal_2, box_longitudinal_2, xRot, chamfer_bottom_left_longitudinal_2);
	G4SubtractionSolid* subtraction_bottom_right_longitudinal_2 = new G4SubtractionSolid("Box-Cylinder", subtraction_bottom_left_longitudinal_2, box_longitudinal_2, xRot, chamfer_bottom_right_longitudinal_2);*/

	/*G4SubtractionSolid* subtraction_a_vertical = new G4SubtractionSolid("Box-Cylinder", subtraction_bottom_right_longitudinal_2, box_vertical, zRot, chamfer_a_vertical);
	G4SubtractionSolid* subtraction_b_vertical = new G4SubtractionSolid("Box-Cylinder", subtraction_a_vertical, box_vertical, zRot, chamfer_b_vertical);
	G4SubtractionSolid* subtraction_c_vertical = new G4SubtractionSolid("Box-Cylinder", subtraction_b_vertical, box_vertical, zRot, chamfer_c_vertical);
	G4SubtractionSolid* subtraction_d_vertical = new G4SubtractionSolid("Box-Cylinder", subtraction_c_vertical, box_vertical, zRot, chamfer_d_vertical);*/

	G4SubtractionSolid* subtraction_a_vertical = new G4SubtractionSolid("Box-Cylinder5", subtraction_bottom_right_longitudinal_1, box_vertical, zRot, chamfer_a_vertical);
	G4SubtractionSolid* subtraction_b_vertical = new G4SubtractionSolid("Box-Cylinder6", subtraction_a_vertical, box_vertical, zRot, chamfer_b_vertical);
	G4SubtractionSolid* subtraction_c_vertical = new G4SubtractionSolid("Box-Cylinder7", subtraction_b_vertical, box_vertical, zRot, chamfer_c_vertical);
	G4SubtractionSolid* subtraction_d_vertical = new G4SubtractionSolid("Box-Cylinder8", subtraction_c_vertical, box_vertical, zRot, chamfer_d_vertical);

#endif // CHAMFER
	//++++++++++++++++++++++++++++++++++++++++++++++

	logicScint = new G4LogicalVolume(solid_scintillator, G4Material::GetMaterial("LFS-3"), "lScintillator",0,0,0);

	physiScint = new G4PVPlacement(yRot90deg,               
		scintillator_position,  // at (x,y,z)
		logicScint,     // its logical volume
		"pScintillator",        // its name
		logicWorld,      // its mother  volume
		false,           // no boolean operations
		0); 

	//_______________________________________________________________________________
	////for YAP:Ce only
	/*solidTrapScint = new G4Trap("sTrapscintillator", 2*mm, 10*mm, 3*mm, 2*mm);

	logicScint = new G4LogicalVolume(solidTrapScint, G4Material::GetMaterial("YAP_Ce"), "lScintillator",0,0,0);

	G4RotationMatrix* yRot90deg= new G4RotationMatrix;
*/
	////2x3x10
	////no rotation

	////2x3
	/*yRot90deg->rotateX(90*degree);*/

	////2x2
	/*yRot90deg->rotateX(270*degree);*/

	////2x10
	//yRot90deg->rotateX(270*degree);
	//yRot90deg->rotateZ(90*degree);


	//physiScint = new G4PVPlacement(/*0*/ yRot90deg,
	//	scintillator_position,  // at (x,y,z)
	//	logicScint,     // its logical volume
	//	"pScintillator",        // its name
	//	logicWorld,      // its mother  volume
	//	false,           // no boolean operations
	//	0);              // copy number
	//_______________________________________________________________________________

	//-------------------------------------------------------------------------------




	//------------------------------------------------------------------------------
	// создание оптической смазки
	solid_grease = new G4Tubs("sgrease", 0.*cm, grease_diameter/2.0, grease_height/2.0, 0.*deg, 360.*deg);
	logic_grease = new G4LogicalVolume(solid_grease, G4Material::GetMaterial("Polydimethylsiloxane"/*"Air"*/), "lGrease", 0, 0, 0);
	physi_grease = new G4PVPlacement(0,               // no rotation
		grease_position,  // at (x,y,z)
		logic_grease,     // its logical volume
		"pGrease",        // its name
		logicWorld,      // its mother  volume
		false,           // no boolean operations
		0);              // copy number
	//---------------------------------------------------------------------------


	//---------------------------------------------------------------------------
	//создание стекла
	solid_glass = new G4Tubs("swindow", 0.*cm, glass_diameter/2.0, glass_height/2.0, 0.*deg, 360.*deg);
	logic_glass = new G4LogicalVolume(solid_glass, G4Material::GetMaterial("FusedSilica"), "lEnvelope", 0,0,0);
	physi_glass = new G4PVPlacement(0,               // no rotation
		glass_position,  // at (x,y,z)
		logic_glass,     // its logical volume
		"pEnvelope",       // its name
		logicWorld,        // its mother  volume
		false,             // no boolean operations
		0);                // copy number
	//---------------------------------------------------------------------------



	//-----------------------------------------------------------------------------
	//создание фотокатода
	solidCathode = new G4Tubs("scath", 0.*cm, cathode_diameter/2.0 , cathode_height/2.0, 0.*deg, 360.*deg);
	logicCathode = new G4LogicalVolume(solidCathode, G4Material::GetMaterial("BialkaliCathode"), "BialkaliCathode_", 0,0,0);
	physiCathode = new G4PVPlacement(0,               // no rotation
		cathode_position,  // at (x,y,z)
		logicCathode,     // its logical volume 
		"pCath",          // its name
		logicWorld,       // its mother  volume
		false,            // no boolean operations
		0);               // copy number


	//--------------------------------------------------------------------------



	////-----------------------------------------------------------------------------
	////создание поглотител€

	G4ThreeVector* tmp_vec = new G4ThreeVector(0, 0, 2*shift);

	G4Tubs *solidAbs_tube = new G4Tubs("abs", 0, cathode_diameter / 2.0, cathode_height / 2.0, 0.*deg, 360.*deg);
	G4SubtractionSolid* solidAbs = new G4SubtractionSolid("Absorber_solid", solidAbs_tube, solid_scintillator, yRot90deg, *tmp_vec);
	
	
	const G4ThreeVector &absorber_position = G4ThreeVector(-0.0*mm, 0, 2 * shift * 0.99);
	
	logicAbs = new G4LogicalVolume(solidAbs, G4Material::GetMaterial("BialkaliCathode"), "Absorber_", 0, 0, 0);
	physiAbs = new G4PVPlacement(0,               // no rotation
		absorber_position,  // at (x,y,z)
		logicAbs,     // its logical volume 
		"pCath",          // its name
		logicWorld,       // its mother  volume
		false,            // no boolean operations
		0);               // copy number


	////--------------------------------------------------------------------------




	//определение чувствительного объема
	G4String sensitiveDetectorName = "/detector/sensitiveDetector";
	theCathodeSD = new CathodeSD(sensitiveDetectorName, physiCathode);
	G4SDManager::GetSDMpointer()->AddNewDetector( theCathodeSD );
	logicCathode->SetSensitiveDetector( theCathodeSD );
	//------------------------------------------------------------------------


	//---------------------------------------------------------------------------
	//установка поверхностей
	G4LogicalBorderSurface* scintillator_world_logical = new G4LogicalBorderSurface("world_scintillator", physiScint, physiWorld, teflon_unified); // from physiScint to physiWorld
	G4LogicalBorderSurface* world_scintillator_logical = new G4LogicalBorderSurface("scintillator_world", physiWorld, physiScint, teflon_unified); // from physiWorld to physiScint

	//G4LogicalBorderSurface* scintillator_grease_logical = new G4LogicalBorderSurface("scintillator_world", physiScint, physi_grease, polishedAir);
	//G4LogicalBorderSurface* grease_scintillator_logical = new G4LogicalBorderSurface("scintillator_world", physi_grease, physiScint, polishedAir);

	//G4LogicalBorderSurface* grease_glass_logical = new G4LogicalBorderSurface("grease_glass_logical", physi_grease, physi_glass, polishedAir);
	//G4LogicalBorderSurface* glass_grease_logical = new G4LogicalBorderSurface("glass_grease_logical", physi_glass, physi_grease, polishedAir);

	G4LogicalBorderSurface* envelope2CathodeSurface = new G4LogicalBorderSurface("envelope2CathodeSurface", physi_glass, physiCathode, silicaCathodeMaterial);



	
	//---------------------------------------------------------------------------


	//------------------------------------------------------------------------------
	// установка атрибутов визуализации
	G4VisAttributes* ScintVisAtt = new G4VisAttributes(G4Colour(1.0,0.0,1.0, 0.6));

	G4VisAttributes* CathodeVisAtt = new G4VisAttributes(G4Colour(1.0, 0.0, 1.0, 0.5));
	CathodeVisAtt->SetForceWireframe(true);

	G4VisAttributes* GreaseVisAtt = new G4VisAttributes(G4Colour(1.0,1.0,0.0,0.8));

	logicWorld->SetVisAttributes(G4VisAttributes::Invisible);
	logicScint->SetVisAttributes(ScintVisAtt);
	logic_grease->SetVisAttributes(GreaseVisAtt);
	logicCathode->SetVisAttributes(CathodeVisAtt);
	//-----------------------------------------------------------------------------

	return physiWorld;
}


void DetectorConstruction::ChangeDetectorConstruction(double parametr)
{
	ChangeSurface(parametr);
	//ChangeMaterials();	
}

