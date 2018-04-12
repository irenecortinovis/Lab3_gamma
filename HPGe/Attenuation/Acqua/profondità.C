void profondità(TString filename, float xmin, float xmax) {
	TH1F *histo = new TH1F("histo", "histo", 1000, xmin, xmax);


	int sumtot = 0;
	double x;
        std::ifstream input (filename.Data(), std::ios::in);
	while(input >> x)
      	{
                histo -> Fill(x);
                sumtot++;
        }
        input.close ();
	histo->Draw();
	c1->Print("media_profondità.png");

        std::cout << "Number of measures: " << sumtot << std::endl;
        std::cout << "Mean: " << histo->GetMean() << std::endl;
        std::cout << "RMS: " << histo->GetRMS() << std::endl;
}
