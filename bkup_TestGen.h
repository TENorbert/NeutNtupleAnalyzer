#ifndef TestGen_H
#define TestGen_H

#include "TObject.h"
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <sstream>
#include <TMath.h>
#include <TF1.h>
#include <TH1.h>
#include <TProfile.h>
#include <TH2.h>
#include <THStack.h>
#include <TFile.h>
#include <TDirectory.h>
#include <TTree.h>
#include <TBranch.h>
#include <TRandom.h>
#include <TLeaf.h>
#include <TString.h>
#include <TSystem.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TFrame.h>
#include <TLegend.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include "TLorentzVector.h"
#include <Math/VectorUtil.h>
#include "AnaInput.h"

#define MAXPHO 10
#define MAXOBJ 10
#define MAXJET 15
#define MAXVTX 50
#define MAXGEN 20
#define MAXMU 5

#define Kappa  0.193366133727   // Defination of Constant R/2C  From CMS TDR R = 1.29m and C = 299792458 m/s

#define  t_cut  -4.0
#define  eb_cut  1.479
#define  csc_dphi_min 0.072  // ~ 4.125 deg
#define  Nxtal_min   5.0
#define  SX_min  0.95     // max Swiss x value
#define  Njet_min 1
#define  MET_min  60.0    // MET threshold
#define  t_th    3.0     // Min time to define signal region
class TestGen : public TObject {

public:
   TestGen( string datacardfile = "DataCard.txt");     
   ~TestGen();        
   void ReadTree( string dataName );
   void Writehists();
   void InitHist();
   void Make_Plots();
   std::string Int2String(int num);
   float GetHaloTime( double gEta);  // calculated Halo Time
   bool IsGammaJetEvent(TLorentzVector jp4, TLorentzVector phop4, int jm, int phm );  // GammaJetEven Selection 
//   void ABCD_funx( int kmax, int n_jets, TLorentzVector gP4); //fxn to do ABCD on Njets;
// make Output Root file
//  TFile* f ;
  TDirectory* neut ; 
  TDirectory* Dphoton ; 
  TDirectory* HaloReg ; 
  TDirectory* SpikeReg ; 
  TDirectory* SpikeInPhoReg ; 
  TDirectory* BkgEst1 ; 

  // Initialize Histograms:
  // Define a  Struct to Hold all Histograms and Output file
  struct kin_hist {

   TH1D* cscdphiInTimeSlice[26];
   TH1D* NCrysInTimeSlice[26];

   TH1D* h_Time;
   TH1D* h_g1Pt ;
   TH1D* WAveSeedBCphotime; 
   TH1D* AveSCphotime; 
   TH1D* evt_met ;
   TH1D* ph_smin ;
   TH1D* ph_smaj; 
   TH1D* ph_e ;
   TH1D* ph_z ;
   TH1D* ph_eta ;
   TH1D* ph_phi;
   TH1D* jet_eta;
   TH1D* jet_phi;
   TH1D* jp_deta;
   TH1D* jp_dphi;
   TH1D* njets ;
   TH1D* npho ;
   TH1D* j_pt ;
   TH1D* ph_HoverE ;
   TH1D* mettheta ;
   TH1D* phomet_thetadiff;
   TH1D* MassNt;  
   TH1D* pho_angle;
   TH1D* pho_EcalIso;
   TH1D* pho_HcalIso;
//   TH1D* hcal_Iso;
   TH1D* pho_TrkIso;
   TH1D* pu_vtx; 
   TH2D* phoTimeVsEta; 
   TH2D* phoTimeVsE;
   TH2D* phoTimeVsPhi;
    
   TH2D* phoTimeVsNCrys, *phoTimeVsPt, *phoTimeVsMet, *NCrysVsCSCdphi, *phoPtVsMet; 
   TH2D* phoEtaVsNCrys,  *phoPhiVsNCrys,*MetVsNCrys, *phoPtVsNCrys;
   TH2D* phoEtaVsCSCdphi,*phoPhiVsCSCdphi, *MetVsCSCdphi,*phoPtVsCSCdphi;


   TH2D* metVsPU;
   TH2D* photimeVsPU;
   TH2D* pho_Ecal_IsoVsPU;
   TH2D* pho_Trk_IsoVsPU;
   TH2D* pho_Hcal_IsoVsPU;
   TH2D* Hcal_IsoVsPU;
   TH2D* sMinorVsPU;
   TH1D *phoCSCtime, *pho_CSCdphi, *phonBC, *phonXtalEB,*pho_SSXEB, *phopzOnpt, *pho_sigmaIeta, *halo_phodrho,*halo_phodphi, *pho_halodphi, *pho_halodrho;
   TH2D* phoetaVsphi;
   TH2D* kpho_timeVsEta, *kpho_timeVsPhi; 
   TH1D* kpho_time, *pho_num_phoEB, *pho_num_jetEB, *pho_num_phoEE, *pho_num_jetEE;
   TH1D* pho_LN2timeEB, *pho_LN2GP2timeEB,*pho_GP2timeEB;
   TH1D* pho_LN2timeEE, *pho_LN2GP2timeEE,*pho_GP2timeEE;
   TH2D *pho_timeVsCSCdphi;     
   //EB and EE
   TH1D *pho_sigmaEtaEB, *pho_sigmaEtaEE, *pho_sminorEB, *pho_sminorEE, *pho_smajorEB, *pho_smajorEE;
   TH2D *pho_timeVsEtaEB,*pho_timeVsEtaEE, *pho_timeVsPhiEB, *pho_timeVsPhiEE; TH1D *pho_timeEB, *pho_timeEE;
   TH1D *pho_ATG2_smajorEB, *pho_ATG2_smajorEE, *pho_ATG2_sminorEB, *pho_ATG2_sminorEE, *pho_ATG2sminorEB, *pho_ATG2_sigmaEtaEB, *pho_ATG2_sigmaEtaEE;
  // Init Vertices Histograms
  TH1D *py1,*py2,*py3,*py4,*py5,*py6,*py7,*py8, *py9,*py10, *py11, *py12,*py13,*py14,*py15,*py16,*py17,*py18,*py19; 
 // Time Vs NVtx plots
  TH1D *tV1, *tV2, *tV3, *tV4, *tV5, *tV6, *tV7, *tV8, *tV9, *tV10, *tV11, *tV12, *tV13, *tV14, *tV15, *tV16, *tV17, *tV18, *tV19, *tV20, *tV21, *tV22;
  TProfile *HcalIso, *trkIso, *hcalIso, *ecalIso, *sminor;
 // ALl Photons variables
 TH2D*eta_gVstimeEB, *pho_ptVscscdphiEB;
 TH1D*n_gEB, *n_jEB, *g_nCrysEB, *g_timeEB, *g_cscdphiEB, *g_ptEB, *g_metEB;
  // Halo Variables
  TH2D* eta_hVstimeEB;
  TH1D*n_hEB,*n_jhEB, *h_nCrysEB, *h_timeEB, *h_cscdphiEB,*h_ptEB, *h_metEB;
  // Posible Spikes
  TH2D* eta_spkVstimeEB;
  TH1D*n_spkEB, *n_jspkEB, *spk_nCrysEB, *spk_timeEB, *spk_cscdphiEB, *spk_ptEB, *spk_metEB;

  // Spikes in Real Photon Region
  TH2D* eta_spkInphoVstimeEB;
  TH1D*n_spkInphoEB, *n_jspkInphoEB, *spkInpho_nCrysEB, *spkInpho_timeEB, *spkInpho_cscdphiEB, *spkInpho_ptEB, *spkInpho_metEB;
//HE Stuff
TH2D *HEhalo_timeVsHEdphi,*HEhalo_timeVsHEGdphi,*HEhalo_timeVsHEradius;
TH2D *HEhalo_timeVsHErho;
TH1D *HEtime,*HEradius,*HEenergy,*HErho,*HEdphi,*HEdphiEB, *HEdphiEE,*TimeREEHE;
TH2D *HEtimeVsPhophi,*HEtimeVsPhoeta;
TH2D *HEhalo_timeVsHEdphiEB,*HEhalo_timeVsHEdphiEE;

TH1D*eb_ptime,*eb_hptime, *eb_spike_ptime,*eb_qcd_ptime,*eb_low_metTime,*eb_high_metTime,*eb_pSWX, *eb_hpSWX, *eb_spike_pSWX,*eb_qcd_pSWX, *eb_pnXtal,*eb_hpnXtal, *eb_spike_pnXtal, *eb_qcd_pnXtal, *eb_pcscdPhi, *eb_hpcscdPhi, *eb_spike_pcscdPhi, *eb_qcd_pcscdPhi , *eb_met0, *eb_met1, *eb_met2, *eb_met3, *eb_time0 , *eb_time1, *eb_time2, *eb_time3;
TH2D* eb_reg, *eb_regA, *eb_regB, *eb_regC, *eb_regD;

TH1D*eb_pPt,*eb_hpPt, *eb_spike_pPt, *eb_qcd_pPt,*eb_pMET,*eb_hpMET, *eb_spike_pMET, *eb_qcd_pMET;

TH1D*eb_pNjets,*eb_hpNjets, *eb_spike_pNjets, *eb_qcd_pNjets;
};

struct Halogamma {
TH2D *halo_etaVsphi, *halo_etaVsStime,*halo_etaVsBCtime, *halo_etaVsSCtime, *halo_phiVsStime, *halo_phiVsBCtime, *halo_phiVsSCtime, *halo_rhoVsphi;

TH1D *halo_pzOnpt, *halo_nBC, *halo_nXtalEB,*halo_SSXEB, *halo_rho, *halo_phi, *halo_sigmaIeta, *halo_phonBCratio, *halo_phonXtalratio, *halo_TrksSbeta, *halo_nhalosegs,*halo_nOThits, *halo_nhalotrk,*halo_seedTime,*halo_wavBCtime, *halo_wavSCtime, *Rhalo_Time,*halo_smin, *halo_smaj;

// Halo Events with |t| < 2ns EB and EE -with removed ECAL Halo Tagging
TH1D *halo_sigmaEtaEB, *halo_sigmaEtaEE, *halo_sminorEB, *halo_sminorEE, *halo_smajorEB, *halo_smajorEE;
TH2D *khalo_timeVsEta, *khalo_timeVsPhi;
TH1D *khalo_time;
TH1D *halo_timeEB, *halo_timeEE, *halo_num_phoEB, *halo_num_phoEE, *halo_num_jetEB, *halo_num_jetEE;
TH1D *halo_CSCdphi;
TH2D *halo_timeVsCSCdphi;
TH2D *halo_timeVsEtaEB, *halo_timeVsEtaEE, *halo_timeVsPhiEB, *halo_timeVsPhiEE;
TH1D* halo_LN2timeEB, *halo_LN2GP2timeEB,*halo_GP2timeEB;
TH1D* halo_LN2timeEE, *halo_LN2GP2timeEE,*halo_GP2timeEE;
TH1D* halo_ATG2_smajorEB, *halo_ATG2_smajorEE, *halo_ATG2_sminorEB, *halo_ATG2_sminorEE, *halo_ATG2_sigmaEtaEB, *halo_ATG2_sigmaEtaEE;

};

// Strange Events 
struct ltimeEvt { 
// Large Time Events
TH1D *ltvtxX, *ltvtxY, *ltvtxZ, *lteta, *ltphi, *ltEvtmet, *ltEvtpt,*ltnjets,*ltnpho,*ltnvtx, *ltphoE ;
};

struct svtxEvt {
// Single vertex events
TH1D *svtxX, *svtxY, *svtxZ, *svtxeta, *svtxphi, *svtxEvtmet, *svtxEvtpt, *svtxnjets, *svtxnpho,*svtxnvtx ;
};


private:

   AnaInput*     Input;

   string hfolder  ;
   string plotType ;
   string rfolder  ;
   int ProcessEvents ;

  // For MC Events
   float genPx[MAXGEN], genPy[MAXGEN], genPz[MAXGEN], genE[MAXGEN], genM[MAXGEN] ;
   float genVx[MAXGEN], genVy[MAXGEN], genVz[MAXGEN], genT[MAXGEN] ;
   int   pdgId[MAXGEN], momId[MAXGEN] ;

   float phoPx[MAXPHO], phoPy[MAXPHO], phoPz[MAXPHO], phoE[MAXPHO], phoHoverE[MAXPHO] , timeChi2[MAXPHO], aveTime1[MAXPHO], aveTime[MAXPHO];
   float seedTime[MAXPHO],seedTimeErr[MAXPHO],aveTimeErr[MAXPHO],aveTimeErr1[MAXPHO], phoEta[MAXPHO],phoPhi[MAXPHO];
   float jetPx[MAXJET],jetPy[MAXJET],jetPz[MAXJET], jetE[MAXJET];
 
   float sigmaEta[MAXPHO],sigmaIeta[MAXPHO]; 
   int   nXtals[MAXPHO],nBC[MAXPHO] ;
 
   float phoEcalIso[MAXPHO], phoHcalIso[MAXPHO]; // HcalIso[MAXPHO];
   float phoTrkIso[MAXPHO], sMinPho[MAXPHO],sMajPho[MAXPHO];
 
   float fSpike[MAXPHO], maxSwissX[MAXPHO], seedSwissX[MAXPHO], dR_TrkPho[MAXPHO] ;
   int   nGen, nPhotons; 
   int   nJets;
   int  nMuons, nElectrons, triggered, nVertices, totalNVtx; 
   int eventId;

   float met;
   float metPx, metPy; 
   float muE[MAXMU];
   float vtxDx[MAXVTX],vtxDy[MAXVTX],vtxDz[MAXVTX];
  
   int   jetCM[MAXJET], jetNDau[MAXJET];
   float jetCEF[MAXJET], jetNHF[MAXJET], jetCHEF[MAXJET], jetEta[MAXJET]; 
// HE Tagging stuff
   float HERho[MAXPHO], HETime[MAXPHO],HEGPhi[MAXPHO],HERadius[MAXPHO],HEEnergy[MAXPHO],HEdphi[MAXPHO];
     

// Halo infos
    float cscTime[MAXPHO]; 
    float cscdPhi[MAXPHO];
//    int nTrksSmallBeta, nHaloSegs ;

    bool IscscHaloSeg_Tag, IscscHaloTrk_Tag, IsBeamHaloIDTightTag, IscscHaloTight_Tag;

 //   int nOutTimeHits, nHaloTracks ;

    float haloPhi, haloRho;

   float vtxX[MAXVTX],vtxY[MAXVTX],vtxZ[MAXVTX], vtxChi2[MAXVTX],vtxNdof[MAXVTX];

   vector<double> jetCuts ;
   vector <int>   trigCut ;
   vector <double> photonCuts;
   vector <double> metCut; 
   vector <double> HaloCuts; 
   vector <double> photonIso; 
   vector <double> JetIdCuts; 
   //ClassDef(TestGen, 1);


};

//#if !defined(__CINT__)
//    ClassImp(TestGen);
#endif

