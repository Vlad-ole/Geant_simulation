#ifndef DETECTORMESSENGER_H
#define DETECTORMESSENGER_H

#include <G4UImessenger.hh>

class DetectorConstruction;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithABool;

class Messenger : public G4UImessenger
{
public:
    Messenger(DetectorConstruction*);
   ~Messenger();

    void SetNewValue(G4UIcommand*, G4String);

  private:
    DetectorConstruction* myDetector;

    G4UIdirectory*             detDir;
    G4UIcmdWithAString*        ScintillationMaterial;
    G4UIcmdWithAString*        ScintillatorFaceSurface;
    G4UIcmdWithAString*        ScintillatorLateralSurface;
    G4UIcmdWithAString*        ScintillatorShape;
    G4UIcmdWithADoubleAndUnit* ScintDiameter;
    G4UIcmdWithADoubleAndUnit* ScintHeadDiameter;
    G4UIcmdWithADoubleAndUnit* ScintThickness;
    G4UIcmdWithADoubleAndUnit* SourceDistance;
    G4UIcmdWithADoubleAndUnit* PMTDiameter;
    G4UIcmdWithADoubleAndUnit* WindowThickness;
    G4UIcmdWithADoubleAndUnit* EnvelopeThickness;
    G4UIcmdWithADoubleAndUnit* GreaseThickness;
    G4UIcmdWithADoubleAndUnit* ShellThickness;
    G4UIcmdWithADoubleAndUnit* AirGap;
    G4UIcommand*               updateCmd;

    G4UIdirectory*             outDir;
    G4UIcmdWithAString*        fileName;

};

#endif // DETECTORMESSENGER_H
