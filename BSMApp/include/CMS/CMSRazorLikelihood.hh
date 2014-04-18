//-------------------------------------------------------
// Description:  CMS  Razor likelihood implementation 
// Authors:      Maurizio Pierini, CERN
//-------------------------------------------------------

#ifndef CMSRazorLikelihood_h
#define CMSRazorLikelihood_h

#include <TH2D.h>
#include <TH1D.h>
#include <TRandom3.h>
#include <TFile.h>
#include <TString.h>
#include <TMath.h>
#include <CommonTools/CountingExperiment.hh>
#include <CommonTools/StatTools.hh>

using namespace std;

class CMSRazorLikelihood : CountingExperiment {
public:
  
  //! constructor
  CMSRazorLikelihood(TString inputFname, TString nHname, TString bHname);
  //! destructor
  virtual ~CMSRazorLikelihood();
  /// Create 1D bin-by-bin histograms of the posterior on s
  void CreatePosteriors(TString outputFname);
  
private:
  TH2D* nH;
  TH2D* bH;
  TFile* fileIN;

};
#endif
