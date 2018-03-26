/* compile with: c++ -o easyfit_peak1.o ../easyfit_peak1.cpp `root-config --cflags --glibs` */

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <TH1F.h>
#include <TCanvas.h>
#include <TF1.h>
#include <TMath.h>
#include <TStyle.h>
#include <TApplication.h>
#include <TROOT.h>

int main(int argc, char *argv[]) {
	if(argc < 2) {
		std::cout << "Inserisci il nome del file sorgente come argomento!" << std::endl;
		exit(1);
	}

  TString opt = argv[2];
  if(opt == "r")
  	gROOT->SetBatch(kTRUE);


  TApplication* Grafica = new TApplication("Grafica", 0, NULL);
	gStyle -> SetOptFit (1111);
	int counts=0;
	TString data_file, result_file;


  //------------------------------------------------------------------------------
  //creazione e riempimento istogramma
  TCanvas* c2 = new TCanvas ("c2", "c2", 1200, 800);
	TH1F* histo_dat = new TH1F ("Peak 1","Peak 1",8192,1,8192);
	histo_dat -> SetFillColor (kYellow);
	histo_dat -> SetXTitle ("channel");
	histo_dat -> SetYTitle ("counts");
	histo_dat -> SetAxisRange (200,8192,"X");
	//histo_dat -> SetAxisRange (0,1000,"X");

  //data_file = "histo.dat";
  data_file = argv[1];
  result_file = "results.txt";
  //std::cout << "inserisci il nome del file da analizzare (default -> histo.dat):   " << std::endl;
  //std::cin >> data_file;
  /*if (data_file->Data() == "");
	{
		data_file = "histo.dat";
	}*/


	int sumtot = 0;
	std::ifstream input (data_file.Data(), std::ios::in);
	for (int bin=1;bin<=8192;bin++)
	{
		input >> counts;
        	histo_dat -> Fill (bin,counts);
		sumtot += counts;
	}

	input.close ();
	std::cout << "Total number of events: " << sumtot << std::endl;

  //------------------------------------------------------------------------------
  // funzione per il fit del picco di segnale

  int minx = 2490;
  int maxx = 2560;

  //double gaussian
	TF1* fitfunc = new TF1 ("fitfunc","gaus(0) + gaus(3) + pol1(6)",minx,maxx); //3373,3403 2977,3007
	fitfunc -> SetNpx (100000);
	fitfunc -> SetLineWidth (2);
	fitfunc -> SetLineColor (kBlue);
	fitfunc -> SetParameters (6000,2521,5,1500,2525,10,50,0);

  //single gaussian
  /*TF1* fitfunc = new TF1 ("fitfunc","gaus(0)",minx,maxx);
	fitfunc -> SetNpx (100000);
	fitfunc -> SetLineWidth (2);
	fitfunc -> SetLineColor (kBlue);
	fitfunc -> SetParameters (6000,2521,5);*/


  //------------------------------------------------------------------------------
  // 	fit e plot dell'istogramma

	histo_dat -> Fit("fitfunc","R");
	histo_dat -> Draw();
  histo_dat->GetXaxis()->SetRange(minx,maxx);
	c2->Print("peak1.png");

  //if double gaussian
  double mean1 = fitfunc -> GetParameter (1);
  double mean2 = fitfunc -> GetParameter (4);
  double err_mean1 = fitfunc -> GetParError (1);
  double err_mean2 = fitfunc -> GetParError (4);
  double FWHM1 = fitfunc -> GetParameter (2)*2.35;
  double FWHM2 = fitfunc -> GetParameter (5)*2.35;
  double err_FWHM1 = fitfunc -> GetParError (2)*2.35;
  double err_FWHM2 = fitfunc -> GetParError (5)*2.35;


  double maximum = fitfunc->GetMaximum(minx,maxx);
  //std::cout << "maximum value \t" << maximum << std::endl;
  double maximumx = fitfunc->GetMaximumX(minx,maxx);
  std::cout << "x of maximum value \t" << maximumx << std::endl;

  TF1* diffunc = new TF1 ("diffunc","abs(-[9] + fitfunc)",minx,maxx);
  diffunc -> SetNpx (100000);
  diffunc -> FixParameter(9,maximum*0.5);
  std::cout << "mean1\t" << mean1 << "\t +- \t" << err_mean1 << std::endl;
  double minimumX1 = diffunc->GetMinimumX(minx,mean1);
  double minimumX2 = diffunc->GetMinimumX(mean1,maxx);
  std::cout << "min sx \t " << minimumX1 << std::endl;
  std::cout << "min dx \t " << minimumX2 << std::endl;

  double FWHM_tot = fabs(minimumX2-minimumX1);
  std::cout << "FWHM double gaussian:\t" << FWHM_tot << std::endl;

  std::ofstream output (result_file.Data(), std::ios::app);	//apro il file in modalità append per non sovrascriverne il contenuto
  output << maximumx;
  output.close();

  //if single gaussian
  /*double mean1 = fitfunc -> GetParameter (1);
  double err_mean1 = fitfunc -> GetParError (1);
  double FWHM1 = fitfunc -> GetParameter (2)*2.35;
  double err_FWHM1 = fitfunc -> GetParError (2)*2.35;

  std::cout << "mean value:\t" << mean1 << "\t +- \t" << err_mean1 << std::endl;
  std::cout << "FWHM single gaussian:\t" << FWHM1 << "\t +- \t" << err_mean1 << std::endl;

  std::ofstream output (result_file.Data(), std::ios::app);	//apro il file in modalità append per non sovrascriverne il contenuto
  output << mean1;
  output.close();*/






  if(opt != "r")		//opzione per evitare il Run() dell'applicazione
  	Grafica->Run();

  return 0;
}
