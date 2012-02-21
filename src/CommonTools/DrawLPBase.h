#include <iostream>
#include <vector>
#include <TChain.h>
#include <TLegend.h>
#include <THStack.h>
#include <TStyle.h>
#include <string>
#include <TPaveText.h>

namespace N_DATA{
	enum DATASET {DATA = 0, DY, WJ, TT, WW, WZ, ZZ};
}
using namespace std;
using namespace N_DATA;

class DrawLP {

public:
//contructor
DrawLP();
DrawLP( float lumi, bool dataFiles=true, bool isCMSArticle=false );
~DrawLP();

TTree *GetTree( string, string );

void BranchAdd( TTree *tree, string branch, float *varName );
void BranchAdd( TTree **tree, string branch, float *varName, int size );
void BranchAdd( TTree **tree, string branch, int *varName, int size );

void SetOutputdir( string OutputDir ){ OutputDir_ = OutputDir; };
bool getIsData(){ return dataFiles_; };
float getLumi(){ return lumi_; };

TPaveText* get_labelCMStop( bool wide ) const;
TPaveText* get_labelCMS( int legendQuadrant=0 ) const;
string get_lumiText() const;

TH1F** InitHistoTH1F(const char *name, const char *title, int size, int nbin, float xnim, float xmax );
void NormalFill( int Ndata, TTree **AllTree, TH1F **histo, float *varName, float *finWeight, float *LumiTot );
void NormalFill( int Ndata, TTree **AllTree, TH1F **histo, int *varName, float *finWeight, float *LumiTot );

TLegend* MakeLeg_Comparison(TH1F **h, float x1, float x2, float y1, float y2);
THStack* MakeStack(TH1F **h);
void Plot( TCanvas *myc1, THStack *Stack, TLegend *leg, TH1F *h1, string nameHisto, string TitleX, string Unity, bool log = true, string TitleY = "Events", bool yes_bin_onY = true );
void deleteHisto(TH1F **h, int size);

private:

string OutputDir_;
float lumi_;
bool dataFiles_;
bool isCMSArticle_;
TStyle *style_;
};
