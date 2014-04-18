//-------------------------------------------------------
// Description:  CMS  MonoJet analysis 
// Authors:      Maurizio Pierini, CERN
//-------------------------------------------------------

///  The CMSMonoJet class implements the MonoJet
///  EXO search by the CMS collaboration, EXO-11-095

#ifndef CMSMonoJet_h
#define CMSMonoJet_h

#include <vector>
#include <TVector3.h>
#include <TLorentzVector.h>

#include "CMS/CMSReco.hh"
#include "CommonTools/DataAnalysis.hh"
#include "CMS/CMSHemisphere.hh"

using namespace std;

class CMSMonoJet : public CMSReco, public DataAnalysis {
public:
  
  //! constructor
  CMSMonoJet(TTree *tree, string ModelName, double Lumi, string analysis);
  //! destructor
  virtual ~CMSMonoJet();
  //! loop over events
  void Loop();
  
private:
  // model name
  string _ModelName;
  //Signal-yield posterior
  TH1D* _Ps250;
  TH1D* _Ps300;
  TH1D* _Ps350;
  TH1D* _Ps400;
  TH1D* _Ps250MU;
  TH1D* _Ps300MU;
  TH1D* _Ps350MU;
  TH1D* _Ps400MU;
  // input file with likelihood
  TFile* _fileLikelihood;
  
};
#endif
