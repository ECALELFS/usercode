#!/bin/bash
cd /afs/cern.ch/work/l/lpernie/pi0/MVA/JoshMVA/CMSSW_5_3_0/src/
export SCRAM_ARCH=slc5_amd64_gcc462
eval `scramv1 runtime -sh`
cd UserCode/CITHZZ/LeptonScaleAndResolution/Electrons
echo 'root -l -q -b trainPi0.C+( "MVA_EtPi0_training.root","weights_Pi0_2/weight_Mediumtrain_EtPi0.root",100,2,"EB" )'
root -l -q -b trainPi0.C+'( "MVA_EtPi0_training.root","weights_Pi0_2/weight_Mediumtrain_EtPi0.root",100,2,"EB" )'
