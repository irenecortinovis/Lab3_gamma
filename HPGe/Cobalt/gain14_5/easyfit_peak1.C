void easyfit_peak1()
{
	gROOT->Reset();
	gStyle -> SetOptFit (1111);
	int counts=0;
	TString data_file;

//------------------------------------------------------------------------------
//creazione e riempimento istogramma
  TCanvas* c2 = new TCanvas ("c2", "c2", 1200, 800);
	TH1F* histo_dat = new TH1F ("Peak 1","Peak 1",8192,1,8192);
	histo_dat -> SetFillColor (kYellow);
	histo_dat -> SetXTitle ("channel");
	histo_dat -> SetYTitle ("counts");
	histo_dat -> SetAxisRange (200,8192,"X");
	//histo_dat -> SetAxisRange (0,1000,"X");

  data_file = "histo.dat";
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

	TF1* fitfunc = new TF1 ("fitfunc","gaus(0) + gaus(3) + pol1(6)",5885,5950); //3373,3403 2977,3007
	fitfunc -> SetNpx (100000);
	fitfunc -> SetLineWidth (2);
	fitfunc -> SetLineColor (kBlue);
	fitfunc -> SetParameters (6000,5897,5,1500,5902,10,50,0);


	/*TF1* fitfunc = new TF1 ("fitfunc","crystalball",3718,3760); //3373,3403 2977,3007
	fitfunc -> SetNpx (100000);
	fitfunc -> SetLineWidth (2);
	fitfunc -> SetLineColor (kBlue);*/



//------------------------------------------------------------------------------
// 	fit e plot dell'istogramma

	histo_dat -> Fit("fitfunc","R");
	histo_dat -> Draw();
	c2->Print("peak1.png");

  double amplitude = fitfunc -> GetParameter (0)*fitfunc -> GetParameter (2)*TMath::Sqrt(2*TMath::Pi());
	double err_amplitude = amplitude*TMath::Sqrt((fitfunc -> GetParError (0)/fitfunc -> GetParameter (0))**2 + (fitfunc -> GetParError (2)/fitfunc -> GetParameter (2))**2);
  double mean1 = fitfunc -> GetParameter (1);
  double mean2 = fitfunc -> GetParameter (4);
  double err_mean1 = fitfunc -> GetParError (1);
  double err_mean2 = fitfunc -> GetParError (4);
  double FWHM1 = fitfunc -> GetParameter (2)*2.35;
  double FWHM2 = fitfunc -> GetParameter (5)*2.35;
  double err_FWHM1 = fitfunc -> GetParError (2)*2.35;
  double err_FWHM2 = fitfunc -> GetParError (5)*2.35;


  TF1* signalfunc = new TF1 ("signalfunc","(fitfunc - pol1)",5885,5950);
  signalfunc -> SetNpx (100000);
  signalfunc -> FixParameter(0, fitfunc -> GetParameter(6));
  signalfunc -> FixParameter(1, fitfunc -> GetParameter(7));
  double maximum = signalfunc->GetMaximum(5885,5950);
  std::cout << "maximum value \t" << maximum << std::endl;


  TF1* diffunc = new TF1 ("diffunc","abs(-[9] +signalfunc)",5885,5950);
  diffunc -> SetNpx (100000);
  diffunc -> FixParameter(9,maximum*0.5);
  std::cout << "mean1\t" << mean1 << std::endl;
  double minimumX1 = diffunc->GetMinimumX(5885,mean1);
  double minimumX2 = diffunc->GetMinimumX(mean1,5950);
  std::cout << "min sx \t " << minimumX1 << std::endl;
  std::cout << "min dx \t " << minimumX2 << std::endl;

  TCanvas* c3 = new TCanvas ("c3", "c3", 1200, 800);
  c3->Divide(1,2);
  c3->cd(1);
  signalfunc -> Draw();
  c3->cd(2);
  diffunc -> Draw();



  double FWHM_tot = fabs(minimumX2-minimumX1);
  std::cout << "FWHM double gaussian:\t" << FWHM_tot << std::endl;
}
