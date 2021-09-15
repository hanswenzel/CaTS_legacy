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
#include "MscSD.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4SDManager.hh"
#include "G4Event.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "ConfigurationManager.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
MscSD::MscSD(G4String name)
  : G4VSensitiveDetector(name)
{
  G4String HCname = name + "_HC";
  collectionName.insert(HCname);
  G4cout << collectionName.size() << "   MscSD name:  " << name
         << " collection Name: " << HCname << G4endl;
  fHCID   = -1;
  verbose = ConfigurationManager::getInstance()->isEnable_verbose();
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void MscSD::Initialize(G4HCofThisEvent* hce)
{
  fMscHitsCollection =
    new MscHitsCollection(SensitiveDetectorName, collectionName[0]);
  if(fHCID < 0)
  {
    if(verbose)
      G4cout << "MscSD::Initialize:  " << SensitiveDetectorName << "   "
             << collectionName[0] << G4endl;
    fHCID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
  }
  hce->AddHitsCollection(fHCID, fMscHitsCollection);
  done = false;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
MscSD::~MscSD() = default;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4bool MscSD::ProcessHits(G4Step* aStep, G4TouchableHistory*)
{
  if(!done)
  {
    if(aStep->GetTrack()->GetParentID() ==
       0)  // only care about the primary particle
    {
      const G4StepPoint* postStep = aStep->GetPostStepPoint();
      if(postStep->GetStepStatus() == fGeomBoundary)
      {
        MscHit* newHit =
          new MscHit(postStep->GetKineticEnergy(), postStep->GetMomentum());
        fMscHitsCollection->insert(newHit);
        done = true;
      }
    }
  }
  return true;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void MscSD::EndOfEvent(G4HCofThisEvent*)
{
  G4int NbHits = fMscHitsCollection->entries();
  if(verbose)
    G4cout << " Number of MscHits:  " << NbHits << G4endl;
}