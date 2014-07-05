//-------------------------------------------------------
// Description:  CMS  Razor analysis 
// Authors:      Maurizio Pierini, CERN
// Authors:      Christopher Rogan, Caltech
//-------------------------------------------------------

///  The CMSRazor class implements the Razor-based
///  SUSY search by the CMS collaboration.
///  http://arxiv.org/abs/1006.2727
///  MISSING ANALYSIS REFERENCE HERE

#ifndef CMSSUSYVars_h
#define CMSSUSYVars_h

#include <vector>
#include <TVector3.h>
#include <TLorentzVector.h>

#include "CMS/CMSReco.hh"
#include "CommonTools/DataAnalysis.hh"
#include "CMS/CMSHemisphere.hh"

using namespace std;

class CMSSUSYVars : public CMSReco, public DataAnalysis {
public:
  
  //! constructor
  CMSSUSYVars(TTree *tree, double Lumi, string analysis);
  //! destructor
  virtual ~CMSSUSYVars();
  //! loop over events
  void Loop(string outFileName);
  void SetSqrts(double sqrts);

private:
  /// Box definition
  int BoxNumber(int iMu, int iEle);
  /// Define the Mu Box
  bool MUBox();
  /// Define the MuEle Box
  bool MUELEBox();
  /// Define the MuMu Box
  bool MUMUBox();
  /// Define the EleEle Box
  bool ELEBox();
  /// Define the Mu Box
  bool ELEELEBox();
  /// Check if event belongs to the Signal Region
  /// for MuMu, EleEle, and MuEle boxes
  bool SignalRegionDiLep(double mr, double rsq);
  /// Check if event belongs to the Signal Region
  /// for Mu and Ele boxes
  bool SignalRegionLep(double mr, double rsq);
  /// Check if event belongs to the Signal Region
  /// for the Had box
  bool SignalRegionHad(double mr, double rsq);
  /// Check if event belongs to the Signal Region
  /// for a specified box 
  bool SignalRegion(double mr, double rsq, double ibox);
  /// Return the posterior distribution for the inclusive xsec,
  /// given a pdf and efficiency for one of the boxes;
  TH1D* XsecProb(TH2D* sigPdf, double eff, TString Filename, int ibin, double xmin, double xmax);
  /// Luminosity
  double _Lumi;

  // collision energy
  double _sqrts;

};
#endif
