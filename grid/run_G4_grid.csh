#!/bin/csh
# 
# File:   run_G4_grid.csh
# Author: wenzel
#
# Created on Feb 25, 2021, 10:02:31 AM
#
# $1 = condor Cluster
# $2 = condor Process
# $3 = name of Particle 
# $4 = Energy of Particle 
# $5 = Number of events
# $6 = x-position 
# $7 = y-position
# $8 = z-position
# $9 = x-direction 
# $10= y-direction
# $11= z-direction
# $12= GEANT Physics list
#--------------------------------------------------------------------------- 
if ($#argv < 12) then
    echo " script needs 12 input variables"
    exit
endif
echo " submitting process "  ${2} "to the grid"
echo start now
/bin/date
pwd
@ SEED         = $1 + $2
set Cluster    = $1
set Process    = $2 
set Particle   = `echo $3  | sed s/\'//g`
set Energy     = `echo $4  | sed s/\'//g`
set NRofEvents = `echo $5  | sed s/\'//g`
set xposition  = `echo $6  | sed s/\'//g`
set yposition  = `echo $7  | sed s/\'//g`
set zposition  = `echo $8  | sed s/\'//g`
set xdirection = `echo $9  | sed s/\'//g`
set ydirection = `echo $10 | sed s/\'//g`
set zdirection = `echo $11 | sed s/\'//g`
set PHYSLIST   = `echo $12 | sed s/\'//g`
#
set FILENAME=/data2/wenzel/G4_data/PBWO_${PHYSLIST}_${Particle}_${Energy}_${xposition}_${Cluster}_${Process}_hits.root
echo $FILENAME
echo $PHYSLIST
echo start
/bin/date
cd ${_CONDOR_SCRATCH_DIR} 
echo Particle ${Particle}
printenv
source /data2/wenzel/gputest10/setup_opticks.sh
cd /data2/wenzel/gputest10/CaTS-install/bin

/bin/cat > pip_IO_DR.mac << EOF+ 
/run/initialize 
#
#
#/process/inactivate Scintillation
/process/optical/scintillation/setStackPhotons false
#
# the Cerenkov process is needed even when we run on GPU (to get the number of photons to be produced) but we don't put optical photons on the stack
#
/process/activate  Cerenkov 
/process/optical/cerenkov/verbose 0
/process/optical/cerenkov/setStackPhotons false
#
/run/physicsModified
#
/run/initialize 
/random/setSeeds ${SEED}
/CaTS/ReferencePhysicsList ${PHYSLIST}
/CaTS/FileName ${FILENAME}
/CaTS/writeHits true 
/CaTS/enable_opticks false
/gun/particle ${Particle}
/gun/direction ${xdirection} ${ydirection} ${zdirection}
/gun/position  ${xposition}  ${yposition}  ${zposition}
/gun/energy ${Energy} GeV
/run/beamOn ${NRofEvents}
 EOF+ 
/bin/cat > /tmp/run_G4.mac << EOF+ 
/G4/random/randomSeed  ${SEED}
/G4/RootIO/Filename ${FILENAME}
/G4/Analysis/Filename ${HISTONAME}
/tracking/verbose 0
/gun/particle ${Particle}
/gun/direction ${xdirection} ${ydirection} ${zdirection}
/gun/position  ${xposition}  ${yposition}  ${zposition}
/gun/energy ${Energy} GeV
/run/beamOn ${NRofEvents}
EOF+

#/bin/more run_G4.mac
#cp  /grid/app/wenzel/Grid/G4-build-local/vis.mac .
#/grid/app/wenzel/Grid/G4-build-local/G4  /grid/app/wenzel/Grid/G4/gdml/crystalcal_bgo.gdml /tmp/run_G4.mac
#/bin/date


