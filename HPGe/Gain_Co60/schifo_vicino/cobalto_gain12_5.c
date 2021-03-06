void cobalto_gain12_5()
{
	gROOT->Reset();
	gStyle -> SetOptFit (1111);
	int counts=0;
	nbins=8192;
	TString data_file;

//------------------------------------------------------------------------------
// creazione e riempimento istogramma
   	TCanvas* c2 = new TCanvas ("c2", "c2", 1200, 800);
	//TH1F* histo_dat = new TH1F ("Calibrazione","Calibrazione",8192,1,8192);
	TH1F* histo_dat = new TH1F ("Calibrazione","Calibrazione",nbins,1,nbins);
	histo_dat -> SetFillColor (kYellow);  
	histo_dat -> SetXTitle ("channel");
	histo_dat -> SetYTitle ("counts");    
	histo_dat -> SetAxisRange (200,8192,"X");
	//histo_dat -> SetAxisRange (0,1000,"X");
  
	std::cout << "inserisci il nome del file da analizzare (default -> histo.dat):   " << std::endl;
	data_file = "cobalto_gain12_5.dat";
	//std::cin >> data_file;

/*	if (data_file->Data() == "");
	{
		data_file = "histo.dat";
	}
  */
	int sumtot = 0;
	std::ifstream input (data_file.Data(), std::ios::in);
	for (int bin=1;bin<=nbins;bin++)
	{
		input >> counts;
        	histo_dat -> Fill (bin,counts);
		sumtot += counts;
	}
   
	input.close ();
	std::cout << "Total number of events: " << sumtot << std::endl;
   
//------------------------------------------------------------------------------
// funzione per il fit del picco di segnale

	TF1* fitfunc = new TF1 ("fitfunc","gaus+[3]",3295,3320); //3373,3403 2977,3007
	fitfunc -> SetNpx (100000);
	fitfunc -> SetLineWidth (2);
	fitfunc -> SetLineColor (kBlue);
	fitfunc -> SetParameter (0, 20000);
	fitfunc -> SetParameter (1, 3304.);
	fitfunc -> SetParameter (2, 10.);
	fitfunc -> SetParameter (3, 1000.);

	
//------------------------------------------------------------------------------
// 	fit e plot dell'istogramma
	
	//histo_dat -> Fit("fitfunc","R");
	histo_dat -> Draw();
	c2->Print("cobalto_gain12_5.svg");	

	double amplitude = fitfunc -> GetParameter (0)*fitfunc -> GetParameter (2)*TMath::Sqrt(2*TMath::Pi());
	double err_amplitude = amplitude*TMath::Sqrt((fitfunc -> GetParError (0)/fitfunc -> GetParameter (0))**2 + (fitfunc -> GetParError (2)/fitfunc -> GetParameter (2))**2);
	double mean = fitfunc -> GetParameter (1);
	double err_mean = fitfunc -> GetParError (1);
	double FWHM = fitfunc -> GetParameter (2)*2.35;
	double err_FWHM = fitfunc -> GetParError (2)*2.35;
	
	std::cout << "\n\n************************************************" << std::endl;
	std::cout << "**	parametri fit			      **" << std::endl;
	std::cout << "\nArea:   " << amplitude << " +/- " << err_amplitude << std::endl;
	std::cout << "media:   " << mean << " +/- " << err_mean << std::endl;
	std::cout << "FWHM:   " << FWHM << " +/- " << err_FWHM << std::endl;
	std::cout << "************************************************" << std::endl;


	
}
