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
/* ------------------------------------------------------------------------
            |\___/|       
            )     (    
           =\     /=
             )===(
            /     \         CaTS: Calorimeter and Tracker Simulation
            |     |         CaTS is a flexible and extend-able framework 
           /       \        for the simulation of calorimeter and tracking detectors. 
           \       /        https://github.com/hanswenzel/CaTS
            \__  _/         CaTS also serves as an Example that demonstrates how to 
              ( (           use opticks from within Geant4 for the creation and propagation 
               ) )          of optical photons. 
              (_(           (see https://bitbucket.org/simoncblyth/opticks.git). 
-------------------------------------------------------------------------*/
// Ascii Art by Joan Stark: https://www.asciiworld.com/-Cats-2-.html

// Geant4 headers
#include "G4UIdirectory.hh"
#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithAString.hh"
// project headers
#include "ConfigurationManagerMessenger.hh"
#include "ConfigurationManager.hh"
using namespace std;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ConfigurationManagerMessenger::ConfigurationManagerMessenger(ConfigurationManager * mgr1)
: mgr(mgr1) {
    testDir = new G4UIdirectory("/CaTS/");
    testDir->SetGuidance("Configuring CaTS");
#ifdef WITH_ROOT
    //
    FileNameCmd = new G4UIcmdWithAString("/CaTS/FileName", this);
    FileNameCmd->SetGuidance("Enter file name for Hits collections ");
    FileNameCmd->SetParameterName("FileName", true);
    FileNameCmd->SetDefaultValue("hist.root");
    FileNameCmd->AvailableForStates(G4State_Idle);
    //
    writeHitsCmd = new G4UIcmdWithABool("/CaTS/writeHits", this);
    writeHitsCmd->SetGuidance("Set flag for writing hits");
    writeHitsCmd->SetParameterName("writeHits", true);
    writeHitsCmd->SetDefaultValue(true);
    writeHitsCmd->AvailableForStates(G4State_Idle);
    //
    HistoFileNameCmd = new G4UIcmdWithAString("/CaTS/FileName", this);
    HistoFileNameCmd->SetGuidance("Enter file name for Hits collections (note: _RunID and  .root extension will be added automatically");
    HistoFileNameCmd->SetParameterName("FileName", true);
    HistoFileNameCmd->SetDefaultValue("hits");
    HistoFileNameCmd->AvailableForStates(G4State_Idle);
    //
    doAnalysisCmd = new G4UIcmdWithABool("/CaTS/doAnalysis", this);
    doAnalysisCmd->SetGuidance("Set flag for writing hits");
    doAnalysisCmd->SetParameterName("doAnalysis", true);
    doAnalysisCmd->SetDefaultValue(true);
    doAnalysisCmd->AvailableForStates(G4State_Idle);
#endif   

#ifdef WITH_G4OPTICKS
    //
    enable_opticksCmd = new G4UIcmdWithABool("/CaTS/enable_opticks", this);
    enable_opticksCmd->SetGuidance("Set flag for enabling opticks");
    enable_opticksCmd->SetParameterName("enable_opticks", true);
    enable_opticksCmd->SetDefaultValue(true);
    enable_opticksCmd->AvailableForStates(G4State_Idle);
#endif
    //
    enable_verboseCmd = new G4UIcmdWithABool("/CaTS/enable_verbose", this);
    enable_verboseCmd->SetGuidance("Set flag for enabling verbose diagnostic printout");
    enable_verboseCmd->SetParameterName("enable_verbose", false);
    enable_verboseCmd->SetDefaultValue(false);
    enable_verboseCmd->AvailableForStates(G4State_PreInit, G4State_Init, G4State_Idle);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ConfigurationManagerMessenger::~ConfigurationManagerMessenger() {
    delete testDir;
#ifdef WITH_ROOT
    delete writeHitsCmd;
    delete doAnalysisCmd;
    delete FileNameCmd;
    delete HistoFileNameCmd;

#endif
#ifdef WITH_G4OPTICKS
    delete enable_opticksCmd;
#endif
    delete enable_verboseCmd;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ConfigurationManagerMessenger::SetNewValue(G4UIcommand* command, G4String newValue) {
#ifdef WITH_ROOT
    if (command == writeHitsCmd) mgr->setWriteHits(writeHitsCmd->GetNewBoolValue(newValue));
    if (command == FileNameCmd) mgr->setFileName(newValue);
    if (command == doAnalysisCmd) mgr->setWriteHits(doAnalysisCmd->GetNewBoolValue(newValue));
    if (command == HistoFileNameCmd) mgr->setFileName(newValue);
#endif
#ifdef WITH_G4OPTICKS
    if (command == enable_opticksCmd) mgr->setEnable_opticks(enable_opticksCmd->GetNewBoolValue(newValue));
#endif
    if (command == enable_verboseCmd) mgr->setEnable_verbose(enable_verboseCmd->GetNewBoolValue(newValue));
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

