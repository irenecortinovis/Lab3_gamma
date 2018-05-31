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
	TGraph *fwhm = new TGraphErrors("FWHM_vs_Energy.txt", "%lg %lg");	//Leggo le prime due colonne
	//TGraph *fwhm2= new TGraph("FWHM_vs_vbias.txt", "%lg %*lg %lg");		//Leggo la prima e la terza colonna
	TLegend *legend = new TLegend(0.65, 0.65, 0.85, 0.85);
	fwhm1->SetTitle("peak1; V_{bias} (V); FWHM");
	fwhm1->SetMarkerColor(kBlue);
	fwhm1->SetLineColor(kBlue);
	fwhm1->SetMarkerStyle(7);
	fwhm1->SetMarkerSize(5);
	fwhm2->SetTitle("peak2; V_{bias} (V); FWHM");
	fwhm2->SetMarkerColor(kRed);
	fwhm2->SetLineColor(kRed);
	fwhm2->SetMarkerStyle(7);
	fwhm2->SetMarkerSize(5);

	//fwhm1->RemovePoint(0);	//HARDCODED: per V_bias = 2000 FWHM = 60... bug
	//fwhm2->RemovePoint(0);

	TMultiGraph *gr = new TMultiGraph();
	gr->Add(fwhm1);
	gr->Add(fwhm2);
	gr->SetTitle("FWHM vs V_{bias}; V_{bias} (V); FWHM");

	legend->AddEntry(fwhm1, "Peak 1", "l");
	legend->AddEntry(fwhm2, "Peak 2", "l");
	gStyle->SetOptFit(1111);

	TCanvas *c1 = new TCanvas("FWHM_vs_vbias","FWHM_vs_vbias",800,600);
	gr->Draw("apec");
	legend->Draw();
	c1->Print("FWHM_vs_vbias.png");

	Grafica->Run();
	return 0;
}
