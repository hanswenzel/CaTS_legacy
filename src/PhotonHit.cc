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
#include "PhotonHit.hh"
#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"
G4ThreadLocal G4Allocator<PhotonHit>* PhotonHitAllocator = 0;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PhotonHit::PhotonHit()
: G4VHit(),
id(0),
pid(0),
wavelength(0),
time(0),
position(0),
direction(0),
polarization(0) {
}

void PhotonHit::SetPolarization(G4ThreeVector polarization) {
    this->polarization = polarization;
}

G4ThreeVector PhotonHit::GetPolarization() const {
    return polarization;
}

void PhotonHit::SetDirection(G4ThreeVector direction) {
    this->direction = direction;
}

G4ThreeVector PhotonHit::GetDirection() const {
    return direction;
}

void PhotonHit::SetPosition(G4ThreeVector position) {
    this->position = position;
}

G4ThreeVector PhotonHit::GetPosition() const {
    return position;
}

void PhotonHit::SetTime(G4double time) {
    this->time = time;
}

G4double PhotonHit::GetTime() const {
    return time;
}

void PhotonHit::SetWavelength(G4double wavelength) {
    this->wavelength = wavelength;
}

void PhotonHit::SetPid(unsigned pid) {
    this->pid = pid;
}

unsigned PhotonHit::GetPid() const {
    return pid;
}

void PhotonHit::SetId(unsigned id) {
    this->id = id;
}

unsigned PhotonHit::GetId() const {
    return id;
}

PhotonHit::PhotonHit(unsigned iid,
        unsigned ipid,
        G4double iwavelength,
        G4double itime,
        G4ThreeVector iposition,
        G4ThreeVector idirection,
        G4ThreeVector ipolarization) : G4VHit() {
    id = iid;
    pid = ipid;
    wavelength = iwavelength;
    time = itime;
    position = iposition;
    direction = idirection;
    polarization = ipolarization;
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PhotonHit::~PhotonHit() {
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PhotonHit::PhotonHit(const PhotonHit& right)
: G4VHit() {
    id = right.id;
    pid = right.pid;
    wavelength = right.wavelength;
    time = right.time;
    position = right.position;
    direction = right.direction;
    polarization = right.polarization;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

const PhotonHit& PhotonHit::operator=(const PhotonHit& right) {
    id = right.id;
    pid = right.pid;
    wavelength = right.wavelength;
    time = right.time;
    position = right.position;
    direction = right.direction;
    polarization = right.polarization;
    return *this;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4bool PhotonHit::operator==(const PhotonHit& right) const {
    return (this == &right) ? true : false;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PhotonHit::Draw() {
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

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PhotonHit::Print() {
    G4cout << "id: " << id
            << " pid: " << pid
            << " wavelength: " << wavelength
            << " time: " << time
            << G4endl;
    //    position.
    //    G4ThreeVector position;
    //    G4ThreeVector direction;
    //    G4ThreeVector polarization;
    //  G4cout << "  trackID: " << fTrackID << "  chamberNb: " << fChamberNb
    //          << "  wavelength deposit[MeV]: " << fEdep
    //          << "  position[mm]: " << fPos << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
