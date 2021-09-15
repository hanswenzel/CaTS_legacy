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
#ifndef TRACKERHIT_HH
#define TRACKERHIT_HH
#pragma once
#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
class TrackerHit : public G4VHit
{
  // Default constructor
 public:
  TrackerHit();
  ~TrackerHit();
  TrackerHit(const TrackerHit&);
  const TrackerHit& operator=(const TrackerHit&);
  G4bool operator==(const TrackerHit&) const;
  inline void* operator new(size_t);
  inline void operator delete(void*);
  virtual void Draw();
  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
  inline virtual void Print()
  {
    G4cout << "TrackerHit  id:  " << id << " Edep: " << Edep
           << " X: " << position.getX() << " Y: " << position.getY()
           << " Z: " << position.getZ() << " time: " << time << G4endl;
  }
  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
  TrackerHit(G4double edep, G4ThreeVector position, G4double time);
  inline void SetEdep(G4double Edep) { this->Edep = Edep; }
  inline G4double GetEdep() { return Edep; }
  inline void SetTime(G4double time) { this->time = time; }
  inline G4double GetTime() const { return time; }
  inline void SetPosition(G4ThreeVector position) { this->position = position; }
  inline G4ThreeVector GetPosition() const { return position; }

 private:
  G4int id{ 0 };
  G4double Edep{ 0 };
  G4ThreeVector position{ 0 };
  G4double time{ 0 };
};
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
using TrackerHitsCollection = G4THitsCollection<TrackerHit>;
extern G4ThreadLocal G4Allocator<TrackerHit>* TrackerHitAllocator;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
inline void* TrackerHit::operator new(size_t)
{
  if(!TrackerHitAllocator)
  {
    TrackerHitAllocator = new G4Allocator<TrackerHit>;
  }
  return (void*) TrackerHitAllocator->MallocSingle();
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
inline void TrackerHit::operator delete(void* aHit)
{
  TrackerHitAllocator->FreeSingle((TrackerHit*) aHit);
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#endif
