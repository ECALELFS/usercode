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
#include <TF1.h>
#include <TChain.h>
#include <TMath.h>
#include <TLegend.h>
#include "CommonTools/DrawLPBase.h"
#include <TROOT.h>
#include <TStyle.h>

#define NdataSet 7

using namespace std;
using namespace N_DATA;

int main(int argc, char* argv[]){

	TCanvas* myc1 = new TCanvas("myc1", "CMS", 600, 600);
	//myc1->SetFillColor(0); gStyle->SetOptStat(0);

	DrawLP *d1 = new DrawLP(4615.);  //Constructor

	float Lumi = d1->getLumi();
	float LumiTot[NdataSet];
	for( int i=0; i < NdataSet; i++ ){
	if(i==0) LumiTot[i] = 1.;
	else LumiTot[i] = Lumi; 
	}

	// INPUT
	string UsedTree = "Tree_AllVariables";
	string PathInput_DATA = "Output/Data/", PathInput_MC = "Output/MC/";
	TTree **AllTree = new TTree*[ NdataSet ];
	AllTree[DATA] = d1->GetTree( PathInput_DATA + "histosDoubleData.root", UsedTree.c_str() );
	AllTree[DY] = d1->GetTree( PathInput_MC + "histosfiles_DYJetsToLL.root", UsedTree.c_str() );
	AllTree[WJ] = d1->GetTree( PathInput_MC + "histosfiles_WJetsToLNu.root", UsedTree.c_str() );
	AllTree[TT] = d1->GetTree( PathInput_MC + "histosfiles_TTJets.root", UsedTree.c_str() );
	AllTree[WW] = d1->GetTree( PathInput_MC + "histosfiles_WW.root", UsedTree.c_str() );
	AllTree[WZ] = d1->GetTree( PathInput_MC + "histosfiles_WZ.root", UsedTree.c_str() );
	AllTree[ZZ] = d1->GetTree( PathInput_MC + "histosfiles_ZZTot.root", UsedTree.c_str() );

        // BR: WEIGHT
	float finWeight_DA, finWeight_DY, finWeight_WJ, finWeight_TT, finWeight_WW, finWeight_WZ, finWeight_ZZ;
	float finWeight[ NdataSet ]={finWeight_DA, finWeight_DY, finWeight_WJ, finWeight_TT, finWeight_WW, finWeight_WZ, finWeight_ZZ};
	d1->BranchAdd( AllTree, "finWeight", finWeight, NdataSet );

	//HISTO: hee_in_llPx
	TH1F **hee_in_llPx;
	hee_in_llPx = d1->InitHisto("", "", NdataSet );
	THStack* hee_in_llPx_S = new THStack("hee_in_llPx_S","");

        // BR: hee_in_llPx
        float l1_px_DA, l1_px_DY, l1_px_WJ, l1_px_TT, l1_px_WW, l1_px_WZ, l1_px_ZZ;
        float l1_px[ NdataSet ]={l1_px_DA, l1_px_DY, l1_px_WJ, l1_px_TT, l1_px_WW, l1_px_WZ, l1_px_ZZ};
        d1->BranchAdd( AllTree, "l1_px", l1_px, NdataSet );

	// hee_in_llPx
	for( int i=0; i < NdataSet; ++i ){
        	for( int iEntry=0; iEntry<AllTree[i]->GetEntries(); iEntry++ ){
        	AllTree[i]->GetEntry(iEntry);
		hee_in_llPx[i]->Fill(l1_px[i], finWeight[i]*LumiTot[i]);
        	}
	}


	// STACK & LEG & Plot
	hee_in_llPx_S = d1->MakeStack(hee_in_llPx);
	TLegend *leg_ee_px;	leg_ee_px = d1->MakeLeg_Comparison( hee_in_llPx, 0.6, 0.4, 0.9, 0.88);
	d1->Plot(myc1, hee_in_llPx_S, leg_ee_px, hee_in_llPx[DATA], "PROVA.png","(ele) Px","GeV");

	// DESTRUCTORS
	d1->deleteHisto(hee_in_llPx, NdataSet );
	delete hee_in_llPx_S; 

	delete d1;  
	delete myc1; 
	delete AllTree;
}
