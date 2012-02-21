#define ZZ_Finalize_cxx
#include "ZZ_Finalize.h"
#include <TH2.h>
#include <TF1.h>
#include <TGraph.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <string.h>
#include <fstream>
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
inline double min(double n1, double n2);
double IsoIdCorr( int l_id, TLorentzVector lept );
double TrigCorr( int l_id, TLorentzVector lept );

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

	fstream f1; 
	f1.open("Final_Eff_ev.txt", ios::out | ios::app | ios::binary);
	if(!f1) { cout<< "Impossibile open Final_Eff_ev.txt."; 
	exit(1);}

	//#include "Include/higgsDeclaration.h"

	TH1F * h_Study		= new TH1F("h_Study", "Study", 30, 0., 3.);		                                h_Study->Sumw2();

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
        TH1F * hee_in_njet      = new TH1F("hee_in_njet", "Number Jet", 10, 0., 10.);					hee_in_njet->Sumw2();	
        TH1F * hee_in_Iso1      = new TH1F("hee_in_Iso1", "Tracker Iso, 1 lept", 40, 0., 30.);				hee_in_Iso1->Sumw2();
        TH1F * hee_in_Iso2      = new TH1F("hee_in_Iso2", "ECAL Iso, 1 lept", 40, 0., 30);				hee_in_Iso2->Sumw2();
        TH1F * hee_in_Iso3      = new TH1F("hee_in_Iso3", "HCAL Iso, 1 lept", 40, 0., 30.);				hee_in_Iso3->Sumw2();
        TH1F * hee_in_Iso       = new TH1F("hee_in_Iso", "Global Iso, 1 lept", 20, -0.1, 0.17);				hee_in_Iso->Sumw2();

        TH1F * hee_llMass       = new TH1F("hee_llMass", "Dilepton Invariant mass", 20, 75., 105.);			hee_llMass->Sumw2();
        TH1F * hee_llPt         = new TH1F("hee_llPt", "Transvers momentum of lepton pair", 30, 25., 325.);		hee_llPt->Sumw2();
        TH1F * hee_l1Pt         = new TH1F("hee_l1Pt", "Transvers momentum of lepton 1", 20, 20., 200.);		hee_l1Pt->Sumw2();
        TH1F * hee_l2Pt         = new TH1F("hee_l2Pt", "Transvers momentum of lepton 2", 25, 20., 200.);		hee_l2Pt->Sumw2();
        TH1F * hee_MET1Pt       = new TH1F("hee_MET1Pt", "PF Missing transvers energy", 30, 50., 200.);			hee_MET1Pt->Sumw2();
        TH1F * hee_l1Eta        = new TH1F("hee_l1Eta", "#eta lepton 1", 15, -2., 2.);					hee_l1Eta->Sumw2();
        TH1F * hee_l2Eta        = new TH1F("hee_l2Eta", "#eta lepton 2", 15, -2., 2.);					hee_l2Eta->Sumw2();
        TH1F * hee_rho          = new TH1F("hee_rho", "Rho variable", 15, 0., 15.);					hee_rho->Sumw2();
        TH1F * hee_nvtx         = new TH1F("hee_nvtx", "Number of Good vertex", 20, 0., 20.);				hee_nvtx->Sumw2();
        TH1F * hee_njet         = new TH1F("hee_njet", "Number Jet", 10, 0., 10.);       	                        hee_njet->Sumw2();
        TH1F * hee_mZZt         = new TH1F("hee_mZZt", "Di-Boson Mass", 50, 150., 500.);				hee_mZZt->Sumw2();

	TH1F * hee_cut_llPt     = new TH1F("hee_cut_llPt", "Transvers momentum of lepton pair", 30, 10., 325.);         hee_cut_llPt->Sumw2();
	TH1F * hee_cut_njet     = new TH1F("hee_cut_njet", "Number Jet", 10, 0., 10.);                                  hee_cut_njet->Sumw2();
	TH1F * hee_cut_MET1Pt   = new TH1F("hee_cut_MET1Pt", "PF Missing transvers energy", 50, 0., 200.);              hee_cut_MET1Pt->Sumw2();
	TH1F * hee_cut_MET1Pt_PRO   = new TH1F("hee_cut_MET1Pt_PRO", "PF Missing transvers energy", 50, 0., 200.);      hee_cut_MET1Pt_PRO->Sumw2();
	TH1F * hee_cut_Balan    = new TH1F("hee_cut_Balan", "Balance cut", 20, 0.5, 2.5);   		            	hee_cut_Balan->Sumw2();
	TH1F * hee_cut_PhiJet   = new TH1F("hee_cut_PhiJet", "Phi Jet-Met", 15, 0., 3.14);  		            	hee_cut_PhiJet->Sumw2();
	TH1F * hee_cut_PhiZ     = new TH1F("hee_cut_PhiZ", "Phi Z-Met", 20, 1.5, 3.14);  		            	hee_cut_PhiZ->Sumw2();
	TH1F * hee_cut_Btag     = new TH1F("hee_cut_Btag", "TCHE", 15, -5., 6.);  		 	           	hee_cut_Btag->Sumw2();
	TH1F * hee_cut_Nlep     = new TH1F("hee_cut_Nlep", "Num of leptons", 5, 0., 5.);  		 	       	hee_cut_Nlep->Sumw2();
	TH1F * hee_cut_llMass   = new TH1F("hee_cut_llMass", "Dilepton Invariant mass", 40, 50., 130.);			hee_cut_llMass->Sumw2();
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
        TH1F * hmumu_in_njet    = new TH1F("hmumu_in_njet", "Number Jet", 10, 0., 10.);      	                        hmumu_in_njet->Sumw2();
        TH1F * hmumu_in_Iso1    = new TH1F("hmumu_in_Iso1", "Tracker Iso, 1 lept", 40, 0., 30.);                        hmumu_in_Iso1->Sumw2();
        TH1F * hmumu_in_Iso2    = new TH1F("hmumu_in_Iso2", "ECAL Iso, 1 lept", 40, 0., 30.);                           hmumu_in_Iso2->Sumw2();
        TH1F * hmumu_in_Iso3    = new TH1F("hmumu_in_Iso3", "HCAL Iso, 1 lept", 40, 0., 30);                            hmumu_in_Iso3->Sumw2();
        TH1F * hmumu_in_Iso     = new TH1F("hmumu_in_Iso", "GLobal Iso, 1 lept", 20, -0.1, 0.17);                       hmumu_in_Iso->Sumw2();

        TH1F * hmumu_llMass     = new TH1F("hmumu_llMass", "Invariant mass of lepton pair", 20, 75., 105.);		hmumu_llMass->Sumw2();
        TH1F * hmumu_llPt       = new TH1F("hmumu_llPt", "Transvers momentum of lepton pair", 30, 25., 325.);		hmumu_llPt->Sumw2();
        TH1F * hmumu_l1Pt       = new TH1F("hmumu_l1Pt", "Transvers momentum of lepton 1", 20, 20., 200.);		hmumu_l1Pt->Sumw2();
        TH1F * hmumu_l2Pt       = new TH1F("hmumu_l2Pt", "Transvers momentum of lepton 2", 25, 20., 200.);		hmumu_l2Pt->Sumw2();
        TH1F * hmumu_MET1Pt     = new TH1F("hmumu_MET1Pt", "PF Missing transvers energy", 30, 50., 200.);		hmumu_MET1Pt->Sumw2();
        TH1F * hmumu_l1Eta      = new TH1F("hmumu_l1Eta", "#eta lepton 1", 15, -2., 2.);				hmumu_l1Eta->Sumw2();
        TH1F * hmumu_l2Eta      = new TH1F("hmumu_l2Eta", "#eta lepton 2", 15, -2., 2.);				hmumu_l2Eta->Sumw2();
        TH1F * hmumu_rho        = new TH1F("hmumu_rho", "Rho variable", 15, 0., 15.);					hmumu_rho->Sumw2();
        TH1F * hmumu_nvtx       = new TH1F("hmumu_nvtx", "Number of Good vertex", 20, 0., 20.);				hmumu_nvtx->Sumw2();
        TH1F * hmumu_njet       = new TH1F("hmumu_njet", "Number Jet", 10, 0., 10.);                               	hmumu_njet->Sumw2();
        TH1F * hmumu_mZZt       = new TH1F("hmumu_mZZt", "Di-Boson Mass", 50, 150., 500.);				hmumu_mZZt->Sumw2();

        TH1F * hmumu_cut_llPt     = new TH1F("hmumu_cut_llPt", "Transvers momentum of lepton pair", 30, 10., 325.);         hmumu_cut_llPt->Sumw2();
	TH1F * hmumu_cut_njet     = new TH1F("hmumu_cut_njet", "Number Jet", 10, 0., 10.);                                  hmumu_cut_njet->Sumw2();
        TH1F * hmumu_cut_MET1Pt   = new TH1F("hmumu_cut_MET1Pt", "PF Missing transvers energy", 50, 0., 200.);              hmumu_cut_MET1Pt->Sumw2();
	TH1F * hmumu_cut_MET1Pt_PRO   = new TH1F("hmumu_cut_MET1Pt_PRO", "PF Missing transvers energy", 50, 0., 200.);	    hmumu_cut_MET1Pt_PRO->Sumw2();
        TH1F * hmumu_cut_Balan    = new TH1F("hmumu_cut_Balan", "Balance cut", 20, 0.5, 2.5);                               hmumu_cut_Balan->Sumw2();
        TH1F * hmumu_cut_PhiJet   = new TH1F("hmumu_cut_PhiJet", "Phi Jet-Met", 15, 0., 3.14);	                            hmumu_cut_PhiJet->Sumw2();
        TH1F * hmumu_cut_PhiZ     = new TH1F("hmumu_cut_PhiZ", "Phi Z-Met", 20, 1.5, 3.14);       			    hmumu_cut_PhiZ->Sumw2();
        TH1F * hmumu_cut_Btag     = new TH1F("hmumu_cut_Btag", "TCHE", 15, -5., 6.);                                        hmumu_cut_Btag->Sumw2();
        TH1F * hmumu_cut_Nlep     = new TH1F("hmumu_cut_Nlep", "Num of leptons", 5, 0., 5.);                                hmumu_cut_Nlep->Sumw2();
        TH1F * hmumu_cut_llMass   = new TH1F("hmumu_cut_llMass", "Dilepton Invariant mass", 40, 50., 130.);                 hmumu_cut_llMass->Sumw2();

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
        TH1F * h_in_njet      = new TH1F("h_in_njet", "Number Jet", 10, 0., 10.);                 	              	h_in_njet->Sumw2();
        TH1F * h_in_Iso1      = new TH1F("h_in_Iso1", "Tracker Iso, 1 lept", 40, 0., 30.);                       	h_in_Iso1->Sumw2();
        TH1F * h_in_Iso2      = new TH1F("h_in_Iso2", "ECAL Iso, 1 lept", 40, 0., 30.);                 	        h_in_Iso2->Sumw2();
        TH1F * h_in_Iso3      = new TH1F("h_in_Iso3", "HCAL Iso, 1 lept", 40, 0., 30.);          	                h_in_Iso3->Sumw2();
        TH1F * h_in_Iso       = new TH1F("h_in_Iso", "Global Iso, 1 lept", 20, -0.1, 0.17);	                        h_in_Iso->Sumw2();
        TH1F * h_in_phiZMet   = new TH1F("h_in_phiZMet", "Delta Phi Met Z", 30, 0., 3.142);				h_in_phiZMet->Sumw2();
        TH1F * h_in_MetParallel  = new TH1F("h_in_MetParallel", "Met Z parallel", 100, -150., 150);			h_in_MetParallel->Sumw2();
        TH1F * h_in_MetTransvers = new TH1F("h_in_MetTransvers", "Met Z transvers", 100, 0., 300);			h_in_MetTransvers->Sumw2();
        TH1F * h_in_MetRed_IND = new TH1F("h_in_MetRed_IND", "Met IND", 50, 0., 200.);					h_in_MetRed_IND->Sumw2();
        TH1F * h_in_MetRed_D0 = new TH1F("h_in_MetRed_D0", "Met D0", 50, 0., 200.);					h_in_MetRed_D0->Sumw2();
        TH1F * h_in_MetRed_MIN = new TH1F("h_in_MetRed_MIN", "Met MIN", 50, 0., 200.);					h_in_MetRed_MIN->Sumw2();

        TH1F * h_llMass       = new TH1F("h_llMass", "Dilepton Invariant mass", 20, 75., 105.);				h_llMass->Sumw2();
        TH1F * h_llPt         = new TH1F("h_llPt", "Transvers momentum of lepton pair", 30, 25., 325.);			h_llPt->Sumw2();
        TH1F * h_l1Pt         = new TH1F("h_l1Pt", "Transvers momentum of lepton 1", 20, 20., 200.);			h_l1Pt->Sumw2();
        TH1F * h_l2Pt         = new TH1F("h_l2Pt", "Transvers momentum of lepton 2", 25, 20., 200.);			h_l2Pt->Sumw2();
        TH1F * h_MET1Pt       = new TH1F("h_MET1Pt", "PF Missing transvers energy", 30, 50., 200.);			h_MET1Pt->Sumw2();
        TH1F * h_l1Eta        = new TH1F("h_l1Eta", "#eta lepton 1", 15, -2., 2.);					h_l1Eta->Sumw2();
        TH1F * h_l2Eta        = new TH1F("h_l2Eta", "#eta lepton 2", 15, -2., 2.);					h_l2Eta->Sumw2();
        TH1F * h_rho          = new TH1F("h_rho", "Rho variable", 15, 0., 15.);						h_rho->Sumw2();
        TH1F * h_nvtx         = new TH1F("h_nvtx", "Number of Good vertex", 20, 0., 20.);				h_nvtx->Sumw2();
        TH1F * h_njet         = new TH1F("h_njet", "Number Jet", 10, 0., 10.);     	            	              	h_njet->Sumw2();
        TH1F * h_phiZMet      = new TH1F("h_phiZMet", "Delta Phi Met Z", 30, 0., 3.142);				h_phiZMet->Sumw2();

        TH1F * h_cut_llPt     = new TH1F("h_cut_llPt", "Transvers momentum of lepton pair", 30, 10., 325.);         h_cut_llPt->Sumw2();
        TH1F * h_cut_njet     = new TH1F("h_cut_njet", "Number Jet", 10, 0., 10.);                                  h_cut_njet->Sumw2();
        TH1F * h_cut_MET1Pt   = new TH1F("h_cut_MET1Pt", "PF Missing transvers energy", 50, 0., 200.);              h_cut_MET1Pt->Sumw2();
	TH1F * h_cut_MET1Pt_PRO   = new TH1F("h_cut_MET1Pt_PRO", "PF Missing transvers energy", 50, 0., 200.);      h_cut_MET1Pt_PRO->Sumw2();
        TH1F * h_cut_Balan    = new TH1F("h_cut_Balan", "Balance cut", 20, 0.5, 2.5);                               h_cut_Balan->Sumw2();
        TH1F * h_cut_PhiJet   = new TH1F("h_cut_PhiJet", "Phi Jet-Met", 15, 0., 3.14);       	                    h_cut_PhiJet->Sumw2();
        TH1F * h_cut_PhiZ     = new TH1F("h_cut_PhiZ", "Phi Z-Met", 20, 1.5, 3.14);				    h_cut_PhiZ->Sumw2();
        TH1F * h_cut_Btag     = new TH1F("h_cut_Btag", "TCHE", 15, -5., 6.);                                        h_cut_Btag->Sumw2();
        TH1F * h_cut_Nlep     = new TH1F("h_cut_Nlep", "Num of leptons", 5, 0., 5.);                                h_cut_Nlep->Sumw2();
        TH1F * h_cut_llMass   = new TH1F("h_cut_llMass", "Dilepton Invariant mass", 40, 50., 130.);                 h_cut_llMass->Sumw2();

        TH1F * h_MetParallel  = new TH1F("h_MetParallel", "Met Z parallel", 20, 40., 150);				h_MetParallel->Sumw2();
        TH1F * h_MetTransvers = new TH1F("h_MetTransvers", "Met Z transvers", 20, 0., 70);				h_MetTransvers->Sumw2();
        TH1F * h_mZZt         = new TH1F("h_mZZt", "Di-Boson Mass", 30, 150., 500.);					h_mZZt->Sumw2();
// Pt Range
        TH1F * h_Pt50_mZ       = new TH1F("h_Pt50_mZ", "Pt<50, mZ mass", 20, 75., 110.);				h_Pt50_mZ->Sumw2();
        TH1F * h_Pt100_mZ      = new TH1F("h_Pt100_mZ", "Pt<100, mZ mass", 20, 75., 110.);				h_Pt100_mZ->Sumw2();
        TH1F * h_Pt150_mZ      = new TH1F("h_Pt150_mZ", "Pt<150, mZ mass", 20, 75., 110.);				h_Pt150_mZ->Sumw2();
        TH1F * h_PtMax_mZ      = new TH1F("h_PtMax_mZ", "Pt Max, mZ mass", 20, 75., 110.);				h_PtMax_mZ->Sumw2();
	//ISO_vs_VTX
        TH1F * h_in_Iso1_1vx  = new TH1F("h_in_Iso1_1vx", "Tracker Iso, 1 lept, 1 vtx", 20, 0., 5.);                      h_in_Iso1_1vx->Sumw2();
        TH1F * h_in_Iso2_1vx  = new TH1F("h_in_Iso2_1vx", "ECAL Iso, 1 lept, 1 vtx", 20, 0., 1.5);                        h_in_Iso2_1vx->Sumw2();
        TH1F * h_in_Iso3_1vx  = new TH1F("h_in_Iso3_1vx", "HCAL Iso, 1 lept, 1 vtx", 20, 0., 1.);                         h_in_Iso3_1vx->Sumw2();
        TH1F * h_in_Iso1_8vx  = new TH1F("h_in_Iso1_8vx", "Tracker Iso, 1 lept, 8 vtx", 20, 0., 5.);                      h_in_Iso1_8vx->Sumw2();
        TH1F * h_in_Iso2_8vx  = new TH1F("h_in_Iso2_8vx", "ECAL Iso, 1 lept, 8 vtx", 20, 0., 1.5);                        h_in_Iso2_8vx->Sumw2();
        TH1F * h_in_Iso3_8vx  = new TH1F("h_in_Iso3_8vx", "HCAL Iso, 1 lept, 8 vtx", 20, 0., 1.);                         h_in_Iso3_8vx->Sumw2();
        TH1F * h_in_Iso1_12vx = new TH1F("h_in_Iso1_12vx", "Tracker Iso, 1 lept, 12 vtx", 20, 0., 5.);                    h_in_Iso1_12vx->Sumw2();
        TH1F * h_in_Iso2_12vx = new TH1F("h_in_Iso2_12vx", "ECAL Iso, 1 lept, 12 vtx", 20, 0., 1.5);                      h_in_Iso2_12vx->Sumw2();
        TH1F * h_in_Iso3_12vx = new TH1F("h_in_Iso3_12vx", "HCAL Iso, 1 lept, 12 vtx", 20, 0., 1.);                       h_in_Iso3_12vx->Sumw2();
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
        //MET_Charge_vs_VTX
        //TH1F * h_in_METCharge1vtx    = new TH1F("h_in_METCharge1vtx", "MET Charge distr. with 1 vertex", 40, 0., 60.);       	   h_in_METCharge1vtx->Sumw2();
        //TH1F * h_in_METCharge4vtx    = new TH1F("h_in_METCharge4vtx", "MET Charge distr. with 4 vertex", 40, 0., 60.);             h_in_METCharge4vtx->Sumw2();
        //TH1F * h_in_METCharge8vtx    = new TH1F("h_in_METCharge8vtx", "MET Charge distr. with 8 vertex", 40, 0., 60.);             h_in_METCharge8vtx->Sumw2();
        //TH1F * h_in_METCharge12vtx    = new TH1F("h_in_METCharge12vtx", "MET Charge distr. with 12 vertex", 40, 0., 60.);          h_in_METCharge12vtx->Sumw2();
        //TH1F * h_in_METCharge18vtx    = new TH1F("h_in_METCharge18vtx", "MET Charge distr. with 18 vertex", 40, 0., 60.);          h_in_METCharge18vtx->Sumw2();

        TH1F * NvtxnoW         = new TH1F("NvtxnoW", "Number of Good vertex", 20, 0., 20.);				NvtxnoW->Sumw2();
        TH1F * NvtxyesW        = new TH1F("NvtxyesW", "Number of Good vertex", 20, 0., 20.);				NvtxyesW->Sumw2();
        TH1F * h_RMS_vtx       = new TH1F("h_RMS_vtx", "MET on x RMS vs N vertex", 20, 0., 20.);		h_RMS_vtx->Sumw2();
        TH1F * h_Iso_vtx       = new TH1F("h_Iso_vtx", "Iso vs N vertex", 20, 0., 20.);				h_Iso_vtx->Sumw2();
	TGraph * g_RMS_vtx     = new TGraph(5); g_RMS_vtx->SetTitle("g_RMS_vtx");
	
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

	Float_t jet_eta = 0.;
	Float_t jet_pt = 0.;

        Float_t vtxweight[20]={1.,1.,1.,1.,1.,1.,1.,1.,1.,1.,1.,1.,1.,1.,1.,1.,1.,1.,1.,1.};
	//Float_t vtxweight[20]={1.,0.634276,0.678203,0.7131,0.743639,0.773336,0.810534,0.856799,0.916266,0.991299,1.08157,1.21162,1.34877,1.49695,1.67696,1.9008,2.1098,2.397,2.80421,3.42399};

	// TTREE
	TTree * Tree_NVertex = new TTree("Tree_NVertex","Tree for re-weighting N verteces");
	TTree * Tree_AllVariables = new TTree("Tree_AllVariables","All variables to plot");
	TTree * Tree_Met_Eff = new TTree("Tree_Met_Eff","Study of Met Efficiency");

	Float_t Nvtx, finWeight = 1.;
	Float_t PhiZMet, met1_px, met1_py, MetParallel, MetTransv, met_Red_pt_IND, met_Red_pt_D0, met_Red_pt_MIN, met_WW, mZZt, l1_CRI, l2_CRI;

	Tree_NVertex->Branch("Nvtx", &Nvtx, "Nvtx/I");
	Tree_NVertex->Branch("finWeight", &finWeight, "finWeight/F");

        Tree_AllVariables->Branch("Nvtx", &Nvtx, "Nvtx/I");
        Tree_AllVariables->Branch("finWeight", &finWeight, "finWeight/F");
        Tree_AllVariables->Branch("l1_px", &l1_px, "l1_px/F");
        Tree_AllVariables->Branch("l1_py", &l1_py, "l1_py/F");
        Tree_AllVariables->Branch("l1_pz", &l1_pz, "l1_pz/F");
        Tree_AllVariables->Branch("l1_en", &l1_en, "l1_en/F");
        Tree_AllVariables->Branch("l2_px", &l2_px, "l2_px/F");
        Tree_AllVariables->Branch("l2_py", &l2_py, "l2_py/F");
        Tree_AllVariables->Branch("l2_pz", &l2_pz, "l2_pz/F");
        Tree_AllVariables->Branch("l2_en", &l2_en, "l2_en/F");
        Tree_AllVariables->Branch("met1_pt", &met1_pt, "met1_pt/F");
        Tree_AllVariables->Branch("met1_phi", &met1_phi, "met1_phi/F");
        Tree_AllVariables->Branch("PhiZMet", &PhiZMet, "PhiZMet/F");
        Tree_AllVariables->Branch("MetParallel", &MetParallel, "MetParallel/F");
        Tree_AllVariables->Branch("MetTransv", &MetTransv, "MetTransv/F");
        Tree_AllVariables->Branch("met_Red_px_IND", &met_Red_pt_IND, "met_Red_pt_IND/F");
        Tree_AllVariables->Branch("met_Red_py_IND", &met_Red_pt_IND, "met_Red_pt_IND/F");
        Tree_AllVariables->Branch("met_Red_pt_IND", &met_Red_pt_IND, "met_Red_pt_IND/F");
        Tree_AllVariables->Branch("met_Red_px_D0", &met_Red_pt_D0, "met_Red_pt_D0/F");
        Tree_AllVariables->Branch("met_Red_py_D0", &met_Red_pt_D0, "met_Red_pt_D0/F");
        Tree_AllVariables->Branch("met_Red_pt_D0", &met_Red_pt_D0, "met_Red_pt_D0/F");
        Tree_AllVariables->Branch("met_Red_px_MIN", &met_Red_pt_MIN, "met_Red_pt_MIN/F");
        Tree_AllVariables->Branch("met_Red_py_MIN", &met_Red_pt_MIN, "met_Red_pt_MIN/F");
        Tree_AllVariables->Branch("met_Red_pt_MIN", &met_Red_pt_MIN, "met_Red_pt_MIN/F");
        Tree_AllVariables->Branch("met_WW", &met_WW, "met_WW/F");
        Tree_AllVariables->Branch("mZZt", &mZZt, "mZZt/F");
        Tree_AllVariables->Branch("l1_iso1", &l1_iso1, "l1_iso1/F");
        Tree_AllVariables->Branch("l1_iso2", &l1_iso2, "l1_iso2/F");
        Tree_AllVariables->Branch("l1_iso3", &l1_iso3, "l1_iso3/F");
        Tree_AllVariables->Branch("l1_CRI", &l1_CRI, "l1_CRI/F");
        Tree_AllVariables->Branch("l2_CRI", &l2_CRI, "l2_CRI/F");
        //TTree* Tree_All_Final = Tree_AllVariables->CloneTree();

	Tree_Met_Eff->Branch("finWeight", &finWeight, "finWeight/F");
	Tree_Met_Eff->Branch("met1_pt", &met1_pt, "met1_pt/F");
	Tree_Met_Eff->Branch("met_Red_pt_IND", &met_Red_pt_IND, "met_Red_pt_IND/F");
	Tree_Met_Eff->Branch("met_Red_pt_D0", &met_Red_pt_D0, "met_Red_pt_D0/F");
	Tree_Met_Eff->Branch("met_Red_pt_MIN", &met_Red_pt_MIN, "met_Red_pt_MIN/F");
	Tree_Met_Eff->Branch("met_WW", &met_WW, "met_WW/F");

	// event loop
	for (Long64_t jentry=0; jentry<nentries;jentry++) {
		if( (jentry) % 1000000 ==0 )  cout << "Event: " << jentry << "/" << nentries << endl;
		Long64_t ientry = LoadTree(jentry); //Set curren entry (-2 if it doesn't exist)
		if (ientry < 0) break;
		nb = fChain->GetEntry(jentry);   nbytes += nb;	

                //---------- Define Variables ----------           
                TLorentzVector lept1, lept2, lepts;
                lept1.SetPxPyPzE(l1_px,l1_py,l1_pz,l1_en);  
                lept2.SetPxPyPzE(l2_px,l2_py,l2_pz,l2_en);
                lepts = lept1 + lept2;
		PhiZMet = delta_phi(met1_phi,lepts.Phi());
		met1_px = met1_pt*cos(met1_phi);
		met1_py = met1_pt*sin(met1_phi);
		MetParallel = -met1_pt*cos(PhiZMet);
		MetTransv = met1_pt*sin(PhiZMet);
		met_Red_pt_IND = sqrt(pow(met_Red_px_IND,2)+pow(met_Red_py_IND,2));
		met_Red_pt_D0 = sqrt(pow(met_Red_px_D0,2)+pow(met_Red_py_D0,2));
		met_Red_pt_MIN = sqrt(pow(met_Red_px_MIN,2)+pow(met_Red_py_MIN,2));

		Nvtx = nvtx;// For the TTree for nvtx reweighting
		mZZt = sqrt( pow( sqrt(pow(lepts.M(),2)+pow(lepts.Pt(),2)) + sqrt(pow(lepts.M(),2)+pow(met1_pt,2)) ,2) - pow(sqrt( pow(lepts.Px()+met1_px,2)+pow(lepts.Py()+met1_py,2) ),2) );

		// reweighting for pile up & Nvetx
		finWeight = 1.;
		if ( isData_ == 0 ){
                float l1Reco = IsoIdCorr( l1_id, lept1 ),	l2Reco = IsoIdCorr( l2_id, lept2 );
		float eeTrigger = 1., mumuTrigger = 0.92;
		mumuTrigger = TrigCorr( l1_id, lept1 );
		    if      (abs(l1_id) == 11 && abs(l2_id) == 11) 	finWeight = Scaling_*weight*Norm_*eeTrigger;//*l1Reco*l2Reco;
		    else if (abs(l1_id) == 13 && abs(l2_id) == 13) 	finWeight = Scaling_*weight*Norm_*mumuTrigger;//*l1Reco*l2Reco;
		    else 						finWeight = Scaling_*weight*Norm_;
		  if ( nvtx < 20 ) {  finWeight = finWeight * vtxweight[nvtx]; }
		  if ( nvtx >= 20 ){  finWeight = finWeight * vtxweight[19];   }
		}
		// Normalization PU weight
		NvtxnoW->Fill(nvtx,Scaling_); 
		NvtxyesW->Fill(nvtx,Scaling_*weight); 

		Eff_Preselection+=finWeight;

		//---------- Basic Preselection ----------		
		// check 2 leptons same flavor
		ee = false;
		mumu = false;
		if	(abs(l1_id) == 11 && abs(l2_id) == 11) ee = true;
		if	(abs(l1_id) == 13 && abs(l2_id) == 13) mumu = true;
		// check two leptons 
		if (( !ee && !mumu ) || (ee && mumu ) ) continue;
		Eff_Two_leptons+=finWeight;
		// pt minimum for each lepton
		if( lept1.Pt() < lept1Pt_ || lept2.Pt() < lept2Pt_ ) continue; 
		Eff_Pt+=finWeight;

		// eta fiducial cut
		if(mumu){	if(fabs(lept1.Eta()) > EtaMu_ || fabs(lept2.Eta()) > EtaMu_) continue;}
		if(ee){		if( (fabs(lept1.Eta()) >= EtaEle_ || (1.4442 <= fabs(lept1.Eta()) && fabs(lept1.Eta()) <= 1.566)) ||
				    (fabs(lept2.Eta()) >= EtaEle_ || (1.4442 <= fabs(lept2.Eta()) && fabs(lept2.Eta()) <= 1.566))) continue;}
                Eff_Eta+=finWeight;

		//ISO (EB -Not used yet-)
		isl1EB = false; //I'd like to put them in lept class
		isl2EB = false;
		if (fabs( lept1.Eta() ) < 1.4442){ 
			isl1EB = true;
		}
		if (fabs( lept2.Eta() ) < 1.4442){ 
			isl2EB = true;
		}
		l1_CRI = (l1_iso1 + l1_iso2 + l1_iso3 - rho * 0.3 * 0.3 * TMath::Pi() )/lept1.Pt();
		l2_CRI = (l2_iso1 + l2_iso2 + l2_iso3 - rho * 0.3 * 0.3 * TMath::Pi() )/lept2.Pt(); 

		//WW met
		float Dphi_min1=0, Dphi_min2=0;
		float Met_Pro1=0, Met_Pro2=0;

		Dphi_min1 = min( delta_phi(lept1.Phi(),met1_phi), delta_phi(lept2.Phi(),met1_phi) );
		Dphi_min2 = min( delta_phi(lept1.Phi(),met2_phi), delta_phi(lept2.Phi(),met2_phi) );

		if (Dphi_min1 >= 1.5707 ) Met_Pro1 = met1_pt;
		if (Dphi_min1 < 1.5707 )  Met_Pro1 = met1_pt*sin(Dphi_min1);
		if (Dphi_min2 >= 1.5707 ) Met_Pro2 = met2_pt;
                if (Dphi_min2 < 1.5707 )  Met_Pro2 = met2_pt*sin(Dphi_min2);

		met_WW = min(Met_Pro1,Met_Pro2); 

                if(ee)          hee_cut_MET1Pt_PRO->Fill(met_WW,finWeight);
                if(mumu)        hmumu_cut_MET1Pt_PRO->Fill(met_WW,finWeight);
                                h_cut_MET1Pt_PRO->Fill(met_WW,finWeight);
		//if( met_WW < 37 + nvtx/2 ) continue;

		//BRANCH
		Tree_NVertex->Fill(); //Reweighting N vertex
		Tree_AllVariables->Fill(); //ALL BRANCH
		if( met1_pt>20. && (lepts.M() > 83. && lepts.M() < 97.) ) Tree_Met_Eff->Fill();

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
                	hee_in_njet->Fill(jn, finWeight);
                        hee_in_Iso1->Fill(l1_iso1, finWeight);
                        hee_in_Iso2->Fill(l1_iso2, finWeight);
                        hee_in_Iso3->Fill(l1_iso3, finWeight);
                        hee_in_Iso->Fill(l1_CRI, finWeight);
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
                	hmumu_in_njet->Fill(jn, finWeight);
                        hmumu_in_Iso1->Fill(l1_iso1, finWeight);
                        hmumu_in_Iso2->Fill(l1_iso2, finWeight);
                        hmumu_in_Iso3->Fill(l1_iso3, finWeight);
                        hmumu_in_Iso->Fill(l1_CRI, finWeight);
                }

                h_in_llMass->Fill(lepts.M(), finWeight);
                h_in_llPt->Fill(lepts.Pt(), finWeight);
                h_in_l1Eta->Fill(lept1.Eta(), finWeight);
                h_in_l2Eta->Fill(lept2.Eta(), finWeight);
                h_in_l1Pt->Fill(lept1.Pt(), finWeight);
                h_in_l2Pt->Fill(lept2.Pt(), finWeight);
                h_in_MET1Pt->Fill(met1_pt, finWeight);
                h_in_MetRed_IND->Fill( met_Red_pt_IND ,finWeight);
                h_in_MetRed_D0->Fill( met_Red_pt_D0 ,finWeight);
                h_in_MetRed_MIN->Fill( met_Red_pt_MIN ,finWeight);
                h_in_rho->Fill(rho, finWeight);
                h_in_nvtx->Fill(nvtx, finWeight);
                h_in_njet->Fill(jn, finWeight);
                h_in_Iso1->Fill(l1_iso1, finWeight);
                h_in_Iso2->Fill(l1_iso2, finWeight);
                h_in_Iso3->Fill(l1_iso3, finWeight);
                h_in_Iso->Fill(l1_CRI, finWeight);
		h_in_phiZMet->Fill(PhiZMet, finWeight);
		h_in_MetParallel->Fill(MetParallel, finWeight);
		h_in_MetTransvers->Fill(MetTransv, finWeight);

                        if( nvtx==1 ){  h_in_MET1vtx->Fill(met1_pt, finWeight);
                        		h_in_METx1vtx->Fill(met1_px, finWeight);
                        		h_in_METy1vtx->Fill(met1_py, finWeight);
                        		//h_in_METCharge1vtx->Fill(metCharge_pt, finWeight);
		
					h_in_Iso1_1vx->Fill(l1_iso1, finWeight);
					h_in_Iso2_1vx->Fill(l1_iso2, finWeight);
					h_in_Iso3_1vx->Fill(l1_iso3, finWeight);


			}
                        if( nvtx==4 ){  h_in_MET4vtx->Fill(met1_pt, finWeight);
                                        h_in_METx4vtx->Fill(met1_px, finWeight);
                                        h_in_METy4vtx->Fill(met1_py, finWeight);
                                        //h_in_METCharge4vtx->Fill(metCharge_pt, finWeight);
			}
                        if( nvtx==8 ){  h_in_MET8vtx->Fill(met1_pt, finWeight);
                                        h_in_METx8vtx->Fill(met1_px, finWeight);
                                        h_in_METy8vtx->Fill(met1_py, finWeight); 
                                        //h_in_METCharge8vtx->Fill(metCharge_pt, finWeight);

                                        h_in_Iso1_8vx->Fill(l1_iso1, finWeight);
                                        h_in_Iso2_8vx->Fill(l1_iso2, finWeight);
                                        h_in_Iso3_8vx->Fill(l1_iso3, finWeight);
			}
                        if( nvtx==12 ){ h_in_MET12vtx->Fill(met1_pt, finWeight);
                                        h_in_METx12vtx->Fill(met1_px, finWeight);
                                        h_in_METy12vtx->Fill(met1_py, finWeight);
                                        //h_in_METCharge12vtx->Fill(metCharge_pt, finWeight);

                                        h_in_Iso1_12vx->Fill(l1_iso1, finWeight);
                                        h_in_Iso2_12vx->Fill(l1_iso2, finWeight);
                                        h_in_Iso3_12vx->Fill(l1_iso3, finWeight); 
			}
                        if( nvtx==18 ){ h_in_MET18vtx->Fill(met1_pt, finWeight);
                                        h_in_METx18vtx->Fill(met1_px, finWeight);
                                        h_in_METy18vtx->Fill(met1_py, finWeight);
                                        //h_in_METCharge18vtx->Fill(metCharge_pt, finWeight);
			}
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
	
		//---------- start cuts --------------------	

		//@@ Z mass window
                if(ee)          hee_cut_llMass->Fill(lepts.M() ,finWeight);
                if(mumu)        hmumu_cut_llMass->Fill(lepts.M() ,finWeight);
                                h_cut_llMass->Fill(lepts.M() ,finWeight);
		if ( lepts.M() < MZmin_ || lepts.M() > MZmax_ ) continue;
		Eff_Z_Mass+=finWeight;

		// check pt of the Z candidate
		if(ee)		hee_cut_llPt->Fill(lepts.Pt(),finWeight);
		if(mumu) 	hmumu_cut_llPt->Fill(lepts.Pt(),finWeight);
				h_cut_llPt->Fill(lepts.Pt(),finWeight);
		if (lepts.Pt() < ZPt_) continue; // Trigger for y+jet control sample
		Eff_Z_Pt+=finWeight;

                // Jet-Veto
                veto_Jet = false;
                int Njet = 0;
		TLorentzVector Jet_loop;
                for (int i = 0; i < jn; i++) {
                        Jet_loop.SetPxPyPzE(jn_px[i],jn_py[i],jn_pz[i],jn_en[i]);
                        if( Jet_loop.Pt() > 30. && fabs(Jet_loop.Eta()) < 5. ){
			  veto_Jet = true;
			  Njet ++;
			}
                }
                if(ee)          hee_cut_njet->Fill(Njet,finWeight);
                if(mumu)        hmumu_cut_njet->Fill(Njet,finWeight);
                                h_cut_njet->Fill(Njet,finWeight);
		if (veto_Jet) continue;
		Eff_Jet_Veto+=finWeight;

		// MET Cut
                if(ee)          hee_cut_MET1Pt->Fill(met1_pt,finWeight);
                if(mumu)        hmumu_cut_MET1Pt->Fill(met1_pt,finWeight);
                                h_cut_MET1Pt->Fill(met1_pt,finWeight);
		if( met1_pt < Met_ ) continue;
		Eff_MET+=finWeight;

		// Balance cut
                if(ee)          hee_cut_Balan->Fill(met1_pt/lepts.Pt(),finWeight);
                if(mumu)        hmumu_cut_Balan->Fill(met1_pt/lepts.Pt(),finWeight);
                                h_cut_Balan->Fill(met1_pt/lepts.Pt(),finWeight);
		if( (met1_pt/lepts.Pt()) < BalancMin_ || (met1_pt/lepts.Pt()) > BalancMax_ ) continue; // Balance between the Pt of Z candidate and MET
		Eff_Balance+=finWeight;
		
		// Delta Phi Jet
		jet_eta = 0.; jet_pt = 0.;
		float Pt_app_jet = 0, Phi_hardJet = 999.;
                for (int i = 0; i < jn; i++) {
			Jet_loop.SetPxPyPzE(jn_px[i],jn_py[i],jn_pz[i],jn_en[i]);
                        if(fabs(Jet_loop.Eta()) < 2.4 && Jet_loop.Pt() > 10. && Jet_loop.Pt() > Pt_app_jet ) {
                                Pt_app_jet = Jet_loop.Pt();
                                Phi_hardJet = Jet_loop.Phi();
                        }
                }
		Eff_Jet_Phi+=finWeight;

		if( Phi_hardJet < 700. ){
                 if(ee)          hee_cut_PhiJet->Fill( fabs(delta_phi(Phi_hardJet,met1_phi)) ,finWeight );
                 if(mumu)        hmumu_cut_PhiJet->Fill( fabs(delta_phi(Phi_hardJet,met1_phi)) ,finWeight);
                                 h_cut_PhiJet->Fill( fabs(delta_phi(Phi_hardJet,met1_phi)) ,finWeight);
		}
		if( (fabs(delta_phi(Phi_hardJet,met1_phi)) < PhiJet_) ) continue; //20 degrees

                // Delta Phi Z
                if(ee)          hee_cut_PhiZ->Fill(PhiZMet,finWeight);
                if(mumu)        hmumu_cut_PhiZ->Fill(PhiZMet,finWeight);
                                h_cut_PhiZ->Fill(PhiZMet,finWeight);
		if( PhiZMet < PhiZ_ ) continue; //60 degrees
		Eff_Z_Phi+=finWeight;

		// B-tagging
		isThereBJet = false;
		jet_eta = 0.; jet_pt = 0.;
		for (int i = 0; i < jn; i++) {
                        Jet_loop.SetPxPyPzE(jn_px[i],jn_py[i],jn_pz[i],jn_en[i]);
			if( Jet_loop.Pt() > 10. ) {
				if( jn_btag1[i] >= 3.3 ) isThereBJet = true;
				i = jn; //close for at 1st Bjet found

                if(ee)          hee_cut_Btag->Fill(jn_btag1[i],finWeight);
                if(mumu)        hmumu_cut_Btag->Fill(jn_btag1[i],finWeight);
                                h_cut_Btag->Fill(jn_btag1[i],finWeight);
			}
		}
		if (isThereBJet) continue;
		Eff_B_Veto+=finWeight;
		
		// leptons veto
		if (sqrt(ln_px[0]*ln_px[0]+ln_py[0]*ln_py[0])>10.){
                 if(ee)          hee_cut_Nlep->Fill(ln,finWeight);
                 if(mumu)        hmumu_cut_Nlep->Fill(ln,finWeight);
                                 h_cut_Nlep->Fill(ln,finWeight);
		}
		if (ln > 0){
			if ( ( abs(ln_id[0]) == 11 || abs(ln_id[0]) == 13 ) && sqrt(ln_px[0]*ln_px[0]+ln_py[0]*ln_py[0])>10. ) continue; //was20
		}
		Eff_Lept_Veto+=finWeight;
		
		// check the isolation of the leptons
		if	(mumu && !ee ){	if( l1_CRI > Iso1 || l2_CRI > Iso2) continue;}
		else if (ee && !mumu ){	if( l1_CRI > Iso1 || l2_CRI > Iso2) continue;}
		else	cout<<"That's impossible!"<<endl;
		Eff_ISO+=finWeight;

		//Tree_All_Final->Fill();

		// Z mass window
                //@@if(ee)          hee_cut_llMass->Fill(lepts.M() ,finWeight);
                //if(mumu)        hmumu_cut_llMass->Fill(lepts.M() ,finWeight);
                //                h_cut_llMass->Fill(lepts.M() ,finWeight);
		//if ( lepts.M() < MZmin_ || lepts.M() > MZmax_ ) continue;
		//Eff_Z_Mass+=finWeight;

		//if(lepts.Pt()>260.){ cout<<"DATASET: "<<Dataset_<<" RUN "<<run<<" LUMI "<<lumi<<" EVENT "<<event<<endl;   
		//cout<<"N Jet: "<<Njet<<endl;
		//}
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
                        hee_njet->Fill(jn, finWeight);
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
                        hmumu_njet->Fill(jn, finWeight);
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
		h_njet->Fill(jn, finWeight);
		h_phiZMet->Fill(PhiZMet, finWeight);
		h_MetParallel->Fill(MetParallel, finWeight);
		h_MetTransvers->Fill(MetTransv, finWeight);

	}// for entries
/*
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
}*/
	dir->GetList()->Write();
	Tree_NVertex->Write();
	Tree_AllVariables->Write();
	Tree_Met_Eff->Write();
	//Tree_All_Final->Write();
	file->Close();
	dir->GetList()->Delete();


//-------------EFFICIENCY
float Lumi = 4615.;
	cout << endl;	
	cout << "Preselection: " << Eff_Preselection*Lumi << endl;
	cout << "Two_leptons: " << Eff_Two_leptons*Lumi << "  Eff_tot: " << Eff_Two_leptons/Eff_Preselection << "  Eff_parz: " << Eff_Two_leptons/Eff_Preselection << endl;
	cout << "Pt: " << Eff_Pt*Lumi <<  "  Eff_tot: " << Eff_Pt/Eff_Preselection << "  Eff_parz: " << Eff_Pt/Eff_Two_leptons << endl;
	cout << "Eta: " << Eff_Eta*Lumi <<  "  Eff_tot: " << Eff_Eta/Eff_Preselection << "  Eff_parz: " << Eff_Eta/Eff_Pt << endl;
        cout << "Z_Mass: " << Eff_Z_Mass*Lumi <<  "  Eff_tot: " << Eff_Z_Mass/Eff_Preselection << "  Eff_parz: " << Eff_Z_Mass/Eff_Eta << endl;
	cout << "Z_Pt: " << Eff_Z_Pt*Lumi <<  "  Eff_tot: " << Eff_Z_Pt/Eff_Preselection << "  Eff_parz: " << Eff_Z_Pt/Eff_Z_Mass << endl;
        cout << "Jet_Veto: " << Eff_Jet_Veto*Lumi <<  "  Eff_tot: " << Eff_Jet_Veto/Eff_Preselection << "  Eff_parz: " << Eff_Jet_Veto/Eff_Z_Pt << endl;
        cout << "MET: " << Eff_MET*Lumi <<  "  Eff_tot: " << Eff_MET/Eff_Preselection << "  Eff_parz: " << Eff_MET/Eff_Jet_Veto << endl;
        cout << "Balance: " << Eff_Balance*Lumi <<  "  Eff_tot: " << Eff_Balance/Eff_Preselection << "  Eff_parz: " << Eff_Balance/Eff_MET << endl;
        cout << "Jet_Phi: " << Eff_Jet_Phi*Lumi <<  "  Eff_tot: " << Eff_Jet_Phi/Eff_Preselection << "  Eff_parz: " << Eff_Jet_Phi/Eff_Balance << endl;
        cout << "Z_Phi: " << Eff_Z_Phi*Lumi <<  "  Eff_tot: " << Eff_Z_Phi/Eff_Preselection << "  Eff_parz: " << Eff_Z_Phi/Eff_Jet_Phi << endl;
        cout << "B_Veto: " << Eff_B_Veto*Lumi <<  "  Eff_tot: " << Eff_B_Veto/Eff_Preselection << "  Eff_parz: " << Eff_B_Veto/Eff_Z_Phi << endl;
        cout << "Lept_Veto: " << Eff_Lept_Veto*Lumi <<  "  Eff_tot: " << Eff_Lept_Veto/Eff_Preselection << "  Eff_parz: " << Eff_Lept_Veto/Eff_B_Veto << endl;
        cout << "ISO: " << Eff_ISO*Lumi <<  "  Eff_tot: " << Eff_ISO/Eff_Preselection << "  Eff_parz: " << Eff_ISO/Eff_Lept_Veto << endl;
//        cout << "Z_Mass: " << Eff_Z_Mass*Lumi <<  "  Eff_tot: " << Eff_Z_Mass/Eff_Preselection << "  Eff_parz: " << Eff_Z_Mass/Eff_ISO << endl;
	cout << endl;
	cout << "Num EE = " << Eff_FinalEE << "  Num MuMu = " << Eff_FinalMuMu << endl;

// TABLE EFF/N.EV FINAL SELECTION
	f1<<"DATASET:"<<Dataset_<<endl;
	f1<<endl;
	f1<<"\\"<<"begin{tabular}{|c|c|c|c|}"<<endl;
	f1<<"\\"<<"hline"<<endl;
	f1<<" Cut &Total Efficency& Relative Efficency&Yelds exp.(4.6 fb-1)\\"<<"\\"<<""<<endl;
	f1<<"\\"<<"hline"<<endl;
	f1<<"Preselection&"<<""<<"&"<<"1."<<"&"<<Eff_Preselection*Lumi<<"\\"<<"\\"<<""<<endl;
	f1<<"\\"<<"hline"<<endl;
	f1<<"Pt(Z)&"<<Eff_Z_Pt/Eff_Preselection<<"&"<<Eff_Z_Pt/Eff_Preselection<<"&"<<Eff_Z_Pt*Lumi<<"\\"<<"\\"<<""<<endl;
	f1<<"\\"<<"hline"<<endl;
	f1<<"Jet Veto&"<<Eff_Jet_Veto/Eff_Preselection<<"&"<<Eff_Jet_Veto/Eff_Z_Pt<<"&"<<Eff_Jet_Veto*Lumi<<"\\"<<"\\"<<""<<endl;
	f1<<"\\"<<"hline"<<endl;
	f1<<"MET&"<<Eff_MET/Eff_Preselection<<"&"<<Eff_MET/Eff_Jet_Veto<<"&"<<Eff_MET*Lumi<<"\\"<<"\\"<<""<<endl;
	f1<<"\\"<<"hline"<<endl;
	f1<<"Balance&"<<Eff_Balance/Eff_Preselection<<"&"<<Eff_Balance/Eff_MET<<"&"<<Eff_Balance*Lumi<<"\\"<<"\\"<<""<<endl;
	f1<<"\\"<<"hline"<<endl;
	f1<<"Jet Phi&"<<Eff_Jet_Phi/Eff_Preselection<<"&"<<Eff_Jet_Phi/Eff_Balance<<"&"<<Eff_Jet_Phi*Lumi<<"\\"<<"\\"<<""<<endl;
	f1<<"\\"<<"hline"<<endl;
	f1<<"Z Phi&"<<Eff_Z_Phi/Eff_Preselection<<"&"<<Eff_Z_Phi/Eff_Jet_Phi<<"&"<<Eff_Z_Phi*Lumi<<"\\"<<"\\"<<""<<endl;
	f1<<"\\"<<"hline"<<endl;
	f1<<"B Veto&"<<Eff_B_Veto/Eff_Preselection<<"&"<<Eff_B_Veto/Eff_Z_Phi<<"&"<<Eff_B_Veto*Lumi<<"\\"<<"\\"<<""<<endl;
	f1<<"\\"<<"hline"<<endl;
	f1<<"Lept Veto&"<<Eff_Lept_Veto/Eff_Preselection<<"&"<<Eff_Lept_Veto/Eff_B_Veto<<"&"<<Eff_Lept_Veto*Lumi<<"\\"<<"\\"<<""<<endl;
	f1<<"\\"<<"hline"<<endl;
	f1<<"Z Mass&"<<Eff_Z_Mass/Eff_Preselection<<"&"<<Eff_Z_Mass/Eff_Lept_Veto<<"&"<<Eff_Z_Mass*Lumi<<"\\"<<"\\"<<""<<endl;
	f1<<"\\"<<"hline"<<endl;
	f1<<"\\"<<"end{tabular}"<<endl;
	f1<<endl;f1<<endl;

f1.close();

}//Loop

// Delta Phi
inline double delta_phi(double phi1, double phi2) {
  double dphi = TMath::Abs(phi1 - phi2);
  return ( dphi <= TMath::Pi()  ? dphi : TMath::TwoPi() - dphi );
}

//Min
inline double min(double n1, double n2) {
if( n1 < n2 ) return n1;
else return n2;
}

// Computre weight
double TrigCorr( int l_id, TLorentzVector lept ) {

 double WEIGHT = 1.;
 if      ( abs(l_id) == 11 ){
  }
 else if ( abs(l_id) == 13 ){
        if( lept.Eta()>0 && lept.Eta()<=0.8 ){
                if      ( lept.Pt()>20 && lept.Pt()<30 ) WEIGHT = 0.977;
                else                                     WEIGHT = 0.977;
        }
        else if( lept.Eta()>0.8 && lept.Eta()<=1.2 ){
                if      ( lept.Pt()>20 && lept.Pt()<30 ) WEIGHT = 0.96;
                else                                     WEIGHT = 0.955;
        }
        else if( lept.Eta()>1.2 && lept.Eta()<=2.1 ){
                if      ( lept.Pt()>20 && lept.Pt()<30 ) WEIGHT = 0.955;
                else                                     WEIGHT = 0.95;
        } 
        else{
                if      ( lept.Pt()>20 && lept.Pt()<30 ) WEIGHT = 0.87;
                else                                     WEIGHT = 0.88;
        }
  }

 return WEIGHT;
}

double IsoIdCorr( int l_id, TLorentzVector lept ) {

  double WEIGHT = 1.;
  if      ( abs(l_id) == 11 ){
        /*if( lept.Eta() > 1.4442 ){
                if      ( lept.Pt()>20 && lept.Pt()<30 ) WEIGHT = 0.938;
                else if ( lept.Pt()>30 && lept.Pt()<40 ) WEIGHT = 0.971;
                else if ( lept.Pt()>40 && lept.Pt()<50 ) WEIGHT = 0.980;
                else                                     WEIGHT = 0.987;
        }
        else{
                if      ( lept.Pt()>20 && lept.Pt()<30 ) WEIGHT = 0.967;
                else if ( lept.Pt()>30 && lept.Pt()<40 ) WEIGHT = 0.970;
                else if ( lept.Pt()>40 && lept.Pt()<50 ) WEIGHT = 0.989;
                else                                     WEIGHT = 0.989;
        } */
  }
  else if ( abs(l_id) == 13 ){
        if( lept.Eta()>0 && lept.Eta()<=0.8 ){
                if      ( lept.Pt()>20 && lept.Pt()<30 ) WEIGHT = 0.9287;
                else					 WEIGHT = 0.9617;
        }
        else if( lept.Eta()>0.8 && lept.Eta()<=1.2 ){
                if      ( lept.Pt()>20 && lept.Pt()<30 ) WEIGHT = 0.9206;
                else                                     WEIGHT = 0.9431;
        }
        else{
                if      ( lept.Pt()>20 && lept.Pt()<30 ) WEIGHT = 0.9284;
                else					 WEIGHT = 0.9472;
        }
	/*if( lept.Eta()>0 && lept.Eta()<1.2 ){
		if	( lept.Pt()>20 && lept.Pt()<30 ) WEIGHT = 0.997;
		else if ( lept.Pt()>30 && lept.Pt()<40 ) WEIGHT = 0.997;
		else if	( lept.Pt()>40 && lept.Pt()<60 ) WEIGHT = 0.997;
		else					 WEIGHT = 0.999;
	}
	else{
                if      ( lept.Pt()>20 && lept.Pt()<30 ) WEIGHT = 0.999;
                else if ( lept.Pt()>30 && lept.Pt()<40 ) WEIGHT = 1.000;
                else if ( lept.Pt()>40 && lept.Pt()<60 ) WEIGHT = 0.998;
                else					 WEIGHT = 0.999;
	}*/
  }

  return WEIGHT;
}

void ZZ_Finalize::SetSelection(TString Selection){
  if( Selection.Contains("Standard") ){
  lept1Pt_ = 20.; lept2Pt_ = 20. ;
  EtaMu_ = 2.4; EtaEle_ = 2.5; 
  ZPt_ = 30;
  Met_ = 60;
  BalancMin_ = 0.4; BalancMax_ = 1.8;
  PhiZ_ = 1.0472;
  PhiJet_ = 0.349;
  Iso1 = 0.15; Iso2 = 0.15;
  MZmin_ = 80; MZmax_ = 100;
  }
  else if( Selection.Contains("Preselection") ){
  lept1Pt_ = 10.; lept2Pt_ = 10. ;
  EtaMu_ = 2.4; EtaEle_ = 2.5;
  ZPt_ = 10.;
  Met_ = 10.;
  BalancMin_ = 0.; BalancMax_ = 3.;
  PhiZ_ = 0.;
  PhiJet_ = 0.;
  Iso1 = 99.; Iso2 = 99.;
  MZmin_ = 0.; MZmax_ = 999.;
  }

  else cout << "Sorry man... Selection not known!" << endl;
}
