#  Tool Scales and put Histograms  in same file for HisFactory
## Aurthor Tambe E. Norbert a.k.a TEN (norbert@physics.umn.edu)

#!/usr/bin/env python
""" Scale and put histograms in same root file!"""
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
gStyle.SetOptStat("emruo")

fout = TFile("Scaled_Hist_Files.root", "RECREATE")

#Get files
fmea = TFile("Analysis_DPTrigger_Displaced_Photon_0Jet-Sample.root")
fsig = TFile("Analysis_DPTrigger_Displaced_Photon_0Jet-Sample.root")

SF = 700
#Get Histograms
h_data = fmea.Get("Analysis_DPTrigger_Displaced_Photon_0Jet-Sample.root/BkgEst/NCrysInTimeSliceEB_6")
#h_data.Scale( h_bg.Integral(-2,2)/h_data.Integral(-2,2) )
h_bg   = fmea.Get("Analysis_DPTrigger_Displaced_Photon_0Jet-Sample.root/BkgEst/NCrysInTimeSliceEB_11")
h_bg2   = h_bg2.Clone("Analysis_DPTrigger_Displaced_Photon_0Jet-Sample.root/BkgEst/NCrysInTimeSliceEB_11")
#h_sg   = fsig.Get("sig_gmsb6000.root/h_sgTime")


#h_data.Scale( h_bg.Integral(-2,2)/h_data.Integral(-2,2) )
h_bg.Scale(SF)
h_bg2.Scale(SF)


fout.cd()
h_data.Write()
h_bg.Write()
h_bg2.Write()
#h_sg.Write()

fout.Close()


