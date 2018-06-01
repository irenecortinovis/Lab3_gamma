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
	const int n = 20;
	double theta[n], count1[n], count2[n], count2_corr[n], err_corr[n], count2_acc[n], err_acc[n],
	count1_sb[n], count2_sb[n], count2_corr_sb[n], err_corr_sb[n], count2_acc_sb[n], err_acc_sb[n],
	count2_norm[n], err_norm[n];
	double ratio, err_ratio;
	std::ifstream ratiofile("ratio.txt");
	ratiofile >> ratio >> err_ratio;
	ratiofile.close();
	std::ifstream infile("Co60_correlation.txt");
	int j = 0;
	char buffer[20];
	infile >> buffer >> buffer >> buffer >> buffer >> buffer;
	//std::cout << "Calcolo dell'errore con 2 metodi: statistica di Poisson e propagazione degli errori (errori su N1, N2, ratio)" << std::endl;
	//std::cout << "theta\tpoisson\tpropagation\tvariation" << std::endl;
	double mean_peak1 = 0;
	while(infile.good()) {
		infile >> theta[j] >> count1[j] >> count2[j] >> count1_sb[j] >> count2_sb[j];
		count2_acc[j] = ratio*count1[j];
		count2_corr[j] = count2[j] - count2_acc[j];		//Sottraggo dai conteggi del picco 2 le false coincidenze
		err_acc[j] = count2_acc[j]*sqrt(pow(err_ratio/ratio, 2) + 1./count1[j]);
		err_corr[j] = sqrt(count2[j] + pow(err_acc[j], 2));

		count2_acc_sb[j] = ratio*count1_sb[j];
		count2_corr_sb[j] = count2_sb[j] - count2_acc_sb[j];		//Sottraggo dai conteggi del picco 2 le false coincidenze
		err_acc_sb[j] = count2_acc_sb[j]*sqrt(pow(err_ratio/ratio, 2) + 1./count1_sb[j]);
		err_corr_sb[j] = sqrt(count2_sb[j] + pow(err_acc_sb[j], 2));
		
		//count2_norm[j] = count2_corr_sb[j]/count1_sb[j];
		//err_norm[j] = count2_norm[j]*sqrt(pow(err_corr_sb[j]/count2_corr_sb[j], 2) + 1./count1_sb[j]);

		//std::cout << theta[j] << "\t" << sqrt(count2_corr[j]) << "\t" << err_corr[j];
		//std::cout << "\t\t+" << 100*(err_corr[j] - sqrt(count2_corr[j]))/sqrt(count2_corr[j]) << "%"<< std::endl;
		mean_peak1 += count1[j];
		j++;
	}
	infile.close();
	int npoints = j;
	mean_peak1 /= (npoints - 1);

	for(j = 0; j < npoints-1; j++) {
		count2_norm[j] = count2_corr_sb[j]/mean_peak1;
		err_norm[j] = count2_norm[j]*sqrt(pow(err_corr_sb[j]/count2_corr_sb[j], 2) + 1./mean_peak1);
	}

	TApplication* Grafica = new TApplication("Grafica", 0, NULL);
	TGraphErrors *angles = new TGraphErrors(npoints-1, theta, count2_corr);
	TGraphErrors *angles_sb = new TGraphErrors(npoints-1, theta, count2_corr_sb);
	TGraphErrors *angles_norm = new TGraphErrors(npoints-1, theta, count2_norm);
	double *y = angles->GetY();
	for(int i = 0; i < angles->GetN(); i++) {
		angles->SetPointError(i, 1, err_corr[i]);			//(i, ex, ey)
		angles_sb->SetPointError(i, 1, err_corr_sb[i]);		//(i, ex, ey)
		angles_sb->SetPointError(i, 1, err_norm[i]);		//(i, ex, ey)
	}

	//TF1 *cos2 = new TF1("cos2", "[0]*([1]*(cos(x/180*pi))**2 + [2]*(cos(x/180*pi))**4) + [3]", 180., 270.);
	TF1 *cos2 = new TF1("cos2", "[0]*([1]*(cos(pi*x/180))**2 + [2]*(cos(pi*x/180))**4 + 1)", 180., 270.);
	TF1 *cos2_sb = new TF1("cos2_sb", "[0]*([1]*(cos(pi*x/180))**2 + [2]*(cos(pi*x/180))**4 + 1)", 180., 270.);
	TF1 *cos2_norm = new TF1("cos2_norm", "[0]*([1]*(cos(pi*x/180))**2 + [2]*(cos(pi*x/180))**4 + 1)", 180., 270.);
	cos2->SetParName(0, "N_{0}");
	cos2->SetParName(1, "a1");
	cos2->SetParName(2, "a2");

	cos2_sb->SetParName(0, "N_{0}");
	cos2_sb->SetParName(1, "a1");
	cos2_sb->SetParName(2, "a2");
	
	cos2_norm->SetParName(0, "N_{0}");
	cos2_norm->SetParName(1, "a1");
	cos2_norm->SetParName(2, "a2");
	
	//cos2->SetParName(3, "offset");
	cos2->SetParameters(6400, 0.125, 0.04);
	cos2_sb->SetParameters(6400, 0.125, 0.04);
	cos2_norm->SetParameters(6400, 0.125, 0.04);
	//cos2->FixParameter(0, 1794);
	//cos2->FixParameter(1, 0.125);
	//cos2->FixParameter(2, 0.042);
	//cos2->SetParLimits(1, 0.118, 0.138);
	//cos2->SetParLimits(2, 0.038, 0.044);
	angles->SetTitle("Angular correlation #gamma-#gamma ^{60}Co; #theta (#circ); N_{counts}");
	angles->SetMarkerColor(kBlue);
	angles->SetLineColor(kBlue);
	angles->SetMarkerStyle(7);
	angles->SetMarkerSize(5);

	angles_sb->SetTitle("Angular correlation signal + background; #theta (#circ); N_{counts}");
	angles_sb->SetMarkerColor(kBlue);
	angles_sb->SetLineColor(kBlue);
	angles_sb->SetMarkerStyle(7);
	angles_sb->SetMarkerSize(5);

	angles_norm->SetTitle("Angular correlation normalized; #theta (#circ); N_{corr} / N_{1}");
	angles_norm->SetMarkerColor(kBlue);
	angles_norm->SetLineColor(kBlue);
	angles_norm->SetMarkerStyle(7);
	angles_norm->SetMarkerSize(5);

	gStyle->SetOptFit(1111);

	TCanvas *c1 = new TCanvas("counts_vs_theta","counts_vs_theta",800,600);
	c1->Divide(2, 2);
	c1->cd(1);
	angles->Draw("ape");
	angles->Fit("cos2", "R");
	c1->cd(2);
	angles_sb->Draw("ape");
	angles_sb->Fit("cos2_sb", "R");
	c1->cd(3);
	angles_norm->Draw("ape");
	angles_norm->Fit("cos2_norm", "R");
	c1->Print("counts_vs_theta.png");

	Grafica->Run();
	return 0;
}
