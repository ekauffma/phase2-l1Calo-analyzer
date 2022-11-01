/*******************************************************************/
/* efficiencyHist.cpp                                              */
/* Author: Stephanie Kwan                                          */
/*******************************************************************/

#include "TGraphAsymmErrors.h"
#include "TH1.h"
#include "TH1F.h"

#include "TAxis.h"
#include "TChain.h"

#include "THStack.h"
#include "TLegend.h"
#include "TPad.h"
#include "TPaveText.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TTree.h"

#include <assert.h>
#include <cmath>
#include <iostream>
#include <math.h>
#include <string>
#include <TMath.h>
#include <vector>

#include "../baseCodeForPlots/tdrstyle.C"
#include "../baseCodeForPlots/comparisonPlots.C"

#ifndef EFFICIENCY_HIST_CPP_INCL
#define EFFICIENCY_HIST_CPP_INCL

/*******************************************************************/

void plotNEfficiencies(std::vector<TGraphAsymmErrors*> graphs, 
             std::vector<TString> labels,
             std::vector<int> colors,
             TString xAxisLabel,
             TString legendName,
             TString outputName,
             TString outputDir,
             TString additionalComment = ""
             ) {
  assert((graphs.size() == labels.size()) && (graphs.size() == colors.size()));

  setTDRStyle();
  TCanvas* Tcan = new TCanvas("Tcan","", 100, 20, 1000, 800);
  TLegend* leg = new TLegend(0.55,0.15,0.90,0.45);
  applySmallerLegStyle(leg);

  Tcan->SetGrid();

  TLatex *latex = new TLatex(); 
  latex->SetNDC();
  latex->SetTextFont(42);
  latex->SetTextColor(kBlack);

  // Set current canvas
  Tcan->cd();  
  Tcan->SetFillColor(0);


  std::vector<TGraphAsymmErrors*>::iterator itGraph;
  std::vector<TString>::iterator itLabel;
  std::vector<int>::iterator itColor;
  
  TGraphAsymmErrors* histDummy;
  for (itGraph = graphs.begin(), itLabel = labels.begin(), itColor = colors.begin();
       itGraph != graphs.end();
       itGraph++, itLabel++, itColor++) {

    // only do this once 
    if (itGraph == graphs.begin()) {
      histDummy = new TGraphAsymmErrors(**itGraph);
    }
      
    // De-reference the iterator to get the TGraphAsymmErrors*
    (*itGraph)->SetMarkerColor(*itColor);
    (*itGraph)->SetMarkerStyle(kFullCircle);
    (*itGraph)->SetLineWidth(2);
    (*itGraph)->SetLineColor(*itColor);
    (*itGraph)->SetMarkerSize(2);
  }

  histDummy->SetMarkerColor(0);
  histDummy->SetLineColor(0);

  histDummy->Draw("");

  for (itGraph = graphs.begin(); itGraph != graphs.end(); itGraph++)  {
    (*itGraph)->Draw("P");
  }

  histDummy->GetXaxis()->SetTitle(xAxisLabel);
  histDummy->GetYaxis()->SetTitle("L1 Efficiency");
  histDummy->GetXaxis()->SetTitleSize(0.06); // default is 0.03                                                                    
  /* Set y-axis limits */  
  histDummy->GetYaxis()->SetRangeUser(0.0, 1.1);
  // histDummy->GetYaxis()->SetRangeUser(0.8, 1.02);

  // Customize legend 

  for (itGraph = graphs.begin(), itLabel = labels.begin();
       itGraph != graphs.end();
       itGraph++, itLabel++)
    {
      leg->AddEntry(*itGraph, "#scale[0.8]{" + *itLabel + "}",  "P");
    }
  leg->Draw();


  // Default to RCT label, use GCT if not
  TString emuLabel = "#scale[1.0]{#bf{CMS}} #scale[0.8]{#it{Phase 2 GCT emulator}}";  
  if (outputName.Contains("RCT")) {
    emuLabel = "#scale[1.0]{#bf{CMS}} #scale[0.8]{#it{Phase 2 RCT emulator}}";  
  }
  latex->DrawLatex(0.16, 0.960, emuLabel); 
  latex->DrawLatex(0.58, 0.960, "#scale[0.8]{200 PU, DoubleEle Pt 1 to 100}"); 

  // Commentary x and y-position
  float commentaryXpos = 0.50;
  float yRow1 = 0.540;
  float yRow2 = 0.480;
  float yRow3 = 0.420;

  latex->DrawLatex(commentaryXpos, yRow2, "#scale[0.8]{Phase-2 L1EG (Crystal, Barrel)}");
  latex->DrawLatex(commentaryXpos, yRow3, "#scale[0.8]{L1 p_{T} > 25, |#eta^{Gen}| < 1.4841" + additionalComment + "}");
  Tcan->Update();


  Tcan->cd();
  Tcan->SaveAs(outputDir+outputName+".pdf");
  Tcan->SaveAs(outputDir+outputName+".png");

  Tcan->Close();
  delete Tcan;
}
             

/*******************************************************************/

#endif
