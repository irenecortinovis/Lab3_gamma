#include <iostream>

#include "TCanvas.h"
#include "TF1.h"
#include "TLegend.h"
#include "TGraph2DErrors.h"
#include "cmath"
#include "TStyle.h"
#include "fstream"
#include "TApplication.h"
#include "TAxis.h"
#include "TAttMarker.h"

using namespace std;

int main(){

  TApplication* Grafica = new TApplication("Grafica", 0, NULL);

  std::ifstream input ("./FWHM_vs_vbias.txt", std::ios::in);
  double v_bias, v_bias_err, gain, gain_err, fwhm1, fwhm1_err, fwhm2, fwhm2_err;
	int npoints = 0;



  //Grafico
  TCanvas* c9 = new TCanvas("FWHM", "FWHM", 800, 800);
  c9->Divide(2,1);
  gStyle->SetOptFit(1111);
  //importo i dati da file .txt, creo grafico con errori
  TGraph2DErrors* fwhmgraph1 = new TGraph2DErrors ();
  fwhmgraph1->SetTitle("PEAK1 (511)");
  fwhmgraph1->SetMarkerColor(kBlue);
  fwhmgraph1->SetMarkerStyle(7);
  fwhmgraph1->SetFillColor(0);
  fwhmgraph1->GetXaxis()->SetTitle("V_BIAS");
  fwhmgraph1->GetYaxis()->SetTitle("GAIN");
  fwhmgraph1->GetZaxis()->SetTitle("FWHM");


  TGraph2DErrors* fwhmgraph2 = new TGraph2DErrors ();
  fwhmgraph2->SetTitle("PEAK2 (1274)");
  fwhmgraph2->SetMarkerColor(kBlue);
  fwhmgraph2->SetMarkerStyle(7);
  fwhmgraph2->SetMarkerSize(3);
  fwhmgraph2->SetFillColor(0);
  fwhmgraph2->GetXaxis()->SetTitle("V_BIAS");
  fwhmgraph2->GetYaxis()->SetTitle("GAIN");
  fwhmgraph2->GetZaxis()->SetTitle("FWHM");

  while(input >> v_bias >> v_bias_err >> gain >> gain_err >> fwhm1 >> fwhm1_err >> fwhm2 >> fwhm2_err)
  {
    fwhmgraph1 -> SetPoint (npoints, v_bias, gain, fwhm1);
    fwhmgraph1 -> SetPointError (npoints, v_bias_err, gain_err, fwhm1_err);
    fwhmgraph2 -> SetPoint (npoints, v_bias, gain, fwhm2);
    fwhmgraph2 -> SetPointError (npoints, v_bias_err, gain_err, fwhm2_err);
		++npoints;
	}

  c9->cd(1);
  fwhmgraph1->Draw("P");
  c9->cd(2);
  fwhmgraph2->Draw("P");

  Grafica->Run();



  c9->Print("FWHM.png");

//------------------------------------------------------------------------------

}
