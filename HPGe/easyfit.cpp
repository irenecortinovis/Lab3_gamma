/*
compile with:
g++ easyfit.cpp  -o easyfit.o `root-config --cflags --glibs`

*/

#include "peak.cc"
#include <fstream>
#include <TApplication.h>
#include <TStyle.h>
#include <TROOT.h>
#include <string>
#include <sstream>
#include <vector>



int main(int argc, char *argv[]) {
	if(argc < 2) {
		std::cout << "Inserisci il nome del file sorgente come argomento!" << std::endl;
		exit(1);
	}

  TString opt[2];
  opt[0] = argv[2];
  opt[1] = argv[3];
  if(opt[0] == "r")
  	gROOT->SetBatch(kTRUE);


  TApplication* Grafica = new TApplication("Grafica", 0, NULL);
	gStyle -> SetOptFit (1111);
	TString data_file, results_file;



  //----------------------------------------------------------//
  //  Parse the config file                                   //
  //----------------------------------------------------------//

  int number_of_lines = 0;
  std::ifstream myfile("config.txt");

  std::vector<double> configdata;
  double line;
  while (myfile >> line)
  {
    ++number_of_lines;
    configdata.push_back(line);
  }
  std::cout << "Number of lines in text file: " << number_of_lines;

  //int nPars = 6; //HARDCODED
  int nPars = 4; //HARDCODED
  int nPeaks = number_of_lines/nPars;


  //------------------------------------------------------------------------------
  // creazione e riempimento istogramma spectrum
  //------------------------------------------------------------------------------

  TCanvas* c1 = new TCanvas ("c1", "c1", 1200, 800);

  TH1F* histo_dat = new TH1F ("Spectrum","Spectrum",8192,1,8192);
	histo_dat -> SetFillColor (kYellow);
	histo_dat -> SetXTitle ("channel");
	histo_dat -> SetYTitle ("counts");
	histo_dat -> SetAxisRange (200,8192,"X");

  data_file = argv[1];

  int counts = 0;
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

	histo_dat -> Draw();
	c1->Print("spectrum.png");

  std::ofstream output (results_file.Data(), std::ios::app);
  if(opt[1] == "bias") {
	results_file = "bias_choice.txt";
	output.open (results_file.Data(), std::ios::app);
  }

  //----------- CONFIG FILE ------------------------
  //  for each peak: 6 parameters
  //  minx, maxx, norm1, mean1, norm2, mean2
  //  one for each line, no spacing lines
  //------------------------------------------------

  for(int i=0; i<nPeaks; i++)
  {
    /*
    TH1F *histo_dat_copy = (TH1F*) histo_dat->Clone();
    peak* peakfit = new peak(configdata.at(nPars*i), configdata.at(nPars*i+1), histo_dat_copy);
    peakfit->FitDoubleGaus(configdata.at(nPars*i+2),configdata.at(nPars*i+3),configdata.at(nPars*i+4),configdata.at(nPars*i+5));
    std::ostringstream name;
    name << "peak" << i;
    peakfit->DrawPeak(name.str());
    peakfit->GetFitVariables();
    peakfit->FitDiffFunc();
    peakfit->GetFWHMtot();*/

    TH1F *histo_dat_copy = (TH1F*) histo_dat->Clone();
    peak* peakfit = new peak(configdata.at(nPars*i), configdata.at(nPars*i+1), histo_dat_copy);
    peakfit->FitSingleGaus(configdata.at(nPars*i+2),configdata.at(nPars*i+3));
    std::ostringstream name;
    name << "peak" << i;
    peakfit->DrawPeak(name.str());
    peakfit->GetFitVariablesSingleGaus();

    if(opt[1] == "bias") {
	     output << peakfit->FWHM_tot << "\t";
    }

    delete peakfit;
  }

  if(opt[1] == "bias") {
	output << std::endl;
	output.close();
  }


  Grafica->Run();
  return 0;
}