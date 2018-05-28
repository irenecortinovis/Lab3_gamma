#include <iostream>
#include <fstream>
#include <iomanip>
#include <TH1F.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TApplication.h>
#include <TGraphErrors.h>
#include <TStyle.h>
#include <TLegend.h>

//c++ calibration.cpp `root-config --cflags --glibs` -o calibration.o



int main(){

	TApplication* Grafica = new TApplication("Grafica", 0, NULL);
	gStyle->SetOptFit(111);
  gStyle->SetStatY(.45);

	//create vectors for tgrapherrors
	int n=7;
	double picco[n];
	double picco_err[n];
	double picco_teorico[n];
	double picco_teorico_err[n];

	//fill in vectors
	double a, b, c, d;
	std::ifstream inFile;
	inFile.open("./calibration.txt", std::ios::in);

	int i = 0;
	while(!inFile.eof())
	{
	    inFile >> a >> b >> c >> d;
	    picco[i] = a;
	    picco_err[i] = b;
	    picco_teorico[i] = c;
	    picco_teorico_err[i] = d;
	    i++;
	}

	inFile.close();

	//plot and fit
	TCanvas* c1 = new TCanvas("c1","Calibration");
	TGraphErrors* gr = new TGraphErrors(n,picco_teorico,picco,picco_teorico_err,picco_err);
	gr->SetTitle("Calibration");
	gr->GetXaxis()->SetTitle("Teoric_peak [keV]");
	gr->GetYaxis()->SetTitle("Measured_peak");


	TF1 *fitC1 = new TF1("fitC1","[0]*x+[1]",picco_teorico[0],picco_teorico[n-1]);
	fitC1->SetParameter(5, -70);
  fitC1->SetParName(0, "a");
  fitC1->SetParName(1, "b");
	gr->Fit("fitC1");

	double a_fit = fitC1->GetParameter(0);
	double a_fit_err = fitC1->GetParError(0);
  double b_fit = fitC1->GetParameter(1);
	double b_fit_err = fitC1->GetParError(1);

	gr->Draw("A*");
	c1->Print("Calibration.png", "png");

	TLegend* legend1 = new TLegend(0.1,0.75,0.5,0.9);
	legend1->AddEntry(fitC1,"I = ax + b","l");
	legend1->AddEntry(gr,"data","p");
	legend1->Draw();


	std::cout << std::fixed;
  std::cout << "fit: ax+b" << std::endl;
  std::cout << "a = " << std::setprecision(2) << a_fit << " +/- " << std::setprecision(2) << a_fit_err << std::endl;
  std::cout << "b = " << std::setprecision(2) << b_fit << " +/- " << std::setprecision(2) << b_fit_err << std::endl;



	Grafica->Run("");

	return 0;
}
