#define ZZ_Finalize_cxx
#include "ZZ_Finalize.h"
#include <TH2.h>
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
	
	#include "Include/higgsDeclaration.h"
	float Eff_Preselection = 0.;
	float Eff_Two_leptons = 0.;
	float Eff_Pt = 0.;
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

	Bool_t ee = 0.;
	Bool_t mumu = 0.;	
	Bool_t isl1EB = 0.;
	Bool_t isl2EB = 0.;
	Bool_t isThereBJet = 0.;
	Bool_t veto_Jet = 0.;

	Float_t l1_CRI = 0.;
	Float_t l2_CRI = 0.;
	Float_t jet_eta = 0.;
	Float_t jet_pt = 0.;

	Float_t finWeight = 0.;

	// event loop

	// nentries = 100;
	for (Long64_t jentry=0; jentry<nentries;jentry++) {
		if (jentry % 50000 == 0) cout << jentry << endl;
		Long64_t ientry = LoadTree(jentry); //Set curren entry (-2 if it doesn't exist)
		if (ientry < 0) break;
		nb = fChain->GetEntry(jentry);   nbytes += nb;
		

		Eff_Preselection++;

		// reweighting for pile up
		finWeight = 1.;
		//if ( isData_ == 0 ) finWeight *= weight;
		if ( isData_ == 0 ) finWeight *= eeScaling_;
		//if (Cut(ientry) < 0) continue;

                //---------- Define Variables ----------           
                TLorentzVector lept1, lept2, lepts;
		TLorentzVector Jet_loop;
                lept1.SetPxPyPzE(l1_px,l1_py,l1_pz,l1_en);
                lept2.SetPxPyPzE(l2_px,l2_py,l2_pz,l2_en);
                lepts = lept1 + lept2;
		
		//---------- Basic Preselection ----------		
		// check 2 leptons same flavor
		ee = 0;
		mumu = 0;
		if (abs(l1_id) == 11 && abs(l2_id) == 11) ee = 1;
		else if (abs(l1_id) == 13 && abs(l2_id) == 13) mumu = 1;
		//else cout<<"Not ee or mumu but something else. Strange!"<<endl;
		// check two leptons opposite charge
		if ((ee == 0 && mumu == 0)) continue;
		Eff_Two_leptons++;
		// pt minimum for each lepton
		//if( (lept1.Pt()==0 || lept2.Pt()==0) && (lepts.M()<20. || lepts.M()>110. )  ) cout<<"Very Very strange!"<<endl; //Why data out of the mZ window have Pt=0??
		if( lept1.Pt() < 20 || lept2.Pt() < 20 ) continue;
		Eff_Pt++;

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
                }

		//---------- compute the kinematic ----
		isl1EB = 0; //I'd like to put them in lept class
		isl2EB = 0;
		if (fabs( lept1.Eta()<20. ) < 1.4442){ 
			isl1EB = 1;
			//if(abs(l1_id) == 11) l1_iso1 -= 1.;
		}
		if (fabs( lept2.Eta()<20. ) < 1.4442){ 
			isl2EB = 1;
			//if(abs(l2_id) == 11) l2_iso1 -= 1.;
		}
		l1_CRI = (l1_iso1 + l1_iso2 + l1_iso3 - rho * 0.3 * 0.3)/lept1.Pt(); 
		l2_CRI = (l2_iso1 + l2_iso2 + l2_iso3 - rho * 0.3 * 0.3)/lept2.Pt(); 
	
		//---------- start cuts --------------------	
		// check pt of the Z candidate
		if (lepts.Pt() < 30) continue; //@@ 25
		Eff_Z_Pt++;	

                // Jet-Veto @@ ADDED
                veto_Jet = 0;
                for (int i = 0; i < jn; i++) {
                        Jet_loop.SetPxPyPzE(jn_px[i],jn_py[i],jn_pz[i],jn_en[i]);
                        if( Jet_loop.Pt() > 30. && fabs(Jet_loop.Eta()) < 5. )  veto_Jet = true;
                }
		if (veto_Jet) continue; //@@ ADDED
		Eff_Jet_Veto++;

		// MET Cut
		if( met1_pt < 50. ) continue;
		Eff_MET++;

		// Balance cut
		if( (lepts.E()/lepts.Pt()) < 0.4 || (lepts.E()/lepts.Pt()) > 1.8 ) continue; //@@ ADDED
		Eff_Balance++;

		// eta fiducial cut
		/*if (mumu && (fabs(l1_eta) > 2.4 || fabs(l2_eta) > 2.4)) continue;
		else if (ee){
			if ((fabs(l1_eta) >= 2.5 || (1.4442 <= fabs(l1_eta) && fabs(l1_eta) <= 1.566)) ||
			   (fabs(l2_eta) >= 2.5 || (1.4442 <= fabs(l2_eta) && fabs(l2_eta) <= 1.566))) continue;
		}
		*/
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
		if( isJet_hard && (fabs(delta_phi(Phi_hardJet,met1_phi)) < 0.349) ) continue; //20degrees

                // Delta Phi Z
		if( delta_phi(met1_phi,lepts.Phi()) < 1.0472 ) continue; //60degrees
		Eff_Z_Phi++;

		// B-tagging
		isThereBJet = 0;
		jet_eta = 0.; jet_pt = 0.;
		for (int i = 0; i < jn; i++) {
                        Jet_loop.SetPxPyPzE(jn_px[i],jn_py[i],jn_pz[i],jn_en[i]);
			if(fabs(Jet_loop.Eta()) < 2.4 && Jet_loop.Pt() > 30. && jn_btag1[i] >= 2) {
				isThereBJet = 1;
				i = jn;
			}
		}
		if (isThereBJet) continue;
		Eff_B_Veto++;

		
		// reject events with more than 2 leptons
		if (ln > 0){
			if (abs(ln_id[0]) == 11 && sqrt(ln_px[0]*ln_px[0]+ln_py[0]*ln_py[0])>20. ) continue; //was10
			if (abs(ln_id[0]) == 13 && sqrt(ln_px[0]*ln_px[0]+ln_py[0]*ln_py[0])>20. ) continue; //was no pt requirement
		}
		Eff_Lept_Veto++;
		
		// check the isolation of the leptons
		if (mumu && (l1_CRI > 0.15 || l2_CRI > 0.15)) continue;
		else if (ee && (l1_CRI > 0.15 || l2_CRI > 0.15)) continue;
		Eff_ISO++;

		// Z mass window
		if ( lepts.M() < 80 || lepts.M() > 100 ) continue; //@@+-15
		Eff_Z_Mass++;

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
			Eff_FinalMuMu++;
		} 

	}

/*
	// display histogram
	
	hee_llMass->SetXTitle("M_{ll}  (GeV)");
	hee_l1Pt->SetXTitle("p_{t}  (GeV)");
	hee_l2Pt->SetXTitle("p_{t}  (GeV)");
	hee_MET1Pt->SetXTitle("MET1  (GeV)");
	hee_l1Eta->SetXTitle("#eta");
	hee_l2Eta->SetXTitle("#eta");
	
	hmumu_llMass->SetXTitle("M_{ll}  (GeV)");
	hmumu_l1Pt->SetXTitle("p_{t}  (GeV)");
	hmumu_l2Pt->SetXTitle("p_{t}  (GeV)");
	hmumu_MET1Pt->SetXTitle("MET1  (GeV)");
	hmumu_l1Eta->SetXTitle("#eta");
	hmumu_l2Eta->SetXTitle("#eta");
*/	
	
	dir->GetList()->Write();
	file->Close();
	dir->GetList()->Delete();

	cout << endl;	
	cout << "Preselection: " << Eff_Preselection << endl;
	cout << "Two_leptons: " << Eff_Two_leptons << "  Eff_tot: " << Eff_Two_leptons/Eff_Preselection << "  Eff_parz: " << Eff_Two_leptons/Eff_Preselection << endl;
	cout << "Pt: " << Eff_Pt <<  "  Eff_tot: " << Eff_Pt/Eff_Preselection << "  Eff_parz: " << Eff_Pt/Eff_Two_leptons << endl;
	cout << "Z_Pt: " << Eff_Z_Pt <<  "  Eff_tot: " << Eff_Z_Pt/Eff_Preselection << "  Eff_parz: " << Eff_Z_Pt/Eff_Pt << endl;
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
	cout << "FinalEE = " << Eff_FinalEE << "  FinalMuMu = " << Eff_FinalMuMu << endl;
}

// Delta Phi
inline double delta_phi(double phi1, double phi2) {
  double dphi = TMath::Abs(phi1 - phi2);
  return (dphi <= TMath::Pi())? dphi : TMath::TwoPi() - dphi;
}
