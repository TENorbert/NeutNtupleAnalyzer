# This Simple Code Overlays Histograms Plots  from Different  Jet Multiplicity Files
# Cannot DO IT with C++ because It root chokes especially when Number bins are 
# not the same.
## Aurthor Tambe E. Norbert a.k.a TEN (norbert@physics.umn.edu)

#!/usr/bin/env python
""" OverLay Myhist.png from several  Directories identical structure!"""
__version__ = "1.0"


import sys
import optparse
import shutil
import os
import re
from ROOT import *
from array import array

# ROOT general options
gROOT.SetBatch(kTRUE)
gROOT.SetStyle("Plain")


gStyle.SetCanvasColor(kWhite)  #   // background is no longer mouse-dropping white
gStyle.SetPalette(1) #           // blue to red false color palette. Use 9 for b/w
gStyle.SetCanvasBorderMode(0) #     // turn off canvas borders
gStyle.SetPadBorderMode(0)
gStyle.SetPaintTextFormat("5.2f") #  // What precision to put numbers if plotted with "TEXT"

#  // For publishing:
gStyle.SetLineWidth(2)
gStyle.SetTextSize(1.1)
gStyle.SetLabelSize(0.06,"xy")
gStyle.SetTitleSize(0.06,"xy")
gStyle.SetTitleOffset(1.2,"x")
gStyle.SetTitleOffset(1.0,"y")
#gStyle.SetPadTopMargin(0.1)
#gStyle.SetPadRightMargin(0.1)
gStyle.SetPadBottomMargin(0.16)
gStyle.SetPadLeftMargin(0.12)

# Get Files!
#---------------MET60Cut---------------------------

##----------------No--Met60Cut-------------------------
f0 =  TFile("LessThan3Jets_DP_All_Trig_NoJetID.root")
f1 =  TFile("MoreThan3Jets_DP_All_Trig_NoJetID.root")
f2 =  TFile("ALLJetsgmsbSum12cL140tau2000_DP_All_Trig_NoJetID.root")
f3 =  TFile("ALLJetsgmsbSum12cL140tau2000_DP_All_Trig_NoJetID.root")
f4 =  TFile("ALLJetsgmsbSum12cL140tau2000_DP_All_Trig_NoJetID.root")
f5 =  TFile("ALLJetsgmsbSum12cL140tau2000_DP_All_Trig_NoJetID.root")


# Seed Xtal Time
#ph_time0 = f0.Get("NeutKin/my.h_Time")
#ph_time1 = f1.Get("NeutKin/my.h_Time")
#ph_time2 = f2.Get("NeutKin/my.h_Time") 
#ph_time3 = f3.Get("NeutKin/my.h_Time") 
#ph_time4 = f4.Get("NeutKin/my.h_Time") 
#ph_time5 = f5.Get("NeutKin/my.h_Time") 

# my.WAveSeedBCphotime
#Sbcph_time0 = f0.Get("NeutKin/my.WAveSeedBCphotime")
#Sbcph_time1 = f1.Get("NeutKin/my.WAveSeedBCphotime")
#Sbcph_time2 = f2.Get("NeutKin/my.WAveSeedBCphotime")
#Sbcph_time3 = f3.Get("NeutKin/my.WAveSeedBCphotime")
#Sbcph_time4 = f4.Get("NeutKin/my.WAveSeedBCphotime")
#Sbcph_time5 = f5.Get("NeutKin/my.WAveSeedBCphotime")


# my W.Ave SC photime Time
SCph_time0 = f0.Get("NeutKin/my.AveSCphotime")
SCph_time1 = f1.Get("NeutKin/my.AveSCphotime")
SCph_time2 = f2.Get("NeutKin/my.AveSCphotime")
SCph_time3 = f3.Get("NeutKin/my.AveSCphotime")
SCph_time4 = f4.Get("NeutKin/my.AveSCphotime")
SCph_time5 = f5.Get("NeutKin/my.AveSCphotime")

# For Seed Time
# Choose Line Colors
ph_time0.SetLineColor(2)
ph_time1.SetLineColor(3)
ph_time2.SetLineColor(4)
ph_time3.SetLineColor(5)
ph_time4.SetLineColor(6)
ph_time5.SetLineColor(7)

# Choose Line Style
ph_time0.SetLineStyle(1)
ph_time1.SetLineStyle(2)
ph_time2.SetLineStyle(5)
ph_time3.SetLineStyle(9)
ph_time4.SetLineStyle(10)
ph_time5.SetLineStyle(3)


#Choose LineWidth
ph_time0.SetLineWidth(1)
ph_time1.SetLineWidth(1)
ph_time2.SetLineWidth(1)
ph_time3.SetLineWidth(1)
ph_time4.SetLineWidth(1)
ph_time5.SetLineWidth(1)


#Choose Marker Style!
#ph_time0.SetMarkerStyle(2)
#ph_time1.SetMarkerStyle(3)
#ph_time2.SetMarkerStyle(4)
#ph_time3.SetMarkerStyle(23)
#ph_time4.SetMarkerStyle(33)
#ph_time5.SetMarkerStyle(34)



# Scale Histograms
if ph_time0.Integral()!=0:
                   ph_time0.Scale(1/ph_time0.Integral())

if ph_time1.Integral()!=0:
                   ph_time1.Scale(1/ph_time1.Integral())

if ph_time2.Integral()!=0:
                   ph_time2.Scale(1/ph_time2.Integral())

if ph_time3.Integral()!=0:
                   ph_time3.Scale(1/ph_time3.Integral())

if ph_time4.Integral()!=0:
                   ph_time4.Scale(1/ph_time4.Integral())

if ph_time5.Integral()!=0:
                   ph_time5.Scale(1/ph_time5.Integral())


# Label Axis
ph_time0.GetXaxis().SetTitle("Photon Time(ns)")
ph_time0.GetYaxis().SetTitle("Event Number")


# For Seed BC Time
# Choose Line Colors
Sbcph_time0.SetLineColor(2)
Sbcph_time1.SetLineColor(3)
Sbcph_time2.SetLineColor(4)
Sbcph_time3.SetLineColor(5)
Sbcph_time4.SetLineColor(6)
Sbcph_time5.SetLineColor(7)

# Choose Line Style
Sbcph_time0.SetLineStyle(1)
Sbcph_time1.SetLineStyle(2)
Sbcph_time2.SetLineStyle(5)
Sbcph_time3.SetLineStyle(9)
Sbcph_time4.SetLineStyle(10)
Sbcph_time5.SetLineStyle(3)


#Choose LineWidth
Sbcph_time0.SetLineWidth(1)
Sbcph_time1.SetLineWidth(1)
Sbcph_time2.SetLineWidth(1)
Sbcph_time3.SetLineWidth(1)
Sbcph_time4.SetLineWidth(1)
Sbcph_time5.SetLineWidth(1)


#Choose Marker Style!
#Sbcph_time0.SetMarkerStyle(2)
#Sbcph_time1.SetMarkerStyle(3)
#Sbcph_time2.SetMarkerStyle(4)
#Sbcph_time3.SetMarkerStyle(23)
#Sbcph_time4.SetMarkerStyle(33)
#Sbcph_time5.SetMarkerStyle(34)



# Scale Histograms
if Sbcph_time0.Integral()!=0:
                   Sbcph_time0.Scale(1/Sbcph_time0.Integral())

if Sbcph_time1.Integral()!=0:
                   Sbcph_time1.Scale(1/Sbcph_time1.Integral())

if Sbcph_time2.Integral()!=0:
                   Sbcph_time2.Scale(1/Sbcph_time2.Integral())

if Sbcph_time3.Integral()!=0:
                   Sbcph_time3.Scale(1/Sbcph_time3.Integral())

if Sbcph_time4.Integral()!=0:
                   Sbcph_time4.Scale(1/Sbcph_time4.Integral())

if Sbcph_time5.Integral()!=0:
                   Sbcph_time5.Scale(1/Sbcph_time5.Integral())


# Label Axis
Sbcph_time0.GetXaxis().SetTitle("Photon Time(ns)")
Sbcph_time0.GetYaxis().SetTitle("Event Number")


# For Seed Time
# Choose Line Colors
SCph_time0.SetLineColor(2)
SCph_time1.SetLineColor(3)
SCph_time2.SetLineColor(4)
SCph_time3.SetLineColor(5)
SCph_time4.SetLineColor(6)
SCph_time5.SetLineColor(7)

# Choose Line Style
SCph_time0.SetLineStyle(1)
SCph_time1.SetLineStyle(2)
SCph_time2.SetLineStyle(5)
SCph_time3.SetLineStyle(9)
SCph_time4.SetLineStyle(10)
SCph_time5.SetLineStyle(3)


#Choose LineWidth
SCph_time0.SetLineWidth(1)
SCph_time1.SetLineWidth(1)
SCph_time2.SetLineWidth(1)
SCph_time3.SetLineWidth(1)
SCph_time4.SetLineWidth(1)
SCph_time5.SetLineWidth(1)


#Choose Marker Style!
#SCph_time0.SetMarkerStyle(2)
#SCph_time1.SetMarkerStyle(3)
#SCph_time2.SetMarkerStyle(4)
#SCph_time3.SetMarkerStyle(23)
#SCph_time4.SetMarkerStyle(33)
#SCph_time5.SetMarkerStyle(34)



# Scale Histograms
if SCph_time0.Integral()!=0:
                   SCph_time0.Scale(1/SCph_time0.Integral())

if SCph_time1.Integral()!=0:
                   SCph_time1.Scale(1/SCph_time1.Integral())

if SCph_time2.Integral()!=0:
                   SCph_time2.Scale(1/SCph_time2.Integral())

if SCph_time3.Integral()!=0:
                   SCph_time3.Scale(1/SCph_time3.Integral())

if SCph_time4.Integral()!=0:
                   SCph_time4.Scale(1/SCph_time4.Integral())

if SCph_time5.Integral()!=0:
                   SCph_time5.Scale(1/SCph_time5.Integral())


# Label Axis
SCph_time0.GetXaxis().SetTitle("Photon Time(ns)")
SCph_time0.GetYaxis().SetTitle("Event Number")


# Draw Plots now
# ************************************************************************************
# Seed Xtal
c1 = TCanvas("c1", "Photon Time", 800, 800)
c1.cd()

ph_time0.SetTitle("Photon(Seed Xtal)Time Distribution")

ph_time0.Draw()
ph_time1.Draw("sames")
ph_time2.Draw("sames")
ph_time3.Draw("sames")
ph_time4.Draw("sames")
ph_time5.Draw("sames")
ph_time0.GetXaxis().SetRangeUser(-25.0, 25.0)
#Add Legend
leg1 = TLegend( 0.14, 0.70, 0.47, 0.90)
leg1.SetBorderSize(1)
leg1.SetFillColor(0)
leg1.AddEntry(ph_time0,"0 Jet + VLIso#gamma ","l")
leg1.AddEntry(ph_time1,"1 Jet + VLIso#gamma ","l")
leg1.AddEntry(ph_time2,"2 Jet + VLIso#gamma ","l")
leg1.AddEntry(ph_time3,"3 Jet + VLIso#gamma ","l")
leg1.AddEntry(ph_time4,"4 Jet + VLIso#gamma ","l")
leg1.AddEntry(ph_time5,"5 Jet + VLIso#gamma ","l")
leg1.SetTextSize(0.018)
leg1.SetHeader("Number of Jets")
leg1.Draw()

#  W. Ave Seed BC
c2 = TCanvas("c2", "Photon Time", 800, 800)
c2.cd()

Sbcph_time0.SetTitle("Photon(W .Ave Seed BC)Time Distribution")

Sbcph_time0.Draw()
Sbcph_time1.Draw("sames")
Sbcph_time2.Draw("sames")
Sbcph_time3.Draw("sames")
Sbcph_time4.Draw("sames")
Sbcph_time5.Draw("sames")
Sbcph_time0.GetXaxis().SetRangeUser(-25.0, 25.0)
#Add Legend
leg2 = TLegend( 0.14, 0.70, 0.47, 0.90)
leg2.SetBorderSize(1)
leg2.SetFillColor(0)
leg2.AddEntry(Sbcph_time0,"0 Jet + VLIso#gamma ","l")
leg2.AddEntry(Sbcph_time1,"1 Jet + VLIso#gamma ","l")
leg2.AddEntry(Sbcph_time2,"2 Jet + VLIso#gamma ","l")
leg2.AddEntry(Sbcph_time3,"3 Jet + VLIso#gamma ","l")
leg2.AddEntry(Sbcph_time4,"4 Jet + VLIso#gamma ","l")
leg2.AddEntry(Sbcph_time5,"5 Jet + VLIso#gamma ","l")
leg2.SetTextSize(0.018)
leg2.SetHeader("Number of Jets")
leg2.Draw()

# SC Time
c3 = TCanvas("c3", "Photon Time", 800, 800)
c3.cd()

SCph_time0.SetTitle("Photon(W. Ave SC)Time Distribution")
SCph_time0.Draw()
SCph_time1.Draw("sames")
SCph_time2.Draw("sames")
SCph_time3.Draw("sames")
SCph_time4.Draw("sames")
SCph_time5.Draw("sames")
SCph_time0.GetXaxis().SetRangeUser(-25.0, 25.0)
#Add Legend
leg3 = TLegend( 0.14, 0.70, 0.47, 0.90)
leg3.SetBorderSize(1)
leg3.SetFillColor(0)
leg3.AddEntry(SCph_time0,"0 Jet + VLIso#gamma ","l")
leg3.AddEntry(SCph_time1,"1 Jet + VLIso#gamma ","l")
leg3.AddEntry(SCph_time2,"2 Jet + VLIso#gamma ","l")
leg3.AddEntry(SCph_time3,"3 Jet + VLIso#gamma ","l")
leg3.AddEntry(SCph_time4,"4 Jet + VLIso#gamma ","l")
leg3.AddEntry(SCph_time5,"5 Jet + VLIso#gamma ","l")
leg3.SetTextSize(0.018)
leg3.SetHeader("Number of Jets")
leg3.Draw()


  
#_______________________ Save Plots_______________________#

c1.SetLogy(1)
c1.SaveAs("Photon_SeedXtalTime_Distribution_VsJetMultiplicity.png")

c2.SetLogy(1)
c2.SaveAs("Photon_W_AveSeedBCTime_Distribution_VsJetMultiplicity.png")

c2.SetLogy(1)
c2.SaveAs("Photon_W_AveSCTime_Distribution_VsJetMultiplicity.png")



















