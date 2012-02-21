#include <stdlib.h>
#include "TFile.h"
#include "TTree.h"
#include <iostream>
#include <cstring>
#include <string>
#include <TStyle.h>
#include <TCanvas.h>
#include <TH1.h>
#include "THStack.h"
#include "TAttLine.h"
#include <TH1.h>
#include <TGraph.h>
#include <TMultiGraph.h>
#include <TF1.h>
#include <TChain.h>
#include <TMath.h>
#include <TLegend.h>
#include "CommonTools/DrawLPBase.h"
#include <TROOT.h>
#include <TStyle.h>

#define NdataSet 2
#define PointToPlot 20

using namespace std;

int main(int argc, char* argv[]){

	TCanvas* myc1 = new TCanvas("myc1", "CMS", 600, 600);
	myc1->SetFillColor(0); gStyle->SetOptStat(0);

	DrawLP *d1 = new DrawLP(4615.);  //Constructor

	float Lumi = d1->getLumi();
	float LumiTot[NdataSet];
	for( int i=0; i < NdataSet; i++ ){
	if(i==0) LumiTot[i] = 1.;
	else LumiTot[i] = Lumi; 
	}

	// INPUT
	string UsedTree = "Tree_Met_Eff";
	string PathInput_DATA = "Output/Data/", PathInput_MC = "Output/MC/";
	TTree **AllTree = new TTree*[ NdataSet ];
	AllTree[0] = d1->GetTree( PathInput_MC + "histosfiles_DYJetsToLL.root", UsedTree.c_str() );
	AllTree[1] = d1->GetTree( PathInput_MC + "histosfiles_ZZTot.root", UsedTree.c_str() );

        // BR: FinWeight
	float finWeight_DY, finWeight_ZZ;
	float finWeight[ NdataSet ]={finWeight_DY, finWeight_ZZ};
	d1->BranchAdd( AllTree, "finWeight", finWeight, NdataSet );

        // BR: met1
        float met1_pt_DY, met1_pt_ZZ;
        float met1_pt[ NdataSet ]={ met1_pt_DY, met1_pt_ZZ};
        d1->BranchAdd( AllTree, "met1_pt", met1_pt, NdataSet );

        // BR: met_Red_pt_IND
        float met_Red_pt_IND_DY, met_Red_pt_IND_ZZ;
        float met_Red_pt_IND[ NdataSet ]={ met_Red_pt_IND_DY, met_Red_pt_IND_ZZ};
        d1->BranchAdd( AllTree, "met_Red_pt_IND", met_Red_pt_IND, NdataSet );

        // BR: met_Red_pt_D0
        float met_Red_pt_D0_DY, met_Red_pt_D0_ZZ;
        float met_Red_pt_D0[ NdataSet ]={ met_Red_pt_D0_DY, met_Red_pt_D0_ZZ};
        d1->BranchAdd( AllTree, "met_Red_pt_D0", met_Red_pt_D0, NdataSet );

        // BR: met_Red_pt_MIN
        float met_Red_pt_MIN_DY, met_Red_pt_MIN_ZZ;
        float met_Red_pt_MIN[ NdataSet ]={ met_Red_pt_MIN_DY, met_Red_pt_MIN_ZZ};
        d1->BranchAdd( AllTree, "met_Red_pt_MIN", met_Red_pt_MIN, NdataSet );

        // BR: met_WW
        float met_WW_DY, met_WW_ZZ;
        float met_WW[ NdataSet ]={ met_WW_DY, met_WW_ZZ};
        d1->BranchAdd( AllTree, "met_WW", met_WW, NdataSet );

	float incr = 2.5;
	float Startcut = 25.;
	float cut = Startcut;
	int IterCut = 22;//(int)(80-Startcut)/incr;
	float Nev[NdataSet]={0.};

	// Efficenza PFMET
	float Eff_met1[NdataSet][100];
	for( int j=0; j < 100; j++ ){
                for( int i=0; i < NdataSet; i++ ){
        Eff_met1[i][j]=0.;
                }
        }

      for( int j=0; j < IterCut; j++ ){

	for( int i=0; i < NdataSet; ++i ){
	
        	for( int iEntry=0; iEntry<AllTree[i]->GetEntries(); iEntry++ ){

       		   AllTree[i]->GetEntry(iEntry);
		   if( j==0 ) Nev[i] += finWeight[i];
		   if( met1_pt[i] > cut ) Eff_met1[i][j] += finWeight[i];
        	}
	}
      cut+=incr;}

	float ZZ_Met1[PointToPlot+1]={0.}, DY_Met1[PointToPlot+1]={0.};
	
	for(int j=0; j < PointToPlot; ++j){
	ZZ_Met1[j]=Eff_met1[1][j]/Nev[1];
	DY_Met1[j]=Eff_met1[0][j]/Nev[0];
	cout<<"DY: "<<j<<"  "<<Nev[0]*Lumi<<"  "<<Eff_met1[0][j]*Lumi<<"  "<<Eff_met1[0][j]/Nev[0]<<endl;
	cout<<"ZZ: "<<j<<"  "<<Nev[1]*Lumi<<"  "<<Eff_met1[1][j]*Lumi<<"  "<<Eff_met1[1][j]/Nev[1]<<endl; cout<<endl;
	}

        // Efficenza REDMET IND
        float Eff_metRED_IND[NdataSet][100];
	for( int j=0; j < 100; j++ ){
	        for( int i=0; i < NdataSet; i++ ){
	Eff_metRED_IND[i][j]=0.;
		}
	}

        cut = Startcut;
      for( int j=0; j < IterCut; j++ ){

        for( int i=0; i < NdataSet; ++i ){

                for( int iEntry=0; iEntry<AllTree[i]->GetEntries(); iEntry++ ){

                   AllTree[i]->GetEntry(iEntry);
                   if( met_Red_pt_IND[i] > cut ) Eff_metRED_IND[i][j] += finWeight[i];
                }
        }
      cut+=incr;}

        float ZZRed_IND[PointToPlot+1]={0.}, DYRed_IND[PointToPlot+1]={0.};

        for(int j=0; j < PointToPlot; ++j){
        ZZRed_IND[j]=Eff_metRED_IND[1][j]/Nev[1];
        DYRed_IND[j]=Eff_metRED_IND[0][j]/Nev[0];
        cout<<"DY: "<<j<<"  "<<Nev[0]*Lumi<<"  "<<Eff_metRED_IND[0][j]*Lumi<<"  "<<Eff_metRED_IND[0][j]/Nev[0]<<endl;
        cout<<"ZZ: "<<j<<"  "<<Nev[1]*Lumi<<"  "<<Eff_metRED_IND[1][j]*Lumi<<"  "<<Eff_metRED_IND[1][j]/Nev[1]<<endl; cout<<endl;
        }

        // Efficenza REDMET D0
        float Eff_metRED_D0[NdataSet][100];
        for( int j=0; j < 100; j++ ){
                for( int i=0; i < NdataSet; i++ ){
        Eff_metRED_D0[i][j]=0.;
                }
        }

        cut = Startcut;
      for( int j=0; j < IterCut; j++ ){

        for( int i=0; i < NdataSet; ++i ){

                for( int iEntry=0; iEntry<AllTree[i]->GetEntries(); iEntry++ ){

                   AllTree[i]->GetEntry(iEntry);
                   if( met_Red_pt_D0[i] > cut ) Eff_metRED_D0[i][j] += finWeight[i];
                }
        }
      cut+=incr;}

        float ZZRed_D0[PointToPlot+1]={0.}, DYRed_D0[PointToPlot+1]={0.};

        for(int j=0; j < PointToPlot; ++j){
        ZZRed_D0[j]=Eff_metRED_D0[1][j]/Nev[1];
        DYRed_D0[j]=Eff_metRED_D0[0][j]/Nev[0];
        cout<<"DY: "<<j<<"  "<<Nev[0]*Lumi<<"  "<<Eff_metRED_D0[0][j]*Lumi<<"  "<<Eff_metRED_D0[0][j]/Nev[0]<<endl;
        cout<<"ZZ: "<<j<<"  "<<Nev[1]*Lumi<<"  "<<Eff_metRED_D0[1][j]*Lumi<<"  "<<Eff_metRED_D0[1][j]/Nev[1]<<endl; cout<<endl;
        }

        // Efficenza REDMET MIN
        float Eff_metRED_MIN[NdataSet][100];
        for( int j=0; j < 100; j++ ){
                for( int i=0; i < NdataSet; i++ ){
        Eff_metRED_MIN[i][j]=0.;
                }
        }

        cut = Startcut;
      for( int j=0; j < IterCut; j++ ){

        for( int i=0; i < NdataSet; ++i ){

                for( int iEntry=0; iEntry<AllTree[i]->GetEntries(); iEntry++ ){

                   AllTree[i]->GetEntry(iEntry);
                   if( met_Red_pt_MIN[i] > cut ) Eff_metRED_MIN[i][j] += finWeight[i];
                }
        }
      cut+=incr;}

        float ZZRed_MIN[PointToPlot+1]={0.}, DYRed_MIN[PointToPlot+1]={0.};

        for(int j=0; j < PointToPlot; ++j){
        ZZRed_MIN[j]=Eff_metRED_MIN[1][j]/Nev[1];
        DYRed_MIN[j]=Eff_metRED_MIN[0][j]/Nev[0];
        cout<<"DY: "<<j<<"  "<<Nev[0]*Lumi<<"  "<<Eff_metRED_MIN[0][j]*Lumi<<"  "<<Eff_metRED_MIN[0][j]/Nev[0]<<endl;
        cout<<"ZZ: "<<j<<"  "<<Nev[1]*Lumi<<"  "<<Eff_metRED_MIN[1][j]*Lumi<<"  "<<Eff_metRED_MIN[1][j]/Nev[1]<<endl; cout<<endl;
        }

        // Efficenza met_WW
        float Eff_met_WW[NdataSet][100];
        for( int j=0; j < 100; j++ ){
                for( int i=0; i < NdataSet; i++ ){
        Eff_met_WW[i][j]=0.;
                }
        }

        cut = Startcut;
      for( int j=0; j < IterCut; j++ ){

        for( int i=0; i < NdataSet; ++i ){

                for( int iEntry=0; iEntry<AllTree[i]->GetEntries(); iEntry++ ){

                   AllTree[i]->GetEntry(iEntry);
                   if( met_WW[i] > cut ) Eff_met_WW[i][j] += finWeight[i];
                }
        }
      cut+=incr;}

        float ZZmet_WW[PointToPlot+1]={0.}, DYmet_WW[PointToPlot+1]={0.};

        for(int j=0; j < PointToPlot; ++j){
        ZZmet_WW[j]=Eff_met_WW[1][j]/Nev[1];
        DYmet_WW[j]=Eff_met_WW[0][j]/Nev[0];
        cout<<"DY: "<<j<<"  "<<Nev[0]*Lumi<<"  "<<Eff_met_WW[0][j]*Lumi<<"  "<<Eff_met_WW[0][j]/Nev[0]<<endl;
        cout<<"ZZ: "<<j<<"  "<<Nev[1]*Lumi<<"  "<<Eff_met_WW[1][j]*Lumi<<"  "<<Eff_met_WW[1][j]/Nev[1]<<endl; cout<<endl;
        }


	myc1->cd();
	myc1->SetLogx();
	
	TGraph *PFMet = new TGraph(PointToPlot+1, DY_Met1, ZZ_Met1);
	PFMet->SetLineColor(2);
	PFMet->SetLineWidth(1);
	PFMet->SetMarkerColor(2);
	PFMet->SetMarkerStyle(20);
	PFMet->SetMarkerSize(0.5);
	PFMet->SetTitle("MET Efficiency");
	PFMet->GetXaxis()->SetTitle("DY Efficiency");
	PFMet->GetYaxis()->SetTitle("ZZ Efficiency");
        PFMet->GetXaxis()->Set(30, 0., 0.2);
        PFMet->GetYaxis()->Set(30, 0., 0.8);

        TGraph *Met_IND = new TGraph(PointToPlot+1, DYRed_IND, ZZRed_IND);
        Met_IND->SetLineColor(kBlue);
        Met_IND->SetLineWidth(1);
        Met_IND->SetMarkerColor(kBlue);
        Met_IND->SetMarkerStyle(20);
        Met_IND->SetMarkerSize(0.5);

        TGraph *Met_D0 = new TGraph(PointToPlot+1, DYRed_D0, ZZRed_D0);
        Met_D0->SetLineColor(3);
        Met_D0->SetLineWidth(1);
        Met_D0->SetMarkerColor(3);
        Met_D0->SetMarkerStyle(20);
        Met_D0->SetMarkerSize(0.5);

        TGraph *Met_MIN = new TGraph(PointToPlot+1, DYRed_MIN, ZZRed_MIN);
        Met_MIN->SetLineColor(9);
        Met_MIN->SetLineWidth(1);
        Met_MIN->SetMarkerColor(9);
        Met_MIN->SetMarkerStyle(20);
        Met_MIN->SetMarkerSize(0.5);

        TGraph *Met_WW = new TGraph(PointToPlot+1, DYmet_WW, ZZmet_WW);
        Met_WW->SetLineColor(6);
        Met_WW->SetLineWidth(1);
        Met_WW->SetMarkerColor(6);
        Met_WW->SetMarkerStyle(20);
        Met_WW->SetMarkerSize(0.5);

	//TLegend
        TLegend *leg = new TLegend(0.15, 0.57, 0.45, 0.87);
        leg->SetFillColor(kWhite);
        leg->AddEntry(PFMet,"PFMET","P");
        leg->AddEntry(Met_IND,"REDMet IND","P");
        leg->AddEntry(Met_D0,"REDMet D0","P");
        leg->AddEntry(Met_MIN,"REDMet MIN","P");
        leg->AddEntry(Met_WW,"Met WW","P");

	PFMet->Draw("ACP");
	Met_IND->Draw("CPsame");
	Met_D0->Draw("CPsame");
	Met_MIN->Draw("CPsame");
	Met_WW->Draw("CPsame");
	leg->Draw("same");
	myc1->SaveAs("Met_Eff.png");
/*
	// STACK & LEG
	hee_in_llPx_S = d1->MakeStack(hee_in_llPx);
	TLegend *leg_ee_px;	leg_ee_px = d1->MakeLeg( hee_in_llPx, 0.6, 0.4, 0.9, 0.88);

	// MAKE PLOT
	myc1->cd();
	myc1->SetLogy();
	hee_in_llPx_S->Draw("HISTO");
	hee_in_llPx[DATA]->SetMarkerStyle(20);
	hee_in_llPx[DATA]->SetMarkerColor(1);
	hee_in_llPx[DATA]->SetMarkerSize(1);
	hee_in_llPx[DATA]->Draw("same");
	leg_ee_px->Draw("same");
	TPaveText* label_cms = d1->get_labelCMStop(0);
	label_cms->Draw("same");
	myc1->SaveAs("PROVA.eps");

	// DESTRUCTORS
	d1->deleteHisto(hee_in_llPx, NdataSet );
	delete hee_in_llPx_S; 
*/
	delete d1;  
	delete myc1; 
	delete AllTree;
}
