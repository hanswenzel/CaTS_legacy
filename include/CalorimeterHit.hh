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
#ifndef CalorimeterHit_h
#define CalorimeterHit_h 1
#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
class CalorimeterHit : public G4VHit
{
 public:
  CalorimeterHit();
  ~CalorimeterHit();
  CalorimeterHit(const CalorimeterHit&);
  const CalorimeterHit& operator=(const CalorimeterHit&);
  G4bool operator==(const CalorimeterHit&) const;
  inline void* operator new(size_t);
  inline void operator delete(void*);
  virtual void Draw();
  inline virtual void Print()
  {
    G4cout << "CalorimeterHit  id:  " << fid << " Edep: " << fEdep << " em_Edep: " << fem_Edep
           << " time: " << ftime << " X: " << fposition.getX() << " Y: " << fposition.getY()
           << " Z: " << fposition.getZ() << G4endl;
  }
  CalorimeterHit(unsigned int i, double e, double em, double t, G4ThreeVector p);
  inline void SetPosition(G4ThreeVector position) { this->fposition = position; };
  inline G4ThreeVector GetPosition() const { return fposition; };
  inline void SetTime(double time) { this->ftime = time; };
  inline double GetTime() const { return ftime; };
  inline void SetId(unsigned int id) { this->fid = id; };
  inline unsigned int GetId() const { return fid; };
  inline void SetEdep(double Edep) { this->fEdep = Edep; };
  inline double GetEdep() const { return fEdep; };
  inline void Setem_Edep(double em_Edep) { this->fem_Edep = em_Edep; };
  inline double Getem_Edep() const { return fem_Edep; };

 private:
  unsigned int fid{ 0 };
  double fEdep{ 0 };
  double fem_Edep{ 0 };
  double ftime{ 0 };
  G4ThreeVector fposition{ 0 };
};
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
using CalorimeterHitsCollection = G4THitsCollection<CalorimeterHit>;
extern G4ThreadLocal G4Allocator<CalorimeterHit>* CalorimeterHitAllocator;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
inline void* CalorimeterHit::operator new(size_t)
{
  if(!CalorimeterHitAllocator)
  {
    CalorimeterHitAllocator = new G4Allocator<CalorimeterHit>;
  }
  return (void*) CalorimeterHitAllocator->MallocSingle();
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
inline void CalorimeterHit::operator delete(void* aHit)
{
  CalorimeterHitAllocator->FreeSingle((CalorimeterHit*) aHit);
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#endif
