/*
compile with:
g++ correlation.cpp -o correlation.o `root-config --cflags --glibs`
*/

//This program fits the angular correlation graph of 511 keV back to back emission with the Fermi-Dirac function

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

int main(int argc, char **argv) {
	TApplication* Grafica = new TApplication("Grafica", 0, NULL);
	TGraphErrors *angles = new TGraphErrors("Na22_correlation.txt", "%lg %lg %lg");
	double *x = angles->GetX();
	for(int i = 0; i < angles->GetN(); i++) {
		angles->SetPointError(i, 3, sqrt(x[i]));		//(i, ex, ey)
	}

	TF1 *fermidirac = new TF1("fd", "[0]/(exp([1]*(x-[2])) + 1)", 0., 30.);
	TF1 *cos2 = new TF1("cos2", "[0]*cos([1]*x)**2 + [2]", 0., 30.);
	fermidirac->SetParName(0, "N_{0}");
	fermidirac->SetParName(1, "#alpha");
	fermidirac->SetParName(2, "#theta_{0}");
	fermidirac->SetParameters(408710., 0.446, 14.);
	cos2->SetParName(0, "N_{0}");
	cos2->SetParName(1, "#omega");
	cos2->SetParName(2, "N_{offset}");
	cos2->SetParameters(410000., 0.1, 1800.);
	angles->SetTitle("Angular correlation 511 keV; #theta (#circ); N_{counts}");
	angles->SetMarkerColor(kBlue);
	angles->SetLineColor(kBlue);
	angles->SetMarkerStyle(7);
	angles->SetMarkerSize(5);

	gStyle->SetOptFit(1111);

	TCanvas *c1 = new TCanvas("counts_vs_theta","counts_vs_theta",800,600);
	angles->Draw("ape");
	//fermidirac->Draw("same");
	angles->Fit("fd", "R");
	//angles->Fit("cos2", "R");
	c1->Print("counts_vs_theta.png");

	Grafica->Run();
	return 0;
}
