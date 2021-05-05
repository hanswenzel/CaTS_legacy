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

#ifndef ConfigurationManagerMessenger_h
#define ConfigurationManagerMessenger_h 1

#include "G4UImessenger.hh"
class ConfigurationManager;
class G4UIdirectory;
class G4UIcmdWithABool;
class G4UIcmdWithAString;
class G4UIcmdWithAnInteger;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class ConfigurationManagerMessenger : public G4UImessenger {
public:
    ConfigurationManagerMessenger(ConfigurationManager*);
    virtual ~ConfigurationManagerMessenger();
    void SetNewValue(G4UIcommand*, G4String);
private:
    ConfigurationManager* mgr;
    G4UIdirectory* testDir;
#ifdef WITH_ROOT
    G4UIcmdWithABool* writeHitsCmd;
    G4UIcmdWithABool* doAnalysisCmd; 
    G4UIcmdWithAString* FileNameCmd;
    G4UIcmdWithAString* HistoFileNameCmd;
#endif
#ifdef WITH_G4OPTICKS
    G4UIcmdWithABool* enable_opticksCmd;
    G4UIcmdWithAnInteger* MaxPhotonsCmd; 
#endif  
    G4UIcmdWithABool* enable_verboseCmd;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#endif

