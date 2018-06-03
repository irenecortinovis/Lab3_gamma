/*
compile with:
g++ correlation.cpp -o correlation.o `root-config --cflags --glibs`
*/

//This program fits the angular correlation graph of gamma-gamma emission from Co60

#include <fstream>
#include <TMultiGraph.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TCanvas.h>
#include <TApplication.h>
#include <TStyle.h>
#include <TROOT.h>
#include <string>
#include <TLegend.h>
#include <cmath>

int main(int argc, char **argv) {
	if(argc < 2) {
		std::cout << "Errore: inserire file sorgente come argomento." << std::endl;
		return 1;
	}

	const int n = 20;
	double theta[n], count1[n], count2[n], count2_corr[n], err_corr[n], count2_acc[n], err_acc[n];
	double ratio, err_ratio;
	std::ifstream ratiofile("ratio.txt");
	ratiofile >> ratio >> err_ratio;
	ratiofile.close();

	std::ifstream infile(argv[1]);
	int j = 0;
	char buffer[20];
	infile >> buffer >> buffer >> buffer;
	while(infile.good()) {
		infile >> theta[j] >> count1[j] >> count2[j];
		count2_acc[j] = ratio*count1[j];
		count2_corr[j] = count2[j] - count2_acc[j];		//Sottraggo dai conteggi del picco 2 le false coincidenze
		err_acc[j] = count2_acc[j]*sqrt(pow(err_ratio/ratio, 2) + 1./count1[j]);
		err_corr[j] = sqrt(count2[j] + pow(err_acc[j], 2));
		j++;
	}
	infile.close();
	int npoints = j;

	TApplication* Grafica = new TApplication("Grafica", 0, NULL);
	TGraphErrors *angles = new TGraphErrors(npoints-1, theta, count2_corr);
	double *y = angles->GetY();
	for(int i = 0; i < angles->GetN(); i++) {
		angles->SetPointError(i, 1, err_corr[i]);			//(i, ex, ey)
	}

	//TF1 *cos2 = new TF1("cos2", "[0]*([1]*(cos(x/180*pi))**2 + [2]*(cos(x/180*pi))**4) + [3]", 180., 270.);
	TF1 *cos2 = new TF1("cos2", "[0]*([1]*(cos(pi*x/180))**2 + [2]*(cos(pi*x/180))**4 + 1)", 180., 270.);
	cos2->SetParName(0, "N_{0}");
	cos2->SetParName(1, "a_{1}");
	cos2->SetParName(2, "a_{2}");

	//cos2->SetParName(3, "offset");
	cos2->SetParameters(20, 0.125, 0.04);
	//cos2->FixParameter(0, 1794);
	//cos2->FixParameter(1, 0.125);
	//cos2->FixParameter(2, 0.042);
	//cos2->SetParLimits(1, 0.118, 0.132);
	//cos2->SetParLimits(2, 0.038, 0.044);
	angles->SetTitle("Angular correlation #gamma-#gamma ^{60}Co; #theta (#circ); N_{counts}");
	angles->SetMarkerColor(kBlue);
	angles->SetLineColor(kBlue);
	angles->SetMarkerStyle(7);
	angles->SetMarkerSize(5);

	gStyle->SetOptFit(1111);

	TCanvas *c1 = new TCanvas("counts_vs_theta","counts_vs_theta",800,600);
	angles->Draw("ape");
	angles->Fit("cos2", "R");
	TF1 *cos2_exp = new TF1("cos2", "[0]*([1]*(cos(pi*x/180))**2 + [2]*(cos(pi*x/180))**4 + 1)", 180., 270.);
	cos2_exp->SetParameter(0, (angles->GetFunction("cos2"))->GetParameter(0));
	cos2_exp->SetParameter(1, 0.125);
	cos2_exp->SetParameter(2, 0.042);
	cos2_exp->SetLineStyle(7);
	cos2_exp->SetLineColor(kGray);
	cos2_exp->Draw("same");
	TLegend *legend = new TLegend(0.15, 0.15, 0.3, 0.3);
	legend->AddEntry(cos2, "Fit", "l");
	legend->AddEntry(cos2_exp, "Theoric", "l");
	legend->Draw();
	c1->Print("counts_vs_theta.png");

	Grafica->Run();
	return 0;
}
