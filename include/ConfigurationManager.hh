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
#ifndef ConfigurationManager_h
#define ConfigurationManager_h 1
//#include <G4String.icc>  // for G4String::operator=, G4String::G4String
#include <mutex>        // for call_once, once_flag
#include "G4String.hh"  // for G4String
class ConfigurationManagerMessenger;
class ConfigurationManager
{
 private:
  static ConfigurationManager* instance;
  static std::once_flag initInstanceFlag;
#ifdef WITH_ROOT
  bool fdoAnalysis{ false };                     // variable determines if we are doing analysis
  G4String fHistoFileName{ "histograms.root" };  // File name for histos and  ntuples
  bool fwriteHits{ false };       // variable determines if hits are written out into Root File
  G4String fFileName;             // File name for root io
  G4String fname{ "hits.root" };  // full File name for root io
#endif
#ifdef WITH_G4OPTICKS
  bool fenable_opticks{ true };  // use opticks if available
  unsigned int fMaxPhotons{ 1000000 };
#endif
  bool fenable_verbose{ false };  // switch on/off diagnostic printouts
  bool fdumpgdml{ false };        // write out Detector to gdml file
  G4String fGDMLFileName{ "dump.gdml_G4" };
  ConfigurationManagerMessenger* confMessenger;
  ConfigurationManager();

 public:
  ~ConfigurationManager();
  static ConfigurationManager* getInstance()
  {
    std::call_once(initInstanceFlag, ConfigurationManager::initConfigurationManager);
    //    if (instance == 0) instance = new ConfigurationManager;
    return instance;
  }
  static void initConfigurationManager() { instance = new ConfigurationManager(); }
#ifdef WITH_ROOT
  inline void setHistoFileName(G4String HistoFileName) { this->fHistoFileName = HistoFileName; }
  inline G4String getHistoFileName() const { return fHistoFileName; }
  inline void setWriteHits(bool writeHits) { this->fwriteHits = writeHits; }
  inline bool isWriteHits() const { return fwriteHits; }
  inline void setdoAnalysis(bool doAnalysis) { this->fdoAnalysis = doAnalysis; }
  inline bool isdoAnalysis() const { return fdoAnalysis; }
  inline void setFileName(G4String FileName) { this->fFileName = FileName; }
  inline G4String getFileName() const { return fFileName; }
  inline void setfname(G4String fname) { this->fname = fname; }
  inline G4String getfname() const { return fname; }
#endif
  void Print();
  inline void setEnable_verbose(bool fenable_verbose) { this->fenable_verbose = fenable_verbose; };
  inline bool isEnable_verbose() const { return fenable_verbose; };
  inline void setGDMLFileName(G4String fGDMLFileName) { this->fGDMLFileName = fGDMLFileName; }
  inline G4String getGDMLFileName() const { return fGDMLFileName; }
  inline void setDumpgdml(bool fdumpgdml) { this->fdumpgdml = fdumpgdml; }
  inline bool isDumpgdml() const { return fdumpgdml; }
#ifdef WITH_G4OPTICKS
  inline void setEnable_opticks(bool enable_opticks) { this->fenable_opticks = enable_opticks; };
  inline bool isEnable_opticks() const { return fenable_opticks; };
  inline void setMaxPhotons(unsigned int MaxPhotons) { this->fMaxPhotons = MaxPhotons; }
  inline unsigned int getMaxPhotons() const { return fMaxPhotons; }
#endif
};
#endif /* /CONFIGURATIONMANAGER */
