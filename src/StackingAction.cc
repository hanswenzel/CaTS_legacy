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
// Project headers
#include "StackingAction.hh"
#include "StackingActionMessenger.hh"
// Geant4 headers
#include "G4ParticleDefinition.hh"
#include "G4Track.hh"
#include "G4ios.hh"
#include "G4VProcess.hh"
#include "G4ClassificationOfNewTrack.hh"
#include <G4UserStackingAction.hh>  // for G4UserStackingAction

StackingAction* StackingAction::instance = 0;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
StackingAction::StackingAction()
  : G4UserStackingAction()
{
  pMessenger = new StackingActionMessenger(this);
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
StackingAction::~StackingAction() { delete pMessenger; }
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4ClassificationOfNewTrack StackingAction::ClassifyNewTrack(const G4Track* aTrack)
{
  G4ClassificationOfNewTrack classification = fWaiting;
  if(aTrack->GetParentID() == 0)
    return classification;
  if(aTrack->GetDefinition()->GetParticleName() == "pi0")
  {
    if(killPi0)
    {
      classification = fKill;
    }
  }
  if(aTrack->GetDefinition()->GetParticleName() == "eta")
  {
    if(killeta)
    {
      classification = fKill;
    }
  }
  if(aTrack->GetDefinition()->GetParticleName() == "gamma")
  {
    if(aTrack->GetCreatorProcess()->GetProcessName() == "nCapture")
    {
      if(killGammafromnCapture)
      {
        classification = fKill;
      }
    }
  }
  return classification;
}
void StackingAction::BeginRun() {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void StackingAction::NewStage() {}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void StackingAction::PrepareNewEvent() {}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void StackingAction::BeginofEvent() {}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void StackingAction::EndofEvent() {}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void StackingAction::Print()
{
  G4cout << "===================================================" << G4endl;
  G4cout << " StackingAction configuration:      " << G4endl;
  G4cout << " Kill Pi0s :                        " << killPi0 << G4endl;
  G4cout << " Kill etas :                        " << killeta << G4endl;
  G4cout << " Kill Gammas from neutron Capture:  " << killGammafromnCapture << G4endl;
  G4cout << "===================================================" << G4endl;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
StackingAction* StackingAction::getInstance()
{
  if(instance == 0)
    instance = new StackingAction();
  return instance;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
