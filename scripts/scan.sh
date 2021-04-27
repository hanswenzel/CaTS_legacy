#!/bin/sh
# 
# File:   scan.sh
# Author: wenzel
#
# Created on Nov 20, 2020, 10:12:41 PM
#
#export G4OPTICKS_DEBUG='--rngmax 10'
#time ./CaTS G4Opticks_50.gdml muon_noIO.mac >& 50_noIO_10.log
#time ./CaTS G4Opticks_100.gdml muon_noIO.mac >& 100_noIO_10.log
#time ./CaTS G4Opticks_5000.gdml muon_noIO.mac >& 5000_noIO_10.log
#time ./CaTS G4Opticks_10000.gdml muon_noIO.mac >& 10000_noIO_10.log
#time ./CaTS G4Opticks_50000.gdml muon_noIO.mac >& 50000_noIO_10.log
#export G4OPTICKS_DEBUG='--rngmax 10 --rtx 1'
#time ./CaTS G4Opticks_50.gdml muon_noIO.mac >& 50_noIO_10rtx.log
#time ./CaTS G4Opticks_100.gdml muon_noIO.mac >& 100_noIO_10rtx.log
#time ./CaTS G4Opticks_5000.gdml muon_noIO.mac >& 5000_noIO_10rtx.log
#time ./CaTS G4Opticks_10000.gdml muon_noIO.mac >& 10000_noIO_10rtx.log
#time ./CaTS G4Opticks_50000.gdml muon_noIO.mac >& 50000_noIO_10rtx.log
export G4OPTICKS_DEBUG='--rngmax 100'
#time ./CaTS G4Opticks_50.gdml muon_noIO.mac >& 50_noIO_100.log
#time ./CaTS G4Opticks_100.gdml muon_noIO.mac >& 100_noIO_100.log
time ./CaTS G4Opticks_5000.gdml muon_noIO.mac >& 5000_noIO_100.log
time ./CaTS G4Opticks_10000.gdml muon_noIO.mac >& 10000_noIO_100.log
time ./CaTS G4Opticks_50000.gdml muon_noIO.mac >& 50000_noIO_100.log
export G4OPTICKS_DEBUG='--rngmax 100 --rtx 1'
#time ./CaTS G4Opticks_50.gdml muon_noIO.mac >& 50_noIO_100rtx.log
#time ./CaTS G4Opticks_100.gdml muon_noIO.mac >& 100_noIO_100rtx.log
time ./CaTS G4Opticks_5000.gdml muon_noIO.mac >& 5000_noIO_100rtx.log
time ./CaTS G4Opticks_10000.gdml muon_noIO.mac >& 10000_noIO_100rtx.log
time ./CaTS G4Opticks_50000.gdml muon_noIO.mac >& 50000_noIO_100rtx.log