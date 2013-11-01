// Simple Plot to calculate Efficiencies
// usage:  root -l 
//        .L EffPlot.C+
//        .X EffPlot("myrootfile.root")
// where myrootfile.root is file containing histograms
// used to calculate Efficiency
// @TEN June 2013
//
#include "TH1.h"
#include "TH2.h"
#include <string>
#include "TF1.h"
#include "TGraph.h"
#include <vector>
#include "TGraphAsymmErrors.h"
#include "TFile.h"
#include "TPaveText.h"
#include "TCanvas.h"
#include "TLegend.h"
#include  "TStyle.h"
#include  "Riostream.h"


using namespace std;
TStyle * gStyle = new TStyle("Style","Default");

// Drawing Efficiency Plot from two histograms    
void EffPlot( char* Ifile) {

std::cout << "Je c'mns avec le fiche :\t" << Ifile << std::endl;
TFile* If = new TFile(Ifile);
//Check if file is gud or ~gud!
if(!If->IsOpen()){ std::cout <<"crazy file! Je sort" << std::endl;
              }else{ std::cout <<" alons y!" << std::endl;}

//TH1D* hCut = (TH1D*)If->Get("BkgEst/my.eb_hptime");
//TH1D* hAll = (TH1D*)If->Get("BkgEst/my.eb_ptime");
TH1D* hCut = (TH1D*)If->Get("BkgEst/my.eb_hpPt");
TH1D* hAll = (TH1D*)If->Get("BkgEst/my.eb_pPt");
//string xlable = "Time(ns)";
string xlable = "Pt(GeV)";
double minBinContent = 1.0;
 int beginBin = 1;
 int endBin = -1;
//string graphName = "CSC HALO Tagging Efficiency Vs Time";
string graphName = "CSC HALO Tagging Efficiency Vs Pt";
string plotType= ".png";
TPaveText* ttex = new TPaveText(765.0, 0.918, 2515.0 , 1.10, "TL" );

  endBin = ( endBin == -1 ) ? hAll->GetNbinsX() : endBin ;

   double ba = 0 ;
   double bc = 0 ;
   double x  = 0 ;
   double rbin  = 0 ;
   double rbin_ = 0 ;
   vector<double> baV ;
   vector<double> bcV ;
   vector<double> xV ;
   vector<double> xW ;
   
   double bW = hCut->GetBinWidth(1) ;
   cout<<" bin width = " << bW <<" end bin = "<< endBin << endl ;

   // Accumulate bin contain
   for ( int i= beginBin ; i<= endBin; i++ ) {
       double bc_ = hCut->GetBinContent(i) ;
       double ba_ = hAll->GetBinContent(i) ;
       double x_  = hAll->GetBinCenter(i) ;
     
       // rebin the histogram in order to have consistence statistic for each bin
       if ( ba < minBinContent || ba < bc || rbin < rbin_ ) {
          ba += ba_ ;
          bc += bc_ ;
          x  +=  x_ ;
          rbin++ ;
        if ( i < beginBin+3 || (ba >= minBinContent && ba >= bc && rbin >= rbin_ ) ) {
             bcV.push_back( bc ) ;
	     baV.push_back( ba ) ;
	     xV.push_back( x / rbin )  ;
	     xW.push_back( rbin * bW / 2.) ;
	     
	     rbin_ = rbin ;
	     //cout<<" x: "<< x/rbin <<" rb: "<< rbin <<" bW:"<< (rbin*bW) / 2. << "  bc: "<< bc <<"  ba: "<< ba ;
	     //cout<<" eff:"<< bc/ba <<" + "<< errs.first <<" - "<< errs.second << endl ;
	     bc   = 0 ;
	     ba   = 0 ;
	     x    = 0 ;
	     rbin = 0 ;
                }
             }
               else {

          bcV.push_back( bc ) ;
          baV.push_back( ba ) ;
          xV.push_back( x / rbin )  ;
          xW.push_back( rbin * bW / 2.) ;
          
	  rbin_ = rbin ;
          //cout<<" x: "<< x/rbin <<" rb: "<< rbin <<" bW:"<< (rbin*bW) / 2. << "  bc: "<< bc <<"  ba: "<< ba ;
          //cout<<" eff:"<< bc/ba <<" + "<< errs.first <<" - "<< errs.second << endl ;
          bc   = 0 ;
          ba   = 0 ;
          x    = 0 ;
          rbin = 0 ;
       }
   }

   cout<<" nbins = "<< xV.size() <<endl ;

   // calculate proper error
   const  int nbins = (int) xV.size() ;
   TH1D* hTop      = new TH1D("hTop", " ",  nbins,  0, nbins );
   TH1D* hBot      = new TH1D("hBot", " ",  nbins,  0, nbins );
   for ( int i=0; i< nbins ; i++ ) {
       hTop->SetBinContent( i+1 , bcV[i] ) ;
       hBot->SetBinContent( i+1 , baV[i] ) ;
   }
   TGraphAsymmErrors* gRatio = new TGraphAsymmErrors();
   gRatio->BayesDivide( hTop, hBot );

   const int sz = (int) xV.size() ;
   double eYL[sz], eYH[sz], fX[sz], eX[sz];
   double* fY = gRatio->GetY() ;
   
   for ( Int_t i=0 ; i< sz ; i++) {
       fX[i]  = xV[i] ;
       eX[i]  = xW[i] ;
       eYL[i] = gRatio->GetErrorYlow(i) ;
       eYH[i] = gRatio->GetErrorYhigh(i) ;
   }

   double xMax =  fX[sz-1] + (2*eX[sz-1]) ;

   TGraphAsymmErrors* gr  = new TGraphAsymmErrors( sz, fX, fY, eX, eX, eYL, eYH );

   TCanvas* c0 = new TCanvas("c0","", 800, 700);
   c0->SetFillColor(10);
   c0->SetFillColor(10);
   gPad->SetGridx();
   gPad->SetGridy();
   c0->SetLeftMargin(0.15);
   c0->SetRightMargin(0.12);
   c0->SetTopMargin(0.1);
   c0->SetBottomMargin(0.12);

   c0->cd();
   gStyle->SetOptStat(kTRUE);
   gStyle->SetOptFit(111);

   gr->SetMaximum( 1.1 );
   gr->SetMinimum( 0.0 );
   gr->SetMarkerStyle(20);
   gr->SetMarkerSize(1);
   gr->SetLineWidth(2);
   gStyle->SetTitleFontSize(0.04) ;
   gr->SetTitle(" CMS Preliminary #sqrt{s} = 8 TeV, Lumi=15.1420 /fb") ;
   gr->GetXaxis()->SetTitleOffset(1.34);
   gr->GetYaxis()->SetTitleOffset(1.39);
   gr->GetXaxis()->SetTitleFont(42);
   gr->GetYaxis()->SetTitleFont(42);
   gr->GetXaxis()->SetTitleSize(0.04);
   gr->GetYaxis()->SetTitleSize(0.04);
   gr->GetXaxis()->SetTitle( xlable.c_str() ) ;
   gr->GetYaxis()->SetTitle(" Efficiency ") ;
   gr->GetXaxis()->SetLimits( 0., xMax );
   gr->Draw("AP");
   ttex->AddText("0-Jet Events, Time <-2.5ns");
   ttex->SetLabel("Bkg Sample");
   ttex->Draw();
   c0->Update();
   //if ( ttex != NULL ) {
   //   ttex->Draw("same") ;
   //   c0->Update();
   //} 
   TString plotname = graphName + "Asym"+plotType ;
   c0->Print( plotname );
/*   
   c0->cd();
   gr1->SetTitle(" CMS Preliminary #sqrt{s} = 8 TeV, Lumi=15.1420 /fb ") ;
   gr1->SetMaximum( 1.1 );
   gr1->SetMinimum( 0.0 );
   gr1->SetMarkerColor(4);
   gr1->SetMarkerStyle(22);
   gr1->SetMarkerSize(1);
   gr1->SetLineWidth(2);
   gr1->GetXaxis()->SetTitleOffset(1.34);
   gr1->GetYaxis()->SetTitleOffset(1.39);
   gr1->GetXaxis()->SetTitle( xlable.c_str() ) ;
   gr1->GetYaxis()->SetTitle(" Efficiency ") ;
   gr1->GetXaxis()->SetLimits( 0., xMax );
   gr1->Draw("AP");
   ttex->AddText("0-Jet Events, Time < -2.5ns");
   ttex->SetLabel("Bkg Sample");
   ttex->Draw();
   c0->Update();
   if ( ttex != NULL ) {
      ttex->Draw("same") ;
      c0->Update();
   } 

   plotname = graphName + "Asym1."+plotType ;
   c0->Print( plotname );
*/ 
   delete hTop ;
   delete hBot ;
//   delete c0 ;
//   delete gr ;
// delete gr1 ;
}

