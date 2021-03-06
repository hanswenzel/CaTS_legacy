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
#ifndef RadiatorSD_h
#define RadiatorSD_h 1
#pragma once
#include "G4VSensitiveDetector.hh"
#include "G4ScintillationTrackInformation.hh"
#include <G4MaterialPropertyVector.hh>  // for G4MaterialPropertyVector
#include <G4String.hh>                  // for G4String
#include <G4Types.hh>                   // for G4double, G4bool, G4int
class G4Step;
class G4Material;
class G4HCofThisEvent;
class G4MaterialPropertiesTable;
class G4PhysicsOrderedFreeVector;
class G4PhysicsTable;
class G4TouchableHistory;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
class RadiatorSD : public G4VSensitiveDetector
{
 public:
  RadiatorSD(G4String name);
  virtual ~RadiatorSD();
  // methods from base class
  virtual void Initialize(G4HCofThisEvent* hitCollection);
  virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory* history);
  virtual void EndOfEvent(G4HCofThisEvent* hitCollection);

 private:
  const G4Material* aMaterial;
  G4MaterialPropertiesTable* aMaterialPropertiesTable;
  //
  // properties related to Scintillation
  //
  G4MaterialPropertyVector* Fast_Intensity;
  G4MaterialPropertyVector* Slow_Intensity;
  G4double YieldRatio;        // slowerRatio,
  G4double FastTimeConstant;  // TimeConstant,
  G4double SlowTimeConstant;  // slowerTimeConstant,
  G4ScintillationType ScintillationType;
  //
  // properties related to Cerenkov
  //
  G4MaterialPropertyVector* Rindex;
  G4PhysicsOrderedFreeVector* CerenkovAngleIntegrals;
  const G4PhysicsTable* thePhysicsTable;
  G4double Pmin{ 0 };
  G4double Pmax{ 0 };
  G4double dp{ 0 };
  G4double nMax{ 0 };
  bool first{ true };
  bool verbose{ false };
  int tCphotons{ 0 };
  int tSphotons{ 0 };
#ifdef WITH_G4OPTICKS
  //
  // info needed for generating Cerenkov photons on the GPU;
  //
  G4double maxCos{ 0.0 };
  G4double maxSin2{ 0.0 };
  G4double beta{ 0.0 };
  G4double beta1{ 0.0 };
  G4double beta2{ 0.0 };
  G4double BetaInverse{ 0.0 };
  G4double MeanNumberOfPhotons1{ 0.0 };
  G4double MeanNumberOfPhotons2{ 0.0 };
  G4int Sphotons{ 0 };  // number of scintillation photons this step
  G4int Cphotons{ 0 };  // number of Cerenkov photons this step
  const G4double ScintillationTime{ 0.0 };
  const G4int scntId{ 1 };
#endif
};
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#endif
