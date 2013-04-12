#!/bin/bash

#cd /afs/cern.ch/work/l/lpernie/ECALpro/ETA_TRY/CMSSW_5_3_6/src/
#export SCRAM_ARCH=slc5_amd64_gcc462
#eval `scramv1 runtime -sh`
#Analysis/Modules/test
#echo 'python /afs/cern.ch/work/l/lpernie/ECALpro/ETA_TRY/CMSSW_5_3_6/src/Analysis/Modules/test/RunOnBatch_data.py'
#python /afs/cern.ch/work/l/lpernie/ECALpro/ETA_TRY/CMSSW_5_3_6/src/Analysis/Modules/test/RunOnBatch_data.py

cd /afs/cern.ch/work/l/lpernie/ECALpro/ETA_TRY/CMSSW_4_2_4/src/
export SCRAM_ARCH=slc5_amd64_gcc434
eval `scramv1 runtime -sh`
cd Analysis/Modules/test
echo 'python /afs/cern.ch/work/l/lpernie/ECALpro/ETA_TRY/CMSSW_4_2_4/src/Analysis/Modules/test/RunOnBatch.py'
python /afs/cern.ch/work/l/lpernie/ECALpro/ETA_TRY/CMSSW_4_2_4/src/Analysis/Modules/test/RunOnBatch.py
