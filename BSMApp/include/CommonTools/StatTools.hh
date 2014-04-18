//-----------------------------------------------------------------
// Description:  minimal set of statistics tools
// Authors:      Maurizio Pierini, CERN
//-----------------------------------------------------------------

#ifndef StatTools_h
#define StatTools_h

#include <TH2D.h>
#include <TH1D.h>
#include <TRandom3.h>
#include <TFile.h>
#include <TString.h>
#include <TMath.h>

using namespace std;

class StatTools {
public:
  
  //! constructor
  StatTools(int seed);
  //! destructor
  virtual ~StatTools();
  /// Find excluded upper value for s, given a likelihood of s*scale and a Credibility Level
  double FindUL(TH1D* Lik, double CL, double scale);
  
  /// perform hit or miss
  bool HitOrMiss(double y);

  /// Provide the posterior on a signal s, inetgrating out the nuisance parameter
  /// b (background) out of a likelihood model
  /// L = P(n|s+b)*G(b|CenB, SigB)
  /// where CenB +/- SigB is the expected background and n is the observed yield. A flat prior on b is assumed
  TH1D* LogNormPoissonConv(TString name, Double_t n, Double_t CenB, Double_t SigB,  Double_t smin = 0., Double_t smax = 100.);

  /// Convolution of a given pdf with a log-normal of a given error sigma,
  /// representing the systematic error on the signal
  /// here sigma is given in [0,1], representing the relative error
  TH1D* LogNormHistoConv(TH1D* histo, double sigma);

protected:

private:

};
#endif
