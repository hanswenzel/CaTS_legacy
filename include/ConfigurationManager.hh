// -----------------------------------------------------
//  _    _        _____         _   
// | |  / \   _ _|_   _|__  ___| |_ 
// | | / _ \ | '__|| |/ _ \/ __| __|
// | |/ ___ \| |   | |  __/\__ \ |_ 
// |_/_/   \_\_|   |_|\___||___/\__|
//                                  
// lArTest: A Geant4 application to study and profile  
//          simulation of physics processes relevant 
//          to liquid Ar TPCs
//
// Author: Hans Wenzel, Fermilab
// -----------------------------------------------------
#ifndef ConfigurationManager_h
#define ConfigurationManager_h 1
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
/* ------------------------------------------------------------------------
            |\___/|       
            )     (    
           =\     /=
             )===(
            /     \         CaTS: Calorimeter and Tracker Simulation
            |     |         CaTS is a flexible and extend-able framework 
           /       \        for the simulation of calorimeter and tracking detectors. 
           \       /        https://github.com/hanswenzel/CaTS
            \__  _/         CaTS also serves as an Example that demonstrates how to 
              ( (           use opticks from within Geant4 for the creation and propagation 
               ) )          of optical photons. 
              (_(           (see https://bitbucket.org/simoncblyth/opticks.git). 
-------------------------------------------------------------------------*/
// Ascii Art by Joan Stark: https://www.asciiworld.com/-Cats-2-.html

#include <vector>
#include "G4String.hh"
class ConfigurationManagerMessenger;

class ConfigurationManager {
private:
    static ConfigurationManager* instance;

#ifdef WITH_ROOT 
    bool doAnalysis; // variable determines if we are doing analysis
    G4String HistoFileName; // File name for histos and  ntuples
    bool writeHits; // variable determines if hits are written out into Root File
    G4String FileName; // File name for root io
    G4String fname; // full File name for root io
#endif
#ifdef WITH_G4OPTICKS  
    bool enable_opticks; // use opticks if available
    unsigned int MaxPhotons;
#endif
    bool enable_verbose; // switch on/off diagnostic printouts
    bool dumpgdml; // write out Detector to gdml file
    G4String GDMLFileName;
    ConfigurationManagerMessenger* confMessenger;
    ConfigurationManager();
public:

    ~ConfigurationManager();
    static ConfigurationManager* getInstance();

#ifdef WITH_ROOT

    inline void setHistoFileName(G4String HistoFileName) {
        this->HistoFileName = HistoFileName;
    }

    inline G4String getHistoFileName() const {
        return HistoFileName;
    }

    inline void setWriteHits(bool writeHits) {
        this->writeHits = writeHits;
    }

    inline bool isWriteHits() const {
        return writeHits;
    }

    inline void setdoAnalysis(bool writeHits) {
        this->doAnalysis = doAnalysis;
    }

    inline bool isdoAnalysis() const {
        return doAnalysis;
    }

    inline void setFileName(G4String FileName) {
        this->FileName = FileName;
    }

    inline G4String getFileName() const {
        return FileName;
    }

    inline void setfname(G4String fname) {
        this->fname = fname;
    }

    inline G4String getfname() const {
        return fname;
    }
#endif  

    inline void setEnable_verbose(bool enable_verbose) {
        this->enable_verbose = enable_verbose;
    };

    inline bool isEnable_verbose() const {
        return enable_verbose;
    };

    inline void setGDMLFileName(G4String GDMLFileName) {
        this->GDMLFileName = GDMLFileName;
    }

    inline G4String getGDMLFileName() const {
        return GDMLFileName;
    }

    inline void setDumpgdml(bool dumpgdml) {
        this->dumpgdml = dumpgdml;
    }

    inline bool isDumpgdml() const {
        return dumpgdml;
    }

#ifdef WITH_G4OPTICKS 

    inline void setEnable_opticks(bool enable_opticks) {
        this->enable_opticks = enable_opticks;
    };

    inline bool isEnable_opticks() const {
        return enable_opticks;
    };
    void setMaxPhotons(unsigned int MaxPhotons);
    unsigned int getMaxPhotons() const;

#endif
};
#endif /* /CONFIGURATIONMANAGER */

