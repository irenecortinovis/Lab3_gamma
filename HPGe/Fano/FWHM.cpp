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
#include <TLatex.h>


int main() {
	TApplication* Grafica = new TApplication("Grafica", 0, NULL);
	TGraphErrors *fwhm = new TGraphErrors("FWHM_vs_Energy.txt", "%lg %lg %lg %lg");	//Leggo le prime due colonne
	TLegend *legend = new TLegend(0.65, 0.65, 0.85, 0.85);
	fwhm->SetTitle("FWHM vs Energy; Energy; FWHM");
	fwhm->SetMarkerColor(kBlue);
	fwhm->SetLineColor(kBlue);
	fwhm->SetMarkerStyle(7);
	fwhm->SetMarkerSize(5);


  //TF1 *fitfano = new TF1("fitfano", "sqrt([0] + [1]*(x) + [2]*(x**2)) ", 0, 1600.);
  TF1 *fitfano = new TF1("fitfano", "sqrt([0] + [1]*(x)) ", 0, 1600.);
	fitfano->SetParName(0, "b^{2}");
  fitfano->SetParName(1, "a^{2}");
  //fitfano->SetParName(2, "c^{2}");
  fitfano->SetParameter(0,1);


  TLatex *latex0 = new TLatex(fwhm->GetX()[0], fwhm->GetY()[0],"Na22");
  TLatex *latex1 = new TLatex(fwhm->GetX()[1], fwhm->GetY()[1],"Na22");
  TLatex *latex2 = new TLatex(fwhm->GetX()[2], fwhm->GetY()[2],"K40");
  TLatex *latex3 = new TLatex(fwhm->GetX()[3], fwhm->GetY()[3],"Co60");
  TLatex *latex4 = new TLatex(fwhm->GetX()[4], fwhm->GetY()[4],"Co60");
  TLatex *latex5 = new TLatex(fwhm->GetX()[5], fwhm->GetY()[5],"Th228");
  TLatex *latex6 = new TLatex(fwhm->GetX()[6], fwhm->GetY()[6],"Th228");
  TLatex *latex7 = new TLatex(fwhm->GetX()[7], fwhm->GetY()[7],"Th228");
  fwhm->GetListOfFunctions()->Add(latex0);
  fwhm->GetListOfFunctions()->Add(latex1);
  fwhm->GetListOfFunctions()->Add(latex2);
  fwhm->GetListOfFunctions()->Add(latex3);
  fwhm->GetListOfFunctions()->Add(latex4);
  fwhm->GetListOfFunctions()->Add(latex5);
  fwhm->GetListOfFunctions()->Add(latex6);
  fwhm->GetListOfFunctions()->Add(latex7);

  /*TF1 *fitfano = new TF1("fitfano", "2.35*sqrt([0]*2.96*x) ", 0, 1600.);
	fitfano->SetParName(0, "F");
	fitfano->SetParameter(0,0.0002);*/


	gStyle->SetOptFit(1111);

	TCanvas *c1 = new TCanvas("FWHM_vs_Energy","FWHM_vs_Energy",800,600);
	fwhm->Draw("ape");
	//legend->Draw();
  fwhm->Fit("fitfano", "R");

  double asquare = fitfano->GetParameter(1);
  double asquare_err = fitfano->GetParError(1);

  double fanofactor = asquare / (2.35*2.35*2.96);
  double fanofactor_err = asquare_err / (2.35*2.35*2.96);

  std::cout << "Fano factor = \t" << fanofactor << "\t +- \t" << fanofactor_err << std::endl;

	c1->Print("FWHM_vs_Energy.png");

	Grafica->Run();
	return 0;
}
