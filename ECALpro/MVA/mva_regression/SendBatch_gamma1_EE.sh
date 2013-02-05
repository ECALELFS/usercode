#!/bin/bash
cd /afs/cern.ch/work/l/lpernie/pi0/MVA/JoshMVA/CMSSW_5_3_0/src/
export SCRAM_ARCH=slc5_amd64_gcc462
eval `scramv1 runtime -sh`
cd UserCode/CITHZZ/LeptonScaleAndResolution/Electrons
echo 'root -l -q -b trainPi0.C+( "MVA_ES_training.root","weights_Pi0_1/weight_Mediumtrain_ESmore2.root",100,1,"EE" )'
root -l -q -b trainPi0.C+'( "MVA_ES_training.root","weights_Pi0_1/weight_Mediumtrain_ESmore2.root",100,1, "EE" )'
