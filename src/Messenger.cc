#include "Messenger.hh"
#include <G4UIdirectory.hh>
#include <G4UIcmdWithAString.hh>
#include <G4UIcmdWithADoubleAndUnit.hh>
#include <G4UIcmdWithABool.hh>
#include <G4UIcmdWithoutParameter.hh>
#include "DetectorConstruction.hh"
#include "CathodeSD.hh"

Messenger::Messenger(DetectorConstruction* myDet) : myDetector(myDet)
{
  detDir = new G4UIdirectory("/detector/");
  detDir->SetGuidance("detector settings.");

  ScintillationMaterial = new G4UIcmdWithAString("/detector/scintillationMaterial",this);
  ScintillationMaterial->SetGuidance("Select Material of the Scintillator.");
  ScintillationMaterial->SetGuidance("Perfect materials have a 1 fs time constant and a yield of 100 photons per keV.");
  ScintillationMaterial->SetGuidance("FastBaF is BaF without the slow component.");
  ScintillationMaterial->SetParameterName("material",false);
  ScintillationMaterial->SetCandidates("BaF FastBaF LYSO LaBr NaI PerfectBaF PerfectFastBaF PerfectLYSO PerfectLaBr PerfectNaI ImmediateBaF ImmediateFastBaF ImmediateLYSO ImmediateLaBr ImmediateNaI");
  ScintillationMaterial->SetDefaultValue("BaF");
  ScintillationMaterial->AvailableForStates(G4State_PreInit,G4State_Idle);

  ScintillatorFaceSurface = new G4UIcmdWithAString("/detector/scintillatorFaceSurface",this);
  ScintillatorFaceSurface->SetGuidance("Select surface finish of the scintillator's face (towards source).");
  ScintillatorFaceSurface->SetGuidance("See /detector/scintillatorLateralSurface for a discription of the possible values");
  ScintillatorFaceSurface->SetParameterName("finish",false);
  ScintillatorFaceSurface->SetCandidates("BGOPolishedAirTeflon BGOGroundAirTeflon polishedAir groundAir polishedWhitePainted groundWhitePainted polishedBlackPainted groundBlackPainted");
  ScintillatorFaceSurface->SetDefaultValue("groundAir");
  ScintillatorFaceSurface->AvailableForStates(G4State_PreInit,G4State_Idle);

  ScintillatorLateralSurface = new G4UIcmdWithAString("/detector/scintillatorLateralSurface",this);
  ScintillatorLateralSurface->SetGuidance("Select scintillator's lateral surface finish.");
  ScintillatorLateralSurface->SetGuidance("BGOPolishedAirTeflon: Uses a look-up-table for BGO crystals (Janecek2010)");
  ScintillatorLateralSurface->SetGuidance("BGOGroundAirTeflon: Uses a look-up-table for BGO crystals (Janecek2010)");
  ScintillatorLateralSurface->SetGuidance("polishedAir: Uses the Glisur model");
  ScintillatorLateralSurface->SetGuidance("groundAir: Uses the UNIFIED model with sigma_alpha set to 0.2 rad and finish=ground");
  ScintillatorLateralSurface->SetGuidance("polishedWhitePainted: Uses the UNIFIED model with sigma_alpha set to 1.3° and finish=groundbackpainted (reflectivity: 95.5%)");
  ScintillatorLateralSurface->SetGuidance("groundWhitePainted: Uses the UNIFIED model with sigma_alpha set to 12° and finish=groundbackpainted (reflectivity: 95.5%)");
  ScintillatorLateralSurface->SetGuidance("polishedBlackPainted: Uses the UNIFIED model with sigma_alpha set to 1.3° and finish=groundbackpainted (reflectivity: 4.3%)");
  ScintillatorLateralSurface->SetGuidance("groundBlackPainted: Uses the UNIFIED model with sigma_alpha set to 12° and finish=groundbackpainted (reflectivity: 4.3%)");
  ScintillatorLateralSurface->SetParameterName("finish",false);
  ScintillatorLateralSurface->SetCandidates("BGOPolishedAirTeflon BGOGroundAirTeflon polishedAir groundAir polishedWhitePainted groundWhitePainted polishedBlackPainted groundBlackPainted");
  ScintillatorLateralSurface->SetDefaultValue("groundAir");
  ScintillatorLateralSurface->AvailableForStates(G4State_PreInit,G4State_Idle);

  ScintillatorShape = new G4UIcmdWithAString("/detector/scintillatorShape",this);
  ScintillatorShape->SetGuidance("Select scintillator's shape.");
  ScintillatorShape->SetParameterName("shape",false);
  ScintillatorShape->SetCandidates("cylindric conical ellipsoidal");
  ScintillatorShape->AvailableForStates(G4State_PreInit,G4State_Idle);

  ScintDiameter = new G4UIcmdWithADoubleAndUnit("/detector/scintDiameter",this);
  ScintDiameter->SetGuidance("Primary diameter of the scintillation crystal.");
  ScintDiameter->SetParameterName("diameter",false);
  ScintDiameter->SetUnitCategory("Length");
  ScintDiameter->AvailableForStates(G4State_PreInit,G4State_Idle);

  ScintHeadDiameter = new G4UIcmdWithADoubleAndUnit("/detector/scintHeadDiameter",this);
  ScintHeadDiameter->SetGuidance("Head diameter of conical scintillation crystals.");
  ScintHeadDiameter->SetGuidance("Automatically updated for cylindric crystals as");
  ScintHeadDiameter->SetGuidance("soon as /detector/scintDiameter is updated.");
  ScintHeadDiameter->SetParameterName("diameter",false);
  ScintHeadDiameter->SetUnitCategory("Length");
  ScintHeadDiameter->AvailableForStates(G4State_PreInit,G4State_Idle);

  ScintThickness = new G4UIcmdWithADoubleAndUnit("/detector/scintThickness",this);
  ScintThickness->SetGuidance("Thickness of the cylindric sctintillation crystal");
  ScintThickness->SetParameterName("dist",false);
  ScintThickness->SetUnitCategory("Length");
  ScintThickness->AvailableForStates(G4State_PreInit,G4State_Idle);

  SourceDistance = new G4UIcmdWithADoubleAndUnit("/detector/sourceDistance",this);
  SourceDistance->SetGuidance("Distance between source and detector cap");
  SourceDistance->SetParameterName("dist",false);
  SourceDistance->SetUnitCategory("Length");
  SourceDistance->AvailableForStates(G4State_PreInit,G4State_Idle);

  PMTDiameter = new G4UIcmdWithADoubleAndUnit("/detector/PMTDiameter",this);
  PMTDiameter->SetGuidance("Overall diameter of the PMT");
  PMTDiameter->SetParameterName("dist",false);
  PMTDiameter->SetUnitCategory("Length");
  PMTDiameter->AvailableForStates(G4State_PreInit,G4State_Idle);

  WindowThickness = new G4UIcmdWithADoubleAndUnit("/detector/windowThickness",this);
  WindowThickness->SetGuidance("Thickness of the PMT's window");
  WindowThickness->SetParameterName("dist",false);
  WindowThickness->SetUnitCategory("Length");
  WindowThickness->AvailableForStates(G4State_PreInit,G4State_Idle);

  EnvelopeThickness = new G4UIcmdWithADoubleAndUnit("/detector/envelopeThickness",this);
  EnvelopeThickness->SetGuidance("Thickness of the PMT's Envelope");
  EnvelopeThickness->SetParameterName("dist",false);
  EnvelopeThickness->SetUnitCategory("Length");
  EnvelopeThickness->AvailableForStates(G4State_PreInit,G4State_Idle);

  GreaseThickness = new G4UIcmdWithADoubleAndUnit("/detector/greaseThickness",this);
  GreaseThickness->SetGuidance("Thickness of the grease layer between scintillator and PMT window");
  GreaseThickness->SetParameterName("dist",false);
  GreaseThickness->SetUnitCategory("Length");
  GreaseThickness->AvailableForStates(G4State_PreInit,G4State_Idle);

  ShellThickness = new G4UIcmdWithADoubleAndUnit("/detector/shellThickness",this);
  ShellThickness->SetGuidance("Thickness of the aluminum shell and cap surrounding the scintillator");
  ShellThickness->SetParameterName("dist",false);
  ShellThickness->SetUnitCategory("Length");
  ShellThickness->AvailableForStates(G4State_PreInit,G4State_Idle);

  AirGap = new G4UIcmdWithADoubleAndUnit("/detector/airGap",this);
  AirGap->SetGuidance("Layer of air between scintillator and shell/cap");
  AirGap->SetParameterName("dist",false);
  AirGap->SetUnitCategory("Length");
  AirGap->AvailableForStates(G4State_PreInit,G4State_Idle);

  updateCmd = new G4UIcmdWithoutParameter("/detector/update",this);
  updateCmd->SetGuidance("Update the detector geometry and material with changed values.");
  updateCmd->SetGuidance("Must be run before beamOn if detector has been changed.");


  outDir = new G4UIdirectory("/output/");
  outDir->SetGuidance("data output settings.");

  fileName = new G4UIcmdWithAString("/output/filename",this);
  fileName->SetGuidance("Set file name for output.");
  fileName->SetParameterName("choice",false);
  fileName->AvailableForStates(G4State_PreInit,G4State_Idle);

}


Messenger::~Messenger()
{
  delete updateCmd;
  delete AirGap;
  delete ShellThickness;
  delete GreaseThickness;
  delete EnvelopeThickness;
  delete WindowThickness;
  delete PMTDiameter;
  delete ScintThickness;
  delete ScintHeadDiameter;
  delete ScintDiameter;
  delete ScintillatorShape;
  delete SourceDistance;
  delete ScintillatorLateralSurface;
  delete ScintillatorFaceSurface;
  delete ScintillationMaterial;
  delete detDir;

  delete fileName;
  delete outDir;
}


void Messenger::SetNewValue(G4UIcommand* command,G4String newValue)
{

}




