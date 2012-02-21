#include <stdlib.h>
#include "TFile.h"
#include "TTree.h"
#include <iostream>
#include <cstring>
#include <string>
#include <TStyle.h>
#include <TCanvas.h>
#include <TH1.h>
#include <THStack.h>
#include <TF1.h>
#include <TStyle.h>
#include <TChain.h>
#include <TMath.h>
#include <TLegend.h>
#include "DrawLPBase.h"
#include "TPaveText.h"
#include <TROOT.h>

using namespace std;
using namespace N_DATA;

DrawLP::DrawLP( float lumi, bool dataFiles, bool isCMSArticle ) {

        lumi_ = lumi;
        dataFiles_ = dataFiles;
        isCMSArticle_ = isCMSArticle;

  style_ = new TStyle("DrawBaseStyle", "");
  style_->SetCanvasColor(0);
  style_->SetPadColor(0);
  style_->SetFrameFillColor(0);
  style_->SetStatColor(0);
  style_->SetOptStat(0);
  style_->SetTitleFillColor(0);
  style_->SetCanvasBorderMode(0);
  style_->SetPadBorderMode(0);
  style_->SetFrameBorderMode(0);
  style_->SetPadBottomMargin(0.12);
  style_->SetPadLeftMargin(0.12);
  style_->cd();
        
  // For the canvas:
    style_->SetCanvasBorderMode(0);
    style_->SetCanvasColor(kWhite);
    style_->SetCanvasDefH(600); //Height of canvas
    style_->SetCanvasDefW(600); //Width of canvas 
    style_->SetCanvasDefX(0);   //POsition on screen
    style_->SetCanvasDefX(0);   //POsition on screen
    style_->SetCanvasDefY(0);
        
  // For the Pad:
    style_->SetPadBorderMode(0);
    style_->SetPadColor(kWhite);
    style_->SetPadGridX(false);
    style_->SetPadGridY(false);
    style_->SetGridColor(0);
    style_->SetGridStyle(3);
    style_->SetGridWidth(1);

  // For the frame:
    style_->SetFrameBorderMode(0);
    style_->SetFrameBorderSize(1);
    style_->SetFrameFillColor(0);
    style_->SetFrameFillStyle(0);
    style_->SetFrameLineColor(1);
    style_->SetFrameLineStyle(1);
    style_->SetFrameLineWidth(1);
  // Margins:
    style_->SetPadTopMargin(0.10);//0.05);
    style_->SetPadBottomMargin(0.15);//0.13);
    style_->SetPadLeftMargin(0.15);//0.16);
    style_->SetPadRightMargin(0.05);//0.02);

  // For the Global title:

    style_->SetOptTitle(0);
    style_->SetTitleFont(42);
    style_->SetTitleColor(1);
    style_->SetTitleTextColor(1);
    style_->SetTitleFillColor(10);
    style_->SetTitleFontSize(0.05);

  // For the axis titles:

    style_->SetTitleColor(1, "XYZ");
    style_->SetTitleFont(42, "XYZ");
    style_->SetTitleSize(0.05, "XYZ");
    style_->SetTitleXOffset(1.15);//0.9);
    style_->SetTitleYOffset(1.4); // => 1.15 if exponents

  // For the axis labels:

    style_->SetLabelColor(1, "XYZ");
    style_->SetLabelFont(42, "XYZ");
    style_->SetLabelOffset(0.007, "XYZ");
    style_->SetLabelSize(0.045, "XYZ");

  // For the axis:

    style_->SetAxisColor(1, "XYZ");
    style_->SetStripDecimals(kTRUE);
    style_->SetTickLength(0.03, "XYZ");
    style_->SetNdivisions(510, "XYZ");
    style_->SetPadTickX(1);  // To get tick marks on the opposite side of the frame
    style_->SetPadTickY(1);

}; //Costructor

DrawLP::~DrawLP(){}; //Destructor

TTree *DrawLP::GetTree( string FilePath, string TreePath ) {

        TFile* File = TFile::Open( FilePath.c_str() );
	TTree *Tree = (TTree*)File->Get( TreePath.c_str() );

	return (TTree *)Tree;
};

void DrawLP::BranchAdd( TTree *tree, string branch, float *varName ) {

        tree->SetBranchAddress( branch.c_str(), varName);

};

void DrawLP::BranchAdd( TTree **tree, string branch, float *varName, int size ) {

        for(int i=0; i<size ;++i){
        tree[i]->SetBranchAddress( branch.c_str(), &varName[i]);
        }
};

void DrawLP::BranchAdd( TTree **tree, string branch, int *varName, int size ) {

        for(int i=0; i<size ;++i){
        tree[i]->SetBranchAddress( branch.c_str(), &varName[i]);
        }

};

/*  float x1, y1, x2, y2;
  if( legendQuadrant==1 ) {
    x1 = 0.63;
    y1 = 0.83;
    x2 = 0.8;
    y2 = 0.87;
  } else if( legendQuadrant==2 ) {
    x1 = (isCMSArticle_) ? 0.22 : 0.25;
    y1 = 0.83;
    x2 = (isCMSArticle_) ? 0.39 : 0.42;
    y2 = 0.87;
  } else if( legendQuadrant==3 ) {
    x1 = 0.25;
    y1 = 0.2;
    x2 = 0.42;
    y2 = 0.24;
  } else if( legendQuadrant==0 ) {
    x1 = 0.145;
    y1 = 0.953;
    x2 = 0.6;
    y2 = 0.975;
  }
*/

TPaveText* DrawLP::get_labelCMStop( bool wide ) const {

  float x1 = 0.;
  if ( dataFiles_ && isCMSArticle_) x1 = 0.25;
  else x1 = 0.25;//12;

 // TPaveText *label_cmstop = new TPaveText( x1, 0.91, 0.96, 0.98, "brNDC");
  TPaveText *label_cmstop = new TPaveText( x1, 0.91, 0.96, 0.96, "brNDC");
  label_cmstop->SetTextSize(0.043);
  label_cmstop->SetFillColor(0);
  label_cmstop->SetTextAlign(31); // align right

  std::string leftText;
  if( !dataFiles_ ) {
    leftText = "CMS Sim. 2012";
  } else {
    if( isCMSArticle_ )
      leftText = "CMS 2012";
    else
      leftText = "CMS Prel. 2012";
  }

  if (lumi_ > 0.) {
    label_cmstop->SetTextAlign(11); // align left
    std::string lumiText = this->get_lumiText();
    if( dataFiles_ ) lumiText = "L = " + lumiText+", #sqrt{s} = 7TeV";
    label_cmstop->AddText(Form("%s, %s", leftText.c_str(), lumiText.c_str()));
  } else {
    label_cmstop->SetTextAlign(11); // align left
    label_cmstop->AddText(Form("%s", leftText.c_str()));
  }

  return label_cmstop;

}

 std::string DrawLP::get_lumiText() const {

  float lumi4Text(lumi_);
  lumi4Text *= 1000000.; // in mub-1
  bool onlyOneDecimal=false;
  std::string units = "#mub^{-1}";
  if( lumi4Text > 10. ) {
    lumi4Text /= 1000.;
    units = "nb^{-1}";
  }
  if( lumi4Text > 100. ) {
    lumi4Text /= 1000.;
    units = "pb^{-1}";
  }
  if( lumi4Text >= 1000. ) {
    lumi4Text /= 1000.;
    units = "fb^{-1}";
  }
  if(  lumi4Text > 10. ) {
    onlyOneDecimal=true;
  }
  if( dataFiles_ ) {
    if( ((int)(lumi4Text*10.) % 10) == 0 ) onlyOneDecimal=true;
  }

  char lumiText[200];
  if( onlyOneDecimal )
    sprintf( lumiText, "%.0f %s", lumi4Text, units.c_str());
  else
    sprintf( lumiText, "%.1f %s", lumi4Text, units.c_str());

  std::string lumiText_str(lumiText);

  return lumiText;
}

TH1F** DrawLP::InitHistoTH1F(const char *name, const char *title, int size, int nbin, float xnim, float xmax ){
    TH1F **h = new TH1F*[size];
    char name_c[100];
    char title_c[200];

    for(int jR=0; jR<size; jR++)
    {
        sprintf(name_c, "%s%d", name, jR);
        sprintf(title_c, "%s%d", title, jR);
        h[jR] = new TH1F(name_c, title_c,  nbin, xnim, xmax);
       // h[jR]->GetXaxis()->SetTitle("Px");
    }
    return h;
}

void DrawLP::NormalFill( int Ndata, TTree **AllTree, TH1F **histo, float *varName, float *finWeight, float *LumiTot ){
 
       for( int i=0; i < Ndata; ++i ){
                for( int iEntry=0; iEntry<AllTree[i]->GetEntries(); iEntry++ ){
                AllTree[i]->GetEntry(iEntry);
                histo[i]->Fill(varName[i], finWeight[i]*LumiTot[i]);
                }
        }
}

void DrawLP::NormalFill( int Ndata, TTree **AllTree, TH1F **histo, int *varName, float *finWeight, float *LumiTot ){

       for( int i=0; i < Ndata; ++i ){
                for( int iEntry=0; iEntry<AllTree[i]->GetEntries(); iEntry++ ){
                AllTree[i]->GetEntry(iEntry);
                histo[i]->Fill(varName[i], finWeight[i]*LumiTot[i]);
                }
        }
}

TLegend* DrawLP::MakeLeg_Comparison(TH1F **h, float x1, float x2, float y1, float y2){

        TLegend *leg = new TLegend( x1, x2 , y1, y2);
        leg->SetFillColor(kWhite);
        leg->AddEntry(h[0],"DATA","P");
        leg->AddEntry(h[1],"DY","F");
        leg->AddEntry(h[2],"TT","F");
        leg->AddEntry(h[3],"WJ","F");
        leg->AddEntry(h[4],"WW","F");
        leg->AddEntry(h[5],"WZ","F");
        leg->AddEntry(h[6],"ZZ","F");
	return leg;
}

THStack* DrawLP::MakeStack(TH1F **hee_in_llPx){

        THStack* hee_in_llPx_S = new THStack("hee_in_llPx_S","");
        hee_in_llPx[TT]->SetFillColor(38);
        hee_in_llPx[TT]->SetLineColor(1);
        hee_in_llPx_S->Add(hee_in_llPx[TT]);
        hee_in_llPx[WJ]->SetFillColor(30);
        hee_in_llPx[WJ]->SetLineColor(1);
        hee_in_llPx_S->Add(hee_in_llPx[WJ]);
        hee_in_llPx[WZ]->SetFillColor(8);
        hee_in_llPx[WZ]->SetLineColor(1);
        hee_in_llPx_S->Add(hee_in_llPx[WZ]);
        hee_in_llPx[ZZ]->SetFillColor(kRed);
        hee_in_llPx[ZZ]->SetLineColor(1);
        hee_in_llPx_S->Add(hee_in_llPx[ZZ]);
        hee_in_llPx[WW]->SetFillColor(7);
        hee_in_llPx[WW]->SetLineColor(1);
        hee_in_llPx_S->Add(hee_in_llPx[WW]);
        hee_in_llPx[DY]->SetFillColor(39);
        hee_in_llPx[DY]->SetLineColor(1);
        hee_in_llPx_S->Add(hee_in_llPx[DY]);
	return hee_in_llPx_S;
}

void DrawLP::Plot( TCanvas *myc1, THStack *Stack, TLegend *leg, TH1F *h1, string nameHisto, string TitleX, string Unity, bool log,  string TitleY, bool yes_bin_onY ){

	string OutputDir;
	if( OutputDir_ != "" )  OutputDir = OutputDir_;
	else		        OutputDir = ".";

	char bin[33]={'\0'};
	float Nbin = h1->GetBinWidth(1);
	string NewYaxis;
if( yes_bin_onY ){
	if( Nbin<0.1 ) sprintf( bin, "%.2f",Nbin );
	else if( ((int)(10.*Nbin) % 10) == 0  ) sprintf( bin, "%.0f",Nbin );
	else sprintf( bin, "%.1f",Nbin );
	NewYaxis = TitleY + " / " + bin + " " + "[" + Unity + "]";	
}
else    NewYaxis = TitleY;
	string NewXaxis;
	if (Unity=="") NewXaxis = TitleX;
	else NewXaxis = TitleX + " " + "[" + Unity + "]";

        myc1->cd();
        myc1->UseCurrentStyle();//("DrawBaseStyle");
	Stack->Draw("HISTO");
        Stack->GetXaxis()->SetTitle(NewXaxis.c_str());
        Stack->GetYaxis()->SetTitle(NewYaxis.c_str());
        myc1->Modified();
        h1->SetMarkerStyle(20);
        h1->SetMarkerColor(1);
        h1->SetMarkerSize(1);
        h1->Draw("Esame");
        leg->Draw("same");
        TPaveText *label_cms = get_labelCMStop(0);
        label_cms->Draw("same");
	string newName = OutputDir + "/" + nameHisto + ".png";
        myc1->SaveAs(newName.c_str());
	if( log ){
	myc1->SetLogy();
        Stack->Draw("HISTO");
        Stack->GetXaxis()->SetTitle(NewXaxis.c_str());
        Stack->GetYaxis()->SetTitle(NewYaxis.c_str());
        myc1->Modified();
        h1->SetMarkerStyle(20);
        h1->SetMarkerColor(1);
        h1->SetMarkerSize(1);
        h1->Draw("Esame");
        leg->Draw("same");
        TPaveText *label_cms = get_labelCMStop(0);
        label_cms->Draw("same");
	string newName = OutputDir + "/" + nameHisto + "_log.png";
        myc1->SaveAs(newName.c_str());
	}
}

void  DrawLP::deleteHisto(TH1F **h, int size){
    for(int jR=0; jR<size; jR++)
        delete h[jR];

    delete h;
}

