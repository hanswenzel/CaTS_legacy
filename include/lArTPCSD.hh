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
#ifndef lArTPCSD_h
#define lArTPCSD_h 1
#pragma once
#include "lArTPCHit.hh"
#include "G4VSensitiveDetector.hh"
#include "G4Scintillation.hh"
#include "G4ScintillationTrackInformation.hh"
class G4Step;
class G4HCofThisEvent;
class G4MaterialPropertiesTable;
// Missinf - compilation error
class G4PhysicsOrderedFreeVector;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class lArTPCSD : public G4VSensitiveDetector {
public:
    lArTPCSD(G4String name);
    virtual ~lArTPCSD();
    // methods from base class
    virtual void Initialize(G4HCofThisEvent* hitCollection);
    virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory* history);
    virtual void EndOfEvent(G4HCofThisEvent* hitCollection);

private:
    G4int materialIndex;
    const G4Material* aMaterial;
    G4MaterialPropertiesTable* aMaterialPropertiesTable;
    //
    // properties related to Scintillation
    //
    G4MaterialPropertyVector* Fast_Intensity{nullptr};
    G4MaterialPropertyVector* Slow_Intensity{nullptr};
    G4double YieldRatio{0}; // slowerRatio,
    G4double FastTimeConstant{0}; // TimeConstant,
    G4double SlowTimeConstant{0}; //slowerTimeConstant,
    G4ScintillationType ScintillationType;
    //
    // properties related to Cerenkov
    //
    G4MaterialPropertyVector* Rindex{nullptr};
    G4PhysicsOrderedFreeVector* CerenkovAngleIntegrals{nullptr};
    const G4PhysicsTable* thePhysicsTable{0};
    G4double Pmin{0};
    G4double Pmax{0};
    G4double dp{0};
    G4double nMax{0};
    bool first{false};
    bool verbose{false};
    int tCphotons{0};
    int tSphotons{0};
    double NumElectrons(double e, double ds);
    lArTPCHitsCollection* flArTPCHitsCollection{nullptr};
    G4int fHCID{0};
};
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#endif
