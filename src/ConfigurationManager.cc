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
#include "ConfigurationManager.hh"
//#include <G4String.hh>                       // for G4String
#include <G4ios.hh>                          // for G4cout, G4endl
#include <ostream>                           // for operator<<, basic_ostream
#include <string>                            // for operator<<
#include "ConfigurationManagerMessenger.hh"  // for ConfigurationManagerMess...
ConfigurationManager* ConfigurationManager::instance = nullptr;
std::once_flag ConfigurationManager::initInstanceFlag;
ConfigurationManager::ConfigurationManager()
{
  confMessenger = new ConfigurationManagerMessenger(this);
}
ConfigurationManager::~ConfigurationManager() { delete confMessenger; }
void ConfigurationManager::Print()
{
  G4cout << "--------------------------------------------------" << G4endl;
  G4cout << "CaTS configuration: " << G4endl;
  G4cout << "====================" << G4endl;
  G4cout << G4endl;
  G4cout << "fenable_verbose:   " << fenable_verbose << G4endl;
  G4cout << "fdumpgdml:         " << fdumpgdml << G4endl;
  G4cout << "fGDMLFileName:     " << fGDMLFileName << G4endl;
#ifdef WITH_ROOT
  G4cout << "doAnalysis:       " << fdoAnalysis << G4endl;
  G4cout << "HistoFileName:    " << fHistoFileName << G4endl;
  G4cout << "writeHits:        " << fwriteHits << G4endl;
  G4cout << "FileName:         " << fFileName << G4endl;
  G4cout << "fname:            " << fname << G4endl;
#endif
#ifdef WITH_G4OPTICKS
  G4cout << "enable_opticks:   " << fenable_opticks << G4endl;
  G4cout << "MaxPhotons:       " << fMaxPhotons << G4endl;
#endif
  G4cout << "--------------------------------------------------" << G4endl;
}
