#include "peak.h"

// ----------- CONSTRUCTORS AND DESTRUCTOR --------------

//ctor
peak::peak(double minimum, double maximum, TH1F* histo)
{
  this->histo_dat = histo;
  this->minx = minimum;
  this->maxx = maximum;
  std::cout << "Peak object initialised" << std::endl;
}

//dtor
peak::~peak()
{
	std::cout << "Peak object deleted" << std::endl;
}

// ----------------- METHODS --------------------

void peak::FitSingleGaus(double norm1, double mean1fit)
{
  this->fitfunc = new TF1 ("fitgaus","gaus(0) + [3]",this->minx,this->maxx);
	(this->fitfunc) -> SetNpx (100000);
	(this->fitfunc) -> SetLineWidth (2);
	(this->fitfunc) -> SetLineColor (kBlue);
  (this->fitfunc) -> SetParameters (norm1,mean1fit,3,0);
  (this->histo_dat) -> Fit("fitgaus","R");
}


void peak::FitDoubleGaus(double norm1, double mean1fit, double norm2, double mean2fit)
{
  this->fitfunc = new TF1 ("fitfunc","gaus(0) + gaus(3) + pol1(6)",this->minx,this->maxx);
	(this->fitfunc) -> SetNpx (100000);
	(this->fitfunc) -> SetLineWidth (2);
	(this->fitfunc) -> SetLineColor (kBlue);
  (this->fitfunc) -> SetParameters (norm1,mean1fit,5,norm2,mean2fit,10,50,0);
  (this->histo_dat) -> Fit("fitfunc","R");
}

void peak::DrawPeak(std::string namecanvas)
{
  (this->c1) = new TCanvas(namecanvas.c_str(), namecanvas.c_str(), 1200, 800);
  (this->histo_dat) -> Draw();
  (this->histo_dat)->GetXaxis()->SetRange(this->minx,this->maxx);
  std::string title = namecanvas + ".png";
	(this->c1)->Print(title.c_str());
}

void peak::GetFitVariablesSingleGaus()
{
  this->mean1 = (this->fitfunc) -> GetParameter (1);
  this->err_mean1 = (this->fitfunc) -> GetParError (1);
  this->FWHM1 = fabs((this->fitfunc) -> GetParameter (2)*2.35);
  this->err_FWHM1 = (this->fitfunc) -> GetParError (2)*2.35;

  std::cout << "FWHM single gaussian:\t" << this->FWHM1 << " +- " << this->err_FWHM1 << std::endl;
}

void peak::GetFitVariablesDoubleGaus()
{
  this->mean1 = (this->fitfunc) -> GetParameter (1);
  this->mean2 = (this->fitfunc) -> GetParameter (4);
  this->err_mean1 = (this->fitfunc) -> GetParError (1);
  this->err_mean2 = (this->fitfunc) -> GetParError (4);
  this->FWHM1 = (this->fitfunc) -> GetParameter (2)*2.35;
  this->FWHM2 = (this->fitfunc) -> GetParameter (5)*2.35;
  this->err_FWHM1 = (this->fitfunc) -> GetParError (2)*2.35;
  this->err_FWHM2 = (this->fitfunc) -> GetParError (5)*2.35;

  std::cout << "mean1\t" << mean1 << "\t +- \t" << err_mean1 << std::endl;

  this->maximum = (this->fitfunc)->GetMaximum(this->minx,this->maxx);
  std::cout << "maximum value \t" << this->maximum << std::endl;
  this->maximumx = (this->fitfunc)->GetMaximumX(this->minx,this->maxx);
  std::cout << "x of maximum value \t" << this->maximumx << std::endl;
}


void peak::FitDiffFunc()
{
  this->diffunc = new TF1 ("diffunc","abs(-[9] + fitfunc)",this->minx,this->maxx);
  (this->diffunc) -> SetNpx (100000);
  (this->diffunc) -> FixParameter(9,this->maximum*0.5);
}

void peak::GetFWHMtot()
{
  double minimumX1 = (this->diffunc)->GetMinimumX(this->minx,this->mean1);
  double minimumX2 = (this->diffunc)->GetMinimumX(this->mean1,this->maxx);
  std::cout << "min sx \t " << minimumX1 << std::endl;
  std::cout << "min dx \t " << minimumX2 << std::endl;

  this->FWHM_tot = fabs(minimumX2-minimumX1);
  std::cout << "FWHM double gaussian:\t" << this->FWHM_tot << std::endl;
}


double peak::GetIntegral(int binmin, int binmax)
{
  return (this->histo_dat)->Integral(binmin, binmax);
}