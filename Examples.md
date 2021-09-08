# Examples
Here we provide examples for running CaTS. The examples consist of a gdml file to define the detector configuration. 

## homogeneous Crystal Calorimeter
Her we just read out the energy deposited in a huge Crystal.

    time ./CaTS -g homogeneous_pbwo_crystalcal.gdml  -pl 'FTFP_BERT'  -m pip_IO_Calo.mac
    time ./readCalorimeterHits CaloHits_Run0.root CaloHistos.root CalorimeterVolume

![alt text](https://github.com/hanswenzel/CaTS/blob/master/images/CaloHistos.png)

## Dual Read out Crystal Calorimeter

Here in addtion to the deposited energy in the calorimeter cell we readout the number of Cerenkov photons that have been produced.

    ./CaTS -g crystalcal_pbwo.gdml -pl 'FTFP_BERT+OPTICAL'  -m pip_IO_DR.mac 
    ./readDRCalorimeterHits  DRCaloHits_Run0.root DRCaloHhstos.root CalorimeterVolume



