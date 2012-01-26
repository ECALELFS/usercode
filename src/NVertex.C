#include <stdlib.h>
#include "TFile.h"
#include "TTree.h"
#include <iostream>
#include <cstring>
#include <string>
#include <TStyle.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TF1.h>
#include <TChain.h>
#include <TMath.h>
#include <TLegend.h>

TCanvas* NVertex(){

  gStyle->SetOptStat(1111111);
  gStyle->SetPalette(1);
  gStyle->SetOptFit(111110);
  gStyle->SetOptFile(1);
  gStyle->SetMarkerStyle(20);
  gStyle->SetMarkerSize(.3);
  gStyle->SetMarkerColor(1);
  gStyle->SetFillColor(0);

  // HISTO & Canvas
  TCanvas* myc1 = new TCanvas("myc1", "myc1", 600, 600);
 
  TH1F* h_nvtx_MC = new TH1F("h_nvtx_MC","MC vtx",20, 0., 20.);
  h_nvtx_MC->Sumw2();
  TH1F* h_nvtx_Data = new TH1F("h_nvtx_Data","Data vtx",20, 0., 20.);
  h_nvtx_Data->Sumw2();
  TH1F* h_nvtx_Ratio = new TH1F("h_nvtx_Ratio","Data vtx",20, 0., 20.);
  h_nvtx_Ratio->Sumw2();
  // TChain

  TChain ch("Tree_NVertex");
  ch.Add("Output/MC/histosfiles_DYJetsToLL.root");
  ch.Add("Output/MC/histosfiles_SingleT_s.root");
  ch.Add("Output/MC/histosfiles_SingleT_t.root");
  ch.Add("Output/MC/histosfiles_SingleT_tW.root");
  ch.Add("Output/MC/histosfiles_SingleTbar_s.root");
  ch.Add("Output/MC/histosfiles_SingleTbar_t.root");
  ch.Add("Output/MC/histosfiles_SingleTbar_tW.root");
  ch.Add("Output/MC/histosfiles_TTJets.root");
  ch.Add("Output/MC/histosfiles_WJetsToLNu.root");
  ch.Add("Output/MC/histosfiles_WW.root");
  ch.Add("Output/MC/histosfiles_WZ.root");
  ch.Add("Output/MC/histosfiles_ZZTot.root");

  TChain ch2("Tree_NVertex");
  ch2.Add("Output/Data/histosDoubleData.root");

  float Nvtx, finWeight;
  ch.SetBranchAddress("Nvtx", &Nvtx);
  ch.SetBranchAddress("finWeight", &finWeight);

  float Nvtx_dat, finWeight_dat;
  ch2.SetBranchAddress("Nvtx", &Nvtx_dat);
  ch2.SetBranchAddress("finWeight", &finWeight_dat);

  for( int iEntry=0; iEntry<ch.GetEntries() ; iEntry++ ){
   ch.GetEntry(iEntry);
   h_nvtx_MC->Fill( Nvtx, finWeight*4615); //Per Lumi
  }

  for( int iEntry=0; iEntry<ch2.GetEntries() ; iEntry++ ){
   ch2.GetEntry(iEntry);
   h_nvtx_Data->Fill( Nvtx_dat, finWeight_dat);
  }

Float_t MC_vtx, Data_vtx; 
  for( int i=1; i<= h_nvtx_MC->GetNbinsX(); i++ ){
   MC_vtx = h_nvtx_MC->GetBinContent(i);
   Data_vtx = h_nvtx_Data->GetBinContent(i);
   h_nvtx_Ratio->SetBinContent(i,Data_vtx/MC_vtx);
   cout<<i<<" MC: "<<MC_vtx<<" Data: "<<Data_vtx<<" Ratio: "<<Data_vtx/MC_vtx<<endl;
  }

myc1->cd();
return myc1;
} //End
