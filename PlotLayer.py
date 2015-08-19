# This Simple Code Overlays Histograms Plots  from Different Files
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
gStyle.SetOptStat(0)

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
f1 =  TFile("Less3Jets_All_Trig.root")
f2 =  TFile("More3Jets_All_Trig.root")
f3 =  TFile("gmsbsum12_ctau200_L140_All_Trig.root")

#Get input directories
#d1 = TDirectory("/afs/cern.ch/user/t/tambe/www/GMSBAnalysis/NJetsEffect/NewPlotsMay22/MoreThan3Jets","","",)
#d2 = TDirectory("/afs/cern.ch/user/t/tambe/www/GMSBAnalysis/NJetsEffect/NewPlotsMay22/LessThan3Jets","","",)
#d3 = TDirectory("/afs/cern.ch/user/t/tambe/www/GMSBAnalysis/NJetsEffect/NewPlotsMay22/GmsB250cmMC","","",)


ph_time1 = f1.Get("NeutKin/my.h_Time")
ph_time2 = f2.Get("NeutKin/my.h_Time")
ph_time3 = f3.Get("NeutKin/my.h_Time") 
#Event Met
evt_met1 = f1.Get("NeutKin/my.evt_met") 
evt_met2 = f2.Get("NeutKin/my.evt_met")
evt_met3 = f3.Get("NeutKin/my.evt_met")

nph1   = f1.Get("NeutKin/my.npho")
nph2   = f2.Get("NeutKin/my.npho")
nph3   = f3.Get("NeutKin/my.npho")

njets1 = f1.Get("NeutKin/my.njets")
njets2 = f2.Get("NeutKin/my.njets")
njets3 = f3.Get("NeutKin/my.njets")
#  Mean Time
#tA_EE_low6 = f6.Get("single-bias/timeVsAoSigmaHighEElog_1")
#tA_EE_low7 = f7.Get("single-bias/timeVsAoSigmaHighEElog_1")

#  Sigma of Time 
#sA_EE_low4 = f4.Get("single-bias/timeVsAoSigmaHighEElog_2")
#sA_EE_low5 = f5.Get("single-bias/timeVsAoSigmaHighEElog_2")
#sA_EE_low6 = f6.Get("single-bias/timeVsAoSigmaHighEElog_2")
#sA_EE_low7 = f7.Get("single-bias/timeVsAoSigmaHighEElog_2")



# Choose Line Colors
ph_time1.SetLineColor(6)
ph_time2.SetLineColor(9)
ph_time3.SetLineColor(12)

evt_met1.SetLineColor(6)
evt_met2.SetLineColor(9)
evt_met3.SetLineColor(12)

nph1.SetLineColor(6)
nph2.SetLineColor(9)
nph3.SetLineColor(12)

njets1.SetLineColor(6)
njets2.SetLineColor(9)
njets3.SetLineColor(12)

ph_time1.SetLineWidth(4)
ph_time2.SetLineWidth(2)
ph_time3.SetLineWidth(3)


evt_met1.SetLineWidth(4)
evt_met2.SetLineWidth(2)
evt_met3.SetLineWidth(3)

nph1.SetLineWidth(4)
nph2.SetLineWidth(2)
nph3.SetLineWidth(3)

njets1.SetLineWidth(4)
njets2.SetLineWidth(2)
njets3.SetLineWidth(3)

#sA_EE_low3.SetLineColor(4)
#sA_EE_low4.SetLineColor(5)
#sA_EE_low5.SetLineColor(6)
#sA_EE_low6.SetLineColor(7)
#sA_EE_low7.SetLineColor(8)

# Choose Fill Colors
#ph_time1.SetFillColor(6)
#ph_time2.SetFillColor(9)
#ph_time3.SetFillColor(12)

#evt_met1.SetFillColor(6)
#evt_met2.SetFillColor(9)
#evt_met3.SetFillColor(12)


#Choose Marker Style!
ph_time1.SetMarkerStyle(6)
ph_time2.SetMarkerStyle(9)
ph_time3.SetMarkerStyle(12)

evt_met1.SetMarkerStyle(6)
evt_met2.SetMarkerStyle(9)
evt_met3.SetMarkerStyle(12)


nph1.SetMarkerStyle(6)
nph2.SetMarkerStyle(9)
nph3.SetMarkerStyle(10)


njets1.SetMarkerStyle(6)
njets2.SetMarkerStyle(9)
njets3.SetMarkerStyle(10)



# Scale Histograms
if ph_time1.Integral()!=0:
                   ph_time1.Scale(1/ph_time1.Integral())

if ph_time2.Integral()!=0:
                   ph_time2.Scale(1/ph_time2.Integral())

if ph_time3.Integral()!=0:
                   ph_time3.Scale(1/ph_time3.Integral())



if evt_met1.Integral()!=0:
                   evt_met1.Scale(1/evt_met1.Integral())


if evt_met2.Integral()!=0:
                   evt_met2.Scale(1/evt_met2.Integral())


if evt_met3.Integral()!=0:
                  evt_met3.Scale(1/evt_met3.Integral())




#tA_EBMod4.SetMarkerStyle(1)
#tA_EE_low1.SetMarkerStyle(2)
#tA_EE_low2.SetMarkerStyle(3)
#tA_EE_low3.SetMarkerStyle(4)
#tA_EE_low4.SetMarkerStyle(5)
#tA_EE_low5.SetMarkerStyle(6)
#tA_EE_low6.SetMarkerStyle(7)
#tA_EE_low7.SetMarkerStyle(8)
 #SIgma
#sA_EBMod4.SetMarkerStyle(1)
#sA_EE_low1.SetMarkerStyle(2)
#sA_EE_low2.SetMarkerStyle(3)
#sA_EE_low3.SetMarkerStyle(4)
#sA_EE_low4.SetMarkerStyle(5)
#sA_EE_low5.SetMarkerStyle(6)
#sA_EE_low6.SetMarkerStyle(7)
#sA_EE_low7.SetMarkerStyle(8)

#SetMaxRange XY Axis
#tA_EBMod4.GetYaxis().SetRangeUser(-1.0,0.4)
#tA_EBMod4.GetXaxis().SetRangeUser(0.0,10000.0)

ph_time1.GetXaxis().SetTitle("Photon Time(ns)")
ph_time1.GetYaxis().SetTitle("Event Number")

evt_met1.GetXaxis().SetTitle("MET(GeV)")
evt_met1.GetYaxis().SetTitle("Event Number")



nph1.GetXaxis().SetTitle("Number of Leading Pt Photons")
nph1.GetYaxis().SetTitle("Event Number")


njets1.GetXaxis().SetTitle("Number of Leading Pt Jets")
njets1.GetYaxis().SetTitle("Event Number")

#sA_EBMod4.GetYaxis().SetRangeUser(0.0,3.5)
#sA_EBMod4.GetXaxis().SetRangeUser(0.0,10000.0)
#sA_EBMod4.GetXaxis().SetTitle("Amplitude(ADC Counts)")
#sA_EBMod4.GetYaxis().SetTitle("#sigma Time(ns)")


# Draw Plots now
# *************************************************************************************
c1 = TCanvas("c1", "Photon Time", 800, 800)
c1.cd()
# ht->GetXaxis()->SetTitle("Energy(GeV)");
#  ht->GetYaxis()->SetTitle("Mean Time(ns)");
#  ht->GetYaxis()->SetRangeUser(-0.8,0.3);
#  ht->GetXaxis()->SetRangeUser(0, 10000);

ph_time1.SetTitle("Photon Time Distribution")
#tA_EBMod4.SetTitle("Mean Time Vs Amplitude Stability")

ph_time1.Draw()
ph_time2.Draw("sames")
ph_time3.Draw("sames")
#Add Legend
leg1 = TLegend( 0.14, 0.70, 0.47, 0.90)
leg1.SetBorderSize(1)
leg1.SetFillColor(0)
leg1.AddEntry(ph_time1,"< 3Jets + VLIso#gamma ","l")
leg1.AddEntry(ph_time2,">= 3Jets + VLIso#gamma ","l")
leg1.AddEntry(ph_time3,"GMSB-c#tau=3000mm-#Lambda=140TeV","l")
leg1.SetTextSize(0.018)
leg1.SetHeader("Samples")
#leg1.AddEntry(tA_EE_low3,"1.9 <|#eta|<2.2","l")
#leg1.AddEntry(tA_EE_low4,"2.2 <|#eta|<2.4","l")
#leg1.AddEntry(tA_EE_low5,"2.4 <|#eta|<2.6","l")
#leg1.AddEntry(tA_EE_low6,"2.6 <|#eta|<2.8","l")
#leg1.AddEntry(tA_EE_low7,"2.8 <|#eta|<3.0","l")
leg1.Draw()

# Use for MET Plot 
c2 = TCanvas ( "c2", "Sigma Time Stability", 800, 800)
c2.cd()
#  ht->GetXaxis()->SetTitle("Energy(GeV)");
#  ht->GetYaxis()->SetTitle("#sigma Time(ns)");
#  ht->GetYaxis()->SetRangeUser(0,3.5);
#  ht->GetXaxis()->SetRangeUser(0, 10000);

evt_met1.SetTitle("Missing Energy Distribution") 
evt_met1.Draw()
evt_met2.Draw("sames")
evt_met3.Draw("sames")

#Add Legend
leg2 = TLegend( 0.35, 0.55, 0.73, 0.77)
leg2.SetBorderSize(1)
leg2.SetFillColor(0)
leg2.AddEntry(evt_met1,"< 3Jets + VLIso #gamma ","l")
leg2.AddEntry(evt_met2,">= 3Jets + VLIso #gamma","l")
leg2.AddEntry(evt_met3,"GMSB-c#tau=3000mm-#Lambda=140TeV","l")
leg2.SetHeader("Samples")
leg2.SetTextSize(0.02)
#leg2 = TLegend( 0.8, 0.55, 0.98,0.77)
#leg2.SetBorderSize(1)
#leg2.SetFillColor(0)
leg2.Draw()



# Number of Photons in Event
c3 = TCanvas("c3", "Photon Time", 800, 800)
c3.cd()
# ht->GetXaxis()->SetTitle("Energy(GeV)");
#  ht->GetYaxis()->SetTitle("Mean Time(ns)");
#  ht->GetYaxis()->SetRangeUser(-0.8,0.3);
#  ht->GetXaxis()->SetRangeUser(0, 10000);

nph1.SetTitle("Number of Leading Pt Photons")
#tA_EBMod4.SetTitle("Mean Time Vs Amplitude Stability")

nph1.Draw()
nph2.Draw("sames")
nph3.Draw("sames")
#ph_time3.Draw("sames")

#Add Legend
leg3 = TLegend( 0.52, 0.45, 0.85, 0.70)
leg3.SetBorderSize(1)
leg3.SetFillColor(0)
leg3.AddEntry(ph_time1,"< 3Jets + VLIso #gamma ","l")
leg3.AddEntry(ph_time2,">= 3Jets + VLIso #gamma ","l")
leg3.AddEntry(ph_time3,"GMSB-c#tau=2000mm-#Lambda=140TeV","l")
leg3.SetTextSize(0.018)
leg3.SetHeader("Samples")
#leg1.AddEntry(tA_EE_low3,"1.9 <|#eta|<2.2","l")
#leg1.AddEntry(tA_EE_low4,"2.2 <|#eta|<2.4","l")
#leg1.AddEntry(tA_EE_low5,"2.4 <|#eta|<2.6","l")
#leg1.AddEntry(tA_EE_low6,"2.6 <|#eta|<2.8","l")
#leg1.AddEntry(tA_EE_low7,"2.8 <|#eta|<3.0","l")
leg3.Draw()

# Number of Jets
c4 = TCanvas("c4", "Photon Time", 800, 800)
c4.cd()
# ht->GetXaxis()->SetTitle("Energy(GeV)");
#  ht->GetYaxis()->SetTitle("Mean Time(ns)");
#  ht->GetYaxis()->SetRangeUser(-0.8,0.3);
#  ht->GetXaxis()->SetRangeUser(0, 10000);

njets1.SetTitle("Number of Leading Pt Jets")
#tA_EBMod4.SetTitle("Mean Time Vs Amplitude Stability")

njets1.Draw()
njets2.Draw("sames")
njets3.Draw("sames")
#Add Legend
leg4 = TLegend( 0.14, 0.70, 0.47, 0.90)
leg4.SetBorderSize(1)
leg4.SetFillColor(0)
leg4.AddEntry(ph_time1,"< 3Jets + VLIso#gamma","l")
leg4.AddEntry(ph_time2,">= 3Jets + VLIso#gamma ","l")
leg4.AddEntry(ph_time3,"GMSB-c#tau=2000mm-#Lambda=140TeV","l")
leg4.SetTextSize(0.018)
leg4.SetHeader("Samples")
#leg1.AddEntry(tA_EE_low3,"1.9 <|#eta|<2.2","l")
#leg1.AddEntry(tA_EE_low4,"2.2 <|#eta|<2.4","l")
#leg1.AddEntry(tA_EE_low5,"2.4 <|#eta|<2.6","l")
#leg1.AddEntry(tA_EE_low6,"2.6 <|#eta|<2.8","l")
#leg1.AddEntry(tA_EE_low7,"2.8 <|#eta|<3.0","l")
leg4.Draw()

  
# Save Plots
#c1.SaveAs("PhotonTimeComparing.png")
c1.SetLogy(1)
c1.SaveAs("PhotonTimeCompareLog.png")

#c2.SaveAs("EventMet.png")
c2.SetLogy(1)
c2.SaveAs("EventMetComparingLog.png")

c3.SetLogy(1)
c3.SaveAs("NumberPhotonsComparingLog.png")

c4.SetLogy(1)
c4.SaveAs("NumberOfJetsComparingLog.png")



