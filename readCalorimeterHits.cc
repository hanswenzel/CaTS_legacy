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
           /       \        for the simulation of calorimeter and tracking
detectors. \       /        https://github.com/hanswenzel/CaTS
            \__  _/         CaTS also serves as an Example that demonstrates how
to ( (           use opticks from within Geant4 for the creation and propagation
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

int main(int argc, char** argv)
{
  // initialize ROOT
  TSystem ts;
  gSystem->Load("libCaTSClassesDict");
  if(argc < 3)
  {
    G4cout
      << "Program requires 2 arguments: name of input file, name of output file"
      << G4endl;
    exit(1);
  }
  TFile* outfile = new TFile(argv[2], "RECREATE");
  TFile fo(argv[1]);
  fo.GetListOfKeys()->Print();
  Event* event = new Event();
  TTree* Tevt  = (TTree*) fo.Get("Events");
  Tevt->SetBranchAddress("event.", &event);
  TBranch* fevtbranch = Tevt->GetBranch("event.");
  Int_t nevent        = fevtbranch->GetEntries();
  cout << " Nr. of Events:  " << nevent << endl;
  double max            = 0.;
  double min            = 1000000;
  string CollectionName = argv[3];
  CollectionName        = CollectionName + "_Calorimeter_HC";
  for(Int_t i = 0; i < nevent; i++)
  {
    fevtbranch->GetEntry(i);
    auto* hcmap = event->GetHCMap();
    for(const auto ele : *hcmap)
    {
      if(ele.first.compare(CollectionName) == 0)
      {
        auto hits    = ele.second;
        G4int NbHits = hits.size();
        for(G4int ii = 0; ii < NbHits; ii++)
        {
          CalorimeterHit* drcaloHit =
            dynamic_cast<CalorimeterHit*>(hits.at(ii));
          const double ed = drcaloHit->GetEdep();
          if(ed > max)
            max = ed;
          if(ed < min)
            min = ed;
        }
      }
    }
  }
  outfile->cd();
  TH1F* hedep =
    new TH1F("energy", "edep", 100, min - 0.1 * min, max + 0.1 * max);
  for(Int_t i = 0; i < nevent; i++)
  {
    fevtbranch->GetEntry(i);
    auto* hcmap = event->GetHCMap();
    for(const auto ele : *hcmap)
    {
      if(ele.first.compare(CollectionName) == 0)
      {
        auto hits    = ele.second;
        G4int NbHits = hits.size();
        for(G4int ii = 0; ii < NbHits; ii++)
        {
          CalorimeterHit* drcaloHit =
            dynamic_cast<CalorimeterHit*>(hits.at(ii));
          hedep->Fill(drcaloHit->GetEdep());
        }
      }
    }
  }
  // hedep->Fit("gaus");
  outfile->Write();
}