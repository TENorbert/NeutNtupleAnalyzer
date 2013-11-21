#include "TestGen.h"


// struct of hists and files
TestGen::kin_hist my;    // Struct holds all Kinematics plots and files
TestGen::ltimeEvt Lt;    // Large time >= 10ns Evts
TestGen::svtxEvt  Sv;    // Single Vertex Evts
TestGen::Halogamma Hg;  // Halo Gamma Gamma Evts

float Time_Array[32] = { -6.0, -5.0, -4.0, -3.0, -2.0, -1.0, 0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0,10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0, 17.0, 18.0, 19.0, 20.0, 21.0, 22.0, 23.0, 24.0, 25.0 };
string name1 = "CSCdphiInTimeSliceEB_";
string name2 = "NCrysInTimeSliceEB_";
std::string hname1[32];
std::string hname2[32];
//TFile *f = new TFile("TodayPhoton_Eta_Studies_DP_Trig_NoJetID.root","recreate");
//TFile *f = new TFile("gmsb_180_DP_gammaTriggger.root","recreate");
TFile *f = new TFile("JetTiming_DPTrigger_Displaced_Photon_outputfile.root","recreate");

TestGen::TestGen( string datacardfile ){

  Input  = new AnaInput( datacardfile );
  
  Input->GetParameters("PlotType",      &plotType ) ; 
  Input->GetParameters("Path",          &hfolder ) ; 
  Input->GetParameters("RootFiles",     &rfolder ) ; 
  Input->GetParameters("ProcessEvents", &ProcessEvents ) ; 
  Input->GetParameters("JetCuts",       &jetCuts );
  Input->GetParameters("TrigCut",       &trigCut );
  Input->GetParameters("photonCuts",    &photonCuts);
  Input->GetParameters("MetCuts",       &metCut);
  Input->GetParameters("HaloCuts",      &HaloCuts);
  Input->GetParameters("photonIso",      &photonIso);
  Input->GetParameters("JetIdCuts",      &JetIdCuts);
}

TestGen::~TestGen(){

  delete Input ;
  cout<<" done ! "<<endl ;

}

// function to convert Int to  String
std::string TestGen::Int2String(int num){
stringstream mystream ;
mystream  << num;
return mystream.str();
}

//
//
//Function to Initialize Histograms
//
//

void TestGen::InitHist() {

// Initial Time_Window hists
for( int ii = 0; ii < 32; ii++){
   
   hname1[ii] = name1 + Int2String(ii);
   hname2[ii] = name2 + Int2String(ii);

   my.cscdphiInTimeSlice[ii] = new TH1D( hname1[ii].c_str(), hname1[ii].c_str(), 100, 0.0, 3.5);
   my.NCrysInTimeSlice[ii] = new TH1D( hname2[ii].c_str(), hname2[ii].c_str(), 50, 0.0, 50.0);

}


   my.phoTimeVsNCrys = new TH2D("my.phoTimeVsNCrys","Photon Time Vs NCrys",50, 0.0, 50.0, 500, -50.0, 50.0);
    my.phoTimeVsPt = new TH2D("my.phoTimeVsPt","Time^{#gamma} Vs P_{T}^{#gamma}",200, 0.0, 3500.0, 500, -50.0, 50.0);
    
    my.phoTimeVsMet = new TH2D("my.phoTimeVsMet","Time^{#gamma} Vs E_{T}^{Miss}",100, 25.0, 1500.0, 40, -5.0, 35.0);
    
    my.NCrysVsCSCdphi = new TH2D("my.NcrysVsCSCdphi","NCrys Vs #delta #phi{CSCSeg,#gamma}",100, 0.0, 3.5, 50, 0.0, 50.0);
    
    my.phoPtVsMet = new TH2D("my.phoPtVsMet"," P_{T}^{#gamma} Vs E_{T}^{Miss}",100, 0.0, 3500.0, 100, 0.0, 3500.0);

    my.phoEtaVsNCrys = new TH2D("my.phoEtaVsNCrys","#eta_{#gamma} Vs NCrys",50, 0.0, 50.0, 100, -3.0, 3.0);
    my.phoPhiVsNCrys = new TH2D("my.phoPhiVsNCrys","#phi_{#gamma} Vs NCrys",50, 0.0, 50.0, 100, -3.0, 3.0);
    
    my.phoPtVsNCrys = new TH2D("my.phoPtVsNCrys","P_{T}^{#gamma} Vs NCrys",50, 0.0, 50.0, 200, 0.0, 3500.0);
    
    my.MetVsNCrys = new TH2D("my.MetVsNCrys","E_{T}^{Miss} Vs NCrys",50, 0.0, 50.0, 200, 0.0, 3500.0);

    my.phoEtaVsCSCdphi = new TH2D("my.phoEtaVsCSCdphi","#eta_{#gamma} Vs #delta #phi(CSC Seg, #gamma)",100, 0.0, 3.5, 100, -3.0, 3.0);
    my.phoPhiVsCSCdphi = new TH2D("my.phoPhiVsCSCdphi","#phi_{#gamma} Vs #delta #phi(CSC Seg, #gamma)",100, 0.0, 3.5, 100, -3.0, 3.0);
    my.MetVsCSCdphi = new TH2D("my.MetVsCSCdphi","E_{T}^{Miss} Vs #delta #phi(CSC Seg, #gamma)",100, 0.0, 3.5, 200, 0.0, 3500.0);
    my.phoPtVsCSCdphi = new TH2D("my.phoPtVsCSCdphi","P_{T}^{#gamma} Vs #delta #phi(CSC Seg, #gamma)",100, 0.0, 3.5, 200, 0.0, 3500.0);


    my.h_Time  = new TH1D("my.h_Time", "Photon Time(ns)", 500,  -50.0, 50.0);
    my.h_g1Pt  = new TH1D("my.h_g1Pt", "Leading Photon Pt(GeV) ", 200,  0, 4000);
    my.WAveSeedBCphotime  = new TH1D("my.WAveSeedBCphotime", "Photon (W Ave Seed BC) Time(ns)", 500,  -50.0, 50.0);
    my.AveSCphotime  = new TH1D("my.AveSCphotime", "Photon (W Ave SC) Time(ns)", 500,  -50.0, 50.0);
    my.evt_met = new TH1D("my.evt_met", "Missing Energy(GeV)", 200, 0, 4000);
    my.ph_smin = new TH1D("my.ph_smin", "Shower Width in dxn of Minor Axis of Ecl Cluster", 100, 0,5);
    my.ph_smaj = new TH1D("my.ph_smaj", "Shower Width in dxn of Major Axis of Ecal Cluster", 100,0, 5);
    my.ph_e = new TH1D("my.ph_e","Leading Photon Energy(GeV)", 200, 0, 4000);
    my.ph_z = new TH1D("my.ph_z", "Z Vextex Position of Photon(cm)", 4000, -2000.0, 2000.0);
    my.ph_eta = new TH1D("my.ph_eta","Leading Photon #eta", 100, -3.0, 3.0);
    my.ph_phi = new TH1D("my.ph_phi", "Leading Photon #phi", 100, -3.142, 3.142);
    my.jet_eta = new TH1D("my.jet_eta", "Leading Jet #eta", 100, -3.0, 3.0);
    my.jet_phi = new TH1D("my.jet_phi", "Leading Jet #phi", 100, -3.142, 3.142);
    my.jp_deta = new TH1D("my.jp_deta", " Leading Jet-Photo #Delta#eta", 100, -3.0, 3.0);
    my.jp_dphi = new TH1D("my.jp_dphi", "Leading Jet-Photon #Delta#phi", 100, -10, 10);
    my.njets = new TH1D("my.njets", "Number of Jets in Event", 20, 0, 20);
    my.npho = new TH1D("my.npho", "Number of #gamma s in Event", 10, 0, 10);
    my.pu_vtx = new TH1D("my.pu_vtx", "Number of PVs", 1000, 0, 50);
    my.j_pt = new TH1D("my.j_pt", " Leading Jet Pt(GeV)", 200, 0, 2000);
    my.ph_HoverE = new TH1D("my.ph_HoverE", "Photon Hadronic Energy Over EM Energy Ratio", 20, -5.0, 5.0);
    my.mettheta  =  new TH1D("my.mettheta", "Gravitino #theta", 200, -10.0, 10.0);
    my.phomet_thetadiff = new TH1D("my.phomet_thetadiff", "Photon-Met Angular Distrubution", 200, -10.0, 10.0);
    my.MassNt  = new TH1D("my.MassNt", "Neutralino Transverse Mass Distribution(GeV)", 250, 0.0, 2500.0);
    my.pho_angle = new TH1D("my.pho_angle","Photon Angular Distribution(Radians)", 200, -10.0, 10.0);
    my.metVsPU = new TH2D("my.metVsPU","Effect of PU on MET",100, 0, 40, 200, 0,2500);
    my.photimeVsPU = new TH2D("my.photimeVsPU","No. PV Vs Photon Time",100, 0, 400, 500, -50.0, 50.0);
    my.pho_Ecal_IsoVsPU = new TH2D("my.phoEcal_IsoVsPU","EcalIso Vs PU", 100, 0.0, 40.0, 100, 0.0, 10.0); 
    my.pho_Trk_IsoVsPU = new TH2D("my.phoTrk_IsoVsPU","TrackIso Vs PU", 100, 0.0, 40.0, 100, 0.0, 10.0); 
    my.pho_Hcal_IsoVsPU = new TH2D("my.phoHcal_IsoVsPU","HcalIso Vs PU", 100, 0.0, 40.0, 100, 0.0, 10.0); 
//    my.Hcal_IsoVsPU = new TH2D("my.Hcal_IsoVsPU","2012 HcalIso Vs PU", 100, 0.0, 40.0, 100, 0.0, 10.0); 
    my.sMinorVsPU = new TH2D("my.sMinorVsPU","sMinor Vs PU", 100, 0.0, 40.0, 100, 0.0, 1.0); 

    my.phoTimeVsEta = new TH2D("my.phoTimeVsEta","Photon Time Vs Eta",100, -3.0, 3.0, 500, -50.0, 50.0);
    my.phoTimeVsE = new TH2D("my.phoTimeVsE","Photon Time Vs Energy", 400, 0.0, 4000.0, 500, -50.0, 50.0);
    my.phoTimeVsPhi = new TH2D("my.phoTimeVsPhi","Photon Time Vs Phi",100, -3.5, 3.5, 500, -50.0, 50.0); 
// Photon Iso studies    
   my.pho_EcalIso = new TH1D("my.pho_EcalIso","Photon EcalIso", 100, 0.0, 10.0);
   my.pho_HcalIso = new TH1D("my.pho_HcalIso", "Photon HcalIso", 100, 0.0, 10.0);
//   my.hcal_Iso    = new TH1D("my.hcal_Iso", "2012 Photon HcalIso", 100, 0.0, 10.0);
   my.pho_TrkIso  = new TH1D("my.pho_TrkIso","Photon Track Iso", 100, 0.0, 10.0);

// Photon 1D plots   
    my.phoCSCtime = new TH1D("my.phoCSCtime","Time of CSC #gamma", 1000, -100.0, 100.0); 
    my.phonBC = new TH1D("my.phonBC","Seed BC in #gamma SC", 100, 0.0, 100.0);
    my.phonXtalEB = new TH1D("my.phonXtalEB","No. Of Crys in #gamma SC ", 100, 0.0, 100.0);
    my.pho_SSXEB = new TH1D("my.pho_SSXEB","SeedXtal SwissX Of #gamma SC ", 100, -10.0, 10.0);
    my.pho_sigmaIeta = new TH1D("my.pho_sigmaIeta","#gamma #sigma_{i#eta,i#eta}", 100, 0.0, 10.0);
    my.phoetaVsphi = new TH2D("my.phoetaVsphi","#eta_{#gamma} Vs #phi_{#gamma} ", 100, -3.0, 3.0, 100, -3.50, 3.50);
    
    my.pho_timeVsEtaEB = new TH2D("my.pho_timeVsEtaEB","Photon Time Vs Eta EB",100, -3.0, 3.0, 500, -50.0, 50.0);
    my.pho_timeVsEtaEE = new TH2D("my.pho_timeVsEtaEE","Photon Time Vs Eta EE",100, -3.0, 3.0, 500, -50.0, 50.0);  
    my.pho_timeVsPhiEB = new TH2D("my.pho_timeVsPhiEB","Photon Time Vs Phi EB",100, -3.5, 3.5, 500, -50.0, 50.0); 
    my.pho_timeVsPhiEE = new TH2D("my.pho_timeVsPhiEE","Photon Time Vs Phi EE",100, -3.5, 3.5, 500, -50.0, 50.0); 
    my.pho_timeEB  = new TH1D("my.pho_timeEB", "Photon Time(ns) EB", 500,  -50.0, 50.0);
    
    my.phoTimeNegPhi_3WinEB  = new TH1D("my.phoTimeNegPhi_3WinEB", "Time #phi in[-3, -2] EB", 500,  -50.0, 50.0);
    my.phoTimePosPhi_3WinEB  = new TH1D("my.phoTimePosPhi_3WinEB", "Time #phi in[2, 3] EB", 500,  -50.0, 50.0);
    my.phoTimePhi_ZeroWinEB  = new TH1D("my.phoTimePhi_ZeroWinEB", "Time #phi in[-0.5, 0.5] EB", 500,  -50.0, 50.0);

    
    my.pho_timeEE  = new TH1D("my.pho_timeEE", "Photon Time(ns) EE", 500,  -50.0, 50.0);
    my.pho_sminorEB = new TH1D("my.pho_sminorEB", "SMinor EB", 100, 0,5);
    my.pho_smajorEB = new TH1D("my.pho_smajorEB", "SMajor EB", 100,0, 5);
    my.pho_sigmaEtaEB = new TH1D("my.pho_sigmaEtaEB", "Photon #sigma_{#eta,#eta} EB", 20,0, 10);
    my.pho_sminorEE = new TH1D("my.pho_sminorEE", "SMinor EE", 20, 0,5);
    my.pho_smajorEE = new TH1D("my.pho_smajorEE", "SMajor EE", 20,0, 5);
    my.pho_sigmaEtaEE = new TH1D("my.pho_sigmaEtaEE", "Photon #sigma_{#eta,#eta} EE", 20,0, 10);
    my.pho_timeVsCSCdphi = new TH2D("my.pho_timeVsCSCdphi","#gamma Time Vs CSC |#delta #phi|",200, -3.50, 3.50, 500, -50.0, 50.0); 
    my.pho_CSCdphi = new TH1D("my.pho_CSCdphi","#gamma,CSCSeg |#delta #phi|",200, -3.50, 3.50);    
    my.pho_num_jetEB = new TH1D("my.pho_num_jetEB", "No. EB Jets ", 20, 0, 20);
    my.pho_num_phoEB = new TH1D("my.pho_num_phoEB", "No. of EB #gamma s ", 10, 0, 10);
    my.pho_num_jetEE = new TH1D("my.pho_num_jetEE", "No. of EE Jets ", 20, 0, 20);
    my.pho_num_phoEE = new TH1D("my.pho_num_phoEE", "No. of EE #gamma s ", 10, 0, 10);
    my.pho_LN2timeEB  = new TH1D("my.pho_LN2timeEB", "Photon Time < -2ns EB", 500,  -50.0, 50.0);
    my.pho_LN2timeEE  = new TH1D("my.pho_LN2timeEE", "Photon Time < -2ns EE", 500,  -50.0, 50.0);
    my.pho_LN2GP2timeEB  = new TH1D("my.pho_LN2GP2timeEB", "-2ns < Photon Time < 2ns EB", 500,  -50.0, 50.0);
    my.pho_LN2GP2timeEE  = new TH1D("my.pho_LN2GP2timeEE", "-2ns < Photon Time < 2ns EE", 500,  -50.0, 50.0);
    my.pho_GP2timeEB  = new TH1D("my.pho_GP2timeEB", "Photon Time > 2ns EB", 500,  -50.0, 50.0);
    my.pho_GP2timeEE  = new TH1D("my.pho_GP2timeEE", "Photon Time > 2ns EE", 500,  -50.0, 50.0);
    my.pho_ATG2_smajorEB = new TH1D("my.pho_ATG2_smajorEB", "SMajor EB |Time| > 2ns", 100,0, 5);
    my.pho_ATG2_smajorEE = new TH1D("my.pho_ATG2_smajorEE", "SMajor EE |Time| > 2ns", 100,0, 5);
    my.pho_ATG2_sminorEB = new TH1D("my.pho_ATG2_sminorEB", "SMinor EB |Time| > 2ns", 100, 0,5);
    my.pho_ATG2_sminorEE = new TH1D("my.pho_ATG2_sminorEE", "SMinor EE |Time| > 2ns", 100, 0,5);
    my.pho_ATG2_sigmaEtaEB = new TH1D("my.pho_ATG2_sigmaEtaEB", "#sigma_{#eta,#eta} EB |Time| > 2ns", 20,0, 10);
    my.pho_ATG2_sigmaEtaEE = new TH1D("my.pho_ATG2_sigmaEtaEE", "#sigma_{#eta,#eta} EE |Time| > 2ns", 20,0, 10);
    
/*HEHalo stuff */
    my.HEhalo_timeVsHEdphi = new TH2D("my.HEhalo_timeVsHEdphi","Photon Time Vs HE-Pho #delta #phi",100, -3.50, 3.50, 500, -50.0, 50.0);
    my.HEhalo_timeVsHEGdphi = new TH2D("my.HEhalo_timeVsHEGdphi","Photon Time Vs HE-Pho #delta #phi Def2",100, -3.50, 3.50, 500, -50.0, 50.0);
    my.HEhalo_timeVsHEradius = new TH2D("my.HEhalo_timeVsHEradius","Photon Time Vs HE Radius",100, 0.0, 50.0, 500, -50.0, 50.0);
    my.HEhalo_timeVsHErho = new TH2D("my.HEhalo_timeVsHErho","Photon Time Vs HE #rho",100, -10.0, 10.0, 500, -50.0, 50.0);
    my.HEtimeVsPhophi = new TH2D("my.HEtimeVsPhophi","HE Time Vs Photon #phi",100, -3.50, 3.50, 500, -100.0, 100.0);
    my.HEtimeVsPhoeta = new TH2D("my.HEtimeVsPhoeta","HE Time Vs Photon #eta",100, -3.0, 3.0, 500, -100.0, 100.0);
   my.HEhalo_timeVsHEdphiEB = new TH2D("my.HEhalo_timeVsHEdphiEB","Photon Time Vs HE-Pho #delta #phi EB",100, -3.50, 3.50, 500, -50.0, 50.0);
   my.HEhalo_timeVsHEdphiEE = new TH2D("my.HEhalo_timeVsHEdphiEE","Photon Time Vs HE-Pho #delta #phi EE",100, -3.50, 3.50, 500, -50.0, 50.0);
   my.HEtime = new TH1D("my.HEtime","HE Time",500, -100.0, 100.0);    
   my.TimeREEHE = new TH1D("my.TimeREEHE","Ratio EE Over HE Time",500, -100.0, 100.0);    
   my.HEradius = new TH1D("my.HEradius","HE Radius",100, 0.0, 50.0);    
   my.HEenergy = new TH1D("my.HEenergy","HE Energy",10000, 0.0, 4000.0);    
   my.HErho = new TH1D("my.HErho","HE #rho",100, 0.0, 50.0);    
   my.HEdphi = new TH1D("my.HEdphi","#delta #phi{HE, #gamma}",100, -3.50, 3.50);    
   my.HEdphiEB = new TH1D("my.HEdphiEB","#delta #phi{HE, #gamma} EB",100, -3.50, 3.50);    
   my.HEdphiEE = new TH1D("my.HEdphiEE","#delta #phi{HE, #gamma} EE",100, -3.50, 3.50);    



    my.halo_phodrho = new TH1D("my.halo_phodrho"," #delta#rho of 0.4 Halo Muon & Photon",100, 0.0, 10.0);
    my.halo_phodphi = new TH1D("my.halo_phodphi"," #delta#phi of 0.4 Muon & Photon",100, -3.50, 3.50);
    my.pho_halodphi = new TH1D("my.pho_halodphi"," #delta#phi of CSC Seg & Photon",100, -3.50, 3.50);
    my.pho_halodrho = new TH1D("my.pho_halodrho"," #delta R of CSC Seg & Photon",100, -3.50, 3.50);
// Halo Plots
    Hg.halo_etaVsphi = new TH2D("Hg.halo_etaVsphi","Halo #gamma  #eta Vs #phi",100, -3.0, 3.0, 100, -3.50, 3.50); 
    Hg.halo_phiVsStime = new TH2D("Hg.halo_phiVsStime","Halo Photon Seed Xtal Time Vs Phi",100, -3.5, 3.5, 500, -50.0, 50.0);
    Hg.halo_phiVsBCtime = new TH2D("Hg.halo_phiVsBCtime","Halo Photon W.Ave BC Time Vs Phi",100, -3.5, 3.5, 500, -50.0, 50.0);
    Hg.halo_phiVsSCtime = new TH2D("Hg.halo_phiVsSCtime","Halo Photon W.Ave SC Time Vs Phi",100, -3.5, 3.5, 500, -50.0, 50.0);
    Hg.halo_etaVsStime = new TH2D("Hg.halo_etaVsStime","Halo Photon Eta Vs Seed Xtal Time",100, -3.0, 3.0, 500, -50.0, 50.0);
    Hg.halo_etaVsBCtime = new TH2D("Hg.halo_etaVsBCtime","Halo Photon Eta Vs W.Ave BC Time",100, -3.0, 3.0, 500, -50.0, 50.0);
    Hg.halo_etaVsSCtime = new TH2D("Hg.halo_etaVsSCtime","Halo Photon Eta Vs W.Ave SC Time",100, -3.0, 3.0, 500, -50.0, 50.0);
    Hg.halo_rhoVsphi = new TH2D("Hg.halo_rhoVsphi","Halo Photon #rho Vs #phi",100, 0.0, 5.0, 100, -3.5, 3.5);
  // 1 d plots 
  Hg.halo_nBC = new TH1D("Hg.halo_nBC","No Basic Clusters of Halo Photon",100, 0.0, 100.0);
  Hg.halo_nXtalEB = new TH1D("Hg.halo_nXtalEB","No Crys in Halo Photon",100, 0.0, 100.0);
  Hg.halo_SSXEB = new TH1D("Hg.halo_SSXEB","SeedCrys SwissX in Halo Photon SC",100, -5.0, 5.0);
  Hg.halo_rho = new TH1D("Hg.halo_rho","Halo #gamma  #rho",100, 0.0, 10.0);
  Hg.halo_phi = new TH1D("my.halo_phi","Halo #gamma #phi",100, -3.50, 3.50);
  Hg.halo_sigmaIeta = new TH1D("Hg.halo_sigmaIeta","#sigma_{i#eta,i#eta} of Halo Photon",1000, 0.0, 10.0);
 // Hg.halo_phonBCratio = new TH1D("Hg.halo_phonBCratio","Ratio of No. Halo Photon to Photon Basic Clusters",100, 0.0, 10.0);
//  Hg.halo_phonXtalEBratio = new TH1D("Hg.halo_phonXtalEBratio","Ratio of Halo Photon to Photon No. Crys",100, 0.0, 10.0);
  
 Hg.halo_seedTime  = new TH1D("Hg.halo_seedTime","Halo #gamma Seed Crys Time",500, -50.0, 50.0);
 Hg.halo_wavBCtime = new TH1D("Hg.halo_wavBCtime","Halo #gamma W.Av BC Time",500, -50.0, 50.0);
 Hg.halo_wavSCtime = new TH1D("Hg.halo_wavSCtime","Halo #gamma W.Av SC Time",500, -50.0, 50.0);    
 Hg.halo_timeVsEtaEB = new TH2D("Hg.halo_timeVsEtaEB","Halo #gamma Time Vs #eta EB",100, -3.0, 3.0, 500, -50.0, 50.0);
 Hg.halo_timeVsEtaEE = new TH2D("Hg.halo_timeVsEtaEE","Halo #gamma Time Vs #eta EE",100, -3.0, 3.0, 500, -50.0, 50.0);  
 Hg.halo_timeVsPhiEB = new TH2D("Hg.halo_timeVsPhiEB","Halo #gamma Time Vs #phi EB",100, -3.5, 3.5, 500, -50.0, 50.0); 
 Hg.halo_timeVsPhiEE = new TH2D("Hg.halo_timeVsPhiEE","Halo #gamma Time Vs #phi EE",100, -3.5, 3.5, 500, -50.0, 50.0); 
 Hg.halo_timeEB  = new TH1D("Hg.halo_timeEB", "Halo #gamma Time(ns) EB", 500,  -50.0, 50.0);
 Hg.halo_timeEE  = new TH1D("Hg.halo_timeEE", "Halo #gamma Time(ns) EE", 500,  -50.0, 50.0);
 Hg.halo_sminorEB = new TH1D("Hg.halo_sminorEB", "Halo #gamma SMinor EB", 100, 0,5);
 Hg.halo_smajorEB = new TH1D("Hg.halo_smajorEB", "Halo #gamma SMajor EB", 100,0, 5);
 Hg.halo_sigmaEtaEB = new TH1D("Hg.halo_sigmaEtaEB", "Halo #gamma #sigma_{#eta,#eta} EB", 20,0, 10);
 Hg.halo_sminorEE = new TH1D("Hg.halo_sminorEE", "Halo #gamma SMinor EE", 20, 0,5);
 Hg.halo_smajorEE = new TH1D("Hg.halo_smajorEE", "Halo #gamma SMajor EE", 20,0, 5);
 Hg.halo_sigmaEtaEE = new TH1D("Hg.halo_sigmaEtaEE", "Halo #gamma #sigma_{#eta,#eta} EB", 20,0, 10);
 Hg.halo_timeVsCSCdphi = new TH2D("Hg.halo_timeVsCSCdphi","Halo #gamma Time Vs CSC |#delta #phi|",100, -3.50, 3.50, 500, -50.0, 50.0); 
 Hg.halo_CSCdphi = new TH1D("Hg.halo_CSCdphi"," Halo #gamma |#delta #phi|",100, -3.50, 3.50);  
 Hg.halo_num_jetEB = new TH1D("Hg.halo_num_jetEB", "Number of EB Jets ", 20, 0, 20);
 Hg.halo_num_phoEB = new TH1D("Hg.halo_num_phoEB", "Number of EB #gamma s ", 10, 0, 10);
 Hg.halo_num_jetEE = new TH1D("Hg.halo_num_jetEE", "Number of EE Jets ", 20, 0, 20);
 Hg.halo_num_phoEE = new TH1D("Hg.halo_num_phoEE", "Number of EE #gamma s ", 10, 0, 10);
 Hg.halo_LN2timeEB  = new TH1D("Hg.halo_LN2timeEB", "Photon Time < -2ns EB", 500,  -50.0, 50.0);
 Hg.halo_LN2timeEE  = new TH1D("Hg.halo_LN2timeEE", "Photon Time < -2ns EE", 500,  -50.0, 50.0);
 Hg.halo_LN2GP2timeEB  = new TH1D("Hg.halo_LN2GP2timeEB", "-2ns < Photon Time < 2ns EB", 500,  -50.0, 50.0);
 Hg.halo_LN2GP2timeEE  = new TH1D("Hg.halo_LN2GP2timeEE", "-2ns < Photon Time < 2ns EE", 500,  -50.0, 50.0);
 Hg.halo_GP2timeEB  = new TH1D("Hg.halo_GP2timeEB", "Photon Time > 2ns EB", 500,  -50.0, 50.0);
 Hg.halo_GP2timeEE  = new TH1D("Hg.halo_GP2timeEE", "Photon Time > 2ns EE", 500,  -50.0, 50.0);
 Hg.halo_ATG2_smajorEB = new TH1D("Hg.halo_ATG2_smajorEB", "SMajor EB |Time| > 2ns", 100,0, 5);
 Hg.halo_ATG2_smajorEE = new TH1D("Hg.halo_ATG2_smajorEE", "SMajor EE |Time| > 2ns", 100,0, 5);
 Hg.halo_ATG2_sminorEB = new TH1D("Hg.halo_ATG2_sminorEB", "SMinor EB |Time| > 2ns", 100, 0,5);
 Hg.halo_ATG2_sminorEE = new TH1D("Hg.halo_ATG2_sminorEE", "SMinor EE |Time| > 2ns", 100, 0,5);
 Hg.halo_ATG2_sigmaEtaEB = new TH1D("Hg.halo_ATG2_sigmaEtaEB", "#sigma_{#eta,#eta} EB |Time| > 2ns", 20,0, 10);
 Hg.halo_ATG2_sigmaEtaEE = new TH1D("Hg.halo_ATG2_sigmaEtaEE", "#sigma_{#eta,#eta} EE |Time| > 2ns", 20,0, 10);
    
 Hg.halo_TrksSbeta = new TH1D("Hg.halo_TrksSbeta","Halo Tracks With Small Beta", 100, 0.0, 100);
 Hg.halo_nhalosegs = new TH1D("Hg.halo_nhalosegs","Number Halo Segments",100, 0.0, 10.0);
 Hg.halo_nOThits = new TH1D("Hg.halo_nOThits","Number of OutOfTime Halo Hits",100, 0.0, 100);
 Hg.halo_nhalotrk = new TH1D("Hg.halo_nhalotrk","Number of Halo Track",100, 0.0, 100);

// Define Large Time Events
 Lt.ltvtxX = new TH1D("Lt.ltvtxX","-10.0 < PhotonTime(ns) < 10.0  X Vertex Distribution", 500, -50.0, 50.0);
 Lt.ltvtxY = new TH1D("Lt.ltvtxY","-10.0 < PhotonTime(ns) < 10.0 Y Vertex Distribution", 500, -50.0, 50.0);
 Lt.ltvtxZ = new TH1D("Lt.ltvtxZ","-10.0 < PhotonTime(ns) < 10.0  Z Vertex Distribution", 500, -50.0, 50.0);
 Lt.ltnjets = new TH1D("Lt.ltnjets","-10.0 < PhotonTime(ns) < 10.0  Number of Jets", 20, 0.0, 20.0);
 Lt.ltnpho = new TH1D("Lt.ltnpho","-10.0 < PhotonTime(ns) < 10.0  Number of #gamma", 10, 0.0, 10.0);
 Lt.ltEvtmet = new TH1D("Lt.ltEvtmet","-10.0 < PhotonTime(ns) < 10.0  MET Distribution", 200, 0.0, 2500.0);
 Lt.ltEvtpt = new TH1D("Lt.ltEvtpt","-10.0 < PhotonTime(ns) < 10.0  Leading #gamma Pt Distribution", 200, 0.0, 2500.0);  
 Lt.ltphoE = new TH1D("Lt.ltphoE","-10.0 < PhotonTime(ns) < 10.0  Leading #gamma Energy Distribution", 400, 0.0, 4000.0);  
 Lt.lteta = new TH1D("Lt.lteta","-10.0 < PhotonTime(ns) < 10.0 Leading #gamma #eta Distribution", 100, -3.0, 3.0);
 Lt.ltphi = new TH1D("Lt.ltphi","-10.0 < PhotonTime(ns) < 10.0 Leading #gamma #phi Distribution", 100, -4.0, 4.0);
 Lt.ltnvtx = new TH1D("Lt.ltnvtx","-10.0 < PhotonTime(ns) < 10.0  Number of Vertices", 50, 0.0, 50.0);
  
        
// Define Single Vertex Events
 Sv.svtxX = new TH1D("Sv.svtxX","X Single Vertex Distribution", 1000, -50.0, 50.0);
 Sv.svtxY = new TH1D("Sv.svtxY","Y Single Vertex Distribution", 1000, -50.0, 50.0);
 Sv.svtxZ = new TH1D("Sv.svtxZ","Z Single Vertex Distribution", 1000, -50.0, 50.0);
 Sv.svtxnjets = new TH1D("Sv.svtxnjets","Number of Jets in Single Vertex Events", 20, 0.0, 20.0);
 Sv.svtxnpho = new TH1D("Sv.svtxnpho","Number of #gamma in Single Vertetx Events", 10, 0.0, 10.0);
 Sv.svtxEvtmet = new TH1D("Sv.svtxEvtmet","MET Distribution in Single Vertex Events", 200, 0.0, 2500.0);
 Sv.svtxEvtpt = new TH1D("Sv.svtxEvtpt","Leading #gamma Pt Distribution in Single Vertex Events", 200, 0.0, 2500.0);  
 Sv.svtxeta = new TH1D("Sv.svtxeta","Leading #gamma #eta Distribution in Single Vertex Events", 100, -3.0, 3.0);
 Sv.svtxphi = new TH1D("Sv.svtxtphi","Leading #gamma #phi Distribution in Single Vertex Events", 100, -4.0, 4.0);
 Sv.svtxnvtx = new TH1D("Sv.svtxnvtx","Number of Vertices ", 50, 0.0, 50.0);

// Seed Time Vs nVtx dists
 my.tV1 = new TH1D("my.tV1", "0<= nVtx< 5 Photon ( Seed Xtal) Timing Dist", 500, -25.0, 25.0);
 my.tV2 = new TH1D("my.tV2", "5< nVtx <= 10 Photon( Seed Xtal) Timing Dist", 500, -25.0, 25.0);
 my.tV3 = new TH1D("my.tV3", "10 < nVtx <=15 Photon( Seed Xtal) Timing Dist", 500, -25.0, 25.0);
 my.tV4 = new TH1D("my.tV4", "15 < nVtx <= 20 Photon( Seed Xtal) Timing Dist", 500, -25.0, 25.0);
 my.tV5 = new TH1D("my.tV5", "20< nVtx <=25 Photon(Seed Xtal) Timing(Seed Xtal) Dist", 500, -25.0, 25.0);
 my.tV6 = new TH1D("my.tV6", "25 < nVtx <=30 Photon(Seed Xtal) Timing Dist", 500, -25.0, 25.0);
 my.tV7 = new TH1D("my.tV7", "30 < nVtx <= 35 Photon(Seed Xtal) Timing Dist", 500, -25.0, 25.0);
// W. AVe SC
 my.tV12 = new TH1D("my.tV12", "0<= nVtx <= 5 Photon(W. Ave SC) Timing Dist", 500, -25.0, 25.0);
 my.tV13 = new TH1D("my.tV13", "5 < nVtx<=10 Photon(W.Ave SC) Timing Dist", 500, -25.0, 25.0);
 my.tV14 = new TH1D("my.tV14", "10 < nVtx<= 15 Photon(W. AVe SC) Timing Dist", 500, -25.0, 25.0);
 my.tV15 = new TH1D("my.tV15", "15 < nVtx <= 20 Photon(W. Ave SC) Timing Dist", 500, -25.0, 25.0);
 my.tV16 = new TH1D("my.tV16", "20 < nVtx <= 25 Photon(W. Ave SC) Timing Dist", 500, -25.0, 25.0);
 my.tV17 = new TH1D("my.tV17", "25 < nVtx <= 30 Photon(W. Ave SC) Timing Dist", 500, -25.0, 25.0);
 my.tV18 = new TH1D("my.tV18", "30 < nVtx <= 35 Photon(W. AVe SC) Timing Dist", 500, -25.0, 25.0); 
 my.py13 = new TH1D("my.py13", "45 < nVtx <= 55 Photon(W. Ave Seed BC) Timing Dist", 500, -25.0, 25.0);
 my.py14 = new TH1D("my.py14", "35 < nVtx <= 45  Photon(W. Ave Seed BC) Timing Dist", 500, -25.0, 25.0);
 my.py15 = new TH1D("my.py15", "24 < nVtx <= 35 Photon(W. Ave  Seed BC) Timing Dist", 500, -25.0, 25.0);
 my.py16 = new TH1D("my.py16", "18 < nVtx <= 24 Photon(W. Ave Seed BC) Timing Dist", 500, -25.0, 25.0);
 my.py17 = new TH1D("my.py17", "12 < nVtx <= 18 Photon(W. Ave Seed BC) Timing Dist", 500, -25.0, 25.0);
 my.py18 = new TH1D("my.py18", "6 < nVtx <= 12 Photon(W. Ave Seed BC) Timing Dist", 500, -25.0, 25.0);
 my.py19 = new TH1D("my.py19", "0 <= nVtx <= 6 Photon(W. Ave Seed BC) Timing Dist", 500, -25.0, 25.0);
// Background Estimation Photon
//
//
my.eb_ptime = new TH1D("my.eb_ptime", "EB Time", 500, -100.0,  0.0 );
my.eb_hptime = new TH1D("my.eb_hptime", "EB Halo #gamma Time", 500, -100.0,  0.0 );
my.eb_spike_ptime = new TH1D("my.eb_spike_ptime", "EB Spike #gamma Time", 500, -100.0,  0.0 );
my.eb_qcd_ptime = new TH1D("my.eb_qcd_ptime", "EB QCD #gamma Time", 500, -100.0,  0.0 );

my.eb_low_metTime = new TH1D("my.eb_low_metTime", "EB Low MET Photon Time", 500, -100.0, 0.0);
my.eb_high_metTime = new TH1D("my.eb_high_metTime", "EB High MET Photon Time", 500.0, -100.0, 0.0);

my.eb_pSWX = new TH1D("my.eb_pSWX", "Seed Xtal SwissCross of #gamma SC", 100, -5.0, 10);
my.eb_hpSWX = new TH1D("my.eb_hpSWX", "Seed Xtal Swiss X of Halo #gamma SC", 100, -5.0, 10);
my.eb_spike_pSWX = new TH1D("my.eb_spike_pSWX", "Seed Xtal SwissCross of Spike ", 100, -5.0, 10);
my.eb_qcd_pSWX = new TH1D("my.eb_qcd_pSWX", "Seed Xtal SwissCross of QCD #gamma SC", 100, -5.0, 10);

my.eb_pnXtal = new TH1D("my.eb_pnXtal", "No. Xtals #gamma SC", 50, 0.0, 50.0);
my.eb_hpnXtal = new TH1D("my.eb_hpnXtal", "No. Xtals Halo #gamma SC", 50, 0.0, 50.0);
my.eb_spike_pnXtal = new TH1D("my.eb_spike_pnXtal", "No. Xtals of Spike ", 50, 0.0, 50.0);
my.eb_qcd_pnXtal = new TH1D("my.eb_qcd_pnXtal", "No. Xtals of QCD #gamma SC", 50, 0.0, 50.0);

my.eb_pcscdPhi = new TH1D("my.eb_pcscdPhi", "CSC-#gamma |#delta #phi|", 100, 0.0, 5.0);
my.eb_hpcscdPhi = new TH1D("my.eb_hpcscdPhi", "CSC-#gamma |#delta #phi|", 100, 0.0, 5.0);
my.eb_spike_pcscdPhi = new TH1D("my.eb_spike_pcscdPhi", "CSC-#gamma |#delta #phi|", 100, 0.0, 5.0);
my.eb_qcd_pcscdPhi = new TH1D("my.eb_qcd_pcscdPhi", "CSC-#gamma |#delta #phi|", 100, 0.0, 5.0);

my.eb_met0 = new TH1D("my.eb_met0", "MET of 0-Jet Events", 4000, 0 , 4000);
my.eb_met1 = new TH1D("my.eb_met1", "MET of 1-Jet Events", 4000, 0 , 4000);
my.eb_met2 = new TH1D("my.eb_met2", "MET of 2-Jet Events", 4000, 0 , 4000);
my.eb_met3 = new TH1D("my.eb_met3", "MET of >=3-Jet Events", 4000, 0 , 4000);

my.eb_time0 = new TH1D("my.eb_time0", "Time of 0-Jet Events", 500, -50.0 ,50.0);
my.eb_time1 = new TH1D("my.eb_time1", "Time of 1-Jet Events", 500, -50.0 , 50.0);
my.eb_time2 = new TH1D("my.eb_time2", "Time of 2-Jet Events", 500, -50.0 , 50.0);
my.eb_time3 = new TH1D("my.eb_time3", "Time of >= 3-Jet Events", 500,-50.0, 50.0);

my.eb_reg = new TH2D("eb_reg", "MET  Vs Photon Time", 4000, 0 , 4000, 1000, -50.0, 50.0);
my.eb_regA = new TH2D("eb_regA", "MET  Vs Photon Time RegA", 4000, 0 , 4000, 1000, -50.0, 50.0);
my.eb_regB = new TH2D("eb_regB", "MET  Vs Photon Time RegB", 4000, 0 , 4000, 1000, -50.0, 50.0);
my.eb_regC = new TH2D("eb_regC", "MET  Vs Photon Time RegC", 4000, 0 , 4000, 1000, -50.0, 50.0);
my.eb_regD = new TH2D("eb_regD", "MET  Vs Photon Time RegD", 4000, 0 , 4000, 1000, -50.0, 50.0);

my.eb_pPt = new TH1D("my.eb_pPt", "Pt_{#gamma} of 0-Jet Events", 4000, 0 , 4000);
my.eb_hpPt = new TH1D("my.eb_hpPt", "Pt_{Halo #gamma} of 0-Jet Events", 4000, 0 , 4000);
my.eb_spike_pPt = new TH1D("my.eb_spike_pPt", "Pt_{Spike #gamma} of 0-Jet Events", 4000, 0 , 4000);
my.eb_qcd_pPt = new TH1D("my.eb_qcd_pPt", "Pt_{QCD #gamma} of 0-Jet Events", 4000, 0 , 4000);

my.eb_pMET = new TH1D("my.eb_pMET", "MET_{#gamma} of 0-Jet Events", 4000, 0 , 4000);
my.eb_hpMET = new TH1D("my.eb_hpMET", "MET_{Halo #gamma} of 0-Jet Events", 4000, 0 , 4000);
my.eb_spike_pMET = new TH1D("my.eb_spike_pMET", "MET_{Spike #gamma} of 0-Jet Events", 4000, 0 , 4000);
my.eb_qcd_pMET = new TH1D("my.eb_qcd_pMET", "MET_{QCD #gamma} of 0-Jet Events", 4000, 0 , 4000);

my.eb_pNjets = new TH1D("my.eb_pNjets", "No. 0f Jets", 20, 0, 20);
my.eb_hpNjets = new TH1D("my.eb_hpNjets", "No. 0f Jets Halo #gamma Event", 20, 0, 20);
my.eb_spike_pNjets = new TH1D("my.eb_spike_pNjets", "No. 0f Jets in Spike #gamma Event", 20, 0, 20);
my.eb_qcd_pNjets = new TH1D("my.eb_qcd_hpNjets", "No. 0f Jets QCD #gamma Event", 20, 0, 20);
my.eb_qcd_pNjets = new TH1D("my.eb_qcd_hpNjets", "No. 0f Jets QCD #gamma Event", 20, 0, 20);

//Spike & Halo reg
my.eta_gVstimeEB = new TH2D("my.eta_gVstimeEB","#eta_{#gamma} Vs Time EB",100, -3.0, 3.0, 500, -50.0, 50.0) ;
my.pho_ptVscscdphiEB = new TH2D("my.pho_ptVscscdphiEB","Pt_{#gamma} Vs #delta #phi(CSCSeg,#gamma) EB",100, 0.0, 3.5, 200, 0.0, 4000.0) ;
my.n_gEB = new TH1D("my.n_gEB", "No. 0f #gamma EB ", 20, 0, 20);
my.n_jEB = new TH1D("my.n_jEB", "No. 0f Jets EB ", 20, 0, 20);
my.g_nCrysEB = new TH1D("my.g_nCrysEB", "No. 0f Crys EB ",100, 0, 50.0);
my.g_timeEB = new TH1D("my.g_timeEB", "Time_{#gamma} EB ", 500, -50, 50);
my.g_cscdphiEB = new TH1D("my.g_cscdphiEB", "#delta #phi(CSCSeg, #gamma) EB", 100, 0, 3.5);
my.g_ptEB = new TH1D("my.g_ptEB", "Pt_{#gamma} EB ", 4000, 0, 4000);
my.g_metEB = new TH1D("my.g_metEB", "E_{T}^{Miss} EB ", 4000, 0, 4000);

//Halo
my.eta_hVstimeEB = new TH2D("my.eta_hVstimeEB","#eta_{Halo #gamma} Vs Time EB",100, -3.0, 3.0, 500, -50.0, 50.0);
my.n_hEB = new TH1D("my.n_hEB", "No. 0f Halo #gamma EB ", 20, 0, 20);
my.n_jhEB = new TH1D("my.n_jhEB", "No. 0f Jets EB ", 20, 0, 20);
my.h_nCrysEB = new TH1D("my.h_nCrysEB", "No. 0f Crys EB ",100, 0, 50.0);
my.h_timeEB = new TH1D("my.h_timeEB", "Time_{Halo #gamma} EB ", 500, -50, 50);
my.h_cscdphiEB = new TH1D("my.h_cscdphiEB", "#delta #phi(CSCSeg, #gamma) EB", 100, 0, 3.5);
my.h_ptEB = new TH1D("my.h_ptEB", "Pt_{Halo #gamma} EB ", 4000, 0, 4000);
my.h_metEB = new TH1D("my.h_metEB", "E_{T}^{Miss} EB ", 4000, 0, 4000);

//Spikes
my.eta_spkVstimeEB = new TH2D("my.eta_spkVstimeEB","#eta_{Spike #gamma} Vs Time EB",100, -3.0, 3.0, 500, -50.0, 50.0);
my.n_spkEB = new TH1D("my.n_spkEB", "No. 0f Spike #gamma EB ", 20, 0, 20);
my.n_jspkEB = new TH1D("my.n_jspkEB", "No. 0f Jets EB ", 20, 0, 20);
my.spk_nCrysEB = new TH1D("my.spk_nCrysEB", "No. 0f Crys EB ",100, 0, 50);
my.spk_timeEB = new TH1D("my.spk_timeEB", "Time_{#gamma} EB ", 500, -50, 50);
my.spk_cscdphiEB = new TH1D("my.spk_cscdphiEB", "#delta #phi(CSCSeg, #gamma) EB", 100, 0, 3.5);
my.spk_ptEB = new TH1D("my.spk_ptEB", "Pt_{#gamma} EB ", 4000, 0, 4000);
my.spk_metEB = new TH1D("my.spk_metEB", "E_{T}^{Miss} EB ", 4000, 0, 4000);

//Spikes in Photon Reg
my.eta_spkInphoVstimeEB = new TH2D("my.eta_spkInphoVstimeEB","Spike in Photon Region #eta_{Spike} Vs Time EB",100, -3.0, 3.0, 500, -50.0, 50.0);
my.n_spkInphoEB = new TH1D("my.n_spkInphoEB", "No. 0f Spike  In Photon Reg EB ", 20, 0, 20);
my.n_jspkInphoEB = new TH1D("my.n_jspkInphoEB", "No. 0f Jets EB ", 20, 0, 20);
my.spkInpho_nCrysEB = new TH1D("my.spkInpho_nCrysEB", "No. 0f Crys EB ",50, 0, 50);
my.spkInpho_timeEB = new TH1D("my.spkInpho_timeEB", "Time_{#gamma} EB ", 500, -50, 50);
my.spkInpho_cscdphiEB = new TH1D("my.spkInpho_cscdphiEB", "#delta #phi(CSCSeg, #gamma) EB", 100, 0, 3.5);
my.spkInpho_ptEB = new TH1D("my.spkInpho_ptEB", "Pt_{#gamma} EB ", 4000, 0, 4000);
my.spkInpho_metEB = new TH1D("my.spkInpho_metEB", "E_{T}^{Miss} EB ", 4000, 0, 4000);


//EEp & EEm
my.EEP_phoTimeVsRho = new TH2D("my.EEP_phoTimeVsRho", "#rho_{#gamma} Vs Time(ns) +EE", 100, 0.0, 100.0, 500, -50.0, 50.0);
my.EEM_phoTimeVsRho = new TH2D("my.EEM_phoTimeVsRho", "#rho_{#gamma} Vs Time(ns) -EE ",100, 0.0, 100.0, 500.0, -50.0, 50.0);
my.EEP_phoTimeVsR = new TH2D("my.EEP_phoTimeVsR", "Radius From Z_{#gamma} Vs Time(ns) +EE ",100, 0.0, 100.0, 500, -50.0, 50.0);
my.EEM_phoTimeVsR = new TH2D("my.EEM_phoTimeVsR", "Radius From Z_{#gamma} Vs Time(ns) -EE ",100, 0.0, 100.0, 500, -50.0, 50.0);

my.EEP_phoTimeVsPhi = new TH2D("my.EEP_phoTimeVsPhi", "#phi_{#gamma} Vs Time(ns) +EE ",100, -3.5, 3.5, 500, -50.0, 50.0);
my.EEM_phoTimeVsPhi = new TH2D("my.EEM_phoTimeVsPhi", "#phi_{#gamma} Vs Time(ns) -EE ",100, -3.5, 3.5, 500, -50.0, 50.0);
   
my.EEP_phoRho = new TH1D("my.EEP_phoRho", "#rho_{#gamma} +EE ",100, 0.0, 100.0);
my.EEM_phoRho = new TH1D("my.EEM_phoRho", "#rho_{#gamma} -EE ",100, 0.0, 100.0);
my.EEP_phoR = new TH1D("my.EEP_phoR", "Radius From Z_{#gamma} +EE ",100, 0.0, 100.0);
my.EEM_phoR = new TH1D("my.EEM_phoR", "Radius From Z_{#gamma} -EE ",100, 0.0, 100.0);

my.EEP_phoPhi = new TH1D("my.EEP_phoPhi", "#phi_{#gamma} +EE ",100, -3.5, 3.5);
my.EEM_phoPhi = new TH1D("my.EEM_phoPhi", "#phi_{#gamma} -EE ",100, -3.5, 3.5);

my.EEP_pho_eta = new TH1D("my.EEP_pho_eta", "#eta_{#gamma}+EE Excl #phi=0,#phi Events",300, -3.0, 3.0);
my.EEM_pho_eta = new TH1D("my.EEM_pho_eta", "#eta_{#gamma}-EE Excl #phi=0,#phi Events",300, -3.0, 3.0);
my.EEP_pho_time = new TH1D("my.EEP_pho_time", "Time_{#gamma}+EE Excl #phi=0,#phi photons",300, -5.0, 25.0);
my.EEM_pho_time = new TH1D("my.EEM_pho_time", "Time_{#gamma}-EE Excl #phi=0,#phi photons",300, -5.0, 25.0);

my.ALL_EEP_pho_eta = new TH1D("my.ALL_EEP_pho_eta", "#eta_{#gamma}+EE ALL Photons",300, -3.0, 3.0);
my.ALL_EEM_pho_eta = new TH1D("my.ALL_EEM_pho_eta", "#eta_{#gamma}-EE ALL Photons",300, -3.0, 3.0);
my.ALL_EEP_pho_time = new TH1D("my.ALL_EEP_pho_time", "Time_{#gamma}+EE ALL photons",300, -5.0, 25.0);
my.ALL_EEM_pho_time = new TH1D("my.ALL_EEM_pho_time", "Time_{#gamma}-EE ALL photons",300, -5.0, 25.0);

my.EEP_ZPphi_pho_eta = new TH1D("my.EEP_ZPphi_pho_eta", "#eta_{#gamma}+EE,,#phi=0,#phi Events",300, -3.0, 3.0);
my.EEM_ZPphi_pho_eta = new TH1D("my.EEM_ZPphi_pho_eta", "#eta_{#gamma}-EE, #phi=0,#phi Events",300, -3.0, 3.0);
my.EEP_ZPphi_pho_time = new TH1D("my.EEP_ZPphi_pho_time", "Time_{#gamma}+EE, #phi=0,#phi photons",300, -5.0, 25.0);
my.EEM_ZPphi_pho_time = new TH1D("my.EEM_ZPphi_pho_time", "Time_{#gamma}-EE #phi=0,#phi photons",300, -5.0, 25.0);

// EE 
my.EEM_CSC_dphi_In_1ns = new TH1D("my.EEM_CSC_dphi_In_1ns", "#delta #phi(CSCSeg, #gamma) t in [-1, 1] -EE", 100, 0, 3.5);
my.EEM_CSC_dphi_NIn_1ns = new TH1D("my.EEM_CSC_dphi_NIn_1ns", "#delta #phi(CSCSeg, #gamma) t Not in [-1, 1] -EE", 100, 0, 3.5);
my.EEM_pho_time_NIn_Halo_Win = new TH1D("my.EEM_pho_time_NIn_Halo_Win", "Time , -EE, Non-Halo Region", 300, -5.0, 25.0);
my.EEM_pho_pt_NIn_Halo_Win = new TH1D("my.EEM_pho_pt_NIn_Halo_Win", "Pt_{#gamma} -EE, Non-Halo Region", 100, 0 , 4000);
my.EEM_pho_eta_NIn_Halo_Win = new TH1D("my.EEM_pho_eta_NIn_Halo_Win", "#eta_{#gamma} -EE, Non-Halo Region",300, -3.5, 3.5);
my.EEM_pho_ncrys_NIn_Halo_Win = new TH1D("my.EEM_pho_ncrys_NIn_Halo_Win", "NCrys, -EE Non-Halo Region ",50, 0, 50);


my.EEM_pho_time_In_Halo_Win = new TH1D("my.EEM_pho_time_In_Halo_Win", "Time , -EE, Halo Region", 300, -5.0, 25.0);
my.EEM_pho_pt_In_Halo_Win = new TH1D("my.EEM_pho_pt_In_Halo_Win", "Pt_{#gamma} -EE, Halo Region", 100, 0 , 4000);
my.EEM_pho_eta_In_Halo_Win = new TH1D("my.EEM_pho_eta_In_Halo_Win", "#eta_{#gamma} -EE, Halo Region",300, -3.5, 3.5);
my.EEM_pho_ncrys_In_Halo_Win = new TH1D("my.EEM_pho_ncrys_In_Halo_Win", "NCrys, -EE Halo Region ",50, 0, 50);


my.EEP_CSC_dphi_In_1ns = new TH1D("my.EEP_CSC_dphi_In_1ns", "#delta #phi(CSCSeg, #gamma) t in [-1, 1] +EE", 100, 0, 3.5);
my.EEP_CSC_dphi_NIn_1ns = new TH1D("my.EEP_CSC_dphi_NIn_1ns", "#delta #phi(CSCSeg, #gamma) t Not in [-1, 1] +EE", 100, 0, 3.5);
my.EEP_pho_time_NIn_Halo_Win = new TH1D("my.EEP_pho_time_NIn_Halo_Win", "Time , +EE, Non-Halo Region", 300, -5.0, 25.0);
my.EEP_pho_pt_NIn_Halo_Win = new TH1D("my.EEP_pho_pt_NIn_Halo_Win", "Pt_{#gamma} +EE, Non-Halo Region", 100, 0 , 4000);
my.EEP_pho_eta_NIn_Halo_Win = new TH1D("my.EEP_pho_eta_NIn_Halo_Win", "#eta_{#gamma} +EE, Non-Halo Region",300, -3.5, 3.5);
my.EEP_pho_ncrys_NIn_Halo_Win = new TH1D("my.EEP_pho_ncrys_NIn_Halo_Win", "NCrys +EE, Non-Halo Region ",50, 0, 50);

my.EEP_pho_time_In_Halo_Win = new TH1D("my.EEP_pho_time_In_Halo_Win", "Time , -EE, Halo Region", 300, -5.0, 25.0);
my.EEP_pho_pt_In_Halo_Win = new TH1D("my.EEP_pho_pt_In_Halo_Win", "Pt_{#gamma} -EE, Halo Region", 100, 0 , 4000);
my.EEP_pho_eta_In_Halo_Win = new TH1D("my.EEP_pho_eta_In_Halo_Win", "#eta_{#gamma} -EE, Halo Region",300, -3.5, 3.5);
my.EEP_pho_ncrys_In_Halo_Win = new TH1D("my.EEP_pho_ncrys_In_Halo_Win", "NCrys, -EE Halo Region ",50, 0, 50);

// Untaggeable Halo
my.EEP_Untag_Halo_pho_time = new TH1D("my.EEP_Untag_Halo_pho_time", "Time , EE+, Untagable Halo", 300, -5.0, 25.0);
my.EEM_Untag_Halo_pho_time = new TH1D("my.EEM_Untag_Halo_pho_time", "Time , EE-, Untagable Halo", 300, -5.0, 25.0);

my.EEP_Untag_Halo_pho_pt = new TH1D("my.EEP_Untag_halo_pho_pt", "Pt_{#gamma} EE+, Untagable Halo", 100, 0 , 4000);
my.EEM_Untag_Halo_pho_pt = new TH1D("my.EEM_Untag_halo_pho_pt", "Pt_{#gamma} EE-, Untagable Halo", 100, 0 , 4000);

my.EEM_Untag_Halo_pho_eta = new TH1D("my.EEM_Untag_halo_pho_eta", "#eta_{#gamma} EE-, Untagable Halo",300, -3.5, 3.5);
my.EEP_Untag_Halo_pho_eta = new TH1D("my.EEP_Untag_halo_pho_eta", "#eta_{#gamma} EE+, Untagable Halo",300, -3.5, 3.5);

my.EEM_Untag_Halo_pho_phi = new TH1D("my.EEM_Untag_halo_pho_phi", "#phi_{#gamma} EE-, Untagable Halo",300, -3.5, 3.5);
my.EEP_Untag_Halo_pho_phi = new TH1D("my.EEP_Untag_halo_pho_phi", "#phi_{#gamma} EE+, Untagable Halo",300, -3.5, 3.5);

my.EEP_Untag_Halo_pho_cscdphi = new TH1D("my.EEP_Untag_Halo_pho_cscdphi", "#delta #phi(CSCSeg, #gamma),EE+, Untagable Halo", 100, 0, 3.5);
my.EEM_Untag_Halo_pho_cscdphi = new TH1D("my.EEM_Untag_Halo_pho_cscdphi", "#delta #phi(CSCSeg, #gamma),EE-, Untagable Halo", 100, 0, 3.5);

my.EEP_Untag_Halo_pho_met = new TH1D("my.EEP_Untag_Halo_pho_met", "MET,EE+, Untagable Halo", 50, 0, 700);
my.EEM_Untag_Halo_pho_met = new TH1D("my.EEM_Untag_Halo_pho_met", "MET,EE-, Untagable Halo", 50, 0, 700);

my.EEP_Untag_Halo_pho_ncrys = new TH1D("my.EEP_Untag_Halo_pho_ncrys", "NCrys,EE+, Untagable Halo", 100, 0, 50);
my.EEM_Untag_Halo_pho_ncrys = new TH1D("my.EEM_Untag_Halo_pho_ncrys", "NCrys,EE-, Untagable Halo", 100, 0, 50);

my.EEM_Untag_Halo_pho_metVstime = new TH2D("my.EEM_Untag_Halo_pho_metVstime","MET Vs Time, EE-, Untagable Halo",100, 0.0, 700, 500, -25.0, 50.0);
my.EEP_Untag_Halo_pho_metVstime = new TH2D("my.EEP_Untag_Halo_pho_metVstime","MET Vs Time, EE+, Untagable Halo",100, 0.0, 700, 500, -25.0, 50.0);


//Jet Timing
my.Jseedtime1= new TH1D("my.Jseedtime1", "Jet SeedTime Cleaned", 200, -50.0, 50.0);
my.Jseedtime2= new TH1D("my.Jseedtime2", "Jet SeedTime Extract", 200, -50.0, 50.0);
my.JseedE= new TH1D("my.JseedE", "Jet Seed Xtal in ECAL Energy", 200, -0.0, 500.0);
my.JEcalEmEr= new TH1D("my.JEcalEmEr", "Jet Em Eenrgy", 200, -0.0, 500.0);

my.Jseedtime2VsPhi = new TH2D("my.seedtime2VsPhi", "#phi_{PFJet} Vs Time(ns)",100, -3.5, 3.5, 500, -50.0, 50.0);
my.Jseedtime2VsEta = new TH2D("my.seedtime2VsEta", "#eta_{PFJet} Vs Time(ns)",100, -3.5, 3.5, 500, -50.0, 50.0);
my.JSClusdR= new TH1D("my.JSClusdR", "JetSClus Matching #delta R", 200, 0.0, 10.0);
my.JseedBCtime = new TH1D("my.JseedBCtime", "Error W. Ave.Time Seed BC", 200, -50.0, 50.0);
my.JWaveBCtime = new TH1D("my.JWaveBCtime", "Error W. Ave.Time Seed BC I", 200, -50.0, 50.0);
my.JnCrys = new TH1D("my.JnCrys", "NCrys in Seed BC", 50, 0.0, 50.0);
my.Jnspike = new TH1D("my.Jnspike", "NCrys with SwissX > 0.98", 50, 0.0, 50.0);
my.JseedtimeVsEnergy= new TH2D("my.JseedtimeVsEnergy", "Seed Time Vs Energy", 200, 0.0, 500.0, 200, -50.0, 50.0);

my.JseedOOtChi2 = new TH1D("my.JseedOOtChi2", "Seed Out-Of time Chi2", 200, -100.0, 100.0);
my.JseedtimeChi2 = new TH1D("my.JseedtimeChi2", "Seed time Chi2", 200, -100.0, 100.0);
my.Jseedtime2VsBCEnergy= new TH2D("my.Jseedtime2VsBCEnergy", "Seed Time Vs Seed BC Energy", 200, 0.0, 500.0, 200, -50.0, 50.0);
my.Jseedtime2VsBCEt = new TH2D("my.Jseedtime2VsBCEt", "Seed Time Vs Seed BC Et", 200, 0.0, 500.0, 200, -50.0, 50.0);
my.Jseedtime2VsBCPt = new TH2D("my.Jseedtime2VsBCPt", "Seed Time Vs Seed BC Pt", 200, 0.0, 500.0, 200, -50.0, 50.0);

my.JwavetimeVsBCEnergy= new TH2D("my.JwavetimeVsBCEnergy", "W.Ave Time Vs Seed BC Energy", 200, 0.0, 500.0, 200, -50.0, 50.0);
my.JseedEVsEta = new TH2D("my.JseedEVsEta", "Seed Crys Energy Vs Eta ", 100, -3.5, 3.5, 200, 0.0, 500.0);
my.JseedBCEVsEta = new TH2D("my.JseedBCEVsEta", "Seed BC Energy Vs Eta ", 100, -3.5, 3.5, 200, 0.0, 500);
my.JseedBCEVsPhi = new TH2D("my.JseedBCEVsPhi", "Seed BC Energy Vs Phi", 100, -3.5, 3.5, 200, 0.0, 500);

my.JnUMjets = new TH1D("my.JnUMjets", "Num of Unmatched Jets", 50, 0.0, 50.0) ;

my.Jseedtime2EB= new TH1D("my.Jseedtime2EB", "Jet SeedTime Extract, EB", 200, -50.0, 50.0);
my.Jseedtime2EE= new TH1D("my.Jseedtime2EE", "Jet SeedTime Extract, EE", 200, -50.0, 50.0);

} // End of Init Hist fuction


// Fxn 2 Write Hist
void TestGen::Writehists(){

f->cd();
neut = f->mkdir("NeutKin");
neut->cd();


my.h_g1Pt->GetXaxis()->SetTitle("Photon Pt(GeV)");
my.h_g1Pt->GetYaxis()->SetTitle("Event Number");
my.h_g1Pt->Draw();
my.h_g1Pt->Write();

my.h_Time->GetXaxis()->SetTitle("Photon Time(ns)");
my.h_Time->GetYaxis()->SetTitle("Event Number");
my.h_Time->Draw();
my.h_Time->Write();

my.WAveSeedBCphotime->GetXaxis()->SetTitle("Photon(W AVe Seed BC) Time(ns)");
my.WAveSeedBCphotime->GetYaxis()->SetTitle("Event Number");
my.WAveSeedBCphotime->Draw();
my.WAveSeedBCphotime->Write();

my.AveSCphotime->GetXaxis()->SetTitle("Photon (W Ave SC) Time(ns)");
my.AveSCphotime->GetYaxis()->SetTitle("Event Number");
my.AveSCphotime->Draw();
my.AveSCphotime->Write();


my.evt_met->GetXaxis()->SetTitle("Event MET(GeV)");
my.evt_met->GetYaxis()->SetTitle("Event Number");
my.evt_met->Draw();
my.evt_met->Write();

my.ph_smin->GetXaxis()->SetTitle("SMinor");
my.ph_smin->GetYaxis()->SetTitle("Event Number");
my.ph_smin->Draw();
my.ph_smin->Write();

my.ph_smaj->GetXaxis()->SetTitle("SMajor");
my.ph_smaj->GetYaxis()->SetTitle("Event Number");
my.ph_smaj->Draw();
my.ph_smaj->Write();

my.ph_e->GetXaxis()->SetTitle("Photon Energy(GeV)");
my.ph_e->GetYaxis()->SetTitle("Event Number");
my.ph_e->Draw();
my.ph_e->Write();

my.njets->GetXaxis()->SetTitle("Number of Jets");
my.njets->GetYaxis()->SetTitle("Event Number");
my.njets->Draw() ;
my.njets->Write();

my.pu_vtx->GetXaxis()->SetTitle("nVertices");
my.pu_vtx->GetYaxis()->SetTitle("Event Number");
my.pu_vtx->Draw() ;
my.pu_vtx->Write();

my.npho->GetXaxis()->SetTitle("Number of #gammas");
my.npho->GetYaxis()->SetTitle("Event Number");
my.npho->Draw();
my.npho->Write();

my.j_pt->GetXaxis()->SetTitle("JetPt(GeV)");
my.j_pt->GetYaxis()->SetTitle("Event Number");
my.j_pt->Draw();
my.j_pt->Write();

	
my.photimeVsPU->GetXaxis()->SetTitle("Number of Vertices");
my.photimeVsPU->GetYaxis()->SetTitle("Photon Time(ns)");
my.photimeVsPU->Draw("colz") ;
my.photimeVsPU->Write();

my.phoCSCtime->GetYaxis()->SetTitle("No. Events");
my.phoCSCtime->GetXaxis()->SetTitle("CSC Photon Time(ns)");
my.phoCSCtime->Draw();
my.phoCSCtime->Write();

my.phonBC->GetXaxis()->SetTitle("No. Of Basic Clusters");
my.phonBC->GetYaxis()->SetTitle("No. Events");
my.phonBC->Draw();
my.phonBC->Write();
// Photon Iso Variables
my.pho_EcalIso->GetXaxis()->SetTitle("#gamma EcalIso");
my.pho_EcalIso->GetYaxis()->SetTitle("Event Number");
my.pho_EcalIso->Draw();
my.pho_EcalIso->Write();

my.pho_HcalIso->GetXaxis()->SetTitle("#gamma HcalIso");
my.pho_HcalIso->GetYaxis()->SetTitle("Event Number");
my.pho_HcalIso->Draw();
my.pho_HcalIso->Write();

my.pho_TrkIso->GetXaxis()->SetTitle("#gamma TrackIso");
my.pho_TrkIso->GetYaxis()->SetTitle("Event Number");
my.pho_TrkIso->Draw();
my.pho_TrkIso->Write();

//my.hcal_Iso->GetXaxis()->SetTitle("#gamma 2012 HCALIso");
//my.hcal_Iso->GetYaxis()->SetTitle("Event Number");
//my.hcal_Iso->Draw();
//my.hcal_Iso->Write();



// PU ? Plots
my.py1 = my.photimeVsPU->ProjectionY("my.py1", 0, 10);
my.py1->SetTitle("1 Vertex ");
my.py1->Draw();
my.py1->Write();

my.py2 = my.photimeVsPU->ProjectionY("my.py2", 11, 21);
my.py2->SetTitle("2 Vertices");
my.py2->Draw();
my.py2->Write();


my.py3 = my.photimeVsPU->ProjectionY("my.py3", 22, 32);
my.py3->SetTitle("3 Vertices");
my.py3->Draw();
my.py3->Write();

my.py4 = my.photimeVsPU->ProjectionY("my.py4", 33, 43);
my.py4->SetTitle("4 Vertices");
my.py4->Draw();
my.py4->Write();


my.py5 = my.photimeVsPU->ProjectionY("my.py5", 44, 54);
my.py5->SetTitle("5 Vertices");
my.py5->Draw();
my.py5->Write();


my.py6 = my.photimeVsPU->ProjectionY("my.py6", 55, 65);
my.py6->SetTitle("6 Vertices");
my.py6->Draw();
my.py6->Write();


my.py7 = my.photimeVsPU->ProjectionY("my.py7", 66, 76);
my.py7->SetTitle("7 Vertices");
my.py7->Draw();
my.py7->Write();


my.py8 = my.photimeVsPU->ProjectionY("my.py8", 77, 87);
my.py8->SetTitle("8 Vertices");
my.py8->Draw();
my.py8->Write();


my.py9 = my.photimeVsPU->ProjectionY("my.py9", 88, 98);
my.py9->SetTitle("9 Vertices");
my.py9->Draw();
my.py9->Write();

my.py10 = my.photimeVsPU->ProjectionY("my.py10", 99, 101);
my.py10->SetTitle("10 Vertices");
my.py10->Draw();
my.py10->Write();

my.py11 = my.photimeVsPU->ProjectionY("my.py11", 102, 112);
my.py11->SetTitle("11 Vertices");
my.py11->Draw();
my.py11->Write();


my.py12 = my.photimeVsPU->ProjectionY("my.py12", 113, 123);
my.py12->SetTitle("12Vertices");
my.py12->Draw();
my.py12->Write();


my.py13->GetXaxis()->SetTitle("45 < nVtx <= 55");
my.py13->GetYaxis()->SetTitle("Event Number");
my.py13->SetTitle("45< nVtx <= 55 Photon Time(ns)");
my.py13->Draw();
my.py13->Write();

my.py14->GetXaxis()->SetTitle("35 < nVtx <= 45");
my.py14->GetYaxis()->SetTitle("Event Number");
my.py14->SetTitle("35< nVtx <=45  Photon Time(ns)");
my.py14->Draw();
my.py14->Write();


my.py15->GetXaxis()->SetTitle("24 < nVtx <= 35");
my.py15->GetYaxis()->SetTitle("Event Number");
my.py15->SetTitle("24< nVtx <= 35 Photon Time(ns)");
my.py15->Draw();
my.py15->Write();


my.py16->GetXaxis()->SetTitle("18 < nVtx <= 24");
my.py16->GetYaxis()->SetTitle("Event Number");
my.py16->SetTitle("18< nVtx <= 24 Photon Time(ns)");
my.py16->Draw();
my.py16->Write();


my.py17->GetXaxis()->SetTitle("12 < nVtx <= 18");
my.py17->GetYaxis()->SetTitle("Event Number");
my.py17->SetTitle("12 < nVtx <= 18 Photon Time(ns)");
my.py17->Draw();
my.py17->Write();

my.py18->GetXaxis()->SetTitle("6 < nVtx <= 12");
my.py18->GetYaxis()->SetTitle("Event Number");
my.py18->SetTitle("6< nVtx <= 12 Photon Time(ns)");
my.py18->Draw();
my.py18->Write();

my.py19->GetXaxis()->SetTitle("0 <= nVtx <= 6");
my.py19->GetYaxis()->SetTitle("Event Number");
my.py19->SetTitle("0<= nVtx <= 6 Photon Time(ns)");
my.py19->Draw();
my.py19->Write();

// Real Distribution of Photon Time Vs Vertices
my.tV1->GetXaxis()->SetTitle("0-7 Vtx");
my.tV1->GetYaxis()->SetTitle("No. Events");
my.tV1->Draw();
my.tV1->Write();

my.tV2->GetXaxis()->SetTitle("7-14 Vtx");
my.tV2->GetYaxis()->SetTitle("No. Events");
my.tV2->Draw();
my.tV2->Write();

my.tV3->GetXaxis()->SetTitle("14-21 Vtx");
my.tV3->GetYaxis()->SetTitle("No. Events");
my.tV3->Draw();
my.tV3->Write();

my.tV4->GetXaxis()->SetTitle("21-28 Vtx");
my.tV4->GetYaxis()->SetTitle("No. Events");
my.tV4->Draw();
my.tV4->Write();

my.tV5->GetXaxis()->SetTitle("28-35 Vtx");
my.tV5->GetYaxis()->SetTitle("No. Events");
my.tV5->Draw();
my.tV5->Write();

my.tV6->GetXaxis()->SetTitle("35-42 Vtx");
my.tV6->GetYaxis()->SetTitle("No. Events");
my.tV6->Draw();
my.tV6->Write();

my.tV7->GetXaxis()->SetTitle("42-49 Vtx");
my.tV7->GetYaxis()->SetTitle("No. Events");
my.tV7->Draw();
my.tV7->Write();

my.tV12->GetXaxis()->SetTitle("0-7 Vtx");
my.tV12->GetYaxis()->SetTitle("No. Events");
my.tV12->Draw();
my.tV12->Write();

my.tV13->GetXaxis()->SetTitle("7-14 Vtx");
my.tV13->GetYaxis()->SetTitle("No. Events");
my.tV13->Draw();
my.tV13->Write();

my.tV14->GetXaxis()->SetTitle("14-21 Vtx");
my.tV14->GetYaxis()->SetTitle("No. Events");
my.tV14->Draw();
my.tV14->Write();

my.tV15->GetXaxis()->SetTitle("21-28 Vtx");
my.tV15->GetYaxis()->SetTitle("No. Events");
my.tV15->Draw();
my.tV15->Write();

my.tV16->GetXaxis()->SetTitle("28-35 Vtx");
my.tV16->GetYaxis()->SetTitle("No. Events");
my.tV16->Draw();
my.tV16->Write();

my.tV17->GetXaxis()->SetTitle("35-42 Vtx");
my.tV17->GetYaxis()->SetTitle("No. Events");
my.tV17->Draw();
my.tV17->Write();

my.tV18->GetXaxis()->SetTitle("42-49 Vtx");
my.tV18->GetYaxis()->SetTitle("No. Events");
my.tV18->Draw();
my.tV18->Write();


my.metVsPU->GetXaxis()->SetTitle("Number of Vertices");
my.metVsPU->GetYaxis()->SetTitle("Event MET(GeV)");
my.metVsPU->Draw("colz");
my.metVsPU->Write();

my.pho_Ecal_IsoVsPU->GetXaxis()->SetTitle("nVtx");
my.pho_Ecal_IsoVsPU->GetYaxis()->SetTitle("EcalIso");
my.pho_Ecal_IsoVsPU->Draw("colz");
my.pho_Ecal_IsoVsPU->Write();

my.ecalIso = my.pho_Ecal_IsoVsPU->ProfileX("my.ecalIso", 1, -1);
my.ecalIso->SetTitle("EcalIso Vs PU");
my.ecalIso->GetYaxis()->SetTitle("EcalIso");
my.ecalIso->GetXaxis()->SetTitle("nVtx");
my.ecalIso->Draw();
my.ecalIso->Write();

my.pho_Hcal_IsoVsPU->GetXaxis()->SetTitle("nVtx");
my.pho_Hcal_IsoVsPU->GetYaxis()->SetTitle("HcalIso");
my.pho_Hcal_IsoVsPU->Draw("colz");
my.pho_Hcal_IsoVsPU->Write();

my.hcalIso = my.pho_Hcal_IsoVsPU->ProfileX("my.hcalIso", 1, -1);
my.hcalIso->SetTitle("HcalIso Vs PU");
my.hcalIso->GetYaxis()->SetTitle("HcalIso");
my.hcalIso->GetXaxis()->SetTitle("nVtx");
my.hcalIso->Draw();
my.hcalIso->Write();

my.pho_Trk_IsoVsPU->GetXaxis()->SetTitle("nVtx");
my.pho_Trk_IsoVsPU->GetYaxis()->SetTitle("TrkIso");
my.pho_Trk_IsoVsPU->Draw("colz");
my.pho_Trk_IsoVsPU->Write();

my.trkIso = my.pho_Trk_IsoVsPU->ProfileX("my.trkIso", 1, -1);
my.trkIso->SetTitle("TrackIso Vs PU");
my.trkIso->GetYaxis()->SetTitle("TrackIso");
my.trkIso->GetXaxis()->SetTitle("nVtx");
my.trkIso->Draw();
my.trkIso->Write();


//my.Hcal_IsoVsPU->GetXaxis()->SetTitle("nVtx");
//my.Hcal_IsoVsPU->GetYaxis()->SetTitle("2012 HcalIso");
//my.Hcal_IsoVsPU->Draw("colz");
//my.Hcal_IsoVsPU->Write();

//my.HcalIso = my.Hcal_IsoVsPU->ProfileX("my.HcalIso", 1, -1);
//my.HcalIso->SetTitle("2012 HcalIso Vs PU");
//my.HcalIso->GetYaxis()->SetTitle("2012 HcalIso");
//my.HcalIso->GetXaxis()->SetTitle("nVtx");
//my.HcalIso->Draw();
//my.HcalIso->Write();

my.sMinorVsPU->GetXaxis()->SetTitle("nVtx");
my.sMinorVsPU->GetYaxis()->SetTitle("sMinor");
my.sMinorVsPU->Draw("colz");
my.sMinorVsPU->Write();

my.sminor = my.sMinorVsPU->ProfileX("my.sminor", 1, -1);
my.sminor->SetTitle("sMinor Vs PU");
my.sminor->GetYaxis()->SetTitle("sMinor");
my.sminor->GetXaxis()->SetTitle("nVtx");
my.sminor->Draw();
my.sminor->Write();



// EB and EE Stuff
my.phonXtalEB->GetXaxis()->SetTitle("No. Of Crys in SC");
my.phonXtalEB->GetYaxis()->SetTitle("No. Events");
my.phonXtalEB->Draw();
my.phonXtalEB->Write();

my.pho_SSXEB->GetXaxis()->SetTitle("SeedXtal in SC SwissXC");
my.pho_SSXEB->GetYaxis()->SetTitle("No. Events");
my.pho_SSXEB->Draw();
my.pho_SSXEB->Write();

my.pho_num_phoEB->GetXaxis()->SetTitle("Number of #gamma s");
my.pho_num_phoEB->GetYaxis()->SetTitle("Event Number");
my.pho_num_phoEB->Draw() ;
my.pho_num_phoEB->Write();

my.pho_num_phoEE->GetXaxis()->SetTitle("Number of #gamma s");
my.pho_num_phoEE->GetYaxis()->SetTitle("Event Number");
my.pho_num_phoEE->Draw() ;
my.pho_num_phoEE->Write();

my.pho_num_jetEB->GetXaxis()->SetTitle("Number of jets");
my.pho_num_jetEB->GetYaxis()->SetTitle("Event Number");
my.pho_num_jetEB->Draw() ;
my.pho_num_jetEB->Write();

my.pho_num_jetEE->GetXaxis()->SetTitle("Number of jets");
my.pho_num_jetEE->GetYaxis()->SetTitle("Event Number");
my.pho_num_jetEE->Draw() ;
my.pho_num_jetEE->Write();

my.pho_timeVsEtaEB->GetXaxis()->SetTitle("#eta_{#gamma}");
my.pho_timeVsEtaEB->GetYaxis()->SetTitle("Seed crys Time(ns)");
my.pho_timeVsEtaEB->Draw("colz");
my.pho_timeVsEtaEB->Write();

my.pho_timeVsEtaEE->GetXaxis()->SetTitle("#eta_{#gamma}");
my.pho_timeVsEtaEE->GetYaxis()->SetTitle("Seed crys Time(ns)");
my.pho_timeVsEtaEE->Draw("colz");
my.pho_timeVsEtaEE->Write();

my.pho_timeVsPhiEB->GetXaxis()->SetTitle("#phi_{#gamma}");
my.pho_timeVsPhiEB->GetYaxis()->SetTitle("Seed Crys Time(ns)");
my.pho_timeVsPhiEB->Draw("colz");
my.pho_timeVsPhiEB->Write();

my.pho_timeVsPhiEE->GetXaxis()->SetTitle("#phi_{#gamma}");
my.pho_timeVsPhiEE->GetYaxis()->SetTitle("Seed Crys Time(ns)");
my.pho_timeVsPhiEE->Draw("colz");
my.pho_timeVsPhiEE->Write();

my.pho_sigmaEtaEB->GetXaxis()->SetTitle("#sigma_{i#eta i#eta}");
my.pho_sigmaEtaEB->GetYaxis()->SetTitle("No. Events");
my.pho_sigmaEtaEB->Draw();
my.pho_sigmaEtaEB->Write();

my.pho_sigmaEtaEE->GetXaxis()->SetTitle("#sigma_{i#eta i#eta}");
my.pho_sigmaEtaEE->GetYaxis()->SetTitle("No. Events");
my.pho_sigmaEtaEE->Draw();
my.pho_sigmaEtaEE->Write();

my.pho_sminorEB->GetXaxis()->SetTitle("SMinor");
my.pho_sminorEB->GetYaxis()->SetTitle("Event Number");
my.pho_sminorEB->Draw();
my.pho_sminorEB->Write();

my.pho_smajorEB->GetXaxis()->SetTitle("SMajor");
my.pho_smajorEB->GetYaxis()->SetTitle("Event Number");
my.pho_smajorEB->Draw();
my.pho_smajorEB->Write();

my.pho_sminorEE->GetXaxis()->SetTitle("SMinor");
my.pho_sminorEE->GetYaxis()->SetTitle("Event Number");
my.pho_sminorEE->Draw();
my.pho_sminorEE->Write();

my.pho_smajorEE->GetXaxis()->SetTitle("SMajor");
my.pho_smajorEE->GetYaxis()->SetTitle("Event Number");
my.pho_smajorEE->Draw();
my.pho_smajorEE->Write();

my.pho_timeEB->GetXaxis()->SetTitle("seed Crys Time(ns)");
my.pho_timeEB->GetYaxis()->SetTitle("Event Number");
my.pho_timeEB->Draw();
my.pho_timeEB->Write();

my.pho_timeEE->GetXaxis()->SetTitle("Photon(seed Crys) Time(ns)");
my.pho_timeEE->GetYaxis()->SetTitle("Event Number");
my.pho_timeEE->Draw();
my.pho_timeEE->Write();

my.pho_timeVsCSCdphi->GetXaxis()->SetTitle("|#phi_{CSC Seg, #gamma}|");
my.pho_timeVsCSCdphi->GetYaxis()->SetTitle("seed Crys Time (ns)");
my.pho_timeVsCSCdphi->Draw();
my.pho_timeVsCSCdphi->Write();

my.pho_CSCdphi->GetXaxis()->SetTitle("|#phi_{CSC Seg, #gamma}|");
my.pho_CSCdphi->GetYaxis()->SetTitle("No. Events");
my.pho_CSCdphi->Draw();
my.pho_CSCdphi->Write();

my.pho_LN2timeEB->GetXaxis()->SetTitle("seed Crys Time(ns)");
my.pho_LN2timeEB->GetYaxis()->SetTitle("Event Number");
my.pho_LN2timeEB->Draw();
my.pho_LN2timeEB->Write();

my.pho_LN2GP2timeEB->GetXaxis()->SetTitle("seed Crys Time(ns)");
my.pho_LN2GP2timeEB->GetYaxis()->SetTitle("Event Number");
my.pho_LN2GP2timeEB->Draw();
my.pho_LN2GP2timeEB->Write();

my.pho_GP2timeEB->GetXaxis()->SetTitle("seed Crys Time(ns)");
my.pho_GP2timeEB->GetYaxis()->SetTitle("Event Number");
my.pho_GP2timeEB->Draw();
my.pho_GP2timeEB->Write();


my.pho_LN2timeEE->GetXaxis()->SetTitle("seed Crys Time(ns)");
my.pho_LN2timeEE->GetYaxis()->SetTitle("Event Number");
my.pho_LN2timeEE->Draw();
my.pho_LN2timeEE->Write();

my.pho_LN2GP2timeEE->GetXaxis()->SetTitle("seed Crys Time(ns)");
my.pho_LN2GP2timeEE->GetYaxis()->SetTitle("Event Number");
my.pho_LN2GP2timeEE->Draw();
my.pho_LN2GP2timeEE->Write();

my.pho_GP2timeEE->GetXaxis()->SetTitle("seed Crys Time(ns)");
my.pho_GP2timeEE->GetYaxis()->SetTitle("Event Number");
my.pho_GP2timeEE->Draw();
my.pho_GP2timeEE->Write();

my.pho_ATG2_sigmaEtaEB->GetXaxis()->SetTitle("#sigma_{i#eta i#eta}");
my.pho_ATG2_sigmaEtaEB->GetYaxis()->SetTitle("No. Events");
my.pho_ATG2_sigmaEtaEB->Draw();
my.pho_ATG2_sigmaEtaEB->Write();

my.pho_ATG2_sigmaEtaEE->GetXaxis()->SetTitle("#sigma_{i#eta i#eta}");
my.pho_ATG2_sigmaEtaEE->GetYaxis()->SetTitle("No. Events");
my.pho_ATG2_sigmaEtaEE->Draw();
my.pho_ATG2_sigmaEtaEE->Write();

my.pho_ATG2_sminorEB->GetXaxis()->SetTitle("SMinor");
my.pho_ATG2_sminorEB->GetYaxis()->SetTitle("Event Number");
my.pho_ATG2_sminorEB->Draw();
my.pho_ATG2_sminorEB->Write();

my.pho_ATG2_smajorEB->GetXaxis()->SetTitle("SMajor");
my.pho_ATG2_smajorEB->GetYaxis()->SetTitle("Event Number");
my.pho_ATG2_smajorEB->Draw();
my.pho_ATG2_smajorEB->Write();

my.pho_ATG2_sminorEE->GetXaxis()->SetTitle("SMinor");
my.pho_ATG2_sminorEE->GetYaxis()->SetTitle("Event Number");
my.pho_ATG2_sminorEE->Draw();
my.pho_ATG2_sminorEE->Write();

my.pho_ATG2_smajorEE->GetXaxis()->SetTitle("SMajor");
my.pho_ATG2_smajorEE->GetYaxis()->SetTitle("Event Number");
my.pho_ATG2_smajorEE->Draw();
my.pho_ATG2_smajorEE->Write();

my.pho_sigmaIeta->GetXaxis()->SetTitle("#sigma_{i#eta i#eta}");
my.pho_sigmaIeta->GetYaxis()->SetTitle("No. Events");
my.pho_sigmaIeta->Draw();
my.pho_sigmaIeta->Write();

my.phoetaVsphi->GetXaxis()->SetTitle("#eta_{#gamma}");
my.phoetaVsphi->GetYaxis()->SetTitle("#phi_{gamma}");
my.phoetaVsphi->Draw();
my.phoetaVsphi->Write();
/* Halo Stuff */
my.HEtimeVsPhoeta->GetXaxis()->SetTitle("#eta_{#gamma}");
my.HEtimeVsPhoeta->GetYaxis()->SetTitle("Seed crys Time(ns)");
my.HEtimeVsPhoeta->Draw("colz");
my.HEtimeVsPhoeta->Write();

my.HEtimeVsPhophi->GetXaxis()->SetTitle("#phi_{#gamma}");
my.HEtimeVsPhophi->GetYaxis()->SetTitle("Seed Crys Time(ns)");
my.HEtimeVsPhophi->Draw("colz");
my.HEtimeVsPhophi->Write();

my.HEhalo_timeVsHEdphi->GetXaxis()->SetTitle("#delta #phi_{HE, #gamma}");
my.HEhalo_timeVsHEdphi->GetYaxis()->SetTitle("Photon Time(ns)");
my.HEhalo_timeVsHEdphi->Draw("colz");
my.HEhalo_timeVsHEdphi->Write();

my.HEhalo_timeVsHEGdphi->GetXaxis()->SetTitle("#delta #phi_{HE, #gamma}");
my.HEhalo_timeVsHEGdphi->GetYaxis()->SetTitle("Photon Time(ns)");
my.HEhalo_timeVsHEGdphi->Draw("colz");
my.HEhalo_timeVsHEGdphi->Write();

my.HEhalo_timeVsHEradius->GetYaxis()->SetTitle("Photon Time");
my.HEhalo_timeVsHEradius->GetXaxis()->SetTitle("HE Radius(units)");
my.HEhalo_timeVsHEradius->Draw("colz");
my.HEhalo_timeVsHEradius->Write();

my.HEhalo_timeVsHErho->GetXaxis()->SetTitle("HE #rho");
my.HEhalo_timeVsHErho->GetYaxis()->SetTitle("Photon Time(ns)");
my.HEhalo_timeVsHErho->Draw("colz");
my.HEhalo_timeVsHErho->Write();

my.HEhalo_timeVsHEdphiEB->GetXaxis()->SetTitle("#delta #phi_{HE, #gamma}");
my.HEhalo_timeVsHEdphiEB->GetYaxis()->SetTitle("Photon Time(ns)");
my.HEhalo_timeVsHEdphiEB->Draw("colz");
my.HEhalo_timeVsHEdphiEB->Write();

my.HEhalo_timeVsHEdphiEE->GetXaxis()->SetTitle("#delta #phi_{HE ,#gamma}");
my.HEhalo_timeVsHEdphiEE->GetYaxis()->SetTitle("Photon Time(ns)");
my.HEhalo_timeVsHEdphiEE->Draw("colz");
my.HEhalo_timeVsHEdphiEE->Write();

my.HEtime->GetXaxis()->SetTitle("HE Time(ns) ");
my.HEtime->GetYaxis()->SetTitle("Num. Of Events");
my.HEtime->Draw();
my.HEtime->Write();

my.TimeREEHE->GetXaxis()->SetTitle(" Time Ratio EE/HE");
my.TimeREEHE->GetYaxis()->SetTitle("Num. Of Events");
my.TimeREEHE->Draw();
my.TimeREEHE->Write();

my.HEradius->GetXaxis()->SetTitle("HE Radius}");
my.HEradius->GetYaxis()->SetTitle("Num. Of Events");
my.HEradius->Draw();
my.HEradius->Write();

my.HEenergy->GetXaxis()->SetTitle("HE Energy(GeV)");
my.HEenergy->GetYaxis()->SetTitle("Num. Of Events");
my.HEenergy->Draw();
my.HEenergy->Write();

my.HErho->GetXaxis()->SetTitle("HE #rho");
my.HErho->GetYaxis()->SetTitle("Num. Of Events");
my.HErho->Draw();
my.HErho->Write();

my.HEdphi->GetXaxis()->SetTitle("#delta #phi{HE,#gamma}");
my.HEdphi->GetYaxis()->SetTitle("Num. Of Events");
my.HEdphi->Draw();
my.HEdphi->Write();

my.HEdphiEB->GetXaxis()->SetTitle("#delta #phi{HE,#gamma} EB");
my.HEdphiEB->GetYaxis()->SetTitle("Num. Of Events");
my.HEdphiEB->Draw();
my.HEdphiEB->Write();

my.HEdphiEE->GetXaxis()->SetTitle("#delta #phi{HE,#gamma} EE");
my.HEdphiEE->GetYaxis()->SetTitle("Num. Of Events");
my.HEdphiEE->Draw();
my.HEdphiEE->Write();

my.halo_phodrho->GetXaxis()->SetTitle("#delta#rho_{halo #gamma}");
my.halo_phodrho->GetYaxis()->SetTitle("No. Events");
my.halo_phodrho->Draw();
my.halo_phodrho->Write();

my.halo_phodphi->GetXaxis()->SetTitle("#delta#phi_{halo #gamma}");
my.halo_phodphi->GetYaxis()->SetTitle("No. Events");
my.halo_phodphi->Draw();
my.halo_phodphi->Write();

Hg.halo_etaVsphi->GetXaxis()->SetTitle("#eta_{Halo #gamma}");
Hg.halo_etaVsphi->GetYaxis()->SetTitle("#phi_{Halo #gamma}");
Hg.halo_etaVsphi->Draw();
Hg.halo_etaVsphi->Write();

Hg.halo_phiVsStime->GetXaxis()->SetTitle("#phi_{Halo #gamma}");
Hg.halo_phiVsStime->GetYaxis()->SetTitle("Seed Crys Time(ns)");
Hg.halo_phiVsStime->Draw();
Hg.halo_phiVsStime->Write();

Hg.halo_phiVsBCtime->GetXaxis()->SetTitle("#phi_{Halo #gamma}");
Hg.halo_phiVsBCtime->GetYaxis()->SetTitle("W.Av Seed BC Time(ns)");
Hg.halo_phiVsBCtime->Draw();
Hg.halo_phiVsBCtime->Write();

Hg.halo_phiVsSCtime->GetXaxis()->SetTitle("#phi_{Halo #gamma}");
Hg.halo_phiVsSCtime->GetYaxis()->SetTitle("W.Av SC Time(ns)");
Hg.halo_phiVsSCtime->Draw();
Hg.halo_phiVsSCtime->Write();

Hg.halo_etaVsStime->GetXaxis()->SetTitle("#eta_{Halo #gamma}");
Hg.halo_etaVsStime->GetYaxis()->SetTitle("Seed Crys Time(ns)");
Hg.halo_etaVsStime->Draw();
Hg.halo_etaVsStime->Write();

Hg.halo_etaVsBCtime->GetXaxis()->SetTitle("#eta_{Halo #gamma}");
Hg.halo_etaVsBCtime->GetYaxis()->SetTitle("W.Av Seed BC Time(ns)");
Hg.halo_etaVsBCtime->Draw();
Hg.halo_etaVsBCtime->Write();

Hg.halo_etaVsSCtime->GetXaxis()->SetTitle("#eta_{Halo #gamma}");
Hg.halo_etaVsSCtime->GetYaxis()->SetTitle("W.Av SC Time(ns)");
Hg.halo_etaVsSCtime->Draw();
Hg.halo_etaVsSCtime->Write();

Hg.halo_rhoVsphi->GetXaxis()->SetTitle("#rho_{Halo #gamma}");
Hg.halo_rhoVsphi->GetYaxis()->SetTitle("#phi_{Halo #gamma}");
Hg.halo_rhoVsphi->Draw();
Hg.halo_rhoVsphi->Write();


Hg.halo_nBC->GetXaxis()->SetTitle("No. BC_{Halo #gamma}");
Hg.halo_nBC->GetYaxis()->SetTitle("No. Events");
Hg.halo_nBC->Draw();
Hg.halo_nBC->Write();

Hg.halo_nXtalEB->GetXaxis()->SetTitle("No. Crys_{Halo #gamma}");
Hg.halo_nXtalEB->GetYaxis()->SetTitle("No. Events");
Hg.halo_nXtalEB->Draw();
Hg.halo_nXtalEB->Write();

Hg.halo_SSXEB->GetXaxis()->SetTitle("seedXtal SwissX of Halo #gamma SC}");
Hg.halo_SSXEB->GetYaxis()->SetTitle("No. Events");
Hg.halo_SSXEB->Draw();
Hg.halo_SSXEB->Write();

Hg.halo_rho->GetXaxis()->SetTitle("#deltaR{Halo #gamma}");
Hg.halo_rho->GetYaxis()->SetTitle("No. Events");
Hg.halo_rho->Draw();
Hg.halo_rho->Write();

Hg.halo_phi->GetXaxis()->SetTitle("#phi_{Halo #gamma}");
Hg.halo_phi->GetYaxis()->SetTitle("No. Events");
Hg.halo_phi->Draw();
Hg.halo_phi->Write();

Hg.halo_sigmaIeta->GetXaxis()->SetTitle("#sigma_{i#eta i#eta}^{Halo #gamma}");
Hg.halo_sigmaIeta->GetYaxis()->SetTitle("No. Events");
Hg.halo_sigmaIeta->Draw();
Hg.halo_sigmaIeta->Write();

//Hg.halo_phonBCratio->GetXaxis()->SetTitle("Ratio(No.BC_{#gamma}/No.BC_{Halo #gamma})");
//Hg.halo_phonBCratio->GetYaxis()->SetTitle("No. Events");
//Hg.halo_phonBCratio->Draw();
//Hg.halo_phonBCratio->Write();

//Hg.halo_phonXtalEBratio->GetXaxis()->SetTitle("Ratio(No.Crys_{#gamma}/No.Crys_{Halo #gamma})");
//Hg.halo_phonXtalEBratio->GetYaxis()->SetTitle("No. Events");
//Hg.halo_phonXtalEBratio->Draw();
//Hg.halo_phonXtalEBratio->Write();

//Hg.halo_TrksSbeta->GetXaxis()->SetTitle("No. Halo Trks Beta Small");
//Hg.halo_TrksSbeta->GetYaxis()->SetTitle("No. Events");
//Hg.halo_TrksSbeta->Draw();
//Hg.halo_TrksSbeta->Write();

//Hg.halo_nhalosegs->GetXaxis()->SetTitle("No.Of Halo Segments");
//Hg.halo_nhalosegs->GetYaxis()->SetTitle("No. Events");
//Hg.halo_nhalosegs->Draw();
//Hg.halo_nhalosegs->Write();

//Hg.halo_nOThits->GetXaxis()->SetTitle("No.Of OutOfTime Halo Hits");
//Hg.halo_nOThits->GetYaxis()->SetTitle("No. Events");
//Hg.halo_nOThits->Draw();
//Hg.halo_nOThits->Write();

//Hg.halo_nhalotrk->GetXaxis()->SetTitle("No.Of Halo Tracks");
//Hg.halo_nhalotrk->GetYaxis()->SetTitle("No. Events");
//Hg.halo_nhalotrk->Draw();
//Hg.halo_nhalotrk->Write();

Hg.halo_seedTime->GetXaxis()->SetTitle("Seed Crys Time_{Halo #gamma}(ns)");
Hg.halo_seedTime->GetYaxis()->SetTitle("No. Events");
Hg.halo_seedTime->Draw();
Hg.halo_seedTime->Write();

Hg.halo_wavBCtime->GetXaxis()->SetTitle("W.Ave BC Time_{Halo #gamma}(ns)");
Hg.halo_wavBCtime->GetYaxis()->SetTitle("No. Events");
Hg.halo_wavBCtime->Draw();
Hg.halo_wavBCtime->Write();

Hg.halo_wavSCtime->GetXaxis()->SetTitle("W.Av BC Time_{Halo #gamma}(ns)");
Hg.halo_wavSCtime->GetYaxis()->SetTitle("No. Events");
Hg.halo_wavSCtime->Draw();
Hg.halo_wavSCtime->Write();

// EB and EE Stuff
Hg.halo_timeVsEtaEB->GetXaxis()->SetTitle("#eta_{#gamma}");
Hg.halo_timeVsEtaEB->GetYaxis()->SetTitle("Seed crys Time(ns)");
Hg.halo_timeVsEtaEB->Draw("colz");
Hg.halo_timeVsEtaEB->Write();

Hg.halo_timeVsEtaEE->GetXaxis()->SetTitle("#eta_{#gamma}");
Hg.halo_timeVsEtaEE->GetYaxis()->SetTitle("Seed crys Time(ns)");
Hg.halo_timeVsEtaEE->Draw("colz");
Hg.halo_timeVsEtaEE->Write();

Hg.halo_timeVsPhiEB->GetXaxis()->SetTitle("#phi_{#gamma}");
Hg.halo_timeVsPhiEB->GetYaxis()->SetTitle("Seed Crys Time(ns)");
Hg.halo_timeVsPhiEB->Draw("colz");
Hg.halo_timeVsPhiEB->Write();

Hg.halo_timeVsPhiEE->GetXaxis()->SetTitle("#phi_{#gamma}");
Hg.halo_timeVsPhiEE->GetYaxis()->SetTitle("Seed Crys Time(ns)");
Hg.halo_timeVsPhiEE->Draw("colz");
Hg.halo_timeVsPhiEE->Write();

Hg.halo_sigmaEtaEB->GetXaxis()->SetTitle("#sigma_{i#eta i#eta}");
Hg.halo_sigmaEtaEB->GetYaxis()->SetTitle("No. Events");
Hg.halo_sigmaEtaEB->Draw();
Hg.halo_sigmaEtaEB->Write();

Hg.halo_sigmaEtaEE->GetXaxis()->SetTitle("#sigma_{i#eta i#eta}");
Hg.halo_sigmaEtaEE->GetYaxis()->SetTitle("No. Events");
Hg.halo_sigmaEtaEE->Draw();
Hg.halo_sigmaEtaEE->Write();

Hg.halo_sminorEB->GetXaxis()->SetTitle("SMinor");
Hg.halo_sminorEB->GetYaxis()->SetTitle("Event Number");
Hg.halo_sminorEB->Draw();
Hg.halo_sminorEB->Write();

Hg.halo_smajorEB->GetXaxis()->SetTitle("SMajor");
Hg.halo_smajorEB->GetYaxis()->SetTitle("Event Number");
Hg.halo_smajorEB->Draw();
Hg.halo_smajorEB->Write();

Hg.halo_sminorEE->GetXaxis()->SetTitle("SMinor");
Hg.halo_sminorEE->GetYaxis()->SetTitle("Event Number");
Hg.halo_sminorEE->Draw();
Hg.halo_sminorEE->Write();

Hg.halo_smajorEE->GetXaxis()->SetTitle("SMajor");
Hg.halo_smajorEE->GetYaxis()->SetTitle("Event Number");
Hg.halo_smajorEE->Draw();
Hg.halo_smajorEE->Write();

Hg.halo_timeEB->GetXaxis()->SetTitle("seed Crys Time(ns)");
Hg.halo_timeEB->GetYaxis()->SetTitle("Event Number");
Hg.halo_timeEB->Draw();
Hg.halo_timeEB->Write();

Hg.halo_timeEE->GetXaxis()->SetTitle("Photon(seed Crys) Time(ns)");
Hg.halo_timeEE->GetYaxis()->SetTitle("Event Number");
Hg.halo_timeEE->Draw();
Hg.halo_timeEE->Write();

Hg.halo_timeVsCSCdphi->GetXaxis()->SetTitle("|#phi_{CSC Seg, #gamma}|");
Hg.halo_timeVsCSCdphi->GetYaxis()->SetTitle("seed Crys Time (ns)");
Hg.halo_timeVsCSCdphi->Draw();
Hg.halo_timeVsCSCdphi->Write();

Hg.halo_CSCdphi->GetXaxis()->SetTitle("|#phi_{CSC Seg, #gamma}|");
Hg.halo_CSCdphi->GetYaxis()->SetTitle("No. Events");
Hg.halo_CSCdphi->Draw();
Hg.halo_CSCdphi->Write();

Hg.halo_LN2timeEB->GetXaxis()->SetTitle("seed Crys Time(ns)");
Hg.halo_LN2timeEB->GetYaxis()->SetTitle("Event Number");
Hg.halo_LN2timeEB->Draw();
Hg.halo_LN2timeEB->Write();

Hg.halo_LN2GP2timeEB->GetXaxis()->SetTitle("seed Crys Time(ns)");
Hg.halo_LN2GP2timeEB->GetYaxis()->SetTitle("Event Number");
Hg.halo_LN2GP2timeEB->Draw();
Hg.halo_LN2GP2timeEB->Write();

Hg.halo_GP2timeEB->GetXaxis()->SetTitle("seed Crys Time(ns)");
Hg.halo_GP2timeEB->GetYaxis()->SetTitle("Event Number");
Hg.halo_GP2timeEB->Draw();
Hg.halo_GP2timeEB->Write();


Hg.halo_LN2timeEE->GetXaxis()->SetTitle("seed Crys Time(ns)");
Hg.halo_LN2timeEE->GetYaxis()->SetTitle("Event Number");
Hg.halo_LN2timeEE->Draw();
Hg.halo_LN2timeEE->Write();

Hg.halo_LN2GP2timeEE->GetXaxis()->SetTitle("seed Crys Time(ns)");
Hg.halo_LN2GP2timeEE->GetYaxis()->SetTitle("Event Number");
Hg.halo_LN2GP2timeEE->Draw();
Hg.halo_LN2GP2timeEE->Write();

Hg.halo_GP2timeEE->GetXaxis()->SetTitle("seed Crys Time(ns)");
Hg.halo_GP2timeEE->GetYaxis()->SetTitle("Event Number");
Hg.halo_GP2timeEE->Draw();
Hg.halo_GP2timeEE->Write();

Hg.halo_ATG2_sigmaEtaEB->GetXaxis()->SetTitle("#sigma_{i#eta i#eta}");
Hg.halo_ATG2_sigmaEtaEB->GetYaxis()->SetTitle("No. Events");
Hg.halo_ATG2_sigmaEtaEB->Draw();
Hg.halo_ATG2_sigmaEtaEB->Write();

Hg.halo_ATG2_sigmaEtaEE->GetXaxis()->SetTitle("#sigma_{i#eta i#eta}");
Hg.halo_ATG2_sigmaEtaEE->GetYaxis()->SetTitle("No. Events");
Hg.halo_ATG2_sigmaEtaEE->Draw();
Hg.halo_ATG2_sigmaEtaEE->Write();

Hg.halo_ATG2_sminorEB->GetXaxis()->SetTitle("SMinor");
Hg.halo_ATG2_sminorEB->GetYaxis()->SetTitle("Event Number");
Hg.halo_ATG2_sminorEB->Draw();
Hg.halo_ATG2_sminorEB->Write();

Hg.halo_ATG2_smajorEB->GetXaxis()->SetTitle("SMajor");
Hg.halo_ATG2_smajorEB->GetYaxis()->SetTitle("Event Number");
Hg.halo_ATG2_smajorEB->Draw();
Hg.halo_ATG2_smajorEB->Write();

Hg.halo_ATG2_sminorEE->GetXaxis()->SetTitle("SMinor");
Hg.halo_ATG2_sminorEE->GetYaxis()->SetTitle("Event Number");
Hg.halo_ATG2_sminorEE->Draw();
Hg.halo_ATG2_sminorEE->Write();

Hg.halo_ATG2_smajorEE->GetXaxis()->SetTitle("SMajor");
Hg.halo_ATG2_smajorEE->GetYaxis()->SetTitle("Event Number");
Hg.halo_ATG2_smajorEE->Draw();
Hg.halo_ATG2_smajorEE->Write();

Hg.halo_num_phoEB->GetXaxis()->SetTitle("No.of Halo #gamma s");
Hg.halo_num_phoEB->GetYaxis()->SetTitle("Event Number");
Hg.halo_num_phoEB->Draw() ;
Hg.halo_num_phoEB->Write();

Hg.halo_num_phoEE->GetXaxis()->SetTitle("No.of Halo #gamma s");
Hg.halo_num_phoEE->GetYaxis()->SetTitle("Event Number");
Hg.halo_num_phoEE->Draw() ;
Hg.halo_num_phoEE->Write();

Hg.halo_num_jetEB->GetXaxis()->SetTitle("Number of jets");
Hg.halo_num_jetEB->GetYaxis()->SetTitle("Event Number");
Hg.halo_num_jetEB->Draw() ;
Hg.halo_num_jetEB->Write();

Hg.halo_num_jetEE->GetXaxis()->SetTitle("Number of jets");
Hg.halo_num_jetEE->GetYaxis()->SetTitle("Event Number");
Hg.halo_num_jetEE->Draw() ;
Hg.halo_num_jetEE->Write();

//Strange time Event Plots 
Lt.ltvtxX->GetXaxis()->SetTitle("X Vertex(cm)");
Lt.ltvtxX->Draw();
Lt.ltvtxX->Write();
Lt.ltvtxY->GetXaxis()->SetTitle("Y Vertex(cm)");
Lt.ltvtxY->Draw();
Lt.ltvtxY->Write();
Lt.ltvtxZ->GetXaxis()->SetTitle("Z Vertex(cm)");
Lt.ltvtxZ->Draw();
Lt.ltvtxZ->Write();
Lt.lteta->GetXaxis()->SetTitle("#eta");
Lt.lteta->Draw();
Lt.lteta->Write();
Lt.ltphi->GetXaxis()->SetTitle("#phi");
Lt.ltphi->Draw();
Lt.ltphi->Write();
Lt.ltEvtmet->GetXaxis()->SetTitle("MET(GeV)");
Lt.ltEvtmet->Draw();
Lt.ltEvtmet->Write();
Lt.ltEvtpt->GetXaxis()->SetTitle("#gamma Pt (GeV/c)");
Lt.ltEvtpt->Draw();
Lt.ltEvtpt->Write();

Lt.ltphoE->GetXaxis()->SetTitle("#gamma Energy (GeV)");
Lt.ltphoE->Draw();
Lt.ltphoE->Write();

Lt.ltnjets->GetXaxis()->SetTitle("Number of Jets");
Lt.ltnjets->Draw();
Lt.ltnjets->Write();
Lt.ltnpho->GetXaxis()->SetTitle("Number of #gamma s");
Lt.ltnpho->Draw();
Lt.ltnpho->Write();
Lt.ltnvtx->GetXaxis()->SetTitle("Number of Primary Vertices");
Lt.ltnvtx->Draw();
Lt.ltnvtx->Write();



//Single Vertex Event Plots 
Sv.svtxX->GetXaxis()->SetTitle("X Vertex(cm)");
Sv.svtxX->Draw();
Sv.svtxX->Write();
Sv.svtxY->GetXaxis()->SetTitle("Y Vertex(cm)");
Sv.svtxY->Draw();
Sv.svtxY->Write();
Sv.svtxZ->GetXaxis()->SetTitle("Z Vertex(cm)");
Sv.svtxZ->Draw();
Sv.svtxZ->Write();
Sv.svtxeta->GetXaxis()->SetTitle("#eta");
Sv.svtxeta->Draw();
Sv.svtxeta->Write();
Sv.svtxphi->GetXaxis()->SetTitle("#phi");
Sv.svtxphi->Draw();
Sv.svtxphi->Write();
Sv.svtxEvtmet->GetXaxis()->SetTitle("MET(GeV)");
Sv.svtxEvtmet->Draw();
Sv.svtxEvtmet->Write();
Sv.svtxEvtpt->GetXaxis()->SetTitle("#gamma Pt (GeV/c)");
Sv.svtxEvtpt->Draw();
Sv.svtxEvtpt->Write();
Sv.svtxnjets->GetXaxis()->SetTitle("Number of Jets");
Sv.svtxnjets->Draw();
Sv.svtxnjets->Write();
Sv.svtxnpho->GetXaxis()->SetTitle("Number of #gamma s");
Sv.svtxnpho->Draw();
Sv.svtxnpho->Write();
Sv.svtxnvtx->GetXaxis()->SetTitle("Number of Primary Vertices");
Sv.svtxnvtx->Draw();
Sv.svtxnvtx->Write();

EEUntag = f->mkdir("EEUntagable");
EEUntag->cd();

my.EEP_Untag_Halo_pho_time->GetXaxis()->SetTitle("Photon Time(ns)");
my.EEP_Untag_Halo_pho_time->GetYaxis()->SetTitle("Event Number");
my.EEP_Untag_Halo_pho_time->Draw();
my.EEP_Untag_Halo_pho_time->Write();

my.EEM_Untag_Halo_pho_time->GetXaxis()->SetTitle("Photon Time(ns)");
my.EEM_Untag_Halo_pho_time->GetYaxis()->SetTitle("Event Number");
my.EEM_Untag_Halo_pho_time->Draw();
my.EEM_Untag_Halo_pho_time->Write();

my.EEP_Untag_Halo_pho_eta->GetXaxis()->SetTitle("#eta_{#gamma}");
my.EEP_Untag_Halo_pho_eta->GetYaxis()->SetTitle("Event Number");
my.EEP_Untag_Halo_pho_eta->Draw();
my.EEP_Untag_Halo_pho_eta->Write();

my.EEM_Untag_Halo_pho_eta->GetXaxis()->SetTitle("#eta_{#gamma}");
my.EEM_Untag_Halo_pho_eta->GetYaxis()->SetTitle("Event Number");
my.EEM_Untag_Halo_pho_eta->Draw();
my.EEM_Untag_Halo_pho_eta->Write();

my.EEP_Untag_Halo_pho_phi->GetXaxis()->SetTitle("#phi_{#gamma}");
my.EEP_Untag_Halo_pho_phi->GetYaxis()->SetTitle("Event Number");
my.EEP_Untag_Halo_pho_phi->Draw();
my.EEP_Untag_Halo_pho_phi->Write();

my.EEM_Untag_Halo_pho_phi->GetXaxis()->SetTitle("#phi_{#gamma}");
my.EEM_Untag_Halo_pho_phi->GetYaxis()->SetTitle("Event Number");
my.EEM_Untag_Halo_pho_phi->Draw();
my.EEM_Untag_Halo_pho_phi->Write();

my.EEM_Untag_Halo_pho_cscdphi->GetXaxis()->SetTitle("#delta#phi(CSC Seg,#gamma");
my.EEM_Untag_Halo_pho_cscdphi->GetYaxis()->SetTitle("Event Number");
my.EEM_Untag_Halo_pho_cscdphi->Draw();
my.EEM_Untag_Halo_pho_cscdphi->Write();

my.EEP_Untag_Halo_pho_cscdphi->GetXaxis()->SetTitle("#delta#phi(CSC Seg,#gamma");
my.EEP_Untag_Halo_pho_cscdphi->GetYaxis()->SetTitle("Event Number");
my.EEP_Untag_Halo_pho_cscdphi->Draw();
my.EEP_Untag_Halo_pho_cscdphi->Write();

my.EEP_Untag_Halo_pho_met->GetXaxis()->SetTitle("MET(GeV/c)");
my.EEP_Untag_Halo_pho_met->GetYaxis()->SetTitle("Event Number");
my.EEP_Untag_Halo_pho_met->Draw();
my.EEP_Untag_Halo_pho_met->Write();

my.EEM_Untag_Halo_pho_met->GetXaxis()->SetTitle("MET(GeV/c)");
my.EEM_Untag_Halo_pho_met->GetYaxis()->SetTitle("Event Number");
my.EEM_Untag_Halo_pho_met->Draw();
my.EEM_Untag_Halo_pho_met->Write();

my.EEP_Untag_Halo_pho_pt->GetXaxis()->SetTitle("Pt(GeV/c)");
my.EEP_Untag_Halo_pho_pt->GetYaxis()->SetTitle("Event Number");
my.EEP_Untag_Halo_pho_pt->Draw();
my.EEP_Untag_Halo_pho_pt->Write();

my.EEM_Untag_Halo_pho_pt->GetXaxis()->SetTitle("Pt(GeV/c)");
my.EEM_Untag_Halo_pho_pt->GetYaxis()->SetTitle("Event Number");
my.EEM_Untag_Halo_pho_pt->Draw();
my.EEM_Untag_Halo_pho_pt->Write();

my.EEP_Untag_Halo_pho_ncrys->GetXaxis()->SetTitle("NCrys");
my.EEP_Untag_Halo_pho_ncrys->GetYaxis()->SetTitle("Event Number");
my.EEP_Untag_Halo_pho_ncrys->Draw();
my.EEP_Untag_Halo_pho_ncrys->Write();

my.EEM_Untag_Halo_pho_ncrys->GetXaxis()->SetTitle("NCrys");
my.EEM_Untag_Halo_pho_ncrys->GetYaxis()->SetTitle("Event Number");
my.EEM_Untag_Halo_pho_ncrys->Draw();
my.EEM_Untag_Halo_pho_ncrys->Write();

my.EEP_Untag_Halo_pho_metVstime->GetXaxis()->SetTitle("MET(GeV/c)");
my.EEP_Untag_Halo_pho_metVstime->GetYaxis()->SetTitle("Seed Time(ns)");
my.EEP_Untag_Halo_pho_metVstime->Draw();
my.EEP_Untag_Halo_pho_metVstime->Write();

my.EEM_Untag_Halo_pho_metVstime->GetXaxis()->SetTitle("MET(GeV/c)");
my.EEM_Untag_Halo_pho_metVstime->GetYaxis()->SetTitle("Seed Time(ns)");
my.EEM_Untag_Halo_pho_metVstime->Draw();
my.EEM_Untag_Halo_pho_metVstime->Write();

//Jet info
my.Jseedtime1->GetXaxis()->SetTitle("Time(ns)");
my.Jseedtime1->GetYaxis()->SetTitle("Event Number");
my.Jseedtime1->Draw();
my.Jseedtime1->Write();

my.Jseedtime2->GetXaxis()->SetTitle("Time(ns)");
my.Jseedtime2->GetYaxis()->SetTitle("Event Number");
my.Jseedtime2->Draw();
my.Jseedtime2->Write();

my.JseedE->GetXaxis()->SetTitle("Energy(GeV)");
my.JseedE->GetYaxis()->SetTitle("Event Number");
my.JseedE->Draw();
my.JseedE->Write();

my.JSClusdR->GetXaxis()->SetTitle("#delta R");
my.JSClusdR->GetYaxis()->SetTitle("Event Number");
my.JSClusdR->Draw();
my.JSClusdR->Write();

my.JseedBCtime->GetXaxis()->SetTitle("Time[ns]");
my.JseedBCtime->GetYaxis()->SetTitle("Event Number");
my.JseedBCtime->Draw();
my.JseedBCtime->Write();

my.JWaveBCtime->GetXaxis()->SetTitle("Wave. Time[ns]");
my.JWaveBCtime->GetYaxis()->SetTitle("Event Number");
my.JWaveBCtime->Draw();
my.JWaveBCtime->Write();

my.JnCrys->GetXaxis()->SetTitle("NCrys");
my.JnCrys->GetYaxis()->SetTitle("Event Number");
my.JnCrys->Draw();
my.JnCrys->Write();

my.Jnspike->GetXaxis()->SetTitle("# Spikes");
my.Jnspike->GetYaxis()->SetTitle("Event Number");
my.Jnspike->Draw();
my.Jnspike->Write();


my.JEcalEmEr->GetXaxis()->SetTitle("Energy(GeV)");
my.JEcalEmEr->GetYaxis()->SetTitle("Event Number");
my.JEcalEmEr->Draw();
my.JEcalEmEr->Write();

my.Jseedtime2VsEta->GetXaxis()->SetTitle("#eta");
my.Jseedtime2VsEta->GetYaxis()->SetTitle("Time(ns)");
my.Jseedtime2VsEta->Draw();
my.Jseedtime2VsEta->Write();

my.Jseedtime2VsPhi->GetXaxis()->SetTitle("#phi");
my.Jseedtime2VsPhi->GetYaxis()->SetTitle("Time(ns)");
my.Jseedtime2VsPhi->Draw();
my.Jseedtime2VsPhi->Write();

my.JseedtimeVsEnergy->GetXaxis()->SetTitle("Seed Energy(GeV)");
my.JseedtimeVsEnergy->GetYaxis()->SetTitle("Seed  Crys Time(ns)");
my.JseedtimeVsEnergy->Draw();
my.JseedtimeVsEnergy->Write();

my.JseedtimeChi2->GetXaxis()->SetTitle("Seed Time {#chi}^{2}");
my.JseedtimeChi2->GetYaxis()->SetTitle("Event Number");
my.JseedtimeChi2->Draw();
my.JseedtimeChi2->Write();

my.JseedOOtChi2->GetXaxis()->SetTitle("Seed OO Time {#chi}^{2}");
my.JseedOOtChi2->GetYaxis()->SetTitle("Event Number");
my.JseedOOtChi2->Draw();
my.JseedOOtChi2->Write();

my.Jseedtime2VsBCEnergy->GetXaxis()->SetTitle("Seed BC Energy(GeV)");
my.Jseedtime2VsBCEnergy->GetYaxis()->SetTitle("Seed Crys Time(ns)");
my.Jseedtime2VsBCEnergy->Draw();
my.Jseedtime2VsBCEnergy->Write();

my.Jseedtime2VsBCEt->GetXaxis()->SetTitle("Seed BC Et(GeV)");
my.Jseedtime2VsBCEt->GetYaxis()->SetTitle("Seed Crys Time(ns)");
my.Jseedtime2VsBCEt->Draw();
my.Jseedtime2VsBCEt->Write();

my.Jseedtime2VsBCPt->GetXaxis()->SetTitle("Seed BC Pt(GeV)");
my.Jseedtime2VsBCPt->GetYaxis()->SetTitle("Seed Crys Time(ns)");
my.Jseedtime2VsBCPt->Draw();
my.Jseedtime2VsBCPt->Write();

my.JwavetimeVsBCEnergy->GetXaxis()->SetTitle("Seed BC Energy(GeV)");
my.JwavetimeVsBCEnergy->GetYaxis()->SetTitle("W.Ave Time(ns)");
my.JwavetimeVsBCEnergy->Draw();
my.JwavetimeVsBCEnergy->Write();

my.JseedEVsEta->GetXaxis()->SetTitle("#eta_{PFJ}");
my.JseedEVsEta->GetYaxis()->SetTitle("Seed Crys Energy(GeV)");
my.JseedEVsEta->Draw();
my.JseedEVsEta->Write();

my.JseedBCEVsEta->GetXaxis()->SetTitle("#eta_{PFJ}");
my.JseedBCEVsEta->GetYaxis()->SetTitle("Seed BC Energy(GeV)");
my.JseedBCEVsEta->Draw();
my.JseedBCEVsEta->Write();

my.JseedBCEVsPhi->GetXaxis()->SetTitle("#phi_{PFJ}");
my.JseedBCEVsPhi->GetYaxis()->SetTitle("Seed BC Energy(GeV)");
my.JseedBCEVsPhi->Draw();
my.JseedBCEVsPhi->Write();

my.JnUMjets->GetXaxis()->SetTitle("Num UnMatched Jets");
my.JnUMjets->GetYaxis()->SetTitle("Event Number");
my.JnUMjets->Draw();
my.JnUMjets->Write();


my.Jseedtime2EB->GetXaxis()->SetTitle("Time(ns)");
my.Jseedtime2EB->GetYaxis()->SetTitle("Event Number");
my.Jseedtime2EB->Draw();
my.Jseedtime2EB->Write();

my.Jseedtime2EE->GetXaxis()->SetTitle("Time(ns)");
my.Jseedtime2EE->GetYaxis()->SetTitle("Event Number");
my.Jseedtime2EE->Draw();
my.Jseedtime2EE->Write();


Dphoton = f->mkdir("BkgEst");
Dphoton->cd();

my.EEP_pho_time->GetXaxis()->SetTitle("Photon Time(ns)");
my.EEP_pho_time->GetYaxis()->SetTitle("Event Number");
my.EEP_pho_time->Draw();
my.EEP_pho_time->Write();

my.EEM_pho_time->GetXaxis()->SetTitle("Photon Time(ns)");
my.EEM_pho_time->GetYaxis()->SetTitle("Event Number");
my.EEM_pho_time->Draw();
my.EEM_pho_time->Write();

my.EEP_pho_eta->GetXaxis()->SetTitle("#eta_{#gamma}");
my.EEP_pho_eta->GetYaxis()->SetTitle("Event Number");
my.EEP_pho_eta->Draw();
my.EEP_pho_eta->Write();

my.EEM_pho_eta->GetXaxis()->SetTitle("#eta_{#gamma}");
my.EEM_pho_eta->GetYaxis()->SetTitle("Event Number");
my.EEM_pho_eta->Draw();
my.EEM_pho_eta->Write();

my.ALL_EEP_pho_time->GetXaxis()->SetTitle("Photon Time(ns)");
my.ALL_EEP_pho_time->GetYaxis()->SetTitle("Event Number");
my.ALL_EEP_pho_time->Draw();
my.ALL_EEP_pho_time->Write();

my.ALL_EEM_pho_time->GetXaxis()->SetTitle("Photon Time(ns)");
my.ALL_EEM_pho_time->GetYaxis()->SetTitle("Event Number");
my.ALL_EEM_pho_time->Draw();
my.ALL_EEM_pho_time->Write();

my.ALL_EEP_pho_eta->GetXaxis()->SetTitle("#eta_{#gamma}");
my.ALL_EEP_pho_eta->GetYaxis()->SetTitle("Event Number");
my.ALL_EEP_pho_eta->Draw();
my.ALL_EEP_pho_eta->Write();

my.ALL_EEM_pho_eta->GetXaxis()->SetTitle("#eta_{#gamma}");
my.ALL_EEM_pho_eta->GetYaxis()->SetTitle("Event Number");
my.ALL_EEM_pho_eta->Draw();
my.ALL_EEM_pho_eta->Write();

my.EEP_ZPphi_pho_time->GetXaxis()->SetTitle("Photon Time(ns)");
my.EEP_ZPphi_pho_time->GetYaxis()->SetTitle("Event Number");
my.EEP_ZPphi_pho_time->Draw();
my.EEP_ZPphi_pho_time->Write();

my.EEM_ZPphi_pho_time->GetXaxis()->SetTitle("Photon Time(ns)");
my.EEM_ZPphi_pho_time->GetYaxis()->SetTitle("Event Number");
my.EEM_ZPphi_pho_time->Draw();
my.EEM_ZPphi_pho_time->Write();

my.EEM_ZPphi_pho_eta->GetXaxis()->SetTitle("#eta_{#gamma}");
my.EEM_ZPphi_pho_eta->GetYaxis()->SetTitle("Event Number");
my.EEM_ZPphi_pho_eta->Draw();
my.EEM_ZPphi_pho_eta->Write();

my.EEP_ZPphi_pho_eta->GetXaxis()->SetTitle("#eta_{#gamma}");
my.EEP_ZPphi_pho_eta->GetYaxis()->SetTitle("Event Number");
my.EEP_ZPphi_pho_eta->Draw();
my.EEP_ZPphi_pho_eta->Write();

my.EEP_phoTimeVsRho->GetXaxis()->SetTitle("#rho_{#gamma}");
my.EEP_phoTimeVsRho->GetYaxis()->SetTitle("Seed Crys Time(ns)");
my.EEP_phoTimeVsRho->Draw("colz");
my.EEP_phoTimeVsRho->Write();

my.EEP_phoTimeVsR->GetXaxis()->SetTitle("RadiusZ_{#gamma}");
my.EEP_phoTimeVsR->GetYaxis()->SetTitle("Seed Crys Time(ns)");
my.EEP_phoTimeVsR->Draw("colz");
my.EEP_phoTimeVsR->Write();


my.EEM_phoTimeVsRho->GetXaxis()->SetTitle("#rho_{#gamma}");
my.EEM_phoTimeVsRho->GetYaxis()->SetTitle("Seed Crys Time(ns)");
my.EEM_phoTimeVsRho->Draw("colz");
my.EEM_phoTimeVsRho->Write();

my.EEM_phoTimeVsR->GetXaxis()->SetTitle("Radiusz_{#gamma}");
my.EEM_phoTimeVsR->GetYaxis()->SetTitle("Seed Crys Time(ns)");
my.EEM_phoTimeVsR->Draw("colz");
my.EEM_phoTimeVsR->Write();


my.EEP_phoTimeVsPhi->GetXaxis()->SetTitle("#phi_{#gamma}");
my.EEP_phoTimeVsPhi->GetYaxis()->SetTitle("Seed Crys Time(ns)");
my.EEP_phoTimeVsPhi->Draw("colz");
my.EEP_phoTimeVsPhi->Write();

my.EEM_phoTimeVsPhi->GetXaxis()->SetTitle("#phi_{#gamma}");
my.EEM_phoTimeVsPhi->GetYaxis()->SetTitle("Seed Crys Time(ns)");
my.EEM_phoTimeVsPhi->Draw("colz");
my.EEM_phoTimeVsPhi->Write();

my.EEM_phoRho->GetXaxis()->SetTitle("#rho_{#gamma}");
my.EEM_phoRho->GetYaxis()->SetTitle("No. Of Events");
my.EEM_phoRho->Draw();
my.EEM_phoRho->Write();

my.EEP_phoRho->GetXaxis()->SetTitle("#rho_{#gamma}");
my.EEP_phoRho->GetYaxis()->SetTitle("No. Of Events");
my.EEP_phoRho->Draw();
my.EEP_phoRho->Write();

my.EEM_phoR->GetXaxis()->SetTitle("RadiusZ_{#gamma}");
my.EEM_phoR->GetYaxis()->SetTitle("No. Of Events");
my.EEM_phoR->Draw();
my.EEM_phoR->Write();

my.EEP_phoR->GetXaxis()->SetTitle("RadiusZ_{#gamma}");
my.EEP_phoR->GetYaxis()->SetTitle("No. Of Events");
my.EEP_phoR->Draw();
my.EEP_phoR->Write();

my.EEM_phoPhi->GetXaxis()->SetTitle("#phi_{#gamma}");
my.EEM_phoPhi->GetYaxis()->SetTitle("No. Of Events");
my.EEM_phoPhi->Draw();
my.EEM_phoPhi->Write();

my.EEP_phoPhi->GetXaxis()->SetTitle("#phi_{#gamma}");
my.EEP_phoPhi->GetYaxis()->SetTitle("No. Of Events");
my.EEP_phoPhi->Draw();
my.EEP_phoPhi->Write();


my.EEM_pho_time_NIn_Halo_Win->GetXaxis()->SetTitle("Time(ns)");
my.EEM_pho_time_NIn_Halo_Win->GetYaxis()->SetTitle("Event Number");
my.EEM_pho_time_NIn_Halo_Win->Draw();
my.EEM_pho_time_NIn_Halo_Win->Write();

my.EEP_pho_time_NIn_Halo_Win->GetXaxis()->SetTitle("Time(ns)");
my.EEP_pho_time_NIn_Halo_Win->GetYaxis()->SetTitle("Event Number");
my.EEP_pho_time_NIn_Halo_Win->Draw();
my.EEP_pho_time_NIn_Halo_Win->Write();

my.EEM_pho_pt_NIn_Halo_Win->GetXaxis()->SetTitle("Pt(GeV/c)");
my.EEM_pho_pt_NIn_Halo_Win->GetYaxis()->SetTitle("Event Number");
my.EEM_pho_pt_NIn_Halo_Win->Draw();
my.EEM_pho_pt_NIn_Halo_Win->Write();

my.EEP_pho_pt_NIn_Halo_Win->GetXaxis()->SetTitle("Pt(GeV/c)");
my.EEP_pho_pt_NIn_Halo_Win->GetYaxis()->SetTitle("Event Number");
my.EEP_pho_pt_NIn_Halo_Win->Draw();
my.EEP_pho_pt_NIn_Halo_Win->Write();

my.EEM_pho_eta_NIn_Halo_Win->GetXaxis()->SetTitle("#eta");
my.EEM_pho_eta_NIn_Halo_Win->GetYaxis()->SetTitle("Event Number");
my.EEM_pho_eta_NIn_Halo_Win->Draw();
my.EEM_pho_eta_NIn_Halo_Win->Write();

my.EEP_pho_eta_NIn_Halo_Win->GetXaxis()->SetTitle("#eta");
my.EEP_pho_eta_NIn_Halo_Win->GetYaxis()->SetTitle("Event Number");
my.EEP_pho_eta_NIn_Halo_Win->Draw();
my.EEP_pho_eta_NIn_Halo_Win->Write();

my.EEM_pho_ncrys_NIn_Halo_Win->GetXaxis()->SetTitle("NCrys");
my.EEM_pho_ncrys_NIn_Halo_Win->GetYaxis()->SetTitle("Event Number");
my.EEM_pho_ncrys_NIn_Halo_Win->Draw();
my.EEM_pho_ncrys_NIn_Halo_Win->Write();

my.EEP_pho_ncrys_NIn_Halo_Win->GetXaxis()->SetTitle("NCrys");
my.EEP_pho_ncrys_NIn_Halo_Win->GetYaxis()->SetTitle("Event Number");
my.EEP_pho_ncrys_NIn_Halo_Win->Draw();
my.EEP_pho_ncrys_NIn_Halo_Win->Write();

// Halo ones
my.EEM_pho_time_In_Halo_Win->GetXaxis()->SetTitle("Time(ns)");
my.EEM_pho_time_In_Halo_Win->GetYaxis()->SetTitle("Event Number");
my.EEM_pho_time_In_Halo_Win->Draw();
my.EEM_pho_time_In_Halo_Win->Write();

my.EEP_pho_time_In_Halo_Win->GetXaxis()->SetTitle("Time(ns)");
my.EEP_pho_time_In_Halo_Win->GetYaxis()->SetTitle("Event Number");
my.EEP_pho_time_In_Halo_Win->Draw();
my.EEP_pho_time_In_Halo_Win->Write();

my.EEM_pho_pt_In_Halo_Win->GetXaxis()->SetTitle("Pt(GeV/c)");
my.EEM_pho_pt_In_Halo_Win->GetYaxis()->SetTitle("Event Number");
my.EEM_pho_pt_In_Halo_Win->Draw();
my.EEM_pho_pt_In_Halo_Win->Write();

my.EEP_pho_pt_In_Halo_Win->GetXaxis()->SetTitle("Pt(GeV/c)");
my.EEP_pho_pt_In_Halo_Win->GetYaxis()->SetTitle("Event Number");
my.EEP_pho_pt_In_Halo_Win->Draw();
my.EEP_pho_pt_In_Halo_Win->Write();

my.EEM_pho_eta_In_Halo_Win->GetXaxis()->SetTitle("#eta");
my.EEM_pho_eta_In_Halo_Win->GetYaxis()->SetTitle("Event Number");
my.EEM_pho_eta_In_Halo_Win->Draw();
my.EEM_pho_eta_In_Halo_Win->Write();

my.EEP_pho_eta_In_Halo_Win->GetXaxis()->SetTitle("#eta");
my.EEP_pho_eta_In_Halo_Win->GetYaxis()->SetTitle("Event Number");
my.EEP_pho_eta_In_Halo_Win->Draw();
my.EEP_pho_eta_In_Halo_Win->Write();

my.EEM_pho_ncrys_In_Halo_Win->GetXaxis()->SetTitle("NCrys");
my.EEM_pho_ncrys_In_Halo_Win->GetYaxis()->SetTitle("Event Number");
my.EEM_pho_ncrys_In_Halo_Win->Draw();
my.EEM_pho_ncrys_In_Halo_Win->Write();

my.EEP_pho_ncrys_In_Halo_Win->GetXaxis()->SetTitle("NCrys");
my.EEP_pho_ncrys_In_Halo_Win->GetYaxis()->SetTitle("Event Number");
my.EEP_pho_ncrys_In_Halo_Win->Draw();
my.EEP_pho_ncrys_In_Halo_Win->Write();

my.EEM_CSC_dphi_In_1ns->GetXaxis()->SetTitle("#delta#phi(CSC Seg,#gamma");
my.EEM_CSC_dphi_In_1ns->GetYaxis()->SetTitle("Event Number");
my.EEM_CSC_dphi_In_1ns->Draw();
my.EEM_CSC_dphi_In_1ns->Write();

my.EEP_CSC_dphi_In_1ns->GetXaxis()->SetTitle("#delta#phi(CSC Seg,#gamma");
my.EEP_CSC_dphi_In_1ns->GetYaxis()->SetTitle("Event Number");
my.EEP_CSC_dphi_In_1ns->Draw();
my.EEP_CSC_dphi_In_1ns->Write();

my.EEM_CSC_dphi_NIn_1ns->GetXaxis()->SetTitle("#delta#phi(CSC Seg,#gamma");
my.EEM_CSC_dphi_NIn_1ns->GetYaxis()->SetTitle("Event Number");
my.EEM_CSC_dphi_NIn_1ns->Draw();
my.EEM_CSC_dphi_NIn_1ns->Write();

my.EEP_CSC_dphi_NIn_1ns->GetXaxis()->SetTitle("#delta#phi(CSC Seg,#gamma");
my.EEP_CSC_dphi_NIn_1ns->GetYaxis()->SetTitle("Event Number");
my.EEP_CSC_dphi_NIn_1ns->Draw();
my.EEP_CSC_dphi_NIn_1ns->Write();





my.phoTimeNegPhi_3WinEB->GetXaxis()->SetTitle("Time(ns)");
my.phoTimeNegPhi_3WinEB->GetYaxis()->SetTitle("No. Events");
my.phoTimeNegPhi_3WinEB->Draw();
my.phoTimeNegPhi_3WinEB->Write();

my.phoTimePosPhi_3WinEB->GetXaxis()->SetTitle("Time(ns)");
my.phoTimePosPhi_3WinEB->GetYaxis()->SetTitle("No. Events");
my.phoTimePosPhi_3WinEB->Draw();
my.phoTimePosPhi_3WinEB->Write();

my.phoTimePhi_ZeroWinEB->GetXaxis()->SetTitle("Time(ns)");
my.phoTimePhi_ZeroWinEB->GetYaxis()->SetTitle("No. Events");
my.phoTimePhi_ZeroWinEB->Draw();
my.phoTimePhi_ZeroWinEB->Write();

for(int ii=0; ii <32; ii++){

    my.cscdphiInTimeSlice[ii]->GetXaxis()->SetTitle("|#delta #phi|");
    my.cscdphiInTimeSlice[ii]->GetYaxis()->SetTitle("No. Events");
    my.cscdphiInTimeSlice[ii]->Draw();
    my.cscdphiInTimeSlice[ii]->Write();

    my.NCrysInTimeSlice[ii]->GetXaxis()->SetTitle("NCrys");
    my.NCrysInTimeSlice[ii]->GetYaxis()->SetTitle("No. Events");
    my.NCrysInTimeSlice[ii]->Draw();
    my.NCrysInTimeSlice[ii]->Write();
}

my.phoTimeVsE->GetXaxis()->SetTitle("Photon Energy(GeV)");
my.phoTimeVsE->GetYaxis()->SetTitle("Seed crys Time(ns)");
my.phoTimeVsE->Draw("colz");
my.phoTimeVsE->Write();

my.phoTimeVsEta->GetXaxis()->SetTitle("#eta_{#gamma}");
my.phoTimeVsEta->GetYaxis()->SetTitle("Seed crys Time(ns)");
my.phoTimeVsEta->Draw("colz");
my.phoTimeVsEta->Write();

my.phoTimeVsPhi->GetXaxis()->SetTitle("#phi_{#gamma}");
my.phoTimeVsPhi->GetYaxis()->SetTitle("Seed Crys Time(ns)");
my.phoTimeVsPhi->Draw("colz");
my.phoTimeVsPhi->Write();


my.phoTimeVsNCrys->GetXaxis()->SetTitle("NCrys");
my.phoTimeVsNCrys->GetYaxis()->SetTitle("Seed Crys Time(ns)");
my.phoTimeVsNCrys->Draw("colz");
my.phoTimeVsNCrys->Write();

my.phoTimeVsPt->GetXaxis()->SetTitle("P_{T}^{#gamma}(GeV)");
my.phoTimeVsPt->GetYaxis()->SetTitle("Seed Crys Time(ns)");
my.phoTimeVsPt->Draw("colz");
my.phoTimeVsPt->Write();

my.phoTimeVsMet->GetXaxis()->SetTitle("E_{T}^{Miss}");
my.phoTimeVsMet->GetYaxis()->SetTitle("Seed Crys Time(ns)");
my.phoTimeVsMet->Draw("colz");
my.phoTimeVsMet->Write();

my.phoEtaVsNCrys->GetXaxis()->SetTitle("NCrys");
my.phoEtaVsNCrys->GetYaxis()->SetTitle("#eta_{#gamma}");
my.phoEtaVsNCrys->Draw("colz");
my.phoEtaVsNCrys->Write();

my.phoPhiVsNCrys->GetXaxis()->SetTitle("NCrys");
my.phoPhiVsNCrys->GetYaxis()->SetTitle("#phi_{#gamma}");
my.phoPhiVsNCrys->Draw("colz");
my.phoPhiVsNCrys->Write();

my.phoPtVsNCrys->GetXaxis()->SetTitle("NCrys");
my.phoPtVsNCrys->GetYaxis()->SetTitle("P_{T}^{#gamma}");
my.phoPtVsNCrys->Draw("colz");
my.phoPtVsNCrys->Write();

my.MetVsNCrys->GetXaxis()->SetTitle("NCrys");
my.MetVsNCrys->GetYaxis()->SetTitle("E_{T}^{Miss}");
my.MetVsNCrys->Draw("colz");
my.MetVsNCrys->Write();

my.phoEtaVsCSCdphi->GetXaxis()->SetTitle("#delta#phi(cscSeg,#gamma)");
my.phoEtaVsCSCdphi->GetYaxis()->SetTitle("#eta_{#gamma}");
my.phoEtaVsCSCdphi->Draw("colz");
my.phoEtaVsCSCdphi->Write();

my.phoPhiVsCSCdphi->GetXaxis()->SetTitle("#delta#phi(cscSeg,#gamma)");
my.phoPhiVsCSCdphi->GetYaxis()->SetTitle("#phi_{#gamma}");
my.phoPhiVsCSCdphi->Draw("colz");
my.phoPhiVsCSCdphi->Write();

my.phoPtVsCSCdphi->GetXaxis()->SetTitle("#delta#phi(cscSeg,#gamma)");
my.phoPtVsCSCdphi->GetYaxis()->SetTitle("P_{T}^{#gamma}");
my.phoPtVsCSCdphi->Draw("colz");
my.phoPtVsCSCdphi->Write();

my.pho_ptVscscdphiEB->GetXaxis()->SetTitle("#delta#phi(cscSeg,#gamma)");
my.pho_ptVscscdphiEB->GetYaxis()->SetTitle("P_{T}^{#gamma}");
my.pho_ptVscscdphiEB->Draw("colz");
my.pho_ptVscscdphiEB->Write();

my.MetVsCSCdphi->GetXaxis()->SetTitle("#delta#phi(cscSeg,#gamma)");
my.MetVsCSCdphi->GetYaxis()->SetTitle("E_{T}^{Miss}");
my.MetVsCSCdphi->Draw("colz");
my.MetVsCSCdphi->Write();

my.NCrysVsCSCdphi->GetXaxis()->SetTitle("#delta#phi(cscSeg,#gamma)");
my.NCrysVsCSCdphi->GetYaxis()->SetTitle("NCrys");
my.NCrysVsCSCdphi->Draw("colz");
my.NCrysVsCSCdphi->Write();

my.phoPtVsMet->GetXaxis()->SetTitle("E_{T}^{Miss}");
my.phoPtVsMet->GetYaxis()->SetTitle("P_{T}^{#gamma}");
my.phoPtVsMet->Draw("colz");
my.phoPtVsMet->Write();

// Spike & Halo Studies
my.eta_gVstimeEB->GetXaxis()->SetTitle("#eta_{#gamma}");
my.eta_gVstimeEB->GetYaxis()->SetTitle("Seed crys Time(ns)");
my.eta_gVstimeEB->Draw("colz");
my.eta_gVstimeEB->Write();

my.n_gEB->GetXaxis()->SetTitle("N_{#gamma}");
my.n_gEB->GetYaxis()->SetTitle("No. Events");
my.n_gEB->Draw();
my.n_gEB->Write();

my.n_jEB->GetXaxis()->SetTitle("N_{Jets}");
my.n_jEB->GetYaxis()->SetTitle("No. Events");
my.n_jEB->Draw();
my.n_jEB->Write();

my.g_nCrysEB->GetXaxis()->SetTitle("NCrys");
my.g_nCrysEB->GetYaxis()->SetTitle("No. Events");
my.g_nCrysEB->Draw();
my.g_nCrysEB->Write();

my.g_timeEB->GetXaxis()->SetTitle("Time(ns)");
my.g_timeEB->GetYaxis()->SetTitle("No. Events");
my.g_timeEB->Draw();
my.g_timeEB->Write();

my.g_cscdphiEB->GetXaxis()->SetTitle("|#delta #phi|");
my.g_cscdphiEB->GetYaxis()->SetTitle("No. Events");
my.g_cscdphiEB->Draw();
my.g_cscdphiEB->Write();

my.g_ptEB->GetXaxis()->SetTitle("Pt_{#gamma}(GeV)");
my.g_ptEB->GetYaxis()->SetTitle("No. Events");
my.g_ptEB->Draw();
my.g_ptEB->Write();

my.g_metEB->GetXaxis()->SetTitle("E_{T}^{Miss}(GeV)");
my.g_metEB->GetYaxis()->SetTitle("No. Events");
my.g_metEB->Draw();
my.g_metEB->Write();


HaloReg = f->mkdir("PureHalo");
HaloReg->cd();

my.eta_hVstimeEB->GetXaxis()->SetTitle("#eta_{#gamma}");
my.eta_hVstimeEB->GetYaxis()->SetTitle("Seed crys Time(ns)");
my.eta_hVstimeEB->Draw("colz");
my.eta_hVstimeEB->Write();

my.n_hEB->GetXaxis()->SetTitle("N_{#gamma}");
my.n_hEB->GetYaxis()->SetTitle("No. Events");
my.n_hEB->Draw();
my.n_hEB->Write();

my.n_jhEB->GetXaxis()->SetTitle("N_{Jets}");
my.n_jhEB->GetYaxis()->SetTitle("No. Events");
my.n_jhEB->Draw();
my.n_jhEB->Write();

my.h_nCrysEB->GetXaxis()->SetTitle("NCrys");
my.h_nCrysEB->GetYaxis()->SetTitle("No. Events");
my.h_nCrysEB->Draw();
my.h_nCrysEB->Write();

my.h_timeEB->GetXaxis()->SetTitle("Time(ns)");
my.h_timeEB->GetYaxis()->SetTitle("No. Events");
my.h_timeEB->Draw();
my.h_timeEB->Write();

my.h_cscdphiEB->GetXaxis()->SetTitle("|#delta #phi|");
my.h_cscdphiEB->GetYaxis()->SetTitle("No. Events");
my.h_cscdphiEB->Draw();
my.h_cscdphiEB->Write();

my.h_ptEB->GetXaxis()->SetTitle("Pt_{#gamma}(GeV)");
my.h_ptEB->GetYaxis()->SetTitle("No. Events");
my.h_ptEB->Draw();
my.h_ptEB->Write();

my.h_metEB->GetXaxis()->SetTitle("E_{T}^{Miss}(GeV)");
my.h_metEB->GetYaxis()->SetTitle("No. Events");
my.h_metEB->Draw();
my.h_metEB->Write();



SpikeReg = f->mkdir("PureSpike");
SpikeReg->cd();

my.eta_spkVstimeEB->GetXaxis()->SetTitle("#eta_{#gamma}");
my.eta_spkVstimeEB->GetYaxis()->SetTitle("Seed crys Time(ns)");
my.eta_spkVstimeEB->Draw("colz");
my.eta_spkVstimeEB->Write();

my.n_spkEB->GetXaxis()->SetTitle("N_{#gamma}");
my.n_spkEB->GetYaxis()->SetTitle("No. Events");
my.n_spkEB->Draw();
my.n_spkEB->Write();

my.n_jspkEB->GetXaxis()->SetTitle("N_{Jets}");
my.n_jspkEB->GetYaxis()->SetTitle("No. Events");
my.n_jspkEB->Draw();
my.n_jspkEB->Write();

my.spk_nCrysEB->GetXaxis()->SetTitle("NCrys");
my.spk_nCrysEB->GetYaxis()->SetTitle("No. Events");
my.spk_nCrysEB->Draw();
my.spk_nCrysEB->Write();

my.spk_timeEB->GetXaxis()->SetTitle("Time(ns)");
my.spk_timeEB->GetYaxis()->SetTitle("No. Events");
my.spk_timeEB->Draw();
my.spk_timeEB->Write();

my.spk_cscdphiEB->GetXaxis()->SetTitle("|#delta #phi|");
my.spk_cscdphiEB->GetYaxis()->SetTitle("No. Events");
my.spk_cscdphiEB->Draw();
my.spk_cscdphiEB->Write();

my.spk_ptEB->GetXaxis()->SetTitle("Pt_{#gamma}(GeV)");
my.spk_ptEB->GetYaxis()->SetTitle("No. Events");
my.spk_ptEB->Draw();
my.spk_ptEB->Write();

my.spk_metEB->GetXaxis()->SetTitle("E_{T}^{Miss}(GeV)");
my.spk_metEB->GetYaxis()->SetTitle("No. Events");
my.spk_metEB->Draw();
my.spk_metEB->Write();


SpikeInPhoReg = f->mkdir("SpikeInPho");
SpikeInPhoReg->cd();

my.eta_spkInphoVstimeEB->GetXaxis()->SetTitle("#eta_{#gamma}");
my.eta_spkInphoVstimeEB->GetYaxis()->SetTitle("Seed crys Time(ns)");
my.eta_spkInphoVstimeEB->Draw("colz");
my.eta_spkInphoVstimeEB->Write();

my.n_spkInphoEB->GetXaxis()->SetTitle("N_{#gamma}");
my.n_spkInphoEB->GetYaxis()->SetTitle("No. Events");
my.n_spkInphoEB->Draw();
my.n_spkInphoEB->Write();

my.n_jspkInphoEB->GetXaxis()->SetTitle("N_{Jets}");
my.n_jspkInphoEB->GetYaxis()->SetTitle("No. Events");
my.n_jspkInphoEB->Draw();
my.n_jspkInphoEB->Write();

my.spkInpho_nCrysEB->GetXaxis()->SetTitle("NCrys");
my.spkInpho_nCrysEB->GetYaxis()->SetTitle("No. Events");
my.spkInpho_nCrysEB->Draw();
my.spkInpho_nCrysEB->Write();

my.spkInpho_timeEB->GetXaxis()->SetTitle("Time(ns)");
my.spkInpho_timeEB->GetYaxis()->SetTitle("No. Events");
my.spkInpho_timeEB->Draw();
my.spkInpho_timeEB->Write();

my.spkInpho_cscdphiEB->GetXaxis()->SetTitle("|#delta #phi|");
my.spkInpho_cscdphiEB->GetYaxis()->SetTitle("No. Events");
my.spkInpho_cscdphiEB->Draw();
my.spkInpho_cscdphiEB->Write();

my.spkInpho_ptEB->GetXaxis()->SetTitle("Pt_{#gamma}(GeV)");
my.spkInpho_ptEB->GetYaxis()->SetTitle("No. Events");
my.spkInpho_ptEB->Draw();
my.spkInpho_ptEB->Write();

my.spkInpho_metEB->GetXaxis()->SetTitle("E_{T}^{Miss}(GeV)");
my.spkInpho_metEB->GetYaxis()->SetTitle("No. Events");
my.spkInpho_metEB->Draw();
my.spkInpho_metEB->Write();




BkgEst1 = f->mkdir("BackGndEst1");
BkgEst1->cd();


my.eb_reg->GetYaxis()->SetTitle("ECAL Time{#gamma}");
my.eb_reg->GetXaxis()->SetTitle("MET(GeV)");
my.eb_reg->Draw();
my.eb_reg->Write();

my.eb_regA->GetYaxis()->SetTitle("ECAL Time{#gamma}");
my.eb_regA->GetXaxis()->SetTitle("MET(GeV)");
my.eb_regA->Draw();
my.eb_regA->Write();

my.eb_regB->GetYaxis()->SetTitle("ECAL Time{#gamma}");
my.eb_regB->GetXaxis()->SetTitle("MET(GeV)");
my.eb_regB->Draw();
my.eb_regB->Write();

my.eb_regC->GetYaxis()->SetTitle("ECAL Time{#gamma}");
my.eb_regC->GetXaxis()->SetTitle("MET(GeV)");
my.eb_regC->Draw();
my.eb_regC->Write();

my.eb_regD->GetYaxis()->SetTitle("ECAL Time{#gamma}");
my.eb_regD->GetXaxis()->SetTitle("MET(GeV)");
my.eb_regD->Draw();
my.eb_regD->Write();

my.eb_ptime->GetXaxis()->SetTitle("Ecal Time_{#gamma}");
my.eb_ptime->GetYaxis()->SetTitle("No. Events");
my.eb_ptime->Draw();
my.eb_ptime->Write();

my.eb_hptime->GetXaxis()->SetTitle("Ecal Time_{Halo #gamma}");
my.eb_hptime->GetYaxis()->SetTitle("No. Events");
my.eb_hptime->Draw();
my.eb_hptime->Write();

my.eb_spike_ptime->GetXaxis()->SetTitle("Ecal Time_{Spike #gamma}");
my.eb_spike_ptime->GetYaxis()->SetTitle("No. Events");
my.eb_spike_ptime->Draw();
my.eb_spike_ptime->Write();

my.eb_qcd_ptime->GetXaxis()->SetTitle("Ecal Time_{QCD #gamma}");
my.eb_qcd_ptime->GetYaxis()->SetTitle("No. Events");
my.eb_qcd_ptime->Draw();
my.eb_qcd_ptime->Write();

my.eb_low_metTime->GetXaxis()->SetTitle("Ecal Time_{#gamma}");
my.eb_low_metTime->GetYaxis()->SetTitle("No. Events");
my.eb_low_metTime->Draw();
my.eb_low_metTime->Write();

my.eb_high_metTime->GetXaxis()->SetTitle("Ecal Time_{#gamma}");
my.eb_high_metTime->GetYaxis()->SetTitle("No. Events");
my.eb_high_metTime->Draw();
my.eb_high_metTime->Write();

my.eb_pSWX->GetXaxis()->SetTitle("SwissX_{ #gamma}");
my.eb_pSWX->GetYaxis()->SetTitle("No. Events");
my.eb_pSWX->Draw();
my.eb_pSWX->Write();

my.eb_hpSWX->GetXaxis()->SetTitle("SwissX_{ Halo #gamma}");
my.eb_hpSWX->GetYaxis()->SetTitle("No. Events");
my.eb_hpSWX->Draw();
my.eb_hpSWX->Write();

my.eb_spike_pSWX->GetXaxis()->SetTitle("SwissX_{Spike #gamma}");
my.eb_spike_pSWX->GetYaxis()->SetTitle("No. Events");
my.eb_spike_pSWX->Draw();
my.eb_spike_pSWX->Write();

my.eb_qcd_pSWX->GetXaxis()->SetTitle("SwissX_{QCD #gamma}");
my.eb_qcd_pSWX->GetYaxis()->SetTitle("No. Events");
my.eb_qcd_pSWX->Draw();
my.eb_qcd_pSWX->Write();

my.eb_pnXtal->GetXaxis()->SetTitle("No. Xtals_{ #gamma}");
my.eb_pnXtal->GetYaxis()->SetTitle("No. Events");
my.eb_pnXtal->Draw();
my.eb_pnXtal->Write();

my.eb_hpnXtal->GetXaxis()->SetTitle("No. Xtals_{Halo #gamma}");
my.eb_hpnXtal->GetYaxis()->SetTitle("No. Events");
my.eb_hpnXtal->Draw();
my.eb_hpnXtal->Write();


my.eb_spike_pnXtal->GetXaxis()->SetTitle("No. Xtals_{Spike #gamma}");
my.eb_spike_pnXtal->GetYaxis()->SetTitle("No. Events");
my.eb_spike_pnXtal->Draw();
my.eb_spike_pnXtal->Write();

my.eb_qcd_pnXtal->GetXaxis()->SetTitle("No. Xtals_{QCD #gamma}");
my.eb_qcd_pnXtal->GetYaxis()->SetTitle("No. Events");
my.eb_qcd_pnXtal->Draw();
my.eb_qcd_pnXtal->Write();

my.eb_pcscdPhi->GetXaxis()->SetTitle("CSC #delta #Phi_{ #gamma}");
my.eb_pcscdPhi->GetYaxis()->SetTitle("No. Events");
my.eb_pcscdPhi->Draw();
my.eb_pcscdPhi->Write();

my.eb_hpcscdPhi->GetXaxis()->SetTitle("CSC #delta #Phi_{Halo #gamma}");
my.eb_hpcscdPhi->GetYaxis()->SetTitle("No. Events");
my.eb_hpcscdPhi->Draw();
my.eb_hpcscdPhi->Write();

my.eb_spike_pcscdPhi->GetXaxis()->SetTitle("CSC #delta #Phi_{ Spike #gamma}");
my.eb_spike_pcscdPhi->GetYaxis()->SetTitle("No. Events");
my.eb_spike_pcscdPhi->Draw();
my.eb_spike_pcscdPhi->Write();

my.eb_qcd_pcscdPhi->GetXaxis()->SetTitle("CSC #delta #Phi_{QCD #gamma}");
my.eb_qcd_pcscdPhi->GetYaxis()->SetTitle("No. Events");
my.eb_qcd_pcscdPhi->Draw();
my.eb_qcd_pcscdPhi->Write();

my.eb_met0->GetXaxis()->SetTitle("E_{T}^{Miss}(GeV)");
my.eb_met0->GetYaxis()->SetTitle("No. Events");
my.eb_met0->Draw();
my.eb_met0->Write();

my.eb_met1->GetXaxis()->SetTitle("E_{T}^{Miss}GeV)");
my.eb_met1->GetYaxis()->SetTitle("No. Events");
my.eb_met1->Draw();
my.eb_met1->Write();

my.eb_met2->GetXaxis()->SetTitle("E_{T}^{Miss}(GeV)");
my.eb_met2->GetYaxis()->SetTitle("No. Events");
my.eb_met2->Draw();
my.eb_met2->Write();

my.eb_met3->GetXaxis()->SetTitle("E_{T}^{Miss}(GeV)");
my.eb_met3->GetYaxis()->SetTitle("No. Events");
my.eb_met3->Draw();
my.eb_met3->Write();

my.eb_time0->GetXaxis()->SetTitle("Time_{#gamma}(ns)");
my.eb_time0->GetYaxis()->SetTitle("No. Events");
my.eb_time0->Draw();
my.eb_time0->Write();

my.eb_time1->GetXaxis()->SetTitle("Time_{#gamma}(ns)");
my.eb_time1->GetYaxis()->SetTitle("No. Events");
my.eb_time1->Draw();
my.eb_time1->Write();

my.eb_time2->GetXaxis()->SetTitle("Time_{#gamma}(ns)");
my.eb_time2->GetYaxis()->SetTitle("No. Events");
my.eb_time2->Draw();
my.eb_time2->Write();

my.eb_time3->GetXaxis()->SetTitle("Time_{#gamma}(ns)");
my.eb_time3->GetYaxis()->SetTitle("No. Events");
my.eb_time3->Draw();
my.eb_time3->Write();

my.eb_pPt->GetXaxis()->SetTitle("Pt_{#gamma}(GeV)");
my.eb_pPt->GetYaxis()->SetTitle("No. Events");
my.eb_pPt->Draw();
my.eb_pPt->Write();

my.eb_hpPt->GetXaxis()->SetTitle("Pt_{Halo #gamma}(GeV)");
my.eb_hpPt->GetYaxis()->SetTitle("No. Events");
my.eb_hpPt->Draw();
my.eb_hpPt->Write();

my.eb_spike_pPt->GetXaxis()->SetTitle("Pt_{Spike #gamma}(GeV)");
my.eb_spike_pPt->GetYaxis()->SetTitle("No. Events");
my.eb_spike_pPt->Draw();
my.eb_spike_pPt->Write();

my.eb_qcd_pPt->GetXaxis()->SetTitle("Pt_{QCD #gamma}(GeV)");
my.eb_qcd_pPt->GetYaxis()->SetTitle("No. Events");
my.eb_qcd_pPt->Draw();
my.eb_qcd_pPt->Write();

my.eb_pMET->GetXaxis()->SetTitle("E_{T}^{Miss}(GeV)");
my.eb_pMET->GetYaxis()->SetTitle("No. Events");
my.eb_pMET->Draw();
my.eb_pMET->Write();

my.eb_hpMET->GetXaxis()->SetTitle("E_{T}^{Miss}(GeV)");
my.eb_hpMET->GetYaxis()->SetTitle("No. Events");
my.eb_hpMET->Draw();
my.eb_hpMET->Write();

my.eb_spike_pMET->GetXaxis()->SetTitle("E_{T}^{Miss}(GeV)");
my.eb_spike_pMET->GetYaxis()->SetTitle("No. Events");
my.eb_spike_pMET->Draw();
my.eb_spike_pMET->Write();

my.eb_qcd_pMET->GetXaxis()->SetTitle("E_{T}^{Miss}(GeV)");
my.eb_qcd_pMET->GetYaxis()->SetTitle("No. Events");
my.eb_qcd_pMET->Draw();
my.eb_qcd_pMET->Write();

my.eb_pNjets->GetXaxis()->SetTitle("No. Jets");
my.eb_pNjets->GetYaxis()->SetTitle("No. Events");
my.eb_pNjets->Draw();
my.eb_pNjets->Write();

my.eb_hpNjets->GetXaxis()->SetTitle("No. Jets");
my.eb_hpNjets->GetYaxis()->SetTitle("No. Events");
my.eb_hpNjets->Draw();
my.eb_hpNjets->Write();

my.eb_spike_pNjets->GetXaxis()->SetTitle("No. Jets");
my.eb_spike_pNjets->GetYaxis()->SetTitle("No. Events");
my.eb_spike_pNjets->Draw();
my.eb_spike_pNjets->Write();

my.eb_qcd_pNjets->GetXaxis()->SetTitle("No. Jets");
my.eb_qcd_pNjets->GetYaxis()->SetTitle("No. Events");
my.eb_qcd_pNjets->Draw();
my.eb_qcd_pNjets->Write();
} // End of Fxn Write hist


//Fxn to Make Plots
void TestGen::Make_Plots(){
// Now Make Plots
   TCanvas*  c1 = new TCanvas("c1","", 800, 600);
   c1->SetFillColor(10);
   c1->SetFillColor(10);
   gStyle->SetOptStat("emriou");
   //c1->SetLogy();

   // Photon Pt distribution
   c1->cd();
   c1->SetLogy();
   gStyle->SetStatY(0.95);
   gStyle->SetStatTextColor(1);
   my.h_g1Pt->SetLineColor(1) ;
   my.h_g1Pt->GetXaxis()->SetTitle("Photon Pt(GeV)");
   my.h_g1Pt->GetYaxis()->SetTitle("Event Number");

   my.h_g1Pt->Draw() ;
   c1->Update();

   TString plotname1 = hfolder + "PhotonPt." +plotType ;
   c1->Print( plotname1 );
   c1->SetLogy(1);

   // Photon Time
   c1->cd() ;
   gStyle->SetStatY(0.95);
   my.h_Time->GetXaxis()->SetTitle("Photon Time(ns)");
   my.h_Time->GetYaxis()->SetTitle("Event Number");
   my.h_Time->Draw() ;
   c1->Update();
   plotname1 = hfolder + "PhotonTime." + plotType ;
   c1->Print( plotname1 );

   // Photon W Ave Seed BC Time
   c1->cd() ;
   gStyle->SetStatY(0.95);
   my.WAveSeedBCphotime->GetXaxis()->SetTitle("Photon ( W Ave Seed BC) Time(ns)");
   my.WAveSeedBCphotime->GetYaxis()->SetTitle("Event Number");
   my.WAveSeedBCphotime->Draw() ;
   c1->Update();
   plotname1 = hfolder + "PhotonSeedBCWAveTime." + plotType ;
   c1->Print( plotname1 );

   c1->cd() ;
   gStyle->SetStatY(0.95);
   my.AveSCphotime->GetXaxis()->SetTitle("Photon( W Ave SC) Time(ns)");
   my.AveSCphotime->GetYaxis()->SetTitle("Event Number");
   my.AveSCphotime->Draw() ;
   c1->Update();
   plotname1 = hfolder + "PhotonWAveSCTime." + plotType ;
   c1->Print( plotname1 );


// Event Met
   c1->cd() ;
   gStyle->SetStatY(0.95);
   c1->SetLogy(1);
my.evt_met->GetXaxis()->SetTitle("E_{T}^{Miss}(GeV)");
my.evt_met->GetYaxis()->SetTitle("No. Events");

   my.evt_met->Draw() ;
   c1->Update();
   plotname1 = hfolder + "EventMet." + plotType ;
 //  c1->SetLogy(1)
   c1->Print( plotname1 );

// Photon sMinor
   c1->cd() ;
   gStyle->SetStatY(0.95);
   my.ph_smin->Draw() ;
   c1->Update();
   plotname1 = hfolder + "PhotonsMinor." + plotType ;
   c1->Print( plotname1 );

// Photon EcalIso
   c1->cd() ;
   gStyle->SetStatY(0.95);
   my.pho_EcalIso->GetXaxis()->SetTitle("#gamma EcalIso");
   my.pho_EcalIso->GetYaxis()->SetTitle("No. Events");
   my.pho_EcalIso->Draw() ;
   c1->Update();
   plotname1 = hfolder + "PhotonEcalIso." + plotType ;
   c1->Print( plotname1 );


// Photon HcallIso
   c1->cd() ;
   gStyle->SetStatY(0.95);
   my.pho_HcalIso->GetXaxis()->SetTitle("#gamm Hcal Iso");
   my.pho_HcalIso->GetYaxis()->SetTitle("No. Events");
   my.pho_HcalIso->Draw() ;
   c1->Update();
   plotname1 = hfolder + "PhotonHcalIso." + plotType ;
   c1->Print( plotname1 );


// Photon TrackIso
   c1->cd() ;
   gStyle->SetStatY(0.95);
   my.pho_TrkIso->Draw() ;
   my.pho_TrkIso->GetXaxis()->SetTitle("#gamma TrackIso");
   my.pho_TrkIso->GetYaxis()->SetTitle("No. Events");
   c1->Update();
   plotname1 = hfolder + "PhotonTrkIso." + plotType ;
   c1->Print( plotname1 );


// Photon  2012 HCAL Iso
//   c1->cd() ;
//   gStyle->SetStatY(0.95);
//   my.hcal_Iso->GetXaxis()->SetTitle("#gamma 2012 HcalIso");
//   my.hcal_Iso->GetYaxis()->SetTitle("Event Number");

 //  my.hcal_Iso->Draw() ;
 //  c1->Update();
 //  plotname1 = hfolder + "Photon_2012_HcalIso." + plotType ;
 //  c1->Print( plotname1 );

// Photon sMajor
   c1->cd() ;
   gStyle->SetStatY(0.95);
   my.ph_smaj->GetXaxis()->SetTitle("#gamma SMajor");
   my.ph_smaj->GetYaxis()->SetTitle("No. Events");

   my.ph_smaj->Draw() ;
   c1->Update();
   plotname1 = hfolder + "PhotonsMajor." + plotType ;
   c1->Print( plotname1 );

// Photon Energy dist
   c1->cd() ;
   gStyle->SetStatY(0.95);
   my.ph_e->GetXaxis()->SetTitle("E_{#gamma}(GeV)");
   my.ph_e->GetYaxis()->SetTitle("No. Events");

   my.ph_e->Draw() ;
   c1->Update();
   plotname1 = hfolder + "PhotonEnergy." + plotType ;
   c1->Print( plotname1 );

// Photon Z Position
   c1->cd() ;
   gStyle->SetStatY(0.95);
   my.ph_z->Draw() ;
   c1->Update();
   plotname1 = hfolder + "PhotonZ." + plotType ;
   c1->Print( plotname1 );


// PU or Nvertices
   c1->cd() ;
   gStyle->SetStatY(0.95);
   my.pu_vtx->GetXaxis()->SetTitle("NVertex");
   my.pu_vtx->GetYaxis()->SetTitle("No. Events");
   my.pu_vtx->Draw() ;
   c1->Update();
   plotname1 = hfolder + "PUStudy." + plotType ;
   c1->Print( plotname1 );

// Photon Eta
   c1->cd() ;
   gStyle->SetStatY(0.95);
   my.ph_eta->Draw() ;
   c1->Update();
   plotname1 = hfolder + "PhotonEta." + plotType ;
   c1->Print( plotname1 );

// Photon Phi
   c1->cd() ;
   gStyle->SetStatY(0.95);
   my.ph_phi->Draw() ;
   c1->Update();
   plotname1 = hfolder + "PhotonPhi." + plotType ;
   c1->Print( plotname1 );

// Leading Jet Eta
   c1->cd() ;
   gStyle->SetStatY(0.95);
   my.jet_eta->Draw() ;
   c1->Update();
   plotname1 = hfolder + "JetEta." + plotType ;
   c1->Print( plotname1 );

// Leading Jet Phi
   c1->cd() ;
   gStyle->SetStatY(0.95);
   my.jet_phi->Draw() ;
   c1->Update();
   plotname1 = hfolder + "JetPhi." + plotType ;
   c1->Print( plotname1 );

// Photon - Jet Eta
   c1->cd() ;
   gStyle->SetStatY(0.95);
   my.jp_deta->Draw() ;
   c1->Update();
   plotname1 = hfolder + "JetPhtonDEta." + plotType ;
   c1->Print( plotname1 );

// Photon -Jet Phi
   c1->cd() ;
   gStyle->SetStatY(0.95);
   my.jp_dphi->Draw() ;
   c1->Update();
   plotname1 = hfolder + "PhotonJetDPhi." + plotType ;
   c1->Print( plotname1 );

// Number of Jet Dist
   c1->cd() ;
   gStyle->SetStatY(0.95);
 my.njets->GetXaxis()->SetTitle("No. Jets");
 my.njets->GetYaxis()->SetTitle("No. Events");

   my.njets->Draw() ;
   c1->Update();
   plotname1 = hfolder + "NumberOfJets." + plotType ;
   c1->Print( plotname1 );

// Number of Photon Dist
   c1->cd() ;
   gStyle->SetStatY(0.95);
   my.npho->GetXaxis()->SetTitle("N_{#gamma}");
   my.npho->GetYaxis()->SetTitle("No. Events");

   my.npho->Draw() ;
   c1->Update();
   plotname1 = hfolder + "NumberOfPhotons." + plotType ;
   c1->Print( plotname1 );

// Leading Jet Pt dist
   c1->cd() ;
   gStyle->SetStatY(0.95);
  my.j_pt->GetXaxis()->SetTitle("Pt_{Jet}(GeV)");
  my.j_pt->GetYaxis()->SetTitle("Event Number");
   my.j_pt->Draw() ;
   c1->Update();
   plotname1 = hfolder + "JetPt." + plotType ;
   c1->Print( plotname1 );

	// Met Direction	
	c1->cd() ;
	gStyle->SetStatY(0.95);
	my.mettheta->Draw();
	c1->Update();
	plotname1 = hfolder + "MetTheta." + plotType ;
	c1->Print(plotname1);

	//Met-Photon Direction
   c1->cd() ;
   gStyle->SetStatY(0.95);

   my.phomet_thetadiff->GetXaxis()->SetTitle("Photon-Gravitino Angle Difference(radians)");
   my.phomet_thetadiff->GetYaxis()->SetTitle("No. Events");
   my.phomet_thetadiff->Draw() ;
   c1->Update();
   plotname1 = hfolder + "Met_PhotonThetaDiff." + plotType ;
   c1->Print( plotname1 );

    //Photon Hadronic Energy over Total Energy Ratio
   c1->cd() ;
   gStyle->SetStatY(0.95);
   my.ph_HoverE->Draw() ;
   c1->Update();
   plotname1 = hfolder + "PhotonHadOverE." + plotType ;
   c1->Print( plotname1 );

   // Transverse Mass of Neutralino
   c1->cd() ;
   gStyle->SetStatY(0.95);
   my.MassNt->GetXaxis()->SetTitle("M_{NLSP}(GeV)");
   my.MassNt->GetYaxis()->SetTitle("Event Number");
   my.MassNt->Draw() ;
   c1->Update();
   plotname1 = hfolder + "NeutTMass." + plotType ;
   c1->Print( plotname1 );

   // Photon Angular Dist
   c1->cd() ;
   gStyle->SetStatY(0.95);
   my.pho_angle->GetXaxis()->SetTitle("Photon Angle(radians)");
   my.pho_angle->GetYaxis()->SetTitle("Event Number");
   my.pho_angle->Draw() ;
   c1->Update();
   plotname1 = hfolder + "PhotonAngle." + plotType ;
   c1->Print( plotname1 );

   
   c1->cd() ; 
   gStyle->SetStatY(0.95);
   my.photimeVsPU->GetXaxis()->SetTitle("Number of Vertices");
   my.photimeVsPU->GetYaxis()->SetTitle("Photon Time(ns)");
   my.photimeVsPU->Draw("colz") ;
   c1->Update();
   c1->SetLogy();
   plotname1 = hfolder + "PhotonTimeVsPU." + plotType ;
   c1->Print( plotname1 );

   c1->cd() ;
   gStyle->SetStatY(0.95);
   my.metVsPU->GetXaxis()->SetTitle("Number of Vertices");
   my.metVsPU->GetYaxis()->SetTitle("E_{T}^{Miss}(GeV)");
   my.metVsPU->Draw("colz") ;
   c1->Update();
   c1->SetLogy();
   plotname1 = hfolder + "METVsPU." + plotType ;
   c1->Print( plotname1 );

// Photon Time Vs Eta
   c1->cd() ;
   gStyle->SetStatY(0.95);
   my.phoTimeVsEta->GetXaxis()->SetTitle("#eta_{#gamma}");
   my.phoTimeVsEta->GetYaxis()->SetTitle("Time_{#gamma}(ns)");
   my.phoTimeVsEta->Draw("colz") ;
   c1->Update();
   c1->SetLogy();
   plotname1 = hfolder + "PhotonTimeVsEtaDist." + plotType ;
   c1->Print( plotname1 );

// Photon Time Vs Energy
   c1->cd() ;
   gStyle->SetStatY(0.95);
   my.phoTimeVsE->GetXaxis()->SetTitle("E_{#gamma}(GeV)");
   my.phoTimeVsE->GetYaxis()->SetTitle("Photon Time(ns)");
   my.phoTimeVsE->Draw("colz") ;
   c1->Update();
   c1->SetLogy();
   plotname1 = hfolder + "PhotonTimeVsEnergy." + plotType ;
   c1->Print( plotname1 );

// Photon Time Vs  Phi
   c1->cd() ;
   gStyle->SetStatY(0.95);
   my.phoTimeVsPhi->GetXaxis()->SetTitle("#phi_{#gamma}");
   my.phoTimeVsPhi->GetYaxis()->SetTitle("Time_{#gamma}(ns)");
   my.phoTimeVsPhi->Draw("colz") ;
   c1->Update();
   c1->SetLogy();
   plotname1 = hfolder + "PhotonTimeVsPhiDist." + plotType ;
   c1->Print( plotname1 );

} // EoF Make_Plots


//***********/ Fuction Doing Analyzing /*********//
// analysis template
void TestGen::ReadTree( string dataName ) { 
   TTree* tr = Input->TreeMap( dataName );

    tr->SetBranchAddress("nPhotons",    &nPhotons);
    tr->SetBranchAddress("nJets",       &nJets);
    tr->SetBranchAddress("triggered",   &triggered);
    tr->SetBranchAddress("nMuons",      &nMuons);
    tr->SetBranchAddress("nElectrons",  &nElectrons);
    tr->SetBranchAddress("nVertices",   &nVertices);
    tr->SetBranchAddress("totalNVtx",   &totalNVtx);
  
    tr->SetBranchAddress("eventId",     &eventId);
//   tr->SetBranchAddress("nOutTimeHits", &nOutTimeHits) ;
//   tr->SetBranchAddress("nHaloTracks",   &nHaloTracks ) ;
   tr->SetBranchAddress("haloPhi",      &haloPhi ) ;
   tr->SetBranchAddress("haloRho",      &haloRho ) ;

   tr->SetBranchAddress("phoPx",       phoPx );
   tr->SetBranchAddress("phoPy",       phoPy );
   tr->SetBranchAddress("phoPz",       phoPz );
   tr->SetBranchAddress("phoE",        phoE );
   tr->SetBranchAddress("phoHoverE",   phoHoverE);
   tr->SetBranchAddress("phoEcalIso",   phoEcalIso);
   tr->SetBranchAddress("phoHcalIso",   phoHcalIso);
   tr->SetBranchAddress("phoTrkIso",   phoTrkIso);
   
   tr->SetBranchAddress("jetCM",   jetCM);
   tr->SetBranchAddress("jetNDau",   jetNDau);
   tr->SetBranchAddress("jetCEF",    jetCEF);
   tr->SetBranchAddress("jetNHF",   jetNHF);
//   tr->SetBranchAddress("jetCHEF",  jetCHEF);
//   tr->SetBranchAddress("jetEta",  jetEta);
     
/*     
 ///// HE stuff ////
   tr->SetBranchAddress("HERho",   HERho);
   tr->SetBranchAddress("HETime",  HETime);
   tr->SetBranchAddress("HEGPhi",  HEGPhi);
   tr->SetBranchAddress("HERadius",  HERadius);
   tr->SetBranchAddress("HEEnergy",   HEEnergy);
   tr->SetBranchAddress("HEdphi",  HEdphi); 
// tr->SetBranchAddress("HcalIso",    HcalIso);
// tr->SetBranchAddress("phoEta",     phoEta );
// tr->SetBranchAddress("phoPhi",      phoPhi );
*/
   tr->SetBranchAddress("sMinPho",       sMinPho );
   tr->SetBranchAddress("sMajPho",       sMajPho );
   tr->SetBranchAddress("jetE",           jetE );
   tr->SetBranchAddress("jetPx",       jetPx );
   tr->SetBranchAddress("jetPy",       jetPy );
   tr->SetBranchAddress("jetPz",       jetPz );
   tr->SetBranchAddress("vtxDx",         vtxDx );
   tr->SetBranchAddress("vtxDy",         vtxDy );
   tr->SetBranchAddress("vtxDz",         vtxDz );
   tr->SetBranchAddress("vtxX",         vtxX );
   tr->SetBranchAddress("vtxY",         vtxY );
   tr->SetBranchAddress("vtxZ",         vtxZ );
   tr->SetBranchAddress("met",            &met);
   tr->SetBranchAddress("metPx",        &metPx);
   tr->SetBranchAddress("metPy",        &metPy);
   tr->SetBranchAddress("muE",         muE );
   tr->SetBranchAddress("seedTime",    seedTime );
   tr->SetBranchAddress("seedTimeErr", seedTimeErr );
   tr->SetBranchAddress("aveTime",     aveTime );
   tr->SetBranchAddress("aveTime1",    aveTime1 );
   tr->SetBranchAddress("aveTimeErr",  aveTimeErr );
   tr->SetBranchAddress("aveTimeErr1", aveTimeErr1 );
   tr->SetBranchAddress("timeChi2",    timeChi2 );
   tr->SetBranchAddress("sigmaEta",    sigmaEta );
   tr->SetBranchAddress("sigmaIeta",   sigmaIeta );    
   tr->SetBranchAddress("fSpike",      fSpike );
   tr->SetBranchAddress("nXtals",     nXtals);
   tr->SetBranchAddress("nBC",     nBC );
   tr->SetBranchAddress("seedSwissX",     seedSwissX );
   tr->SetBranchAddress("cscTime",     cscTime);
   tr->SetBranchAddress("cscdPhi",     cscdPhi); 
//   tr->SetBranchAddress("nTrksSmallBeta",   &nTrksSmallBeta); 
//   tr->SetBranchAddress("nHaloSegs",     &nHaloSegs ); 
 

   tr->SetBranchAddress("jseedtime1",    jseedtime1 );
   tr->SetBranchAddress("jseedtime2",    jseedtime2 );
   tr->SetBranchAddress("jseedE",    jseedE );
   tr->SetBranchAddress("jgammaE",    jgammaE );
   tr->SetBranchAddress("jdR",        jdR );
   tr->SetBranchAddress("jseedBCtime",        jseedBCtime);
   tr->SetBranchAddress("jWavetime",        jWavetime);
   tr->SetBranchAddress("jnXtals",        jnXtals);
   tr->SetBranchAddress("jnspikes",        jnspikes);
   tr->SetBranchAddress("jseedBCEnergy",   jseedBCEnergy);
   tr->SetBranchAddress("jseedBCEt",       jseedBCEt);
   tr->SetBranchAddress("jseedBCPt",       jseedBCPt);
   tr->SetBranchAddress("jnUnMatched",     jnUnMatched);

   tr->SetBranchAddress("haloPhi",     &haloPhi);
   tr->SetBranchAddress("haloRho",     &haloRho );
   tr->SetBranchAddress("IscscHaloSeg_Tag",     &IscscHaloSeg_Tag);
   tr->SetBranchAddress("IscscHaloTrk_Tag",     &IscscHaloTrk_Tag);
   tr->SetBranchAddress("IsBeamHaloIDTightTag",     &IsBeamHaloIDTightTag);
   tr->SetBranchAddress("IscscHaloTight_Tag",     &IscscHaloTight_Tag);
// MC Infos
   tr->SetBranchAddress("nGen",        &nGen);
   tr->SetBranchAddress("genPx",       genPx );
   tr->SetBranchAddress("genPy",       genPy );
   tr->SetBranchAddress("genPz",       genPz );
   tr->SetBranchAddress("genE",        genE );
   tr->SetBranchAddress("genM",        genM );
   tr->SetBranchAddress("genVx",       genVx );
   tr->SetBranchAddress("genVy",       genVy );
   tr->SetBranchAddress("genVz",       genVz );
   tr->SetBranchAddress("genT",        genT );  // tau*gamma*beta
   tr->SetBranchAddress("pdgId",       pdgId );
   tr->SetBranchAddress("momId",       momId );

	// Initialise Histograms
     	InitHist();

    	// Get Events
  	 int totalN = tr->GetEntries();
   	cout<<" from  "<< dataName <<" total entries = "<< totalN <<" Process "<< ProcessEvents <<endl;

   	int nEvt = 0 ;
  	 cout << "Event processing Starts" << endl;
// Loop  over events
for ( int i=0; i< totalN ; i++ ) {

 	   if ( ProcessEvents > 0 && i > ( ProcessEvents - 1 ) ) break;
                tr->GetEntry( i );
 

        	  // Select only DisplacedPhO Triggered Events
 		bool passTrig = false  ;
    		for ( size_t j = 0 ; j< trigCut.size(); j++ ) {
   		     if ( triggered == trigCut[j]) passTrig = true ;
   		 }		
     
        	     if ( !passTrig ) continue ; 

        		 // Apply MET Selection
     		     if (met < metCut[0]) continue ;
       		     nEvt++;
                     double metratio = (metPy ? metPx/metPy : 0);
       		     // if(metPx == 0){ metratio = 0;} else { metratio = metPy ? metPx/metPy : 0 ;} 
      		     double thetamet = TMath::ATan(metratio); // Gravitino direction for MET Vector!
        	     double thetapho = 0;  // Photon angle
                     double phoeta = 0;    // Photon eta
        	     double pho_gravtheta = 0; // dxn of Grav wrt to photon
        	     float  massNt = 0;  // Neutralino  transverse Mass 

       		    //def photon/jet/halo 4-Vectors
        	    TLorentzVector g1P4(0,0,0,0),  j1p4(0,0,0,0), gHP4(0,0,0,0);  
                    double max_gPt  = 0 ;
        	    int kmax = -1 ;
                    int n_pho = 0; 
                    int jmax  = -1 ; 
        
           	    // Get Leading Jet Kinematics 
        	    double max_jPt = 0;
                    int    n_jets = 0 ;
   
  	 // Loop and select Max Pt Photon
   	for ( int k=0; k< nPhotons; k++) {
     	TLorentzVector gP4_ = TLorentzVector( phoPx[k], phoPy[k], phoPz[k], phoE[k] ) ;
        if ( gP4_.Pt() < photonCuts[0] ) continue ;
        if ( fabs(gP4_.Eta()) > photonCuts[2] ) continue ;

        // Include PhotonIso here!
        
	//  Halo Tagging 
       
        n_pho++ ;
        //if ( nPhotons > 0 ) cout<<" photon"<<k <<" pt:"<<gP4_.Pt() <<endl;
        if ( gP4_.Pt() > max_gPt ) {
         max_gPt = gP4_.Pt() ;
         kmax = k ;
         g1P4 = gP4_ ;
     
        } 
           
    }  // End of Nphoton Loops

       // Aply  cut on sMin on max Pt Photon
       //if( sMinPho[kmax] < photonCuts[4]  ||  sMinPho[kmax] > photonCuts[5] ) continue ;

        if ( max_gPt < photonCuts[1] ) continue ;

     	// Loop on Jets
     	for ( int j = 0; j < nJets; j++){
    	 TLorentzVector jp4_ = TLorentzVector(jetPx[j], jetPy[j], jetPz[j], jetE[j] ); 
      		 if( jp4_.Pt() < jetCuts[0] ) continue ; 
      		 // JetID Cuts
 
	       	 n_jets++ ;
       		// apply Jet Pt cuts
       		if (jp4_.Pt() > max_jPt) {
         	    max_jPt = jp4_.Pt();
         	    j1p4    = jp4_;
          	    jmax   =  j ; 
                 }       

  	     } // End of Loop Over Njets                     
            
             cout << " Number of Jets " << n_jets << endl;
       
            if ( ( n_jets < jetCuts[1] ) ||  ( n_jets > jetCuts[2] ) ) continue ;
          
      	 	 // Halo Rejection here!
       		// if (( sMajPho[kmax] > HaloCuts[0]) && ( cscdPhi[kmax] < HaloCuts[1] )) continue;
	
       		//if ( cscdPhi[kmax] < HaloCuts[1] ) continue;     /* If using only csc for tagging */

       		double tratio =( (HETime[kmax]== 0) ? 0 : fabs(seedTime[kmax]/HETime[kmax]) );
       		//if ( tratio > HaloCuts[2] ) continue; /* Using HE Time for Tagging Halo */
       		//  if ( fabs(HETime[kmax]) > HaloCuts[2] ) continue; /* Using HE Time for Tagging Halo */
     		//  double dRzpV=TMath::Sqrt(vtxDx[kmax]*vtxDx[kmax] + vtxDy[kmax]*vtxDy[kmax] + vtxDz[kmax]*vtxDz[kmax]);
       		double dRzpV=TMath::Sqrt(vtxX[kmax]*vtxX[kmax] + vtxY[kmax]*vtxY[kmax] + vtxZ[kmax]*vtxZ[kmax]);
 		  //    double dRhopV=TMath::Sqrt(vtxDx[kmax]*vtxDx[kmax] + vtxDy[kmax]*vtxDy[kmax]);
       		double dRhopV=TMath::Sqrt(vtxX[kmax]*vtxX[kmax] + vtxY[kmax]*vtxY[kmax]);

      		 // Bug checking
      	        if( n_jets == 0) { cout << "le 0-Jets Events a de Photon variables " << g1P4.Pt() << " Eta " << g1P4.Eta() 
<< " Phi " << g1P4.Phi() << " Energy " << g1P4.E() << " Numb of Photons = " << n_pho <<  endl; }

  		// Apply Crystals Selection
		//if( (nXtals[kmax] < 6) || (nXtals[kmax] > 22) ) continue ;
		//if ( seedSwissX[kmax] > photonCuts[9] ) continue ;   // Apply SwissX cuts
		//Begin Filling hists
		my.photimeVsPU->Fill(totalNVtx,seedTime[kmax]);
		my.h_Time->Fill( seedTime[kmax] );
		my.WAveSeedBCphotime->Fill( aveTime1[kmax] );
		my.AveSCphotime->Fill( aveTime[kmax] );
		my.ph_smin->Fill(sMinPho[kmax] );
		my.ph_smaj ->Fill(sMajPho[kmax] );
		my.ph_HoverE ->Fill(phoHoverE[kmax]);
		//Eta Dependence studies
		my.phoTimeVsEta->Fill( g1P4.Eta(),seedTime[kmax] );  
		my.phoTimeVsE->Fill ( g1P4.E(), seedTime[kmax] ) ;
		my.phoTimeVsPhi->Fill( g1P4.Phi(), seedTime[kmax] ) ; 
		my.phoetaVsphi->Fill(g1P4.Eta(), g1P4.Phi());  // gamma eta vs phi
		my.h_g1Pt->Fill( max_gPt );
		my.ph_e ->Fill( g1P4.E() );
		my.ph_z ->Fill( g1P4.Z());
		phoeta = g1P4.Eta();
		my.ph_eta->Fill(g1P4.Eta());
		my.ph_phi->Fill(g1P4.Phi());
		thetapho = 2*TMath::ATan(TMath::Exp(-phoeta));  // Photon Angle
		pho_gravtheta = thetapho - thetamet;
		my.phomet_thetadiff->Fill( (g1P4.Eta()-(-TMath::Log(TMath::Tan(thetamet/2))))); 
		massNt = TMath::Sqrt(2*max_gPt*met*(1 - TMath::Cos(pho_gravtheta)) );
		my.phomet_thetadiff->Fill(pho_gravtheta);
		my.npho ->Fill(n_pho); 
		my.pho_angle ->Fill(thetapho);
		my.pu_vtx->Fill(totalNVtx);
		// Isolation Variabs          
		my.pho_EcalIso->Fill(phoEcalIso[kmax]);
		my.pho_HcalIso->Fill(phoHcalIso[kmax]);
		// my.hcal_Iso->Fill(HcalIso[kmax]);
		my.pho_TrkIso->Fill(phoTrkIso[kmax]);
		my.pho_Ecal_IsoVsPU->Fill(totalNVtx,phoEcalIso[kmax]);
		my.pho_Trk_IsoVsPU->Fill(totalNVtx,phoTrkIso[kmax]);
		my.pho_Hcal_IsoVsPU->Fill(totalNVtx, phoHcalIso[kmax]);
		// my.Hcal_IsoVsPU->Fill(totalNVtx,HcalIso[kmax]);
		my.sMinorVsPU->Fill(totalNVtx,sMinPho[kmax]);

		// Fill Photon CSC related Infors
		my.phoCSCtime->Fill(cscTime[kmax]);
		my.pho_CSCdphi->Fill(cscdPhi[kmax]);
		my.phonBC->Fill(nBC[kmax]);

             
		if (j1p4.Eta() < 1.479 ) { my.Jseedtime2EB->Fill(jseedtime2[jmax]) ;
 		}else{ my.Jseedtime2EE->Fill(jseedtime2[jmax]) ; }
     //Cut on Matched SuperCluster Pt
      if ( jseedBCEt[jmax] > jetCuts[3] ) {
		// Jet timing
		my.Jseedtime1->Fill(jseedtime1[jmax]) ;
		my.Jseedtime2->Fill(jseedtime2[jmax]) ;
		my.JseedE->Fill(jseedE[jmax]) ;
		my.JSClusdR->Fill(jdR[jmax]) ;
		my.JseedBCtime->Fill(jseedBCtime[jmax]) ;
		my.JWaveBCtime->Fill(jWavetime[jmax]) ;
		my.JnCrys->Fill(jnXtals[jmax]) ;
		my.JnUMjets->Fill(jnUnMatched[jmax]) ;
		my.Jnspike->Fill(jnspikes[jmax]) ;
		my.JEcalEmEr->Fill(jgammaE[jmax]) ;
		my.Jseedtime2VsEta->Fill(j1p4.Eta() , jseedtime2[jmax]) ;
		my.Jseedtime2VsPhi->Fill(j1p4.Phi() , jseedtime2[jmax]) ;
		my.JseedtimeVsEnergy->Fill( jseedE[jmax], jseedtime2[jmax]) ;              
                my.JseedtimeChi2->Fill( jseedChi2[jmax] ) ;
                my.JseedOOtChi2->Fill ( jseedOOtChi2[jmax] ) ;
              
                my.Jseedtime2VsBCEnergy->Fill( jseedBCEnergy[jmax], jseedtime2[jmax] ) ; 
                my.Jseedtime2VsBCEt->Fill( jseedBCEt[jmax], jseedtime2[jmax] ) ; 
                my.Jseedtime2VsBCPt->Fill( jseedBCPt[jmax], jseedtime2[jmax] ) ; 
                my.JwavetimeVsBCEnergy->Fill( jseedBCEnergy[jmax], jseedBCtime[jmax] ) ; 
                my.JseedEVsEta->Fill( j1p4.Eta(), jseedE[jmax] ) ; 
                my.JseedBCEVsEta->Fill( j1p4.Eta(), jseedBCEnergy[jmax] ) ; 
                my.JseedBCEVsPhi->Fill( j1p4.Phi(), jseedBCEnergy[jmax] ) ; 
      }
		// 2D Maps
		//EB and EE plots
		if( fabs(g1P4.Eta()) < 1.479 ) {

		//Check different Phi windows For any Phi Assym
		if( fabs(g1P4.Phi()) < 0.5 ) {
		my.phoTimePhi_ZeroWinEB->Fill(seedTime[kmax]); }

		if( (g1P4.Phi() < -2.0 ) && (g1P4.Phi() > -3.0) ) {
		my.phoTimeNegPhi_3WinEB->Fill(seedTime[kmax]); }

		if( (g1P4.Phi() > 2.0 ) && (g1P4.Phi() < 3.0) ) {
		my.phoTimePosPhi_3WinEB->Fill(seedTime[kmax]); }


		//if( fabs(g1P4.Eta()) < 3.0 ) {

		//Slice in Time study////

	for( int ii=0; ii<32; ii++) {

  		 if((seedTime[kmax] >= Time_Array[ii]) && (seedTime[kmax] < Time_Array[ii+1]) ){ 
    		 my.cscdphiInTimeSlice[ii]->Fill(cscdPhi[kmax]);
	         my.NCrysInTimeSlice[ii]->Fill(nXtals[kmax]);
                 }
     		cout <<"Time slice\t" << Time_Array[ii] << "  has CSCdPhi \t" << cscdPhi[kmax] << "  and NCrys\t" << nXtals[kmax] << endl;
           }   
     	
    		if ( n_jets >= jetCuts[1] ){ // Temporal remove n number of jet events
         	my.pho_timeVsCSCdphi->Fill(cscdPhi[kmax], seedTime[kmax]);
         	my.phoEtaVsCSCdphi->Fill(cscdPhi[kmax], g1P4.Eta());
         	my.phoPhiVsCSCdphi->Fill(cscdPhi[kmax], g1P4.Phi());
                my.MetVsCSCdphi->Fill(cscdPhi[kmax], met);
                my.phoPtVsCSCdphi->Fill(cscdPhi[kmax], max_gPt);
                my.pho_ptVscscdphiEB->Fill(cscdPhi[kmax], max_gPt);
                my.phoEtaVsNCrys->Fill( nXtals[kmax], g1P4.Eta());
                my.phoPhiVsNCrys->Fill( nXtals[kmax], g1P4.Phi());
                my.MetVsNCrys->Fill( nXtals[kmax], met);
                my.phoPtVsNCrys->Fill( nXtals[kmax], max_gPt);
                my.phoTimeVsNCrys->Fill(nXtals[kmax], seedTime[kmax]);
                my.phoTimeVsPt->Fill(max_gPt, seedTime[kmax]);
                my.phoTimeVsMet->Fill(met, seedTime[kmax]);
                my.phoPtVsMet->Fill( met, max_gPt);
                my.NCrysVsCSCdphi->Fill(cscdPhi[kmax], nXtals[kmax]);
                }


               	// EB Bkg ALL gamma variables
         	my.eta_gVstimeEB->Fill(g1P4.Eta(), seedTime[kmax]);
        	my.n_gEB->Fill(n_pho);
        	my.n_jEB->Fill(n_jets);
                my.g_nCrysEB->Fill( nXtals[kmax]);
                my.g_timeEB->Fill(seedTime[kmax]);
                my.g_cscdphiEB->Fill(cscdPhi[kmax]);
                my.g_ptEB->Fill(max_gPt);
                my.g_metEB->Fill(met);

       		  // Spike & Halo regs
        	if( ((seedTime[kmax] >= -15.1)  && (seedTime[kmax] <= -7.1)) && ( (fabs(g1P4.Phi()) >= 0.45) && (fabs(g1P4.Phi()) <= 2.6 ) ) ) {  
//           	if( cscdPhi[kmax] < 0.035) continue;
         	  my.eta_spkVstimeEB->Fill(g1P4.Eta(), seedTime[kmax]);
        	  my.n_spkEB->Fill(n_pho);
          	  my.n_jspkEB->Fill(n_jets);
                  my.spk_nCrysEB->Fill(nXtals[kmax]);
                  my.spk_timeEB->Fill(seedTime[kmax]);
                  my.spk_cscdphiEB->Fill(cscdPhi[kmax]);
                  my.spk_ptEB->Fill(max_gPt);
                  my.spk_metEB->Fill(met);

                 } 
         	// pure Halo Reg
	//	if( ( (fabs(g1P4.Phi()) <= 3.0 ) && (fabs(g1P4.Phi()) >= 2.6) ) || (fabs(g1P4.Phi()) <= 0.43 )  ){
		if( ( ((fabs(g1P4.Phi()) <= 3.0 ) && (fabs(g1P4.Phi()) >= 2.6) ) && ( (seedTime[kmax] >= -9.1) && (seedTime[kmax] <= -2.1) )) ||
		( ((fabs(g1P4.Phi()) <= 3.0 ) && (fabs(g1P4.Phi()) >= 2.6) ) && ( (seedTime[kmax] >= 2.9) && (seedTime[kmax] <= 23.0) ))  || 
		( ((fabs(g1P4.Phi()) <= 3.0 ) && (fabs(g1P4.Phi()) >= 2.6) ) && ( (seedTime[kmax] >= -9.1) && (seedTime[kmax] <= -2.1) )) ||
		( ((fabs(g1P4.Phi()) <= 0.43 )) && ( (seedTime[kmax] >= -9.1) && (seedTime[kmax] <= -2.1) )) ||
		( ((fabs(g1P4.Phi()) <= 0.43) ) && ( (seedTime[kmax] >= 2.9) && (seedTime[kmax] <= 23.0)) ) 	
	)	{

           	my.eta_hVstimeEB->Fill(g1P4.Eta(), seedTime[kmax]);
          	my.n_hEB->Fill(n_pho);
           	my.n_jhEB->Fill(n_jets);
          	my.h_nCrysEB->Fill(nXtals[kmax]);
           	my.h_timeEB->Fill(seedTime[kmax]);
           	my.h_cscdphiEB->Fill(cscdPhi[kmax]);
           	my.h_ptEB->Fill(max_gPt);
          	my.h_metEB->Fill(met);
         	}	 

		//Estimate of Spike in Photon Region

	        if( (fabs(seedTime[kmax]) < 1.9) && ( (fabs(g1P4.Phi()) >= 0.5) && (fabs(g1P4.Phi()) <= 2.6 ) ) ) {  
        	   my.eta_spkInphoVstimeEB->Fill(g1P4.Eta(), seedTime[kmax]);
         	   my.n_spkInphoEB->Fill(n_pho);
           	   my.n_jspkInphoEB->Fill(n_jets);
         	   my.spkInpho_nCrysEB->Fill(nXtals[kmax]);
           	   my.spkInpho_timeEB->Fill(seedTime[kmax]);
                   my.spkInpho_cscdphiEB->Fill(cscdPhi[kmax]);
                   my.spkInpho_ptEB->Fill(max_gPt);
                   my.spkInpho_metEB->Fill(met);
         	 } 
     
           	   my.pho_timeVsEtaEB->Fill(g1P4.Eta(), seedTime[kmax]);
                   my.pho_timeVsPhiEB->Fill(g1P4.Phi(), seedTime[kmax]);
          	   my.pho_sminorEB->Fill(sMinPho[kmax]);
          	   my.pho_smajorEB->Fill(sMajPho[kmax]);
         	   my.pho_sigmaEtaEB->Fill(sigmaEta[kmax]);
           	   my.pho_timeEB->Fill(seedTime[kmax]);
          	   my.pho_num_phoEB->Fill(n_pho);
         	   my.pho_num_jetEB->Fill(n_jets);
          	   my.pho_SSXEB->Fill(seedSwissX[kmax]);
           	   my.phonXtalEB->Fill(nXtals[kmax]);
         	   my.pho_sigmaIeta->Fill(sigmaIeta[kmax]);


//  Bkg Esti  in EB //
std::cout << "La regione de ABCD" << std::endl;
std::cout <<"Lead Photon has Position=: " << kmax <<"\n" << " Njets =: " << n_jets << "\n" <<" has Eta =:"
<< g1P4.Eta() <<"\t" <<" and Phi=: " << g1P4.Phi() << std::endl;

if(n_jets == 0 ){ my.eb_met0->Fill(met);my.eb_time0->Fill(seedTime[kmax]);}
if(n_jets == 1 ){ my.eb_met1->Fill(met);my.eb_time1->Fill(seedTime[kmax]);}
if(n_jets == 2 ){ my.eb_met2->Fill(met);my.eb_time2->Fill(seedTime[kmax]);}
if(n_jets >= 3 ){ my.eb_met3->Fill(met);my.eb_time3->Fill(seedTime[kmax]);}

// #jets Eff Hist

if(seedTime[kmax] < photonCuts[7]) {
my.eb_pNjets->Fill(n_jets);
if(cscdPhi[kmax] < HaloCuts[1] ){ my.eb_hpNjets->Fill(n_jets);}else if ((seedSwissX[kmax] > SX_min) || (nXtals[kmax] < Nxtal_min)){my.eb_spike_pNjets->Fill(n_jets);
}else{my.eb_qcd_pNjets->Fill(n_jets);}
}
//if( Njet_max < n_jets < Njet_min ){
//if ( n_jets == jetCuts[1] ){
if ( ( n_jets == jetCuts[1]) && (seedTime[kmax] < photonCuts[7])){
   my.eb_ptime->Fill(seedTime[kmax]);
   my.eb_pSWX->Fill(seedSwissX[kmax]);
   my.eb_pnXtal->Fill(nXtals[kmax]);
   my.eb_pcscdPhi->Fill(cscdPhi[kmax]);
   my.eb_pPt->Fill( max_gPt );
   my.eb_pMET->Fill(met);
   if(met < MET_min){my.eb_low_metTime->Fill(seedTime[kmax]);} else{my.eb_high_metTime->Fill(seedTime[kmax]); }
   //if ( cscdPhi[kmax] < csc_dphi_min) continue;
   if(cscdPhi[kmax] < HaloCuts[1] ){ std::cout << "j'ai vu en Halo passe ici" << std::endl;
                                       my.eb_hptime ->Fill(seedTime[kmax]);
                                       my.eb_hpSWX->Fill(seedSwissX[kmax]);
                                       my.eb_hpnXtal->Fill(nXtals[kmax]);
                                       my.eb_hpcscdPhi->Fill(cscdPhi[kmax]);
                                       my.eb_hpPt->Fill( max_gPt );
                                       my.eb_hpMET->Fill(met);
   }else if ((seedSwissX[kmax] > SX_min) || (nXtals[kmax] < Nxtal_min)){
                                       std::cout <<"C'est pas un Halo mais un Spike" << std::endl;
                                         my.eb_spike_ptime->Fill(seedTime[kmax]);
                                         my.eb_spike_pSWX->Fill(seedSwissX[kmax]);
                                         my.eb_spike_pnXtal->Fill(nXtals[kmax]);
                                         my.eb_spike_pcscdPhi->Fill(cscdPhi[kmax]);
                                         my.eb_spike_pPt->Fill( max_gPt );
                                         my.eb_spike_pMET->Fill(met);
   }else { std::cout << "C'est pas un Halo ou un Spike! alors ce..." << std::endl;
          my.eb_qcd_ptime->Fill(seedTime[kmax]);
          my.eb_qcd_pSWX->Fill(seedSwissX[kmax]);
          my.eb_qcd_pnXtal->Fill(nXtals[kmax]);
          my.eb_qcd_pcscdPhi->Fill(cscdPhi[kmax]);
          my.eb_qcd_pPt->Fill( max_gPt );
          my.eb_qcd_pMET->Fill(met);
         }
	 
}
else if(( n_jets >= 3) && (seedTime[kmax] > 0)){

// Define ABCD region
      my.eb_reg->Fill(met, seedTime[kmax]);
      if((seedTime[kmax] <= t_th) && (met <= MET_min)){ my.eb_regA->Fill( met, seedTime[kmax]);}
      if((seedTime[kmax] <= t_th) && (met > MET_min)){my.eb_regB->Fill( met, seedTime[kmax]);}
      if((seedTime[kmax] > t_th) && (met <= MET_min)){my.eb_regC->Fill( met, seedTime[kmax]);}
      if((seedTime[kmax] > t_th) && (met > MET_min)){my.eb_regD->Fill( met, seedTime[kmax]);}
      }
 
std::cout <<"J'ai finis" << std::endl;


///@@@@@ Done with Bkg Esti @@@@@@////


/****** HE stuff ****/
my.HEhalo_timeVsHEdphiEB->Fill(HEGPhi[kmax], seedTime[kmax]);
my.HEdphiEB->Fill(HEGPhi[kmax]);
// Treating - & + time Seperately)
if( seedTime[kmax] < photonCuts[7] ) {
my.pho_LN2timeEB->Fill(seedTime[kmax]);
}else if( (seedTime[kmax] > photonCuts[7] ) && (seedTime[kmax] < photonCuts[8]) ) {
my.pho_LN2GP2timeEB->Fill(seedTime[kmax]);
}else {
my.pho_GP2timeEB->Fill(seedTime[kmax]);
}
// Ouside 2ns Events
         if(fabs(seedTime[kmax]) > photonCuts[8] ) { 
            my.pho_ATG2_sigmaEtaEB->Fill(sigmaEta[kmax]);
            my.pho_ATG2_sminorEB->Fill(sMinPho[kmax]);
            my.pho_ATG2_smajorEB->Fill(sMajPho[kmax]);
           }


 }else{ // endcap
   
       my.pho_timeVsEtaEE->Fill(g1P4.Eta(), seedTime[kmax]);
       my.pho_timeVsPhiEE->Fill(g1P4.Phi(), seedTime[kmax]);
       my.pho_sminorEE->Fill(sMinPho[kmax]);
       my.pho_smajorEE->Fill(sMajPho[kmax]);
       my.pho_sigmaEtaEE->Fill(sigmaEta[kmax]);
       my.pho_timeEE->Fill(seedTime[kmax]);
       my.pho_num_phoEE->Fill(n_pho);
       my.pho_num_jetEE->Fill(n_jets); 

// if(n_jets == jetCuts[1]) {
       //-EE
       if(g1P4.Eta() < 0.0)
         {
         /* check Gud Photon in EE */
	if(  (fabs(g1P4.Phi()) <= TMath::Pi() && fabs(g1P4.Phi()) >= 2.51 ) || (fabs(g1P4.Phi()) <= 0.6 ) ){  
	
	  my.EEM_pho_time_In_Halo_Win->Fill(seedTime[kmax]);
	  my.EEM_pho_eta_In_Halo_Win->Fill(g1P4.Eta());
	  my.EEM_pho_pt_In_Halo_Win->Fill(max_gPt);
	  my.EEM_pho_ncrys_In_Halo_Win->Fill(nXtals[kmax]);
	  }else{
	  my.EEM_pho_time_NIn_Halo_Win->Fill(seedTime[kmax]);
	  my.EEM_pho_eta_NIn_Halo_Win->Fill(g1P4.Eta());
	  my.EEM_pho_pt_NIn_Halo_Win->Fill(max_gPt);
	  my.EEM_pho_ncrys_NIn_Halo_Win->Fill(nXtals[kmax]);


	  }

	 // Check Untaggable Halo Photons in EE
	 
         if( fabs(g1P4.Eta() ) > 1.95){

	  my.EEM_Untag_Halo_pho_time->Fill(seedTime[kmax]);
	  my.EEM_Untag_Halo_pho_eta->Fill(g1P4.Eta());
	  my.EEM_Untag_Halo_pho_phi->Fill(g1P4.Phi());
          my.EEM_Untag_Halo_pho_cscdphi->Fill(cscdPhi[kmax]);
          my.EEM_Untag_Halo_pho_ncrys->Fill(nXtals[kmax]);
          my.EEM_Untag_Halo_pho_pt->Fill(max_gPt);
          my.EEM_Untag_Halo_pho_met->Fill(met);
          my.EEM_Untag_Halo_pho_metVstime->Fill(met, seedTime[kmax]);
	 }




       
        if( fabs(seedTime[kmax]) <= 1.0){
	  my.EEM_CSC_dphi_In_1ns->Fill(cscdPhi[kmax]);
	  }else{
	  my.EEM_CSC_dphi_NIn_1ns->Fill(cscdPhi[kmax]);
	  }

	   my.EEM_phoTimeVsRho->Fill(dRhopV, seedTime[kmax]);
	   my.EEM_phoTimeVsPhi->Fill(g1P4.Phi(), seedTime[kmax]);
	   my.EEM_phoRho->Fill(dRhopV);
	   my.EEM_phoPhi->Fill(g1P4.Phi());
           
	    //Delta maths R
	   my.EEM_phoTimeVsR->Fill(dRzpV, seedTime[kmax]);
	   my.EEM_phoR->Fill(dRzpV);
            
	   my.ALL_EEM_pho_time->Fill(seedTime[kmax]); 
	   my.ALL_EEM_pho_eta->Fill(g1P4.Eta());

       	      if(( fabs(g1P4.Phi()) < 0.50) || (fabs(g1P4.Phi()) > 2.5 )){
        	    my.EEM_ZPphi_pho_time->Fill(seedTime[kmax]); 
	            my.EEM_ZPphi_pho_eta->Fill(g1P4.Eta());
	       }else{
                     my.EEM_pho_time->Fill(seedTime[kmax]); 
	             my.EEM_pho_eta->Fill(g1P4.Eta());
               	} 

         }else{ //+EE
	    
         /* check Gud Photon in EE */	
	if(  (fabs(g1P4.Phi()) <= TMath::Pi() && fabs(g1P4.Phi()) >= 2.51 ) || (fabs(g1P4.Phi()) <= 0.6 ) ){  
	  my.EEP_pho_time_In_Halo_Win->Fill(seedTime[kmax]);
	  my.EEP_pho_eta_In_Halo_Win->Fill(g1P4.Eta());
	  my.EEP_pho_pt_In_Halo_Win->Fill(max_gPt);
	  my.EEP_pho_ncrys_In_Halo_Win->Fill(nXtals[kmax]);
	  
	  }else{

	  my.EEP_pho_time_NIn_Halo_Win->Fill(seedTime[kmax]);
	  my.EEP_pho_eta_NIn_Halo_Win->Fill(g1P4.Eta());
	  my.EEP_pho_pt_NIn_Halo_Win->Fill(max_gPt);
	  my.EEP_pho_ncrys_NIn_Halo_Win->Fill(nXtals[kmax]);
	  }

            // Untagged Halo in EE+
         if( fabs(g1P4.Eta() ) > 1.95){

	  my.EEP_Untag_Halo_pho_time->Fill(seedTime[kmax]);
	  my.EEP_Untag_Halo_pho_eta->Fill(g1P4.Eta());
	  my.EEP_Untag_Halo_pho_phi->Fill(g1P4.Phi());
          my.EEP_Untag_Halo_pho_cscdphi->Fill(cscdPhi[kmax]);
          my.EEP_Untag_Halo_pho_ncrys->Fill(nXtals[kmax]);
          my.EEP_Untag_Halo_pho_pt->Fill(max_gPt);
          my.EEP_Untag_Halo_pho_met->Fill(met);
          my.EEP_Untag_Halo_pho_metVstime->Fill(met, seedTime[kmax]);
	 }


       
        if( fabs(seedTime[kmax]) <= 1.0){
	  my.EEP_CSC_dphi_In_1ns->Fill(cscdPhi[kmax]);
	  }else{
	  my.EEP_CSC_dphi_NIn_1ns->Fill(cscdPhi[kmax]);
	  }

	   my.EEP_phoTimeVsRho->Fill(dRhopV, seedTime[kmax]);
	   my.EEP_phoTimeVsPhi->Fill(g1P4.Phi(), seedTime[kmax]);
	   my.EEP_phoRho->Fill(dRhopV);
	   my.EEP_phoPhi->Fill(g1P4.Phi());

	    //Delta maths R
	   my.EEP_phoTimeVsR->Fill(dRzpV, seedTime[kmax]);
	   my.EEP_phoR->Fill(dRzpV);
	 
           
	   my.ALL_EEP_pho_time->Fill(seedTime[kmax]); 
	   my.ALL_EEP_pho_eta->Fill(g1P4.Eta());

       	      if(fabs((g1P4.Phi()) < 0.5 ) || (fabs(g1P4.Phi()) > 2.50) ){
        	    my.EEP_ZPphi_pho_time->Fill(seedTime[kmax]); 
	            my.EEP_ZPphi_pho_eta->Fill(g1P4.Eta());
	       }else{
                     my.EEP_pho_time->Fill(seedTime[kmax]); 
	             my.EEP_pho_eta->Fill(g1P4.Eta());
               	} 

	  }

 // }


          /****** HE stuff ****/
         /*&&&&& HE Tag stuff &&&&*/
       my.HEhalo_timeVsHEdphiEE->Fill(HEGPhi[kmax], seedTime[kmax]);
       my.HEdphiEE->Fill(HEGPhi[kmax]);
       my.HEhalo_timeVsHEdphi->Fill(HEdphi[kmax], seedTime[kmax]);
       my.HEhalo_timeVsHEGdphi->Fill(HEGPhi[kmax], seedTime[kmax]);
       my.HEhalo_timeVsHEradius->Fill(HERadius[kmax], seedTime[kmax]);
       my.HEhalo_timeVsHErho->Fill(HERho[kmax], seedTime[kmax]);
       my.HEtimeVsPhophi->Fill(g1P4.Phi(), HETime[kmax]);
       my.HEtimeVsPhoeta->Fill(g1P4.Eta(), HETime[kmax]);
       my.HEtime->Fill(HETime[kmax]);
       my.HEradius->Fill(HERadius[kmax]);
       my.HEenergy->Fill(HEEnergy[kmax]);
       my.HErho->Fill(HERho[kmax]);
       my.HEdphi->Fill(HEGPhi[kmax]);

       //double tratio =( (HETime[kmax]== 0) ? 0 : fabs(seedTime[kmax]/HETime[kmax]) );
       my.TimeREEHE->Fill(tratio );

        // Treating - & + time Seperately)
        if( seedTime[kmax] < photonCuts[7] ) {
        my.pho_LN2timeEE->Fill(seedTime[kmax]);
        }else if( (seedTime[kmax] > photonCuts[7] ) && (seedTime[kmax] < photonCuts[8]) ) {
        my.pho_LN2GP2timeEE->Fill(seedTime[kmax]);
        }else {
        my.pho_GP2timeEE->Fill(seedTime[kmax]);
        }
        // Ouside 2ns Events
        if(fabs(seedTime[kmax]) > photonCuts[8] ) { 
        my.pho_ATG2_sigmaEtaEE->Fill(sigmaEta[kmax]);
        my.pho_ATG2_sminorEE->Fill(sMinPho[kmax]);
        my.pho_ATG2_smajorEE->Fill(sMajPho[kmax]);
        }

      }

       // For Leading Jets
       my.j_pt->Fill(max_jPt); // Jet With Largest Pt
       my.jet_eta->Fill(j1p4.Eta() );
       my.jet_phi->Fill(j1p4.Phi() );
       my.evt_met->Fill(met);
       my.metVsPU->Fill(totalNVtx, met); // PU effect?
       my.mettheta->Fill(thetamet);
       my.MassNt->Fill(massNt); 
       my.njets->Fill(n_jets);


float dphi = ROOT::Math::VectorUtil::DeltaPhi(j1p4, g1P4);
my.jp_deta->Fill( fabs(j1p4.Eta() - g1P4.Eta()) );
my.jp_dphi->Fill ( dphi ) ;


// Halo Related Issues
float hphodphi = ROOT::Math::VectorUtil::DeltaPhi(gHP4, g1P4);
float hphodR = ROOT::Math::VectorUtil::DeltaR(gHP4, g1P4);

my.pho_halodphi->Fill(hphodphi);
my.pho_halodrho->Fill(hphodR);

hphodphi = (hphodphi > 3.1416 ) ? 6.2832 - hphodphi : hphodphi ;
//float dphi = 0; 
float halodR = 0;


/***@@@@@@ My Criteria for anything Halo-like @@@@@@@*****/
//if(IscscHaloSeg_Tag || IscscHaloTrk_Tag || IsBeamHaloIDTightTag || IscscHaloTight_Tag ) {
//
//
//
//if (( sMajPho[kmax] > HaloCuts[0]) && ( cscdPhi[kmax] < HaloCuts[1] )) { 
//
//
//// Our Refined Tight Halo Criteria
if ( cscdPhi[kmax] < HaloCuts[1] ) {  /* Using only csc for tagging */
gHP4 = g1P4 ; 
dphi = ROOT::Math::VectorUtil::DeltaPhi(gHP4, g1P4);
halodR   = ROOT::Math::VectorUtil::DeltaR(gHP4, g1P4);
my.halo_phodrho->Fill(halodR);
my.halo_phodphi->Fill(dphi); 

Hg.halo_etaVsphi->Fill(gHP4.Eta(),gHP4.Phi()); 
Hg.halo_phiVsStime->Fill(gHP4.Phi(),seedTime[kmax]);
Hg.halo_phiVsBCtime->Fill(gHP4.Phi(),aveTime1[kmax]); 
Hg.halo_phiVsSCtime->Fill(gHP4.Phi(),aveTime[kmax]); 
Hg.halo_etaVsStime->Fill(gHP4.Eta(),seedTime[kmax]);
Hg.halo_etaVsBCtime->Fill(gHP4.Eta(),aveTime1[kmax]); 
Hg.halo_etaVsSCtime->Fill(gHP4.Eta(),aveTime[kmax]); 
Hg.halo_rhoVsphi->Fill(halodR, haloPhi); 
Hg.halo_seedTime->Fill(seedTime[kmax]);
Hg.halo_wavBCtime->Fill(aveTime1[kmax]);
Hg.halo_wavSCtime->Fill(aveTime[kmax]);
//1 d plots
Hg.halo_nBC->Fill(nBC[kmax]);
Hg.halo_rho->Fill(halodR);
Hg.halo_phi->Fill(gHP4.Phi());
Hg.halo_sigmaIeta->Fill(sigmaIeta[kmax]);
Hg.halo_CSCdphi->Fill(cscdPhi[kmax]);
Hg.halo_timeVsCSCdphi->Fill(cscdPhi[kmax], seedTime[kmax]);
//EB and EE plots
if( fabs(g1P4.Eta()) < 1.479 ) {
Hg.halo_timeVsEtaEB->Fill(g1P4.Eta(), seedTime[kmax]);
Hg.halo_timeVsPhiEB->Fill(g1P4.Phi(), seedTime[kmax]);
Hg.halo_sminorEB->Fill(sMinPho[kmax]);
Hg.halo_smajorEB->Fill(sMajPho[kmax]);
Hg.halo_sigmaEtaEB->Fill(sigmaEta[kmax]);
Hg.halo_timeEB->Fill(seedTime[kmax]);
Hg.halo_num_phoEB->Fill(n_pho);
Hg.halo_num_jetEB->Fill(n_jets);
Hg.halo_nXtalEB->Fill(nXtals[kmax]);
Hg.halo_SSXEB->Fill(seedSwissX[kmax]);
//treating -&+ time
if( seedTime[kmax] < photonCuts[7] ) {
Hg.halo_LN2timeEB->Fill(seedTime[kmax]);
}else if( (seedTime[kmax] > photonCuts[7] ) && (seedTime[kmax] < photonCuts[8]) ) {
Hg.halo_LN2GP2timeEB->Fill(seedTime[kmax]);
}else {
Hg.halo_GP2timeEB->Fill(seedTime[kmax]);
}
// Ouside 2ns Events
if(fabs(seedTime[kmax]) > photonCuts[8]) { 
Hg.halo_ATG2_sigmaEtaEB->Fill(sigmaEta[kmax]);
Hg.halo_ATG2_sminorEB->Fill(sMinPho[kmax]);
Hg.halo_ATG2_smajorEB->Fill(sMajPho[kmax]);
 }

}else{
Hg.halo_timeVsEtaEE->Fill(g1P4.Eta(), seedTime[kmax]);
Hg.halo_timeVsPhiEE->Fill(g1P4.Phi(), seedTime[kmax]);
Hg.halo_sminorEE->Fill(sMinPho[kmax]);
Hg.halo_smajorEE->Fill(sMajPho[kmax]);
Hg.halo_sigmaEtaEE->Fill(sigmaEta[kmax]);
Hg.halo_timeEE->Fill(seedTime[kmax]);
Hg.halo_num_phoEE->Fill(n_pho);
Hg.halo_num_jetEE->Fill(n_jets);
//treating -&+ time
if( seedTime[kmax] < photonCuts[7] ) {
Hg.halo_LN2timeEE->Fill(seedTime[kmax]);
}else if( (seedTime[kmax] > photonCuts[7] ) && (seedTime[kmax] < photonCuts[8]) ) {
Hg.halo_LN2GP2timeEE->Fill(seedTime[kmax]);
}else {
Hg.halo_GP2timeEE->Fill(seedTime[kmax]);
}
// Ouside 2ns Events
if(fabs(seedTime[kmax]) > photonCuts[8] ) { 
Hg.halo_ATG2_sigmaEtaEE->Fill(sigmaEta[kmax]);
Hg.halo_ATG2_sminorEE->Fill(sMinPho[kmax]);
Hg.halo_ATG2_smajorEE->Fill(sMajPho[kmax]);
 }

}


 } // End of halo tagging

//if(nhaloBC   !=0)
//Hg.halo_phonBCratio->Fill( nhaloBC/nBC[kmax] );
//if(nhaloXtal !=0) 
//Hg.halo_phonXtalratio->Fill( nhaloXtal/nXtals[kmax] );

// Halo Tracks and segments

//Hg.halo_TrksSbeta->Fill(nTrksSmallBeta);
//Hg.halo_nhalosegs->Fill(nHaloSegs);
//Hg.halo_nhalotrk->Fill(nHaloTracks);
//Hg.halo_nOThits->Fill(nOutTimeHits);



// Plot Photon  Seed time Vs PU  
if( totalNVtx >= 0 && totalNVtx <= 7) my.tV1->Fill(seedTime[kmax]);
if( totalNVtx >  7 && totalNVtx <= 14) my.tV2->Fill(seedTime[kmax]);
if( totalNVtx > 14 && totalNVtx <= 21) my.tV3->Fill(seedTime[kmax]);
if( totalNVtx > 21 && totalNVtx <= 28) my.tV4->Fill(seedTime[kmax]);
if( totalNVtx > 28 && totalNVtx <= 35) my.tV5->Fill(seedTime[kmax]);
if( totalNVtx > 35 && totalNVtx <= 42) my.tV6->Fill(seedTime[kmax]);
if( totalNVtx > 42 && totalNVtx <= 49) my.tV7->Fill(seedTime[kmax]);
//if( totalNVtx > 35 && totalNVtx <= 40) my.tV8->Fill(seedTime[kmax]);
//if( totalNVtx > 40 && totalNVtx <= 45) my.tV9->Fill(seedTime[kmax]);
//if( totalNVtx > 45 && totalNVtx <= 50) my.tV10->Fill(seedTime[kmax]);
//if( totalNVtx > 50 && totalNVtx <= 55) my.tV11->Fill(seedTime[kmax]);
//Ave SC Time Vs PU
if( totalNVtx >= 0 && totalNVtx <= 7) my.tV12->Fill(aveTime[kmax]);
if( totalNVtx >  7 && totalNVtx <= 14) my.tV13->Fill(aveTime[kmax]);
if( totalNVtx > 14 && totalNVtx <= 21) my.tV14->Fill(aveTime[kmax]);
if( totalNVtx > 21 && totalNVtx <= 28) my.tV15->Fill(aveTime[kmax]);
if( totalNVtx > 28 && totalNVtx <= 35) my.tV16->Fill(aveTime[kmax]);
if( totalNVtx > 35 && totalNVtx <= 42) my.tV17->Fill(aveTime[kmax]);
if( totalNVtx > 42 && totalNVtx <= 49) my.tV18->Fill(aveTime[kmax]);

//if( totalNVtx > 35 && totalNVtx <= 40) my.tV19->Fill(aveTime[kmax]);
//if( totalNVtx > 40 && totalNVtx <= 45) my.tV20->Fill(aveTime[kmax]);
//if( totalNVtx > 45 && totalNVtx <= 50) my.tV21->Fill(aveTime[kmax]);
//if( totalNVtx > 50 && totalNVtx <= 55) my.tV22->Fill(aveTime[kmax]);

// Timing  Ave Seed BC Time PU Dependence
if( totalNVtx >= 0  &&  totalNVtx <= 6 ) my.py19->Fill(aveTime1[kmax]);
if( totalNVtx >  6  &&  totalNVtx <= 12) my.py18->Fill(aveTime1[kmax]);
if( totalNVtx > 12  &&  totalNVtx <= 18) my.py17->Fill(aveTime1[kmax]);
if( totalNVtx > 18  &&  totalNVtx <= 24) my.py16->Fill(aveTime1[kmax]);
if( totalNVtx > 24  &&  totalNVtx <= 35) my.py15->Fill(aveTime1[kmax]);
if( totalNVtx > 35  &&  totalNVtx <= 45) my.py14->Fill(aveTime1[kmax]);
if( totalNVtx > 45  &&  totalNVtx <= 55) my.py13->Fill(aveTime1[kmax]);



          
// Check weird Photon Time
// if(seedTime[kmax] >= 10){ hasweirdtime = true;};
//if( (seedTime[kmax] < -5.0) || (seedTime[kmax] > 10.0)   ){


//          Lt.ltnjets->Fill(nJets);
//          Lt.ltnpho->Fill(nPhotons);  // The Number of Photons in Event with Large Leading Photon weird time
//          Lt.ltEvtpt->Fill(max_gPt);
//          Lt.ltEvtmet->Fill(met);
//          Lt.lteta->Fill(g1P4.Eta());
//          Lt.ltphoE->Fill(g1P4.E());
//          Lt.ltphi->Fill(g1P4.Phi());
//          Lt.ltnvtx->Fill(totalNVtx);

//          cout << "Has NJets= " << nJets  << "\t" << " Has NPhotons= " << nPhotons << "\n";
//                          cout << "Photon Has Pt=  " << max_gPt << " GeV/c" << "\t"  << "Missing Energy= " << met << " GeV \n";
//                          cout << "Number of vertices= " << totalNVtx << endl;

// // Loop over its number of vertices and print out Vertext position
// for(int nv =0; nv <  totalNVtx; nv++) {
//                                          Lt.ltvtxX->Fill(vtxX[nv]);
//                                          Lt.ltvtxY->Fill(vtxY[nv]);
//                                          Lt.ltvtxZ->Fill(vtxZ[nv]);
//                                          cout << "Strange Ev't with PV from Origin : (X, Y, Z)= \t" << "(" << vtxX[nv] <<", " <<
//                                          vtxY[nv] << ", " << vtxZ[nv]  << ")" <<  endl;
//                                        }
// }  


// check for 1 Vertex events
//TLorentzVector p1P4(0,0,0,0); //,j1p4(0,0,0,0)  ; // If I need Leading JetPt too!
//double max_pPt  = 0 ; // Max Photon Pt

// single vertex events
//if (totalNVtx == 1){

//Sv.svtxnjets->Fill(nJets);
//Sv.svtxEvtmet->Fill(met); 
//Sv.svtxnpho->Fill(nPhotons);
// Loop over all the Photons in 1 vertex Event and Get Leading Pt Photon
//for ( int k=0; k< nPhotons; k++) {
//TLorentzVector pP4_ = TLorentzVector( phoPx[k], phoPy[k], phoPz[k], phoE[k] ) ;
//if ( nPhotons > 0 ) cout<<" photon"<<k <<" pt:"<<gP4_.Pt() <<endl;
// if ( pP4_.Pt() > max_pPt ) {
//      max_pPt = pP4_.Pt() ;
//      p1P4 = pP4_ ;
//      }  
//Sv.svtxEvtpt->Fill(max_pPt);
// Sv.svtxeta->Fill(p1P4.Eta());
// Sv.svtxphi->Fill(p1P4.Phi());
// Sv.svtxnvtx->Fill(totalNVtx); // Making sure NVertices is 1 --debug
// Sv.svtxX->Fill(vtxX[0]);     // Single vertex is 1st elem of Array?                                 
// Sv.svtxY->Fill(vtxY[0]);                           
// Sv.svtxZ->Fill(vtxZ[0]);
// cout <<"1 Vtx Event Has\n" << " Number of Jets=: " 
// << nJets << " ," << " With Number of Photons:= " << nPhotons  << "\t" << " Missing Energy:= " << met << endl;
// cout << "single vertex position at : (X, Y, Z) =  " << "(" << vtxX[0] <<", " << vtxZ[0] << ", " << vtxZ[0] << ")"<<  endl;
 //   }

//  } // End of Loop over Nvtx = 1 Events 

int evtId = eventId ; 
int Entry  = i ;          
printf("\nEvent Now has Event ID: %d \n",  evtId);
printf("\n Entry Now is Entry :  %d \n", Entry );


} // end of event looping

  //Don't make plots now!
//Make_Plots();

Writehists();


cout << "J'ai finis avec les Hist!" << endl;

f->Close();
 

} // End of ReadTree()
