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
#ifndef Ctx_h
#define Ctx_h 1
/**
Follow pattern of CG4Ctx
 **/
#pragma once
#include <string>
#include "G4ThreeVector.hh"

class G4Event;
class G4Track;
class G4Step;
class G4StepPoint;

class Ctx {
public:
    static std::string Format(const G4Step* step, const char* msg);
    static std::string Format(const G4StepPoint* point, const char* msg);
    static std::string Format(const G4ThreeVector& vec, const char* msg, unsigned int fwid);

    const G4Event* _event;
    int _event_id;

    const G4Track* _track;
    int _track_id;
    int _record_id;

    int _track_step_count;
    int _track_pdg_encoding;
    bool _track_optical;
    std::string _track_particle_name;


    const G4Step* _step;
    int _step_id;
    G4ThreeVector _step_origin;

    void setEvent(const G4Event* event);

    void setTrack(const G4Track* track);
    void postTrack(const G4Track* track);
    void setTrackOptical(const G4Track* track);
    void postTrackOptical(const G4Track* track);

    void setStep(const G4Step* step);
};
#endif
