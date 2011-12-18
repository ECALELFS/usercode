// ---------------------------------------------------------------
//
//  AnalysisElectron - electron class used in the ZZllvv analysis
//
// ---------------------------------------------------------------


#ifndef Analysis_Electron_h
#define Analysis_Electron_h

#include "Analysis_Lepton.h"




class Analysis_Electron : public Analysis_Lepton {

 public:

  Analysis_Electron( float x=0., float y=0., float z=0., float t=0.) : Analysis_Lepton( x, y, z, t ) {};
  Analysis_Electron( double x=0., double y=0., double z=0., double t=0.) : Analysis_Lepton( x, y, z, t ) {};

  Analysis_Electron( const TLorentzVector &v) : Analysis_Lepton( v ) {};

  bool isIsolatedVBTF80();
  bool isIsolatedVBTF95();
  bool separatedIsoRel();//

  bool electronIDVBTF80();
  bool electronIDVBTF95();
  bool separatedIDVBTF80();//

  bool conversionRejectionVBTF80();
  bool conversionRejectionVBTF95();

  bool passedVBTF80();
  bool passedVBTF95();
  bool passedTrigger80();//

  double combinedIsoRel();


  // public data members:

  // isolation:
  double dr03TkSumPt;
  double dr03EcalRecHitSumEt;
  double dr03HcalTowerSumEt;

  // electron ID:
  double sigmaIetaIeta; 
  double deltaPhiAtVtx; 
  double deltaEtaAtVtx; 
  double hOverE; 

  // conversion rejection:
  int expInnerLayersGsfTrack;
  double convDist;
  double convDcot;

};

#endif



