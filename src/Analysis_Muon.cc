#include "Analysis_Muon.h"



bool Analysis_Muon::passedMuonID() {

  bool passed = ( isGlobalMuonPromptTight && isAllTrackerMuon 
                && pixelHits>0 && trackerHits>10 
                && nMatchedStations>=2
                && (dxy<0.02) && (dz<1.) );

  return passed;

}



bool Analysis_Muon::isIsolated() {

  bool isIsolated = this->combinedIsoRel() < 0.15;

  return isIsolated;

}




bool Analysis_Muon::passedVBTF() {

  bool isIsolated = this->isIsolated();
  bool passedMuonID = this->passedMuonID();

  return ( isIsolated && passedMuonID );

}


float Analysis_Muon::combinedIsoRel() {

 return (sumPt03 + emEt03 + hadEt03)/this->Pt();

}
