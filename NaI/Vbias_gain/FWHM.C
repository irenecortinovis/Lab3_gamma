#include <iostream>

#include "TCanvas.h"
#include "TF1.h"
#include "TLegend.h"
#include "TGraph2DErrors.h"
#include "cmath"

using namespace std;

void ImpedenzaL() {

  //inserire R (valore noto)

  // *** IMPEDENZA di L ***

  //Grafico
  auto c9 = new TCanvas;
  c9->SetGrid();
  gStyle->SetOptFit(1111);
  //importo i dati da file .txt, creo grafico con errori
  TGraph2DErrors Impedenza ("./FWHM_vs_vbias.txt", "%lg %lg %lg %lg %lg %lg");
  Impedenza.SetTitle("PEAK1 (511); V_BIAS; GAIN; FWHM");
  Impedenza.SetMarkerColor(kBlue);
  Impedenza.SetMarkerStyle(7);
  Impedenza.SetFillColor(0);
  Impedenza.Draw("APE");


  c9->Print("ImpedenzaL.png");

//------------------------------------------------------------------------------

}
