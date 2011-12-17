/////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Aug 17 18:06:26 2011 by ROOT version 5.27/06b
// from TTree data/Event Summary
// found on file: ../HZZ_ntuples/DoubleElectronPromptReco.root
//////////////////////////////////////////////////////////


#ifndef higgsAna_h
#define higgsAna_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH1F.h>
#include <TStopwatch.h>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class higgsAna {
public :
	TTree          *fChain;   //!pointer to the analyzed TTree or TChain
	Int_t           fCurrent; //!current Tree number in a TChain
	
	TString		outputFileName;
	Int_t		isData;
	Int_t		leptonType;
	Int_t		whichFile;
	vector<TString > fileNames;
	vector<TString > fileNamesNov;
	TString dataDirectory;
	TString outputDirectory;

	Float_t eeScaling[20];
	Float_t mumuScaling[20];

	char title[100];

	// Declaration of leaf types
	#include "Include/higgsVar_Nov.h"
	// List of branches
	#include "Include/higgsBranches_Nov.h"


	higgsAna();
	virtual ~higgsAna();
	virtual Int_t    Cut(Long64_t entry);
	virtual Int_t    GetEntry(Long64_t entry);
	virtual Long64_t LoadTree(Long64_t entry);
	virtual void     Init(TTree *tree);
	virtual void	 SetFiles(int which=0);
	virtual void	 OpenFiles(int which=0, TTree *tree=0);
	virtual void     Loop();
	virtual void	 LoopOnElectrons();
	virtual void	 LoopOnMuons();
	virtual void	 LoopOnLeptons();
	virtual void	 LoopOnBG();
	virtual void 	 DoEverything();
	virtual void	 Plot(string histoName);
	virtual Bool_t   Notify();
	virtual void     Show(Long64_t entry = -1);


};

#endif

#ifdef higgsAna_cxx
higgsAna::higgsAna()
{
	cout << endl;
	cout << "   ------------------------------------------------------------------- " << endl;
	cout << "   |    Bonjour, vous êtes actuellementa la recherche du boson de   | " << endl;
	cout << "   |            Brout-Englert-Higgs-Hagen-Guralnik-Kibble            | " << endl;
	cout << "   ------------------------------------------------------------------- " << endl;
	cout << endl; 

	dataDirectory = "/user/aleonard/HZZ_ntuples_Nov/";
	leptonType = 0;
      
	fileNames.push_back("DoubleElectronPromptRecov4.root");   		// 0
       	fileNames.push_back("DoubleElectronMay10ReReco.root");  		// 1
       	fileNames.push_back("DoubleElectronPromptRecov6.root");                 // 2
       	fileNames.push_back("DoubleElectron05AugReReco.root");  		// 3
	fileNames.push_back("DoubleElectronPromptReco_2011B.root");		// 4
       	fileNames.push_back("DoubleMuPromptRecov4.root");         		// 5
       	fileNames.push_back("DoubleMuMay10ReReco.root");        		// 6
       	fileNames.push_back("DoubleMuPromptRecov6_172620_173244.root");         // 7
	fileNames.push_back("DoubleMuPromptRecov6_173380_173692.root");		// 8
       	fileNames.push_back("DoubleMu05AugReReco.root");        		// 9
	fileNames.push_back("DoubleMuPromptReco_2011B.root");			// 10
       	fileNames.push_back("DYJetsToLL_0.root");                 		// 11
       	fileNames.push_back("DYJetsToLL_1.root");                 		// 12
       	fileNames.push_back("DYJetsToLL_2.root");                 		// 13
       	fileNames.push_back("DYJetsToLL_3.root");                 		// 14
       	fileNames.push_back("DYJetsToLL_4.root");                 		// 15
       	fileNames.push_back("DYJetsToLL_5.root");                 		// 16
       	fileNames.push_back("DYJetsToLL_6.root");                 		// 17
       	fileNames.push_back("DYJetsToLL_7.root");                 		// 18
       	fileNames.push_back("DYJetsToLL_8.root");                 		// 19
       	fileNames.push_back("WJetsToLNu.root");                 		// 20
       	fileNames.push_back("TTJets.root");                     		// 21
       	fileNames.push_back("SingleT_tW.root");                 		// 22
       	fileNames.push_back("SingleTbar_tW.root");              		// 23
       	fileNames.push_back("SingleT_s.root");                 			// 24
       	fileNames.push_back("SingleTbar_s.root");              			// 25
       	fileNames.push_back("SingleT_t.root");                 			// 26
       	fileNames.push_back("SingleTbar_t.root");              			// 27
       	fileNames.push_back("WZ.root");                   			// 28
       	fileNames.push_back("WW.root");                  			// 29
       	fileNames.push_back("ZZ.root");                  			// 30
       	fileNames.push_back("GGtoH170toZZto2L2Nu.root");        		// 31
       	fileNames.push_back("GGtoH180toZZto2L2Nu.root");       			// 32
       	fileNames.push_back("GGtoH200toWWto2L2Nu.root");        		// 33
       	fileNames.push_back("GGtoH200toZZto2L2Nu.root");        		// 34
       	fileNames.push_back("GGtoH300toZZto2L2Nu.root");        		// 35
       	fileNames.push_back("GGtoH500toZZto2L2Nu.root");        		// 36
       	fileNames.push_back("VBFtoH200toZZto2L2Nu.root");       		// 37
       	fileNames.push_back("VBFtoH300toZZto2L2Nu.root");       		// 38
       	fileNames.push_back("VBFtoH500toZZto2L2Nu.root");       		// 39
	
	Float_t xsec[20];
	for (int i = 0; i < 9; i++){
		xsec[i] = 3048.;
	}
	xsec[9] = 31314.; xsec[10] = 165.; xsec[11] = 7.87; xsec[12] = 7.87; xsec[13] = 3.19; xsec[14] = 1.44;
	xsec[15] = 41.92; xsec[16] = 22.6; xsec[17] = 18.2; xsec[18] = 43.; xsec[19] = 5.9;  

	Float_t nGen[20];

	cout << endl;

	for (int i = 0; i < 20; i++){
		TFile *f = new TFile(dataDirectory+fileNames[i+11]);
		f->cd("evAnalyzer/h2zz");
		TH1D *h = (TH1D*) gDirectory->Get("cutflow");
		cout <<" nGen  " << i << "  " << h->GetBinContent(1) << endl;	
		nGen[i] = h->GetBinContent(1);
		f->Close();	
	}
	
	float temp = 0;
	for (int i = 0; i < 9; i++){
		temp += nGen[i];
	}
	for (int i = 0; i < 9; i++){
		nGen[i] = temp;
		cout << "ngen_" << i << "  " << nGen[i] << endl;
	}

	
	cout << endl  << " MC luminosities "  << endl;
	for (int i =0; i <20; i++){
		cout << "Lumi " << i << "  = " << nGen[i]*1./xsec[i] << endl; 
	}
	 
	cout << endl << "Scaling" << endl;
	
	
	for (int i = 0; i < 20; i++){
		eeScaling[i] = 4615.*xsec[i]*1./nGen[i];
		mumuScaling[i] = eeScaling[i];
		cout << eeScaling[i] << endl;
	}
	

}

higgsAna::~higgsAna()
{
   if (!fChain){
	cout << "Hello destructor" << endl;
	return;
   }
   cout << "Hello delete" << endl;
   //delete fChain->GetCurrentFile();
}

Int_t higgsAna::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}

void higgsAna::SetFiles(int which)
{
	if (isData){
		outputDirectory = "Output/Data/";
		if (leptonType == 11) outputFileName = outputDirectory + "histos" + "DoubleElectrons.root";
		else if (leptonType == 13) outputFileName = outputDirectory + "histos" + "DoubleMuons.root";
	}
	else {
		outputDirectory = "Output/MC/";
		outputFileName = "Output/MC/histos"+fileNames[which];
	}
}

void higgsAna::OpenFiles(int which, TTree *tree)
{	

	if (tree == 0){
                TChain *chain = new TChain("evAnalyzer/data");
                if (isData){
                        if (leptonType==11){
                                chain->Add(dataDirectory+fileNames[0]);
                                chain->Add(dataDirectory+fileNames[1]);
                                chain->Add(dataDirectory+fileNames[2]);
                                chain->Add(dataDirectory+fileNames[3]);
                                chain->Add(dataDirectory+fileNames[4]);
				
                        }
                        else if (leptonType==13){
                                chain->Add(dataDirectory+fileNames[5]);
                                chain->Add(dataDirectory+fileNames[6]);
                                chain->Add(dataDirectory+fileNames[7]);
                                chain->Add(dataDirectory+fileNames[8]);
                                chain->Add(dataDirectory+fileNames[9]);
                                chain->Add(dataDirectory+fileNames[10]);
                        }
                }
                else {
                        chain->Add(dataDirectory+fileNames[which]);
                }
                tree = chain;
        }
        Init(tree);
	
}

void higgsAna::LoopOnElectrons()
{
        isData = 1;
        leptonType = 11;
        sprintf(title, "electrons");
	SetFiles();
        OpenFiles();
        Loop();
}

void higgsAna::LoopOnMuons() 
{
        isData = 1;
        leptonType = 13;
        sprintf(title, "muons");
	SetFiles();
        OpenFiles();
        Loop();
}

void higgsAna::LoopOnLeptons()
{
        LoopOnElectrons();
        LoopOnMuons();
}

void higgsAna::LoopOnBG()
{
        isData = 0;
        for (int i = 11; i <31; i++){
                SetFiles(i);
		OpenFiles(i);
                Loop();
        } 
}

void higgsAna::DoEverything(){
	LoopOnLeptons();
	LoopOnBG();
	Plot("MET1Pt");
	Plot("llMass");
}

Long64_t higgsAna::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (!fChain->InheritsFrom(TChain::Class()))  return centry;
   TChain *chain = (TChain*)fChain;
   if (chain->GetTreeNumber() != fCurrent) {
      fCurrent = chain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void higgsAna::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   #include "Include/higgsSetBranches.h"   
   Notify();
}

Bool_t higgsAna::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void higgsAna::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t higgsAna::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
	std::cout << entry << endl;
	return 1;
}
#endif // #ifdef higgsAna_cxx
