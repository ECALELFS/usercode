#include <stdlib.h>
#include <iostream>
#include <string>
#include "CommonTools/DrawBase.h"
#include "CommonTools/fitTools.h"



void draw_vs_pt_plots( DrawBase* db, int nPtBins, Double_t* ptBins, const std::string& histoName, const std::string& axisName, const std::string& units="", const std::string& instanceName="Entries", bool log=false );


int main(int argc, char* argv[]) {

  if(  argc != 1 ) {
    std::cout << "USAGE: ./drawHWWlvjj" << std::endl;
    exit(23);
  }

  //std::string selType(argv[1]);

 // std::string zJets_dataset = "ZJets_alpgen";

  std::string leptType = "ALL";
  //if( argc==3 ) {
  //  std::string leptType_str(argv[2]);
  //  leptType = leptType_str;
  //}

  DrawBase* db = new DrawBase("HWWlvjj");
  db->set_pdf_aussi((bool)false);

  std::string outputdir_str = "PLOT_Data";
  //if( leptType!="ALL" ) outputdir_str += "_" + leptType;
  //@@ outputdir_str += "_" + leptType;
  db->set_outputdir(outputdir_str);

  //--------- Monte Carlo
  TFile* mcBkg_DY = TFile::Open("Output/MC/histosDYJetsToLL.root");
  db->add_mcFile(mcBkg_DY, "DY", " DY ", 39);
  TFile* mcBkg_WJets = TFile::Open("Output/MC/histosWJetsToLNu.root");
  db->add_mcFile(mcBkg_WJets, "WJets", "W + Jets", 38);
  TFile* mcBkg_TT = TFile::Open("Output/MC/histosTTJets.root");
  db->add_mcFile(mcBkg_TT, "tt", " tt ", 30);

  TFile* mcBkg_WW = TFile::Open("Output/MC/histosWW.root");
  db->add_mcFile(mcBkg_WW, "WW", " WW ", 7);
  TFile* mcBkg_ZZ = TFile::Open("Output/MC/histosZZ.root");
  db->add_mcFile(mcBkg_ZZ, "ZZ", " ZZ ", 2);
  TFile* mcBkg_WZ = TFile::Open("Output/MC/histosWZ.root");
  db->add_mcFile(mcBkg_WZ, "WZ", " WZ ", 8);

  //--------- DATA
  //TFile* Data_ = TFile::Open("Output/Data/histosDoubleElectrons.root");
  TFile* Data_ = TFile::Open("Output/Data/histosDoubleData.root");
  db->add_dataFile(Data_, "Data", " Data ", 1);

  db->set_lumiNormalization( 4615. ); //1 fb-1 li somma e norm alla lumi
  //db->set_noStack( false);//(bool)true );
  //db->set_shapeNormalization();
  
// HISTO ee
  db->drawHisto( "hee_in_llMass", "ee Invariant mass", "GeV/c^{2}", "Events", true);
  db->drawHisto( "hee_in_llPt", "Di-lepton Transverse Momentum", "GeV/c", "Events", true);
  db->drawHisto( "hee_in_l1Pt", "Lead. lepton Transverse Momentum", "GeV/c", "Events", true);
  db->drawHisto( "hee_in_l2Pt", "SubLead. Lepton Transverse Momentum", "GeV/c", "Events", true);
  db->drawHisto( "hee_in_MET1Pt", "Missing Energy", "GeV/c", "Events", true);
  db->drawHisto( "hee_in_l1Eta", "Lead. lepton #eta", "", "Events", true);
  db->drawHisto( "hee_in_l2Eta", "SubLead. lepton #eta", "", "Events", true);
  db->drawHisto( "hee_in_rho", "Rho density", "GeV/Area", "Events", true);

  db->drawHisto( "hee_llMass", "ee Invariant mass", "GeV/c^{2}", "Events", true);
  db->drawHisto( "hee_llPt", "Di-lepton Transverse Momentum", "GeV/c", "Events", true);
  db->drawHisto( "hee_l1Pt", "Lead. lepton Transverse Momentum", "GeV/c", "Events", true);
  db->drawHisto( "hee_l2Pt", "SubLead. Lepton Transverse Momentum", "GeV/c", "Events", true);
  db->drawHisto( "hee_MET1Pt", "Missing Energy", "GeV/c", "Events", true);
  db->drawHisto( "hee_l1Eta", "Lead. lepton #eta", "", "Events", true);
  db->drawHisto( "hee_l2Eta", "SubLead. lepton #eta", "", "Events", true);
  db->drawHisto( "hee_rho", "Rho density", "GeV/Area", "Events", true);

// HISTO mumu
  db->drawHisto( "hmumu_in_llMass", "mumu Invariant mass", "GeV/c^{2}", "Events", true);
  db->drawHisto( "hmumu_in_llPt", "Di-lepton Transverse Momentum", "GeV/c", "Events", true);
  db->drawHisto( "hmumu_in_l1Pt", "Lead. lepton Transverse Momentum", "GeV/c", "Events", true);
  db->drawHisto( "hmumu_in_l2Pt", "SubLead. Lepton Transverse Momentum", "GeV/c", "Events", true);
  db->drawHisto( "hmumu_in_MET1Pt", "Missing Energy", "GeV/c", "Events", true);
  db->drawHisto( "hmumu_in_l1Eta", "Lead. lepton #eta", "", "Events", true);
  db->drawHisto( "hmumu_in_l2Eta", "SubLead. lepton #eta", "", "Events", true);
  db->drawHisto( "hmumu_in_rho", "Rho density", "GeV/Area", "Events", true);
 
  db->drawHisto( "hmumu_llMass", "mumu Invariant mass", "GeV/c^{2}", "Events", true);
  db->drawHisto( "hmumu_llPt", "Di-lepton Transverse Momentum", "GeV/c", "Events", true);
  db->drawHisto( "hmumu_l1Pt", "Lead. lepton Transverse Momentum", "GeV/c", "Events", true);
  db->drawHisto( "hmumu_l2Pt", "SubLead. Lepton Transverse Momentum", "GeV/c", "Events", true);
  db->drawHisto( "hmumu_MET1Pt", "Missing Energy", "GeV/c", "Events", true);
  db->drawHisto( "hmumu_l1Eta", "Lead. lepton #eta", "", "Events", true);
  db->drawHisto( "hmumu_l2Eta", "SubLead. lepton #eta", "", "Events", true);
  db->drawHisto( "hmumu_rho", "Rho density", "GeV/Area", "Events", true);

  delete db;
 
  db = 0;

  return 0;

}  


void draw_vs_pt_plots( DrawBase* db, int nPtBins, Double_t* ptBins, const std::string& histoName, const std::string& axisName, const std::string& units, const std::string& instanceName, bool log ) {

  for( int iPtBin=0; iPtBin<nPtBins-1; ++iPtBin ) {

    Double_t ptMin = ptBins[iPtBin];
    Double_t ptMax = ptBins[iPtBin+1];

    char histoName_thisBin[250];
    sprintf( histoName_thisBin, "%s_pt_%.0lf_%.0lf", histoName.c_str(), ptMin, ptMax);

    std::string histoName_thisBin_str(histoName_thisBin);

    char legendTitle[200];
    sprintf( legendTitle, "%.0lf < pt < %.0lf GeV/c", ptMin, ptMax);
    std::string legendTitle_str(legendTitle);
    db->set_legendTitle(legendTitle_str);

    db->drawHisto( histoName_thisBin_str, axisName, units, instanceName, log );

  } //for bins

} //draw_vs_pt_plots

// To Have this Label without this code
//  TPaveText* cmsLabel = db->get_labelCMS();
//  TPaveText* sqrtLabel = db->get_labelSqrt();
//  cmsLabel->Draw("same"); 
//  sqrtLabel->Draw("same");
