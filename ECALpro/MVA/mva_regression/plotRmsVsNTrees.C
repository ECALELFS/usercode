#include <TROOT.h>                  // access to gROOT, entry point to ROOT system
#include <TSystem.h>                // interface to OS
#include <TStyle.h>
#include <TFile.h>                  // file handle class
#include <TTree.h>                  // class to access ntuples
#include <TBranch.h>                // class to access branches in TTree
#include <TClonesArray.h>           // ROOT array class
#include <TCanvas.h>                // class for drawing
#include <TH1F.h>                   // 1D histograms
#include <TH2F.h>                   // 2D histograms
#include <TString.h>
#include <TGraphAsymmErrors.h>     
#include <TGraphErrors.h>
#include <TBenchmark.h>             // class to track macro running statistics
#include <TLorentzVector.h>         // 4-vector class
#include <TVector3.h>               // 3D vector class
#include <vector>                   // STL vector class
#include <iostream>                 // standard I/O
#include <iomanip>                  // functions to format standard I/O
#include <fstream>                  // functions for file I/O
#include <string>                   // C++ string class
#include <sstream>                  // class for parsing strings
#include "TLegend.h"
#include "TEfficiency.h"
#include "TMath.h"

void plotRmsVsNTrees(string inputDirectory, int nTreesMin, int nFiles, string option){

  Float_t rms_training[nFiles];
  Float_t rmsError_training[nFiles];
  Float_t numberOfTrees[nFiles];
 

  Float_t rms_testing[nFiles];
  Float_t rmsError_testing[nFiles];
 
  Float_t underflow_training[nFiles]; 
  Float_t overflow_training[nFiles]; 

  Float_t underflow_testing[nFiles]; 
  Float_t overflow_testing[nFiles]; 


  int j=0;

  Double_t lowEdge=0;   
  Double_t upperEdge=1;
  stringstream lowEdgeString;
  stringstream upperEdgeString;

  for (int i = nTreesMin;i<=nTreesMin*pow(2,nFiles-1);i=i*2) {
    
    TString fileString=inputDirectory+"ElectronEnergyRegression_";
    TString trainingString=fileString+"training_"+option+"_nTrees_";
    trainingString+=i;
    trainingString+=".root";
    //    cout<<trainingString<<endl;
    TFile* trainingFile=TFile::Open(trainingString);
    TH1F* trainingHisto=(TH1F*)trainingFile->Get("mvaHisto_eb");

    if(j==0){
      lowEdge=trainingHisto->GetXaxis()->GetBinLowEdge(trainingHisto->GetXaxis()->GetFirst());
      upperEdge=trainingHisto->GetXaxis()->GetBinUpEdge(trainingHisto->GetXaxis()->GetLast());
      lowEdgeString<<setprecision(1)<<lowEdge;
      upperEdgeString<<setprecision(1)<<upperEdge;
    }

    rms_training[j]=trainingHisto->GetRMS();
    rmsError_training[j]=trainingHisto->GetRMSError();
    numberOfTrees[j]=i;

    underflow_training[j]=trainingHisto->GetBinContent(0)/trainingHisto->GetEntries();
    overflow_training[j]=trainingHisto->GetBinContent(trainingHisto->GetNbinsX()+1)/trainingHisto->GetEntries();

    TString testingString=fileString+"testing_"+option+"_nTrees_";
    testingString+=i;
    testingString+=".root";
    //    cout<<testingString<<endl;
    TFile* testingFile=TFile::Open(testingString);
    TH1F* testingHisto=(TH1F*)testingFile->Get("mvaHisto_eb");

    rms_testing[j]=testingHisto->GetRMS();
    rmsError_testing[j]=testingHisto->GetRMSError();
    
    underflow_testing[j]=testingHisto->GetBinContent(0)/testingHisto->GetEntries();
    overflow_testing[j]=testingHisto->GetBinContent(testingHisto->GetNbinsX()+1)/testingHisto->GetEntries();

    j++;
    //    cout<<rms_testing[j]<<" "<<rmsError_testing[j]<<" "<<numberOfTrees_testing[j]<<endl;

  }

  TGraphErrors* RMSvsnTrees_training_eb=new TGraphErrors(nFiles,numberOfTrees,rms_training,0,rmsError_training);
  RMSvsnTrees_training_eb->SetName("RMSvsnTrees_training_eb");
  RMSvsnTrees_training_eb->SetTitle("RMSvsnTrees_training_eb");
  RMSvsnTrees_training_eb->GetXaxis()->SetTitle("nTrees");
  RMSvsnTrees_training_eb->GetYaxis()->SetTitle("RMS");
  RMSvsnTrees_training_eb->SetMarkerStyle(20);

  TGraphErrors* RMSvsnTrees_testing_eb=new TGraphErrors(nFiles,numberOfTrees,rms_testing,0,rmsError_testing);
  RMSvsnTrees_testing_eb->SetName("RMSvsnTrees_testing_eb");
  RMSvsnTrees_testing_eb->SetTitle("RMSvsnTrees_testing_eb");
  RMSvsnTrees_testing_eb->GetXaxis()->SetTitle("nTrees");
  RMSvsnTrees_testing_eb->GetYaxis()->SetTitle("RMS");
  RMSvsnTrees_testing_eb->SetMarkerStyle(20);
  RMSvsnTrees_testing_eb->SetMarkerColor(kRed);
  RMSvsnTrees_testing_eb->SetLineColor(kRed);

  TGraphErrors* UnderflowvsnTrees_training_eb=new TGraphErrors(nFiles,numberOfTrees,underflow_training,0,0);
  TString binningString="range_";
  binningString+=lowEdgeString.str();
  binningString+="_";
  binningString+=upperEdgeString.str();


  UnderflowvsnTrees_training_eb->SetName("UnderflowvsnTrees_training_eb");
  UnderflowvsnTrees_training_eb->SetTitle("UnderflowvsnTrees_training_eb"+binningString);
  UnderflowvsnTrees_training_eb->GetXaxis()->SetTitle("nTrees");
  UnderflowvsnTrees_training_eb->GetYaxis()->SetTitle("Underflows");
  UnderflowvsnTrees_training_eb->SetMarkerStyle(20);

  TGraphErrors* UnderflowvsnTrees_testing_eb=new TGraphErrors(nFiles,numberOfTrees,underflow_testing,0,0);
  UnderflowvsnTrees_testing_eb->SetName("UnderflowvsnTrees_testing_eb");
  UnderflowvsnTrees_testing_eb->SetTitle("UnderflowvsnTrees_testing_eb");
  UnderflowvsnTrees_testing_eb->GetXaxis()->SetTitle("nTrees");
  UnderflowvsnTrees_testing_eb->GetYaxis()->SetTitle("Underflows");
  UnderflowvsnTrees_testing_eb->SetMarkerStyle(20);
  UnderflowvsnTrees_testing_eb->SetMarkerColor(kRed);
  UnderflowvsnTrees_testing_eb->SetLineColor(kRed);

  TGraphErrors* OverflowvsnTrees_training_eb=new TGraphErrors(nFiles,numberOfTrees,overflow_training,0,0);
  OverflowvsnTrees_training_eb->SetName("OverflowvsnTrees_training_eb");
  OverflowvsnTrees_training_eb->SetTitle("OverflowvsnTrees_training_eb"+binningString);
  OverflowvsnTrees_training_eb->GetXaxis()->SetTitle("nTrees");
  OverflowvsnTrees_training_eb->GetYaxis()->SetTitle("Overflows");
  OverflowvsnTrees_training_eb->SetMarkerStyle(20);

  TGraphErrors* OverflowvsnTrees_testing_eb=new TGraphErrors(nFiles,numberOfTrees,overflow_testing,0,0);
  OverflowvsnTrees_testing_eb->SetName("OverflowvsnTrees_testing_eb");
  OverflowvsnTrees_testing_eb->SetTitle("OverflowvsnTrees_testing_eb");
  OverflowvsnTrees_testing_eb->GetXaxis()->SetTitle("nTrees");
  OverflowvsnTrees_testing_eb->GetYaxis()->SetTitle("Overflows");
  OverflowvsnTrees_testing_eb->SetMarkerStyle(20);
  OverflowvsnTrees_testing_eb->SetMarkerColor(kRed);
  OverflowvsnTrees_testing_eb->SetLineColor(kRed);



  TLegend* leg= new TLegend(0.1,0.7,0.4,0.9);
  leg->AddEntry(RMSvsnTrees_training_eb,"training","P");
  leg->AddEntry(RMSvsnTrees_testing_eb,"testing","P");

  TCanvas* RMSCanvas=new TCanvas("RMSCanvas","RMSCanvas");

  RMSvsnTrees_training_eb->Draw("ap");
  RMSvsnTrees_training_eb->GetYaxis()->SetRangeUser(rms_training[nFiles-1]-rmsError_training[nFiles-1]*3,rms_testing[0]+rmsError_testing[0]*3);
  RMSvsnTrees_testing_eb->Draw("psame");
  //  leg->Draw("same");  

  TCanvas* UnderflowCanvas=new TCanvas("UnderflowCanvas","UnderflowCanvas");

  UnderflowvsnTrees_training_eb->Draw("ap");
  UnderflowvsnTrees_training_eb->GetYaxis()->SetRangeUser(underflow_training[nFiles-1]-underflow_training[nFiles-1]*0.2,underflow_testing[0]+underflow_testing[0]*0.2);
  UnderflowvsnTrees_testing_eb->Draw("psame");
  //  leg->Draw("same");  

  TCanvas* OverflowCanvas=new TCanvas("OverflowCanvas","OverflowCanvas");

  OverflowvsnTrees_training_eb->Draw("ap");
  OverflowvsnTrees_training_eb->GetYaxis()->SetRangeUser(overflow_training[nFiles-1]-overflow_training[nFiles-1]*0.2,overflow_testing[0]+overflow_testing[0]*0.2);
  OverflowvsnTrees_testing_eb->Draw("psame");
  //  leg->Draw("same");  


  TString inputDirectoryString=inputDirectory;
  TFile* fOut=TFile::Open(inputDirectoryString+"/RmsPlots_"+option+".root","recreate");
  RMSvsnTrees_training_eb->Write();
  RMSvsnTrees_testing_eb->Write();
  UnderflowvsnTrees_training_eb->Write();
  OverflowvsnTrees_training_eb->Write();
  UnderflowvsnTrees_testing_eb->Write();
  OverflowvsnTrees_testing_eb->Write();
  RMSCanvas->Write();
  UnderflowCanvas->Write();
  OverflowCanvas->Write();
  fOut->Close();

  /*  TF1 *fa = new TF1("fa","TMath::Sqrt([0]*[0]/x+ [2]*[2]/(x*x))",0,100);                                                                         
  fa->SetParameter(0,1);                                                                                                                                  
  fa->SetParameter(1,0.05);                                                                                                                               
  fa->SetParameter(2,23);                                                                                                                                 
                                                                                                                                                            
  RMSvsnStatistic->Fit("fa");
  */
    
}
