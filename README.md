![alt text](https://github.com/hanswenzel/CaTS/blob/master/images/CaTS.png)
# CaTS: Calorimeter and Tracker Simulation

CaTS is a flexible and extend-able framework (based on geant4 and ROOT)
for the simulation of calorimeter and tracking detectors. 
It also serves as an Example that demonstrates how to use opticks
from within Geant4 for the creation and propagation of optical photons.
https://bitbucket.org/simoncblyth/opticks.git.

The components of CaTS are:


Detector Description:      described in gdml input file (e.g. crystalcal.gdml)
(Geometry, Materials,
 optical properties,
 sensitive detector)

Input modules:                

    GPS
    Particle Gun
    HEPMC (Pythia)


Physics Lists:                  choice of all Reference Physics Lists
                                          optical physics processes (Cerenkov, Rayleigh,
                                          Scintillation etc.) are added (talk to)  
                
Sensitive Detectors:        (+ corresponding Hit classes)        

    TrackerSD(Hit)  
    CalorimeterSD(Hit)
    DRCalorimeterSD(Hit) (besides registering energy deposit counts produced Cerenkov photons)
    StoppingCalorimeterSD (registers total energy of entering particle and kills the particle afterwards to avoid further tracking)
    PhotonSD(Hit): sensitive detector that  registers optical photons.





This requires the opticks environment to be set up properly (see  https://github.com/hanswenzel/CaTS/blob/master/Instructions.md)

To get started : 

```bash
git clone https://github.com/hanswenzel/CaTS.git
cd CaTS/

# to setup the opticks environment source the setup_opticks.sh file described in:
# https://github.com/hanswenzel/CaTS/blob/master/Instructions.md


source (path to opticks WORK_DIR)/setup_opticks.sh 
cd ../
mkdir CaTS-build
cd CaTS-build

cmake -DCMAKE_BUILD_TYPE=Debug \
  -DCMAKE_PREFIX_PATH="${LOCAL_BASE}/opticks/externals;${LOCAL_BASE}/opticks" \
  -DOPTICKS_PREFIX=${LOCAL_BASE}/opticks \
  -DCMAKE_MODULE_PATH=${OPTICKS_HOME}/cmake/Modules \
  -DCMAKE_INSTALL_PREFIX=../CaTS-install \
  ../CaTS

make install
cd ../CaTS-install/bin
time ./CaTS -g  simpleLArTPC.gdml -pl 'FTFP_BERT+OPTICAL+STEPLIMIT'  -m time.mac

Only the -g command line variable is mandatory! If you don't specify the macro file interactive mode is assumed:

./CaTS -g simpleLArTPC.gdml -pl 'FTFP_BERT+OPTICAL+STEPLIMIT'

if you don't provide the -pl argument the default physics list configuration:
'FTFP_BERT+OPTICAL+STEPLIMIT'
is used

```
![alt text](https://github.com/hanswenzel/CaTS/blob/master/images/display.png)
```bash
to look at the hit collection and make a few histograms:

./readHits  NewHits_Run0.root histos.root

on can the use root to look  at the plots:

root histos.root
   ------------------------------------------------------------------
  | Welcome to ROOT 6.22/06                        https://root.cern |
  | (c) 1995-2020, The ROOT Team; conception: R. Brun, F. Rademakers |
  | Built for linuxx8664gcc on Dec 13 2020, 13:28:00                 |
  | From tags/v6-22-06@v6-22-06                                      |
  | Try '.help', '.demo', '.license', '.credits', '.quit'/'.q'       |
   ------------------------------------------------------------------

root [0] 
Attaching file histos.root as _file0...
(TFile *) 0x559578f76f60
root [1] TBrowser b
(TBrowser &) Name: Browser Title: ROOT Object Browser
```

![alt text](https://github.com/hanswenzel/CaTS/blob/master/images/position.png)

