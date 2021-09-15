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
#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1
#include "G4VUserDetectorConstruction.hh"
#include "Event.hh"
class ColorReader;
class G4GDMLParser;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
class DetectorConstruction : public G4VUserDetectorConstruction
{
 public:
  DetectorConstruction(G4String fname);
  ~DetectorConstruction() override;
  // Prefer deleted functions to private undefined ones.
  DetectorConstruction& operator=(const DetectorConstruction& right) = delete;
  DetectorConstruction(const DetectorConstruction&)                  = delete;
  void ReadGDML();
  // Prefer to declare virtual functions with override,
  // virtual keyword can be then ommitted
  G4VPhysicalVolume* Construct() override;
  void ConstructSDandField() override;
  void UpdateGeometry();

 private:
  G4String gdmlFile;
  // Data members were not initialized
  G4GDMLParser* parser{ nullptr };
  ColorReader* fReader{ nullptr };
  bool verbose{ false };
};
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....
#endif
