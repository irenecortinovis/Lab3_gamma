/*
compile with:
c++ -o easyfit.o ../easyfit.cpp `root-config --cflags --glibs`
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


int main(int argc, char * argv[]){
  if(argc < 2) {
  	std::cout << "Inserisci il nome del file sorgente come argomento!" << std::endl;
        exit(1);
  }

  TApplication* Grafica = new TApplication("Grafica", 0, NULL);
  //gStyle -> SetOptFit (1111);
	int counts=0;
	TString data_file;

//------------------------------------------------------------------------------
// creazione e riempimento istogramma
  TCanvas* c2 = new TCanvas ("c2", "c2", 1200, 800);
	TH1F* histo_dat = new TH1F ("Spectrum","Spectrum",8192,1,8192);
	histo_dat -> SetFillColor (kYellow);
	histo_dat -> SetXTitle ("channel");
	histo_dat -> SetYTitle ("counts");
	histo_dat -> SetAxisRange (200,8192,"X");
	//histo_dat -> SetAxisRange (0,1000,"X");

  //data_file = "histo.dat";
  data_file = argv[1];
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
// 	fit e plot dell'istogramma

	//histo_dat -> Fit("fitfunc","R");
	histo_dat -> Draw();
	c2->Print("spectrum.png");

  Grafica->Run();

}
