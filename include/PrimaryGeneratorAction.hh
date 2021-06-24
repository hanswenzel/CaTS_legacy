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
#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1
#pragma once 
#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"
class G4ParticleGun;
class PrimaryGeneratorActionMessenger;
class G4VPrimaryGenerator;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {
private:
    PrimaryGeneratorAction & operator=(const PrimaryGeneratorAction &right);
    PrimaryGeneratorAction(const PrimaryGeneratorAction&);
    G4VPrimaryGenerator* currentGenerator;
    G4String currentGeneratorName;
    std::map<G4String, G4VPrimaryGenerator*> gentypeMap;
    PrimaryGeneratorActionMessenger* gunMessenger;
    static PrimaryGeneratorAction* instance;

public:
    PrimaryGeneratorAction();
    virtual ~PrimaryGeneratorAction();
    virtual void GeneratePrimaries(G4Event*);
    void SetGenerator(G4VPrimaryGenerator* gen);
    void SetGenerator(G4String genname);
    G4VPrimaryGenerator* GetGenerator() const;
    G4String GetGeneratorName() const;
    static PrimaryGeneratorAction* getInstance();
};
// ====================================================================
// inline functions
// ====================================================================

inline void PrimaryGeneratorAction::SetGenerator(G4VPrimaryGenerator* gen) {
    currentGenerator = gen;
}

inline void PrimaryGeneratorAction::SetGenerator(G4String genname) {
    std::map<G4String, G4VPrimaryGenerator*>::iterator pos = gentypeMap.find(genname);
    if (pos != gentypeMap.end()) {
        currentGenerator = pos->second;
        currentGeneratorName = genname;
    }
}

inline G4VPrimaryGenerator* PrimaryGeneratorAction::GetGenerator() const {
    return currentGenerator;
}

inline G4String PrimaryGeneratorAction::GetGeneratorName() const {
    return currentGeneratorName;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
