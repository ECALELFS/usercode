/////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Aug 17 18:06:26 2011 by ROOT version 5.27/06b
// from TTree data/Event Summary
// found on file: ../HZZ_ntuples/DoubleElectronPromptReco.root
//////////////////////////////////////////////////////////


#ifndef ZZ_Finalize_h
#define ZZ_Finalize_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH1F.h>
#include <TStopwatch.h>
#include <iostream>
#include <vector>
#include <string.h>
#include <TLorentzVector.h>

using namespace std;

class ZZ_Finalize {
public :
	TTree          *fChain;   //!pointer to the analyzed TTree or TChain
	Int_t           fCurrent; //!current Tree number in a TChain
	
	TString		outputFileName_;
	Int_t		isData_;
	Int_t		leptonType_;
	vector<TString > fileNames_;
	vector<TString > fileNamesNov_;
	TString outputDirectory_;
	TString Dataset_;
	float CrossSect_;

	Float_t Scaling_;

	char title[100];

	// Declaration of leaf types
	#include "Include/higgsVar_Nov.h"
	// List of branches
	#include "Include/higgsBranches_Nov.h"

	ZZ_Finalize();
	virtual ~ZZ_Finalize();
	virtual Int_t    Cut(Long64_t entry);
	virtual Int_t    GetEntry(Long64_t entry);
	virtual void     SetInput(TString dataset);
	virtual Long64_t LoadTree(Long64_t entry);
	virtual void     Init(TTree *tree);
	virtual void	 SetOutput();
	virtual void     Loop();
	virtual Bool_t   Notify();
	virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef ZZ_Finalize_cxx
ZZ_Finalize::ZZ_Finalize(){
	cout << endl;
	cout << "   ------------------------------------------------------------------- " << endl;
	cout << "   |                              Hi man,                            | " << endl;
	cout << "   |                      ready to make Science???                   | " << endl;
	cout << "   ------------------------------------------------------------------- " << endl;
	cout << endl; 

	leptonType_ = 0;
	isData_ = 0;
}

ZZ_Finalize::~ZZ_Finalize(){
   if (!fChain){
	cout << "Hello destructor" << endl;
	return;
   }
   cout << "See you man... [Destructor]" << endl;
}

void ZZ_Finalize::SetInput(TString dataset){

//------SET CROSS SECTION
	Dataset_ = dataset;
	if( Dataset_.Contains("Double") ){
	 CrossSect_ =1.;
	 isData_= 1;
		//if( Dataset_.Contains("Ele") ) leptonType_ = 11;
		//if( Dataset_.Contains("Mu") ) leptonType_ = 13.;
	}
	else if( Dataset_.Contains("DYJetsToLL") ) CrossSect_ = 3048.;		// DY
	else if( Dataset_.Contains("WJetsToLNu") ) CrossSect_ = 31314.;		// WJets
	else if( Dataset_.Contains("TTJets") ) CrossSect_ = 165.;		// TT
	else if( Dataset_.Contains("SingleT_tW") ) CrossSect_ = 7.87;		// T_tw
	else if( Dataset_.Contains("SingleTbar_tW") ) CrossSect_ = 7.87;	// Tbar_tw
	else if( Dataset_.Contains("SingleT_s") ) CrossSect_ = 3.19;		// T_s
	else if( Dataset_.Contains("SingleTbar_s") ) CrossSect_ = 1.44;	// Tbar_s
	else if( Dataset_.Contains("SingleT_t") ) CrossSect_ = 41.92;		// T_t
	else if( Dataset_.Contains("SingleTbar_t") ) CrossSect_ = 22.6;	// Tbar_t
	else if( Dataset_.Contains("WZ") ) CrossSect_ = 18.2;			// WZ
	else if( Dataset_.Contains("WW") ) CrossSect_ = 43.;			// WW
	else if( Dataset_.Contains("ZZ") ) CrossSect_ = 5.9;			// ZZ
	else cout<<"Dataset unknow... Try again."<<endl;

	cout<<"Dataset: "<<Dataset_<<" Cross Section: "<<CrossSect_<<" IsData: "<<isData_<<endl;

//------ADDING FILE AND COMPUTING Ngen
        Float_t nGen = 0.;
        Float_t Gen_app = 0.;

   FILE* iff = fopen(Dataset_+".txt","r");
   if(iff == 0) {
     std::cout << "Cannot open input file... now exiting." << std::endl;
     exit(-1);
   }
   char singleLine[500];
   TChain *chain = new TChain("evAnalyzer/data");
   TTree *tree = new TTree();

   while( fscanf(iff, "%s", singleLine) !=EOF ) {
	TString singleLine_str(singleLine);
	cout << "-> Adding " << singleLine_str << std::endl;

                TFile *f = new TFile(singleLine_str);
                f->cd("evAnalyzer/h2zz");
                TH1D *h = (TH1D*) gDirectory->Get("cutflow");
                cout <<"nGen = "<< h->GetBinContent(1) << endl;   
                Gen_app = h->GetBinContent(1);
                f->Close();
	nGen=nGen+Gen_app;
		// Open file
                chain->Add(singleLine_str);
   }//While
   fclose(iff);

	if( isData_==1 ){ CrossSect_=1.; nGen=1.; }

        cout  <<"MC luminosities (1 for Data): "<<nGen/CrossSect_<<endl;
        cout  <<"SCALING (Lumin. for Data ): "<<CrossSect_/nGen<<endl;

        Scaling_ = CrossSect_/nGen;


	if( isData_==1 ) Scaling_=1.;

        tree = chain;
        Init(tree);
	SetOutput();

	cout<<"OutputFileName: "<<outputFileName_<<endl;
}

Int_t ZZ_Finalize::GetEntry(Long64_t entry){
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}

void ZZ_Finalize::SetOutput(){
	if (isData_){
		outputDirectory_ = "Output/Data/";
		//if (leptonType_ == 11) outputFileName_ = outputDirectory_ + "histos" + "DoubleElectrons.root";
		//else if (leptonType_ == 13) outputFileName_ = outputDirectory_ + "histos" + "DoubleMuons.root";
		outputFileName_ = outputDirectory_ + "histos" + "DoubleData.root";
	}
	else {
		outputDirectory_ = "Output/MC/";
		outputFileName_ = outputDirectory_ + "histos" + Dataset_ + ".root";
	}
}


Long64_t ZZ_Finalize::LoadTree(Long64_t entry){
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

void ZZ_Finalize::Init(TTree *tree){
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

Bool_t ZZ_Finalize::Notify(){
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void ZZ_Finalize::Show(Long64_t entry){
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}

Int_t ZZ_Finalize::Cut(Long64_t entry){
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
	std::cout << entry << endl;
	return 1;
}
#endif // #ifdef ZZ_Finalize_cxx
