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

    if(argc!=2 ){
    cout<<"Wrong number of argument"<<endl;
    cout<<"Correct usage: ./ZZ_Finalize [arg]"<<endl;
    cout<<" Where [arg] is the Dataset (you must have a dataset.txt who contain the path of the inputFile)"<<endl;
    return -1;
    }

	TString input(argv[1]);

	ZZ_Finalize *Analysis = new ZZ_Finalize();
	Analysis->SetInput(input);
	Analysis->Loop();

	delete Analysis;

	Analysis=0;

return 0;

}
