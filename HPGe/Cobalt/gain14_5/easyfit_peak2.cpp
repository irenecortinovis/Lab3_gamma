/*
compile with:
c++ -o easyfit_peak2.o ../easyfit_peak2.cpp `root-config --cflags --glibs`
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <TH1F.h>
#include <TCanvas.h>
#include <TF1.h>
#include <TMath.h>
#include <TStyle.h>
#include <TApplication.h>
#include <TPad.h>


int main(int argc, char * argv[]){
  if(argc < 2) {
         std::cout << "Inserisci il nome del file sorgente come argomento!" << std::endl;
         exit(1);
  }

  TApplication* Grafica = new TApplication("Grafica", 0, NULL);

  gStyle -> SetOptFit (1111);
	int counts=0;
	TString data_file, result_file;

//------------------------------------------------------------------------------
// creazione e riempimento istogramma
  TCanvas* c2 = new TCanvas ("c2", "c2", 1200, 800);
	TH1F* histo_dat = new TH1F ("Peak 2","Peak 2",8192,1,8192);
	histo_dat -> SetFillColor (kYellow);
	histo_dat -> SetXTitle ("channel");
	histo_dat -> SetYTitle ("counts");
	histo_dat -> SetAxisRange (200,8192,"X");
	//histo_dat -> SetAxisRange (0,1000,"X");

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


  int minx = 6695;
  int maxx = 6725;
	TF1* fitfunc = new TF1 ("fitfunc","gaus(0) + gaus(3)",minx,maxx);
	fitfunc -> SetNpx (100000);
	fitfunc -> SetLineWidth (2);
	fitfunc -> SetLineColor (kBlue);
	fitfunc -> SetParameters (6000,6706,5,1500,6709,10);

	/*TF1* fitfuncgaus1 = new TF1 ("fitfunc","gaus",6695,6725); //3373,3403 2977,3007
	fitfuncgaus1 -> SetNpx (100000);
	fitfuncgaus1 -> SetLineWidth (2);
	fitfuncgaus1 -> SetLineColor (kBlue);
	fitfuncgaus1 -> SetParameters (6000,6706,5);*/


//------------------------------------------------------------------------------
// 	fit e plot dell'istogramma con due gaussiane

	histo_dat -> Fit("fitfunc","R");
	histo_dat -> Draw();
  histo_dat->GetXaxis()->SetRange(6660,6760);
	c2->Print("peak2.png");

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
  TF1* diffunc = new TF1 ("diffunc","abs(fitfunc - [0])",minx,maxx);
  diffunc -> SetNpx (100000);
  diffunc -> FixParameter(0, maximum*0.5);
  double minimumX1 = diffunc->GetMinimumX(minx,mean2);
  double minimumX2 = diffunc->GetMinimumX(mean2,maxx);
  //std::cout << "min sx \t " << minimumX1 << std::endl;
  //std::cout << "min dx \t " << minimumX2 << std::endl;

  double FWHM_tot = fabs(minimumX2-minimumX1);
  std::cout << "FWHM double gaussian:\t" << FWHM_tot << std::endl;
  std::ofstream output (result_file.Data(), std::ios::app);     //apro il file in modalità append per non sovrascriverne il contenuto
  output << FWHM_tot;
  output.close();

  TString opt = argv[2];
  if(opt != "r")		//opzione per evitare il Run() dell'applicazione
        Grafica->Run();

  return 0;
}
