//-------------------------------------------------------
// Description:  CMS  SSDilepBtag analysis 
// Authors:      Maurizio Pierini, CERN
//-------------------------------------------------------

///  The CMSSSDilepBtag class implements the SSDilepBtag
///  EXO search by the CMS collaboration, EXO-11-095

#ifndef CMSSSDilepBtag_h
#define CMSSSDilepBtag_h

#include <vector>
#include <TVector3.h>
#include <TLorentzVector.h>

#include "CMS/CMSReco.hh"
#include "CommonTools/DataAnalysis.hh"
#include "CMS/CMSHemisphere.hh"

using namespace std;

class CMSSSDilepBtag : public CMSReco, public DataAnalysis {
public:
  
  //! constructor
  CMSSSDilepBtag(TTree *tree, string ModelName, double Lumi, string analysis);
  //! destructor
  virtual ~CMSSSDilepBtag();
  //! loop over events
  void Loop();
  
private:
  double weightBtag(double thisPt);
  double weightElectron(double thisPt);
  double weightMuon(double thisPt);
  double weightMET(double thisMET, double METmin);
  double weightHT(double thisHT, double HTmin);
  double turnOn(double x, double x12, double sigma);

  // model name
  string _ModelName;
  //Signal-yield posterior
  TH1D* _Ps0;
  TH1D* _Ps1;
  TH1D* _Ps2;
  TH1D* _Ps3;
  TH1D* _Ps4;
  TH1D* _Ps5;
  TH1D* _Ps6;
  TH1D* _Ps7;
  TH1D* _Ps8;
  // input file with likelihood
  TFile* _fileLikelihood;  
};
#endif
