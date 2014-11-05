#ifndef CathodeSD_h
#define CathodeSD_h 1

#include <G4VSensitiveDetector.hh>

class G4Step;
class G4HCofThisEvent;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class CathodeSD : public G4VSensitiveDetector
{
  public:
      CathodeSD(G4String, G4VPhysicalVolume *cathode);
     ~CathodeSD();

      void Initialize(G4HCofThisEvent*);
      G4bool ProcessHits(G4Step*, G4TouchableHistory*);
	  G4bool ProcessHits_Optical(const G4Step* aStep, G4TouchableHistory* );
      void EndOfEvent(G4HCofThisEvent*);

  private:
      const G4VPhysicalVolume * _cathode;
	  int   _nHits;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

