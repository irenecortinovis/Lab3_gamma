#ifndef peak_h
#define peak_h

#include <iostream>
#include <cstdlib>
#include <TH1F.h>
#include <TCanvas.h>
#include <TF1.h>
#include <TMath.h>
#include <string>

class peak
{

public:

  double minx;
  double maxx;
  TCanvas* c1;
  TCanvas* c2;
  TH1F* histo_dat;
  TH1F* histo_signal;
  TF1* fitfunc;
  TF1* diffunc;

  double mean1;
  double mean2;
  double err_mean1;
  double err_mean2;
  double FWHM1;
  double FWHM2;
  double err_FWHM1;
  double err_FWHM2;

  double maximum;
  double maximumx;

  double mean_tot;
  double err_mean_tot;
  double FWHM_tot;
  double err_FWHM_tot;

  //constructor
  peak(double minimum, double maximum, TH1F* histo);
  //destructor
  ~peak();

  //methods
  void FitSingleGaus(double norm1, double mean1fit);
  void FitDoubleGaus(double norm1, double mean1fit, double norm2, double mean2fit);
  void DrawPeak(std::string namecanvas="");
  void DrawSignal(std::string namecanvas="");
  void GetFitVariablesDoubleGaus();
  void GetFitVariablesSingleGaus();
  void FitDiffFunc();
  void GetFWHMtot();
  void Getmeantot();
  double GetIntegral(int binmin, int binmax);
  double peak::GetSignalIntegral();
  void GetSignal(std::string namehisto="", int ngaus=0);

};

#endif
