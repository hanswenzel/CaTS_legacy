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
// Geant4 headers
#include "G4SystemOfUnits.hh"
// project headers
#include "ConfigurationManager.hh"
#include "ConfigurationManagerMessenger.hh"
// using namespace std;
ConfigurationManager* ConfigurationManager::instance = nullptr;
std::once_flag ConfigurationManager::initInstanceFlag;
ConfigurationManager::ConfigurationManager()
{
  confMessenger = new ConfigurationManagerMessenger(this);
#ifdef WITH_ROOT
  HistoFileName = "histograms.root";
  doAnalysis    = false;  // by default don't do analysis
  fname         = "hits.root";
  writeHits     = false;  // by default we don't write hits
#endif
#ifdef WITH_G4OPTICKS
  enable_opticks = true;  // by default we use opticks
  MaxPhotons     = 1000000;
#endif
  // enable_verbose = false; // by default we run quiet
  // dumpgdml = false; // by default we don't write out Detector to gdml file
  // GDMLFileName = "dump.gdml_G4";
}
ConfigurationManager::~ConfigurationManager() { delete confMessenger; }
#ifdef WITH_G4OPTICKS
void ConfigurationManager::setMaxPhotons(unsigned int MaxPhotons)
{
  this->MaxPhotons = MaxPhotons;
}
unsigned int ConfigurationManager::getMaxPhotons() const { return MaxPhotons; }
#endif
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
  G4cout << "doAnalysis:       " << doAnalysis << G4endl;
  G4cout << "HistoFileName:    " << HistoFileName << G4endl;
  G4cout << "writeHits:        " << writeHits << G4endl;
  G4cout << "FileName:         " << FileName << G4endl;
  G4cout << "fname:            " << fname << G4endl;
#endif
#ifdef WITH_G4OPTICKS
  G4cout << "enable_opticks:   " << enable_opticks << G4endl;
  G4cout << "MaxPhotons:       " << MaxPhotons << G4endl;
#endif
  G4cout << "--------------------------------------------------" << G4endl;
}
