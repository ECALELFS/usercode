#define ZZ_Finalize_cxx
#include "ZZ_Finalize.h"
#include <TH2.h>
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

using namespace std;

void ZZ_Finalize::Loop()
{
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
	Int_t compteur[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	Int_t compteurEE = 0;
	Int_t compteurMuMu = 0;

	TDirectory *dir = gDirectory;
	TFile *file = new TFile(outputFileName, "RECREATE");

	Long64_t nentries = fChain->GetEntriesFast(); // Entries number fot TChain

	Long64_t nbytes = 0, nb = 0;

	Bool_t ee;
	Bool_t mumu;	
	Bool_t isl1EB;
	Bool_t isl2EB;
	Bool_t isThereBJet;

	Float_t l1_eta;
	Float_t l2_eta;
	Float_t l1_pt;
	Float_t l2_pt;
	Float_t l1_CRI;
	Float_t l2_CRI;
	Float_t ll_px;
	Float_t ll_py;
	Float_t ll_pt;
	Float_t ll_m;
	Float_t jet_eta;
	Float_t jet_pt;

	Float_t finWeight;

	// event loop

	// nentries = 100;
	for (Long64_t jentry=0; jentry<nentries;jentry++) {
		if (jentry % 50000 == 0) cout << jentry << endl;
		Long64_t ientry = LoadTree(jentry); //Set curren entry (-2 if it doesn't exist)
		if (ientry < 0) break;
		nb = fChain->GetEntry(jentry);   nbytes += nb;
		

		compteur[0]++;
		
		// reweighting for pile up
		finWeight = 1;
		if (!isData) finWeight *= weight;
	
		// if (Cut(ientry) < 0) continue;
		
		//---------- compute the kinematic ----------		

		TLorentzVector lept1, lept2, lepts;
		//if((l1_px * l1_px + l1_py * l1_py)==0 || (l2_px * l2_px + l2_py * l2_py)==0 ) continue;
		lept1.SetPxPyPzE(l1_px,l1_py,l1_pz,l1_en);
		lept2.SetPxPyPzE(l2_px,l2_py,l2_pz,l2_en);
		lepts = lept1 + lept2;
//if( (l1_px * l1_px + l1_py * l1_py)==0 || (l2_px * l2_px + l2_py * l2_py)==0  ) cout<<"))))))))))))"<<endl;
		l1_pt = sqrt(l1_px * l1_px + l1_py * l1_py); //Zero Ogni tanto
		l2_pt = sqrt(l2_px * l2_px + l2_py * l2_py);
		ll_px = l1_px + l2_px;
		ll_py = l1_py + l2_py;
		ll_pt = sqrt(ll_px * ll_px + ll_py * ll_py);
		l1_eta = 0.5*log((l1_en+l1_pz)/(l1_en-l1_pz));
		l2_eta = 0.5*log((l2_en+l2_pz)/(l2_en-l2_pz));
		isl1EB = 0; //I'd like to put them in lept class
		isl2EB = 0;
		if (fabs( l1_eta ) < 1.4442){ //@@
			isl1EB = 1;
			//if(abs(l1_id) == 11) l1_iso1 -= 1.;
		}
		if (fabs( l2_eta ) < 1.4442){ //@@
			isl2EB = 1;
			//if(abs(l2_id) == 11) l2_iso1 -= 1.;
		}
		l1_CRI = (l1_iso1 + l1_iso2 + l1_iso3 - rho * 0.3 * 0.3)/l1_pt; //@@
		l2_CRI = (l2_iso1 + l2_iso2 + l2_iso3 - rho * 0.3 * 0.3)/l2_pt; //@@
		ll_m = sqrt( (l1_en+l2_en)*(l1_en+l2_en)
				- (l1_px+l2_px)*(l1_px+l2_px)
				- (l1_py+l2_py)*(l1_py+l2_py)
				- (l1_pz+l2_pz)*(l1_pz+l2_pz) );
		
		//---------- start cuts --------------------
		// check 2 leptons same flavor
		ee = 0;
		mumu = 0;
		if (abs(l1_id) == 11 && abs(l2_id) == 11) ee = 1;
		else if (abs(l1_id) == 13 && abs(l2_id) == 13) mumu = 1;
		// check two leptons opposite charge
		//if (l1_id * l2_id >= 0 || (ee == 0 && mumu == 0)) continue;
		if ((ee == 0 && mumu == 0)) continue;
		compteur[1]++;
		
		// eta fiducial cut
		/*if (mumu && (fabs(l1_eta) > 2.4 || fabs(l2_eta) > 2.4)) continue;
		else if (ee){
			if ((fabs(l1_eta) >= 2.5 || (1.4442 <= fabs(l1_eta) && fabs(l1_eta) <= 1.566)) ||
			   (fabs(l2_eta) >= 2.5 || (1.4442 <= fabs(l2_eta) && fabs(l2_eta) <= 1.566))) continue;
		}
		*/
		// check the pt resolution for the muons
		//if (mumu && (l1_ptErr/l1_pt > 0.1 || l2_ptErr/l2_pt > 0.1)) continue;
		
		// Z mass window
		if (fabs(ll_m - 91.) > 15.) continue; //@@
		compteur[2]++; 
		
		// b-tagging
		isThereBJet = 0;
		
		for (int i = 0; i < jn; i++) {
			jet_eta = 0.5*log((jn_en[i]+jn_pz[i])/(jn_en[i]-jn_pz[i]));
			jet_pt = sqrt(jn_px[i]*jn_px[i] + jn_py[i]*jn_py[i]);
			if(fabs(jet_eta) < 2.4 && jet_pt > 30. && jn_btag1[i] >= 2) {
				isThereBJet = 1;
				i = jn;
			}
		}
		if (isThereBJet) continue;
		compteur[3]++;
	
		// check pt of the Z candidate
		if (ll_pt < 25) continue; //@@
		compteur[4]++;	
		
		// reject events with more than 2 leptons
		if (ln > 0){
			if (abs(ln_id[0]) == 11 && sqrt(ln_px[0]*ln_px[0]+ln_py[0]*ln_py[0])>10. ) continue;
			if (abs(ln_id[0]) == 13 ) continue;
		}
		compteur[5]++;		
		
		// check the isolation of the leptons
		if (mumu && (l1_CRI > 0.15 || l2_CRI > 0.15)) continue;
		else if (ee && (l1_CRI > 0.15 || l2_CRI > 0.15)) continue;
		compteur[6]++;		
	
		
				
		// pt minimum for each lepton
		if (l1_pt < 20 || l2_pt < 20) continue; //@@
		compteur[7]++;
		

	
		// Fill histos
		if (ee){
			hee_llMass->Fill(ll_m, finWeight);
			hee_llPt->Fill(ll_pt, finWeight);
			hee_l1Eta->Fill(l1_eta, finWeight);
			hee_l2Eta->Fill(l2_eta, finWeight);
			hee_l1Pt->Fill(l1_pt, finWeight);
			hee_l2Pt->Fill(l2_pt, finWeight);
			hee_MET1Pt->Fill(met1_pt, finWeight);
			compteurEE++;
		}
		else if (mumu){
			hmumu_llMass->Fill(ll_m, finWeight);
			hmumu_llPt->Fill(ll_pt, finWeight);
			hmumu_l1Eta->Fill(l1_eta, finWeight);
			hmumu_l2Eta->Fill(l2_eta, finWeight);
			hmumu_l1Pt->Fill(l1_pt, finWeight);
			hmumu_l2Pt->Fill(l2_pt, finWeight);
			hmumu_MET1Pt->Fill(met1_pt, finWeight);
			compteurMuMu++;
		} 

			
	}


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
	
	
	dir->GetList()->Write();
	file->Close();
	dir->GetList()->Delete();

	cout << endl;	
	for (int i = 0; i<8; i++){
		cout <<" compteur  "<<i<< "  " <<  compteur[i] << endl;
	}
	cout << endl;
	cout << "compteurEE = " << compteurEE << "  compteurMuMu = " << compteurMuMu << endl;

}


void ZZ_Finalize::Plot(string histoName)
{
	string temp1 = "hee_" + histoName;
	string temp2 = "hmumu_" + histoName;
	string temp3 = histoName;
	char *eeName, *mumuName, *Name;
	eeName = new char [temp1.size()+1];
	mumuName = new char [temp2.size()+1];
	Name = new char [temp3.size()];
	strcpy (eeName, temp1.c_str());
	strcpy (mumuName, temp2.c_str());
	strcpy (Name, temp3.c_str());
	

	
	isData = 1;
	leptonType = 11;
	SetFiles();
	TFile *eeDataFile = new TFile(outputFileName, "READ");
	TH1F *hee_data = (TH1F*) eeDataFile->Get(eeName);
	hee_data->SetMarkerStyle(20);
	hee_data->SetMarkerColor(1);
	hee_data->SetLineColor(1);
	hee_data->SetMarkerSize(1);
	
	leptonType = 13;
	SetFiles();
	TFile *mumuDataFile = new TFile(outputFileName, "READ");
	TH1F *hmumu_data = (TH1F*) mumuDataFile->Get(mumuName);
	hmumu_data->SetMarkerStyle(20);
	hmumu_data->SetMarkerColor(1);
	hmumu_data->SetLineColor(1);
	hmumu_data->SetMarkerSize(1);

	TCanvas *can = new TCanvas(Name, Name, 0, 0, 840, 800);
	can->Divide(2,2);
	
	can->cd(1);
	hee_data->DrawCopy("e");
	can->cd(3);
	hmumu_data->DrawCopy("e");
	can->cd(2);
	can->cd(2)->SetLogy();
	hee_data->SetMinimum(0.0009);
	hee_data->DrawCopy("e");
	can->cd(4);
	can->cd(4)->SetLogy();
	hmumu_data->SetMinimum(0.0009);
	hmumu_data->DrawCopy("e");
	

	TFile *MCFile[20];
	TH1F *hee_MC[20];
	TH1F *hmumu_MC[20];

	isData = 0;
	
	cout << endl << "SCALING" << endl;
	for (int i = 0; i < 20; i++){
		SetFiles(i+11);
		MCFile[i] = new TFile(outputFileName, "READ");
		hee_MC[i] = (TH1F*) MCFile[i]->Get(eeName);
		hee_MC[i]->Scale(eeScaling[i]);	
		hmumu_MC[i] = (TH1F*) MCFile[i]->Get(mumuName);
		hmumu_MC[i]->Scale(mumuScaling[i]);
		
		
		//cout <<" ee:  " << eeScaling[i] << "   mumu: " << mumuScaling[i] << endl;
		
	
	}

	// add histograms

	Color_t colors[20] = {kGreen-10,0,0,0,0,0,0,0,0, kRed+2, kGreen-6, kGreen+1,0,0,0,0,0, kAzure-6, kBlue-6, kBlue-10}; 	
	//Int_t colors[20] = {30,0,0,0,0,0,0,0,0, 50, 72, 8,0,0,0,0,0, 54, 51, 38}; 
	//Int_t colors[8] = {50, 66, 91, 0, 0, 59, 51, 8}; 

	// DY + WJets + Top + WW + WZ + ZZ
	// WJets + Top + WW + WZ + ZZ
	// Top + WW + WZ + ZZ
	// WW + WZ + ZZ
	// WZ + ZZ
	// ZZ
	for (int j = 0; j < 20; j++){
		if ( (j >=1 && j<=8) || (j >= 12 && j <= 16) ) continue;
		for (int i = j+1; i < 20; i++){
			hee_MC[j]->Add(hee_MC[i]);
			hmumu_MC[j]->Add(hmumu_MC[i]);
		}
		can->cd(1);
		hee_MC[j]->SetFillColor(colors[j]);
		hee_MC[j]->DrawCopy("same");
		can->cd(2);
		hee_MC[j]->SetMinimum(0.0009);
		hee_MC[j]->DrawCopy("same");
		can->cd(3);
		hmumu_MC[j]->SetFillColor(colors[j]);
		hmumu_MC[j]->DrawCopy("same");
		can->cd(4);
		hmumu_MC[j]->SetMinimum(0.0009);
		hmumu_MC[j]->DrawCopy("same");

		//cout << " ee    " << hee_MC[j]->GetName() << " " << hee_MC[j]->Integral();
		//cout << "    mumu  " << hmumu_MC[j]->GetName() << " " << hmumu_MC[j]->Integral() << endl;
	}
	for (int j = 0; j < 19; j++){
		if ( (j >=1 && j<=8) || (j >= 12 && j <= 16) ) continue;
		cout << " ee  " << hee_MC[j]->Integral() - hee_MC[j+1]->Integral();
		cout << "   mumu  " << hmumu_MC[j]->Integral() - hmumu_MC[j+1]->Integral() << endl;
	}
		cout << " ee  " << hee_MC[19]->Integral() ;
		cout << "   mumu  " << hmumu_MC[19]->Integral() << endl;
	
	
	// electrons
	can->cd(1);
	hee_data->DrawCopy("esame");
	can->cd(1)->RedrawAxis();
	
	can->cd(2);
	//for (int i = 1; i< 20; i++) {
	//	hee_MC[0]->Add(hee_MC[i]);
	//}
	//hee_MC[0]->SetMinimum(0.09);
	//hee_MC[0]->DrawCopy("same");
	hee_data->SetMinimum(0.0009);
	hee_data->DrawCopy("esame");
	can->cd(2)->RedrawAxis();
	
	// muons
	can->cd(3);
	hmumu_data->DrawCopy("esame");
	can->cd(3)->RedrawAxis();
	
	can->cd(4);
	hmumu_data->SetMinimum(0.0009);
	hmumu_data->DrawCopy("esame");
	can->cd(4)->RedrawAxis();


	can->cd(2);
	TLegend *leg = new TLegend(0.5, 0.55, 0.75, 0.8);
	leg->SetBorderSize(0);
	leg->SetFillStyle(0);
	TLegendEntry *entry=leg->AddEntry(hee_MC[0], "Z+Jets","f");
	entry->SetFillStyle(1001);
	entry->SetFillColor(kGreen-10);
	entry=leg->AddEntry(hee_MC[9], "W+Jets","f");
	entry->SetFillStyle(1001);
	entry->SetFillColor(kRed+2);
	entry=leg->AddEntry(hee_MC[10], "TTJets","f");
	entry->SetFillStyle(1001);
	entry->SetFillColor(kGreen-6);
	entry=leg->AddEntry(hee_MC[11], "Top","f");
	entry->SetFillStyle(1001);
	entry->SetFillColor(kGreen+1);
	entry=leg->AddEntry(hee_MC[17], "WZ","f");
	entry->SetFillStyle(1001);
	entry->SetFillColor(kAzure-6);
	entry=leg->AddEntry(hee_MC[18], "WW","f");
	entry->SetFillStyle(1001);
	entry->SetFillColor(kBlue-6);
	entry=leg->AddEntry(hee_MC[19], "ZZ","f");
	entry->SetFillStyle(1001);
	entry->SetFillColor(kBlue-10);
	entry=leg->AddEntry(hee_data, "data ee", "ple");
	entry->SetMarkerStyle(20);
	leg->Draw();

	can->cd(4);
	TLegend *leg2 = new TLegend(0.5, 0.55, 0.75, 0.8);
	leg2->SetBorderSize(0);
	leg2->SetFillStyle(0);
	entry=leg2->AddEntry(hee_MC[0], "Z+Jets","f");
	entry->SetFillStyle(1001);
	entry->SetFillColor(kGreen-10);
	entry=leg2->AddEntry(hee_MC[9], "W+Jets","f");
	entry->SetFillStyle(1001);
	entry->SetFillColor(kRed+2);
	entry=leg2->AddEntry(hee_MC[10], "TTJets","f");
	entry->SetFillStyle(1001);
	entry->SetFillColor(kGreen-6);
	entry=leg2->AddEntry(hee_MC[11], "Top","f");
	entry->SetFillStyle(1001);
	entry->SetFillColor(kGreen+1);
	entry=leg2->AddEntry(hee_MC[17], "WZ","f");
	entry->SetFillStyle(1001);
	entry->SetFillColor(kAzure-6);
	entry=leg2->AddEntry(hee_MC[18], "WW","f");
	entry->SetFillStyle(1001);
	entry->SetFillColor(kBlue-6);
	entry=leg2->AddEntry(hee_MC[19], "ZZ","f");
	entry->SetFillStyle(1001);
	entry->SetFillColor(kBlue-10);

	entry=leg2->AddEntry(hee_data, "data #mu #mu", "ple");
	entry->SetMarkerStyle(20);
	leg2->Draw();


	cout << hee_MC[0]->Integral() << endl;
	cout << hee_data->GetSumOfWeights() << endl << endl;
	cout << hmumu_MC[0]->Integral() << endl;
	cout << hmumu_data->GetSumOfWeights() << endl;

	
	for (int i = 0; i < 20; i++){
		MCFile[i]->Close();
	}
	eeDataFile->Close();
	mumuDataFile->Close();


}


