// -*- C++ -*-
//
// Package:    NewPi0Dumper_Gun
// Class:      NewPi0Dumper_Gun
// 
/**\class NewPi0Dumper_Gun NewPi0Dumper_Gun.cc  ,Analysis/Modules/src/NewPi0Dumper_Gun.cc

Description: [one line class summary]

Implementation:
[Notes on implementation]
 */
//
// Original Author:  Shahram Rahatlou
//         Created:  Wed Aug 25 10:44:55 CEST 2010
// $Id: NewPi0Dumper_Gun.cc,v 1.1 2013/02/04 13:18:49 lpernie Exp $
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "FWCore/Framework/interface/ESHandle.h"

#include <vector>
#include <iostream>
#include <utility>
#include "TRegexp.h"
using std::vector;
using std::cout;
using std::endl;
using std::pair;
#include <cmath>
#include<algorithm>
using std::max_element;
#include <string>
#include <set>
using std::set;

//Geom
#include "Geometry/CaloGeometry/interface/CaloSubdetectorGeometry.h"
#include "RecoEcal/EgammaCoreTools/interface/PositionCalc.h"
#include "FWCore/Framework/interface/ESHandle.h"
//ES
#include "Geometry/CaloTopology/interface/EcalPreshowerTopology.h"
#include "Geometry/EcalAlgo/interface/EcalPreshowerGeometry.h"
#include "Analysis/CalibTools/interface/EcalPreshowerHardcodedGeometry.h"
#include "Analysis/CalibTools/interface/EcalPreshowerHardcodedTopology.h"
//#include "Analysis/CalibTools/interface/PreshowerCluster.h"
#include "Analysis/CalibTools/interface/PreshowerTools.h"
#include "Analysis/CalibTools/interface/GeometryService.h"
#include "Analysis/CalibTools/interface/EndcapTools.h"
//EB Cont Correction
#include "Analysis/CalibTools/interface/EcalEnerCorr.h"
#include "DataFormats/BeamSpot/interface/BeamSpot.h"
//PF
#include "DataFormats/ParticleFlowReco/interface/PFCluster.h"

#include "Geometry/CaloTopology/interface/CaloTopology.h"
#include "DataFormats/EcalDetId/interface/EcalSubdetector.h"
#include "Geometry/CaloTopology/interface/EcalBarrelHardcodedTopology.h"
#include "Geometry/CaloTopology/interface/EcalEndcapHardcodedTopology.h"
#include "Analysis/Pi0Calib/interface/ECALGeometry.h"
#include "DataFormats/CaloRecHit/interface/CaloCluster.h"
#include "Analysis/Pi0Calib/interface/EcalCalibMap.h"
#include "DataFormats/Math/interface/Point3D.h"
#include "DataFormats/Math/interface/LorentzVector.h"
#include "DataFormats/EcalRecHit/interface/EcalRecHitCollections.h"
#include "DataFormats/EcalDetId/interface/EBDetId.h"
#include "DataFormats/EcalDetId/interface/EEDetId.h"
#include "DataFormats/EcalDetId/interface/EcalSubdetector.h"

#include "Analysis/Pi0Calib/interface/EcalRecHitCompare.h"
#include "Analysis/Pi0Calib/interface/PosCalcParams.h"
#include "Analysis/Pi0Calib/interface/GlobalFunctions.h"

#include "DataFormats/HcalRecHit/interface/HcalRecHitCollections.h"
#include "RecoCaloTools/MetaCollections/interface/CaloRecHitMetaCollections.h"
#include "Geometry/Records/interface/CaloGeometryRecord.h"
#include "Geometry/CaloGeometry/interface/CaloGeometry.h"
#include "RecoCaloTools/Selectors/interface/CaloConeSelector.h"
#include "Geometry/CaloGeometry/interface/CaloCellGeometry.h"
#include "MagneticField/Engine/interface/MagneticField.h"
#include "MagneticField/Records/interface/IdealMagneticFieldRecord.h"

// Trigger
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutRecord.h"
#include "CondFormats/L1TObjects/interface/L1GtTriggerMenu.h"
#include "CondFormats/DataRecord/interface/L1GtTriggerMenuRcd.h"
#include "CondFormats/L1TObjects/interface/L1GtTriggerMenuFwd.h"
#include "FWCore/Framework/interface/TriggerNamesService.h"
#include <FWCore/Common/interface/TriggerNames.h>
#include <DataFormats/Common/interface/TriggerResults.h>

// MC
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"
#include "SimDataFormats/Track/interface/SimTrack.h"
#include "SimDataFormats/Track/interface/SimTrackContainer.h"
#include "SimDataFormats/Vertex/interface/SimVertex.h"
#include "SimDataFormats/Vertex/interface/SimVertexContainer.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

// conversions
#include "DataFormats/EgammaCandidates/interface/Conversion.h"
#include "DataFormats/EgammaCandidates/interface/ConversionFwd.h"

#include "DataFormats/JetReco/interface/PFJet.h"
#include "DataFormats/JetReco/interface/PFJetCollection.h"
#include "DataFormats/METReco/interface/CaloMETCollection.h"
#include "DataFormats/METReco/interface/CaloMET.h"
#include "DataFormats/METReco/interface/PFMET.h"
#include "DataFormats/METReco/interface/PFMETCollection.h"
#include "JetMETCorrections/Objects/interface/JetCorrector.h"

#include "RecoEcal/EgammaCoreTools/interface/EcalClusterTools.h"

//Laser and transparency loss
#include "CalibCalorimetry/EcalLaserAnalyzer/interface/MEEBGeom.h"
#include "CalibCalorimetry/EcalLaserAnalyzer/interface/MEEEGeom.h"
#include "DataFormats/Provenance/interface/Timestamp.h"

#include "FWCore/Framework/interface/ModuleFactory.h"
#include "FWCore/Framework/interface/ESProducer.h"

#include "CondFormats/EcalObjects/interface/EcalLaserAlphas.h"
#include "CondFormats/EcalObjects/interface/EcalLaserAPDPNRatiosRef.h"
#include "CondFormats/EcalObjects/interface/EcalLaserAPDPNRatios.h"

#include "CondFormats/DataRecord/interface/EcalLaserAlphasRcd.h"
#include "CondFormats/DataRecord/interface/EcalLaserAPDPNRatiosRefRcd.h"
#include "CondFormats/DataRecord/interface/EcalLaserAPDPNRatiosRcd.h"

// root
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include <TH1F.h>
#include <TH2F.h>
#include "TLorentzVector.h"
#include "TVector3.h"

//using math::TVector3;

#define PTBINSEB 7
#define PTBINSEE 5
#define N_IETA 86
#define N_ETARING 78
#define N_iPHI 360
//#define CHECKIETACORR
//#define INDEXETA65
//#define TTREEMVA
//#define DEBUGMVA

//Function
double max_array(double *A, int n);
double max(double x, double y);

//
// class declaration
//

struct gammaTracker {
    TVector3 pi0;
    TLorentzVector gamma;
    bool IsEB;
    bool IsConverted;
    bool IsGoodPi0;
    gammaTracker() : pi0(0.,0.,0.), gamma(0.,0.,0.,0.), IsEB(false), IsConverted(true), IsGoodPi0(false) { }
} gamma1, gamma2, gamma1ES, gamma2ES;

struct ClusterShape {
    float s1;
    float s4;
    float s9;
    float s25;
    float s4s9;
    float time;
    float ncry9;
    float ncry25;
    int flag;

    // major and minor cluster moments wrt principale axes:
    float sMaj9;
    float sMin9;
    float sMaj25;
    float sMin25;
    float sMaj49;
    float sMin49;

    float transparencyLoss;
    //float transparencyLossInvertZSide;
    float laserCorr;
    float alpha;

    ClusterShape() : s1(-99.), s4(-99.), s9(-99.), s25(-99.), s4s9(-1.), 
    time(-9999.), ncry9(-1), ncry25(-1), flag(0.) ,
    sMaj9(-99.), sMin9(-99.), 
    sMaj25(-99.), sMin25(-99.),
    sMaj49(-99.), sMin49(-99.), 
    transparencyLoss(-99.),
    laserCorr(-99.), alpha(-99)
    { }
};

#define NPFJETMAX 20
#define NCRYMAX 1000
#define NCLUMAX 500
#define NPI0MAX 400
#define NCONVMAX 500

using namespace reco;

class NewPi0Dumper_Gun : public edm::EDAnalyzer {
    public:
	  explicit NewPi0Dumper_Gun(const edm::ParameterSet&);
	  ~NewPi0Dumper_Gun();


    private:
	  virtual void beginJob() ;
	  virtual void analyze(const edm::Event&, const edm::EventSetup&);
	  virtual void endJob() ;

	  //void FillTriggerInfo(const edm::Event&, const edm::EventSetup&);
	  bool GetHLTResults(const edm::Event& iEvent, std::string s);
	  void FillMCInfo(const edm::Event&, const edm::EventSetup&);

	  template <class DetIdType, class RecHitCollectionType, class IteratorType> 
		void make3x3Clusters( const CaloGeometry* geometry, const RecHitCollectionType* hits, std::vector<CaloCluster>* clusters,
			  std::vector< ClusterShape >* shapes, edm::Timestamp const & iTime, vector<int>* Ncristal,vector<float>* S4S9,vector<float>* S1S9,vector<float>* S2S9, vector<float>* EtrSeed );
	  void AssociateGamma(std::vector<CaloCluster> clusters,  std::vector< int > AllCristal, std::vector< float > s4s9_all, std::vector< float > s1s9_all, std::vector< float > s2s9_all );
	  void AssociateGammaES(std::vector<CaloCluster> clustersEE, std::vector<CaloCluster> clustersES, std::vector<GlobalPoint> posES, std::vector<float> Es_e1, std::vector<float> Es_e2);

	  TVector3 ComputeDirection(bool isEB, TVector3 gamma,TVector3  pi0);
	  TVector3 ComputeESDirection(bool isEB, TVector3 gamma,TVector3  pi0);
	  bool useES_;  
	  bool HLTResults_;  
	  bool Are_pi0_;  

	  // MC truth methods : to be moved to a dedicated class
	  // Method for iterative printing of decay chains 
	  bool printChildren(const SimTrack* p, 
		    std::map<const SimTrack*, std::set<const SimTrack*> > const& ptokids,
		    std::map<const SimTrack*, const SimVertex*> const& ptovtx,
		    int level, bool save, int motherGenIndex);

	  // Standard Tree Fill to avoid repeating the same code for the endcap
	  void fillPi0Tree( math::PtEtaPhiMLorentzVector &pi0P4PV,  std::map<size_t,size_t> &savedCluEB,
		    math::PtEtaPhiMLorentzVector &g1P4PV, math::PtEtaPhiMLorentzVector &g2P4PV,
		    std::vector< ClusterShape > &shapes,
		    const CaloCluster* g1, const CaloCluster* g2, int &nClu, int i, int j, vector<int> &Ncristal, vector<float>& EtSeeds);

	  double DPhi(double phi1, double phi2);
	  double DR( double phi1, double phi2, double eta1, double eta2);
	  double min( double a, double b);
	  void   FillEBContCorr(double gPt, int giEta, double gRatio );
	  void   FillEBContCorr_PHI7Bin(bool isEBp, double gPt, int giPhi, double gRatio );
	  void   FillEEContCorr(double gPt, int EtaRing, double gRatio );

	  TH1F** initializeContCorrHisto(const char *name, const char *title, int size );
	  void   deleteContCorrHisto(TH1F **h, int size);
	  TH1F** ContCorrEB_1;
	  TH1F** ContCorrEB_2;
	  TH1F** ContCorrEB_3;
	  TH1F** ContCorrEB_4;
	  TH1F** ContCorrEB_5;
	  TH1F** ContCorrEB_6;
	  TH1F** ContCorrEB_7;
	  TH1F** ContCorrEB_PHI_7PTBin_p;
	  TH1F** ContCorrEB_PHI_7PTBin_m;
	  EcalEnerCorr containmentCorrections_;

	  TH1F** ContCorrEE_1;
	  TH1F** ContCorrEE_2;
	  TH1F** ContCorrEE_3;
	  TH1F** ContCorrEE_4;
	  TH1F** ContCorrEE_5;
	  TH1F** ContCorrEE_6;
	  TH1F** ContCorrEE_7;

	  TH1F** ContCorrEB_PHI_7PTBin_360iPHI_p;
	  TH1F** ContCorrEB_PHI_7PTBin_360iPHI_m;

	  TH1F *h_Eff_EB;

	  //Inizialize the Branch of the tree
	  void InitTreeVariable();

	  //B.R. of pi0->e+,e-,gamma
	  Float_t Tot_Ev;
	  Float_t eeg, eeee;

	  // ----------member data ---------------------------
	  CaloTopology *ebTopology;         // hardcoded topology
	  CaloTopology *eeTopology;         // hardcoded topology
	  CaloSubdetectorTopology *estopology_;        // hardcoded topology
	  ECALGeometry* geom;               // hardcoded geometry from root file
	  ECALGeometry* geom_;               // hardcoded geometry from root file for ES
	  PosCalcParams          PCparams_;

	  const EcalPreshowerGeometry *esGeometry_;
	  const CaloGeometry* geometry;

	  bool DoOffGeom_;
	  //TH1F *EBdeltaR;     
	  //TH1F *EBRisoPi0_Pt;
	  //TH1F *EBRisoPi0_E;
	  //TH1F *EBRisoPi0_Eta;
	  //TH1F *EBRisoPi0_Phi;
	  //TH1F *EBRisoGammaUnc_E;
	  //TH1F *EBRisoGammaUnc_Eta;
	  //TH1F *EBRisoGammaUnc_Phi;
	  //TH1F *EBRisoGammaUnc_DR;
	  //TH1F *EBRisoGammaUnc2_E;
	  //TH1F *EBRisoGammaUnc2_Eta;
	  //TH1F *EBRisoGammaUnc2_Phi;
	  //TH1F *EBRisoGammaUnc2_DR;
	  //TH1F *EBmPioUnc;
	  //TH1F *EBmPioUncOnlyOne;
	  //TH1F *EBmPioNonClu;
	  //TH1F *EEdeltaR;     
	  //TH1F *EERisoPi0_Pt; 
	  //TH1F *EERisoPi0_E; 
	  //TH1F *EERisoPi0_Eta;
	  //TH1F *EERisoPi0_Phi;
	  //TH1F *EERisoGammaUnc_E;
	  //TH1F *EERisoGammaUnc_Eta;
	  //TH1F *EERisoGammaUnc_Phi;
	  //TH1F *EERisoGammaUnc_DR;
	  //TH1F *EERisoGammaUnc2_E;
	  //TH1F *EERisoGammaUnc2_Eta;
	  //TH1F *EERisoGammaUnc2_Phi;
	  //TH1F *EERisoGammaUnc2_DR;
	  //TH1F *EEmPioUnc;
	  //TH1F *EEmPioUncOnlyOne;
	  //TH1F *EEmPioNonClu;

	  //TH1F *DeltaE_ES;
	  //TH1F *ES_E1layer;
	  //TH1F *ES_E2layer;

	  //TH2F *ConversionGammaRho_z;
	  //TH2F *ConversionGammax_y;
	  //TH2F *Gammas_Dr_E;
	  //TH2F *Pi0_M_Eta;
	  //TH2F *Pi0_assoc_M_Eta;
	  //TH2F *Gammas_Dr_risE;
	  TH2F *Cluster_NCrist_DRgamma;
	  TH2F *ES_DEta_Eta;
	  //TH2F *ES_DEta_EtaMod;
	  //TH2F *ES_DEta_E;
	  TH2F *ES_DEta_Phi;
	  TH2F *ES_DPhi_Eta;
	  //TH2F *ES_DPhi_EtaMod;
	  // TH2F *ES_DPhi_E;
	  //TH2F *ES_DPhi_Phi;
	  TH2F *h2_EtaCorr;

	  TH1F *G1G2_unc;
	  TH1F *G1G2_tot;
	  TH1F *G1_unc;
	  //TH1F *G1_tot;
	  TH1F *G2_unc;
	  //TH1F *G2_tot;

	  std::vector<TLorentzVector> MyMCParicles;
	  std::vector<TLorentzVector> MyEBParicles;
	  std::vector<TLorentzVector> MyEEParicles;

	  bool invertEELaserCorrections_;
	  // input tags
	  edm::InputTag triggerTag_;
	  edm::InputTag EBRecHitCollectionTag_;
	  edm::InputTag EERecHitCollectionTag_;
	  edm::InputTag ESRecHitCollectionTag_;
	  edm::InputTag PFRecHitCollectionTag_;
	  edm::InputTag conversionsTag_;

	  std::string   pfakt5JetCorrectionServiceTag_;

	  // TTree variables
	  TFile* m_file;
	  TFile* m_file_contCorr;

#ifdef TTREEMVA
	  TTree* m_Mva;
	  TTree* m_Mva_tot;
#endif
	  //TTree* m_tree; 
	  TTree* m_tree_opt; 
	  std::string outfilename_;
	  std::string outfilename_ContCorr_;
	  std::string externalGeometry_;
	  TFile *externalGeometryFile_;  

	  bool storeMCTruth_;
	  bool OnlyContCorr_;
	  bool goodCollSelection_;
	  bool useBeamSpotPosition_;

	  static const int MAXL1bits = 200;
	  static const int MAXHLTbits = 200;
	  //int nL1bits;
	  //int L1bits[MAXL1bits];
	  //int nL1bitsTech;
	  //int L1bitsTech[MAXL1bits];

	  int             runn;
	  int             eventn;
	  int             ls;
	  float           iso;

	  //   Int_t nCry;
	  //   Float_t eCry[NCRYMAX];
	  //   Float_t ptCry[NCRYMAX];
	  //   Float_t timeCry[NCRYMAX];
	  //   Int_t flagCry[NCRYMAX];
	  //   Int_t ietaCry[NCRYMAX];
	  //   Int_t iphiCry[NCRYMAX];
	  //   Int_t iCry[NCRYMAX];
	  //   Int_t iSM[NCRYMAX];
	  //   Float_t etaCry[NCRYMAX];
	  //   Float_t phiCry[NCRYMAX];

	  Int_t nClu;
	  Int_t nClu_EB;
	  Int_t nClu_EE;
	  Int_t nCris[NCLUMAX];
	  Float_t EtSeed[NCLUMAX];
	  Float_t S1Clu[NCLUMAX];
	  Float_t S4Clu[NCLUMAX];
	  Float_t S9Clu[NCLUMAX];
	  Float_t S25Clu[NCLUMAX];
	  Float_t etaClu[NCLUMAX];
	  Float_t phiClu[NCLUMAX];
	  Float_t ptClu[NCLUMAX];
	  Float_t timeClu[NCLUMAX];
	  Int_t nCryClu[NCLUMAX];
	  Int_t indexCryClu[NCLUMAX][9];
	  Float_t transparencyLossClu[NCLUMAX];
	  //Float_t transparencyLossCluInvertZSide[NCLUMAX];
	  Float_t laserCorrectionClu[NCLUMAX];
	  Float_t laserAlphaClu[NCLUMAX];

	  Float_t   distTrkMatchClu[NCLUMAX];

	  Int_t flagClu[NCLUMAX];
	  Int_t ietaClu[NCLUMAX];
	  Int_t iphiClu[NCLUMAX];
	  Int_t iCryClu[NCLUMAX];
	  Int_t iSMClu[NCLUMAX];
	  Int_t imodClu[NCLUMAX];
	  Int_t iTTClu[NCLUMAX];
	  Int_t iTTetaClu[NCLUMAX];
	  Int_t iTTphiClu[NCLUMAX];

	  float sMaj9Clu[NCLUMAX];
	  float sMin9Clu[NCLUMAX];
	  float sMaj25Clu[NCLUMAX];
	  float sMin25Clu[NCLUMAX];
	  float sMaj49Clu[NCLUMAX];
	  float sMin49Clu[NCLUMAX];


	  Int_t nPi0;
	  Int_t nPi0_EB;
	  Int_t nPi0_EE;
	  Float_t ePi0[NPI0MAX];
	  Float_t massPi0[NPI0MAX];
	  Float_t ptPi0[NPI0MAX];
	  Float_t etaPi0[NPI0MAX];
	  Float_t phiPi0[NPI0MAX];
	  Float_t CristTot[NPI0MAX];
	  Float_t DRClus[NPI0MAX];
	  Float_t isoPi0[NPI0MAX];
	  Int_t ietaTTPi0[NPI0MAX];
	  Int_t iphiTTPi0[NPI0MAX];
	  Int_t indexClu1Pi0[NPI0MAX];
	  Int_t indexClu2Pi0[NPI0MAX];

	  Int_t    nPFJet;
	  Float_t  ePFJet[NPFJETMAX];
	  Float_t  ptPFJet[NPFJETMAX];
	  Float_t  ptcorrPFJet[NPFJETMAX];
	  Float_t  etaPFJet[NPFJETMAX];
	  Float_t  phiPFJet[NPFJETMAX];

	  Float_t  sumetPFMet;
	  Float_t  ptPFMet;
	  Float_t  phiPFMet;

	  Float_t  sumetMet;
	  Float_t  ptMet;
	  Float_t  phiMet;

	  // trigger and conds foir GOODCOLL in MC
	  //bool isBSC;

	  // mc truth
	  static const int nMaxMC = 350;
	  static const int kPhoton = 22;
	  static const int kPi0 = 111;
	  static const int kElectron = 11;
	  Float_t STr_pi0_x;
	  Float_t STr_pi0_y;
	  Float_t STr_pi0_z;
	  Float_t STr_pi0_eta;
	  Float_t STr_pi0_phi;
	  Float_t STr_ptPi0;
	  Float_t STr_MPi0;
	  Int_t STr_Pi0IsEB;
	  bool STr_G1Uncon;
	  bool STr_G2Uncon;
	  Float_t STr_Sim_Dr;
	  Float_t STr_RecG1_E;
	  Float_t STr_RecG1_Eta;
	  Float_t STr_RecG1_Phi;
	  Float_t STr_RecG1_DR;
	  Float_t STr_RecG1_NCris;
	  Float_t STr_SimG1_E;
	  Float_t STr_SimG1_Eta;
	  Float_t STr_SimG1_Phi;
	  Float_t STr_SimG1_X;
	  Float_t STr_SimG1_Y;
	  Float_t STr_SimG1_Z;
	  Float_t STr_RecG2_E;
	  Float_t STr_RecG2_Eta;
	  Float_t STr_RecG2_Phi;
	  Float_t STr_RecG2_DR;
	  Float_t STr_RecG2_NCris;
	  Float_t STr_SimG2_E;
	  Float_t STr_SimG2_Eta;
	  Float_t STr_SimG2_Phi;
	  Float_t STr_SimG2_X;
	  Float_t STr_SimG2_Y;
	  Float_t STr_SimG2_Z;

	  Float_t STr_ESimG1_E;
	  Float_t STr_ESimG1_Eta;
	  Float_t STr_ESimG1_Phi;
	  Float_t STr_ESimG1_X;
	  Float_t STr_ESimG1_Y;
	  Float_t STr_ESimG1_Z;
	  Float_t STr_ESimG2_E;
	  Float_t STr_ESimG2_Eta;
	  Float_t STr_ESimG2_Phi;
	  Float_t STr_ESimG2_X;
	  Float_t STr_ESimG2_Y;
	  Float_t STr_ESimG2_Z;


	  Float_t STr_NCristG1;
	  Float_t STr_NCristG2;
	  Float_t STr_RecPi0_M;
	  Float_t STr_RecPi0_Eta;
	  Int_t   STr2_NPi0_rec;
	  Int_t   STr2_Pi0recIsEB[NPI0MAX];
	  Float_t STr2_IsoPi0_rec[NPI0MAX];
	  Float_t STr2_S4S9_1[NPI0MAX];
	  Float_t STr2_S4S9_2[NPI0MAX];
	  Int_t   STr2_n1CrisPi0_rec[NPI0MAX];
	  Int_t   STr2_n2CrisPi0_rec[NPI0MAX];
	  Float_t STr2_mPi0_rec[NPI0MAX];
	  Float_t STr2_ptG1_rec[NPI0MAX];
	  Float_t STr2_ptG2_rec[NPI0MAX];
	  Float_t STr2_etaPi0_rec[NPI0MAX];
	  Float_t STr2_ptPi0_rec[NPI0MAX];
	  Float_t STr2_DeltaRG1G2[NPI0MAX];
	  Float_t STr2_Es_e1_1[NPI0MAX];
	  Float_t STr2_Es_e1_2[NPI0MAX];
	  Float_t STr2_Es_e2_1[NPI0MAX];
	  Float_t STr2_Es_e2_2[NPI0MAX];
	  Int_t   STr_Es_nEE;
	  Int_t   STr_Es_nES;
	  Float_t STr_Es_RecG1_E;
	  Float_t STr_Es_RecG1_Eta;
	  Float_t STr_Es_RecG1_Phi;
	  Float_t STr_Es_RecG1es_E;
	  Float_t STr_Es_e1_1;
	  Float_t STr_Es_e1_2;
	  Float_t STr_Es_RecG2_E;
	  Float_t STr_Es_RecG2_Eta;
	  Float_t STr_Es_RecG2_Phi;
	  Float_t STr_Es_RecG2es_E;
	  Float_t STr_Es_e2_1;
	  Float_t STr_Es_e2_2;
	  Float_t STr_Es_RecPi0_M;
	  Float_t STr_Es_RecPi0_Eta;
	  Float_t STr_Es_RecPi0es_M;
	  Float_t STr_Es_RecPi0es_Eta;
	  Float_t STr_Es_RecPi0esPos_M;
	  Float_t STr_Es_RecPi0esPos_Eta;
	  Float_t STr_Es_RecPi0esPos_Mw;
	  Float_t STr_Es_RecPi0esPos_Etaw;
	  Float_t STr_Es_Clu1es_Eta1;
	  Float_t STr_Es_Clu1es_Phi1;
	  Float_t STr_Es_Clu1es_x1;
	  Float_t STr_Es_Clu1es_y1;
	  Float_t STr_Es_Clu1es_z1;
	  Float_t STr_Es_Clu2es_Eta1;
	  Float_t STr_Es_Clu2es_Phi1;
	  Float_t STr_Es_Clu2es_x1;
	  Float_t STr_Es_Clu2es_y1;
	  Float_t STr_Es_Clu2es_z1;

	  Float_t STrPF_nClus;  
	  Float_t STrPF_RecG1_E;  
	  Float_t STrPF_RecG1_Eta;
	  Float_t STrPF_RecG1_Phi;
	  Float_t STrPF_RecG1_DR; 
	  Float_t STrPF_RecG2_E;  
	  Float_t STrPF_RecG2_Eta;
	  Float_t STrPF_RecG2_Phi;
	  Float_t STrPF_RecG2_DR; 
	  Float_t STrPF_Pi0_M; 
	  Float_t STrPF_Pi0_Eta; 
	  Int_t STrPF_nPi0_rec;
	  Int_t STrPF_Pi0recIsEB[NPI0MAX];
	  Float_t STrPF_mPi0_rec[NPI0MAX];
	  Float_t STrPF_etaPi0_rec[NPI0MAX];

	  //Float_t STrES_DeltaE[NCLUMAX];
	  Int_t   nMC;
	  Int_t   pdgIdMC[nMaxMC];
	  Int_t   statusMC[nMaxMC];
	  Int_t   motherIDMC[nMaxMC];
	  Int_t   motherIndexMC[nMaxMC];
	  Float_t ptMC[nMaxMC];
	  Float_t mMC[nMaxMC];
	  Float_t eMC[nMaxMC];
	  Float_t etaMC[nMaxMC];
	  Float_t phiMC[nMaxMC];
	  bool    convertedMC[nMaxMC]; 
	  Float_t ConversionPi0_rho[nMaxMC];
	  Float_t ConversionPi0_z[nMaxMC];
	  Float_t ConversionG1_x[nMaxMC];
	  Float_t ConversionG1_y[nMaxMC];
	  Float_t ConversionG1_rho[nMaxMC];
	  Float_t ConversionG1_z[nMaxMC];
	  Float_t ConversionG2_x[nMaxMC];
	  Float_t ConversionG2_y[nMaxMC];
	  Float_t ConversionG2_rho[nMaxMC];
	  Float_t ConversionG2_z[nMaxMC];

	  // SIM particles (those not already in MC particles list)
	  // help to study in-flight decays of Kshort, Lambda etc.
	  // These are also useful to study photon conversions 
	  static const int nMaxSIM = 350;
	  Int_t nSIM;
	  Int_t pdgIdSIM[nMaxSIM];
	  Int_t statusSIM[nMaxSIM];
	  //Int_t motherIDSIM[nMaxSIM]; 
	  Int_t motherGenIndexSIM[nMaxSIM]; 
	  Float_t ptSIM[nMaxSIM];
	  Float_t eSIM[nMaxSIM];
	  Float_t etaSIM[nMaxSIM];
	  Float_t phiSIM[nMaxSIM];
	  Float_t rSIM[nMaxSIM];
	  Float_t zSIM[nMaxSIM];

	  // Reconstructed photon conversions
	  Int_t nconvPhot;
	  Float_t chi2convPhot[NCONVMAX];
	  Float_t ndofconvPhot[NCONVMAX];
	  Float_t rconvPhot[NCONVMAX];
	  Float_t phiconvPhot[NCONVMAX];
	  Float_t zconvPhot[NCONVMAX];
	  Int_t ntrkconvPhot[NCONVMAX];
	  Float_t eovpconvPhot[NCONVMAX];
	  Float_t etaecalconvPhot[NCONVMAX];
	  Float_t phiecalconvPhot[NCONVMAX];
	  Float_t energyecalconvPhot[NCONVMAX];
	  // Extra conversion ID - pairwise
	  Int_t algoconvPhot[NCONVMAX];
	  Float_t d0convPhot[NCONVMAX];
	  Float_t detaecalconvPhot[NCONVMAX];
	  Float_t dphiecalconvPhot[NCONVMAX];
	  Float_t dphivtxconvPhot[NCONVMAX];
	  Float_t pairsepconvPhot[NCONVMAX];
	  Float_t pairmassconvPhot[NCONVMAX];
	  // Extra conversion ID - trackwise
	  Float_t trchi21convPhot[NCONVMAX];
	  Float_t trndof1convPhot[NCONVMAX];
	  Int_t trqual1convPhot[NCONVMAX];
	  Float_t trpt1convPhot[NCONVMAX];
	  Float_t trerr1convPhot[NCONVMAX];
	  Float_t trchi22convPhot[NCONVMAX];
	  Float_t trndof2convPhot[NCONVMAX];
	  Int_t trqual2convPhot[NCONVMAX];
	  Float_t trpt2convPhot[NCONVMAX];
	  Float_t trerr2convPhot[NCONVMAX];
	  Float_t phi1convPhot[NCONVMAX];
	  Float_t eta1convPhot[NCONVMAX];
	  Float_t p1convPhot[NCONVMAX];
	  Float_t phi2convPhot[NCONVMAX];
	  Float_t eta2convPhot[NCONVMAX];
	  Float_t p2convPhot[NCONVMAX];

	  // cuts
	  Float_t ptpi0Cut_, ptCluCut_, s1CluCut_, s1CluCutEE_, s4s9CluCut_;

	  //MVA
	  //Float_t MVA_Mass;
	  //Float_t MVA_Mass_MC;
	  //Float_t MVA_E3x3_1;
	  //Float_t MVA_E3x3_2;
	  //Float_t MVA_Pt_1;
	  //Float_t MVA_Pt_2;
	  //Float_t MVA_Eta_1;
	  //Float_t MVA_Eta_2;
	  //Float_t MVA_Phi_1;
	  //Float_t MVA_Phi_2;
	  //Float_t MVA_Nxtal_1;
	  //Float_t MVA_Nxtal_2;
	  //Float_t MVA_S4S9_1;
	  //Float_t MVA_S4S9_2; 

	  Float_t MVA_E3x3_1;   
	  Float_t MVA_E3x3MC_1;   
	  Float_t MVA_E3x3_2;    
	  Float_t MVA_E3x3MC_2;    
	  Float_t MVA_Pt_1;       
	  Float_t MVA_Pt_2;       
	  Int_t   MVA_Nxtal_1;    
	  Int_t   MVA_Nxtal_2;    
	  Float_t MVA_S4S9_1;     
	  Float_t MVA_S4S9_2;     
	  Float_t MVA_S1S9_1;     
	  Float_t MVA_S1S9_2;     
	  Float_t MVA_S2S9_1;     
	  Float_t MVA_S2S9_2;     
	  Int_t   MVA_Eta_1;      
	  Int_t   MVA_Eta_2;      
	  Int_t   MVA_Phi_1;      
	  Int_t   MVA_Phi_2;      
	  Int_t   MVA_Eta_1on5;   
	  Int_t   MVA_Eta_2on5;   
	  Int_t   MVA_Phi_1on2;   
	  Int_t   MVA_Phi_2on2;   
	  Int_t   MVA_Eta_1on2520;
	  Int_t   MVA_Eta_2on2520;
	  Int_t   MVA_Phi_1on20;  
	  Int_t   MVA_Phi_2on20;  
	  Float_t MVA_nEta_1;  
	  Float_t MVA_nEta_2;  
	  Float_t MVA_nPhi_1;  
	  Float_t MVA_nPhi_2;  
	  bool    MVA_isConv_1;  
	  bool    MVA_isConv_2;  
	  //Togheter
	  Float_t MVA_E3x3_t;
	  Float_t MVA_E3x3MC_t;
	  Float_t MVA_Pt_t;
	  Int_t   MVA_Nxtal_t;
	  Float_t MVA_S4S9_t;
	  Float_t MVA_S1S9_t;
	  Float_t MVA_S2S9_t;
	  Int_t   MVA_Eta_t;
	  Int_t   MVA_Phi_t;
	  Int_t   MVA_Eta_ton5;
	  Int_t   MVA_Phi_ton2;
	  Int_t   MVA_Eta_ton2520;
	  Int_t   MVA_Phi_ton20;

	  // Efficiency EB
	  int Ntot;
	  int Ntot_EB;
	  int N1rec_EB;
	  int N1_2rec_EB;
	  int Nfinal_EB;

};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
NewPi0Dumper_Gun::NewPi0Dumper_Gun(const edm::ParameterSet& ps)
{
    cout<<"Constructor"<<endl;
    //now do what ever initialization is needed
    // B.R. pi0->e+,e-,gamma
    Tot_Ev=0.;  eeg=0.; eeee=0.;

    // collections to fetch
    triggerTag_               = ps.getUntrackedParameter<edm::InputTag>("triggerTag",edm::InputTag("TriggerResults"));
    EBRecHitCollectionTag_    = ps.getUntrackedParameter<edm::InputTag>("EBRecHitCollectionTag");
    EERecHitCollectionTag_    = ps.getUntrackedParameter<edm::InputTag>("EERecHitCollectionTag");
    ESRecHitCollectionTag_    = ps.getUntrackedParameter<edm::InputTag>("ESRecHitCollectionTag");
    useES_                    = ps.getUntrackedParameter<bool>("useES",true);
    HLTResults_               = ps.getUntrackedParameter<bool>("HLTResults",true);
    Are_pi0_                  = ps.getUntrackedParameter<bool>("Are_pi0",true);
    OnlyContCorr_             = ps.getUntrackedParameter<bool>("OnlyContCorr",false);
    PFRecHitCollectionTag_    = ps.getUntrackedParameter<edm::InputTag>("PFRecHitCollectionTag");
    conversionsTag_           = ps.getUntrackedParameter<edm::InputTag>("conversionsTag");
    outfilename_              = ps.getUntrackedParameter<std::string>("OutputFile","NewPi0Tuple.root");
    outfilename_ContCorr_     = ps.getUntrackedParameter<std::string>("outfilename_ContCorr","ContCorr.root");
    externalGeometry_         = ps.getUntrackedParameter<std::string>("ExternalGeometry");
    storeMCTruth_             = ps.getUntrackedParameter<bool>("StoreMCTruth",false);
    goodCollSelection_        = ps.getUntrackedParameter<bool>("goodCollSelection",false);
    useBeamSpotPosition_      = ps.getUntrackedParameter<bool>("useBeamSpotPosition",true);
    invertEELaserCorrections_ = ps.getUntrackedParameter<bool>("InvertEELaserCorrections",true);
    DoOffGeom_                = ps.getUntrackedParameter<bool>("DoOffGeom",true);
    if(DoOffGeom_) cout<<"Using: Official geometry"<<endl;
    else           cout<<"Using: external geometry"<<endl;

    ptpi0Cut_             = ps.getUntrackedParameter<double>("ptpi0Cut", 0.700);
    s1CluCut_             = ps.getUntrackedParameter<double>("s1CluCut", 0.350);
    s1CluCutEE_           = ps.getUntrackedParameter<double>("s1CluCutEE", 0.5);
    ptCluCut_             = ps.getUntrackedParameter<double>("ptCluCut", 0.300);
    s4s9CluCut_           = ps.getUntrackedParameter<double>("s4s9CluCut", 0.85);
    cout<<"Cut Used: ptpi0Cut: "<<ptpi0Cut_<<" s1CluCut "<<s1CluCut_<<" s1CluCutEE "<<s1CluCutEE_<<" ptCluCut: "<<ptCluCut_<<" s4s9CluCut: "<<s4s9CluCut_<<endl;

    ebTopology = new CaloTopology();  
    eeTopology = new CaloTopology();  
    EcalBarrelHardcodedTopology* ebHCTopology=new EcalBarrelHardcodedTopology();
    EcalEndcapHardcodedTopology* eeHCTopology=new EcalEndcapHardcodedTopology();
    ebTopology->setSubdetTopology(DetId::Ecal,EcalBarrel,ebHCTopology);
    eeTopology->setSubdetTopology(DetId::Ecal,EcalEndcap,eeHCTopology);

    estopology_ = new EcalPreshowerHardcodedTopology();

    TFile* f = TFile::Open( "/afs/cern.ch/user/l/lpernie/scratch1/pi0Calib/pi0/CMSSW_4_2_4/src/CalibCode/submit/common/caloGeometry.root"  );
    geom = ECALGeometry::getGeometry(f);
    //ES
    externalGeometryFile_ = TFile::Open(externalGeometry_.c_str());
    if(!externalGeometryFile_) cms::Exception("ExtGeom") << "External Geometry file (" << externalGeometry_ << ") not found" << endl;
    geom_ = ECALGeometry::getGeometry(externalGeometryFile_);
    GeometryService::setGeometryName(externalGeometry_);
    GeometryService::setGeometryPtr(geom_);

    PCparams_.param_LogWeighted_ = true;
    PCparams_.param_T0_barl_     = 5.7;
    PCparams_.param_T0_endc_     = 3.1;
    PCparams_.param_T0_endcES_   = 1.2;
    PCparams_.param_W0_          = 4.2;
    PCparams_.param_X0_          = 0.89;

    // Cont correction
    ContCorrEB_1 = initializeContCorrHisto("ContCorr_EB_bin_1_","E^{rec}/E^{gen}", N_IETA );
    ContCorrEB_2 = initializeContCorrHisto("ContCorr_EB_bin_2_","E^{rec}/E^{gen}", N_IETA );
    ContCorrEB_3 = initializeContCorrHisto("ContCorr_EB_bin_3_","E^{rec}/E^{gen}", N_IETA );
    ContCorrEB_4 = initializeContCorrHisto("ContCorr_EB_bin_4_","E^{rec}/E^{gen}", N_IETA );
    ContCorrEB_5 = initializeContCorrHisto("ContCorr_EB_bin_5_","E^{rec}/E^{gen}", N_IETA );
    ContCorrEB_6 = initializeContCorrHisto("ContCorr_EB_bin_6_","E^{rec}/E^{gen}", N_IETA );
    ContCorrEB_7 = initializeContCorrHisto("ContCorr_EB_bin_7_","E^{rec}/E^{gen}", N_IETA );

    containmentCorrections_.loadContainmentCorrectionsEB( "/afs/cern.ch/work/l/lpernie/pi0/Calibration/CMSSW_4_2_4/src/CalibCode/submit/common/totNewPi0TupleMB_fillingTot.fittedcorrectionsEB.root" );
    ContCorrEB_PHI_7PTBin_p = initializeContCorrHisto("ContCorrEB_PHI_7PTBin_p_","E^{rec}/E^{gen}", 20*PTBINSEB);
    ContCorrEB_PHI_7PTBin_m = initializeContCorrHisto("ContCorrEB_PHI_7PTBin_m_","E^{rec}/E^{gen}", 20*PTBINSEB);
    ContCorrEB_PHI_7PTBin_360iPHI_p = initializeContCorrHisto("ContCorrEB_PHI_7PTBin_360iPHI_p_","E^{rec}/E^{gen}", N_iPHI*PTBINSEB);
    ContCorrEB_PHI_7PTBin_360iPHI_m = initializeContCorrHisto("ContCorrEB_PHI_7PTBin_360iPHI_m_","E^{rec}/E^{gen}", N_iPHI*PTBINSEB);

    ContCorrEE_1 = initializeContCorrHisto("ContCorr_EE_bin_1_","E^{rec}/E^{gen}", N_ETARING);
    ContCorrEE_2 = initializeContCorrHisto("ContCorr_EE_bin_2_","E^{rec}/E^{gen}", N_ETARING);
    ContCorrEE_3 = initializeContCorrHisto("ContCorr_EE_bin_3_","E^{rec}/E^{gen}", N_ETARING);
    ContCorrEE_4 = initializeContCorrHisto("ContCorr_EE_bin_4_","E^{rec}/E^{gen}", N_ETARING);
    ContCorrEE_5 = initializeContCorrHisto("ContCorr_EE_bin_5_","E^{rec}/E^{gen}", N_ETARING);
    ContCorrEE_6 = initializeContCorrHisto("ContCorr_EE_bin_6_","E^{rec}/E^{gen}", N_ETARING);
    ContCorrEE_7 = initializeContCorrHisto("ContCorr_EE_bin_7_","E^{rec}/E^{gen}", N_ETARING);

}


NewPi0Dumper_Gun::~NewPi0Dumper_Gun()
{
    cout<<"Destructor"<<endl;

    if(!OnlyContCorr_){
	  m_file->Write();
	  m_file->Close();
    }
    else{
	  m_file_contCorr->Write();
	  m_file_contCorr->Close();
    }

    // do anything here that needs to be done at desctruction time
    // (e.g. close files, deallocate resources etc.)
    //delete CutVariables_EB;
    delete geom;
    //delete EBdeltaR;      
    //delete EBRisoPi0_Pt;  
    //delete EBRisoPi0_E;  
    //delete EBRisoPi0_Eta; 
    //delete EBRisoPi0_Phi; 
    //delete EBRisoGammaUnc_E; 
    //delete EBRisoGammaUnc_Eta; 
    //delete EBRisoGammaUnc_Phi; 
    //delete EBRisoGammaUnc_DR; 
    //delete EBRisoGammaUnc2_E; 
    //delete EBRisoGammaUnc2_Eta; 
    //delete EBRisoGammaUnc2_Phi; 
    //delete EBRisoGammaUnc2_DR; 
    //delete EBmPioUnc; 
    //delete EBmPioUncOnlyOne; 
    //delete EBmPioNonClu; 
    //delete EEdeltaR;      
    //delete EERisoPi0_Pt;  
    //delete EERisoPi0_E;  
    //delete EERisoPi0_Eta; 
    //delete EERisoPi0_Phi;
    //delete EERisoGammaUnc_E; 
    //delete EERisoGammaUnc_Eta; 
    //delete EERisoGammaUnc_Phi; 
    //delete EERisoGammaUnc_DR; 
    //delete EERisoGammaUnc2_E; 
    //delete EERisoGammaUnc2_Eta; 
    //delete EERisoGammaUnc2_Phi; 
    //delete EERisoGammaUnc2_DR; 
    //delete EEmPioUnc; 
    //delete EEmPioUncOnlyOne; 
    //delete EEmPioNonClu; 

    //delete DeltaE_ES; 
    //delete ES_E1layer; 
    //delete ES_E2layer; 

    //delete ConversionGammaRho_z;
    //delete ConversionGammax_y;
    //delete Gammas_Dr_E;
    //delete Pi0_M_Eta;
    //delete Pi0_assoc_M_Eta;
    //delete Gammas_Dr_risE;
    delete Cluster_NCrist_DRgamma;
    delete ES_DEta_Eta;
    //delete ES_DEta_EtaMod;
    //delete ES_DEta_E;
    delete ES_DEta_Phi;
    delete ES_DPhi_Eta;
    //delete ES_DPhi_EtaMod;
    //delete ES_DPhi_E;
    //delete ES_DPhi_Phi;
    delete h2_EtaCorr;

    delete G1G2_unc;
    delete G1G2_tot;
    delete G1_unc;
    delete G2_unc;
    deleteContCorrHisto( ContCorrEB_1, N_IETA );
    deleteContCorrHisto( ContCorrEB_2, N_IETA );
    deleteContCorrHisto( ContCorrEB_3, N_IETA );
    deleteContCorrHisto( ContCorrEB_4, N_IETA );
    deleteContCorrHisto( ContCorrEB_5, N_IETA );
    deleteContCorrHisto( ContCorrEB_6, N_IETA );
    deleteContCorrHisto( ContCorrEB_7, N_IETA );

    deleteContCorrHisto( ContCorrEB_PHI_7PTBin_p, 20*PTBINSEB );
    deleteContCorrHisto( ContCorrEB_PHI_7PTBin_m, 20*PTBINSEB );
    deleteContCorrHisto( ContCorrEB_PHI_7PTBin_360iPHI_p, N_iPHI*PTBINSEB );
    deleteContCorrHisto( ContCorrEB_PHI_7PTBin_360iPHI_m, N_iPHI*PTBINSEB );

    deleteContCorrHisto( ContCorrEE_1, N_ETARING );
    deleteContCorrHisto( ContCorrEE_2, N_ETARING );
    deleteContCorrHisto( ContCorrEE_3, N_ETARING );
    deleteContCorrHisto( ContCorrEE_4, N_ETARING );
    deleteContCorrHisto( ContCorrEE_5, N_ETARING );
    deleteContCorrHisto( ContCorrEE_6, N_ETARING );
    deleteContCorrHisto( ContCorrEE_7, N_ETARING );

    delete h_Eff_EB;
}


//
// member functions
//


// ------------ method called once each job just before starting event loop  ------------
void NewPi0Dumper_Gun::beginJob()
{
    cout<<"Begin Job"<<endl;
    Ntot=0; Ntot_EB=0; N1rec_EB=0; N1_2rec_EB=0; Nfinal_EB=0;

    m_file = new TFile(outfilename_.c_str(),"RECREATE");
    m_file_contCorr = new TFile(outfilename_ContCorr_.c_str(),"RECREATE");

    m_file->cd();

#ifdef TTREEMVA
    //TTree MVA
    m_Mva  = new TTree("h_mva","Conteinment Correction");
    //Old one
    //m_Mva->Branch("MVA_Mass",&MVA_Mass,"MVA_Mass/F");
    //m_Mva->Branch("MVA_Mass_MC",&MVA_Mass_MC,"MVA_Mass_MC/F");
    //m_Mva->Branch("MVA_E3x3_1",&MVA_E3x3_1,"MVA_E3x3_1/F");
    //m_Mva->Branch("MVA_E3x3_2",&MVA_E3x3_2,"MVA_E3x3_2/F");
    //m_Mva->Branch("MVA_Pt_1",&MVA_Pt_1,"MVA_Pt_1/F");
    //m_Mva->Branch("MVA_Pt_2",&MVA_Pt_2,"MVA_Pt_2/F");
    //m_Mva->Branch("MVA_Eta_1",&MVA_Eta_1,"MVA_Eta_1/F");
    //m_Mva->Branch("MVA_Eta_2",&MVA_Eta_2,"MVA_Eta_2/F");
    //m_Mva->Branch("MVA_Phi_1",&MVA_Phi_1,"MVA_Phi_1/F");
    //m_Mva->Branch("MVA_Phi_2",&MVA_Phi_2,"MVA_Phi_2/F");
    //m_Mva->Branch("MVA_Nxtal_1",&MVA_Nxtal_1,"MVA_Nxtal_1/F");
    //m_Mva->Branch("MVA_Nxtal_2",&MVA_Nxtal_2,"MVA_Nxtal_2/F");
    //m_Mva->Branch("MVA_S4S9_1",&MVA_S4S9_1,"MVA_S4S9_1/F");
    //m_Mva->Branch("MVA_S4S9_2",&MVA_S4S9_2,"MVA_S4S9_2/F");

    m_Mva->Branch("MVA_E3x3_1",&MVA_E3x3_1,"MVA_E3x3_1/F");
    m_Mva->Branch("MVA_E3x3MC_1",&MVA_E3x3MC_1,"MVA_E3x3MC_1/F");
    m_Mva->Branch("MVA_E3x3_2",&MVA_E3x3_2,"MVA_E3x3_2/F");
    m_Mva->Branch("MVA_E3x3MC_2",&MVA_E3x3MC_2,"MVA_E3x3MC_2/F");
    m_Mva->Branch("MVA_Pt_1",&MVA_Pt_1,"MVA_Pt_1/F");
    m_Mva->Branch("MVA_Pt_2",&MVA_Pt_2,"MVA_Pt_2/F");
    m_Mva->Branch("MVA_Nxtal_1",&MVA_Nxtal_1,"MVA_Nxtal_1/I");
    m_Mva->Branch("MVA_Nxtal_2",&MVA_Nxtal_2,"MVA_Nxtal_2/I");
    m_Mva->Branch("MVA_S4S9_1",&MVA_S4S9_1,"MVA_S4S9_1/F");
    m_Mva->Branch("MVA_S4S9_2",&MVA_S4S9_2,"MVA_S4S9_2/F");
    m_Mva->Branch("MVA_S1S9_1",&MVA_S1S9_1,"MVA_S1S9_1/F");
    m_Mva->Branch("MVA_S1S9_2",&MVA_S1S9_2,"MVA_S1S9_2/F");
    m_Mva->Branch("MVA_S2S9_1",&MVA_S2S9_1,"MVA_S2S9_1/F");
    m_Mva->Branch("MVA_S2S9_2",&MVA_S2S9_2,"MVA_S2S9_2/F");
    m_Mva->Branch("MVA_Eta_1",&MVA_Eta_1,"MVA_Eta_1/I");
    m_Mva->Branch("MVA_Eta_2",&MVA_Eta_2,"MVA_Eta_2/I");
    m_Mva->Branch("MVA_Phi_1",&MVA_Phi_1,"MVA_Phi_1/I");
    m_Mva->Branch("MVA_Phi_2",&MVA_Phi_2,"MVA_Phi_2/I");
    m_Mva->Branch("MVA_Eta_1on5",&MVA_Eta_1on5,"MVA_Eta_1on5/I");
    m_Mva->Branch("MVA_Eta_2on5",&MVA_Eta_2on5,"MVA_Eta_2on5/I");
    m_Mva->Branch("MVA_Phi_1on2",&MVA_Phi_1on2,"MVA_Phi_1on2/I");
    m_Mva->Branch("MVA_Phi_2on2",&MVA_Phi_2on2,"MVA_Phi_2on2/I");
    m_Mva->Branch("MVA_Eta_1on2520",&MVA_Eta_1on2520,"MVA_Eta_1on2520/I");
    m_Mva->Branch("MVA_Eta_2on2520",&MVA_Eta_2on2520,"MVA_Eta_2on2520/I");
    m_Mva->Branch("MVA_Phi_1on20",&MVA_Phi_1on20,"MVA_Phi_1on20/I");
    m_Mva->Branch("MVA_Phi_2on20",&MVA_Phi_2on20,"MVA_Phi_2on20/I");
    m_Mva->Branch("MVA_nEta_1",&MVA_nEta_1,"MVA_nEta_1/F");
    m_Mva->Branch("MVA_nEta_2",&MVA_nEta_2,"MVA_nEta_2/F");
    m_Mva->Branch("MVA_nPhi_1",&MVA_nPhi_1,"MVA_nPhi_1/F");
    m_Mva->Branch("MVA_nPhi_2",&MVA_nPhi_2,"MVA_nPhi_2/F");
    m_Mva->Branch("MVA_isConv_1",&MVA_isConv_1,"MVA_isConv_1/O");
    m_Mva->Branch("MVA_isConv_2",&MVA_isConv_2,"MVA_isConv_2/O");
    // Together gamma1 and 2
    m_Mva_tot  = new TTree("h_mva_tot","Conteinment Correction gamma1, gamma2 together");
    m_Mva_tot->Branch("MVA_E3x3_t",&MVA_E3x3_t,"MVA_E3x3_t/F");
    m_Mva_tot->Branch("MVA_E3x3MC_t",&MVA_E3x3MC_t,"MVA_E3x3MC_t/F");
    m_Mva_tot->Branch("MVA_Pt_t",&MVA_Pt_t,"MVA_Pt_t/F");
    m_Mva_tot->Branch("MVA_Nxtal_t",&MVA_Nxtal_t,"MVA_Nxtal_t/I");
    m_Mva_tot->Branch("MVA_S4S9_t",&MVA_S4S9_t,"MVA_S4S9_t/F");
    m_Mva_tot->Branch("MVA_S1S9_t",&MVA_S1S9_t,"MVA_S1S9_t/F");
    m_Mva_tot->Branch("MVA_S2S9_t",&MVA_S2S9_t,"MVA_S2S9_t/F");
    m_Mva_tot->Branch("MVA_Eta_t",&MVA_Eta_t,"MVA_Eta_t/I");
    m_Mva_tot->Branch("MVA_Phi_t",&MVA_Phi_t,"MVA_Phi_t/I");
    m_Mva_tot->Branch("MVA_Eta_ton5",&MVA_Eta_ton5,"MVA_Eta_ton5/I");
    m_Mva_tot->Branch("MVA_Phi_ton2",&MVA_Phi_ton2,"MVA_Phi_ton2/I");
    m_Mva_tot->Branch("MVA_Eta_ton2520",&MVA_Eta_ton2520,"MVA_Eta_ton2520/I");
    m_Mva_tot->Branch("MVA_Phi_ton20",&MVA_Phi_ton20,"MVA_Phi_ton20/I");

#endif
    m_tree_opt = new TTree("tree_opt","Pi0 Analysis Tree for optim");
    //m_tree = new TTree("h1","Pi0 Analysis Tree");
    // GENERAL block branches
    //m_tree->Branch("Run",&runn,"Run/I");
    //m_tree->Branch("Event",&eventn,"Event/I");
    //m_tree->Branch("LumiSection",&ls,"LumiSection/I");

    /// trigger variables
    ////m_tree->Branch("nL1bits",&nL1bits,"nL1bits/I");
    ////m_tree->Branch("L1bits",L1bits,"L1bits[nL1bits]/I");
    ////m_tree->Branch("nL1bitsTech",&nL1bitsTech,"nL1bitsTech/I");
    ////m_tree->Branch("L1bitsTech",L1bitsTech,"L1bitsTech[nL1bitsTech]/I");

    //m_tree->Branch("isBSC",&isBSC,"isBSC/O");

    // cluster variables
    //m_tree->Branch("nClu",&nClu,"nClu/I");
    //m_tree->Branch("nClu_EB",&nClu_EB,"nClu_EB/I");
    //m_tree->Branch("nClu_EE",&nClu_EE,"nClu_EE/I");
    //m_tree->Branch("nCris",&nCris,"nCris[nClu]/I");
    //m_tree->Branch("EtSeed",&EtSeed,"EtSeed[nClu]/F");
    //m_tree->Branch("ptClu",&ptClu,"ptClu[nClu]/F");
    //m_tree->Branch("etaClu",&etaClu,"etaClu[nClu]/F");
    //m_tree->Branch("phiClu",&phiClu,"phiClu[nClu]/F");
    //m_tree->Branch("S1Clu",&S1Clu,"S1Clu[nClu]/F");
    //m_tree->Branch("S4Clu",&S4Clu,"S4Clu[nClu]/F");
    //m_tree->Branch("S9Clu",&S9Clu,"S9Clu[nClu]/F");
    //m_tree->Branch("S25Clu",&S25Clu,"S25Clu[nClu]/F");
    //m_tree->Branch("timeClu",&timeClu,"timeClu[nClu]/F");
    //m_tree->Branch("nCryClu",&nCryClu,"nCryClu[nClu]/I");
    //m_tree->Branch("flagClu",&flagClu,"flagClu[nClu]/I");

    //m_tree->Branch("ietaClu",&ietaClu,"ietaClu[nClu]/I");
    //m_tree->Branch("iphiClu",&iphiClu,"iphiClu[nClu]/I");
    //m_tree->Branch("iCryClu",&iCryClu,"iCryClu[nClu]/I");
    //m_tree->Branch("iSMClu",&iSMClu,"iSMClu[nClu]/I");
    //m_tree->Branch("imodClu",&imodClu,"imodClu[nClu]/I");
    //m_tree->Branch("iTTClu",&iTTClu,"iTTClu[nClu]/I");
    //m_tree->Branch("iTTetaClu",&iTTetaClu,"iTTetaClu[nClu]/I");
    //m_tree->Branch("iTTphiClu",&iTTphiClu,"iTTphiClu[nClu]/I");

    //m_tree->Branch("distTrkMatchClu",&distTrkMatchClu,"distTrkMatchClu[nClu]/F");

    //m_tree->Branch("sMaj9Clu", &sMaj9Clu, "sMaj9Clu[nClu]/F");
    //m_tree->Branch("sMaj25Clu",&sMaj25Clu,"sMaj25Clu[nClu]/F");
    //m_tree->Branch("sMaj49Clu",&sMaj49Clu,"sMaj49Clu[nClu]/F");
    //m_tree->Branch("sMin9Clu", &sMin9Clu, "sMin9Clu[nClu]/F");
    //m_tree->Branch("sMin25Clu",&sMin25Clu,"sMin25Clu[nClu]/F");
    //m_tree->Branch("sMin49Clu",&sMin49Clu,"sMin49Clu[nClu]/F");
    //m_tree->Branch("transparencyLossClu",&transparencyLossClu,"transparencyLossClu[nClu]/F");
    //m_tree->Branch("laserCorrectionClu",&laserCorrectionClu,"laserCorrectionClu[nClu]/F");
    //m_tree->Branch("laserAlphaClu",&laserAlphaClu,"laserAlphaClu[nClu]/F");

    //// pi0 variables
    //m_tree->Branch("nPi0",&nPi0,"nPi0/I");
    //m_tree->Branch("nPi0_EB",&nPi0_EB,"nPi0_EB/I");
    //m_tree->Branch("nPi0_EE",&nPi0_EE,"nPi0_EE/I");
    //m_tree->Branch("massPi0",&massPi0,"massPi0[nPi0]/F");
    //m_tree->Branch("ePi0",&ePi0,"ePi0[nPi0]/F");
    //m_tree->Branch("ptPi0",&ptPi0,"ptPi0[nPi0]/F");
    //m_tree->Branch("etaPi0",&etaPi0,"etaPi0[nPi0]/F");
    //m_tree->Branch("phiPi0",&phiPi0,"phiPi0[nPi0]/F");
    //m_tree->Branch("CristTot",&CristTot,"CristTot[nPi0]/F");
    //m_tree->Branch("DRClus",&DRClus,"DRClus[nPi0]/F");
    //m_tree->Branch("indexClu1Pi0",&indexClu1Pi0,"indexClu1Pi0[nPi0]/I");
    //m_tree->Branch("indexClu2Pi0",&indexClu2Pi0,"indexClu2Pi0[nPi0]/I");

    m_tree_opt->Branch( "STr2_NPi0_rec",      &STr2_NPi0_rec,    "STr2_NPi0_rec/I");
    m_tree_opt->Branch( "STr2_Pi0recIsEB",    &STr2_Pi0recIsEB,    "STr2_Pi0recIsEB[STr2_NPi0_rec]/I");
    m_tree_opt->Branch( "STr2_IsoPi0_rec",    &STr2_IsoPi0_rec,     "STr2_IsoPi0_rec[STr2_NPi0_rec]/F");
    m_tree_opt->Branch( "STr2_S4S9_1",        &STr2_S4S9_1,         "STr2_S4S9_1[STr2_NPi0_rec]/F");
    m_tree_opt->Branch( "STr2_S4S9_2",        &STr2_S4S9_2,         "STr2_S4S9_2[STr2_NPi0_rec]/F");
    m_tree_opt->Branch( "STr2_n1CrisPi0_rec", &STr2_n1CrisPi0_rec,  "STr2_n1CrisPi0_rec[STr2_NPi0_rec]/I");
    m_tree_opt->Branch( "STr2_n2CrisPi0_rec", &STr2_n2CrisPi0_rec,  "STr2_n2CrisPi0_rec[STr2_NPi0_rec]/I");
    m_tree_opt->Branch( "STr2_mPi0_rec",      &STr2_mPi0_rec,       "STr2_mPi0_rec[STr2_NPi0_rec]/F");
    m_tree_opt->Branch( "STr2_ptG1_rec",      &STr2_ptG1_rec,       "STr2_ptG1_rec[STr2_NPi0_rec]/F");
    m_tree_opt->Branch( "STr2_ptG2_rec",      &STr2_ptG2_rec,       "STr2_ptG2_rec[STr2_NPi0_rec]/F");
    m_tree_opt->Branch( "STr2_etaPi0_rec",    &STr2_etaPi0_rec,     "STr2_etaPi0_rec[STr2_NPi0_rec]/F");
    m_tree_opt->Branch( "STr2_ptPi0_rec",     &STr2_ptPi0_rec,      "STr2_ptPi0_rec[STr2_NPi0_rec]/F");
    m_tree_opt->Branch( "STr2_DeltaRG1G2",    &STr2_DeltaRG1G2,     "STr2_DeltaRG1G2[STr2_NPi0_rec]/F");
    m_tree_opt->Branch( "STr2_Es_e1_1",       &STr2_Es_e1_1,        "STr2_Es_e1_1[STr2_NPi0_rec]/F");
    m_tree_opt->Branch( "STr2_Es_e1_2",       &STr2_Es_e1_2,        "STr2_Es_e1_2[STr2_NPi0_rec]/F");
    m_tree_opt->Branch( "STr2_Es_e2_1",       &STr2_Es_e2_1,        "STr2_Es_e2_1[STr2_NPi0_rec]/F");
    m_tree_opt->Branch( "STr2_Es_e2_2",       &STr2_Es_e2_2,        "STr2_Es_e2_2[STr2_NPi0_rec]/F");
    //m_tree->Branch( "STr_Es_nEE",         &STr_Es_nEE,          "STr_Es_nEE/I");
    //m_tree->Branch( "STr_Es_nES",         &STr_Es_nES,          "STr_Es_nES/I");
    //m_tree->Branch( "STr_Es_RecG1_E",     &STr_Es_RecG1_E,      "STr_Es_RecG1_E/F");
    //m_tree->Branch( "STr_Es_RecG1_Eta",   &STr_Es_RecG1_Eta,    "STr_Es_RecG1_Eta/F");
    //m_tree->Branch( "STr_Es_RecG1_Phi",   &STr_Es_RecG1_Phi,    "STr_Es_RecG1_Phi/F");
    //m_tree->Branch( "STr_Es_RecG1es_E",   &STr_Es_RecG1es_E,    "STr_Es_RecG1es_E/F");
    //m_tree->Branch( "STr_Es_e1_1",        &STr_Es_e1_1,         "STr_Es_e1_1/F");
    //m_tree->Branch( "STr_Es_e1_2",        &STr_Es_e1_2,         "STr_Es_e1_2/F");
    //m_tree->Branch( "STr_Es_RecG2_E",     &STr_Es_RecG2_E,      "STr_Es_RecG2_E/F");
    //m_tree->Branch( "STr_Es_RecG2_Eta",   &STr_Es_RecG2_Eta,    "STr_Es_RecG2_Eta/F");
    //m_tree->Branch( "STr_Es_RecG2_Phi",   &STr_Es_RecG2_Phi,    "STr_Es_RecG2_Phi/F");
    //m_tree->Branch( "STr_Es_RecG2es_E",   &STr_Es_RecG2es_E,    "STr_Es_RecG2es_E/F");
    //m_tree->Branch( "STr_Es_e2_1",        &STr_Es_e2_1,         "STr_Es_e2_1/F");
    //m_tree->Branch( "STr_Es_e2_2",        &STr_Es_e2_2,         "STr_Es_e2_2/F");
    //m_tree->Branch( "STr_Es_RecPi0_M",    &STr_Es_RecPi0_M,     "STr_Es_RecPi0_M/F");
    //m_tree->Branch( "STr_Es_RecPi0_Eta",  &STr_Es_RecPi0_Eta,   "STr_Es_RecPi0_Eta/F");
    //m_tree->Branch( "STr_Es_RecPi0es_M",  &STr_Es_RecPi0es_M,   "STr_Es_RecPi0es_M/F");
    //m_tree->Branch( "STr_Es_RecPi0es_Eta",&STr_Es_RecPi0es_Eta, "STr_Es_RecPi0es_Eta/F");
    //m_tree->Branch( "STr_Es_RecPi0esPos_M",  &STr_Es_RecPi0esPos_M,   "STr_Es_RecPi0esPos_M/F");
    //m_tree->Branch( "STr_Es_RecPi0esPos_Eta",&STr_Es_RecPi0esPos_Eta, "STr_Es_RecPi0esPos_Eta/F");
    //m_tree->Branch( "STr_Es_RecPi0esPos_Mw",  &STr_Es_RecPi0esPos_Mw,   "STr_Es_RecPi0esPos_Mw/F");
    //m_tree->Branch( "STr_Es_RecPi0esPos_Etaw",&STr_Es_RecPi0esPos_Etaw, "STr_Es_RecPi0esPos_Etaw/F");
    //m_tree->Branch( "STr_Es_Clu1es_Eta1", &STr_Es_Clu1es_Eta1,  "STr_Es_Clu1es_Eta1/F");
    //m_tree->Branch( "STr_Es_Clu1es_Phi1", &STr_Es_Clu1es_Phi1,  "STr_Es_Clu1es_Phi1/F");
    //m_tree->Branch( "STr_Es_Clu1es_x1"  , &STr_Es_Clu1es_x1,    "STr_Es_Clu1es_x1/F");
    //m_tree->Branch( "STr_Es_Clu1es_y1"  , &STr_Es_Clu1es_y1,    "STr_Es_Clu1es_y1/F");
    //m_tree->Branch( "STr_Es_Clu1es_z1"  , &STr_Es_Clu1es_z1,    "STr_Es_Clu1es_z1/F");
    //m_tree->Branch( "STr_Es_Clu2es_Eta1", &STr_Es_Clu2es_Eta1,  "STr_Es_Clu2es_Eta1/F");
    //m_tree->Branch( "STr_Es_Clu2es_Phi1", &STr_Es_Clu2es_Phi1,  "STr_Es_Clu2es_Phi1/F");
    //m_tree->Branch( "STr_Es_Clu2es_x1"  , &STr_Es_Clu2es_x1,    "STr_Es_Clu2es_x1/F");
    //m_tree->Branch( "STr_Es_Clu2es_y1"  , &STr_Es_Clu2es_y1,    "STr_Es_Clu2es_y1/F");
    //m_tree->Branch( "STr_Es_Clu2es_z1"  , &STr_Es_Clu2es_z1,    "STr_Es_Clu2es_z1/F");

    //m_tree->Branch( "STrPF_nClus",     &STrPF_nClus,      "STrPF_nClus/F");
    //m_tree->Branch( "STrPF_RecG1_E",   &STrPF_RecG1_E,    "STrPF_RecG1_E/F");
    //m_tree->Branch( "STrPF_RecG1_Eta", &STrPF_RecG1_Eta,  "STrPF_RecG1_Eta/F");
    //m_tree->Branch( "STrPF_RecG1_Phi", &STrPF_RecG1_Phi,  "STrPF_RecG1_Phi/F");
    //m_tree->Branch( "STrPF_RecG1_DR",  &STrPF_RecG1_DR,   "STrPF_RecG1_DR/F");
    //m_tree->Branch( "STrPF_RecG2_E",   &STrPF_RecG2_E,    "STrPF_RecG2_E/F");
    //m_tree->Branch( "STrPF_RecG2_Eta", &STrPF_RecG2_Eta,  "STrPF_RecG2_Eta/F");
    //m_tree->Branch( "STrPF_RecG2_Phi", &STrPF_RecG2_Phi,  "STrPF_RecG2_Phi/F");
    //m_tree->Branch( "STrPF_RecG2_DR",  &STrPF_RecG2_DR,   "STrPF_RecG2_DR/F");
    //m_tree->Branch( "STrPF_Pi0_M",     &STrPF_Pi0_M,      "STrPF_Pi0_M/F");
    //m_tree->Branch( "STrPF_Pi0_Eta",   &STrPF_Pi0_Eta,    "STrPF_Pi0_Eta/F");
    //m_tree->Branch( "STrPF_nPi0_rec",   &STrPF_nPi0_rec,    "STrPF_nPi0_rec/I");
    //m_tree->Branch( "STrPF_Pi0recIsEB", &STrPF_Pi0recIsEB,  "STrPF_Pi0recIsEB[STrPF_nPi0_rec]/I");
    //m_tree->Branch( "STrPF_mPi0_rec",   &STrPF_mPi0_rec,    "STrPF_mPi0_rec[STrPF_nPi0_rec]/F");
    //m_tree->Branch( "STrPF_etaPi0_rec", &STrPF_etaPi0_rec,  "STrPF_etaPi0_rec[STrPF_nPi0_rec]/F");

    // mc truth
    if(storeMCTruth_) {
	  //m_tree->Branch( "STr_pi0_x",     &STr_pi0_x,    "STr_pi0_x/F");
	  //m_tree->Branch( "STr_pi0_y",     &STr_pi0_y,    "STr_pi0_y/F");
	  //m_tree->Branch( "STr_pi0_z",     &STr_pi0_z,    "STr_pi0_z/F");
	  //m_tree->Branch( "STr_pi0_eta",     &STr_pi0_eta,    "STr_pi0_eta/F");
	  //m_tree->Branch( "STr_pi0_phi",     &STr_pi0_phi,    "STr_pi0_phi/F");
	  //m_tree->Branch( "STr_ptPi0",       &STr_ptPi0,      "STr_ptPi0/F");
	  //m_tree->Branch( "STr_MPi0",        &STr_MPi0,       "STr_MPi0/F");
	  //m_tree->Branch( "STr_Pi0IsEB",     &STr_Pi0IsEB,      "STr_Pi0IsEB/I");
	  //m_tree->Branch( "STr_G1Uncon",     &STr_G1Uncon,      "STr_G1Uncon/O");
	  //m_tree->Branch( "STr_G2Uncon",     &STr_G2Uncon,      "STr_G2Uncon/O");
	  //m_tree->Branch( "STr_Sim_Dr",      &STr_Sim_Dr,       "STr_Sim_Dr/F");
	  //m_tree->Branch( "STr_RecG1_E",     &STr_RecG1_E,      "STr_RecG1_E/F");
	  //m_tree->Branch( "STr_RecG1_Eta",   &STr_RecG1_Eta,    "STr_RecG1_Eta/F");
	  //m_tree->Branch( "STr_RecG1_Phi",   &STr_RecG1_Phi,    "STr_RecG1_Phi/F");
	  //m_tree->Branch( "STr_RecG1_DR",    &STr_RecG1_DR,     "STr_RecG1_DR/F");
	  //m_tree->Branch( "STr_RecG1_NCris", &STr_RecG1_NCris,  "STr_RecG1_NCris/F");
	  //m_tree->Branch( "STr_SimG1_E",     &STr_SimG1_E,      "STr_SimG1_E/F");
	  //m_tree->Branch( "STr_SimG1_Eta",   &STr_SimG1_Eta,    "STr_SimG1_Eta/F");
	  //m_tree->Branch( "STr_SimG1_Phi",   &STr_SimG1_Phi,    "STr_SimG1_Phi/F");
	  //m_tree->Branch( "STr_SimG1_X",     &STr_SimG1_X,      "STr_SimG1_X/F");
	  //m_tree->Branch( "STr_SimG1_Y",     &STr_SimG1_Y,      "STr_SimG1_Y/F");
	  //m_tree->Branch( "STr_SimG1_Z",     &STr_SimG1_Z,      "STr_SimG1_Z/F");
	  //m_tree->Branch( "STr_RecG2_E",     &STr_RecG2_E,      "STr_RecG2_E/F");
	  //m_tree->Branch( "STr_RecG2_Eta",   &STr_RecG2_Eta,    "STr_RecG2_Eta/F");
	  //m_tree->Branch( "STr_RecG2_Phi",   &STr_RecG2_Phi,    "STr_RecG2_Phi/F");
	  //m_tree->Branch( "STr_RecG2_DR",    &STr_RecG2_DR,     "STr_RecG2_DR/F");
	  //m_tree->Branch( "STr_RecG2_NCris", &STr_RecG2_NCris,  "STr_RecG2_NCris/F");
	  //m_tree->Branch( "STr_SimG2_E",     &STr_SimG2_E,      "STr_SimG2_E/F");
	  //m_tree->Branch( "STr_SimG2_Eta",   &STr_SimG2_Eta,    "STr_SimG2_Eta/F");
	  //m_tree->Branch( "STr_SimG2_Phi",   &STr_SimG2_Phi,    "STr_SimG2_Phi/F");
	  //m_tree->Branch( "STr_SimG2_X",     &STr_SimG2_X,      "STr_SimG2_X/F");
	  //m_tree->Branch( "STr_SimG2_Y",     &STr_SimG2_Y,      "STr_SimG2_Y/F");
	  //m_tree->Branch( "STr_SimG2_Z",     &STr_SimG2_Z,      "STr_SimG2_Z/F");
	  //m_tree->Branch( "STr_NCristG1",    &STr_NCristG1,     "STr_NCristG1/F");
	  //m_tree->Branch( "STr_NCristG2",    &STr_NCristG2,     "STr_NCristG2/F");
	  //m_tree->Branch( "STr_RecPi0_M",    &STr_RecPi0_M,     "STr_RecPi0_M/F");
	  //m_tree->Branch( "STr_RecPi0_Eta",  &STr_RecPi0_Eta,    "STr_RecPi0_Eta/F");

	  //m_tree->Branch( "STr_ESimG1_E",     &STr_ESimG1_E,      "STr_ESimG1_E/F");
	  //m_tree->Branch( "STr_ESimG1_Eta",   &STr_ESimG1_Eta,    "STr_ESimG1_Eta/F");
	  //m_tree->Branch( "STr_ESimG1_Phi",   &STr_ESimG1_Phi,    "STr_ESimG1_Phi/F");
	  //m_tree->Branch( "STr_ESimG1_X",     &STr_ESimG1_X,      "STr_ESimG1_X/F");
	  //m_tree->Branch( "STr_ESimG1_Y",     &STr_ESimG1_Y,      "STr_ESimG1_Y/F");
	  //m_tree->Branch( "STr_ESimG1_Z",     &STr_ESimG1_Z,      "STr_ESimG1_Z/F");
	  //m_tree->Branch( "STr_ESimG2_E",     &STr_ESimG2_E,      "STr_ESimG2_E/F");
	  //m_tree->Branch( "STr_ESimG2_Eta",   &STr_ESimG2_Eta,    "STr_ESimG2_Eta/F");
	  //m_tree->Branch( "STr_ESimG2_Phi",   &STr_ESimG2_Phi,    "STr_ESimG2_Phi/F");
	  //m_tree->Branch( "STr_ESimG2_X",     &STr_ESimG2_X,      "STr_ESimG2_X/F");
	  //m_tree->Branch( "STr_ESimG2_Y",     &STr_ESimG2_Y,      "STr_ESimG2_Y/F");
	  //m_tree->Branch( "STr_ESimG2_Z",     &STr_ESimG2_Z,      "STr_ESimG2_Z/F");


	  //m_tree->Branch( "nMC",           &nMC,          "nMC/I");
	  //m_tree->Branch( "pdgIdMC",       pdgIdMC,       "pdgIdMC[nMC]/I");
	  //m_tree->Branch( "statusMC",      statusMC,      "statusMC[nMC]/I");
	  //m_tree->Branch( "motherIDMC",    motherIDMC,    "motherIDMC[nMC]/I");
	  //m_tree->Branch( "motherIndexMC", motherIndexMC, "motherIndexMC[nMC]/I");
	  //m_tree->Branch( "ptMC",          ptMC,          "ptMC[nMC]/F");
	  //m_tree->Branch( "mMC",           mMC,           "mMC[nMC]/F");
	  //m_tree->Branch( "eMC",           eMC,           "eMC[nMC]/F");
	  //m_tree->Branch( "etaMC",         etaMC,         "etaMC[nMC]/F");
	  //m_tree->Branch( "phiMC",         phiMC,         "phiMC[nMC]/F");
	  //m_tree->Branch( "convertedMC",   convertedMC,   "convertedMC[nMC]/O");
	  //m_tree->Branch("ConversionPi0_rho",&ConversionPi0_rho,"ConversionPi0_rho[nMC]/F");
	  //m_tree->Branch("ConversionPi0_z",&ConversionPi0_z,"ConversionPi0_z[nMC]/F");
	  //m_tree->Branch("ConversionG1_x",&ConversionG1_x,"ConversionG1_x[nMC]/F");
	  //m_tree->Branch("ConversionG1_y",&ConversionG1_y,"ConversionG1_y[nMC]/F");
	  //m_tree->Branch("ConversionG1_rho",&ConversionG1_rho,"ConversionG1_rho[nMC]/F");
	  //m_tree->Branch("ConversionG1_z",&ConversionG1_z,"ConversionG1_z[nMC]/F");
	  //m_tree->Branch("ConversionG2_x",&ConversionG2_x,"ConversionG2_x[nMC]/F");
	  //m_tree->Branch("ConversionG2_y",&ConversionG2_y,"ConversionG2_y[nMC]/F");
	  //m_tree->Branch("ConversionG2_rho",&ConversionG2_rho,"ConversionG2_rho[nMC]/F");
	  //m_tree->Branch("ConversionG2_z",&ConversionG2_z,"ConversionG2_z[nMC]/F");

	  //m_tree->Branch("nSIM",&nSIM,"nSIM/I");
	  //m_tree->Branch("pdgIdSIM",&pdgIdSIM,"pdgIdSIM[nSIM]/I");
	  //m_tree->Branch("statusSIM",&statusSIM,"statusSIM[nSIM]/I");
	  //m_tree->Branch("motherGenIndexSIM",&motherGenIndexSIM,"motherGenIndexSIM[nSIM]/I");
	  //m_tree->Branch("ptSIM ",&ptSIM ,"ptSIM[nSIM]/F");
	  //m_tree->Branch("eSIM  ",&eSIM  ,"eSIM[nSIM]/F");
	  //m_tree->Branch("etaSIM",&etaSIM,"etaSIM[nSIM]/F");
	  //m_tree->Branch("phiSIM",&phiSIM,"phiSIM[nSIM]/F");
	  //m_tree->Branch("rSIM",&rSIM,"rSIM[nSIM]/F");
	  //m_tree->Branch("zSIM",&zSIM,"zSIM[nSIM]/F");
    }

    //EBdeltaR      = new TH1F("EBdeltaR","EB P0 DR", 50, 0., 0.5);
    //EBRisoPi0_Pt  = new TH1F("EBRisoPi0_Pt","Pt Risol P0 EB", 50, -1.2, 0.2);
    //EBRisoPi0_Eta = new TH1F("EBRisoPi0_Eta","Eta Risol P0 EB", 50, -1.5, 1.5);
    //EBRisoPi0_Phi = new TH1F("EBRisoPi0_Phi","Phi Risol P0 EB", 50, -1.5, 1.5);
    //EBRisoPi0_E = new TH1F("EBRisoPi0_E","E Risol P0 EB", 50, -1.2, 0.2);
    //EBRisoGammaUnc_E = new TH1F("EBRisoGammaUnc_E","E Risol Gamma Unconv EB", 50, -1., 1.);
    //EBRisoGammaUnc_Eta = new TH1F("EBRisoGammaUnc_Eta","Eta Risol Gamma Unconv EB", 50, -0.1, 0.1);
    //EBRisoGammaUnc_Phi = new TH1F("EBRisoGammaUnc_Phi","Phi Risol Gamma Unconv EB", 50, -0.1, 0.1);
    //EBRisoGammaUnc_DR = new TH1F("EBRisoGammaUnc_DR","EB DR Gamma1", 50, 0., 0.1);
    //EBRisoGammaUnc2_E = new TH1F("EBRisoGammaUnc2_E","E Risol Gamma2 Unconv EB", 50, -1., 1.);
    //EBRisoGammaUnc2_Eta = new TH1F("EBRisoGammaUnc2_Eta","Eta Risol Gamma2 Unconv EB", 50, -0.1, 0.1);
    //EBRisoGammaUnc2_Phi = new TH1F("EBRisoGammaUnc2_Phi","Phi Risol Gamma2 Unconv EB", 50, -0.1, 0.1);
    //EBRisoGammaUnc2_DR = new TH1F("EBRisoGammaUnc2_DR","EB DR Gamma2", 50, 0., 0.1);
    //EBmPioUnc = new TH1F("EBmPioUnc","Unconv EB pi0", 100, 0.0, 2.);
    //EBmPioUncOnlyOne = new TH1F("EBmPioUncOnlyOne","Unconv Only One EB pi0", 100, 0.0, 2.);
    //EBmPioNonClu = new TH1F("EBmPioNonClu","Converted EB pi0", 100, 0.0, 2.);
    //EEdeltaR      = new TH1F("EEdeltaR","EE P0 DR", 50, 0., 0.5);
    //EERisoPi0_Pt  = new TH1F("EERisoPi0_Pt","Pt Risol P0 EE", 50, -1.2, 0.2);
    //EERisoPi0_Eta = new TH1F("EERisoPi0_Eta","Eta Risol P0 EE", 50, -1.5, 1.5);
    //EERisoPi0_Phi = new TH1F("EERisoPi0_Phi","Phi Risol P0 EE", 50, -1.5, 1.5);
    //EERisoPi0_E = new TH1F("EERisoPi0_E","E Risol P0 EE", 50, -1.2, 0.2);
    //EERisoGammaUnc_E = new TH1F("EERisoGammaUnc_E","E Risol Gamma Unconv EE", 50, -1., 1.);
    //EERisoGammaUnc_Eta = new TH1F("EERisoGammaUnc_Eta","Eta Risol Gamma Unconv EE", 50, -0.1, 0.1);
    //EERisoGammaUnc_Phi = new TH1F("EERisoGammaUnc_Phi","Phi Risol Gamma Unconv EE", 50, -0.1, 0.1);
    //EERisoGammaUnc_DR = new TH1F("EERisoGammaUnc_DR","EE DR Gamma1", 50, 0., 0.1);
    //EERisoGammaUnc2_E = new TH1F("EERisoGammaUnc2_E","E Risol Gamma2 Unconv EE", 50, -1., 1.);
    //EERisoGammaUnc2_Eta = new TH1F("EERisoGammaUnc2_Eta","Eta Risol Gamma2 Unconv EE", 50, -0.1, 0.1);
    //EERisoGammaUnc2_Phi = new TH1F("EERisoGammaUnc2_Phi","Phi Risol Gamma2 Unconv EE", 50, -0.1, 0.1);
    //EERisoGammaUnc2_DR = new TH1F("EERisoGammaUnc2_DR","EE DR Gamma2", 50, 0., 0.1);
    //EEmPioUnc = new TH1F("EEmPioUnc","Unconv EE pi0", 100, 0.0, 1.4);
    //EEmPioUncOnlyOne = new TH1F("EEmPioUncOnlyOne","Unconv Only One EE pi0", 100, 0.0, 2.);
    //EEmPioNonClu = new TH1F("EEmPioNonClu","Converted EE pi0", 100, 0.0, 2.);

    //DeltaE_ES  = new TH1F("DeltaE_ES","Percentage E recovered", 100, 0.0, 1.);
    //ES_E1layer = new TH1F("ES_E1layer","E 1st layer in ES", 100, 0., 0.5);
    //ES_E2layer = new TH1F("ES_E2layer","E 2st layer in ES", 100, 0., 0.5);

    //ConversionGammaRho_z = new TH2F("ConversionGammaRho_z","Conversion of gamma: Z (x-axis) vs Rho (y-axis)", 400, -330., 330., 400, 0., 129.);
    //ConversionGammax_y = new TH2F("ConversionGammax_y","Conversion of gamma: X (x-axis) vs Y (y-axis)", 400, -129., 129., 400, -129., 129.);
    //Gammas_Dr_E = new TH2F("Gammas_Dr_E","Delta R gammas: X (Delta R) vs Y (energy)", 120, 0., 0.3, 120., 0., 60.);
    //Pi0_M_Eta = new TH2F("Pi0_M_Eta","Pio mass vs Eta: X (Eta) vs Y (mass)", 200, 0., 3., 200., 0., 1.);
    //Pi0_assoc_M_Eta = new TH2F("Pi0_assoc_M_Eta","Associated Pio mass vs Eta: X (Eta) vs Y (mass)", 200, 0., 3., 200., 0., 1.);
    //Gammas_Dr_risE = new TH2F("Gammas_Dr_risE","Delta R gammas: X (Delta R) vs Y (energy resol.)", 120, 0., 0.15, 120, -1., 1.);
    Cluster_NCrist_DRgamma = new TH2F("Cluster_NCrist_DRgamma","N Crist Cluster less energetic vs Dr gammas: X (N Crist) vs Y (DRgammas)", 9, 0., 9., 70, 0.01, 0.2);
    ES_DEta_Eta      = new TH2F("ES_DEta_Eta",   "ES Delta Eta vs Eta: X (Delta Eta) vs Y (Eta)", 100, -0.04, 0.04, 100, -3., 3.);
    //ES_DEta_EtaMod = new TH2F("ES_DEta_EtaMod","ES Delta Eta vs Eta: X (fabs Delta Eta) vs Y (Eta)", 100, 0., 0.04, 100, -3., 3.);
    //ES_DEta_E      = new TH2F("ES_DEta_E",     "ES Delta Eta vs E: X (Delta Eta) vs Y (E)", 100, -0.04, 0.04, 100, 0., 50.);
    ES_DEta_Phi      = new TH2F("ES_DEta_Phi",   "ES Delta Eta vs Phi: X (Delta Eta) vs Y (Phi)", 100, -0.04, 0.04, 100, -3.15, 3.15);
    ES_DPhi_Eta      = new TH2F("ES_DPhi_Eta",   "ES Delta Eta vs Eta: X (Delta Phi) vs Y (Eta)", 100, -0.04, 0.04, 100, -3., 3.);
    //ES_DPhi_EtaMod   = new TH2F("ES_DPhi_EtaMod","ES Delta Eta vs Eta: X (fabs Phi Eta) vs Y (Eta)", 100, 0., 0.04, 100, -3., 3.);
    //ES_DPhi_E        = new TH2F("ES_DPhi_E",     "ES Delta Eta vs E: X (Delta Phi) vs Y (E)", 100, -0.04, 0.04, 100, 0., 50.);
    //ES_DPhi_Phi      = new TH2F("ES_DPhi_Phi",   "ES Delta Eta vs Phi: X (Delta Phi) vs Y (Phi)", 100, -0.04, 0.04, 100, -3.15, 3.15);
    h2_EtaCorr       = new TH2F("h2_EtaCorr",    "Cont Correction: X (iEta) vs Y (E bin)", 85, 0.5, 85.5, 12, 0.5, 12.5);

    G1G2_unc = new TH1F("G1G2_unc","Prob Both Gamma Converted", 100, -3., 3.);
    G1G2_tot = new TH1F("G1G2_tot","Both Gamma", 100, -3., 3.);
    G1_unc = new TH1F("G1_unc","Prob only on gamma Converted", 100, -3., 3.);
    G2_unc = new TH1F("G2_unc","Prob No gamma Converted", 100, -3., 3.);

    h_Eff_EB  = new TH1F("h_Eff_EB","N Entries EB CutbyCut", 5, -0.5, 5.5);

}

// ------------ method called once each job just after ending the event loop  ------------
void 
NewPi0Dumper_Gun::endJob() {

    cout<<"End Job"<<endl;
    cout<<"Cross Sec(pi0->e+,e-,gamma): "<<eeg/Tot_Ev<<endl;
    cout<<"Cross Sec(pi0->e+,e-,e+,e-): "<<eeee/Tot_Ev<<endl;

    if(!OnlyContCorr_){
	  m_file->cd();

	  //EBdeltaR->Write();
	  //EBRisoPi0_Pt->Write(); 
	  //EBRisoPi0_E->Write(); 
	  //EBRisoPi0_Eta->Write();
	  //EBRisoPi0_Phi->Write();
	  //EBRisoGammaUnc_E->Write();
	  //EBRisoGammaUnc_Eta->Write();
	  //EBRisoGammaUnc_Phi->Write();
	  //EBRisoGammaUnc_DR->Write();
	  //EBRisoGammaUnc2_E->Write();
	  //EBRisoGammaUnc2_Eta->Write();
	  //EBRisoGammaUnc2_Phi->Write();
	  //EBRisoGammaUnc2_DR->Write();
	  //EBmPioUnc->Write();
	  //EBmPioUncOnlyOne->Write();
	  //EBmPioNonClu->Write();
	  //EEdeltaR->Write();     
	  //EERisoPi0_Pt->Write(); 
	  //EERisoPi0_E->Write(); 
	  //EERisoPi0_Eta->Write();
	  //EERisoPi0_Phi->Write();
	  //EERisoGammaUnc_E->Write();
	  //EERisoGammaUnc_Eta->Write();
	  //EERisoGammaUnc_Phi->Write();
	  //EERisoGammaUnc_DR->Write();
	  //EERisoGammaUnc2_E->Write();
	  //EERisoGammaUnc2_Eta->Write();
	  //EERisoGammaUnc2_Phi->Write();
	  //EERisoGammaUnc2_DR->Write();
	  //EEmPioUnc->Write();
	  //EEmPioUncOnlyOne->Write();
	  //EEmPioNonClu->Write();

	  //DeltaE_ES->Write();
	  //ES_E1layer->Write();
	  //ES_E2layer->Write();

	  //ConversionGammaRho_z->Write();
	  //ConversionGammax_y->Write();
	  //Gammas_Dr_E->Write();
	  //Pi0_M_Eta->Write();
	  //Pi0_assoc_M_Eta->Write();
	  //Gammas_Dr_risE->Write();
	  Cluster_NCrist_DRgamma->Write();
	  ES_DEta_Eta->Write();
	  //ES_DEta_EtaMod->Write();
	  //ES_DEta_E->Write();
	  ES_DEta_Phi->Write();
	  ES_DPhi_Eta->Write();
	  //ES_DPhi_EtaMod->Write();
	  //ES_DPhi_E->Write();
	  //ES_DPhi_Phi->Write();
	  h2_EtaCorr->Write();

	  G1G2_unc->Divide(G1G2_tot);
	  G1G2_unc->SetMaximum(1.);  G1G2_unc->SetMinimum(0.);
	  G1G2_unc->Write();
	  //  G1G2_tot->Write();
	  G1_unc->Divide(G1G2_tot);
	  G1_unc->SetMaximum(1.);  G1_unc->SetMinimum(0.);
	  G1_unc->Write();
	  G2_unc->Divide(G1G2_tot);
	  G2_unc->SetMaximum(1.);  G2_unc->SetMinimum(0.);
	  G2_unc->Write();

	  //m_tree->Write();
	  m_tree_opt->Write();
    }
    else{
	  m_file_contCorr->cd();
	  //for(int i=0; i<N_IETA; ++i)  ContCorrEB_1[i]->Write();
	  //for(int i=0; i<N_IETA; ++i)  ContCorrEB_2[i]->Write();
	  //for(int i=0; i<N_IETA; ++i)  ContCorrEB_3[i]->Write();
	  //for(int i=0; i<N_IETA; ++i)  ContCorrEB_4[i]->Write();
	  //for(int i=0; i<N_IETA; ++i)  ContCorrEB_5[i]->Write();
	  //for(int i=0; i<N_IETA; ++i)  ContCorrEB_6[i]->Write();
	  //for(int i=0; i<N_IETA; ++i)  ContCorrEB_7[i]->Write();
	  for(int i=0; i<20*PTBINSEB; ++i)  ContCorrEB_PHI_7PTBin_p[i]->Write();
	  for(int i=0; i<20*PTBINSEB; ++i)  ContCorrEB_PHI_7PTBin_m[i]->Write();
	  //for(int i=0; i<N_iPHI*PTBINSEB; ++i)  ContCorrEB_PHI_7PTBin_360iPHI_p[i]->Write();
	  //for(int i=0; i<N_iPHI*PTBINSEB; ++i)  ContCorrEB_PHI_7PTBin_360iPHI_m[i]->Write();  

	  //for(int i=0; i<N_ETARING; ++i)  ContCorrEE_1[i]->Write();
	  //for(int i=0; i<N_ETARING; ++i)  ContCorrEE_2[i]->Write();
	  //for(int i=0; i<N_ETARING; ++i)  ContCorrEE_3[i]->Write();
	  //for(int i=0; i<N_ETARING; ++i)  ContCorrEE_4[i]->Write();
	  //for(int i=0; i<N_ETARING; ++i)  ContCorrEE_5[i]->Write();
	  //for(int i=0; i<N_ETARING; ++i)  ContCorrEE_6[i]->Write();
	  //for(int i=0; i<N_ETARING; ++i)  ContCorrEE_7[i]->Write();

    }
}

// ------------ method called to for each event  ------------
    void
NewPi0Dumper_Gun::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{

    bool EB_HLT=true, EE_HLT=true;
    if( HLTResults_ ){
	  if(Are_pi0_){
		EB_HLT = GetHLTResults(iEvent, "AlCa_EcalPi0EBonly.*");
		EE_HLT = GetHLTResults(iEvent, "AlCa_EcalPi0EEonly.*");
	  }
	  else{
		EB_HLT = GetHLTResults(iEvent, "AlCa_EcalEtaEBonly_*");
		EE_HLT = GetHLTResults(iEvent, "AlCa_EcalEtaEEonly_*");
	  }
    }

    //ES
    edm::ESHandle<CaloGeometry> geoHandle;
    iSetup.get<CaloGeometryRecord>().get(geoHandle);
    geometry = geoHandle.product();
    estopology_ = new EcalPreshowerTopology(geoHandle);
    esGeometry_ = (dynamic_cast<const EcalPreshowerGeometry*>( (CaloSubdetectorGeometry*) geometry->getSubdetectorGeometry (DetId::Ecal,EcalPreshower) ));

    // inizialize the variable for the tree.
    InitTreeVariable();
    MyMCParicles.clear();
    MyEBParicles.clear();
    MyEEParicles.clear();

    using namespace edm;
    using namespace reco;

    // tree variables
    runn = iEvent.id().run();
    eventn = iEvent.id().event();
    ls = iEvent.luminosityBlock();

    if(storeMCTruth_) FillMCInfo(iEvent, iSetup);

    //FillTriggerInfo(iEvent, iSetup);

    //EB cluster
    Handle< EBRecHitCollection > ebHandle;
    iEvent.getByLabel ( EBRecHitCollectionTag_, ebHandle);
    const EBRecHitCollection* hits = ebHandle.product();

    // 3x3 clusters
    std::vector< CaloCluster > clusters; // contains the output clusters
    std::vector< ClusterShape > shapes; // contains the output clusters
    vector<int> Ncristal_EB;
    vector<float> s4s9_EB; vector<float> s1s9_EB; vector<float> s2s9_EB;
    //vector<int> Nclus_ieta_EB;
    //vector<DetId> Nclus_id_EB;
    vector<float> EtSeed_EB;
    Ncristal_EB.clear(); s4s9_EB.clear(); s1s9_EB.clear(); s2s9_EB.clear();
    EtSeed_EB.clear();

    if(EB_HLT){

	  make3x3Clusters<EBDetId,EBRecHitCollection,EBRecHitCollection::const_iterator>(geometry, hits, &clusters, &shapes, iEvent.time(), &Ncristal_EB, &s4s9_EB, &s1s9_EB, &s2s9_EB, &EtSeed_EB);
	  if( Ncristal_EB.size() != s4s9_EB.size() || clusters.size() != s2s9_EB.size() || Ncristal_EB.size() != clusters.size() ) cout<<"WARNING size EB"<<endl;
	  // keep track of clusters used to make pi0 candidates
	  std::map<size_t,size_t> savedCluEB;
	  nClu = 0;

	  // loop over clusters to make Pi0
	  nPi0 = 0; nPi0_EB = 0; nPi0_EE = 0;
	  for(size_t i=0; i< clusters.size(); ++i) {

		const CaloCluster* g1 = &(clusters[i]);

		// track association
		math::XYZPoint impact1(999.,999.,999.);

		// 2nd loop over clusters
		for(size_t j=i+1; j<clusters.size(); ++j) 
		{

		    if(nPi0>= NPI0MAX/2 || nClu >= NCLUMAX/2) {
			  cout << "WARNING: No more space in the arrays: nPi0: " << nPi0;
			  continue;
		    }

		    const CaloCluster* g2 = &(clusters[j]);           
		    // using the origin
		    math::PtEtaPhiMLorentzVector g1P4( g1->energy()/cosh(g1->eta()), g1->eta(), g1->phi(), 0. );
		    math::PtEtaPhiMLorentzVector g2P4( g2->energy()/cosh(g2->eta()), g2->eta(), g2->phi(), 0. );
		    math::PtEtaPhiMLorentzVector pi0P4 = g1P4 + g2P4;

		    // use PV 
		    TVector3 tmpV( g1->x(), g1->y(), g1->z());
		    math::PtEtaPhiMLorentzVector g1P4PV( g1->energy()/cosh(tmpV.Eta()), tmpV.Eta(), tmpV.Phi(), 0. );

		    tmpV = TVector3( g2->x(), g2->y(), g2->z());
		    math::PtEtaPhiMLorentzVector g2P4PV( g2->energy()/cosh(tmpV.Eta()), tmpV.Eta(), tmpV.Phi(), 0. );
		    math::PtEtaPhiMLorentzVector pi0P4PV = g1P4PV + g2P4PV;

		    // basic selection to reduce combinatorics
		    if(pi0P4PV.pt() < ptpi0Cut_) continue;

		    //		    fillPi0Tree(  pi0P4PV, savedCluEB,
		    //				g1P4PV, g2P4PV,
		    //				shapes,
		    //				g1, g2, nClu, i, j, Ncristal_EB, EtSeed_EB);

		    //new cut
		    float nextClu = 999., Drtmp = 999.;
		    for(size_t ind=0; ind<clusters.size(); ++ind){
			  const CaloCluster* Gtmp = &(clusters[ind]);
			  double deltaR1 = DR(Gtmp->phi(),g1P4.phi(),Gtmp->eta(),g1P4.eta());
			  double deltaR2 = DR(Gtmp->phi(),g2P4.phi(),Gtmp->eta(),g2P4.eta());
			  if( ind!=i && ind!=j && (deltaR1<Drtmp || deltaR2<Drtmp ) ){
				nextClu = min(deltaR1,deltaR2);
				Drtmp = nextClu;
			  }
		    }
		    if( clusters.size()<3 ) nextClu=999.;
		    STr2_IsoPi0_rec[nPi0] = nextClu;
		    if( g1->energy()>g2->energy() ){
			  STr2_n1CrisPi0_rec[nPi0] = Ncristal_EB[i];
			  STr2_n2CrisPi0_rec[nPi0] = Ncristal_EB[j];
		    }
		    else{
			  STr2_n1CrisPi0_rec[nPi0] = Ncristal_EB[j];
			  STr2_n2CrisPi0_rec[nPi0] = Ncristal_EB[i];
		    }
		    STr2_mPi0_rec[nPi0] = pi0P4.mass();
		    STr2_ptG1_rec[nPi0] = g1P4.pt();
		    STr2_ptG2_rec[nPi0] = g2P4.pt();
		    STr2_S4S9_1[nPi0] = s4s9_EB[i];
		    STr2_S4S9_2[nPi0] = s4s9_EB[j];
		    STr2_etaPi0_rec[nPi0] = pi0P4.Eta();
		    STr2_ptPi0_rec[nPi0] = pi0P4.Pt();
		    STr2_Pi0recIsEB[nPi0] = 1;
		    STr2_DeltaRG1G2[nPi0] = DR(g1P4PV.phi(),g2P4PV.phi(),g1P4PV.eta(),g2P4PV.eta() );
		    STr2_Es_e1_1[nPi0] = -1.;            STr2_Es_e1_1[nPi0] = -1.;
		    STr2_Es_e2_2[nPi0] = -1.;            STr2_Es_e2_2[nPi0] = -1.;
		    //Pi0_M_Eta->Fill(fabs(pi0P4.Eta()),pi0P4.mass());
		    nPi0++; nPi0_EB++;
		    TLorentzVector thispar; thispar.SetPtEtaPhiE(pi0P4.pt(),pi0P4.eta(),pi0P4.phi(),pi0P4.energy());
		    MyEBParicles.push_back(thispar);
		} // loop over clusters (g2)
	  } // loop over clusters to make pi0 
	  // endcap 3x3 clusters
    }//EB_HLT

    // EE rechits
    // ES
    Handle< ESRecHitCollection > esHandle;
    iEvent.getByLabel ( ESRecHitCollectionTag_, esHandle);

    Handle< EERecHitCollection > eeHandle;
    iEvent.getByLabel ( EERecHitCollectionTag_, eeHandle);
    const EERecHitCollection* hitsEE = eeHandle.product();

    std::vector< CaloCluster > clustersEE; // contains the output clusters
    std::vector< ClusterShape > shapesEE; // contains the output clusters
    vector<int> Ncristal_EE;
    vector<float> s4s9_EE; vector<float> s1s9_EE; vector<float> s2s9_EE;
    vector<float> EtSeed_EE;
    Ncristal_EE.clear(); clustersEE.clear();
    EtSeed_EE.clear(); s4s9_EE.clear(); s1s9_EE.clear(); s2s9_EE.clear();
    std::vector< CaloCluster > eseeclusters_tot, eseeclusters;
    std::vector< GlobalPoint > posES;
    std::vector< float > Es_e1, Es_e2, Es_e1_tot, Es_e2_tot;
    eseeclusters.clear(); eseeclusters_tot.clear();
    posES.clear(); Es_e1.clear(); Es_e2.clear(); Es_e1_tot.clear(); Es_e2_tot.clear();
    std::vector< float > s4s9_EE_tot;
    if(EE_HLT){
	  make3x3Clusters<EEDetId,EERecHitCollection,EERecHitCollection::const_iterator>(geometry, hitsEE, &clustersEE, &shapesEE, iEvent.time(), &Ncristal_EE, &s4s9_EE, &s1s9_EE, &s2s9_EE, &EtSeed_EE);

	  //loop over eecluster to find matches with preshower
	  PreshowerTools esClusteringAlgo(geometry, estopology_, esHandle);
	  bool Added_One=false;
	  int i=0;
	  for( std::vector<CaloCluster>::const_iterator eeclus_iter  = clustersEE.begin(); eeclus_iter != clustersEE.end(); ++eeclus_iter, i++ ){
		Added_One=false;
		double X = eeclus_iter->x();       double Y = eeclus_iter->y();       double Z = eeclus_iter->z();
		const GlobalPoint point(X,Y,Z);


		DetId tmp1 = esGeometry_->getClosestCellInPlane(point,1);
		DetId tmp2 = esGeometry_->getClosestCellInPlane(point,2);

		if ((tmp1.rawId()!=0) && (tmp2.rawId()!=0) && fabs(point.eta())>1.66 && fabs(point.eta()<2.56 ) )//@ fiducial cut
		{
		    ESDetId tmp1_conversion (tmp1);
		    ESDetId tmp2_conversion (tmp2);

		    PreshowerCluster preshowerclusterp1 = esClusteringAlgo.makeOnePreshowerCluster( PreshowerTools::clusterwindowsize_, &tmp1_conversion);
		    PreshowerCluster preshowerclusterp2 = esClusteringAlgo.makeOnePreshowerCluster( PreshowerTools::clusterwindowsize_, &tmp2_conversion);
		    double e1 = preshowerclusterp1.energy();
		    double e2 = preshowerclusterp2.energy();
		    // GeV to #MIPs
		    e1 = e1 / PreshowerTools::mip_;
		    e2 = e2 / PreshowerTools::mip_;
		    double tempenergy = eeclus_iter->energy();

		    //if(e1+e2 > 1.0e-10) 
		    if(e1 > 2.0 || e2 > 2.0) /// cut @ 2 MIPs as suggested by Ming @ DPG/EGamma Joint Meeting 19.03.2012 
		    {
			  Es_e1.push_back(PreshowerTools::gamma_*(PreshowerTools::calib_planeX_*e1)); Es_e2.push_back(PreshowerTools::gamma_*(PreshowerTools::calib_planeX_*e2));
			  double deltaE = PreshowerTools::gamma_*(PreshowerTools::calib_planeX_*e1 + PreshowerTools::calib_planeY_*e2);

			  //if((e1+e2)!=0.) DeltaE_ES->Fill( ((deltaE + eeclus_iter->energy())/eeclus_iter->energy())-1. );
			  //if(e1!=0.)      ES_E1layer->Fill( PreshowerTools::gamma_*(PreshowerTools::calib_planeX_*e1) );
			  //if(e2!=0.)      ES_E2layer->Fill( PreshowerTools::gamma_*(PreshowerTools::calib_planeX_*e2) );
			  tempenergy = deltaE + eeclus_iter->energy();
			  //if(useEEContainmentCorrections_) tempenergy *= containmentCorrections_.getContainmentPointCorrectionsEE( tempenergy , (eeclus_iter->position()).eta() );
			  eseeclusters.push_back( CaloCluster( tempenergy, eeclus_iter->position(), CaloID(CaloID::DET_ECAL_ENDCAP),  eeclus_iter->hitsAndFractions(), CaloCluster::undefined, eeclus_iter->seed() ) );
			  Added_One=true;

			  double DZ2 = (preshowerclusterp2.z()-preshowerclusterp1.z() )/2.;
			  GlobalPoint posClu(preshowerclusterp1.x()*(1.+DZ2/preshowerclusterp1.z() ),preshowerclusterp2.y()*(1.-DZ2/preshowerclusterp2.z()),(preshowerclusterp1.z()+preshowerclusterp2.z() )/2. );

			  if( fabs(preshowerclusterp1.z())>30  && fabs(preshowerclusterp2.z())>30 )  posES.push_back(posClu);
			  else{                                      GlobalPoint posFak2(-999.,-999.,-999.); posES.push_back(posFak2); }           
			  //The perfect cluster
			  if( fabs(preshowerclusterp1.z())>30  && fabs(preshowerclusterp2.z())>30 ){
				math::XYZPoint posit(posClu.x(),posClu.y(),posClu.z());
				//float Etaw = ( (float)(posit.eta())/(pow(0.0016,2)) + (float)( eeclus_iter->position().eta())/(pow(0.0139,2)) ) / (1./pow(0.0016,2)+1./pow(0.0139,2));
				//float Phiw = ( (float)(posit.phi())/(pow(0.0018,2)) + (float)( eeclus_iter->position().phi())/(pow(0.0176,2)) ) / (1./pow(0.0018,2)+1./pow(0.0176,2));

				eseeclusters_tot.push_back( CaloCluster( tempenergy, posit, CaloID(CaloID::DET_ECAL_ENDCAP),  eeclus_iter->hitsAndFractions(), CaloCluster::undefined, eeclus_iter->seed() ) );
				s4s9_EE_tot.push_back(s4s9_EE[i]);
				Es_e1_tot.push_back(PreshowerTools::gamma_*(PreshowerTools::calib_planeX_*e1)); Es_e2_tot.push_back(PreshowerTools::gamma_*(PreshowerTools::calib_planeX_*e2));

			  }
		    }
		}
		if( !Added_One ){
		    eseeclusters.push_back( CaloCluster( -999., eeclus_iter->position(), CaloID(CaloID::DET_ECAL_ENDCAP),  eeclus_iter->hitsAndFractions(), CaloCluster::undefined, eeclus_iter->seed() ) );
		    GlobalPoint posClu(-999.,-999.,-999.);
		    posES.push_back(posClu);
		    Es_e1.push_back(-1.); Es_e2.push_back(-1.);
		    Added_One=false;
		}
	  }//end of the ES matching loop
	  //Check size
	  if( eseeclusters.size()!=Es_e1.size() || posES.size()!=clustersEE.size() || eseeclusters.size()!=clustersEE.size()) cout<<"WARNING EE"<<Es_e1.size()<<"  "<<Es_e2.size()<<"<-check  ok->"<<eseeclusters.size()<<"  "<<clustersEE.size()<<endl;
	  if( s4s9_EE_tot.size()!=eseeclusters_tot.size()) cout<<"WARNING ES"<<s4s9_EE_tot.size()<<"  "<<eseeclusters_tot.size()<<endl;

	  if(storeMCTruth_ && gamma1.IsGoodPi0 && clustersEE.size()>0) AssociateGammaES(clustersEE, eseeclusters, posES, Es_e1, Es_e2);

    }//EE_HLT

    std::vector< CaloCluster > Allclusters(clusters);
    nClu_EB = (int)clusters.size();
    nClu_EE = (int)clustersEE.size();
    std::vector< int > AllCristal(Ncristal_EB);
    std::vector< float > s4s9_all(s4s9_EB);
    std::vector< float > s1s9_all(s1s9_EB);
    std::vector< float > s2s9_all(s2s9_EB);

    if( clusters.size()!=Ncristal_EB.size() || clusters.size()!=s4s9_EB.size() || clusters.size()!=s1s9_EB.size() || clusters.size()!=s2s9_EB.size() )
	  cout<<"WARNING: -> EB Variables size. Clu: "<<clusters.size()<<" xtal: "<<Ncristal_EB.size()<<" S4: "<<s4s9_EB.size()<<" S1: "<<s1s9_EB.size()<<" S2: "<<s2s9_EB.size()<<endl;
    if( clustersEE.size()!=Ncristal_EE.size() || clustersEE.size()!=s4s9_EE.size() || clustersEE.size()!=s1s9_EE.size() || clustersEE.size()!=s2s9_EE.size() )
	  cout<<"WARNING: -> EE Variables size. Clu: "<<clustersEE.size()<<" xtal: "<<Ncristal_EE.size()<<" S4: "<<s4s9_EE.size()<<" S1: "<<s1s9_EE.size()<<" S2: "<<s2s9_EE.size()<<endl;

    for(unsigned int i=0; i<clustersEE.size(); i++){
	  Allclusters.push_back(clustersEE[i]);
	  AllCristal.push_back(Ncristal_EE[i]);
	  s4s9_all.push_back( s4s9_EE[i] ); s1s9_all.push_back( s4s9_EE[i] ); s2s9_all.push_back( s4s9_EE[i] );
    }


    if( Allclusters.size()!=AllCristal.size() || Allclusters.size()!=s4s9_all.size() || Allclusters.size()!=s1s9_all.size() || Allclusters.size()!=s2s9_all.size() )
	  cout<<"WARNING: -> ALL Variables size. Clu: "<<Allclusters.size()<<" xtal: "<<AllCristal.size()<<" S4: "<<s4s9_all.size()<<" S1: "<<s1s9_all.size()<<" S2: "<<s2s9_all.size()<<endl;

    if(storeMCTruth_ && gamma1.IsGoodPi0) AssociateGamma(Allclusters, AllCristal, s4s9_all, s1s9_all, s2s9_all);

    //No needs to go on if you need just MVA
    bool Continue_withCombinatory(true);
#ifdef TTREEMVA
    Continue_withCombinatory = false;
#endif 

    if(!OnlyContCorr_ && Continue_withCombinatory){

	  std::map<size_t,size_t> savedCluEE;

	  std::vector< CaloCluster > clustersEE_ES(clustersEE);
	  if(useES_){
		clustersEE_ES.clear();
		clustersEE_ES = eseeclusters_tot;
		s4s9_EE.clear();
		s4s9_EE = s4s9_EE_tot;
		Es_e1.clear(); Es_e2.clear();
		Es_e1 = Es_e1_tot; Es_e2 = Es_e2_tot;
	  }

	  // loop over clusters to make Pi0
	  for(size_t i=0; i< clustersEE_ES.size(); ++i) {

		const CaloCluster* g1 = &(clustersEE_ES[i]);

		// track association
		math::XYZPoint impact1(999.,999.,999.);

		// 2nd loop over clusters
		for(size_t j=i+1; j<clustersEE_ES.size(); ++j) {

		    if(nPi0>= NPI0MAX || nClu >= NCLUMAX) {
			  cout << "No more space in the arrays: nPi0: " << nPi0<<endl;
			  continue;
		    }

		    const CaloCluster* g2 = &(clustersEE_ES[j]);           
		    // using the origin
		    math::PtEtaPhiMLorentzVector g1P4( g1->energy()/cosh(g1->eta()), g1->eta(), g1->phi(), 0. );
		    math::PtEtaPhiMLorentzVector g2P4( g2->energy()/cosh(g2->eta()), g2->eta(), g2->phi(), 0. );
		    math::PtEtaPhiMLorentzVector pi0P4 = g1P4 + g2P4;

		    // use PV 
		    TVector3 tmpV( g1->x(), g1->y(), g1->z());
		    math::PtEtaPhiMLorentzVector g1P4PV( g1->energy()/cosh(tmpV.Eta()), 
				tmpV.Eta(), tmpV.Phi(), 0. );

		    tmpV = TVector3( g2->x(), g2->y(), g2->z());
		    math::PtEtaPhiMLorentzVector g2P4PV( g2->energy()/cosh(tmpV.Eta()), 
				tmpV.Eta(), tmpV.Phi(), 0. );
		    math::PtEtaPhiMLorentzVector pi0P4PV = g1P4PV + g2P4PV;

		    // basic selection to reduce combinatorics
		    if(pi0P4PV.pt() < ptpi0Cut_) continue;
		    if(g1P4.eta()==g2P4.eta() && g1P4.phi()==g2P4.phi()) continue; 

		    //		    fillPi0Tree( pi0P4PV, savedCluEE,
		    //				g1P4PV, g2P4PV,
		    //				shapesEE,
		    //				g1, g2, nClu, i, j, Ncristal_EE, EtSeed_EE);

		    //new cut
		    float nextClu = 999., Drtmp = 999.;
		    for(size_t ind=0; ind<clustersEE_ES.size(); ++ind){
			  const CaloCluster* Gtmp = &(clustersEE_ES[ind]);
			  double deltaR1 = DR(Gtmp->phi(),g1P4.phi(),Gtmp->eta(),g1P4.eta());
			  double deltaR2 = DR(Gtmp->phi(),g2P4.phi(),Gtmp->eta(),g2P4.eta());
			  if( ind!=i && ind!=j && (deltaR1<Drtmp || deltaR2<Drtmp ) ){
				nextClu = min(deltaR1,deltaR2);
				Drtmp = nextClu;
			  }
		    }
		    if( clustersEE_ES.size()<3 ) nextClu=999.;
		    STr2_IsoPi0_rec[nPi0] = nextClu;
		    if( g1->energy()>g2->energy() ){
			  STr2_n1CrisPi0_rec[nPi0] = Ncristal_EE[i];
			  STr2_n2CrisPi0_rec[nPi0] = Ncristal_EE[j];
		    }
		    else{
			  STr2_n1CrisPi0_rec[nPi0] = Ncristal_EE[j];
			  STr2_n2CrisPi0_rec[nPi0] = Ncristal_EE[i];
		    }
		    STr2_mPi0_rec[nPi0] = pi0P4.mass();
		    STr2_ptG1_rec[nPi0] = g1P4.pt();
		    STr2_ptG2_rec[nPi0] = g2P4.pt();
		    STr2_S4S9_1[nPi0] = s4s9_EE[i];
		    STr2_S4S9_2[nPi0] = s4s9_EE[j];
		    STr2_etaPi0_rec[nPi0] = pi0P4.Eta();
		    STr2_ptPi0_rec[nPi0] = pi0P4.Pt();
		    STr2_Pi0recIsEB[nPi0] = 2;
		    STr2_DeltaRG1G2[nPi0] = DR(g1P4PV.phi(),g2P4PV.phi(),g1P4PV.eta(),g2P4PV.eta() );
		    STr2_Es_e1_1[nPi0] = Es_e1[i];
		    STr2_Es_e1_2[nPi0] = Es_e2[i];
		    STr2_Es_e2_1[nPi0] = Es_e1[j];
		    STr2_Es_e2_2[nPi0] = Es_e2[j];  

		    //Pi0_M_Eta->Fill(fabs(pi0P4.Eta()),pi0P4.mass());
		    nPi0++; nPi0_EE++;
		    TLorentzVector thispar; thispar.SetPtEtaPhiE(pi0P4.pt(),pi0P4.eta(),pi0P4.phi(),pi0P4.energy());
		    MyEEParicles.push_back(thispar);
		} // loop over clusters (g2)

	  } // loop over clusters to make pi0 

	  STr2_NPi0_rec = nPi0;
	  //Association and resolution:
	  if(storeMCTruth_){
		if(MyMCParicles.size()>=2) cout<<"WARNING: You have more than 1 MC particle generated!!!! You have:"<<MyMCParicles.size()<<"Particles"<<endl;
		//EB
		float deltaR_tmp =1.;
		bool assoc = false;
		//int n_tmp = -1;
		for(unsigned i =0; i<MyEBParicles.size(); i++){
		    double deltaR = DR(MyEBParicles[i].Phi(),MyMCParicles[0].Phi(),MyEBParicles[i].Eta(),MyMCParicles[0].Eta()); 
		    if(deltaR<deltaR_tmp){
			  deltaR_tmp = deltaR; /*n_tmp = i;*/ assoc = true;
		    }
		}
		if(assoc){
		    //EBdeltaR->Fill(deltaR_tmp);
		    //EBRisoPi0_Eta->Fill( MyEBParicles[n_tmp].Eta()-MyMCParicles[0].Eta() );
		    //EBRisoPi0_Phi->Fill( MyEBParicles[n_tmp].Phi()-MyMCParicles[0].Phi() );
		    //EBRisoPi0_Pt->Fill( (MyEBParicles[n_tmp].Pt()-MyMCParicles[0].Pt())/MyMCParicles[0].Pt() );
		    //EBRisoPi0_E->Fill( (MyEBParicles[n_tmp].E()-MyMCParicles[0].E())/MyMCParicles[0].E() );
		}
		//EE
		deltaR_tmp =1.;        assoc = false;        /*n_tmp = -1;*/
		for(unsigned i =0; i<MyEEParicles.size(); i++){
		    double deltaR =  DR(MyEEParicles[i].Phi(),MyMCParicles[0].Phi(),MyEEParicles[i].Eta(),MyMCParicles[0].Eta());
		    if(deltaR<deltaR_tmp){
			  deltaR_tmp = deltaR; /*n_tmp = i;*/ assoc = true;
		    }
		}
		if(assoc){
		    //EEdeltaR->Fill(deltaR_tmp);
		    //EERisoPi0_Eta->Fill( MyEEParicles[n_tmp].Eta()-MyMCParicles[0].Eta() );
		    //EERisoPi0_Phi->Fill( MyEEParicles[n_tmp].Phi()-MyMCParicles[0].Phi() );
		    //EERisoPi0_Pt->Fill( (MyEEParicles[n_tmp].Pt()-MyMCParicles[0].Pt())/MyMCParicles[0].Pt() );
		    //EERisoPi0_E->Fill( (MyEEParicles[n_tmp].E()-MyMCParicles[0].E())/MyMCParicles[0].E() );
		}      
		//Fill pro histo;
		if( gamma1.IsGoodPi0 && MyMCParicles.size()!=0 ){
		    G1G2_tot->Fill( MyMCParicles[0].Eta() );
		    if( gamma1.IsConverted && gamma2.IsConverted ) G1G2_unc->Fill( MyMCParicles[0].Eta() );
		    if( gamma1.IsConverted ) G1_unc->Fill( MyMCParicles[0].Eta()  );
		    if( gamma2.IsConverted ) G2_unc->Fill( MyMCParicles[0].Eta()  );            
		}

	  }//if_storeMCTruth

	  //m_tree->Fill();
	  m_tree_opt->Fill();
    } //if(!OnlyContCorr_ & Continue_withCombinatory)
    delete estopology_;
}


//========================================================================================
template <class DetIdType, class RecHitCollectionType, class IteratorType> 
void NewPi0Dumper_Gun::make3x3Clusters(
	  const CaloGeometry* geometry, const RecHitCollectionType* ebHandle,
	  std::vector<CaloCluster>* clusters,
	  std::vector< ClusterShape >* shapes,
	  edm::Timestamp const & iTime, std::vector<int>* Ncristal, std::vector<float>* S4S9, std::vector<float>* S1S9, std::vector<float>* S2S9, std::vector<float>* EtrSeed )
{

    std::vector<EcalRecHit> seeds;
    seeds.clear();

    vector<DetId> usedXtals;
    usedXtals.clear();

    typedef std::map< DetId , bool > XtalInUse;
    XtalInUse isUsed; // map of which xtals have been used

    std::vector<DetId> detIdEBRecHits;
    std::vector<EcalRecHit> EBRecHits;

    // sort by energy and find the seeds
    for(IteratorType itb= ebHandle->begin(); itb != ebHandle->end(); ++itb) {
	  if(itb->energy() > 0.) {
		int idXtal= itb->id();
		float posTotalEnergy(itb->energy());
		float T0 = PCparams_.param_T0_barl_;
		float maxDepth = PCparams_.param_X0_ * ( T0 + log( posTotalEnergy ) );
		float maxToFront = geom->getPosition(idXtal).mag(); // to front face
		float depth = maxDepth + maxToFront - geom->getPosition(idXtal).mag() ;
		GlobalPoint posThis = geom->getPosition(idXtal,depth);            
		DetIdType EBoEE(itb->id());
		GlobalPoint posiz = geometry->getPosition( itb->id() );
		//if( EBoEE.subdet() == EcalBarrel ){
		//  EB_GeomDeltaEta->Fill(posThis.eta()-posiz.eta());
		//  EB_GeomDeltaPhi->Fill(posThis.phi()-posiz.phi());
		//}
		//if( EBoEE.subdet() == EcalEndcap ){
		//  EE_GeomDeltaEta->Fill(posThis.eta()-posiz.eta());
		//  EE_GeomDeltaPhi->Fill(posThis.phi()-posiz.phi());
		//}
		float EtSeeds = DoOffGeom_ ? itb->energy()/cosh(posiz.eta()) : itb->energy()/cosh(posThis.eta());
		if( EBoEE.subdet() == EcalBarrel )     { if(itb->energy() > s1CluCut_ )         seeds.push_back( *itb ); }
		else if( EBoEE.subdet() == EcalEndcap) { if(EtSeeds > s1CluCutEE_)        seeds.push_back( *itb ); }
		else cout<<"WARNING: cristal not in Barrel or in Endcap"<<endl;
	  }
    } // loop over xtals
    sort(seeds.begin(), seeds.end(), ecalRecHitLess());

    // loop over seeds and make clusters
    for (std::vector<EcalRecHit>::iterator itseed=seeds.begin();
		itseed!=seeds.end(); itseed++) {

	  DetId seed_id( itseed->id() );
	  DetIdType  seed_id_subdet(seed_id);

	  // check if seed already in use. If so go to next seed
	  std::map< DetId , bool >::const_iterator mapit = isUsed.find( seed_id );
	  if( mapit != isUsed.end() ) continue; // seed already in use

	  // find 3x3 matrix of xtals
	  int clusEtaSize_(3), clusPhiSize_(3);
	  std::vector<DetId> clus_v;

	  if( seed_id_subdet.subdet() == EcalBarrel ) 
		clus_v = ebTopology->getWindow(seed_id,clusEtaSize_,clusPhiSize_);       
	  else if( seed_id_subdet.subdet() == EcalEndcap ) 
		clus_v = eeTopology->getWindow(seed_id,clusEtaSize_,clusPhiSize_);       

	  // needed for position calculator
	  std::vector<std::pair<DetId,float> > clus_used;

	  // xtals actually used after removing those already used
	  vector<const EcalRecHit*> RecHitsInWindow; // 3x3 around seed. no sharing w/ other clusters. only unique xtals
	  vector<const EcalRecHit*> RecHitsInWindow3x3All; // 3x3 around seed. includes xtals from other clusters

	  float simple_energy = 0; 
	  float posTotalEnergy(0.); // need for position calculation

	  // make 3x3  cluster - reject overlaps
	  for (std::vector<DetId>::const_iterator det=clus_v.begin(); det!=clus_v.end(); det++) {
		DetIdType thisId( *det );

		// find the rec hit
		IteratorType ixtal = ebHandle->find( thisId );
		if( ixtal == ebHandle->end() ) continue; // xtal not found

		RecHitsInWindow3x3All.push_back( &(*ixtal) );

		// skip this xtal if already used
		XtalInUse::const_iterator mapit = isUsed.find( thisId );
		if( mapit != isUsed.end() ) continue; // xtal already used

		RecHitsInWindow.push_back( &(*ixtal) );
		clus_used.push_back(std::make_pair(*det,1.));
		simple_energy +=  ixtal->energy();
		if(ixtal->energy()>0.) posTotalEnergy += ixtal->energy(); // use only pos energy for position
	  } // loop over xtals in the region

	  if(simple_energy <= 0) { 
		cout << "skipping cluster with negative energy " << simple_energy << endl; 
		continue;
	  }

	  float s4s9_tmp[4];
	  for(int i=0;i<4;i++){ 
		s4s9_tmp[i]= 0;
	  }

	  //        DetIdType  seed_id_subdet(seed_id);
	  int seed_ieta, seed_iphi;

	  if( seed_id_subdet.subdet() == EcalEndcap ) {
		seed_ieta = EEDetId(seed_id).ix();
		seed_iphi = EEDetId(seed_id).iy();

	  } else if( seed_id_subdet.subdet() == EcalBarrel ) {
		seed_ieta = EBDetId(seed_id).ieta();
		seed_iphi = EBDetId(seed_id).iphi();
		convxtalid( seed_iphi,seed_ieta);
	  }

	  // not sure works also for EE
#ifdef INDEXETA65
	  if( fabs(EBDetId(seed_id).ieta())>63 && fabs(EBDetId(seed_id).ieta())<67 )
		cout<<"iETA: "<<fabs(EBDetId(seed_id).ieta())<<" iPHI: "<<EBDetId(seed_id).iphi()<<" Index: "<<EBDetId(seed_id).hashedIndex()<<endl;
#endif
	  // energy of 3x3 cluster
	  float e3x3(0.);
	  int ncry9(0);
	  std::vector<std::pair<DetId,float> > enFracs;

	  // variables for position caculation
	  float xclu(0.), yclu(0.), zclu(0.); // temp var to compute weighted average
	  float trClu(0.), alphaClu(0.), laserCorrClu(0.);
	  //float trCluInvertZSide(0.);
	  float total_weight(0.);// to compute position
	  float total_TrWeight(0.);// to compute average transparency correction


	  // Calculate shower depth
	  float T0 = PCparams_.param_T0_barl_;
	  float maxDepth = PCparams_.param_X0_ * ( T0 + log( posTotalEnergy ) );
	  float maxToFront = geom->getPosition(seed_id).mag(); // to front face

	  double EnergyCristals[9] = {0.};
	  // loop over xtals and compute energy and position

	  for(unsigned int j=0; j<RecHitsInWindow.size();j++){

		DetIdType det(RecHitsInWindow[j]->id());

		int ieta, iphi;

		if( seed_id_subdet.subdet() == EcalEndcap ) {
		    ieta = EEDetId(det).ix();
		    iphi = EEDetId(det).iy();

		} else if( seed_id_subdet.subdet() == EcalBarrel ) {
		    ieta = EBDetId(det).ieta();
		    iphi = EBDetId(det).iphi();
		    convxtalid(iphi,ieta);
		}
		else cout<<"WARNING: cristal not in Barrel or in Endcap"<<endl;

		// use calibration coeff for energy and position
		float en = RecHitsInWindow[j]->energy();
		int dx = diff_neta_s(seed_ieta,ieta);
		int dy = diff_nphi_s(seed_iphi,iphi);
		EnergyCristals[j] = en;

		if(abs(dx)<=1 && abs(dy)<=1) {
		    e3x3 += en;
		    ncry9++;
		    if(dx <= 0 && dy <=0){ s4s9_tmp[0] += en; }
		    if(dx >= 0 && dy <=0){ s4s9_tmp[1] += en; }
		    if(dx <= 0 && dy >=0){ s4s9_tmp[2] += en; }
		    if(dx >= 0 && dy >=0){ s4s9_tmp[3] += en; }
		    enFracs.push_back( std::make_pair( RecHitsInWindow[j]->id(), en ) );
		    // NOTA BENE: sto usando le frazioni per salvare energia rechit
		    isUsed[ RecHitsInWindow[j]->id() ] = true;
		}

		// compute position
		if(en>0.) {
		    float weight = std::max( float(0.), float(PCparams_.param_W0_ + log(en/posTotalEnergy)) );

		    float depth = maxDepth + maxToFront - geom->getPosition(det).mag() ;
		    GlobalPoint posThis = DoOffGeom_ ? geometry->getPosition( det ) : geom->getPosition(det,depth);
		    //GlobalPoint posThis = geom->getPosition(det,depth);

		    xclu += weight*posThis.x(); 
		    yclu += weight*posThis.y(); 
		    zclu += weight*posThis.z(); 
		    total_weight += weight;
		}

	  } // loop over 3x3 rechits

	  float e2x2 = *max_element( s4s9_tmp,s4s9_tmp+4);
	  float s4s9 = e2x2/e3x3;
	  math::XYZPoint clusPos( xclu/total_weight, 
		    yclu/total_weight,
		    zclu/total_weight ); 

	  if(s4s9<s4s9CluCut_) continue;

	  //calculate e5x5 and fill energy fractions for 5x5 area - 3x3  already done
	  float e5x5 = 0;
	  int ncry25 = 0;
	  vector<const EcalRecHit*> RecHitsInWindow5x5; // 5x5 around seed. includes xtals from others
	  std::vector<DetId> clus_v5x5;
	  if( seed_id_subdet.subdet() == EcalBarrel ) 
		clus_v5x5 = ebTopology->getWindow(seed_id,5,5);       
	  else if( seed_id_subdet.subdet() == EcalEndcap ) 
		clus_v5x5 = eeTopology->getWindow(seed_id,5,5);       

	  for( std::vector<DetId>::const_iterator idItr = clus_v5x5.begin(); idItr != clus_v5x5.end(); idItr++){
		DetIdType det = *idItr;

		//inside collections
		IteratorType itdet = ebHandle->find(det);
		if(itdet == ebHandle->end()) continue;

		RecHitsInWindow5x5.push_back( &(*itdet) );
		e5x5 += itdet->energy();
		ncry25++;

		// check whether hit in 3x3 window - if not fraction = 0
		vector<const EcalRecHit*>::const_iterator in3x3 = find( RecHitsInWindow.begin(), RecHitsInWindow.end(), &(*itdet) ); 
		if( in3x3 == RecHitsInWindow.end() ) {
		    enFracs.push_back(std::make_pair(det,0.));
		}
	  }


	  vector<const EcalRecHit*> RecHitsInWindow7x7; // 7x7 around seed. includes xtals from others
	  std::vector<DetId> clus_v7x7;
	  if( seed_id_subdet.subdet() == EcalBarrel ) 
		clus_v7x7 = ebTopology->getWindow(seed_id,7,7);       
	  else if( seed_id_subdet.subdet() == EcalEndcap ) 
		clus_v7x7 = eeTopology->getWindow(seed_id,7,7);       

	  for( std::vector<DetId>::const_iterator idItr = clus_v7x7.begin(); idItr != clus_v7x7.end(); idItr++){
		DetIdType det = *idItr;

		//inside collections
		IteratorType itdet = ebHandle->find(det);
		if(itdet == ebHandle->end()) continue;
		RecHitsInWindow7x7.push_back( &(*itdet) );
	  }

	  // cluster shape
	  ClusterShape shape;
	  shape.s9 = e3x3;
	  shape.ncry9 = ncry9;
	  shape.s4 = e2x2;
	  shape.s4s9 = s4s9;
	  shape.s25 = e5x5;
	  shape.ncry25 = ncry25;
	  shape.s1 = itseed->energy();
	  shape.time = itseed->time();
	  shape.flag = itseed->recoFlag();
	  shape.transparencyLoss = float(trClu)/float(total_TrWeight);
	  shape.laserCorr = float(laserCorrClu)/float(total_TrWeight);
	  shape.alpha = float(alphaClu)/float(total_TrWeight);
	  //shape.transparencyLossInvertZSide = float(trCluInvertZSide)/float(total_TrWeight);

	  /// by now 2nd moments are implemented only for EB
	  if( seed_id_subdet.subdet() == EcalBarrel ) 
	  {
		// compute major and minor moments
		Cluster2ndMoments mom3x3 = EcalClusterTools::cluster2ndMoments( RecHitsInWindow3x3All );
		Cluster2ndMoments mom5x5 = EcalClusterTools::cluster2ndMoments( RecHitsInWindow5x5    );
		Cluster2ndMoments mom7x7 = EcalClusterTools::cluster2ndMoments( RecHitsInWindow7x7    );

		shape.sMaj9  = mom3x3.sMaj;
		shape.sMaj25 = mom5x5.sMaj;
		shape.sMaj49 = mom7x7.sMaj;
		shape.sMin9  = mom3x3.sMin;
		shape.sMin25 = mom5x5.sMin;
		shape.sMin49 = mom7x7.sMin;
	  }
	  else if( seed_id_subdet.subdet() == EcalEndcap )
	  {
		shape.sMaj9  = -999.999;
		shape.sMaj25 = -999.999;
		shape.sMaj49 = -999.999;
		shape.sMin9  = -999.999;
		shape.sMin25 = -999.999;
		shape.sMin49 = -999.999;
	  }

	  // compute pt of gamma and cut
	  float ptClus = e3x3/cosh(clusPos.eta());

	  if(ptClus<ptCluCut_) continue;

	  // energy corrections in bins of eta and energy
	  //if(!noCorrections_) e3x3 *= energyCorrection(e3x3,clusPos.eta());

	  // make calo clusters
	  Ncristal->push_back( RecHitsInWindow.size() ); //for the Branch
	  S4S9->push_back( s4s9 ); //for the Branch
	  S1S9->push_back( itseed->energy()/e3x3 ); //for the Branch
	  int IndMax=-1;
	  double maxEne = max_array( EnergyCristals, 9 );
	  for(int i=0; i<9; i++){ if(EnergyCristals[i]==maxEne) IndMax = i; }
	  for(int i=0; i<9; i++){ if(i == IndMax) EnergyCristals[i]=0.; }
	  double maxEne2 = max_array( EnergyCristals, 9);
	  S2S9->push_back( (maxEne+maxEne2)/e3x3 ); //for the Branch
	  clusters->push_back( CaloCluster( e3x3, clusPos, CaloID(CaloID::DET_ECAL_BARREL),
			  enFracs, CaloCluster::undefined, seed_id ) );
	  shapes->push_back( shape );

	  //recompute position just for Et
	  GlobalPoint posi;
	  if(itseed->energy() > 0.) {
		int idXtal= itseed->id();
		float posTotalEnergy(itseed->energy());
		float T0 = PCparams_.param_T0_barl_;
		float maxDepth = PCparams_.param_X0_ * ( T0 + log( posTotalEnergy ) );
		float maxToFront = geom->getPosition(idXtal).mag(); // to front face
		float depth = maxDepth + maxToFront - geom->getPosition(idXtal).mag() ;
		posi = DoOffGeom_ ? geometry->getPosition( itseed->id() ) : geom->getPosition(idXtal,depth);
	  }
	  EtrSeed->push_back( itseed->energy()/cosh(posi.eta())  ); //for the Branch

    } //loop over seeds to make clusters
}

// Associating Gamma
void NewPi0Dumper_Gun::AssociateGamma(std::vector<CaloCluster> clusters,  std::vector< int > AllCristal, std::vector< float > s4s9_all, std::vector< float > s1s9_all, std::vector< float > s2s9_all )
{
    Ntot++;
    if( gamma1.IsEB && gamma2.IsEB ) Ntot_EB++;

    TLorentzVector G1, G2;
    bool assoc=false;
    double deltaR_tmp = 0.05;
    int n_tmp = -1;
    for(unsigned int i=0; i<clusters.size(); i++){
	  const CaloCluster g1 = clusters[i];
	  double deltaR = DR(g1.phi(),gamma1.gamma.Phi(),g1.eta(),gamma1.gamma.Eta());
	  if(deltaR<deltaR_tmp){
		deltaR_tmp = deltaR; n_tmp = i; assoc = true;
	  }
    }
    if(assoc){
	  const CaloCluster g1 = clusters[n_tmp];
	  if( (g1.seed().subdetId()==1) ) N1rec_EB++;
	  G1.SetPtEtaPhiE( g1.energy()/cosh(g1.eta()) ,g1.eta(),g1.phi(),g1.energy());
	  STr_RecG1_E = g1.energy(); STr_RecG1_Eta = g1.eta(); STr_RecG1_Phi = g1.phi();
	  STr_RecG1_DR = deltaR_tmp;
	  STr_RecG1_NCris = AllCristal[n_tmp];
	  if( !gamma1.IsConverted && !gamma2.IsConverted ){ 
		if( gamma1.IsEB ){ //EBRisoGammaUnc_E->Fill( (gamma1.gamma.E()-g1.energy() )/gamma1.gamma.E() );
		    //EBRisoGammaUnc_Eta->Fill( gamma1.gamma.Eta()-g1.eta() );
		    //EBRisoGammaUnc_Phi->Fill( gamma1.gamma.Phi()-g1.phi() );
		    //EBRisoGammaUnc_DR->Fill( deltaR_tmp );
		}
		else    { //EERisoGammaUnc_E->Fill( (gamma1.gamma.E()-g1.energy() )/gamma1.gamma.E() );
		    //EERisoGammaUnc_Eta->Fill( gamma1.gamma.Eta()-g1.eta() );
		    //EERisoGammaUnc_Phi->Fill( gamma1.gamma.Phi()-g1.phi() );
		    //EERisoGammaUnc_DR->Fill( deltaR_tmp ); 
		}
	  }
	  if(!gamma2.IsConverted && !gamma1.IsConverted && (g1.seed().subdetId()==1) /*&& Nclus_ieta_EB.size()>0 && Nclus_ieta_EB.size()==clusters.size()*/ ){
		EBDetId iEta(g1.seed());
		//FillEBContCorr( g1.energy()/cosh(g1.eta()), iEta.ietaAbs(), g1.energy()/gamma1.gamma.E() );
		if(iEta.ieta()>0) FillEBContCorr_PHI7Bin( true,  g1.energy()/cosh(g1.eta()), iEta.iphi(), (g1.energy()*containmentCorrections_.getContainmentCorrectionsEB(g1.energy(), iEta.ietaAbs()))/gamma1.gamma.E() );
		else              FillEBContCorr_PHI7Bin( false, g1.energy()/cosh(g1.eta()), iEta.iphi(), (g1.energy()*containmentCorrections_.getContainmentCorrectionsEB(g1.energy(), iEta.ietaAbs()))/gamma1.gamma.E() );
	  }
	  if(!gamma2.IsConverted && !gamma1.IsConverted && (g1.seed().subdetId()==2) /*&& Nclus_id_EE.size()>0 && Nclus_id_EE.size()==clusters.size()*/ ){
		//int Nindex = EndcapTools::getRingIndex( g1.seed() );
		//FillEEContCorr( g1.energy()/cosh(g1.eta()) , Nindex, g1.energy()/gamma1.gamma.E());
	  }
    }
#ifdef CHECKIETACORR
    //Prova
    cout<<"Filling TH2 for Cont Correction in iEta "<<endl;
    float en = 0.;
    for(int i=0; i<12; i++){
	  if(i==0) en=0.5; if(i==1) en=0.8; if(i==2) en=1.05;
	  if(i==3) en=1.15; if(i==4) en=1.25; if(i==5) en=1.4;
	  if(i==6) en=1.7; if(i==7) en=2.3; if(i==8) en=2.7;
	  if(i==9) en=3.3; if(i==10) en=3.7; if(i==11) en=7.;
	  for(int j=0; j<85; j++)   h2_EtaCorr->SetBinContent(j+1,i+1, containmentCorrections_.getContainmentCorrectionsEB(en, j+1));
    }
#endif

    bool assoc2=false;
    deltaR_tmp = 0.05;
    int n_tmp2 = -1;
    if(assoc){
	  for(unsigned int i=0; i<clusters.size(); i++){
		if( (int)i!=n_tmp ){
		    const CaloCluster g2 = clusters[i];
		    double deltaR = DR(g2.phi(),gamma2.gamma.Phi(),g2.eta(),gamma2.gamma.Eta());
		    if(deltaR<deltaR_tmp ){
			  deltaR_tmp = deltaR; n_tmp2 = i; assoc2 = true;
		    }
		}
	  }
    }
    if(assoc2 && assoc){
	  const CaloCluster g1 = (clusters[n_tmp]);
	  const CaloCluster g2 = (clusters[n_tmp2]);
	  if( (g1.seed().subdetId()==1) && (g2.seed().subdetId()==1) ) N1_2rec_EB++;
	  G2.SetPtEtaPhiE( g2.energy()/cosh(g2.eta()) ,g2.eta(),g2.phi(),g2.energy() );
	  STr_RecG2_E = g2.energy(); STr_RecG2_Eta = g2.eta(); STr_RecG2_Phi = g2.phi();
	  STr_RecG2_DR = deltaR_tmp;
	  STr_RecG2_NCris = AllCristal[n_tmp2];
	  //Gammas_Dr_risE->Fill( gamma1.gamma.DeltaR(gamma2.gamma), (gamma2.gamma.E()-g2.energy() )/gamma2.gamma.E() );
	  if( !gamma2.IsConverted && !gamma1.IsConverted ){ 
		if( gamma2.IsEB ){
		    //EBRisoGammaUnc2_E->Fill( (gamma2.gamma.E()-g2.energy() )/gamma2.gamma.E() );
		    //EBRisoGammaUnc2_Eta->Fill( gamma2.gamma.Eta()-g2.eta() );
		    //EBRisoGammaUnc2_Phi->Fill( gamma2.gamma.Phi()-g2.phi() );
		    //EBRisoGammaUnc2_DR->Fill( deltaR_tmp );
		}
		else{
		    //EERisoGammaUnc2_E->Fill( (gamma2.gamma.E()-g2.energy() )/gamma2.gamma.E() );
		    //EERisoGammaUnc2_Eta->Fill( gamma2.gamma.Eta()-g2.eta() );
		    //EERisoGammaUnc2_Phi->Fill( gamma2.gamma.Phi()-g2.phi() );
		    //EERisoGammaUnc2_DR->Fill( deltaR_tmp );
		}
	  }
	  if(!gamma2.IsConverted && !gamma1.IsConverted && (g2.seed().subdetId()==1) /*&& Nclus_ieta_EB.size()>0 && Nclus_ieta_EB.size()==clusters.size()*/ ){
		EBDetId iEta(g2.seed());
		//FillEBContCorr( g2.energy()/cosh(g2.eta()) , iEta.ietaAbs(), g2.energy()/gamma2.gamma.E() );
		if(iEta.ieta()>0) FillEBContCorr_PHI7Bin(true,  g2.energy()/cosh(g2.eta()), iEta.iphi(), (g2.energy()*containmentCorrections_.getContainmentCorrectionsEB(g2.energy(), iEta.ietaAbs()))/gamma2.gamma.E() );
		else              FillEBContCorr_PHI7Bin(false, g2.energy()/cosh(g2.eta()), iEta.iphi(), (g2.energy()*containmentCorrections_.getContainmentCorrectionsEB(g2.energy(), iEta.ietaAbs()))/gamma2.gamma.E() );
	  }
	  if(!gamma2.IsConverted && !gamma1.IsConverted && (g2.seed().subdetId()==2) /*&& Nclus_id_EE.size()>0 && Nclus_id_EE.size()==clusters.size() */){
		//int Nindex = EndcapTools::getRingIndex( g2.seed() );
		//FillEEContCorr( g2.energy()/cosh(g2.eta()) , Nindex, g2.energy()/gamma2.gamma.E());
	  }
    }
    if( assoc && assoc2){
#ifdef TTREEMVA
	  int Ind1 = n_tmp, Ind2 = n_tmp2;
	  const CaloCluster g1 = clusters[Ind1];
	  const CaloCluster g2 = clusters[Ind2];
	  int n_tmp_tmp = -1, iEta_tmp = 0, iPhi_tmp = 0;
	  TLorentzVector G_Sort_1, G_Sort_2;
	  float e3x3MC_1 = -1, e3x3MC_2 = -1;
	  bool isConverted_1 = gamma1.IsConverted, isConverted_2 = gamma2.IsConverted; 

	  if( (g1.seed().subdetId()==1) && (g2.seed().subdetId()==1) ){
		EBDetId  id_1(g1.seed()); int iEta1 = id_1.ieta(); int iPhi1 = id_1.iphi();
		EBDetId  id_2(g2.seed()); int iEta2 = id_2.ieta(); int iPhi2 = id_2.iphi();
		if( g1.energy()/cosh(g1.eta()) > g2.energy()/cosh(g2.eta()) ){
		    G_Sort_1.SetPtEtaPhiE( g1.energy()/cosh(g1.eta()) ,g1.eta(),g1.phi(),g1.energy() );
		    G_Sort_2.SetPtEtaPhiE( g2.energy()/cosh(g2.eta()) ,g2.eta(),g2.phi(),g2.energy() );
		    e3x3MC_1 = gamma1.gamma.E();
		    e3x3MC_2 = gamma2.gamma.E();
		}
		else{
		    G_Sort_1.SetPtEtaPhiE( g2.energy()/cosh(g2.eta()) ,g2.eta(),g2.phi(),g2.energy() );
		    G_Sort_2.SetPtEtaPhiE( g1.energy()/cosh(g1.eta()) ,g1.eta(),g1.phi(),g1.energy() );
		    e3x3MC_1 = gamma2.gamma.E();
		    e3x3MC_2 = gamma1.gamma.E();
		    n_tmp_tmp = Ind1; Ind1 = Ind2;   Ind2 = n_tmp_tmp;
		    iEta_tmp = iEta1; iEta1 = iEta2; iEta2 = iEta_tmp;
		    iPhi_tmp = iPhi1; iPhi1 = iPhi2; iPhi2 = iPhi_tmp;
		    isConverted_1 = gamma2.IsConverted; isConverted_2 = gamma1.IsConverted;
		}
		Nfinal_EB++;
		// Old
		//MVA_Mass     = (G_Sort_1+G_Sort_2).M();
		//MVA_Mass_MC  = 0.135;
		//MVA_E3x3_1   = G_Sort_1.E();
		//MVA_E3x3_2   = G_Sort_2.E();
		//MVA_Pt_1     = G_Sort_1.Pt();
		//MVA_Pt_2     = G_Sort_2.Pt();
		//MVA_Eta_1    = iEta1;
		//MVA_Eta_2    = iEta2;
		//MVA_Phi_1    = iPhi1;
		//MVA_Phi_2    = iPhi2;
		//MVA_Nxtal_1  = AllCristal[Ind1];
		//MVA_Nxtal_2  = AllCristal[Ind2];
		//MVA_S4S9_1   = s4s9_all[Ind1];
		//MVA_S4S9_2   = s4s9_all[Ind2];

		MVA_E3x3_1      = G_Sort_1.E();
		MVA_E3x3MC_1    = e3x3MC_1;
		MVA_E3x3_2      = G_Sort_2.E();
		MVA_E3x3MC_2    = e3x3MC_2;
		MVA_Pt_1        = G_Sort_1.Pt();
		MVA_Pt_2        = G_Sort_2.Pt();
		MVA_Nxtal_1     = AllCristal[Ind1];
		MVA_Nxtal_2     = AllCristal[Ind2];
		MVA_S4S9_1      = s4s9_all[Ind1];
		MVA_S4S9_2      = s4s9_all[Ind2];
		MVA_S1S9_1      = s1s9_all[Ind1];
		MVA_S1S9_2      = s1s9_all[Ind2];
		MVA_S2S9_1      = s2s9_all[Ind1];
		MVA_S2S9_2      = s2s9_all[Ind2];
		MVA_Eta_1       = iEta1;
		MVA_Eta_2       = iEta2;
		MVA_Phi_1       = iPhi1;
		MVA_Phi_2       = iPhi2;
		MVA_Eta_1on5    = iEta1%5;
		MVA_Eta_2on5    = iEta2%5;
		MVA_Phi_1on2    = iPhi1%2;
		MVA_Phi_2on2    = iPhi2%2;
		MVA_Eta_1on2520 = (TMath::Abs(iEta1)<=25)*(iEta1%25) + (TMath::Abs(iEta1)>25)*((iEta1-25*TMath::Abs(iEta1)/iEta1)%20); //Distance in xtal from module boundaries
		MVA_Eta_2on2520 = (TMath::Abs(iEta2)<=25)*(iEta2%25) + (TMath::Abs(iEta2)>25)*((iEta2-25*TMath::Abs(iEta2)/iEta2)%20);
		MVA_Phi_1on20   = iPhi1%20;
		MVA_Phi_2on20   = iPhi2%20;
		MVA_nEta_1      = G_Sort_1.Eta();
		MVA_nEta_2      = G_Sort_2.Eta();
		MVA_nPhi_1      = G_Sort_1.Phi();
		MVA_nPhi_2      = G_Sort_2.Phi();
		MVA_isConv_1    = isConverted_1;
		MVA_isConv_2    = isConverted_2;
		m_Mva->Fill();

		// Together gamma1 and 2
		MVA_E3x3_t      = G_Sort_1.E();
		MVA_E3x3MC_t    = e3x3MC_1;
		MVA_Pt_t        = G_Sort_1.Pt();
		MVA_Nxtal_t     = AllCristal[Ind1];
		MVA_S4S9_t      = s4s9_all[Ind1];
		MVA_S1S9_t      = s1s9_all[Ind1];
		MVA_S2S9_t      = s2s9_all[Ind1];
		MVA_Eta_t       = iEta1;
		MVA_Phi_t       = iPhi1;
		MVA_Eta_ton5    = iEta1%5;
		MVA_Phi_ton2    = iPhi1%2;
		MVA_Eta_ton2520 = (TMath::Abs(iEta1)<=25)*(iEta1%25) + (TMath::Abs(iEta1)>25)*((iEta1-25*TMath::Abs(iEta1)/iEta1)%20);
		MVA_Phi_ton20   = iPhi1%20;
		m_Mva_tot->Fill();
		MVA_E3x3_t      = G_Sort_2.E();
		MVA_E3x3MC_t    = e3x3MC_2;
		MVA_Pt_t        = G_Sort_2.Pt();
		MVA_Nxtal_t     = AllCristal[Ind2];
		MVA_S4S9_t      = s4s9_all[Ind2];
		MVA_S1S9_t      = s1s9_all[Ind2];
		MVA_S2S9_t      = s2s9_all[Ind2];
		MVA_Eta_t       = iEta2;
		MVA_Phi_t       = iPhi2;
		MVA_Eta_ton5    = iEta2%5;
		MVA_Phi_ton2    = iPhi2%2;
		MVA_Eta_ton2520 = (TMath::Abs(iEta2)<=25)*(iEta2%25) + (TMath::Abs(iEta2)>25)*((iEta2-25*TMath::Abs(iEta2)/iEta2)%20);
		MVA_Phi_ton20   = iPhi2%20;
		m_Mva_tot->Fill();

	  }
#endif
	  STr_NCristG1 = AllCristal[n_tmp]; STr_NCristG2 = AllCristal[n_tmp2];
	  if( G1.E()<G2.E()  ) Cluster_NCrist_DRgamma->Fill( AllCristal[n_tmp], gamma2.gamma.DeltaR(gamma1.gamma) );
	  else                 Cluster_NCrist_DRgamma->Fill( AllCristal[n_tmp2], gamma2.gamma.DeltaR(gamma1.gamma) );
	  STr_RecPi0_M = (G1+G2).M(); 
	  STr_RecPi0_Eta = (G1+G2).Eta(); 
	  //Pi0_assoc_M_Eta->Fill((G1+G2).Eta(),(G1+G2).M());
	  if( gamma1.IsEB ){
		//if( !gamma1.IsConverted && !gamma2.IsConverted ) EBmPioUnc->Fill( (G1+G2).M() );
		//if( gamma1.IsConverted && !gamma2.IsConverted )  EBmPioUncOnlyOne->Fill( (G1+G2).M() );
		//if( !gamma1.IsConverted && gamma2.IsConverted )  EBmPioUncOnlyOne->Fill( (G1+G2).M() );
		//if( gamma1.IsConverted && gamma2.IsConverted )   EBmPioNonClu->Fill( (G1+G2).M() );
	  }
	  else{
		//if( !gamma1.IsConverted && !gamma2.IsConverted ) EEmPioUnc->Fill( (G1+G2).M() );
		//if( gamma1.IsConverted && !gamma2.IsConverted )  EEmPioUncOnlyOne->Fill( (G1+G2).M() );
		//if( !gamma1.IsConverted && gamma2.IsConverted )  EEmPioUncOnlyOne->Fill( (G1+G2).M() );
		//if( gamma1.IsConverted && gamma2.IsConverted )   EEmPioNonClu->Fill( (G1+G2).M() );
	  }
    } 
}

void NewPi0Dumper_Gun::FillEBContCorr(double gPt, int giEta, double gRatio ){

    int ien=0;
    double PtBinBoundEB[PTBINSEB];
    PtBinBoundEB[0]=0.; PtBinBoundEB[1]=0.9; PtBinBoundEB[2]=1.5; PtBinBoundEB[3]=2.1; PtBinBoundEB[4]=3.; PtBinBoundEB[5]=5.; PtBinBoundEB[6]=8.;

    for(ien=0; ien < PTBINSEB; ++ien) {
	  if(gPt <= PtBinBoundEB[ien+1]) break;
    }
    if(ien==0)       ContCorrEB_1[giEta]->Fill( gRatio );
    else if(ien==1)  ContCorrEB_2[giEta]->Fill( gRatio );
    else if(ien==2)  ContCorrEB_3[giEta]->Fill( gRatio );
    else if(ien==3)  ContCorrEB_4[giEta]->Fill( gRatio );
    else if(ien==4)  ContCorrEB_5[giEta]->Fill( gRatio );
    else if(ien==5)  ContCorrEB_6[giEta]->Fill( gRatio );
    else             ContCorrEB_7[giEta]->Fill( gRatio );

}

void NewPi0Dumper_Gun::FillEBContCorr_PHI7Bin(bool isEBp, double gPt, int giPhi, double gRatio ){

    int giPhi_20 = giPhi%20;
    int ien=0;
    double PtBinBoundEB[PTBINSEB];
    PtBinBoundEB[0]=0.; PtBinBoundEB[1]=0.9; PtBinBoundEB[2]=1.5; PtBinBoundEB[3]=2.1; PtBinBoundEB[4]=3.; PtBinBoundEB[5]=5.; PtBinBoundEB[6]=8.;

    for(ien=0; ien < PTBINSEB; ++ien) {
	  if(gPt <= PtBinBoundEB[ien+1]) break;
    }
    if(ien==7) ien=6;
    if(giPhi_20==0) giPhi_20=20;

    int nBin = 20*ien+giPhi_20;
    if(isEBp) ContCorrEB_PHI_7PTBin_p[nBin-1]->Fill( gRatio );
    else      ContCorrEB_PHI_7PTBin_m[nBin-1]->Fill( gRatio );

    int nBin_tot = N_iPHI*ien+giPhi;
    if(isEBp) ContCorrEB_PHI_7PTBin_360iPHI_p[nBin_tot-1]->Fill( gRatio );
    else      ContCorrEB_PHI_7PTBin_360iPHI_m[nBin_tot-1]->Fill( gRatio );
}

void NewPi0Dumper_Gun::FillEEContCorr(double gPt, int EtaRing, double gRatio ){
    //cout<<EtaRing<<"  "<<gPt<<"  "<<gRatio<<endl;
    int ien=0;
    double PtBinBoundEE[PTBINSEE];
    PtBinBoundEE[0]=0.; PtBinBoundEE[1]=2.5; PtBinBoundEE[2]=5.; PtBinBoundEE[3]=8.; PtBinBoundEE[4]=10.; //PtBinBoundEE[5]=10.; PtBinBoundEE[6]=12.;

    for(ien=0; ien < PTBINSEE; ++ien) {
	  if(gPt <= PtBinBoundEE[ien+1]) break;
    }

    if(ien==0)       ContCorrEE_1[EtaRing]->Fill( gRatio );
    else if(ien==1)  ContCorrEE_2[EtaRing]->Fill( gRatio );
    else if(ien==2)  ContCorrEE_3[EtaRing]->Fill( gRatio );
    else if(ien==3)  ContCorrEE_4[EtaRing]->Fill( gRatio );
    else             ContCorrEE_5[EtaRing]->Fill( gRatio );
    //else if(ien==5)  ContCorrEE_6[EtaRing]->Fill( gRatio );
    //else             ContCorrEE_7[EtaRing]->Fill( gRatio );

}

TH1F** NewPi0Dumper_Gun::initializeContCorrHisto(const char *name, const char *title, int size )
{
    TH1F **h = new TH1F*[size];
    char name_c[100];
    char title_c[200];

    for(int jR=0; jR<size; jR++)
    {
	  sprintf(name_c, "%s%d", name, jR);
	  sprintf(title_c, "%s%d", title, jR);
	  h[jR] = new TH1F(name_c, title_c, 100,0.,2.);
	  h[jR]->GetXaxis()->SetTitle("E^{reco}/E^{gen}");
    }
    return h;
}

void NewPi0Dumper_Gun::deleteContCorrHisto(TH1F **h, int size)
{
    for(int jR=0; jR<size; jR++)
	  delete h[jR];

    delete h;
}

void NewPi0Dumper_Gun::AssociateGammaES(std::vector<CaloCluster> clustersEE, std::vector<CaloCluster> clustersES, std::vector<GlobalPoint> posES, std::vector<float> Es_e1, std::vector<float> Es_e2)
{

    STr_Es_nEE = clustersEE.size();
    int nES=0;
    for(unsigned int i=0; i<clustersES.size();i++){
	  if(clustersES[i].energy() > -1.) nES++;
    }
    STr_Es_nES = nES;

    if(  clustersEE.size() == clustersES.size() ){

	  //Associate EE
	  TLorentzVector G1,G1es, G2, G2es, G1posES, G2posES, G1posESw, G2posESw;
	  bool assoc=false;
	  double deltaR_tmp = 0.05;
	  int n_tmp = -1;
	  for(unsigned int i=0; i<clustersEE.size(); i++){
		const CaloCluster g1 = clustersEE[i];
		double deltaR = DR(g1.phi(),gamma1.gamma.Phi(),g1.eta(),gamma1.gamma.Eta());
		if(deltaR<deltaR_tmp){
		    deltaR_tmp = deltaR; n_tmp = i; assoc = true;
		}
	  }
	  if(assoc && clustersES[n_tmp].energy()>0.){
		const CaloCluster g1 = clustersEE[n_tmp];
		const CaloCluster g1es = clustersES[n_tmp];
		G1.SetPtEtaPhiE( g1.energy()/cosh(g1.eta()) ,g1.eta(),g1.phi(),g1.energy());
		G1es.SetPtEtaPhiE( g1es.energy()/cosh(g1.eta()) ,g1es.eta(),g1es.phi(),g1es.energy());
		STr_Es_RecG1_E = g1.energy(); STr_Es_RecG1_Eta = g1.eta(); STr_Es_RecG1_Phi = g1.phi();
		STr_Es_RecG1es_E = g1es.energy();
		STr_Es_e1_1 = Es_e1[n_tmp];
		STr_Es_e1_2 = Es_e2[n_tmp];
		if(posES[n_tmp].x()>-800){
		    G1posES.SetPtEtaPhiE( g1es.energy()/cosh(posES[n_tmp].eta()) , posES[n_tmp].eta(), posES[n_tmp].phi(),g1es.energy());
		    float Etaw = ( (float)(posES[n_tmp].eta())/(pow(0.0016,2)) + (float)(g1.eta())/(pow(0.0139,2)) ) / (1./pow(0.0016,2)+1./pow(0.0139,2));
		    float Phiw = ( (float)(posES[n_tmp].phi())/(pow(0.0018,2)) + (float)(g1.phi())/(pow(0.0176,2)) ) / (1./pow(0.0018,2)+1./pow(0.0176,2));
		    G1posESw.SetPtEtaPhiE( g1es.energy()/cosh(Etaw) , Etaw, Phiw, g1es.energy());
		    STr_Es_Clu1es_Eta1 = posES[n_tmp].eta();        STr_Es_Clu1es_Phi1 = posES[n_tmp].phi();  
		    STr_Es_Clu1es_x1 = posES[n_tmp].x();            STr_Es_Clu1es_y1 = posES[n_tmp].y();  STr_Es_Clu1es_z1 = posES[n_tmp].z();
		    ES_DEta_Eta->Fill( gamma1ES.gamma.Eta()-posES[n_tmp].eta(), gamma1ES.gamma.Eta() );
		    //ES_DEta_EtaMod->Fill( fabs(gamma1ES.gamma.Eta()-posES[n_tmp].eta()), gamma1ES.gamma.Eta() );
		    //ES_DEta_E->Fill( gamma1ES.gamma.Eta()-posES[n_tmp].eta(), gamma1ES.gamma.E() );
		    ES_DEta_Phi->Fill( gamma1ES.gamma.Eta()-posES[n_tmp].eta(), gamma1ES.gamma.Phi() );
		    ES_DPhi_Eta->Fill( gamma1ES.gamma.Phi()-posES[n_tmp].phi(), gamma1ES.gamma.Eta() );
		    //ES_DPhi_EtaMod->Fill( fabs(gamma1ES.gamma.Phi()-posES[n_tmp].phi()), gamma1ES.gamma.Eta() );
		    //ES_DPhi_E->Fill( gamma1ES.gamma.Phi()-posES[n_tmp].phi(), gamma1ES.gamma.E() );
		    //ES_DPhi_Phi->Fill( gamma1ES.gamma.Phi()-posES[n_tmp].phi(), gamma1ES.gamma.Phi() );
		}
	  }

	  bool assoc2=false;
	  deltaR_tmp = 0.05;
	  int n_tmp2 = -1;
	  if(assoc && clustersES[n_tmp].energy()>0.){
		for(unsigned int i=0; i<clustersEE.size(); i++){
		    if( (int)i!=n_tmp ){
			  const CaloCluster g2 = clustersEE[i];
			  double deltaR = DR(g2.phi(),gamma2.gamma.Phi(),g2.eta(),gamma2.gamma.Eta()); 
			  if(deltaR<deltaR_tmp ){
				deltaR_tmp = deltaR; n_tmp2 = i; assoc2 = true;
			  }
		    }
		}
	  }
	  if(assoc2 && clustersES[n_tmp2].energy()>0. ){
		const CaloCluster g2 = (clustersEE[n_tmp2]);
		const CaloCluster g2es = (clustersES[n_tmp2]);
		G2.SetPtEtaPhiE( g2.energy()/cosh(g2.eta()) ,g2.eta(),g2.phi(),g2.energy());
		G2es.SetPtEtaPhiE( g2es.energy()/cosh(g2es.eta()) ,g2es.eta(),g2es.phi(),g2es.energy());
		STr_Es_RecG2_E = g2.energy(); STr_Es_RecG2_Eta = g2.eta(); STr_Es_RecG2_Phi = g2.phi();
		STr_Es_RecG2es_E = g2es.energy();
		STr_Es_e2_1 = Es_e1[n_tmp2];
		STr_Es_e2_2 = Es_e2[n_tmp2];
		if(posES[n_tmp2].x()>-800){
		    G2posES.SetPtEtaPhiE( g2es.energy()/cosh(posES[n_tmp2].eta()) , posES[n_tmp2].eta(), posES[n_tmp2].phi(),g2es.energy());
		    float Etaw = ( (float)(posES[n_tmp2].eta())/(pow(0.0016,2)) + (float)(g2.eta())/(pow(0.0139,2)) ) / (1./pow(0.0016,2)+1./pow(0.0139,2));
		    float Phiw = ( (float)(posES[n_tmp2].phi())/(pow(0.0018,2)) + (float)(g2.phi())/(pow(0.0176,2)) ) / (1./pow(0.0018,2)+1./pow(0.0176,2));
		    G2posESw.SetPtEtaPhiE( g2es.energy()/cosh(Etaw) , Etaw, Phiw,g2es.energy());
		    STr_Es_Clu2es_Eta1 = posES[n_tmp2].eta();    STr_Es_Clu2es_Phi1 = posES[n_tmp2].phi();
		    STr_Es_Clu2es_x1 = posES[n_tmp2].x();        STr_Es_Clu2es_y1 = posES[n_tmp2].y();  STr_Es_Clu2es_z1 = posES[n_tmp2].z();
		}
	  }
	  if( assoc && assoc2 && clustersES[n_tmp].energy()>0. && clustersES[n_tmp2].energy()>0.  ){
		STr_Es_RecPi0_M   = (G1+G2).M();         STr_Es_RecPi0_Eta   = (G1+G2).Eta(); 
		STr_Es_RecPi0es_M = (G1es+G2es).M();     STr_Es_RecPi0es_Eta = (G1es+G2es).Eta(); 
		if(posES[n_tmp].x()>-800 && posES[n_tmp2].x()>-800 && ( posES[n_tmp].eta() != posES[n_tmp2].eta() && posES[n_tmp].phi() != posES[n_tmp2].phi() ) ){
		    STr_Es_RecPi0esPos_M = (G1posES+G2posES).M();     STr_Es_RecPi0esPos_Eta = (G1posES+G2posES).Eta();
		    STr_Es_RecPi0esPos_Mw = (G1posESw+G2posESw).M();     STr_Es_RecPi0esPos_Etaw = (G1posESw+G2posESw).Eta();

		    //Containment corrections
		    //DetId id(15);
		    //cout<<EndcapTools::getRingIndex(id)<<endl;

		}
	  } 

    }// If EE ES same size
    else cout<<"WARNING: ES clusters != EE clusters"<<endl;
}


TVector3 NewPi0Dumper_Gun::ComputeDirection(bool isEB, TVector3 gamma, TVector3  pi0){

    float Norm = 0.;
    if(isEB)      Norm = (129. - sqrt( pow(pi0.X(),2)+pow(pi0.Y(),2) ) )/sqrt( pow(gamma.X(),2)+pow(gamma.Y(),2) );
    if(!isEB && gamma.Z() > 0.)     Norm = (330. - pi0.Z())/gamma.Z();
    if(!isEB && gamma.Z() < 0.)     Norm = (-330. - pi0.Z())/gamma.Z();

    TVector3 newGamma = gamma*Norm;
    return newGamma;

}

TVector3 NewPi0Dumper_Gun::ComputeESDirection(bool isEB, TVector3 gamma, TVector3  pi0){

    float Norm = 0.;
    if(isEB)      Norm = (129. - sqrt( pow(pi0.X(),2)+pow(pi0.Y(),2) ) )/sqrt( pow(gamma.X(),2)+pow(gamma.Y(),2) );
    if(!isEB && gamma.Z() > 0.)     Norm = (305.606 - pi0.Z())/gamma.Z();
    if(!isEB && gamma.Z() < 0.)     Norm = (-305.606 - pi0.Z())/gamma.Z();

    TVector3 newGamma = gamma*Norm;
    return newGamma;

}

bool
NewPi0Dumper_Gun::GetHLTResults(const edm::Event& iEvent, std::string s){

    edm::Handle<edm::TriggerResults> hltTriggerResultHandle;
    iEvent.getByLabel(triggerTag_, hltTriggerResultHandle);

    edm::TriggerNames HLTNames;

    HLTNames = iEvent.triggerNames(*hltTriggerResultHandle);
    std::string tempnames;
    int hltCount = hltTriggerResultHandle->size();
    TRegexp reg(TString( s.c_str()) );

    for (int i = 0 ; i != hltCount; ++i) {
	  TString hltName_tstr(HLTNames.triggerName(i));
	  //cout<<"Trigger: "<<hltName_tstr<<endl;
	  std::string hltName_str(HLTNames.triggerName(i));
	  if ( hltName_tstr.Contains(reg) ){
		//    cout<<hltTriggerResultHandle->accept(i)<<endl;
		return hltTriggerResultHandle->accept(i);
	  }
    }
    return false;
} // HLT isValid


/*
//--------------------------------------------------------------------------------------------
void NewPi0Dumper_Gun::FillTriggerInfo(const edm::Event& iEvent, const edm::EventSetup& iSetup) {
//--------------------------------------------------------------------------------------------

using namespace edm;
using namespace reco;

// trigger Handles
Handle< L1GlobalTriggerReadoutRecord > gtReadoutRecord;
iEvent.getByLabel( l1TriggerInput_, gtReadoutRecord);

ESHandle<L1GtTriggerMenu> menuRcd;
iSetup.get<L1GtTriggerMenuRcd>().get(menuRcd);

/// L1 trigger results for physics algorithms
//const L1GtTriggerMenu* menu = menuRcd.product();
const DecisionWord& gtDecisionWordBeforeMask = gtReadoutRecord->decisionWord();

isBSC = false;

nL1bits = int( gtDecisionWordBeforeMask.size() );

for (int iBit = 0; iBit < nL1bits; ++iBit)
L1bits[iBit] = gtDecisionWordBeforeMask[iBit] ;
/// L1 technical triggers
const TechnicalTriggerWord&  technicalTriggerWordBeforeMask = gtReadoutRecord->technicalTriggerWord();
nL1bitsTech = int(technicalTriggerWordBeforeMask.size());
for(int iBit = 0; iBit < nL1bitsTech; ++iBit) {
L1bitsTech[iBit] = technicalTriggerWordBeforeMask.at(iBit);
}

isBSC = L1bitsTech[0] && (L1bitsTech[40] || L1bitsTech[41]) 
&& ! (L1bitsTech[36] || L1bitsTech[37] || L1bitsTech[38] || L1bitsTech[39]) 
&& ! ((L1bitsTech[42] && ! L1bitsTech[43]) || (L1bitsTech[43] && ! L1bitsTech[42])) ;


} // end of FillTriggerInfo
 */

//--------------------------------------------------------------------------------------------
void NewPi0Dumper_Gun::FillMCInfo(const edm::Event& iEvent, const edm::EventSetup& iSetup) {
    //--------------------------------------------------------------------------------------------

    using namespace std;
    using namespace edm;
    using namespace reco;

    nSIM = nMC = 0;

    if(iEvent.isRealData()) { cout << "No MC truth in data! return" << endl; return; }

    // get MC info from GenParticleCandidates 
    Handle<GenParticleCollection> genParticles;
    iEvent.getByLabel("genParticles", genParticles);
    // get GEANT sim tracks and vertices (includes conversions)
    Handle<SimTrackContainer> simTracks_h;
    const SimTrackContainer* simTracks;
    iEvent.getByLabel("g4SimHits", simTracks_h);
    simTracks = (simTracks_h.isValid()) ? simTracks_h.product() : 0;

    Handle<SimVertexContainer> simVert_h;
    const SimVertexContainer* simVertices;
    iEvent.getByLabel("g4SimHits", simVert_h);
    simVertices = (simVert_h.isValid()) ? simVert_h.product() : 0;

    int current_particle = -1;
    set<int> mothers;
    map<const GenParticle*, int> mapMC;
    map<const GenParticle*, int>::iterator mapMC_it;

    int p_count(0);
    int motherIDMC_temp = -1;

    for (GenParticleCollection::const_iterator p = genParticles->begin(); p != genParticles->end(); ++p, ++p_count) 
    {
	  if( p->pdgId()!=111 ) cout<<"ID: "<<p->pdgId()<<endl;
	  if ( nMC >= (nMaxMC-1) ) continue;

	  // looking for mother particle
	  motherIDMC_temp = -1;
	  //where_is_pi0_mother = -1; // debug
	  if (p->numberOfMothers() > 0) 
	  {
		const Candidate * mom = p->mother();
		for (size_t j = 0; j != genParticles->size(); ++j) 
		{
		    const Candidate * ref = &((*genParticles)[j]);
		    if (mom==ref)
		    {
			  motherIDMC_temp = j; 
			  //if(mom->pdgId()==kPi0)//debug
			  //   where_is_pi0_mother = j; // debug
		    }
		}
	  } 

	  // Neutral particles kept with >100 MeV 
	  if ( p->status()==1  && p->pt()>0.100 )//|| (p->charge()!=0 && p->pt()>0.075)) ) 
	  {
		TLorentzVector thisMCpar; thisMCpar.SetPtEtaPhiE(p->pt(),p->eta(),p->phi(),p->energy());
		MyMCParicles.push_back(thisMCpar);
		pdgIdMC[nMC] = p->pdgId();
		statusMC[nMC] = p->status();
		ptMC[nMC] = p->pt();
		mMC[nMC] = p->mass();
		eMC[nMC] = p->energy();
		etaMC[nMC] = p->eta(); 
		phiMC[nMC] = p->phi(); 
		mapMC[&(*p)] = nMC;
		convertedMC[nMC] = false;
		motherIDMC[nMC] = -1; //((const GenParticle*)p->mother())->pdgId(); 
		motherIndexMC[nMC] = -1; //hic::check
		current_particle = nMC;
		++nMC; 

		// if stable photon/electron, find parent
		if (p->status() == 1 && motherIDMC_temp != -1 && (p->pdgId() == kPhoton || fabs(p->pdgId()) == kElectron ) ) //|| p->pdgId() == 221)) // 221=eta0 
		{
		    cout<<" if stable photon/electron, find parent "<<endl;
		    const GenParticle *mom = (const GenParticle*)p->mother();

		    // saving the mother pdgId 
		    motherIDMC[current_particle] = mom->pdgId();

		    if ( mom->status() == 2 &&  (mom->pdgId()<81 || mom->pdgId()>100)) // avoid to store partons and MC internal
		    {
			  // if the mother particle is found for the first time
			  if(mothers.find(motherIDMC_temp) == mothers.end())
			  {
				mothers.insert(motherIDMC_temp);
				if (nMC>=nMaxMC) continue;
				pdgIdMC[nMC] = mom->pdgId();
				statusMC[nMC] = mom->status();
				ptMC[nMC] = mom->pt();
				mMC[nMC] = mom->mass();
				eMC[nMC] = mom->energy();
				etaMC[nMC] = mom->eta();
				phiMC[nMC] = mom->phi(); 
				mapMC[mom] = nMC;
				//motherIndexMC[nMC-1] = nMC;
				++nMC;
			  }
			  //else
			  //{
			  //motherIndexMC[nMC-1] = mapMC.find(mom)->second;
			  //}
		    }

		    mapMC_it =  mapMC.find(mom);
		    if(mapMC_it != mapMC.end())
			  motherIndexMC[current_particle] = mapMC_it->second;
		    //cout << "   my_pi0::" << motherIndexMC[current_particle] << endl;
		} // stable particle has parents 
	  } // particle selection
    } // loop over particles

    //----- Figure out the particle decays in tracker volume  ------

    // Vertices only return trackID of their parent SimTrack
    // Figure out the mapping from trackID to SimTrack
    map<unsigned int, const SimTrack*> trackMap;
    for (SimTrackContainer::const_iterator iSim = simTracks->begin(); iSim != simTracks->end(); ++iSim) 
    {

	  if (!iSim->noVertex()) 
	  {
		assert(trackMap.find(iSim->trackId())==trackMap.end());
		trackMap[iSim->trackId()] = &(*iSim);
	  }
    }

    // Find all SimTracks that come from decays before the ECAL
    // and find their parent SimTracks
    map<const SimTrack*, const SimTrack*> promptParent; // daughter->mother
    map<const SimTrack*, set<const SimTrack*> > promptDecays; // m->ds
    map<const SimTrack*, const SimVertex*> promptVertex; // daughter->vertex
    map<const SimTrack*, const SimVertex*> promptALLVertex; // daughter->vertex in Any Occasion
    map<const SimTrack*, const SimTrack*> promptALLParent; // daughter->mother in Any Occasion

    //cout<<"EV. COMPLETO:"<<endl;
    bool isValid=false;
    int num=0;
    for (SimTrackContainer::const_iterator iSim = simTracks->begin(); iSim != simTracks->end(); ++iSim, num++) 
    {
	  if (!iSim->noVertex()) 
	  {
		// Find the parent vertex and see if it classifies as an early decay
		// Exclude the primary vertex (noParent)
		SimVertex const& vtx = (*simVertices)[iSim->vertIndex()];
		if (!vtx.noParent() && vtx.position().Rho() < 129 && fabs(vtx.position().z()) < 304) 
		{
		    // Find parent SimParticle that produced this vertex
		    // vtx->parentIndex is NOT a vector index :( so use trackMap
		    assert(trackMap.find(vtx.parentIndex())!=trackMap.end());
		    const SimTrack* p = trackMap[vtx.parentIndex()];
		    promptParent[&(*iSim)] = p; // nel Pi0Gun: ->genpartIndex() e' -1
		    promptDecays[p].insert(&(*iSim));
		    promptVertex[&(*iSim)] = &vtx;
		} // early decay
		if (!vtx.noParent() ){
		    isValid = true;
		    promptALLVertex[&(*iSim)] = &vtx;
		    const SimTrack* p = trackMap[vtx.parentIndex()];
		    promptALLParent[&(*iSim)] = p; 
		    // cout<<num<<" PDG: "<<iSim->type()<<" id: "<<iSim->trackId()<<" Son of: "<<p->type()<<" id: "<<p->trackId()
		    // <<" x vtx:" <<vtx.position().x()<<" Z Vtx: "<<vtx.position().z()<<"Px "<<iSim->momentum().x()<<" py "<<iSim->momentum().y()<<" pz "<<iSim->momentum().z()<<
		    // "pt "<<sqrt(pow(iSim->momentum().x(),2)+pow(iSim->momentum().y(),2)+pow(iSim->momentum().z(),2))<<endl;
		}
	  } // has vertex
    } // for simTracks

    //cout<<"Event:"<<endl;
    //Store Pi0 & gamma
    int nP0=0,  nGamma1=0, nGamma2=0;
    unsigned int IdGamma1=0, IdGamma2=0;
    TVector3 pi0_pos, ga1, ga2;
    num=0;
    float OneEle=0., TwoEle=0., TheGamma=0.;
    for (SimTrackContainer::const_iterator iSim = simTracks->begin(); iSim != simTracks->end(); ++iSim, num++){
	  if (!iSim->noVertex() ){
		SimVertex const& vtx = (*simVertices)[iSim->vertIndex()];
		if( !vtx.noParent() )
		{
		    //cout<<"Type: "<<iSim->type()<<" parents "<<promptALLParent[&(*iSim)]->type()<<endl;
		    if( iSim->type()==11  && promptALLParent[&(*iSim)]->type()==111 && num<5 )  OneEle++;
		    if( iSim->type()==-11 && promptALLParent[&(*iSim)]->type()==111 && num<5 )  TwoEle++;
		    if( iSim->type()==22  && promptALLParent[&(*iSim)]->type()==111 && num<5 )  TheGamma++;

		    if( iSim->type()==22 && promptALLParent[&(*iSim)]->type()==111 && num==1){
			  pi0_pos.SetXYZ(promptALLVertex[&(*iSim)]->position().x(),promptALLVertex[&(*iSim)]->position().y(),promptALLVertex[&(*iSim)]->position().z());
			  ConversionPi0_rho[nP0] = promptALLVertex[&(*iSim)]->position().Rho(); ConversionPi0_z[nP0] = promptALLVertex[&(*iSim)]->position().z();
			  ga1.SetXYZ(iSim->momentum().x(),iSim->momentum().y(),iSim->momentum().z());
			  IdGamma1 = iSim->trackId();
		    }
		    if( iSim->type()==22 && promptALLParent[&(*iSim)]->type()==111 && num==2){
			  ga2.SetXYZ(iSim->momentum().x(),iSim->momentum().y(),iSim->momentum().z());
			  STr_pi0_x = pi0_pos.X(); STr_pi0_z = pi0_pos.Z(); STr_pi0_z = pi0_pos.Z(); STr_pi0_eta = pi0_pos.Eta(); STr_pi0_phi = pi0_pos.Phi();
			  IdGamma2 = iSim->trackId();
			  nP0++;  
		    }
		    if( iSim->type()==11 && promptALLParent[&(*iSim)]->type()==22 && (promptALLParent[&(*iSim)]->trackId()==IdGamma1 || promptALLParent[&(*iSim)]->trackId()==IdGamma2 ) ){
			  SimVertex const& vtxgamma = (*simVertices)[ promptALLParent[&(*iSim)]->vertIndex() ];
			  if( !vtxgamma.noParent() && promptALLParent[ promptALLParent[&(*iSim)] ]->type()==111 ){           
				if(promptALLParent[&(*iSim)]->trackId()==IdGamma1){       
				    ConversionG1_x[nGamma1] = promptALLVertex[&(*iSim)]->position().x();
				    ConversionG1_y[nGamma1] = promptALLVertex[&(*iSim)]->position().y();
				    ConversionG1_rho[nGamma1] = promptALLVertex[&(*iSim)]->position().Rho();
				    ConversionG1_z[nGamma1] = promptALLVertex[&(*iSim)]->position().z();
				    nGamma1++;
				}
				if(promptALLParent[&(*iSim)]->trackId()==IdGamma2){ 
				    ConversionG2_x[nGamma2] = promptALLVertex[&(*iSim)]->position().x();
				    ConversionG2_y[nGamma2] = promptALLVertex[&(*iSim)]->position().y();
				    ConversionG2_rho[nGamma2] = promptALLVertex[&(*iSim)]->position().Rho();
				    ConversionG2_z[nGamma2] = promptALLVertex[&(*iSim)]->position().z();
				    nGamma2++;
				}
			  }
		    }
		}
	  }
    }

    if( OneEle==1 && TwoEle==1 && TheGamma>0 ){eeg++;}
    if( OneEle==2 && TwoEle==2){ eeee++;}
    if( TheGamma==0 ){ cout<<"No Gamma from Pi0"<<endl;}
    Tot_Ev++;
    //Fill for unconverted
    if(!isValid) cout<<"SimTrack not valid"<<endl;
    gamma1.IsConverted = true; gamma2.IsConverted = true;
    gamma1ES.IsConverted = true; gamma2ES.IsConverted = true;
    for(int i=0; i<nP0; i++){
	  if(isValid && nGamma1==0){
		ConversionG1_x[i] = 999.;
		ConversionG1_y[i] = 999.;
		ConversionG1_rho[i] = 999.;
		ConversionG2_z[i] = 999.;
		gamma1.IsConverted = false;
		gamma1ES.IsConverted = false;
	  }
	  if( isValid && nGamma2==0){
		ConversionG2_x[i] = 999.;
		ConversionG2_y[i] = 999.;
		ConversionG2_rho[i] = 999.;
		ConversionG2_z[i] = 999.;
		gamma2.IsConverted = false;
		gamma2ES.IsConverted = false;
	  }
    }
    if(nP0!=0 ){
	  gamma1.IsGoodPi0 = true; gamma2.IsGoodPi0 = true;
	  gamma1.gamma.SetPxPyPzE( ga1.X() , ga1.Y(), ga1.Z(),sqrt( pow(ga1.X(),2)+pow(ga1.Y(),2)+pow(ga1.Z(),2)) );
	  gamma2.gamma.SetPxPyPzE( ga2.X() , ga2.Y(), ga2.Z(),sqrt( pow(ga2.X(),2)+pow(ga2.Y(),2)+pow(ga2.Z(),2)) );
	  //cout<<gamma1.gamma.Eta()-gamma2.gamma.Eta()<<gamma1.gamma.Phi()-gamma2.gamma.Phi()<<endl;
	  STr_Sim_Dr = gamma1.gamma.DeltaR(gamma2.gamma);
	  //Gammas_Dr_E->Fill(STr_Sim_Dr, (gamma1.gamma+gamma2.gamma).E() );
	  gamma1.IsEB = (fabs(gamma1.gamma.Eta())<1.479); gamma2.IsEB = (fabs(gamma2.gamma.Eta())<1.479);
	  gamma1ES.IsEB = (fabs(gamma1.gamma.Eta())<1.479); gamma2ES.IsEB = (fabs(gamma2.gamma.Eta())<1.479);
	  gamma1.pi0.SetXYZ( pi0_pos.X(), pi0_pos.Y(), pi0_pos.Z()); gamma2.pi0 = gamma1.pi0;
	  gamma1ES.pi0.SetXYZ( pi0_pos.X(), pi0_pos.Y(), pi0_pos.Z()); gamma2ES.pi0 = gamma1.pi0;
	  STr_G1Uncon = !gamma1.IsConverted; STr_G2Uncon = !gamma2.IsConverted;
	  if( gamma1.IsEB && gamma2.IsEB )   STr_Pi0IsEB = 1;
	  if( !gamma1.IsEB && !gamma2.IsEB ) STr_Pi0IsEB = 2;
	  if( (gamma1.IsEB && !gamma1.IsEB) ||  (!gamma1.IsEB && gamma1.IsEB) ) cout<<"Gamma in EE, gamma in EB"<<endl;
	  //----Correct Gamma---
	  TVector3 Gamma1From0; Gamma1From0.SetXYZ(gamma1.gamma.Px(), gamma1.gamma.Py(), gamma1.gamma.Pz() );
	  TVector3 Gamma2From0; Gamma2From0.SetXYZ(gamma2.gamma.Px(), gamma2.gamma.Py(), gamma2.gamma.Pz() );
	  TVector3 GammaCorr1; GammaCorr1 = ComputeDirection( gamma1.IsEB , Gamma1From0, gamma1.pi0);
	  TVector3 GammaCorr2; GammaCorr2 = ComputeDirection( gamma2.IsEB , Gamma2From0, gamma2.pi0);
	  GammaCorr1 = gamma1.pi0+GammaCorr1;
	  GammaCorr2 = gamma2.pi0+GammaCorr2;
	  gamma1.gamma.SetPtEtaPhiE( sqrt( pow(ga1.X(),2)+pow(ga1.Y(),2)+pow(ga1.Z(),2))/cosh(GammaCorr1.Eta()), GammaCorr1.Eta(), GammaCorr1.Phi(), sqrt( pow(ga1.X(),2)+pow(ga1.Y(),2)+pow(ga1.Z(),2)) );
	  gamma2.gamma.SetPtEtaPhiE( sqrt( pow(ga2.X(),2)+pow(ga2.Y(),2)+pow(ga2.Z(),2))/cosh(GammaCorr2.Eta()), GammaCorr2.Eta(), GammaCorr2.Phi(), sqrt( pow(ga2.X(),2)+pow(ga2.Y(),2)+pow(ga2.Z(),2)) );
	  STr_SimG1_Eta = gamma1.gamma.Eta(); STr_SimG1_Phi = gamma1.gamma.Phi(); STr_SimG1_E = gamma1.gamma.E();
	  STr_SimG2_Eta = gamma2.gamma.Eta(); STr_SimG2_Phi = gamma2.gamma.Phi(); STr_SimG2_E = gamma2.gamma.E();
	  STr_SimG1_X = GammaCorr1.X(); STr_SimG1_Y = GammaCorr1.Y(); STr_SimG1_Z = GammaCorr1.Z();
	  STr_SimG2_X = GammaCorr2.X(); STr_SimG2_Y = GammaCorr2.Y(); STr_SimG2_Z = GammaCorr2.Z();
	  STr_ptPi0 = (gamma1.gamma+gamma2.gamma).Pt();
	  STr_MPi0 = (gamma1.gamma+gamma2.gamma).M();

	  TVector3 GammaCorr1ES; GammaCorr1ES = ComputeESDirection( gamma1.IsEB , Gamma1From0, gamma1.pi0);
	  TVector3 GammaCorr2ES; GammaCorr2ES = ComputeESDirection( gamma2.IsEB , Gamma2From0, gamma2.pi0);
	  GammaCorr1ES = gamma1.pi0+GammaCorr1ES;
	  GammaCorr2ES = gamma2.pi0+GammaCorr2ES;
	  gamma1ES.gamma.SetPtEtaPhiE( sqrt( pow(ga1.X(),2)+pow(ga1.Y(),2)+pow(ga1.Z(),2))/cosh(GammaCorr1ES.Eta()), GammaCorr1ES.Eta(), GammaCorr1ES.Phi(), sqrt( pow(ga1.X(),2)+pow(ga1.Y(),2)+pow(ga1.Z(),2)) );
	  gamma2ES.gamma.SetPtEtaPhiE( sqrt( pow(ga2.X(),2)+pow(ga2.Y(),2)+pow(ga2.Z(),2))/cosh(GammaCorr2ES.Eta()), GammaCorr2ES.Eta(), GammaCorr2ES.Phi(), sqrt( pow(ga2.X(),2)+pow(ga2.Y(),2)+pow(ga2.Z(),2)) );
	  STr_ESimG1_Eta = GammaCorr1ES.Eta(); STr_ESimG1_Phi = GammaCorr1ES.Phi(); STr_ESimG1_E = gamma1ES.gamma.E();
	  STr_ESimG2_Eta = GammaCorr2ES.Eta(); STr_ESimG2_Phi = GammaCorr2ES.Phi(); STr_ESimG2_E = gamma2ES.gamma.E();
	  STr_ESimG1_X = GammaCorr1ES.X(); STr_ESimG1_Y = GammaCorr1ES.Y(); STr_ESimG1_Z = GammaCorr1ES.Z();
	  STr_ESimG2_X = GammaCorr2ES.X(); STr_ESimG2_Y = GammaCorr2ES.Y(); STr_ESimG2_Z = GammaCorr2ES.Z();

    }
    else{ 
	  gamma1.IsGoodPi0 = false; gamma2.IsGoodPi0 = false;
    }

    // Find grandparent SimTracks all the way up the chain
    map<const SimTrack*, const SimTrack*> chainParents;// g.daughter->grandma
    map<const SimTrack*, set<const SimTrack*> > chainDecays; // gm->gds

    for (map<const SimTrack*, const SimTrack*>::const_iterator iSim = promptParent.begin(); iSim != promptParent.end(); ++iSim) 
    {
	  // Check that the SimTrack has no daughters itself (=grandchild)
	  if (promptDecays.find(iSim->first)==promptDecays.end())
	  {
		// Find the first SimTrack in the parentage chain (=grandparent)
		const SimTrack *p = iSim->second;
		while (promptParent.find(p) != promptParent.end())
		    p = promptParent[p];
		chainParents[iSim->first] = p;  
		chainDecays[p].insert(iSim->first);
	  } // is grandchild
    } // for promptParent

    // Associate grandParents to GenParticles
    map<const GenParticle*, const SimTrack*> decayedSims;
    map<const SimTrack*, const GenParticle*> decayedGens;

    for (map<const SimTrack*, set<const SimTrack*> >::const_iterator iSim = chainDecays.begin(); iSim != chainDecays.end(); ++iSim) 
    {
	  if (iSim->first->noGenpart()) 
		continue;

	  // Make sure the decay chain wasn't already pruned out
	  if (promptDecays.find(iSim->first)!=promptDecays.end() && promptDecays[iSim->first].size()!=0) 
	  {
		// NB: genpartIndex offset by 1
		const GenParticle* iGen =
		    &(*genParticles)[iSim->first->genpartIndex()-1];
		assert(iGen->pdgId()==iSim->first->type());
		decayedSims[iGen] = iSim->first;
		decayedGens[iSim->first] = iGen;
	  }
    } // for chainParents 
    /*
    // Save the decay products of the long-lived particles
    for (map<const GenParticle*, const SimTrack*>::const_iterator iGen = decayedSims.begin(); iGen != decayedSims.end(); ++iGen) 
    {
    const GenParticle *p = iGen->first;
    if (p->pdgId()==310 || // K0s 
    p->pdgId()==3122 || // Lambda
    p->pdgId()==3322 || // Xi0 
    p->pdgId()==111 || // Pi0 
    p->pdgId()==221) // eta
    {
    bool saved = printChildren(decayedSims[p], promptDecays, promptVertex, 0, true, p->pdgId());
    if (saved && mapMC.find(p)!=mapMC.end()) 
    statusMC[mapMC[p]] *= -1;
    } // decay prod
    } // for iGen 
     */
    /// Save conversions 
    for (map<const GenParticle*, const SimTrack*>::const_iterator iGen = decayedSims.begin(); iGen != decayedSims.end(); ++iGen) 
    {
	  const GenParticle *p = iGen->first; //nel Pi0 Gun: SONO SOLO 111
	  /// if the photon comes from pi0 or eta
	  //if (p->pdgId()==22 && p->mother()->status()==2 && p->mother()->pdgId()==111) 

	  if (p->pdgId()==22 && (p->mother()->pdgId()==111 ||  // pi0 
			  p->mother()->pdgId()==221 ) ) // eta
	  {
		/// find the mother gen-particle index in the gen-particle vector
		mapMC_it =  mapMC.find(p);
		int mother_gen_index = -1;
		if(mapMC_it != mapMC.end())
		    mother_gen_index = mapMC_it->second;

		if(mother_gen_index > 0)
		    convertedMC[mother_gen_index] = true;
		// save the decay chain
		bool saved = printChildren(decayedSims[p], promptDecays,  promptVertex, 0, true, mother_gen_index);
		if (saved && mapMC.find(p)!=mapMC.end()) {
		    statusMC[mapMC[p]] *= -1;
		}
	  } // is primary photon
    } // for iGen 

} // end of FillMCInfo

// Method for iterative printing of decay chains
//------------------------------------------------------------------------------------
bool NewPi0Dumper_Gun::printChildren(const SimTrack* p, 
	  std::map<const SimTrack*, set<const SimTrack*> > const& ptokids,
	  std::map<const SimTrack*, const SimVertex*> const& ptovtx,
	  int level, bool save, int motherGenIndex) {
    //------------------------------------------------------------------------------------

    using namespace std;
    // Print parent
    bool hasvtx = (ptovtx.find(p) != ptovtx.end());

    bool hasKids = (ptokids.find(p) != ptokids.end());

    // Save only SIM tracks not already in GenParticle list
    bool saved = false;
    if (save && level > 0 && nSIM < nMaxSIM) {
	  pdgIdSIM[nSIM] = p->type();
	  statusSIM[nSIM] = (hasKids ? 2 : 1);
	  ptSIM[nSIM] = p->momentum().pt();
	  eSIM[nSIM] = p->momentum().energy();
	  etaSIM[nSIM] = p->momentum().eta();
	  phiSIM[nSIM] = p->momentum().phi();
	  motherGenIndexSIM[nSIM] = motherGenIndex;
	  if (hasvtx) {
		rSIM[nSIM] = ptovtx.find(p)->second->position().Rho();
		zSIM[nSIM] = ptovtx.find(p)->second->position().z();
	  }
	  else {
		rSIM[nSIM] = zSIM[nSIM] = 0.;
		//assert(hasvtx);
	  }

	  ++nSIM;
	  saved = true;
    }

    // Print children, if any
    if (hasKids) {

	  set<const SimTrack*> const& kids = ptokids.find(p)->second;
	  for (set<const SimTrack*>::const_iterator iKid = kids.begin();
		    iKid != kids.end(); ++iKid)
		saved |= printChildren(*iKid, ptokids, ptovtx, level+1, save, motherGenIndex);
    } // if kids

    return saved;
} // printChildren

void NewPi0Dumper_Gun::fillPi0Tree(
	  math::PtEtaPhiMLorentzVector &pi0P4PV,  std::map<size_t,size_t> &savedCluEB,
	  math::PtEtaPhiMLorentzVector &g1P4PV, math::PtEtaPhiMLorentzVector &g2P4PV,
	  std::vector< ClusterShape > &shapes,
	  const CaloCluster* g1, const CaloCluster* g2, int &nClu, int i, int j, vector<int> &Ncristal, vector<float>& EtSeeds)
{
    massPi0[nPi0] =  pi0P4PV.mass();
    ePi0[nPi0] =  pi0P4PV.energy();
    ptPi0[nPi0] =  pi0P4PV.pt();
    etaPi0[nPi0] =  pi0P4PV.eta();
    phiPi0[nPi0] =  pi0P4PV.phi();
    CristTot[nPi0] =  Ncristal[i]+Ncristal[j];
    DRClus[nPi0] =  DR(g1P4PV.phi(),g2P4PV.phi(),g1P4PV.eta(),g2P4PV.eta());

    // 1st daugher index
    std::map<size_t,size_t>::const_iterator ind = savedCluEB.find( i );
    if( ind == savedCluEB.end() ) {
	  savedCluEB[ i ]  = nClu;
	  S9Clu[nClu] = g1P4PV.energy();
	  nCris[nClu] = Ncristal[i];
	  EtSeed[nClu] = EtSeeds[i];
	  ptClu[nClu] =  g1P4PV.pt();
	  etaClu[nClu] = g1P4PV.eta();
	  phiClu[nClu] = g1P4PV.phi();
	  S1Clu[nClu] =  shapes[i].s1;
	  S4Clu[nClu] =  shapes[i].s4;
	  S25Clu[nClu] = shapes[i].s25;
	  timeClu[nClu] = shapes[i].time;
	  nCryClu[nClu] = shapes[i].ncry9;
	  flagClu[nClu] = shapes[i].flag;
	  sMaj9Clu[nClu]  = shapes[i].sMaj9;
	  sMaj25Clu[nClu] = shapes[i].sMaj25;
	  sMaj49Clu[nClu] = shapes[i].sMaj49;
	  sMin9Clu[nClu]  = shapes[i].sMin9;
	  sMin25Clu[nClu] = shapes[i].sMin25;
	  sMin49Clu[nClu] = shapes[i].sMin49;
	  transparencyLossClu[nClu] = shapes[i].transparencyLoss;
	  //transparencyLossCluInvertZSide[nClu] = shapes[i].transparencyLossInvertZSide;
	  laserCorrectionClu[nClu] = shapes[i].laserCorr;
	  laserAlphaClu[nClu] = shapes[i].alpha;

	  if( g1->seed().subdetId() == EcalBarrel ) 
	  {
		EBDetId sid( g1->seed() );
		ietaClu[nClu] = sid.ieta();
		iphiClu[nClu] = sid.iphi();
		iCryClu[nClu] = sid.ic();
		iSMClu[nClu] = sid.ism();
		imodClu[nClu] = sid.im();
		iTTClu[nClu] = sid.tower().iTT();
		iTTetaClu[nClu] = sid.tower_ieta();
		iTTphiClu[nClu] = sid.tower_iphi();
	  }
	  else if( g1->seed().subdetId() == EcalEndcap ) 
	  {  
		EEDetId sid( g1->seed() );
		ietaClu[nClu] = sid.ix();
		iphiClu[nClu] = sid.iy();
		iCryClu[nClu] = sid.ic();
		iSMClu[nClu] = sid.iquadrant();
		imodClu[nClu] = sid.isc();
		iTTClu[nClu] =    -999; //sid.tower().iTT();
		iTTetaClu[nClu] = -999; //sid.tower_ieta();
		iTTphiClu[nClu] = -999; //sid.tower_iphi();
	  }

	  nClu++;
    }

    // 2nd daugher index
    ind = savedCluEB.find( j );
    if( ind == savedCluEB.end() ) {
	  savedCluEB[ j ]  = nClu;
	  S9Clu[nClu] = g2P4PV.energy();
	  nCris[nClu] = Ncristal[j];
	  EtSeed[nClu] = EtSeeds[j]; 
	  ptClu[nClu] =  g2P4PV.pt();
	  etaClu[nClu] = g2P4PV.eta();
	  phiClu[nClu] = g2P4PV.phi();
	  S1Clu[nClu] =  shapes[j].s1;
	  S4Clu[nClu] =  shapes[j].s4;
	  S25Clu[nClu] = shapes[j].s25;
	  timeClu[nClu] = shapes[j].time;
	  nCryClu[nClu] = shapes[j].ncry9;
	  flagClu[nClu] = shapes[j].flag;
	  sMaj9Clu[nClu]  = shapes[j].sMaj9;
	  sMaj25Clu[nClu] = shapes[j].sMaj25;
	  sMaj49Clu[nClu] = shapes[j].sMaj49;
	  sMin9Clu[nClu]  = shapes[j].sMin9;
	  sMin25Clu[nClu] = shapes[j].sMin25;
	  sMin49Clu[nClu] = shapes[j].sMin49;
	  transparencyLossClu[nClu] = shapes[i].transparencyLoss;
	  //transparencyLossCluInvertZSide[nClu] = shapes[i].transparencyLossInvertZSide;
	  laserCorrectionClu[nClu] = shapes[j].laserCorr;
	  laserAlphaClu[nClu] = shapes[j].alpha;

	  if( g2->seed().subdetId() == EcalBarrel ) 
	  {
		EBDetId sid( g2->seed() );
		ietaClu[nClu] = sid.ieta();
		iphiClu[nClu] = sid.iphi();
		iCryClu[nClu] = sid.ic();
		iSMClu[nClu] = sid.ism();
		imodClu[nClu] = sid.im();
		iTTClu[nClu] = sid.tower().iTT();
		iTTetaClu[nClu] = sid.tower_ieta();
		iTTphiClu[nClu] = sid.tower_iphi();
	  }
	  else if( g2->seed().subdetId() == EcalEndcap ) 
	  {
		EEDetId sid( g2->seed() );
		ietaClu[nClu] = sid.ix();
		iphiClu[nClu] = sid.iy();
		iCryClu[nClu] = sid.ic();
		iSMClu[nClu] = sid.iquadrant();
		imodClu[nClu] = sid.isc();
		iTTClu[nClu] =    -999; //sid.tower().iTT();
		iTTetaClu[nClu] = -999; //sid.tower_ieta();
		iTTphiClu[nClu] = -999; //sid.tower_iphi();
	  }
	  /*
	     EBDetId sid( g2->seed() );
	     ietaClu[nClu] = sid.ieta();
	     iphiClu[nClu] = sid.iphi();
	     iCryClu[nClu] = sid.ic();
	     iSMClu[nClu] = sid.ism();
	     imodClu[nClu] = sid.im();
	     iTTClu[nClu] = sid.tower().iTT();
	     iTTetaClu[nClu] = sid.tower_ieta();
	     iTTphiClu[nClu] = sid.tower_iphi();
	   */
	  nClu++;
    }

    indexClu1Pi0[nPi0] = savedCluEB[i];
    indexClu2Pi0[nPi0] = savedCluEB[j];

    // 1st daughter always with higher energy
    if(g2P4PV.pt() > g1P4PV.pt()) {
	  indexClu1Pi0[nPi0] = savedCluEB[j];
	  indexClu2Pi0[nPi0] = savedCluEB[i];
    }
}

double NewPi0Dumper_Gun::DPhi(double phi1, double phi2)
{
    double deltaPhi = phi1 - phi2;
    if (deltaPhi > Geom::pi()) deltaPhi -= 2.*Geom::pi();
    if (deltaPhi < -Geom::pi()) deltaPhi += 2.*Geom::pi();

    return deltaPhi;
}
double NewPi0Dumper_Gun::DR( double phi1, double phi2, double eta1, double eta2)
{
    double deltaEta = eta1-eta2;
    double deltaPhi = DPhi(phi1,phi2);
    return std::sqrt(deltaEta*deltaEta+deltaPhi*deltaPhi);
}
double NewPi0Dumper_Gun::min( double a, double b)
{
    if( a<=b ) return a;
    else       return b;
}

void NewPi0Dumper_Gun::InitTreeVariable(){
    nClu_EB =0.; nClu_EE =0.;
    STr_pi0_x = -999.;
    STr_pi0_y = -999.;
    STr_pi0_z = -999.;
    STr_pi0_eta = -999.;
    STr_pi0_phi = -999.;
    STr_ptPi0   = -999.;
    STr_MPi0    = -999.;
    STr_Pi0IsEB = 0;
    STr_G1Uncon = false;
    STr_G2Uncon = false;
    STr_Sim_Dr = -999.;
    STr_RecG1_E = -999.;
    STr_RecG1_Eta = -999.;
    STr_RecG1_Phi = -999.;
    STr_RecG1_DR = -999.;
    STr_RecG2_NCris = -999.;
    STr_SimG1_E = -999.;
    STr_SimG1_Eta = -999.;
    STr_SimG1_Phi = -999.;
    STr_SimG1_X = -999.;
    STr_SimG1_Y = -999.;
    STr_SimG1_Z = -999.;
    STr_RecG2_E = -999.;
    STr_RecG2_Eta = -999.;
    STr_RecG2_Phi = -999.;
    STr_RecG2_DR = -999.;
    STr_RecG2_NCris = -999.;
    STr_SimG2_E = -999.;
    STr_SimG2_Eta = -999.;
    STr_SimG2_Phi = -999.;
    STr_SimG2_X = -999.;
    STr_SimG2_Y = -999.;
    STr_SimG2_Z = -999.;

    STr_ESimG1_E = -999.;
    STr_ESimG1_Eta = -999.;
    STr_ESimG1_Phi = -999.;
    STr_ESimG1_X = -999.;
    STr_ESimG1_Y = -999.;
    STr_ESimG1_Z = -999.;
    STr_ESimG2_E = -999.;
    STr_ESimG2_Eta = -999.;
    STr_ESimG2_Phi = -999.;
    STr_ESimG2_X = -999.;
    STr_ESimG2_Y = -999.;
    STr_ESimG2_Z = -999.;

    STr_NCristG1 = -999.;
    STr_NCristG2 = -999.;
    STr_RecPi0_M = -999.;
    STr_RecPi0_Eta = -999.;
    STr2_NPi0_rec = 0;
    for(int i=0; i< NPI0MAX; i++) STr2_Es_e1_1[i] = -999.;
    for(int i=0; i< NPI0MAX; i++) STr2_Es_e1_2[i] = -999.;
    for(int i=0; i< NPI0MAX; i++) STr2_Es_e2_1[i] = -999.;
    for(int i=0; i< NPI0MAX; i++) STr2_Es_e2_2[i] = -999.;
    for(int i=0; i< NPI0MAX; i++) STr2_IsoPi0_rec[i] = 999.;
    for(int i=0; i< NPI0MAX; i++) STr2_n1CrisPi0_rec[i] = 0;
    for(int i=0; i< NPI0MAX; i++) STr2_n2CrisPi0_rec[i] = 0;
    for(int i=0; i< NPI0MAX; i++) STr2_Pi0recIsEB[i] = 0;
    for(int i=0; i< NPI0MAX; i++) STr2_mPi0_rec[i] = -999.;
    for(int i=0; i< NPI0MAX; i++) STr2_ptG1_rec[i] = -999.;
    for(int i=0; i< NPI0MAX; i++) STr2_ptG2_rec[i] = -999.;
    for(int i=0; i< NPI0MAX; i++) STr2_S4S9_1[i] = -999.;
    for(int i=0; i< NPI0MAX; i++) STr2_S4S9_2[i] = -999.;
    for(int i=0; i< NPI0MAX; i++) STr2_etaPi0_rec[i] = -999.;
    for(int i=0; i< NPI0MAX; i++) STr2_ptPi0_rec[i] = -999.;
    for(int i=0; i< NPI0MAX; i++) STr2_DeltaRG1G2[i] = -999.;
    STr_Es_nEE = 0;
    STr_Es_nES = 0;

    STr_Es_RecG1_E=-999.;
    STr_Es_RecG1_Eta=-999.;
    STr_Es_RecG1_Phi=-999.;
    STr_Es_RecG1es_E=-999.;
    STr_Es_e1_1=-999.;
    STr_Es_e1_2=-999.;
    STr_Es_RecG2_E=-999.;
    STr_Es_RecG2_Eta=-999.;
    STr_Es_RecG2_Phi=-999.;
    STr_Es_RecG2es_E=-999.;
    STr_Es_e2_1=-999.;
    STr_Es_e2_2=-999.;
    STr_Es_RecPi0_M=-999.;
    STr_Es_RecPi0_Eta=-999.;
    STr_Es_RecPi0es_M=-999.;
    STr_Es_RecPi0es_Eta=-999.;
    STr_Es_RecPi0esPos_M=-999.;
    STr_Es_RecPi0esPos_Eta=-999.;
    STr_Es_RecPi0esPos_Mw=-999.;
    STr_Es_RecPi0esPos_Etaw=-999.;
    STr_Es_Clu1es_Eta1=-999.;
    STr_Es_Clu1es_Phi1=-999.;
    STr_Es_Clu1es_x1=-999.;
    STr_Es_Clu1es_y1=-999.;
    STr_Es_Clu1es_z1=-999.;
    STr_Es_Clu2es_Eta1=-999.;
    STr_Es_Clu2es_Phi1=-999.;
    STr_Es_Clu2es_x1=-999.;
    STr_Es_Clu2es_y1=-999.;
    STr_Es_Clu2es_z1=-999.;

    STrPF_RecG1_E   = -999.;
    STrPF_RecG1_Eta = -999.; 
    STrPF_RecG1_Phi = -999.;
    STrPF_RecG1_DR  = -999.;
    STrPF_RecG2_E   = -999.;
    STrPF_RecG2_Eta = -999.; 
    STrPF_RecG2_Phi = -999.;
    STrPF_RecG2_DR  = -999.;
    STrPF_Pi0_M     = -999.;
    STrPF_Pi0_Eta   = -999.;
    STrPF_nPi0_rec  = 0;
    for(int i=0; i< NPI0MAX; i++)  STrPF_Pi0recIsEB[i]  = 0.;
    for(int i=0; i< NPI0MAX; i++)  STrPF_mPi0_rec[i]  = -999.;
    for(int i=0; i< NPI0MAX; i++)  STrPF_etaPi0_rec[i] = -999.;
}

double max_array(double *A, int n){ 

    if(n==1)  return A[0]; 
    else      return max(A[0],max_array(A+1, n-1)); 
} 

double max (double x, double y) { 
    if(x>=y)  return x; 
    else      return y; 
}

//define this as a plug-in
DEFINE_FWK_MODULE(NewPi0Dumper_Gun);
