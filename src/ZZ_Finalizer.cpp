#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH1F.h>
#include <TStopwatch.h>
#include <iostream>
#include <vector>
#include <string>
#include <TLorentzVector.h>

#include "ZZ_Finalize.h"

using namespace std;
  
int main(int argc, char* argv[]){

    if(argc!=2 && argc!=3 ){
    cout<<"Wrong number of argument"<<endl;
    cout<<"Correct usage: ./ZZ_Finalize [arg]"<<endl;
    cout<<" Where [arg] can be: LoopOnElectrons, LoopOnMuons, LoopOnLeptons, LoopOnBG, DoEverything"<<endl;
    cout<<"Or: ./ZZ_Finalize [arg1] [arg2]"<<endl;
    cout<<" Where [arg1] is: Plot. And [arg2] is the name of histogram."<<endl;
    return -1;
    }

	ZZ_Finalize *Analysis = new ZZ_Finalize();

	if(argc == 2){

	 if( strcmp(argv[1],"LoopOnElectrons")==0 ){
	 Analysis->LoopOnElectrons();
	 }
         else if( strcmp(argv[1],"LoopOnMuons")==0 ){
         Analysis->LoopOnMuons();
         }
         else if( strcmp(argv[1],"LoopOnLeptons")==0 ){
         Analysis->LoopOnLeptons();
         }
         else if( strcmp(argv[1],"LoopOnBG")==0 ){
         Analysis->LoopOnBG();
         }
         else if( strcmp(argv[1],"DoEverything")==0 ){
         Analysis->DoEverything();
         }
         else if( strcmp(argv[1],"Plot")==0 ){
         cout<<"Sorry man, Plot requires 2 arguments"<<endl;
         }
         else{
         cout<<"Sorry man, this command is not defined"<<endl;
	 cout<<"Correct usage: ./ZZ_Finalize [arg]"<<endl;
	 cout<<" Where [arg] can be: LoopOnElectrons, LoopOnMuons, LoopOnLeptons, LoopOnBG, DoEverything"<<endl;
	 cout<<"Or: ./ZZ_Finalize [arg1] [arg2]"<<endl;
	 cout<<" Where [arg1] is: Plot. And [arg2] is the name of histogram."<<endl;
         }
	}//if(argc == 2)

        if(argc == 3){
         if( strcmp(argv[1],"Plot")==0 ){
         Analysis->Plot( argv[2] );
         }
         else{
         cout<<"Sorry man, this command is not defined."<<endl;
         cout<<"Correct usage: ./ZZ_Finalize [arg]"<<endl;
         cout<<" Where [arg] can be: LoopOnElectrons, LoopOnMuons, LoopOnLeptons, LoopOnBG, DoEverything"<<endl;
         cout<<"Or: ./ZZ_Finalize [arg1] [arg2]"<<endl;    cout<<" Where [arg1] is: Plot. And [arg2] is the name of histogram."<<endl;
         }
	}//if(argc == 3)

delete Analysis;

Analysis=0;

return 0;

}
