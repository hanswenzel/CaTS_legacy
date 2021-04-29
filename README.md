# CaTS: Calorimeter and Tracker Simulation

CaTS is a flexible and extend-able framework (based on geant4 and ROOT)
for the simulation of calorimeter and tracking detectors. 
It also serves as an Example that demonstrates how to use opticks
from within Geant4 for the creation and propagation of optical photons.
https://bitbucket.org/simoncblyth/opticks.git.
This requires the opticks environment to be set up properly.  At the moment we
use the following external packages and versions thereof:  

- nvidia Optix 6.5
- nvidia cuda 11.0
- nvidia driver 460.27.04
- geant4 10.7.p01 
- boost 1.71.0
- xercesc 3.2.2
- openmesh 6.3
- glew 1.13.0
- glfw 3.1.1
- cmake 3.18.4

To get started : 

```bash
git clone https://github.com/hanswenzel/CaTS.git
cd CaTS/

# now have a look at set_env_lq.sh and change the variables on the top to point to the opticks installation you want to use and change it accordingly.
# The provided set_env_lq.sh gives an example.
# After you changed it:

cp set_env_lq.sh set_env.sh
source setup_opticks.sh 
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
export OPTICKS_EMBEDDED_COMMANDLINE_EXTRA="--rngmax 10"
time ./CaTS -gdml G4Opticks_50000.gdml -pl 'FTFP_BERT+OPTICAL'  -macro muon_IO.mac
```
