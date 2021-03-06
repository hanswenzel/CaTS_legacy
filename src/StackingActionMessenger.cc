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
//---------------------------------------------------------------------
//*            |\___/|                                                *
//*            )     (                                                *
//*           =\     /=                                               *
//*             )===(                                                 *
//*            /     \     CaTS: Calorimeter and Tracker Simulation   *
//*            |     |     is a flexible and extend-able framework    *
//*           /       \    for the simulation of various detector     *
//*	      \       /    systems                                    *
//*            \__  _/     https://github.com/hanswenzel/CaTS         *
//*	         ( (                                                  *
//*	          ) )                                                 *
//*              (_(                                                  *
//* CaTS also serves as an example that demonstrates how to use       *
//* opticks from within Geant4 for the creation and propagation of    *
//* optical photons.                                                  *
//* see https://bitbucket.org/simoncblyth/opticks.git).               *
//* Ascii Art by Joan Stark: https://www.asciiworld.com/-Cats-2-.html *
//---------------------------------------------------------------------
//
#include "StackingActionMessenger.hh"
#include <G4ApplicationState.hh>
#include "StackingAction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithoutParameter.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
StackingActionMessenger::StackingActionMessenger(StackingAction* CaTSAction)
  : CaTSAction(CaTSAction)
{
  StackingActionDir = new G4UIdirectory("/CaTS/StackingAction/");
  StackingActionDir->SetGuidance("CaTS StackingAction control commands.");
  killPi0Cmd = new G4UIcmdWithABool("/CaTS/StackingAction/killPi0", this);
  killPi0Cmd->SetGuidance("true for killing Pi0 at creation");
  killPi0Cmd->SetGuidance("Default is false");
  killPi0Cmd->SetParameterName("killPi0", false);
  killPi0Cmd->SetDefaultValue(false);
  killPi0Cmd->AvailableForStates(G4State_PreInit, G4State_Idle);
  killetaCmd = new G4UIcmdWithABool("/CaTS/StackingAction/killeta", this);
  killetaCmd->SetGuidance("true for killing eta at creation");
  killetaCmd->SetGuidance("Default is false");
  killetaCmd->SetParameterName("killeta", false);
  killetaCmd->SetDefaultValue(false);
  killetaCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
  killGammafromnCaptureCmd =
    new G4UIcmdWithABool("/CaTS/StackingAction/killGammafromnCapture", this);
  killGammafromnCaptureCmd->SetGuidance("true for killing gammas from nCapture at creation");
  killGammafromnCaptureCmd->SetGuidance("Default is false");
  killGammafromnCaptureCmd->SetParameterName("killGammafromnCapture", false);
  killGammafromnCaptureCmd->SetDefaultValue(false);
  killGammafromnCaptureCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
  listCmd = new G4UIcmdWithoutParameter("/CaTS/StackingAction/List", this);
  listCmd->SetGuidance("List the status of control flags of the StackingAction.");
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
StackingActionMessenger::~StackingActionMessenger()
{
  delete killPi0Cmd;
  delete killetaCmd;
  delete killGammafromnCaptureCmd;
  delete StackingActionDir;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void StackingActionMessenger::SetNewValue(G4UIcommand* command, G4String newValues)
{
  if(command == killPi0Cmd)
  {
    CaTSAction->SetkillPi0(killPi0Cmd->GetNewBoolValue(newValues));
  }
  else if(command == killetaCmd)
  {
    CaTSAction->Setkilleta(killetaCmd->GetNewBoolValue(newValues));
  }
  else if(command == killGammafromnCaptureCmd)
  {
    CaTSAction->SetkillGammafromnCapture(killGammafromnCaptureCmd->GetNewBoolValue(newValues));
  }
  else if(command == listCmd)
  {
    CaTSAction->Print();
  }
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
