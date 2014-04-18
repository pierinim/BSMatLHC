//-------------------------------------------------------
// Description:  CMS Lepton efficiencies check 
// Authors:      Raffaele Tito D'Agnolo, SNS
//-------------------------------------------------------

#ifndef CMSLeptEff_h
#define CMSLeptEff_h

#include <vector>
#include <TVector3.h>
#include <TLorentzVector.h>

#include "CMSReco.hh"

using namespace std;

class CMSLeptEff : public CMSReco {
public:
  
  //! constructor
  CMSLeptEff(TTree *tree=0, bool vecbosFlag=false, bool isMu=true, TString Selector="WP80");
  //! destructor
  virtual ~CMSLeptEff();
  //! loop over events
  void Loop(string outFileName);
  
private:
  bool _isMu;
  TString _Selector;

};
#endif
