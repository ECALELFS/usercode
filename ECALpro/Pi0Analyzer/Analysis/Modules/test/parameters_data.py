#Base Parameter

eosPath      = '/store/caf/user/lpernie'
queue        = '8nh' #option: cmscaf1nd
OnlyContCorr = False
isPi0        = True#!
nInter       = -1
useES        = 'True'
inputlist_n  = 'ALL_2012D_good.list' #2012D
dirname      = 'ANALYZ_RunD_Eta_02'
useES        = 'True'
Are_pi0      = False#!
ijobmax      = 1
nEventsPerJob= 1000000

#Cuts
ptpi0Cut    = 0.7 
s1CluCutEE  = 0.5
s1CluCut    = 0.35
ptCluCut    = 0.35
cuts4s9     = 0.7

#-----------------------------------------------------------------------------------
alphaTagRecord2='';alphaTag2='';alphaDB2=''
GeVTagRecord='';GeVTag='';GeVDB=''

######################################################################
# Now decomment the part that correspond to data you want to run on. #
######################################################################
##2012D
###/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions12/8TeV/Prompt/Cert_190456-208686_8TeV_PromptReco_Collisions12_JSON.txt
json_file ='goodrunlist_json2012D.txt'
HLTResults = 'True'
is2012 = True
is_2011 = 'True' #Just for the fit, put true 
useHLTFilter="True"
correctHits='True'
overWriteGlobalTag = True
globaltag='GR_P_V40::All'
if(Are_pi0): 
   esInputTag = "InputTag('hltAlCaPi0RecHitsFilterEEonly','pi0EcalRecHitsES', 'HLT')"
   ebInputTag = "InputTag('hltAlCaPi0EBUncalibrator','pi0EcalRecHitsEB','HLT')"
   eeInputTag = "InputTag('hltAlCaPi0EEUncalibrator','pi0EcalRecHitsEE','HLT')"
   HLTPaths='AlCa_EcalPi0*' 
else:
   esInputTag = "InputTag('hltAlCaEtaRecHitsFilterEEonly','etaEcalRecHitsES', 'HLT')"
   ebInputTag = "InputTag('hltAlCaEtaEBUncalibrator','etaEcalRecHitsEB','HLT')"
   eeInputTag = "InputTag('hltAlCaEtaEEUncalibrator','etaEcalRecHitsEE','HLT')"
   HLTPaths='AlCa_EcalEta*'
doEnenerScale='True'
doIC='True'
doLaserCorr="True"
GeVTagRecord='EcalADCToGeVConstantRcd'
GeVTag='EcalADCToGeVConstant_Bon_V20111129'
GeVDB='frontier://FrontierProd/CMS_COND_31X_ECAL'
laserTagRecord='EcalIntercalibConstantsRcd'
laserTag = 'EcalIntercalibConstants_V20120620_piZPhiSEtaScale2012_IOV2_AlphaStudies'
laserDB  = 'frontier://FrontierInt/CMS_COND_ECAL'
alphaTagRecord2='EcalLaserAlphasRcd'
alphaTag2='EcalLaserAlphas_EB_sic1_btcp152_EE_sic1_btcp116'
alphaDB2='frontier://FrontierInt/CMS_COND_ECAL'
alphaTagRecord='EcalLaserAPDPNRatiosRcd'
alphaTag='EcalLaserAPDPNRatios_20130124_447_p1_v2'
alphaDB='frontier://FrontierProd/CMS_COND_42X_ECAL_LAS'

##############
#2012C
###/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions12/8TeV/Reprocessing/Cert_190456-196531_8TeV_13Jul2012ReReco_Collisions12_JSON_v2.txt
#json_file ='goodrunlist_json2012C.txt'
#HLTResults = 'True'
#is2012 = True
#is_2011 = 'True' #Just for the fit, put true 
#useHLTFilter="True"
#correctHits='True'
#overWriteGlobalTag = True
#globaltag='GR_P_V42::All'
#ebInputTag = "InputTag('hltAlCaPi0EBUncalibrator','pi0EcalRecHitsEB','HLT')"
#eeInputTag = "InputTag('hltAlCaPi0EEUncalibrator','pi0EcalRecHitsEE','HLT')"
#esInputTag = "InputTag('hltAlCaPi0RecHitsFilterEEonly','pi0EcalRecHitsES', 'HLT')"
#doEnenerScale='True'
#doIC='True'
#doLaserCorr="True"
#laserTagRecord='EcalIntercalibConstantsRcd'
#laserTag = 'EcalIntercalibConstants_V20120620_piZPhiSEtaScale2012_IOV2_AlphaStudies'
#laserDB  = 'frontier://FrontierInt/CMS_COND_ECAL'
#alphaTagRecord='EcalLaserAPDPNRatiosRcd'
#alphaTag='EcalLaserAPDPNRatios_20121020_447_p1_v2'
#alphaDB='frontier://FrontierProd/CMS_COND_42X_ECAL_LAS'
#HLTPaths='AlCa_EcalPi0*' 

##############
##2012B
###/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions12/8TeV/Prompt/Cert_190456-208357_8TeV_PromptReco_Collisions12_JSON.txt
#json_file ='goodrunlist_json2012C.txt'
#HLTResults = 'True'
#is2012 = True
#is_2011 = 'True' #Just for the fit, put true 
#useHLTFilter="True"
#correctHits='True'
#overWriteGlobalTag = True
#globaltag='FT_R_53_V6::All'
#ebInputTag = "InputTag('hltAlCaPi0EBUncalibrator','pi0EcalRecHitsEB','HLT')"
#eeInputTag = "InputTag('hltAlCaPi0EEUncalibrator','pi0EcalRecHitsEE','HLT')"
#esInputTag = "InputTag('hltAlCaPi0RecHitsFilterEEonly','pi0EcalRecHitsES', 'HLT')"
#doEnenerScale='True'
#doIC='True'
#doLaserCorr="True"
#laserTagRecord='EcalIntercalibConstantsRcd'
#laserTag = 'EcalIntercalibConstants_V20120620_piZPhiSEtaScale2012_IOV2_AlphaStudies'
#laserDB  = 'frontier://FrontierInt/CMS_COND_ECAL'
#alphaTagRecord='EcalLaserAPDPNRatiosRcd'
#alphaTag='EcalLaserAPDPNRatios_20121020_447_p1_v2'
#alphaDB='frontier://FrontierProd/CMS_COND_42X_ECAL_LAS'
#HLTPaths='AlCa_EcalPi0*'


##############
##2011 AlcaRAW
###/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions11/7TeV/Prompt/Cert_160404-180252_7TeV_PromptReco_Collisions11_JSON.txt
#json_file ='goodrunlist_json2011.txt'
#HLTResults = 'False'
#is_2011 = 'True'
#is2012 = False
#overWriteGlobalTag = False
#doEnenerScale='False'
#doIC='False'
#doLaserCorr='True'
#ebInputTag = "InputTag('hltAlCaPi0RecHitsFilter','pi0EcalRecHitsEB', 'HLT')"
#eeInputTag = "InputTag('hltAlCaPi0RecHitsFilter','pi0EcalRecHitsEE', 'HLT')"
#esInputTag = "InputTag('hltAlCaPi0RecHitsFilter','pi0EcalRecHitsES', 'HLT')"
#useHLTFilter = 'True'
#correctHits = 'True'
#globaltag='GR_R_42_V24::All'
#laserTagRecord='EcalLaserAPDPNRatiosRcd'
#alphaTagRecord='EcalLaserAlphasRcd'
#laserTag            = 'EcalLaserAPDPNRatios_data_20120814_2011-2012_v3'
#laserDB             = 'frontier://FrontierProd/CMS_COND_42X_ECAL_LAS'
#alphaTag            = 'EcalLaserAlphas_EB_sic_btcp152_EE_sic1_btcp116'
#alphaDB             = 'frontier://FrontierPrep/CMS_COND_ECAL'
#HLTPaths='AlCa_EcalPi0_*'

##############

##2010 AlcaRECO
###/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions10/7TeV/StreamExpress/goodrunlist_json.txt
#json_file = 'goodrunlist_json2010.txt'
#HLTResults = 'False'
#is_2011 = 'False'
#is2012 = False
#overWriteGlobalTag = False
#doEnenerScale='False'
#doIC='False'
#doLaserCorr="True"
#ebInputTag = "InputTag('ecalPi0Corrected','pi0EcalRecHitsEB')"
#eeInputTag = "InputTag('ecalPi0Corrected','pi0EcalRecHitsEE')"
#esInputTag = "InputTag('hltAlCaPi0RecHitsFilter','pi0EcalRecHitsES')"
#useHLTFilter = "False"
#correctHits = 'False'
#globaltag='GR_R_42_V21B::All'
#laserTagRecord='EcalLaserAPDPNRatiosRcd'
#laserTag = 'EcalLaserAPDPNRatios_data_20111122_158851_180363'
#laserDB  = 'frontier://FrontierPrep/CMS_COND_ECAL'
#alphaTagRecord='EcalLaserAlphasRcd'
#alphaTag = 'EcalLaserAlphas_lto420-620_progr_data_20111122'
#alphaDB  = 'frontier://FrontierPrep/CMS_COND_ECAL'
#HLTPaths='AlCa_EcalPi0_*' 
