//-----------------------------------------------------------------
// Description:  Likelihood for a generic counting experiment
// Authors:      Maurizio Pierini, CERN
//-----------------------------------------------------------------

#ifndef CountingExperiment_h
#define CountingExperiment_h

#include <TH2D.h>
#include <TH1D.h>
#include <TRandom3.h>
#include <TFile.h>
#include <TString.h>
#include <TMath.h>

#include <CommonTools/StatTools.hh>

using namespace std;

class CountingExperiment {
public:
  
  //! constructor
  CountingExperiment(Int_t n, Double_t b, Double_t db, Double_t mins, Double_t maxs);
  //! constructor
  CountingExperiment(){};
  //! destructor
  virtual ~CountingExperiment();
  /// Create 1D bin-by-bin histograms of the posterior on s
  void CreatePosteriors(TString outputFname, TString name, TString openMode);
  
protected:
  /// Basic statistics tools
  StatTools* _statTools;

private:
  /// Observed yield
  Int_t _n;
  /// Expected background
  Double_t _b;
  /// Error on expected background
  Double_t _db;
  /// Mininimum signal yield
  Double_t _mins;
  /// Maximum signal yield
  Double_t _maxs;

};
#endif
