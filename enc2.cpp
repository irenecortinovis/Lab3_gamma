void enc2(){

  TGraphErrors *encV0_05 = new TGraphErrors();
  encV0_05->SetTitle("ENC^2 vs ST at V = 0.050; #tau (shaping time); ENC^2");
  encV0_05->SetMarkerColor(kBlue);
  encV0_05->SetMarkerStyle(7);
  TGraphErrors *encV0_075 = new TGraphErrors();
  encV0_075->SetTitle("ENC^2 vs ST at V = 0.075; #tau (shaping time); ENC^2");
  encV0_075->SetMarkerColor(kBlue);
  encV0_075->SetMarkerStyle(7);
  TGraphErrors *encV0_1 = new TGraphErrors();
  encV0_1->SetTitle("ENC^2 vs ST at V = 0.100; #tau (shaping time); ENC^2");
  encV0_1->SetMarkerColor(kBlue);
  encV0_1->SetMarkerStyle(7);

  std::ifstream FWHMfile("fwhm.txt");

  double fwhm, fwhm_err;
  double ST = 0.5;
  int i = 0;

  // numero delle fwhm = 9  HARDCODED!!
  // tutti gli if sotto si basano su questo

  while (FWHMfile >> fwhm >> fwhm_err) {

      if (i == 0 || i == 1 || i == 2) {
        if (i == 1) {
          ST = 1.5;
        }
        if (i == 2) {
          ST = 3.0;
        }

        encV0_1->SetPoint(i,ST,pow(fwhm/2.35,2));
        encV0_1->SetPointError(i,0.1,fwhm_err/2.35);
      }

      if (i == 3 || i == 4 || i == 5) {
        if (i == 3) {
          ST = 0.5;
        }
        if (i == 4) {
          ST = 1.5;
        }
        if (i == 5) {
          ST = 3.0;
        }

        encV0_075->SetPoint(i-3,ST,pow(fwhm/2.35,2));
        encV0_075->SetPointError(i-3,0.1,fwhm_err/2.35);
        // il -3 è messo perchè a root non piace partire con il primo punto del grafico con indice maggiore di zero,
        // senza il -3 a volte il bugga a caso e mette dei valori a caso ai punti del grafico.
      }

      if (i == 6 || i == 7 || i == 8) {
        if (i == 6) {
          ST = 0.5;
        }
        if (i == 7) {
          ST = 1.5;
        }
        if (i == 8) {
          ST = 3.0;
        }

        encV0_05->SetPoint(i-6,ST,pow(fwhm/2.35,2));
        encV0_05->SetPointError(i-6,0.1,fwhm_err/2.35);
        // il -6 è messo perchè a root non piace partire con il primo punto del grafico con indice maggiore di zero,
        // senza il -6 a volte il bugga a caso e mette dei valori a caso ai punti del grafico.
      }

      ++i;
  }

  gStyle->SetOptFit(1111);

  TF1 *enc_fit = new TF1("enc^2 fit","[0]/x+[1]*x");
  enc_fit->SetLineColor(kRed);
  enc_fit->SetParNames("aC^{2}","bI_{fuga}");

  TCanvas *c1 = new TCanvas("enc2_V0_01","enc2_V0_01",400,400);
  encV0_1->Fit(enc_fit);
  encV0_1->Draw("ape");
  enc_fit->Draw("same");
  c1->Print("enc2_V0_01.png");

  TCanvas *c2 = new TCanvas("enc2_V0_075","enc2_V0_075",400,400);
  encV0_075->Fit(enc_fit);
  encV0_075->Draw("ape");
  enc_fit->Draw("same");
  c2->Print("enc2_V0_075.png");

  TCanvas *c3 = new TCanvas("enc2_V0_05","enc2_V0_05",400,400);
  encV0_05->Fit(enc_fit);
  encV0_05->Draw("ape");
  enc_fit->Draw("same");
  c3->Print("enc2_V0_05.png");

}
