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
#ifndef MSCHIT_HH
#define MSCHIT_HH
#pragma once
#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"

class MscHit : public G4VHit {
    // Default constructor
public:
    MscHit();
    ~MscHit();
    MscHit(const MscHit&);
    const MscHit& operator=(const MscHit&);
    G4bool operator==(const MscHit&) const;
    inline void* operator new(size_t);
    inline void operator delete(void*);
    virtual void Draw();
    //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

    inline virtual void Print() {
        G4cout << "MscHit KinE: " << kinE
                << " Px: " << momentum.getX()
                << " Py: " << momentum.getY()
                << " Pz: " << momentum.getZ() << G4endl;
    }

    MscHit(double kinE, G4ThreeVector momentum);
    void SetKinE(double kinE);
    double GetKinE() const;
    void SetMomentum(G4ThreeVector momentum);
    G4ThreeVector GetMomentum() const;


private:
    double kinE{0};
    G4ThreeVector momentum{0};
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

using MscHitsCollection = G4THitsCollection<MscHit>;
extern G4ThreadLocal G4Allocator<MscHit>* MscHitAllocator;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void* MscHit::operator new(size_t){
    if (!MscHitAllocator) {
        MscHitAllocator = new G4Allocator<MscHit>;
    }
    return (void *) MscHitAllocator->MallocSingle();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void MscHit::operator delete(void *aHit) {
    MscHitAllocator->FreeSingle((MscHit*) aHit);
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#endif
