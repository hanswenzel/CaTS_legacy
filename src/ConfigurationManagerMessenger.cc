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
// Geant4 headers
#include "G4UIdirectory.hh"
#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithoutParameter.hh"
// project headers
#include "ConfigurationManagerMessenger.hh"
#include "ConfigurationManager.hh"
using namespace std;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
ConfigurationManagerMessenger::ConfigurationManagerMessenger(
  ConfigurationManager* mgr1)
  : mgr(mgr1)
{
  testDir = new G4UIdirectory("/CaTS/");
  testDir->SetGuidance("Configuring CaTS");
#ifdef WITH_ROOT
  //
  FileNameCmd = new G4UIcmdWithAString("/CaTS/FileName", this);
  FileNameCmd->SetGuidance("Enter file name for Hits collections ");
  FileNameCmd->SetParameterName("FileName", true);
  FileNameCmd->SetDefaultValue("hist.root");
  FileNameCmd->AvailableForStates(G4State_PreInit, G4State_Init, G4State_Idle);
  //
  writeHitsCmd = new G4UIcmdWithABool("/CaTS/writeHits", this);
  writeHitsCmd->SetGuidance("Set flag for writing hits");
  writeHitsCmd->SetParameterName("writeHits", true);
  writeHitsCmd->SetDefaultValue(true);
  writeHitsCmd->AvailableForStates(G4State_PreInit, G4State_Init, G4State_Idle);
  //
  HistoFileNameCmd = new G4UIcmdWithAString("/CaTS/FileName", this);
  HistoFileNameCmd->SetGuidance(
    "Enter file name for Hits collections (note: _RunID and  .root extension "
    "will be added automatically");
  HistoFileNameCmd->SetParameterName("FileName", true);
  HistoFileNameCmd->SetDefaultValue("hits");
  HistoFileNameCmd->AvailableForStates(G4State_PreInit, G4State_Init,
                                       G4State_Idle);
  //
  doAnalysisCmd = new G4UIcmdWithABool("/CaTS/doAnalysis", this);
  doAnalysisCmd->SetGuidance("Set flag for making some analysis histograms");
  doAnalysisCmd->SetParameterName("doAnalysis", false);
  doAnalysisCmd->SetDefaultValue(false);
  doAnalysisCmd->AvailableForStates(G4State_PreInit, G4State_Init,
                                    G4State_Idle);
#endif
#ifdef WITH_G4OPTICKS
  //
  enable_opticksCmd = new G4UIcmdWithABool("/CaTS/enable_opticks", this);
  enable_opticksCmd->SetGuidance("Set flag for enabling opticks");
  enable_opticksCmd->SetParameterName("enable_opticks", true);
  enable_opticksCmd->SetDefaultValue(true);
  enable_opticksCmd->AvailableForStates(G4State_PreInit, G4State_Init,
                                        G4State_Idle);
  //
  MaxPhotonsCmd = new G4UIcmdWithAnInteger("/CaTS/MaxPhotons", this);
  MaxPhotonsCmd->SetGuidance(
    "Maximum number of Photons to collect before calling Opticks");
  MaxPhotonsCmd->SetParameterName("MaxPhotons", 1000000);
  MaxPhotonsCmd->SetDefaultValue(1000000);
  MaxPhotonsCmd->AvailableForStates(G4State_PreInit);
#endif
  //
  listCmd = new G4UIcmdWithoutParameter("/CaTS/list", this);
  listCmd->SetGuidance("List all configuration parameters");
  //
  enable_verboseCmd = new G4UIcmdWithABool("/CaTS/enable_verbose", this);
  enable_verboseCmd->SetGuidance(
    "Set flag for enabling verbose diagnostic printout");
  enable_verboseCmd->SetParameterName("enable_verbose", false);
  enable_verboseCmd->SetDefaultValue(false);
  enable_verboseCmd->AvailableForStates(G4State_PreInit, G4State_Init,
                                        G4State_Idle);
  dumpgdmlCmd = new G4UIcmdWithABool("/CaTS/dumpgdml", this);
  dumpgdmlCmd->SetGuidance(
    "Set flag for enabling dumping the detector to a gdml file");
  dumpgdmlCmd->SetParameterName("dumpgdml", false);
  dumpgdmlCmd->SetDefaultValue(false);
  dumpgdmlCmd->AvailableForStates(G4State_PreInit);
  GDMLFileNameCmd = new G4UIcmdWithAString("/CaTS/GDMLFileName", this);
  GDMLFileNameCmd->SetGuidance("Enter file name for Hits collections ");
  GDMLFileNameCmd->SetParameterName("GDMLFileName", true);
  GDMLFileNameCmd->SetDefaultValue("G4dump.gdml");
  GDMLFileNameCmd->AvailableForStates(G4State_PreInit);
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
ConfigurationManagerMessenger::~ConfigurationManagerMessenger()
{
  delete testDir;
#ifdef WITH_ROOT
  delete writeHitsCmd;
  delete doAnalysisCmd;
  delete FileNameCmd;
  delete HistoFileNameCmd;
#endif
#ifdef WITH_G4OPTICKS
  delete enable_opticksCmd;
  delete MaxPhotonsCmd;
#endif
  delete listCmd;
  delete enable_verboseCmd;
  delete dumpgdmlCmd;
  delete GDMLFileNameCmd;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void ConfigurationManagerMessenger::SetNewValue(G4UIcommand* command,
                                                G4String newValue)
{
#ifdef WITH_ROOT
  if(command == writeHitsCmd)
    mgr->setWriteHits(writeHitsCmd->GetNewBoolValue(newValue));
  if(command == FileNameCmd)
    mgr->setFileName(newValue);
  if(command == doAnalysisCmd)
    mgr->setdoAnalysis(doAnalysisCmd->GetNewBoolValue(newValue));
  if(command == HistoFileNameCmd)
    mgr->setHistoFileName(newValue);
#endif
#ifdef WITH_G4OPTICKS
  if(command == enable_opticksCmd)
    mgr->setEnable_opticks(enable_opticksCmd->GetNewBoolValue(newValue));
  if(command == MaxPhotonsCmd)
    mgr->setEnable_opticks(MaxPhotonsCmd->GetNewIntValue(newValue));
#endif
  if(command == listCmd)
    mgr->Print();
  if(command == enable_verboseCmd)
    mgr->setEnable_verbose(enable_verboseCmd->GetNewBoolValue(newValue));
  if(command == dumpgdmlCmd)
    mgr->setDumpgdml(dumpgdmlCmd->GetNewBoolValue(newValue));
  if(command == GDMLFileNameCmd)
    mgr->setGDMLFileName(newValue);
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
