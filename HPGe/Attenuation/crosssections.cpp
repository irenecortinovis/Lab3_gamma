/*
compile with:
g++ crosssections.cpp -o crosssections.o `root-config --cflags --glibs`
*/
#include <iostream>
#include <stdlib.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TCanvas.h>
#include <TF1.h>
#include <TApplication.h>
#include <TStyle.h>
#include <TROOT.h>
#include <TLegend.h>
#include <cmath>

int main(int argc, char **argv) {
	TApplication* Grafica = new TApplication("Grafica", 0, NULL);
  gStyle->SetOptFit(1111);


  //the order is: water, copper, lead

  double density[] = {997000,8960000,11340000}; //gm-3
  double nAv = 6.02e23;
  double molarmass[] = {18.015,63.5,207.2}; //gmol-1
  double Zeta[] = {10,29,82};
  double Zeta_err[] = {0,0,0};
  double Mu[] = {5.8,49,67};
  double Mu_err[] = {0.2,15,5};

  double n0[3];
  double y[3];
  double y_err[3];

  for(int i=0; i<3; i++)
  {
    n0[i] = (density[i] / molarmass[i]) * nAv * Zeta[i];
    y[i] = Mu[i] / n0[i];
    y_err[i] = Mu_err[i] / n0[i];

  }


  TGraphErrors *attenuation = new TGraphErrors(3, &Zeta[0], &y[0], &Zeta_err[0], &y_err[0]);
  /*TF1 *fitatt = new TF1("fitatt", "[0]*(x**5) + [1]*x ", 0., 110.);
	fitatt->SetParName(0, "A_{PE}");
	fitatt->SetParName(1, "A_{compt}");
  fitatt->FixParameter(0,1e-10);
	fitatt->SetParameter(1,0.09);*/
	attenuation->SetTitle("Cross sections; #Z ; #Mu / n_e");
	attenuation->SetMarkerColor(kBlue);
	attenuation->SetLineColor(kBlue);
	attenuation->SetMarkerStyle(7);
	attenuation->SetMarkerSize(5);

  TCanvas *c1 = new TCanvas("Cross sections","Cross sections",1400,800);
	attenuation->Draw("ape");
	//attenuation->Fit("fitatt", "R");



  Grafica->Run();
  return 0;
}
