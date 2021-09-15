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
#ifndef PhotonHit_h
#define PhotonHit_h 1
#pragma once
#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
class PhotonHit : public G4VHit
{
 public:
  PhotonHit();
  ~PhotonHit();
  PhotonHit(const PhotonHit&);
  const PhotonHit& operator=(const PhotonHit&);
  G4bool operator==(const PhotonHit&) const;
  inline void* operator new(size_t);
  inline void operator delete(void*);
  virtual void Draw();
  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
  inline virtual void Print()
  {
    G4cout << "PhotonHit id: " << id << " pid: " << pid
           << " wavelength: " << wavelength << " time: " << time
           << " position X: " << position.getX() << " Y: " << position.getY()
           << " Z: " << position.getZ() << " direction X: " << direction.getX()
           << " Y: " << direction.getY() << " Z: " << direction.getZ()
           << " polarization: X:" << polarization.getX()
           << " Y: " << polarization.getY() << " Z: " << polarization.getZ()
           << G4endl;
  }
  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
  PhotonHit(unsigned id, unsigned pid, G4double wavelength, G4double time,
            G4ThreeVector position, G4ThreeVector direction,
            G4ThreeVector polarization);
  inline void SetWavelength(G4double wavelength)
  {
    this->wavelength = wavelength;
  }
  inline G4double GetWavelength() { return wavelength; }
  inline void SetPolarization(G4ThreeVector polarization)
  {
    this->polarization = polarization;
  }
  inline G4ThreeVector GetPolarization() const { return polarization; }
  inline void SetDirection(G4ThreeVector direction)
  {
    this->direction = direction;
  }
  inline G4ThreeVector GetDirection() const { return direction; }
  inline void SetPosition(G4ThreeVector position) { this->position = position; }
  inline G4ThreeVector GetPosition() const { return position; }
  inline void SetTime(G4double time) { this->time = time; }
  inline G4double GetTime() const { return time; }
  inline void SetPid(unsigned pid) { this->pid = pid; }
  inline unsigned GetPid() const { return pid; }
  inline void SetId(unsigned id) { this->id = id; }
  inline unsigned GetId() const { return id; }

 private:
  unsigned id{ 0 };
  unsigned pid{ 0 };
  G4double wavelength{ 0 };
  G4double time{ 0 };
  G4ThreeVector position{ 0 };
  G4ThreeVector direction{ 0 };
  G4ThreeVector polarization{ 0 };
};
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
using PhotonHitsCollection = G4THitsCollection<PhotonHit>;
extern G4ThreadLocal G4Allocator<PhotonHit>* PhotonHitAllocator;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
inline void* PhotonHit::operator new(size_t)
{
  if(!PhotonHitAllocator)
  {
    PhotonHitAllocator = new G4Allocator<PhotonHit>;
  }
  return (void*) PhotonHitAllocator->MallocSingle();
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
inline void PhotonHit::operator delete(void* aHit)
{
  PhotonHitAllocator->FreeSingle((PhotonHit*) aHit);
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#endif
