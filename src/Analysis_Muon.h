// ---------------------------------------------------------------
//
//  AnalysisMuon - muon class used in the ZZllvv analysis
//
// ---------------------------------------------------------------


#ifndef Analysis_Muon_h
#define Analysis_Muon_h

#include "Analysis_Lepton.h"




class Analysis_Muon : public Analysis_Lepton {

 public:

  Analysis_Muon( float x=0., float y=0., float z=0., float t=0.) : Analysis_Lepton( x, y, z, t ) {};
  Analysis_Muon( double x=0., double y=0., double z=0., double t=0.) : Analysis_Lepton( x, y, z, t ) {};

  Analysis_Muon( const TLorentzVector &v) : Analysis_Lepton( v ) {};

  bool passedMuonID();
  bool isIsolated();
  bool passedVBTF();

  virtual float combinedIsoRel();

  // public data members:

  bool isGlobalMuonPromptTight;
  bool isAllTrackerMuon;

  int pixelHits;
  int trackerHits;

  int nMatchedStations;

  double dxy;
  double dz;

  // isolation:
  double sumPt03;
  double emEt03;
  double hadEt03;

};

#endif
