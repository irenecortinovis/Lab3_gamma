/*
compile with:
g++ chisquare_test.cpp -o chisquare_test.o `root-config --cflags --glibs`
*/

//This program calculates Chisquare of TGraph with respect to a set of functions.

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

TLegend *legend = new TLegend(0.72, 0.55, 0.97, 0.92);
TGraphErrors *angles;

void SetFunc(TF1 *func, TString name, Color_t color, double p0, double p1, double p2) {
	func = new TF1(name, "[0]*([1]*(cos(pi*x/180))**2 + [2]*(cos(pi*x/180))**4 + 1)", 180., 270.);
	func->SetParameters(p0, p1, p2);
	func->SetLineStyle(7);
	func->SetLineColor(color);
	func->Draw("same");
	double chisquare = angles->Chisquare(func);
	double chisquare_red = chisquare/(angles->GetN() - 1);	//N.B.: chi_red = chi / (N-1)  !!!!
	std::cout << name << "\t" << chisquare << "\t\t" << chisquare_red << std::endl;
	legend->AddEntry(func, name, "l");
}

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
	//TGraphErrors *angles = new TGraphErrors(npoints-1, theta, count2_corr);
	angles = new TGraphErrors(npoints-1, theta, count2_corr);
	double *y = angles->GetY();
	for(int i = 0; i < angles->GetN(); i++) {
		angles->SetPointError(i, 1, err_corr[i]);			//(i, ex, ey)
	}

	angles->SetTitle("Angular correlation - #Chi^{2} test; #theta (#circ); N_{counts}");
	angles->SetMarkerColor(kBlue);
	angles->SetLineColor(kBlue);
	angles->SetMarkerStyle(7);
	angles->SetMarkerSize(5);

	gStyle->SetOptFit(1111);

	TCanvas *c1 = new TCanvas("chisquare_test","chisquare_test",800,600);
	angles->Draw("ape");
	legend->AddEntry(angles, "Data", "l");
	std::cout << "decay\tchisquare\tchisquare (red)" << std::endl;
	TF1 *QQ24, *QQ23, *QQ22, *QQ21, *QQ20, *DQ21, *DQ22, *DQ23, *QD13, *QD12, *QD11, *DD12, *DD11, *DD10;	
	SetFunc(QQ24, "QQ24", kRed, y[angles->GetN() - 1], 0.125, 0.042);
	SetFunc(QQ23, "QQ23", kOrange, y[angles->GetN() - 1], 0., -1./3.);
	SetFunc(QQ22, "QQ22", kYellow, y[angles->GetN() - 1], -15./13., -16./13.);
	SetFunc(QQ21, "QQ21", kGreen, y[angles->GetN() - 1], 5., -16./3.);
	SetFunc(QQ20, "QQ20", kGreen+3, y[angles->GetN() - 1], -3., 4.);
	SetFunc(DQ21, "DQ21 & QD11 & DD12 & DD11", kCyan, y[angles->GetN() - 1], -1./3., 0.);
	SetFunc(DQ22, "DQ22 & QD12", kMagenta, y[angles->GetN() - 1], 3./7., 0.);		//DOPPIONE
	SetFunc(DQ23, "DQ23 & QD13", kViolet, y[angles->GetN() - 1], -3./29., 0.);	//DOPPIONE
	//SetFunc(QD13, "QD13", kCyan, y[angles->GetN() - 1], -3./29., 0.);
	//SetFunc(QD12, "QD12", kBrown, y[angles->GetN() - 1], 3./7., 0.);	//DOPPIONE
	//SetFunc(QD11, "QD11", kViolet, y[angles->GetN() - 1], -1./3., 0.);	//DOPPIONE
	//SetFunc(DD12, "DD12", kBrown, y[angles->GetN() - 1], -1./3., 0.);	//DOPPIONE
	//SetFunc(DD11, "DD11", kBrown, y[angles->GetN() - 1], -1./3., 0.);	//DOPPIONE
	SetFunc(DD10, "DD10", kGray, y[angles->GetN() - 1], 1., 0.);	//DOPPIONE

	//(angles->GetYaxis())->SetLimits(1000.,9000.);
	angles->SetMinimum(4000.);
	angles->SetMaximum(12000.);

	legend->Draw();
	c1->Print("chisquare_test.png");

	Grafica->Run();
	return 0;
}
