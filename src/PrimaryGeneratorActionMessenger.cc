#include "PrimaryGeneratorActionMessenger.hh"
#include "PrimaryGeneratorAction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
PrimaryGeneratorActionMessenger::PrimaryGeneratorActionMessenger(
        PrimaryGeneratorAction* CaTSGun)
: CaTSAction(CaTSGun) {
    genCmd = new G4UIcmdWithAString("/CaTS/generator", this);
    genCmd->SetGuidance("Select primary generator.");
    genCmd->SetGuidance("Available generators : particleGun,GPS,HEPEvt");
    genCmd->SetParameterName("generator", true);
    genCmd->SetDefaultValue("particleGun");
    genCmd->SetCandidates("particleGun GPS HEPEvt");
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
PrimaryGeneratorActionMessenger::~PrimaryGeneratorActionMessenger() {
    delete genCmd;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void PrimaryGeneratorActionMessenger::SetNewValue(
        G4UIcommand* command, G4String newValue) {
    if (command == genCmd) {
        CaTSAction->SetGenerator(newValue);
        G4cout << "setting new primary Event Generator to: " << newValue << G4endl;
    }
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

