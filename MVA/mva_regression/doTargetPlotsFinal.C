{
  tdrStyle->SetOptStat(1111);
  //  TFile *fileVariables = TFile::Open("root://eoscms//eos/cms/store/group/phys_egamma/emanuele/elereg/eletrees/V2/ZjetsMad_Summer12.root");
  TFile *fileVariables = TFile::Open("ZjetsMad_Summer12.Testing.root");
  //  TFile *fileTarget_ptSplit = TFile::Open("targets_ZjetsMad_Summer12/new/ElectronEnergyRegression_ptSplit_Testing_V11_nTrees_100.root");
  TFile *fileTarget_Final = TFile::Open("targetsHZZwZtrain/ECAL_Tracker_Split/ElectronEnergyRegression_Final_V00.root");
  TFile *fileTarget_ECALandP = TFile::Open("targetsHZZwZtrain/ECAL_Tracker_Split/Wpt_ptSplitElectronEnergyRegression_V00_splitEtaAndPt.root");

  TTree* tree=(TTree*)fileVariables->Get("T1");
  tree->AddFriend("targeteb_tree",fileTarget_ECALandP);
  tree->AddFriend("targetebvar_tree",fileTarget_ECALandP);
  tree->AddFriend("targetee_tree",fileTarget_ECALandP);
  tree->AddFriend("targeteevar_tree",fileTarget_ECALandP);
  tree->AddFriend("targetp1_1tree",fileTarget_ECALandP);
  tree->AddFriend("targetp1_1var_tree",fileTarget_ECALandP);
  tree->AddFriend("targetp1_2tree",fileTarget_ECALandP);
  tree->AddFriend("targetp1_2var_tree",fileTarget_ECALandP);
  tree->AddFriend("targetp1_3tree",fileTarget_ECALandP);
  tree->AddFriend("targetp1_3var_tree",fileTarget_ECALandP);
  tree->AddFriend("targetp2_1tree",fileTarget_ECALandP);
  tree->AddFriend("targetp2_1var_tree",fileTarget_ECALandP);
  tree->AddFriend("targetp2_2tree",fileTarget_ECALandP);
  tree->AddFriend("targetp2_2var_tree",fileTarget_ECALandP);
  tree->AddFriend("targetp2_3tree",fileTarget_ECALandP);
  tree->AddFriend("targetp2_3var_tree",fileTarget_ECALandP);
  tree->AddFriend("targetp3_1tree",fileTarget_ECALandP);
  tree->AddFriend("targetp3_1var_tree",fileTarget_ECALandP);
  tree->AddFriend("targetp3_2tree",fileTarget_ECALandP);
  tree->AddFriend("targetp3_2var_tree",fileTarget_ECALandP);
  tree->AddFriend("targetp3_3tree",fileTarget_ECALandP);
  tree->AddFriend("targetp3_3var_tree",fileTarget_ECALandP);

  /*  tree->AddFriend("targetebECALP_tree",fileTarget_Final);
  tree->AddFriend("targeteeECALP_tree",fileTarget_Final);
  tree->AddFriend("targetebECALPvar_tree",fileTarget_Final);
  tree->AddFriend("targeteeECALPvar_tree",fileTarget_Final);
  */
  TString binning="(100,-0.7,0.7)";
  TString option="HZZ";
 
  TCut statusenergycut="(GeneratedEnergyStatus3-GeneratedEnergyStatus1)/GeneratedEnergyStatus3<0.01 && GeneratedEnergyStatus3>=GeneratedEnergyStatus1";
  TCut isEB="abs(eta)<1.479";
  TCut isEE="abs(eta)>1.479 && abs(eta)<2.5";
  TCut ptCut="pt<15";
  TCut mcMatchCut="mcmatch==1";
  TCut fiducialcut="(abs(eta)<1.4442 || abs(eta)>1.556)";
  TCut etasplit[3];
  TCut ptsplit[3];

  etasplit[0]="abs(eta)<1";
  etasplit[1]="abs(eta)>1 && abs(eta)<1.479";
  etasplit[2]="abs(eta)>1.479";
  ptsplit[0]="pt<15"; 
  ptsplit[1]="pt>15 && pt<25";
  ptsplit[2]="pt>25";
  statusenergycut="(GeneratedEnergyStatus3-GeneratedEnergyStatus1)/GeneratedEnergyStatus3<0.01 && GeneratedEnergyStatus3>=GeneratedEnergyStatus1";

  THStack noRegStackEta[3];
  THStack RegStackEta[3];

  THStack noRegStackPt[3];
  THStack RegStackPt[3];


  for(int i=0;i<=2;++i){
    for(int j=0;j<=2;++j){
      stringstream ii,jj,iii,jjj;
      ii<<(i+1);
      jj<<(j+1);
      iii<<i;
      jjj<<j;
      TCut etaCut=etasplit[i];
      TCut ptCut=ptsplit[j];
      if((i+1)!=3 && (j+1)<2){
      tree->Draw(" ( GeneratedEnergyStatus3-pmodegsf ) /GeneratedEnergyStatus3 >> hnoreg"+TString(TString(ii.str())+"_"+TString(jj.str())+binning), mcMatchCut && statusenergycut && etaCut && ptCut,"p");
      tree->Draw(" ( GeneratedEnergyStatus3-pmodegsf*targetp"+TString(ii.str())+"_"+TString(jj.str())+" ) /GeneratedEnergyStatus3 >> hreg"+TString(TString(ii.str())+"_"+TString(jj.str())+binning), mcMatchCut && statusenergycut && etaCut && ptCut,"same");
      }else{
      tree->Draw(" ( GeneratedEnergyStatus3-pmodegsf*targetp"+TString(ii.str())+"_"+TString(jj.str())+" ) /GeneratedEnergyStatus3 >> hreg"+TString(TString(ii.str())+"_"+TString(jj.str())+binning), mcMatchCut && statusenergycut && etaCut && ptCut);
      tree->Draw(" ( GeneratedEnergyStatus3-pmodegsf ) /GeneratedEnergyStatus3 >> hnoreg"+TString(TString(ii.str())+"_"+TString(jj.str())+binning), mcMatchCut && statusenergycut && etaCut && ptCut,"samep");
      }
      gROOT->ProcessLine("hreg"+TString(ii.str())+"_"+TString(jj.str())+"->SetLineColor(kRed)");
      c1->SaveAs("plots/DiffEtaAndPtSplit_"+TString(ii.str())+"_"+TString(jj.str())+".png");


      gROOT->ProcessLine("noRegStackEta["+TString(iii.str())+"].Add(hnoreg"+TString(TString(ii.str())+"_"+TString(jj.str()))+")");
      gROOT->ProcessLine("RegStackEta["+TString(iii.str())+"].Add(hreg"+TString(TString(ii.str())+"_"+TString(jj.str()))+")");
      gROOT->ProcessLine("noRegStackPt["+TString(jjj.str())+"].Add(hnoreg"+TString(TString(ii.str())+"_"+TString(jj.str()))+")");
      gROOT->ProcessLine("RegStackPt["+TString(jjj.str())+"].Add(hreg"+TString(TString(ii.str())+"_"+TString(jj.str()))+")");

  
    }
  }
  //  tree->Draw("(((pmodegsf*targetp/pow(targetpvar*pmodegsf,2)+SCRawEnergy*targeteb/pow(targetebvar*SCRawEnergy,2))/(1/pow(targetpvar*pmodegsf,2)+1/pow(targetebvar*SCRawEnergy,2)))*targetebECALP-GeneratedEnergyStatus3)/GeneratedEnergyStatus3>>hPtSplit_eb(100,-0.5,0.5)",energycut && isEB && ptCut && mcMatchCut,"ep");
  //  hPtSplit_eb->SetLineColor(kRed);

  for(int i=0;i<=2;++i){
    stringstream ii;
    ii<<i+1;
    RegStackEta[i].Draw();
    noRegStackEta[i].Draw("samep");

    c1->SaveAs("plots/DiffInclusiveEta"+TString(ii.str())+".png"); 


    noRegStackPt[i].Draw("p");
    RegStackPt[i].Draw("same");
    noRegStackPt[i].Draw("psame");
    c1->SaveAs("plots/DiffInclusivePt"+TString(ii.str())+".png"); 


  }

}
