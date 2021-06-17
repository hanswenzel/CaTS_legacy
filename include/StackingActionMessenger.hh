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

#ifndef StackingActionMessenger_h
#define StackingActionMessenger_h 1

#include "G4UImessenger.hh"
#include "globals.hh"

class StackingAction;
class G4UIdirectory;
class G4UIcmdWithABool;
class G4UIcmdWithoutParameter;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class StackingActionMessenger : public G4UImessenger {
public:
    StackingActionMessenger(StackingAction*);
    ~StackingActionMessenger();

    virtual void SetNewValue(G4UIcommand*, G4String);

private:
    StackingAction* CaTSAction;
    G4UIdirectory* StackingActionDir;
    G4UIcmdWithABool* killPi0Cmd;
    G4UIcmdWithABool* killetaCmd;
    G4UIcmdWithABool* killGammafromnCaptureCmd;
    G4UIcmdWithoutParameter* listCmd;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

