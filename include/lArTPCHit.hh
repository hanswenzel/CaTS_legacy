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
#ifndef LARTPCHIT_HH
#define LARTPCHIT_HH
#pragma once
#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4Types.hh"  // for G4double, G4bool
#include "G4ios.hh"    // for G4cout, G4endl
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
class lArTPCHit : public G4VHit
{
 public:
  lArTPCHit();
  ~lArTPCHit();
  lArTPCHit(G4double fe, G4double fx, G4double fy, G4double fz);
  lArTPCHit(const lArTPCHit&);
  const lArTPCHit& operator=(const lArTPCHit&);
  G4bool operator==(const lArTPCHit&) const;
  inline void* operator new(size_t);
  inline void operator delete(void*);
  virtual void Draw();
  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
  inline virtual void Print()
  {
    G4cout << "lArTPCHit Nr. of electrons: " << fElectrons << "  x position [mm]: " << fPosX
           << "  y position [mm]: " << fPosY << "  z position [mm]: " << fPosZ << G4endl;
  }
  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
  void SetElectrons(G4double de) { fElectrons = de; };
  void SetPosX(G4double x) { fPosX = x; };
  void SetPosY(G4double y) { fPosY = y; };
  void SetPosZ(G4double z) { fPosZ = z; };
  G4double GetEdep() { return fElectrons; };
  G4double GetPosX() { return fPosX; };
  G4double GetPosY() { return fPosY; };
  G4double GetPosZ() { return fPosZ; };

 private:
  G4double fElectrons{ 0 };
  G4double fPosX{ 0 };
  G4double fPosY{ 0 };
  G4double fPosZ{ 0 };
};
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
using lArTPCHitsCollection = G4THitsCollection<lArTPCHit>;
extern G4ThreadLocal G4Allocator<lArTPCHit>* lArTPCHitAllocator;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
inline void* lArTPCHit::operator new(size_t)
{
  if(!lArTPCHitAllocator)
  {
    lArTPCHitAllocator = new G4Allocator<lArTPCHit>;
  }
  return (void*) lArTPCHitAllocator->MallocSingle();
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
inline void lArTPCHit::operator delete(void* aHit)
{
  lArTPCHitAllocator->FreeSingle((lArTPCHit*) aHit);
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#endif /* LARTPCHIT_HH */
