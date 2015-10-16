# This Simple Code Overlays Histograms Plots from Different Files
# Cannot DO IT with C++ because It root chokes especially when Number bins are
# not the same.
## Aurthor Tambe E. Norbert a.k.a TEN (norbert@physics.umn.edu)
#!/usr/bin/env python
""" OverLay Myhist.png from several Directories identical structure!"""
__version__ = "1.0"
import sys
import optparse
import shutil
import os
import re
from ROOT import *
from array import array

Lowlim  = -30
Highlim = 30 
ncl     = 0
nch     = 30
# ROOT Plot Options***/	
gROOT.Reset()
gROOT.Clear()
gROOT.SetStyle("Plain")
gROOT.SetBatch(kFALSE)
gStyle.SetOptTitle(0)
gStyle.SetOptStat(0)
gStyle.SetOptFit(1)
gStyle.SetStatX(.89)
gStyle.SetStatY(.89) 
gStyle.SetStatBorderSize(0)
gStyle.SetCanvasColor(kWhite) #   // background is no longer mouse-dropping white
gStyle.SetPalette(1)        #// blue to red false color palette. Use 9 for b/w
gStyle.SetCanvasBorderMode(0) #     // turn off canvas borders
gStyle.SetPadBorderMode(0) #
gStyle.SetPaintTextFormat("5.2f") #  // What precision to put numbers if plotted with "TEXT"
# For publishing
gStyle.SetLineWidth(2)
gStyle.SetTextSize(1.1)
gStyle.SetLabelSize(0.06,"xy")
gStyle.SetTitleSize(0.09,"xy")
gStyle.SetTitleOffset(1.2,"x")
gStyle.SetTitleOffset(1.8,"y")
gStyle.SetPadTopMargin(0.1)
gStyle.SetPadRightMargin(0.1)
gStyle.SetPadBottomMargin(0.16)
gStyle.SetPadLeftMargin(0.12)
TGaxis.SetMaxDigits(2) #// Set Axis to be of the form 0.11 10^N

# Get Files!
#---------------MET60Cut---------------------------
fdata = TFile("Analysis_DPTrigger_Displaced_Photon_ALL_NJets_outputfile.root")
fmc_sig = TFile("Analysis_DPTrigger_gmsb_180_6000_ALLjet.root")
# Get Historgrams
## MC Signal
mc_sig_timeEB = fmc_sig.Get("NeutKin/my.pho_timeEB") 
mc_sig_timeEE = fmc_sig.Get("NeutKin/my.pho_timeEE")
mc_sig_time = fmc_sig.Get("NeutKin/my.h_Time") 
## Data
data_timeEB = fdata.Get("NeutKin/my.pho_timeEB")  
data_timeEE = fdata.Get("NeutKin/my.pho_timeEE") 
data_time = fdata.Get("NeutKin/my.h_Time") 

## Number of Crystals
photon_all_eb_xtal = fdata.Get("BackGndEst1/my.eb_pnXtal")
photon_halo_eb_xtal = fdata.Get("BackGndEst1/my.eb_hpnXtal")
photon_spike_eb_xtal = fdata.Get("BackGndEst1/my.eb_spike_pnXtal")
photon_qcd_eb_xtal = fdata.Get("BackGndEst1/my.eb_qcd_pnXtal")

# Choose Line Colors
mc_sig_timeEB.SetLineColor(6)
mc_sig_timeEE.SetLineColor(9)
mc_sig_time.SetLineColor(2)

data_timeEB.SetLineColor(6)
data_timeEE.SetLineColor(9)
data_time.SetLineColor(2)

# Evt Sel Var
photon_all_eb_xtal.SetLineColor(1)
photon_halo_eb_xtal.SetLineColor(4)
photon_spike_eb_xtal.SetLineColor(2)
photon_qcd_eb_xtal.SetLineColor(3)

## Choose Line Widths
mc_sig_timeEB.SetLineWidth(4)
mc_sig_timeEE.SetLineWidth(4)
mc_sig_time.SetLineWidth(4)

data_timeEB.SetLineWidth(4)
data_timeEE.SetLineWidth(4)
data_time.SetLineWidth(4)

## Sel Variables
photon_all_eb_xtal.SetLineWidth(4)
photon_halo_eb_xtal.SetLineWidth(4)
photon_spike_eb_xtal.SetLineWidth(4)
photon_qcd_eb_xtal.SetLineWidth(4)
# Choose Fill Colors
#s_time.SetFillColor(6)
#A_time.SetFillColor(9)

#Choose Marker Style!
mc_sig_timeEB.SetMarkerStyle(6)
mc_sig_timeEE.SetMarkerStyle(9)
mc_sig_time.SetMarkerStyle(8)

data_timeEB.SetMarkerStyle(6)
data_timeEE.SetMarkerStyle(9)
data_time.SetMarkerStyle(8)

## Kinematics
#photon_all_eb_xtal.SetMarkerStyle(6)
#photon_halo_eb_xtal.SetMarkerStyle(6)
#photon_spike_eb_xtal.SetMarkerStyle(6)
#photon_qcd_eb_xtal.SetMarkerStyle(6)

#### Or Line Style
photon_all_eb_xtal.SetLineStyle(7)
photon_halo_eb_xtal.SetLineStyle(3)
photon_spike_eb_xtal.SetLineStyle(4)
photon_qcd_eb_xtal.SetLineStyle(6)


# Scale Histograms
if mc_sig_timeEB.Integral()!=0:
   mc_sig_timeEB.Scale(1/mc_sig_timeEB.Integral())
if mc_sig_timeEE.Integral()!=0:
   mc_sig_timeEE.Scale(1/mc_sig_timeEE.Integral())
if mc_sig_time.Integral()!=0:
   mc_sig_time.Scale(1/mc_sig_time.Integral())

if data_timeEB.Integral()!=0:
   data_timeEB.Scale(1/data_timeEB.Integral())
if data_timeEE.Integral()!=0:
   data_timeEE.Scale(1/data_timeEE.Integral())
if data_time.Integral()!=0:
   data_time.Scale(1/data_time.Integral())

## Rename Axis
mc_sig_time.GetXaxis().SetTitle("ECAL Time(ns)")
mc_sig_time.GetYaxis().SetTitle("Events")

data_time.GetXaxis().SetTitle("ECAL Time(ns)")
data_time.GetYaxis().SetTitle("Events")

## Sel Var
photon_all_eb_xtal.GetXaxis().SetTitle("Number Of Crystals in Supercluster")
photon_all_eb_xtal.GetYaxis().SetTitle("Events")
# Draw Plots now
# *************************************************************************************
c1 = TCanvas("c1", "SPS8: Photon Time", 800, 800)
c1.SetGridx();
c1.SetGridy();
c1.GetFrame().SetFillColor(10);
c1.GetFrame().SetBorderMode(-1);
c1.GetFrame().SetBorderSize(5);
c1.cd()

mc_sig_time.SetTitle("Photon Time")
mc_sig_time.Draw()
mc_sig_timeEB.Draw("sames")
mc_sig_timeEE.Draw("sames")
mc_sig_time.GetXaxis().SetRangeUser(Lowlim, Highlim)
#Add Legend
leg1 = TLegend( 0.60, 0.75, 0.90, 0.90)
leg1.SetBorderSize(1)
leg1.SetFillColor(0)
leg1.AddEntry(mc_sig_time,"ALL","l")
leg1.AddEntry(mc_sig_timeEB,"EB","l")
leg1.AddEntry(mc_sig_timeEE,"EE","l")
leg1.SetTextSize(0.020)
leg1.SetHeader("")
leg1.Draw()

c2 = TCanvas("c2", "Data: Photon Time", 800, 800)
c2.SetGridx();
c2.SetGridy();
c2.GetFrame().SetFillColor(10);
c2.GetFrame().SetBorderMode(-1);
c2.GetFrame().SetBorderSize(5);
c2.cd()

data_time.SetTitle("Photon Time")
data_time.Draw()
data_timeEB.Draw("sames")
data_timeEE.Draw("sames")
data_time.GetXaxis().SetRangeUser(Lowlim, Highlim)
#Add Legend
leg2 = TLegend( 0.60, 0.75, 0.90, 0.90)
leg2.SetBorderSize(1)
leg2.SetFillColor(0)
leg2.AddEntry(data_time,"ALL","l")
leg2.AddEntry(data_timeEB,"EB","l")
leg2.AddEntry(data_timeEE,"EE","l")
leg2.SetTextSize(0.020)
leg2.SetHeader("")
leg2.Draw()


### Event Sel Variales
c3 = TCanvas("c3", "Event Selection Variables", 900, 900)
c3.SetGridx();
c3.SetGridy();
c3.GetFrame().SetFillColor(10);
c3.GetFrame().SetBorderMode(-1);
c3.GetFrame().SetBorderSize(5);
c3.cd()

photon_all_eb_xtal.SetTitle("") ## forget Title

photon_all_eb_xtal.Draw()
photon_halo_eb_xtal.Draw("sames")
photon_spike_eb_xtal.Draw("sames")
photon_qcd_eb_xtal.Draw("sames")
photon_all_eb_xtal.GetXaxis().SetRangeUser(ncl, nch)

#Add Legend
leg3 = TLegend( 0.52, 0.65, 0.90, 0.90)
leg3.SetBorderSize(1)
leg3.SetFillColor(0)
leg3.AddEntry(photon_all_eb_xtal,"ALL Photons","l")
leg3.AddEntry(photon_halo_eb_xtal,"Halo-Induced Photon","l")
leg3.AddEntry(photon_spike_eb_xtal,"Spike-Induced Photon","l")
leg3.AddEntry(photon_qcd_eb_xtal,"|t_{#gamma}| < 1.0ns Photons","l")
leg3.SetTextSize(0.030)
leg3.SetHeader("")
leg3.Draw()

## CMS Things
#s_lumi = "19.1"
s_lumi = ""
#CoMEr = "#sqrt{(S)} = 8 TeV"
CoMEr = "#sqrt{s} = 8 TeV"
#std::string lint = "#int Ldt= "+s_lumi+" fb^{-1}"
#std::string lint = s_lumi + "fb^{-1}"+ CoMEr
lint = s_lumi + CoMEr
cmstex = TLatex()
cmstex.SetTextAlign(12)
cmstex.SetTextSize(0.035)
cmstex.SetTextFont(22)
cmstex.SetTextAngle(0)
cmstex.SetTextColor(kBlack)
cmstex.SetNDC()
#cmstex.DrawLatex(0.155, 0.967, "CMS Preliminary");
#cmstex.DrawLatex(0.43, 0.967, CoMEr.c_str());
#cmstex.DrawLatex(0.75, 0.96, lint.c_str());
cmstex.DrawLatex(0.20, 0.865, "CMS");
cmstex.DrawLatex(0.20, 0.832, "Preliminary");
cmstex.DrawLatex(0.72, 0.920, lint);





#_______________________ Save Plots_______________________#
c1.SetLogy(0)
c1.SaveAs("/home/user1/norbert/public_html/LL_Neutral_Parts/SELECTION_VARIABLE_STUDY/SPS8-Photon-TimeEBEBALL.png")
c1.SaveAs("/home/user1/norbert/public_html/LL_Neutral_Parts/SELECTION_VARIABLE_STUDY/SPS8-Photon-TimeEBEBALL.pdf")
c1.SaveAs("/home/user1/norbert/public_html/LL_Neutral_Parts/SELECTION_VARIABLE_STUDY/SPS8-Photon-TimeEBEBALL.eps")

c2.SetLogy(0)
c2.SaveAs("/home/user1/norbert/public_html/LL_Neutral_Parts/SELECTION_VARIABLE_STUDY/Data-Photon-TimeEBEBALL.png")
c2.SaveAs("/home/user1/norbert/public_html/LL_Neutral_Parts/SELECTION_VARIABLE_STUDY/Data-Photon-TimeEBEBALL.pdf")
c2.SaveAs("/home/user1/norbert/public_html/LL_Neutral_Parts/SELECTION_VARIABLE_STUDY/Data-Photon-TimeEBEBALL.eps")


c3.SetLogy(0)
c3.SaveAs("/home/user1/norbert/public_html/LL_Neutral_Parts/SELECTION_VARIABLE_STUDY/NumberOfCrystalsInPhotonEB-Comparison.png")
c3.SaveAs("/home/user1/norbert/public_html/LL_Neutral_Parts/SELECTION_VARIABLE_STUDY/NumberOfCrystalsInPhotonEB-Comparison.pdf")
c3.SaveAs("/home/user1/norbert/public_html/LL_Neutral_Parts/SELECTION_VARIABLE_STUDY/NumberOfCrystalsInPhotonEB-Comparison.eps")
