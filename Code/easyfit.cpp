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
#include <iomanip>




int main(int argc, char *argv[]) {
	if(argc < 2) {
		std::cout << "Inserisci il nome del file sorgente come argomento!" << std::endl;
		exit(1);
	}

  TString opt[2]; //HARDCODED
  opt[0] = argv[2];
  opt[1] = argv[3];
  if(opt[0] == "r")
  	gROOT->SetBatch(kTRUE);


  TApplication* Grafica = new TApplication("Grafica", 0, NULL);
	gStyle -> SetOptFit (1111);
	TString data_file, back_file, results_file;



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

  int nPars = 7; //HARDCODED
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

  TH1F* histo_back = new TH1F ("Background","Background",8192,1,8192);
  histo_back -> SetFillColor (kYellow);
  histo_back -> SetXTitle ("channel");
  histo_back -> SetYTitle ("counts");
  histo_back -> SetAxisRange (200,8192,"X");

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

	histo_dat -> DrawCopy("HIST");
	//histo_dat -> Draw("HIST");
	c1->Print("spectrum.png");

  std::ofstream output (results_file.Data(), std::ios::app);
  if(opt[1] == "bias") {
	results_file = "../FWHM_vs_vbias.txt";
	output.open (results_file.Data(), std::ios::app);
  }

  if(opt[1] == "bias_nai") {
	results_file = "../../FWHM_vs_vbias.txt";
	output.open (results_file.Data(), std::ios::app);
  }

  if(opt[1] == "enc") {
	results_file = "../../ENC_vs_ST.txt";
	output.open (results_file.Data(), std::ios::app);
  }

  if(opt[1] == "att") {
    std::cout << "Input background file: " << std::endl;
    //std::cin >> back_file;
    back_file = "../../../../Background/Fondo_gain12-5/fondo_gain12-5.dat";

    int backcounts = 0;

    std::ifstream backinput (back_file.Data(), std::ios::in);
    for (int bin=1;bin<=8192;bin++)
    {
      backinput >> backcounts;
      histo_back -> Fill (bin,backcounts);
    }
    backinput.close ();

    results_file = "../Attenuation.txt";
  	output.open (results_file.Data(), std::ios::app);
  }

  if(opt[1] == "pet") {
	 results_file = "../Na22_correlation.txt";
	 output.open (results_file.Data(), std::ios::app);
  }

  if(opt[1] == "co60test" || opt[1] == "Co60test") {
   results_file = "../Co60_test.txt";
   output.open (results_file.Data(), std::ios::app);
  }

  if(opt[1] == "co60" || opt[1] == "Co60") {
   results_file = "../Co60_correlation.txt";
   output.open (results_file.Data(), std::ios::app);
  }

  if(opt[1] == "co60ratio" || opt[1] == "Co60ratio") {
   results_file = "../ratio.txt";
   output.open (results_file.Data(), std::ios::out);
  }

  if(opt[1] == "fanohpge" || opt[1] == "fanonai") {
  	results_file = "../FWHM_vs_Energy.txt";
	output.open (results_file.Data(), std::ios::app);
  }

  //----------- CONFIG FILE -----------------------------------
  //  for each peak: 7 parameters
  //  ngaus (1 o 2), minx, maxx, norm1, mean1, norm2, mean2
  //  one for each line, no spacing lines
  //  if only one gaus, will ignore the last two parameters
  //-----------------------------------------------------------

  for(int i=0; i<nPeaks; i++)
  {
    TH1F *histo_dat_copy = (TH1F*) histo_dat->Clone();
    peak* peakfit = new peak(configdata.at(nPars*i+1), configdata.at(nPars*i+2), histo_dat_copy);

    if (configdata.at(nPars*i) == 1)
    {
      peakfit->FitSingleGaus(configdata.at(nPars*i+3),configdata.at(nPars*i+4));
      std::ostringstream name;
      std::ostringstream name_signal;
      name << "peak" << i;
      name_signal << "signal" << i;
      peakfit->DrawPeak(name.str());
      peakfit->GetFitVariablesSingleGaus();
      peakfit->GetSignal(name_signal.str(), 1);
      peakfit->DrawSignal(name_signal.str());
    }
    else if (configdata.at(nPars*i) == 2)
    {
      peakfit->FitDoubleGaus(configdata.at(nPars*i+3),configdata.at(nPars*i+4),configdata.at(nPars*i+5),configdata.at(nPars*i+6));
      std::ostringstream name;
      std::ostringstream name_signal;
      name << "peak" << i;
      name_signal << "signal" << i;
      peakfit->DrawPeak(name.str());
      peakfit->GetFitVariablesDoubleGaus();
      peakfit->FitDiffFunc();
      peakfit->Getmeantot();
      peakfit->GetFWHMtot();
      peakfit->GetSignal(name_signal.str(), 2);
      peakfit->DrawSignal(name_signal.str());
    }
    else if (configdata.at(nPars*i) == 3)
    {
      peakfit->FitStepGaus(configdata.at(nPars*i+3),configdata.at(nPars*i+4));
      std::ostringstream name;
      std::ostringstream name_signal;
      name << "peak" << i;
      name_signal << "signal" << i;
      peakfit->DrawPeak(name.str());
      peakfit->GetFitVariablesStepGaus();
      peakfit->GetSignal(name_signal.str(), 3);
      peakfit->DrawSignal(name_signal.str());
    }
    else if (configdata.at(nPars*i) == 4)
    {
      peakfit->FitErfGaus(configdata.at(nPars*i+3),configdata.at(nPars*i+4));
      std::ostringstream name;
      std::ostringstream name_signal;
      name << "peak" << i;
      name_signal << "signal" << i;
      peakfit->GetFitVariablesErfGaus();
      peakfit->DrawPeak(name.str());
      peakfit->GetSignal(name_signal.str(), 4);
      peakfit->DrawSignal(name_signal.str());
    }
    else
      std::cout << "ERROR number of gaussians" << std::endl;

    if(opt[1] == "bias") {
	     output << std::fixed << std::setprecision(2) << peakfit->FWHM_tot << "\t\t";
       output << std::fixed << std::setprecision(2) << peakfit->err_FWHM_tot << "\t";

    }
    if(opt[1] == "bias_nai") {
	     output << peakfit->FWHM1 << "\t";
	     output << peakfit->err_FWHM1 << "\t";
    }
    if(opt[1] == "enc") {
	     output << peakfit->FWHM1 << "\t";
    }
    if(opt[1] == "att") {
      double data_counts = peakfit->GetIntegral(configdata.at(nPars*i+1),configdata.at(nPars*i+2));
      double back_counts = histo_back->Integral(configdata.at(nPars*i+1),configdata.at(nPars*i+2));
      //std::cout << "Signal + background counts:\t" << data_counts << std::endl;
      //std::cout << "Background counts:\t" << back_counts << std::endl;
      double integral = data_counts - back_counts;
      std::cout << "Integral signal:\t" << integral << std::endl;

      output << "\t" << integral << "\n";
    }
    if(opt[1] == "pet") {
    	//double integral = peakfit->GetIntegral(peakfit->mean1 - (2./2.35)*FWHM1, peakfit->mean1 + (2./2.35)*FWHM1);		//Integro entro 2 sigma
    	double integral = peakfit->GetIntegral(5100, 5200);				//Integro tra 5100 e 5200 per tutti gli istogrammi (HARDCODED?)
    	std::cout << "Integral signal + background:\t" << integral << std::endl;
    	output << "\t" << integral << "\n";
    }
    if(opt[1] == "co60test" || opt[1] == "Co60test") {
      double integral = peakfit->GetIntegral(6714, 6743);
      std::cout << "Integral signal + background:\t" << integral << std::endl;
      output << integral << "\n";
    }
    if(opt[1] == "co60" || opt[1] == "Co60") {
      std::cout << "minx = " << peakfit->minx << std::endl;
      std::cout << "maxx = " << peakfit->maxx << std::endl;
      double signal = peakfit->GetSignalIntegral(peakfit->minx, peakfit->maxx);
      std::cout << "Integral signal = \t" << signal << std::endl;
      output << "\t" << signal;
      if(i == 1)
      	output << "\n";
    }
/*    if(opt[1] == "co60ratio" || opt[1] == "Co60ratio") {
      double integral2 = peakfit->GetIntegral(6710, 6737);
      double integral1 = peakfit->GetIntegral(5900, 5924);
      double ratio = integral2/integral1;
      double err_ratio = ratio*sqrt(1./integral1 + 1./integral2);	//errore del rapporto
      std::cout << "Ratio gamma2/gamma1:\t" << ratio << std::endl;
      std::cout << "ErrRatio gamma2/gamma1:\t" << err_ratio << std::endl;
      if(i == 0)
        output << ratio << "\n" << err_ratio << "\n";
    }*/
    double ratio;
    double err_ratio;
    if(opt[1] == "co60ratio" || opt[1] == "Co60ratio") {
      double integral = peakfit->GetSignalIntegral(peakfit->minx, peakfit->maxx);
      if(i == 0) {          //N.B.: si suppone che il primo picco in config.txt sia il primo picco del cobalto
        ratio = 1./integral;
        err_ratio = 1./integral;
      }
      if(i == 1) {
        ratio *= integral;
        err_ratio = ratio*sqrt(err_ratio + 1./integral);
        std::cout << "Ratio gamma2/gamma1:\t" << ratio << std::endl;
        std::cout << "ErrRatio gamma2/gamma1:\t" << err_ratio << std::endl;
        output << ratio << "\n" << err_ratio << "\n";
      }
    }
    if(opt[1] == "fanohpge") {
      output << peakfit->mean_tot / 5.09 << "\t" << peakfit->FWHM_tot / 5.09 << "\t"
      << peakfit->err_mean_tot / 5.09 << "\t" << peakfit->err_FWHM_tot / 5.09;
  		output << "\n";
    }
    if(opt[1] == "fanonai") {
      output << peakfit->mean_tot / 4.04 << "\t" << peakfit->FWHM_tot / 4.04 << "\t"
      << peakfit->err_mean_tot / 4.04 << "\t" << peakfit->err_FWHM_tot / 4.04;
  		output << "\n";
    }

    delete peakfit;
  }

  if(opt[1] == "bias" || opt[1] == "bias_nai" || opt[1] == "enc" || opt[1] == "att" || opt[1] == "pet" || opt[1] == "co60test" || opt[1] == "Co60test" || opt[1] == "co60" || opt[1] == "Co60" || opt[1] == "co60ratio" || opt[1] == "Co60ratio" || opt[1] == "fanohpge" || opt[1] == "fanonai") {
  //if(opt[1] != "") {
	output.close();
  }
  else {
	Grafica->Run();
  }

  return 0;
}
