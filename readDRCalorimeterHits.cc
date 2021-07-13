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
#include "TROOT.h"
#include "TFile.h"
#include "TSystem.h"
#include "TKey.h"
#include "TTree.h"
#include "TH1.h"
#include "TH2.h"
//
#include "Event.hh"
#include "lArTPCHit.hh"
#include "PhotonHit.hh"
#include "CalorimeterHit.hh"
#include "DRCalorimeterHit.hh"
#include "InteractionHit.hh"
using namespace std;

int main(int argc, char** argv) {
    // initialize ROOT
    TSystem ts;
    gSystem->Load("libCaTSClassesDict");
    //if (argc < 2) cout << "Missing name of the file to read!" << endl;

    if (argc < 3) {
        G4cout << "Program requires 2 arguments: name of input file, name of output file" << G4endl;
        exit(1);
    }
    TFile* outfile = new TFile(argv[2], "RECREATE");
    outfile->cd();
    //    TH1F* hedep = new TH1F("energy", "edep", 1100, 0.0, 105000.);
    //TH1F* hnceren = new TH1F("nceren", "nceren", 70000, 0.0, 7000000.);
    TH2F* pos2 = new TH2F("pposition", "position of Photon Hits", 400, -1000., 1000., 400, -500, 500);
    TH1F* time = new TH1F("time", "timing of photon hits", 400, 0., 100.);
    TH1F* time0 = new TH1F("time0", "timing of photon hits", 400, 0., 100.);
    TH1F* time1 = new TH1F("time1", "timing of photon hits", 400, 0., 100.);
    TH1F* time2 = new TH1F("time2", "timing of photon hits", 400, 0., 100.);
    TH1F* pe = new TH1F("pe", "wavelength of detected photons", 400, 0., 400.);
    TFile fo(argv[1]);
    std::vector<lArTPCHit*> hits;
    std::vector<PhotonHit*> hitsp;
    //  avoid unused variable warning
    //    (void) hits;
    //    (void) hitsp;
    fo.GetListOfKeys()->Print();
    Event *event = new Event();
    TTree *Tevt = (TTree*) fo.Get("Events");
    Tevt->SetBranchAddress("event.", &event);
    TBranch* fevtbranch = Tevt->GetBranch("event.");
    Int_t nevent = fevtbranch->GetEntries();
    bool verbose = false;
    if (verbose) cout << " Nr. of Events:  " << nevent << endl;
    double max = 0.;
    double min = 1000000;
    double nmax = 0.;
    double nmin = 1000000000;
    for (Int_t i = 0; i < nevent; i++) {
        fevtbranch->GetEntry(i);
        std::map<G4String, std::vector<G4VHit*> > *hcmap = event->GetHCMap();
        std::map<G4String, std::vector<G4VHit*> >::iterator hciter;
        //cout << "Number of Hit collections:  " << hcmap->size() << endl;
        for (hciter = hcmap->begin(); hciter != hcmap->end(); hciter++) {
            //cout << (*hciter).first << endl;
            std::vector<G4VHit*> hits = (*hciter).second;
            //std::vector<G4String> hits;
            G4int NbHits = hits.size();
            if ((*hciter).first == "CalorimeterVolume_DRCalorimeter_HC") {
                for (G4int ii = 0; ii < NbHits; ii++) {
                    DRCalorimeterHit* drcaloHit = dynamic_cast<DRCalorimeterHit*> (hits.at(ii));
                    const double ed = drcaloHit->GetEdep();
                    if (ed > max) max = ed;
                    if (ed < min) min = ed;
                    const unsigned int nceren = drcaloHit->GetNceren();
                    if (nceren > nmax) nmax = nceren;
                    if (nceren < nmin) nmin = nceren;
                }
            }
            if ((*hciter).first == "volArgon_Target_HC") {

                cout << "=================================" << endl;
                for (G4int ii = 0; ii < NbHits; ii++) {
                    InteractionHit* interHit = dynamic_cast<InteractionHit*> (hits.at(ii));
                    cout << interHit->GetPname() << endl;
                }
            }
            if ((hciter)->first == "Det_Photondetector_HC") {
                cout << "Number of Hits   :  " << hits.size() << endl;
                for (G4int ii = 0; ii < NbHits; ii++) {
                    PhotonHit* photonHit = dynamic_cast<PhotonHit*> (hits.at(ii));
                    //                  cout << "X: " << photonHit->GetPosition().getX() << endl;
                    //                  cout << "Y: " << photonHit->GetPosition().getY() << endl;
                    //                  cout << "Z: " << photonHit->GetPosition().getZ() << endl;
                    cout << photonHit->GetWavelength()*1.e-6 << endl;
                    time->Fill(photonHit->GetTime());
                    pe->Fill(photonHit->GetWavelength()*1.e-6);
                    if (photonHit->GetPosition().getZ()<-100.) time0->Fill(photonHit->GetTime());
                    if (photonHit->GetPosition().getZ()>-100. && photonHit->GetPosition().getZ() < 100) time1->Fill(photonHit->GetTime());
                    if (photonHit->GetPosition().getZ() < 100.) time2->Fill(photonHit->GetTime());
                    pos2->Fill(photonHit->GetPosition().getZ(), photonHit->GetPosition().getY());
                }
            }
        }
    }
    outfile->cd();
    TH1F* hedep = new TH1F("energy", "edep", 100, min, max);
    TH1F* hnceren = new TH1F("nceren", "nceren", 100, nmin, nmax);
    for (Int_t i = 0; i < nevent; i++) {
        fevtbranch->GetEntry(i);
        std::map<G4String, std::vector<G4VHit*> >* hcmap = event->GetHCMap();
        std::map<G4String, std::vector<G4VHit*> >::iterator hciter;
        for (hciter = hcmap->begin(); hciter != hcmap->end(); hciter++) {
            std::vector<G4VHit*> hits = (*hciter).second;
            G4int NbHits = hits.size();
            if ((hciter)->first == "CalorimeterVolume_DRCalorimeter_HC") {
                for (G4int ii = 0; ii < NbHits; ii++) {
                    DRCalorimeterHit* drcaloHit = dynamic_cast<DRCalorimeterHit*> (hits.at(ii));
                    hedep->Fill(drcaloHit->GetEdep());
                    hnceren->Fill(drcaloHit->GetNceren());
                }
            }
        }
    }
    //hedep->Fit("gaus");
    //hnceren->Fit("gaus");
    outfile->Write();
}

