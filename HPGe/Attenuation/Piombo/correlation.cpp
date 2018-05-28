/*
compile with:
g++ correlation.cpp -o correlation.o `root-config --cflags --glibs`
*/

//This program fits the attenuation with an exponential function

#include <fstream>
#include <stdlib.h>
#include <TMultiGraph.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TCanvas.h>
#include <TApplication.h>
#include <TStyle.h>
#include <TROOT.h>
#include <string>
#include <vector>
#include <TLegend.h>

int main(int argc, char **argv) {
	TApplication* Grafica = new TApplication("Grafica", 0, NULL);
  gStyle->SetOptFit(1111);

  std::ifstream myfile("Attenuation.txt");
  std::string line;
  int i=0;
  std::vector<double> x_depth, y_peak1, y_peak2, y_peak3;
  while(myfile >> line)
  {
    if (i>3)
    {
      if(i%4 == 0)
        x_depth.push_back(atof(line.c_str()));
      if(i%4 == 1)
        y_peak1.push_back(atof(line.c_str()));
      if(i%4 == 2)
        y_peak2.push_back(atof(line.c_str()));
      if(i%4 == 3)
        y_peak3.push_back(atof(line.c_str()));
    }
    i++;
  }

  TGraphErrors *graph_depths1 = new TGraphErrors(x_depth.size(), &x_depth[0], &y_peak1[0]);
	for(int i = 0; i < x_depth.size(); i++) {
		graph_depths1->SetPointError(i, 0.1, sqrt(y_peak1.at(i)));
	}

  TGraphErrors *graph_depths2 = new TGraphErrors(x_depth.size(), &x_depth[0], &y_peak2[0]);
	for(int i = 0; i < x_depth.size(); i++) {
		graph_depths2->SetPointError(i, 0.1, sqrt(y_peak2.at(i)));
	}

  TGraphErrors *graph_depths3 = new TGraphErrors(x_depth.size(), &x_depth[0], &y_peak3[0]);
	for(int i = 0; i < x_depth.size(); i++) {
		graph_depths3->SetPointError(i, 0.1, sqrt(y_peak3.at(i)));
	}

	TF1 *expon1 = new TF1("fd1", "[0]*(exp(-[1]*x))", 0., 110.);
	expon1->SetParName(0, "N_{0}");
	expon1->SetParName(1, "#mu");
	expon1->SetParameters(100000., 0.05);
	graph_depths1->SetTitle("Attenuation for lead peak1; #depth (#mm); N_{counts}");
	graph_depths1->SetMarkerColor(kBlue);
	graph_depths1->SetLineColor(kBlue);
	graph_depths1->SetMarkerStyle(7);
	graph_depths1->SetMarkerSize(5);

  TF1 *expon2 = new TF1("fd2", "[0]*(exp(-[1]*x))", 0., 110.);
	expon2->SetParName(0, "N_{0}");
	expon2->SetParName(1, "#mu");
	expon2->SetParameters(100000., 0.005);
	graph_depths2->SetTitle("Attenuation for lead peak2; #depth (#mm); N_{counts}");
	graph_depths2->SetMarkerColor(kBlue);
	graph_depths2->SetLineColor(kBlue);
	graph_depths2->SetMarkerStyle(7);
	graph_depths2->SetMarkerSize(5);

  TF1 *expon3 = new TF1("fd3", "[0]*(exp(-[1]*x))", 0., 110.);
	expon3->SetParName(0, "N_{0}");
	expon3->SetParName(1, "#mu");
	expon3->SetParameters(700., 0.005);
	graph_depths3->SetTitle("Attenuation for lead peak K40; #depth (#mm); N_{counts}");
	graph_depths3->SetMarkerColor(kBlue);
	graph_depths3->SetLineColor(kBlue);
	graph_depths3->SetMarkerStyle(7);
	graph_depths3->SetMarkerSize(5);


	TCanvas *c1 = new TCanvas("counts_vs_depth","counts_vs_depth",1400,800);
  c1->Divide(3,1);
  c1->cd(1);
	graph_depths1->Draw("ape");
	graph_depths1->Fit("fd1", "R");
  c1->cd(2);
  graph_depths2->Draw("ape");
	graph_depths2->Fit("fd2", "R");
  c1->cd(3);
  graph_depths3->Draw("ape");
	graph_depths3->Fit("fd3", "R");


  //Value of mu
  double weight1 = 1/pow(expon1->GetParError(1),2);
  double weight2 = 1/pow(expon2->GetParError(1),2);
  double mu1 = expon1->GetParameter(1);
  double mu2 = expon2->GetParameter(1);

  double mu_final = (mu1*weight1+mu2*weight2)/(weight1+weight2);
  double mu_final_err = sqrt(1/(weight1+weight2));
  std::cout << "Mu = " << mu_final*1000 << "\t +- \t" << mu_final_err*1000 << "m-1" << std::endl;


	c1->Print("counts_vs_depth.png");

	Grafica->Run();
	return 0;
}
