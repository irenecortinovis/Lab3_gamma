/*
compile with:
g++ FWHM.cpp -o FWHM.o `root-config --cflags --glibs`
*/
#include <fstream>
#include <TMultiGraph.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TCanvas.h>
#include <TApplication.h>
#include <TStyle.h>
#include <TROOT.h>
#include <string>
#include <TLegend.h>


int main() {
	TApplication* Grafica = new TApplication("Grafica", 0, NULL);
	TGraphErrors *fwhm = new TGraphErrors("FWHM_vs_Energy.txt", "%lg %lg %lg %lg");	//Leggo le prime due colonne
	TLegend *legend = new TLegend(0.65, 0.65, 0.85, 0.85);
	fwhm->SetTitle("FWHM vs Energy; Energy; FWHM");
	fwhm->SetMarkerColor(kBlue);
	fwhm->SetLineColor(kBlue);
	fwhm->SetMarkerStyle(7);
	fwhm->SetMarkerSize(5);


  /*TF1 *fitfano = new TF1("fitfano", "sqrt([0] + [1]*(x) + [2]*(x**2)) ", 0, 1600.);
	fitfano->SetParName(0, "b^{2}");
  fitfano->SetParName(1, "a^{2}");
  fitfano->SetParName(2, "c^{2}");
  fitfano->SetParameter(0,0);
  fitfano->SetParameter(1,0);
	fitfano->SetParameter(2,0);*/


  TF1 *fitfano = new TF1("fitfano", "sqrt([0]*2.96*x) ", 0, 1600.);
	fitfano->SetParName(0, "b^{2}");
	fitfano->SetParameter(0,0.1);


	gStyle->SetOptFit(1111);

	TCanvas *c1 = new TCanvas("FWHM_vs_Energy","FWHM_vs_Energy",800,600);
	fwhm->Draw("ape");
	//legend->Draw();
  fwhm->Fit("fitfano", "R");

	c1->Print("FWHM_vs_Energy.png");

	Grafica->Run();
	return 0;
}
