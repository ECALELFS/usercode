#include <stdlib.h>
#include <iostream>
#include <string>
#include "CommonTools/DrawBase.h"
#include "CommonTools/fitTools.h"



void draw_vs_pt_plots( DrawBase* db, int nPtBins, Double_t* ptBins, const std::string& histoName, const std::string& axisName, const std::string& units="", const std::string& instanceName="Entries", bool log=false );


int main(int argc, char* argv[]) {

  if(  argc != 1 ) {
    std::cout << "USAGE: ./drawHWWlvjj [(string) selectionType] [(string) leptType=\"ALL\"]" << std::endl;
    exit(23);
  }

  //std::string selType(argv[1]);

 // std::string zJets_dataset = "ZJets_alpgen";

  std::string leptType = "ALL";
  //if( argc==3 ) {
  //  std::string leptType_str(argv[2]);
  //  leptType = leptType_str;
 // }

  DrawBase* db = new DrawBase("HWWlvjj");
  db->set_pdf_aussi((bool)false);

  std::string outputdir_str = "PLOT";
  //if( leptType!="ALL" ) outputdir_str += "_" + leptType;
  //@@outputdir_str += "_" + leptType;
  db->set_outputdir(outputdir_str);

  //--------- Monte Carlo
  TFile* mcBkg_DY = TFile::Open("Output/MC/histosfiles_DYJetsToLL.root");
  db->add_mcFile(mcBkg_DY, "DY", " DY ", 39);
  /*TFile* mcBkg_WJets = TFile::Open("Output/MC/histosfiles_WJetsToLNu.root");
  db->add_mcFile(mcBkg_WJets, "WJets", "W + Jets", 38);
  TFile* mcBkg_TT = TFile::Open("Output/MC/histosfiles_TTJets.root");
  db->add_mcFile(mcBkg_TT, "tt", " tt ", 30);

  TFile* mcBkg_WW = TFile::Open("Output/MC/histosfiles_WW.root");
  db->add_mcFile(mcBkg_WW, "WW", " WW ", 7);
  TFile* mcBkg_WZ = TFile::Open("Output/MC/histosfiles_WZ.root");
  db->add_mcFile(mcBkg_WZ, "WZ", " WZ ", 8);
  TFile* mcBkg_ZZ = TFile::Open("Output/MC/histosfiles_ZZ.root");
  db->add_mcFile(mcBkg_ZZ, "ZZ", " ZZ ", 2);
*/
  //db->set_lumiNormalization( 1000. ); //1 fb-1 li somma e norm alla lumi
  //db->set_noStack( false);//(bool)true );
  //db->set_shapeNormalization();

              // MET with different VTX
  std::vector< HistoAndName > MET_in_vtx;
  HistoAndName h_in_MET1vtx;
  h_in_MET1vtx.histoName = "h_in_MET1vtx";
  h_in_MET1vtx.legendName = "1 vertices";
  MET_in_vtx.push_back( h_in_MET1vtx );
  HistoAndName h_in_MET8vtx;
  h_in_MET8vtx.histoName = "h_in_MET8vtx";
  h_in_MET8vtx.legendName = "8 vertices";
  MET_in_vtx.push_back( h_in_MET8vtx );
  HistoAndName h_in_MET18vtx;
  h_in_MET18vtx.histoName = "h_in_MET18vtx";
  h_in_MET18vtx.legendName = "12 vertices";
  MET_in_vtx.push_back( h_in_MET18vtx ); 
  db->compareDifferentHistos( MET_in_vtx, "MET_in_vtx", "MET with different vertex [GeV/c]", "");

  std::vector< HistoAndName > METx_vtx;
  HistoAndName h_METx1vtx;
  h_METx1vtx.histoName = "h_in_METx1vtx";
  h_METx1vtx.legendName = "1 vertices";
  METx_vtx.push_back( h_METx1vtx );
  HistoAndName h_METx8vtx;
  h_METx8vtx.histoName = "h_in_METx8vtx";
  h_METx8vtx.legendName = "8 vertices";
  METx_vtx.push_back( h_METx8vtx );
  HistoAndName h_METx18vtx;
  h_METx18vtx.histoName = "h_in_METx18vtx";
  h_METx18vtx.legendName = "18 vertices";
  METx_vtx.push_back( h_METx18vtx );
  db->compareDifferentHistos( METx_vtx, "METx_vtx", "MET_x with different vertex [GeV/c]", "");

  std::vector< HistoAndName > METy_vtx;
  HistoAndName h_METy1vtx;
  h_METy1vtx.histoName = "h_in_METy1vtx";
  h_METy1vtx.legendName = "1 vertices";
  METy_vtx.push_back( h_METy1vtx );
  HistoAndName h_METy8vtx;
  h_METy8vtx.histoName = "h_in_METy8vtx";
  h_METy8vtx.legendName = "8 vertices";
  METy_vtx.push_back( h_METy8vtx );
  HistoAndName h_METy18vtx;
  h_METy18vtx.histoName = "h_in_METy18vtx";
  h_METy18vtx.legendName = "18 vertices";
  METy_vtx.push_back( h_METy18vtx );
  db->compareDifferentHistos( METy_vtx, "METy_vtx", "MET_y with different vertex [GeV/c]", "");

  std::vector< HistoAndName > METx_rho;
  HistoAndName h_in_METx2rho;
  h_in_METx2rho.histoName = "h_in_METx2rho";
  h_in_METx2rho.legendName = "Rho < 2";
  METx_rho.push_back( h_in_METx2rho );
  HistoAndName h_in_METx8rho;
  h_in_METx8rho.histoName = "h_in_METx8rho";
  h_in_METx8rho.legendName = "6 < Rho < 8";
  METx_rho.push_back( h_in_METx8rho );
  HistoAndName h_in_METx14rho;
  h_in_METx14rho.histoName = "h_in_METx14rho";
  h_in_METx14rho.legendName = "12 < Rho < 14";
  METx_rho.push_back( h_in_METx14rho );
  db->compareDifferentHistos( METx_rho, "METx_rho", "MET_x with different Rho [GeV/c]", "");

  std::vector< HistoAndName > METy_rho;
  HistoAndName h_in_METy2rho;
  h_in_METy2rho.histoName = "h_in_METy2rho";
  h_in_METy2rho.legendName = "Rho < 2";
  METy_rho.push_back( h_in_METy2rho );
  HistoAndName h_in_METy8rho;
  h_in_METy8rho.histoName = "h_in_METy8rho";
  h_in_METy8rho.legendName = "6 < Rho < 8";
  METy_rho.push_back( h_in_METy8rho );
  HistoAndName h_in_METy14rho;
  h_in_METy14rho.histoName = "h_in_METy14rho";
  h_in_METy14rho.legendName = "12 < Rho < 14";
  METy_rho.push_back( h_in_METy14rho );
  db->compareDifferentHistos( METy_rho, "METy_rho", "MET_y with different Rho [GeV/c]", "");

  db->set_mcMarkers("false");
  db->set_markerSize(1);
  db->drawHisto( "h_RMS_vtx", "N vertex", "", "RMS on MET_x", true);

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
