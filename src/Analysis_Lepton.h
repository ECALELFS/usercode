// -------------------------------------------------------------
//
//  AnalysisLepton - lepton class used in the ZZllvv analysis
//
// -------------------------------------------------------------

#ifndef Analysis_Lepton_h
#define Analysis_Lepton_h

#include "TLorentzVector.h"



class Analysis_Lepton : public TLorentzVector {

 public:

  Analysis_Lepton( float x=0., float y=0., float z=0., float t=0.) : TLorentzVector( x, y, z, t ) {
    charge=0;
  }

  Analysis_Lepton( const TLorentzVector &v) : TLorentzVector( v ) {
    charge=0;
  }

  int charge;

};

#endif
