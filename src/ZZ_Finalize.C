#define ZZ_Finalize_cxx
#include "ZZ_Finalize.h"
#include <TH2.h>
#include <TF1.h>
#include <TGraph.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <TLegend.h>
#include <math.h>
#include <TLegendEntry.h>
#include <TLorentzVector.h>
#include <TFitResultPtr.h>

#include "Analysis_Electron.h"
#include "Analysis_Muon.h"

inline double delta_phi(double phi1, double phi2);

using namespace std;

void ZZ_Finalize::Loop(){

//   In a ROOT session, you can do:
//      Root > .L ZZ_Finalize.C
//      Root > ZZ_Finalize t
//      Root > t.GetEntry(12); // Fill t data members with entry number 12
//      Root > t.Show();       // Show values of entry 12
//      Root > t.Show(16);     // Read and show values of entry 16
//      Root > t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
	if (fChain == 0) return;
	
	//#include "Include/higgsDeclaration.h"

	TTree * Tree_NVertex = new TTree("Tree_NVertex","Tree for re-weighting N verteces");
	Float_t Nvtx, finWeight = 1.;
	Tree_NVertex->Branch("Nvtx", &Nvtx, "Nvtx/I");
	Tree_NVertex->Branch("finWeight", &finWeight, "finWeight/F");

// HISTO ee
        TH1F * hee_in_llMass    = new TH1F("hee_in_llMass", "Dilepton Invariant mass", 20, 75., 110.);			hee_in_llMass->Sumw2();
        TH1F * hee_in_llPt      = new TH1F("hee_in_llPt", "Transvers momentum of lepton pair", 30, 25., 325.);		hee_in_llPt->Sumw2();
        TH1F * hee_in_l1Pt      = new TH1F("hee_in_l1Pt", "Transvers momentum of lepton 1", 25, 20., 100.);		hee_in_l1Pt->Sumw2();
        TH1F * hee_in_l2Pt      = new TH1F("hee_in_l2Pt", "Transvers momentum of lepton 2", 25, 20., 100.);		hee_in_l2Pt->Sumw2();
        TH1F * hee_in_MET1Pt    = new TH1F("hee_in_MET1Pt", "PF Missing transvers energy", 50, 0., 200.);		hee_in_MET1Pt->Sumw2();
        TH1F * hee_in_l1Eta     = new TH1F("hee_in_l1Eta", "#eta lepton 1", 20, -4.5, 4.5);				hee_in_l1Eta->Sumw2();
        TH1F * hee_in_l2Eta     = new TH1F("hee_in_l2Eta", "#eta lepton 2", 20, -4.5, 4.5);				hee_in_l2Eta->Sumw2();
        TH1F * hee_in_rho       = new TH1F("hee_in_rho", "Rho variable", 15, 0., 15.);					hee_in_rho->Sumw2();
        TH1F * hee_in_nvtx      = new TH1F("hee_in_nvtx", "Number of Good vertex", 20, 0., 20.);			hee_in_nvtx->Sumw2();

        TH1F * hee_llMass       = new TH1F("hee_llMass", "Dilepton Invariant mass", 20, 75., 105.);			hee_llMass->Sumw2();
        TH1F * hee_llPt         = new TH1F("hee_llPt", "Transvers momentum of lepton pair", 30, 25., 325.);		hee_llPt->Sumw2();
        TH1F * hee_l1Pt         = new TH1F("hee_l1Pt", "Transvers momentum of lepton 1", 25, 20., 200.);		hee_l1Pt->Sumw2();
        TH1F * hee_l2Pt         = new TH1F("hee_l2Pt", "Transvers momentum of lepton 2", 25, 20., 200.);		hee_l2Pt->Sumw2();
        TH1F * hee_MET1Pt       = new TH1F("hee_MET1Pt", "PF Missing transvers energy", 50, 0., 200.);			hee_MET1Pt->Sumw2();
        TH1F * hee_l1Eta        = new TH1F("hee_l1Eta", "#eta lepton 1", 20, -2., 2.);					hee_l1Eta->Sumw2();
        TH1F * hee_l2Eta        = new TH1F("hee_l2Eta", "#eta lepton 2", 20, -2., 2.);					hee_l2Eta->Sumw2();
        TH1F * hee_rho          = new TH1F("hee_rho", "Rho variable", 15, 0., 15.);					hee_rho->Sumw2();
        TH1F * hee_nvtx         = new TH1F("hee_nvtx", "Number of Good vertex", 20, 0., 20.);				hee_nvtx->Sumw2();
        TH1F * hee_mZZt         = new TH1F("hee_mZZt", "Di-Boson Mass", 100, 150., 800.);				hee_mZZt->Sumw2();

// HISTO mumu 
        TH1F * hmumu_in_llMass  = new TH1F("hmumu_in_llMass", "Invariant mass of lepton pair", 20, 75., 110.);		hmumu_in_llMass->Sumw2();
        TH1F * hmumu_in_llPt    = new TH1F("hmumu_in_llPt", "Transvers momentum of lepton pair", 30, 25., 325.);	hmumu_in_llPt->Sumw2();
        TH1F * hmumu_in_l1Pt    = new TH1F("hmumu_in_l1Pt", "Transvers momentum of lepton 1", 25, 20., 100.);		hmumu_in_l1Pt->Sumw2();
        TH1F * hmumu_in_l2Pt    = new TH1F("hmumu_in_l2Pt", "Transvers momentum of lepton 2", 25, 20., 100.);		hmumu_in_l2Pt->Sumw2();
        TH1F * hmumu_in_MET1Pt  = new TH1F("hmumu_in_MET1Pt", "PF Missing transvers energy", 50, 0., 200.);		hmumu_in_MET1Pt->Sumw2();
        TH1F * hmumu_in_l1Eta   = new TH1F("hmumu_in_l1Eta", "#eta lepton 1", 20, -4.5, 4.5);				hmumu_in_l1Eta->Sumw2();
        TH1F * hmumu_in_l2Eta   = new TH1F("hmumu_in_l2Eta", "#eta lepton 2", 20, -4.5, 4.5);				hmumu_in_l2Eta->Sumw2();
        TH1F * hmumu_in_rho     = new TH1F("hmumu_in_rho", "Rho variable", 15, 0., 15.);				hmumu_in_rho->Sumw2();
        TH1F * hmumu_in_nvtx    = new TH1F("hmumu_in_nvtx", "Number of Good vertex", 20, 0., 20.);			hmumu_in_nvtx->Sumw2();

        TH1F * hmumu_llMass     = new TH1F("hmumu_llMass", "Invariant mass of lepton pair", 20, 75., 105.);		hmumu_llMass->Sumw2();
        TH1F * hmumu_llPt       = new TH1F("hmumu_llPt", "Transvers momentum of lepton pair", 30, 25., 325.);		hmumu_llPt->Sumw2();
        TH1F * hmumu_l1Pt       = new TH1F("hmumu_l1Pt", "Transvers momentum of lepton 1", 25, 20., 200.);		hmumu_l1Pt->Sumw2();
        TH1F * hmumu_l2Pt       = new TH1F("hmumu_l2Pt", "Transvers momentum of lepton 2", 25, 20., 200.);		hmumu_l2Pt->Sumw2();
        TH1F * hmumu_MET1Pt     = new TH1F("hmumu_MET1Pt", "PF Missing transvers energy", 50, 0., 200.);		hmumu_MET1Pt->Sumw2();
        TH1F * hmumu_l1Eta      = new TH1F("hmumu_l1Eta", "#eta lepton 1", 20, -2., 2.);				hmumu_l1Eta->Sumw2();
        TH1F * hmumu_l2Eta      = new TH1F("hmumu_l2Eta", "#eta lepton 2", 20, -2., 2.);				hmumu_l2Eta->Sumw2();
        TH1F * hmumu_rho        = new TH1F("hmumu_rho", "Rho variable", 15, 0., 15.);					hmumu_rho->Sumw2();
        TH1F * hmumu_nvtx       = new TH1F("hmumu_nvtx", "Number of Good vertex", 20, 0., 20.);				hmumu_nvtx->Sumw2();
        TH1F * hmumu_mZZt       = new TH1F("hmumu_mZZt", "Di-Boson Mass", 100, 150., 800.);				hmumu_mZZt->Sumw2();
// GLOBAL
        TH1F * h_in_llMass    = new TH1F("h_in_llMass", "Dilepton Invariant mass", 20, 75., 110.);			h_in_llMass->Sumw2();
        TH1F * h_in_llPt      = new TH1F("h_in_llPt", "Transvers momentum of lepton pair", 30, 25., 325.);		h_in_llPt->Sumw2();
        TH1F * h_in_l1Pt      = new TH1F("h_in_l1Pt", "Transvers momentum of lepton 1", 25, 20., 100.);			h_in_l1Pt->Sumw2();
        TH1F * h_in_l2Pt      = new TH1F("h_in_l2Pt", "Transvers momentum of lepton 2", 25, 20., 100.);			h_in_l2Pt->Sumw2();
        TH1F * h_in_MET1Pt    = new TH1F("h_in_MET1Pt", "PF Missing transvers energy", 50, 0., 200.);			h_in_MET1Pt->Sumw2();
        TH1F * h_in_l1Eta     = new TH1F("h_in_l1Eta", "#eta lepton 1", 20, -4.5, 4.5);					h_in_l1Eta->Sumw2();
        TH1F * h_in_l2Eta     = new TH1F("h_in_l2Eta", "#eta lepton 2", 20, -4.5, 4.5);					h_in_l2Eta->Sumw2();
        TH1F * h_in_rho       = new TH1F("h_in_rho", "Rho variable", 15, 0., 15.);					h_in_rho->Sumw2();
        TH1F * h_in_nvtx      = new TH1F("h_in_nvtx", "Number of Good vertex", 20, 0., 20.);				h_in_nvtx->Sumw2();
        TH1F * h_in_phiZMet   = new TH1F("h_in_phiZMet", "Delta Phi Met Z", 30, 0., 3.142);				h_in_phiZMet->Sumw2();
        TH1F * h_in_MetParallel  = new TH1F("h_in_MetParallel", "Met Z parallel", 100, 0., 300);			h_in_MetParallel->Sumw2();
        TH1F * h_in_MetTransvers = new TH1F("h_in_MetTransvers", "Met Z transvers", 100, -150., 150);			h_in_MetTransvers->Sumw2();

        TH1F * h_llMass       = new TH1F("h_llMass", "Dilepton Invariant mass", 20, 75., 105.);				h_llMass->Sumw2();
        TH1F * h_llPt         = new TH1F("h_llPt", "Transvers momentum of lepton pair", 30, 25., 325.);			h_llPt->Sumw2();
        TH1F * h_l1Pt         = new TH1F("h_l1Pt", "Transvers momentum of lepton 1", 25, 20., 200.);			h_l1Pt->Sumw2();
        TH1F * h_l2Pt         = new TH1F("h_l2Pt", "Transvers momentum of lepton 2", 25, 20., 200.);			h_l2Pt->Sumw2();
        TH1F * h_MET1Pt       = new TH1F("h_MET1Pt", "PF Missing transvers energy", 50, 0., 200.);			h_MET1Pt->Sumw2();
        TH1F * h_l1Eta        = new TH1F("h_l1Eta", "#eta lepton 1", 20, -2., 2.);					h_l1Eta->Sumw2();
        TH1F * h_l2Eta        = new TH1F("h_l2Eta", "#eta lepton 2", 20, -2., 2.);					h_l2Eta->Sumw2();
        TH1F * h_rho          = new TH1F("h_rho", "Rho variable", 15, 0., 15.);						h_rho->Sumw2();
        TH1F * h_nvtx         = new TH1F("h_nvtx", "Number of Good vertex", 20, 0., 20.);				h_nvtx->Sumw2();
        TH1F * h_phiZMet      = new TH1F("h_phiZMet", "Delta Phi Met Z", 30, 0., 3.142);				h_phiZMet->Sumw2();
        TH1F * h_MetParallel  = new TH1F("h_MetParallel", "Met Z parallel", 100, 0., 300);				h_MetParallel->Sumw2();
        TH1F * h_MetTransvers = new TH1F("h_MetTransvers", "Met Z transvers", 100, -150., 150);				h_MetTransvers->Sumw2();

        TH1F * h_mZZt         = new TH1F("h_mZZt", "Di-Boson Mass", 100, 150., 800.);					h_mZZt->Sumw2();
// Pt Range
        TH1F * h_Pt50_mZ       = new TH1F("h_Pt50_mZ", "Pt<50, mZ mass", 20, 75., 110.);				h_Pt50_mZ->Sumw2();
        TH1F * h_Pt100_mZ      = new TH1F("h_Pt100_mZ", "Pt<100, mZ mass", 20, 75., 110.);				h_Pt100_mZ->Sumw2();
        TH1F * h_Pt150_mZ      = new TH1F("h_Pt150_mZ", "Pt<150, mZ mass", 20, 75., 110.);				h_Pt150_mZ->Sumw2();
        TH1F * h_PtMax_mZ      = new TH1F("h_PtMax_mZ", "Pt Max, mZ mass", 20, 75., 110.);				h_PtMax_mZ->Sumw2();
// HISTO 
	//MET_vs_VTX
        TH1F * h_in_MET1vtx    = new TH1F("h_in_MET1vtx", "MET distr. with 1 vertex", 40, 0., 60.);		h_in_MET1vtx->Sumw2();
        TH1F * h_in_METx1vtx   = new TH1F("h_in_METx1vtx", "MET_x distr. with 1 vertex", 40, -40., 40.);	h_in_METx1vtx->Sumw2();
        TH1F * h_in_METy1vtx   = new TH1F("h_in_METy1vtx", "MET_y distr. with 1 vertex", 40, -40., 40.);	h_in_METy1vtx->Sumw2();
        TH1F * h_in_MET4vtx    = new TH1F("h_in_MET4vtx", "MET distr. with 4 vertex", 40, 0., 60.);		h_in_MET4vtx->Sumw2();
        TH1F * h_in_METx4vtx   = new TH1F("h_in_METx4vtx", "MET_x distr. with 4 vertex", 40, -40., 40.);	h_in_METx4vtx->Sumw2();
        TH1F * h_in_METy4vtx   = new TH1F("h_in_METy4vtx", "MET_y distr. with 4 vertex", 40, -40., 40.);	h_in_METy4vtx->Sumw2();
        TH1F * h_in_MET8vtx    = new TH1F("h_in_MET8vtx", "MET distr. with 8 vertex", 40, 0., 60.);		h_in_MET8vtx->Sumw2();
        TH1F * h_in_METx8vtx   = new TH1F("h_in_METx8vtx", "MET_x distr. with 8 vertex", 40, -40., 40.);	h_in_METx8vtx->Sumw2();
        TH1F * h_in_METy8vtx   = new TH1F("h_in_METy8vtx", "MET_y distr. with 8 vertex", 40, -40., 40.);	h_in_METy8vtx->Sumw2();
        TH1F * h_in_MET12vtx    = new TH1F("h_in_MET12vtx", "MET distr. with 12 vertex", 40, 0., 60.);		h_in_MET12vtx->Sumw2();
        TH1F * h_in_METx12vtx   = new TH1F("h_in_METx12vtx", "MET_x distr. with 12 vertex", 40, -40., 40.);	h_in_METx12vtx->Sumw2();
        TH1F * h_in_METy12vtx   = new TH1F("h_in_METy12vtx", "MET_y distr. with 12 vertex", 40, -40., 40.);	h_in_METy12vtx->Sumw2();
        TH1F * h_in_MET18vtx    = new TH1F("h_in_MET18vtx", "MET distr. with 18 vertex", 40, 0., 60.);		h_in_MET18vtx->Sumw2();
        TH1F * h_in_METx18vtx   = new TH1F("h_in_METx18vtx", "MET_x distr. with 18 vertex", 40, -40., 40.);	h_in_METx18vtx->Sumw2();
        TH1F * h_in_METy18vtx   = new TH1F("h_in_METy18vtx", "MET_y distr. with 18 vertex", 40, -40., 40.);	h_in_METy18vtx->Sumw2();
	//MET_vs_rho
        TH1F * h_in_METx2rho   = new TH1F("h_in_METx2rho", "MET_x distr. with rho 0-2", 40, -40., 40.);		h_in_METx2rho->Sumw2();
        TH1F * h_in_METy2rho   = new TH1F("h_in_METy2rho", "MET_y distr. with rho 0-2", 40, -40., 40.);         h_in_METy2rho->Sumw2();
        TH1F * h_in_METx4rho   = new TH1F("h_in_METx4rho", "MET_x distr. with rho 2-4", 40, -40., 40.);         h_in_METx4rho->Sumw2();
        TH1F * h_in_METy4rho   = new TH1F("h_in_METy4rho", "MET_y distr. with rho 2-4", 40, -40., 40.);         h_in_METy4rho->Sumw2();
        TH1F * h_in_METx6rho   = new TH1F("h_in_METx6rho", "MET_x distr. with rho 4-6", 40, -40., 40.);         h_in_METx6rho->Sumw2();
        TH1F * h_in_METy6rho   = new TH1F("h_in_METy6rho", "MET_y distr. with rho 4-6", 40, -40., 40.);         h_in_METy6rho->Sumw2();
        TH1F * h_in_METx8rho   = new TH1F("h_in_METx8rho", "MET_x distr. with rho 6-8", 40, -40., 40.);         h_in_METx8rho->Sumw2();
        TH1F * h_in_METy8rho   = new TH1F("h_in_METy8rho", "MET_y distr. with rho 6-8", 40, -40., 40.);         h_in_METy8rho->Sumw2();
        TH1F * h_in_METx10rho  = new TH1F("h_in_METx10rho", "MET_x distr. with rho 8-10", 40, -40., 40.);       h_in_METx10rho->Sumw2();
        TH1F * h_in_METy10rho  = new TH1F("h_in_METy10rho", "MET_y distr. with rho 8-10", 40, -40., 40.);       h_in_METy10rho->Sumw2();
        TH1F * h_in_METx12rho  = new TH1F("h_in_METx12rho", "MET_x distr. with rho 10-12", 40, -40., 40.);      h_in_METx12rho->Sumw2();
        TH1F * h_in_METy12rho  = new TH1F("h_in_METy12rho", "MET_y distr. with rho 10-12", 40, -40., 40.);      h_in_METy12rho->Sumw2();
        TH1F * h_in_METx14rho  = new TH1F("h_in_METx14rho", "MET_x distr. with rho 12-14", 40, -40., 40.);      h_in_METx14rho->Sumw2();
        TH1F * h_in_METy14rho  = new TH1F("h_in_METy14rho", "MET_y distr. with rho 12-14", 40, -40., 40.);      h_in_METy14rho->Sumw2();
        TH1F * h_in_METx16rho  = new TH1F("h_in_METx16rho", "MET_x distr. with rho 14-16", 40, -40., 40.);      h_in_METx16rho->Sumw2();
        TH1F * h_in_METy16rho  = new TH1F("h_in_METy16rho", "MET_y distr. with rho 14-16", 40, -40., 40.);      h_in_METy16rho->Sumw2();
        TH1F * h_in_METx18rho  = new TH1F("h_in_METx18rho", "MET_x distr. with rho 16+", 40, -40., 40.);	h_in_METx18rho->Sumw2();
        TH1F * h_in_METy18rho  = new TH1F("h_in_METy18rho", "MET_y distr. with rho 16+", 40, -40., 40.);        h_in_METy18rho->Sumw2();

        TH1F * h_RMS_vtx       = new TH1F("h_RMS_vtx", "MET on x RMS vs N vertex", 20, 0., 20.);		h_RMS_vtx->Sumw2();
	TGraph * g_RMS_vtx     = new TGraph(5); g_RMS_vtx->SetTitle("g_RMS_vtx");
	
        TH1F * h_Nevent   = new TH1F("h_Nevent", "Event after cuts", 13, 0., 13.);
	TAxis * ProvaAxis=h_Nevent->GetXaxis();
	ProvaAxis->SetBinLabel(1 , "Preselection");
	ProvaAxis->SetBinLabel(2 , "Two leptons");
	ProvaAxis->SetBinLabel(3 , "Pt Lept");
	ProvaAxis->SetBinLabel(4 , "Pt Z");
	ProvaAxis->SetBinLabel(5 , "Jet Veto");
	ProvaAxis->SetBinLabel(6 , "MET");
	ProvaAxis->SetBinLabel(7 , "Balance");
	ProvaAxis->SetBinLabel(8 , "Jet Phi");
	ProvaAxis->SetBinLabel(9 , "Z Phi");
	ProvaAxis->SetBinLabel(10, "B-Veto");
	ProvaAxis->SetBinLabel(11, "Lept Veto");
	ProvaAxis->SetBinLabel(12, "ISO");
	ProvaAxis->SetBinLabel(13, "Z Mass");

	float Eff_Preselection = 0.;
	float Eff_Two_leptons = 0.;
	float Eff_Pt = 0.;
	float Eff_Eta = 0.;
	float Eff_Z_Pt = 0.;
	float Eff_Jet_Veto = 0.;
	float Eff_MET = 0.;
	float Eff_Balance = 0.;
	float Eff_Jet_Phi = 0.;
	float Eff_Z_Phi = 0.;
	float Eff_B_Veto = 0.;
	float Eff_Lept_Veto = 0.;
	float Eff_ISO = 0.;
	float Eff_Z_Mass = 0.;
	float Eff_FinalEE = 0.;
	float Eff_FinalMuMu = 0.;

	TDirectory *dir = gDirectory;
	TFile *file = new TFile(outputFileName_, "RECREATE");

	Long64_t nentries = fChain->GetEntriesFast(); // Entries number fot TChain

	Long64_t nbytes = 0, nb = 0;

	Bool_t ee = false;
	Bool_t mumu = false;	
	Bool_t isl1EB = false;
	Bool_t isl2EB = false;
	Bool_t isThereBJet = false;
	Bool_t veto_Jet = false;

	Float_t l1_CRI = 0.;
	Float_t l2_CRI = 0.;
	Float_t jet_eta = 0.;
	Float_t jet_pt = 0.;

        //Float_t vtxweight[20]={1.,1.,1.,1.,1.,1.,1.,1.,1.,1.,1.,1.,1.,1.,1.,1.,1.,1.,1.,1.};
	Float_t vtxweight[20]={1.,0.634276,0.678203,0.7131,0.743639,0.773336,0.810534,0.856799,0.916266,0.991299,1.08157,1.21162,1.34877,1.49695,1.67696,1.9008,2.1098,2.397,2.80421,3.42399};

	// event loop
	for (Long64_t jentry=0; jentry<nentries;jentry++) {
		if( (jentry) % 1000000 ==0 )  cout << "Event: " << jentry << "/" << nentries << endl;
		Long64_t ientry = LoadTree(jentry); //Set curren entry (-2 if it doesn't exist)
		if (ientry < 0) break;
		nb = fChain->GetEntry(jentry);   nbytes += nb;

		// reweighting for pile up & Nvetx
		finWeight = 1.;
		if ( isData_ == 0 ){
		    finWeight = Scaling_*weight;
		  if ( nvtx < 20 ) {  finWeight = Scaling_ * weight * vtxweight[nvtx]; }
		  if ( nvtx >= 20 ){  finWeight = Scaling_ * weight * vtxweight[19];   }
		}

		Eff_Preselection++;
		h_Nevent->SetBinContent(1,(h_Nevent->GetBinContent(1)+1.)*finWeight);

                //---------- Define Variables ----------           
                TLorentzVector lept1, lept2, lepts;
                lept1.SetPxPyPzE(l1_px,l1_py,l1_pz,l1_en);  
                lept2.SetPxPyPzE(l2_px,l2_py,l2_pz,l2_en);
                lepts = lept1 + lept2;
		float met1_px = met1_pt*cos(met1_phi);
		float met1_py = met1_pt*sin(met1_phi);
		Nvtx = nvtx;// For the TTree for nvtx reweighting
		double PhiZMet = delta_phi(met1_phi,lepts.Phi());
		double MetParallel = met1_pt*sin(PhiZMet);
		double MetTransv = met1_pt*cos(PhiZMet);
		double mZZt = sqrt( pow( sqrt(pow(lepts.M(),2)+pow(lepts.Pt(),2)) + sqrt(pow(lepts.M(),2)+pow(met1_pt,2)) ,2) - pow(sqrt( pow(lepts.Px()+met1_px,2)+pow(lepts.Py()+met1_py,2) ),2) );

		//---------- Basic Preselection ----------		
		// check 2 leptons same flavor
		ee = false;
		mumu = false;
		if	(abs(l1_id) == 11 && abs(l2_id) == 11) ee = true;
		if	(abs(l1_id) == 13 && abs(l2_id) == 13) mumu = true;
		// check two leptons 
		if (( !ee && !mumu ) || (ee && mumu ) ) continue;
		Eff_Two_leptons++;
		h_Nevent->SetBinContent(2,(h_Nevent->GetBinContent(2)+1.)*finWeight);
		// pt minimum for each lepton
		if( lept1.Pt() < 20 || lept2.Pt() < 20 ) continue;
		Eff_Pt++;
		h_Nevent->SetBinContent(3,(h_Nevent->GetBinContent(3)+1.)*finWeight);

		// eta fiducial cut
		if(mumu){	if(fabs(lept1.Eta()) > 2.4 || fabs(lept2.Eta()) > 2.4) continue;}
		if(ee){		if( (fabs(lept1.Eta()) >= 2.5 || (1.4442 <= fabs(lept1.Eta()) && fabs(lept1.Eta()) <= 1.566)) ||
				    (fabs(lept2.Eta()) >= 2.5 || (1.4442 <= fabs(lept2.Eta()) && fabs(lept2.Eta()) <= 1.566))) continue;}
                Eff_Eta++;

		Tree_NVertex->Fill(); //Reweighting N vertex

		//---------- Beginning Histo ----------
                if (ee){
                        hee_in_llMass->Fill(lepts.M(), finWeight);
                        hee_in_llPt->Fill(lepts.Pt(), finWeight);
                        hee_in_l1Eta->Fill(lept1.Eta(), finWeight);
                        hee_in_l2Eta->Fill(lept2.Eta(), finWeight);
                        hee_in_l1Pt->Fill(lept1.Pt(), finWeight);
                        hee_in_l2Pt->Fill(lept2.Pt(), finWeight);
                        hee_in_MET1Pt->Fill(met1_pt, finWeight);
                        hee_in_rho->Fill(rho, finWeight);
                        hee_in_nvtx->Fill(nvtx, finWeight);
                }
                else if (mumu){
                        hmumu_in_llMass->Fill(lepts.M(), finWeight);
                        hmumu_in_llPt->Fill(lepts.Pt(), finWeight);
                        hmumu_in_l1Eta->Fill(lept1.Eta(), finWeight);
                        hmumu_in_l2Eta->Fill(lept2.Eta(), finWeight);
                        hmumu_in_l1Pt->Fill(lept1.Pt(), finWeight);
                        hmumu_in_l2Pt->Fill(lept2.Pt(), finWeight);
                        hmumu_in_MET1Pt->Fill(met1_pt, finWeight);
                        hmumu_in_rho->Fill(rho, finWeight);
                        hmumu_in_nvtx->Fill(nvtx, finWeight);
                }
                h_in_llMass->Fill(lepts.M(), finWeight);
                h_in_llPt->Fill(lepts.Pt(), finWeight);
                h_in_l1Eta->Fill(lept1.Eta(), finWeight);
                h_in_l2Eta->Fill(lept2.Eta(), finWeight);
                h_in_l1Pt->Fill(lept1.Pt(), finWeight);
                h_in_l2Pt->Fill(lept2.Pt(), finWeight);
                h_in_MET1Pt->Fill(met1_pt, finWeight);
                h_in_rho->Fill(rho, finWeight);
                h_in_nvtx->Fill(nvtx, finWeight);
		h_in_phiZMet->Fill(PhiZMet, finWeight);
		h_in_MetParallel->Fill(MetParallel, finWeight);
		h_in_MetTransvers->Fill(MetTransv, finWeight);


                        if( nvtx==1 ){  h_in_MET1vtx->Fill(met1_pt, finWeight);
                        		h_in_METx1vtx->Fill(met1_px, finWeight);
                        		h_in_METy1vtx->Fill(met1_py, finWeight); }
                        if( nvtx==4 ){  h_in_MET4vtx->Fill(met1_pt, finWeight);
                                        h_in_METx4vtx->Fill(met1_px, finWeight);
                                        h_in_METy4vtx->Fill(met1_py, finWeight); }
                        if( nvtx==8 ){  h_in_MET8vtx->Fill(met1_pt, finWeight);
                                        h_in_METx8vtx->Fill(met1_px, finWeight);
                                        h_in_METy8vtx->Fill(met1_py, finWeight); }
                        if( nvtx==12 ){ h_in_MET12vtx->Fill(met1_pt, finWeight);
                                        h_in_METx12vtx->Fill(met1_px, finWeight);
                                        h_in_METy12vtx->Fill(met1_py, finWeight); }
                        if( nvtx==18 ){ h_in_MET18vtx->Fill(met1_pt, finWeight);
                                        h_in_METx18vtx->Fill(met1_px, finWeight);
                                        h_in_METy18vtx->Fill(met1_py, finWeight); }

			if( rho <= 2. ){ h_in_METx2rho->Fill(met1_px, finWeight);
					h_in_METy2rho->Fill(met1_py, finWeight); }
                        else if( rho > 2. && rho <= 4. ){ h_in_METx4rho->Fill(met1_px, finWeight);
                             		             	  h_in_METy4rho->Fill(met1_py, finWeight); }
                        else if( rho > 4. && rho <= 6. ){ h_in_METx6rho->Fill(met1_px, finWeight);
                                                          h_in_METy6rho->Fill(met1_py, finWeight); }
                        else if( rho > 6. && rho <= 8. ){ h_in_METx8rho->Fill(met1_px, finWeight);
                                                          h_in_METy8rho->Fill(met1_py, finWeight); }
                        else if( rho > 8. && rho <= 10. ){ h_in_METx10rho->Fill(met1_px, finWeight);
                                                           h_in_METy10rho->Fill(met1_py, finWeight); }
                        else if( rho > 10. && rho <= 12. ){ h_in_METx12rho->Fill(met1_px, finWeight);
                                                            h_in_METy12rho->Fill(met1_py, finWeight); }
                        else if( rho > 12. && rho <= 14. ){ h_in_METx14rho->Fill(met1_px, finWeight);
                                                            h_in_METy14rho->Fill(met1_py, finWeight); }
                        else if( rho > 14. && rho <= 16. ){ h_in_METx16rho->Fill(met1_px, finWeight);
                                                            h_in_METy16rho->Fill(met1_py, finWeight); }
                        else if( rho > 16. ){ h_in_METx18rho->Fill(met1_px, finWeight);
                                              h_in_METy18rho->Fill(met1_py, finWeight); }
		//---------- compute the kinematic ----
		isl1EB = false; //I'd like to put them in lept class
		isl2EB = false;
		if (fabs( lept1.Eta() ) < 1.4442){ 
			isl1EB = true;
			//if(abs(l1_id) == 11) l1_iso1 -= 1.;
		}
		if (fabs( lept2.Eta() ) < 1.4442){ 
			isl2EB = true;
			//if(abs(l2_id) == 11) l2_iso1 -= 1.;
		}
		l1_CRI = (l1_iso1 + l1_iso2 + l1_iso3 - rho * 0.3 * 0.3)/lept1.Pt(); 
		l2_CRI = (l2_iso1 + l2_iso2 + l2_iso3 - rho * 0.3 * 0.3)/lept2.Pt(); 
	
		//---------- start cuts --------------------	
		// check pt of the Z candidate
		if (lepts.Pt() < 30) continue; // Trigger for y+jet control sample
		Eff_Z_Pt++;
		h_Nevent->SetBinContent(4,(h_Nevent->GetBinContent(4)+1.)*finWeight);

                // Jet-Veto
                veto_Jet = false;
		TLorentzVector Jet_loop;
                for (int i = 0; i < jn; i++) {
                        Jet_loop.SetPxPyPzE(jn_px[i],jn_py[i],jn_pz[i],jn_en[i]);
                        if( Jet_loop.Pt() > 30. && fabs(Jet_loop.Eta()) < 5. )  veto_Jet = true;
                }
		if (veto_Jet) continue;
		Eff_Jet_Veto++;
		h_Nevent->SetBinContent(5,(h_Nevent->GetBinContent(5)+1.)*finWeight);

		// MET Cut
		if( met1_pt < 60. ) continue; // a 60 meno divario Data-MC
		Eff_MET++;
		h_Nevent->SetBinContent(6,(h_Nevent->GetBinContent(6)+1.)*finWeight);

		// Balance cut
		if( (met1_pt/lepts.Pt()) < 0.4 || (met1_pt/lepts.Pt()) > 1.8 ) continue; // Balance between the Pt of Z candidate and MET
		Eff_Balance++;
		h_Nevent->SetBinContent(7,(h_Nevent->GetBinContent(7)+1.)*finWeight);
		
		// check the pt resolution for the muons
		//if (mumu && (l1_ptErr/l1_pt > 0.1 || l2_ptErr/l2_pt > 0.1)) continue

		// Delta Phi Jet
		jet_eta = 0.; jet_pt = 0.;
		float Pt_app_jet = 0, Phi_hardJet = 0.;
		bool isJet_hard = false;
                for (int i = 0; i < jn; i++) {
			Jet_loop.SetPxPyPzE(jn_px[i],jn_py[i],jn_pz[i],jn_en[i]);
                        if(fabs(Jet_loop.Eta()) < 2.45 && Jet_loop.Pt() > 10. && Jet_loop.Pt() > Pt_app_jet ) {
                                Pt_app_jet = Jet_loop.Pt();
                                Phi_hardJet = Jet_loop.Phi();
				isJet_hard = true;
                        }
                }
		Eff_Jet_Phi++;
		h_Nevent->SetBinContent(8,(h_Nevent->GetBinContent(8)+1.)*finWeight);
		if( isJet_hard && (fabs(delta_phi(Phi_hardJet,met1_phi)) < 0.349) ) continue; //20 degrees

                // Delta Phi Z
		if( PhiZMet < 1.0472 ) continue; //60 degrees
		Eff_Z_Phi++;
		h_Nevent->SetBinContent(9,(h_Nevent->GetBinContent(9)+1.)*finWeight);

		// B-tagging
		isThereBJet = false;
		jet_eta = 0.; jet_pt = 0.;
		for (int i = 0; i < jn; i++) {
                        Jet_loop.SetPxPyPzE(jn_px[i],jn_py[i],jn_pz[i],jn_en[i]);
			if( Jet_loop.Pt() > 10. && jn_btag1[i] >= 1.1) {
				isThereBJet = true;
				i = jn; //close for at 1st Bjet found
			}
		}
		if (isThereBJet) continue;
		Eff_B_Veto++;
		h_Nevent->SetBinContent(10,(h_Nevent->GetBinContent(10)+1.)*finWeight);
		
		// reject events with more than 2 leptons
		if (ln > 0){
			if (abs(ln_id[0]) == 11 && sqrt(ln_px[0]*ln_px[0]+ln_py[0]*ln_py[0])>20. ) continue; //was10
			if (abs(ln_id[0]) == 13 && sqrt(ln_px[0]*ln_px[0]+ln_py[0]*ln_py[0])>20. ) continue; //was no pt requirement
		}
		Eff_Lept_Veto++;
		h_Nevent->SetBinContent(11,(h_Nevent->GetBinContent(11)+1.)*finWeight);
		
		// check the isolation of the leptons
		if	(mumu && !ee ){	if( l1_CRI > 0.15 || l2_CRI > 0.15) continue;}
		else if (ee && !mumu ){	if( l1_CRI > 0.15 || l2_CRI > 0.15) continue;}
		else	cout<<"That's impossible!"<<endl;
		Eff_ISO++;
		h_Nevent->SetBinContent(12,(h_Nevent->GetBinContent(12)+1.)*finWeight);

		// Z mass window
		if ( lepts.M() < 80 || lepts.M() > 100 ) continue;
		Eff_Z_Mass++;
		h_Nevent->SetBinContent(13,(h_Nevent->GetBinContent(13)+1.)*finWeight);


		// ZPt ranges
		if( lepts.Pt() <= 50 ){
		h_Pt50_mZ->Fill(lepts.M(), finWeight);
		}
                else if( lepts.Pt() > 50 && lepts.Pt() <= 100){
		h_Pt100_mZ->Fill(lepts.M(), finWeight);
                }
                else if( lepts.Pt() > 100 && lepts.Pt() <= 150){
		h_Pt150_mZ->Fill(lepts.M(), finWeight);
                }
		else{
		h_PtMax_mZ->Fill(lepts.M(), finWeight);
		}
		// Fill histos
		if (ee){
			hee_llMass->Fill(lepts.M(), finWeight);
			hee_llPt->Fill(lepts.Pt(), finWeight);
			hee_l1Eta->Fill(lept1.Eta(), finWeight);
			hee_l2Eta->Fill(lept2.Eta(), finWeight);
			hee_l1Pt->Fill(lept1.Pt(), finWeight);
			hee_l2Pt->Fill(lept2.Pt(), finWeight);
			hee_MET1Pt->Fill(met1_pt, finWeight);
			hee_rho->Fill(rho, finWeight);
                        hee_nvtx->Fill(nvtx, finWeight);
                        hee_mZZt->Fill(mZZt, finWeight);
			Eff_FinalEE++;
		}
		else if (mumu){
			hmumu_llMass->Fill(lepts.M(), finWeight);
			hmumu_llPt->Fill(lepts.Pt(), finWeight);
			hmumu_l1Eta->Fill(lept1.Eta(), finWeight);
			hmumu_l2Eta->Fill(lept2.Eta(), finWeight);
			hmumu_l1Pt->Fill(lept1.Pt(), finWeight);
			hmumu_l2Pt->Fill(lept2.Pt(), finWeight);
			hmumu_MET1Pt->Fill(met1_pt, finWeight);
			hmumu_rho->Fill(rho, finWeight);
			hmumu_nvtx->Fill(nvtx, finWeight);
                        hmumu_mZZt->Fill(mZZt, finWeight);
			Eff_FinalMuMu++;
		}
                h_llMass->Fill(lepts.M(), finWeight);
                h_llPt->Fill(lepts.Pt(), finWeight);
                h_l1Eta->Fill(lept1.Eta(), finWeight);
                h_l2Eta->Fill(lept2.Eta(), finWeight);
                h_l1Pt->Fill(lept1.Pt(), finWeight);
                h_l2Pt->Fill(lept2.Pt(), finWeight);
                h_MET1Pt->Fill(met1_pt, finWeight);
                h_rho->Fill(rho, finWeight);
                h_nvtx->Fill(nvtx, finWeight);
                h_mZZt->Fill(mZZt, finWeight);
		h_nvtx->Fill(nvtx, finWeight);
		h_phiZMet->Fill(PhiZMet, finWeight);
		h_MetParallel->Fill(MetParallel, finWeight);
		h_MetTransvers->Fill(MetTransv, finWeight);
	}// for entries

//-------------RSM from MET vs vtx
if( (h_in_METx18vtx->GetEntries() > 0.) && (h_in_METx12vtx->GetEntries() > 0.) ){
	h_in_METx1vtx->Fit("gaus");	TF1 *fit_x1 = h_in_METx1vtx->GetFunction("gaus");	Double_t RMS_x1 = fit_x1->GetParameter("Sigma");
	h_in_METx4vtx->Fit("gaus");	TF1 *fit_x4 = h_in_METx4vtx->GetFunction("gaus");	Double_t RMS_x4 = fit_x4->GetParameter("Sigma");
	h_in_METx8vtx->Fit("gaus");	TF1 *fit_x8 = h_in_METx8vtx->GetFunction("gaus");	Double_t RMS_x8 = fit_x8->GetParameter("Sigma");
	h_in_METx12vtx->Fit("gaus");	TF1 *fit_x12 = h_in_METx12vtx->GetFunction("gaus");	Double_t RMS_x12 = fit_x12->GetParameter("Sigma");
	h_in_METx18vtx->Fit("gaus");	TF1 *fit_x18 = h_in_METx18vtx->GetFunction("gaus");	Double_t RMS_x18 = fit_x18->GetParameter("Sigma");

	h_RMS_vtx->SetBinContent(1,RMS_x1);
	h_RMS_vtx->SetBinContent(4,RMS_x4);
	h_RMS_vtx->SetBinContent(8,RMS_x8);
	h_RMS_vtx->SetBinContent(12,RMS_x12);
	h_RMS_vtx->SetBinContent(18,RMS_x18);	
	
	g_RMS_vtx->SetPoint(1,1,RMS_x1); g_RMS_vtx->SetPoint(2,4,RMS_x4); g_RMS_vtx->SetPoint(3,8,RMS_x8); g_RMS_vtx->SetPoint(4,12,RMS_x12); g_RMS_vtx->SetPoint(5,18,RMS_x18);

	TF1 *myfit = new TF1("myfit","[0] + [1]*x^0.5", -20, 20);
	myfit->SetParameter(0, 7);
	myfit->SetParameter(1, 1);
	h_RMS_vtx->Fit("myfit");
	g_RMS_vtx->Fit("myfit");
	g_RMS_vtx->Write();
}
	dir->GetList()->Write();
	Tree_NVertex->Write();
	file->Close();
	dir->GetList()->Delete();


//-------------EFFICIENCY
	cout << endl;	
	cout << "Preselection: " << Eff_Preselection << endl;
	cout << "Two_leptons: " << Eff_Two_leptons << "  Eff_tot: " << Eff_Two_leptons/Eff_Preselection << "  Eff_parz: " << Eff_Two_leptons/Eff_Preselection << endl;
	cout << "Pt: " << Eff_Pt <<  "  Eff_tot: " << Eff_Pt/Eff_Preselection << "  Eff_parz: " << Eff_Pt/Eff_Two_leptons << endl;
	cout << "Eta: " << Eff_Eta <<  "  Eff_tot: " << Eff_Eta/Eff_Preselection << "  Eff_parz: " << Eff_Eta/Eff_Pt << endl;
	cout << "Z_Pt: " << Eff_Z_Pt <<  "  Eff_tot: " << Eff_Z_Pt/Eff_Preselection << "  Eff_parz: " << Eff_Z_Pt/Eff_Eta << endl;
        cout << "Jet_Veto: " << Eff_Jet_Veto <<  "  Eff_tot: " << Eff_Jet_Veto/Eff_Preselection << "  Eff_parz: " << Eff_Jet_Veto/Eff_Z_Pt << endl;
        cout << "MET: " << Eff_MET <<  "  Eff_tot: " << Eff_MET/Eff_Preselection << "  Eff_parz: " << Eff_MET/Eff_Jet_Veto << endl;
        cout << "Balance: " << Eff_Balance <<  "  Eff_tot: " << Eff_Balance/Eff_Preselection << "  Eff_parz: " << Eff_Balance/Eff_MET << endl;
        cout << "Jet_Phi: " << Eff_Jet_Phi <<  "  Eff_tot: " << Eff_Jet_Phi/Eff_Preselection << "  Eff_parz: " << Eff_Jet_Phi/Eff_Balance << endl;
        cout << "Z_Phi: " << Eff_Z_Phi <<  "  Eff_tot: " << Eff_Z_Phi/Eff_Preselection << "  Eff_parz: " << Eff_Z_Phi/Eff_Jet_Phi << endl;
        cout << "B_Veto: " << Eff_B_Veto <<  "  Eff_tot: " << Eff_B_Veto/Eff_Preselection << "  Eff_parz: " << Eff_B_Veto/Eff_Z_Phi << endl;
        cout << "Lept_Veto: " << Eff_Lept_Veto <<  "  Eff_tot: " << Eff_Lept_Veto/Eff_Preselection << "  Eff_parz: " << Eff_Lept_Veto/Eff_B_Veto << endl;
        cout << "ISO: " << Eff_ISO <<  "  Eff_tot: " << Eff_ISO/Eff_Preselection << "  Eff_parz: " << Eff_ISO/Eff_Lept_Veto << endl;
        cout << "Z_Mass: " << Eff_Z_Mass <<  "  Eff_tot: " << Eff_Z_Mass/Eff_Preselection << "  Eff_parz: " << Eff_Z_Mass/Eff_ISO << endl;
	cout << endl;
	cout << "Num EE = " << Eff_FinalEE << "  Num MuMu = " << Eff_FinalMuMu << endl;
}

// Delta Phi
inline double delta_phi(double phi1, double phi2) {
  double dphi = TMath::Abs(phi1 - phi2);
  return ( dphi <= TMath::Pi()  ? dphi : TMath::TwoPi() - dphi );
}
