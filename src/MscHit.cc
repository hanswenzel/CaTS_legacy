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
#include "MscHit.hh"
//#include "G4UnitsTable.hh"
G4ThreadLocal G4Allocator<MscHit>* MscHitAllocator = nullptr;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
MscHit::MscHit()
  : G4VHit()
{}
MscHit::MscHit(double E, G4ThreeVector mom)
  : G4VHit()
{
  this->kinE     = E;
  this->momentum = mom;
}
void MscHit::SetKinE(double kinE) { this->kinE = kinE; }
double MscHit::GetKinE() const { return kinE; }
void MscHit::SetMomentum(G4ThreeVector momentum) { this->momentum = momentum; }
G4ThreeVector MscHit::GetMomentum() const { return momentum; }
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
MscHit::~MscHit() {}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
MscHit::MscHit(const MscHit& right)
  : G4VHit()
{
  kinE     = right.kinE;
  momentum = right.momentum;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
const MscHit& MscHit::operator=(const MscHit& right)
{
  kinE     = right.kinE;
  momentum = right.momentum;
  return *this;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4bool MscHit::operator==(const MscHit& right) const
{
  return (this == &right) ? true : false;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void MscHit::Draw()
{
  /*
      G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
      if (pVVisManager) {
          G4Circle circle(position);
          circle.SetScreenSize(2.);
          circle.SetFillStyle(G4Circle::filled);
          G4Colour colour(1., 0., 0.);
          G4VisAttributes attribs(colour);
          circle.SetVisAttributes(attribs);
          pVVisManager->Draw(circle);
      }
   */
}
