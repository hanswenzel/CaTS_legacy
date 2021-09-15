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
#include "CalorimeterHit.hh"
#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"
G4ThreadLocal G4Allocator<CalorimeterHit>* CalorimeterHitAllocator = nullptr;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
CalorimeterHit::CalorimeterHit()
  : G4VHit()
{}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
CalorimeterHit::CalorimeterHit(unsigned i, G4double e, G4double em, G4double t,
                               G4ThreeVector p)
  : G4VHit()
{
  id       = i;
  Edep     = e;
  em_Edep  = em;
  time     = t;
  position = p;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
CalorimeterHit::~CalorimeterHit() = default;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
CalorimeterHit::CalorimeterHit(const CalorimeterHit& right)
  : G4VHit()
{
  // No need to call class member functions via this->
  id       = right.id;
  Edep     = right.Edep;
  em_Edep  = right.em_Edep;
  time     = right.time;
  position = right.position;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
const CalorimeterHit& CalorimeterHit::operator=(const CalorimeterHit& right)
{
  // No need to call class member functions via this->
  id       = right.id;
  Edep     = right.Edep;
  em_Edep  = right.em_Edep;
  time     = right.time;
  position = right.position;
  return *this;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4bool CalorimeterHit::operator==(const CalorimeterHit& right) const
{
  return (this == &right) ? true : false;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void CalorimeterHit::Draw()
{
  G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
  if(pVVisManager)
  {
    G4Circle circle(position);
    circle.SetScreenSize(2.);
    circle.SetFillStyle(G4Circle::filled);
    G4Colour colour(1., 0., 0.);
    G4VisAttributes attribs(colour);
    circle.SetVisAttributes(attribs);
    pVVisManager->Draw(circle);
  }
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
