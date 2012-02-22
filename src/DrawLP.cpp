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

	DrawLP *d1 = new DrawLP(4615.);  //Constructor

	float Lumi = d1->getLumi();
	float LumiTot[NdataSet];
	d1->SetOutputdir("Plot_LP");

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

//NVTX	//HISTO & BRANCH
	TH1F **h_in_nvtx;	h_in_nvtx = d1->InitHistoTH1F("h_in_nvtx", "", NdataSet, 20, 0., 20. );		THStack* h_in_nvtx_S = new THStack("h_in_nvtx_S","");
        int nvtx_DA, nvtx_DY, nvtx_WJ, nvtx_TT, nvtx_WW, nvtx_WZ, nvtx_ZZ;
        int nvtx[ NdataSet ]={nvtx_DA, nvtx_DY, nvtx_WJ, nvtx_TT, nvtx_WW, nvtx_WZ, nvtx_ZZ};
        d1->BranchAdd( AllTree, "nvtx", nvtx, NdataSet );
	//NORMAL FILL
	d1->NormalFill2( NdataSet, AllTree, h_in_nvtx, nvtx, finWeight, LumiTot);
	//Stack & Leg & Plot
	h_in_nvtx_S = d1->MakeStack(h_in_nvtx);
	TLegend *leg_nvtx;	leg_nvtx = d1->MakeLeg_Comparison( h_in_nvtx, 0.6, 0.4, 0.9, 0.88);
	d1->Plot(myc1, h_in_nvtx_S, leg_nvtx, h_in_nvtx[DATA], "nvtx","Num of vertex","");
        // DESTRUCTORS
        d1->deleteHisto(h_in_nvtx, NdataSet );
        delete h_in_nvtx_S;
//Met1  //HISTO & BRANCH
        TH1F **h_in_met1_pt;       h_in_met1_pt = d1->InitHistoTH1F("h_in_met1_pt", "", NdataSet, 50, 0., 200. );          THStack* h_in_met1_pt_S = new THStack("h_in_met1_pt_S","");
        float met1_pt_DA, met1_pt_DY, met1_pt_WJ, met1_pt_TT, met1_pt_WW, met1_pt_WZ, met1_pt_ZZ;
        float met1_pt[ NdataSet ]={met1_pt_DA, met1_pt_DY, met1_pt_WJ, met1_pt_TT, met1_pt_WW, met1_pt_WZ, met1_pt_ZZ};
        d1->BranchAdd( AllTree, "met1_pt", met1_pt, NdataSet );
        //NORMAL FILL
	d1->NormalFill( NdataSet, AllTree, h_in_met1_pt, met1_pt, finWeight, LumiTot);
        //HISTO & BRANCH: Met1
        h_in_met1_pt_S = d1->MakeStack(h_in_met1_pt);
        TLegend *leg_met1;      leg_met1 = d1->MakeLeg_Comparison( h_in_met1_pt, 0.6, 0.4, 0.9, 0.88);
        d1->Plot(myc1, h_in_met1_pt_S, leg_met1, h_in_met1_pt[DATA], "met1","PFMet","GeV");

	// DESTRUCTORS
	d1->deleteHisto(h_in_nvtx, NdataSet );
	delete h_in_nvtx_S; 
        d1->deleteHisto(h_in_met1_pt, NdataSet );
	delete h_in_met1_pt_S; 

	delete d1;  
	delete myc1; 
	delete AllTree;
}
