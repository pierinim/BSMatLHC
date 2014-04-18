//-------------------------------------------------------
// Description:  CMS WW analysis
// Authors:      Raffaele Tito D'Agnolo, SNS
//-------------------------------------------------------

#ifndef CMSWW_h
#define CMSWW_h

#include <vector>
#include <TVector3.h>
#include <TLorentzVector.h>

#include "CMSReco.hh"
#include "DelphesGenTree.hh"
using namespace std;

class CMSWW : public CMSReco {

public:
  
  //! constructor
  CMSWW(TTree *tree=0, bool vecbosFlag=false);
  //! destructor
  virtual ~CMSWW();
  //! loop over events
  void Loop(string outFileName);
  //Muon identification
  bool isCMSMuon(int iMu);

private:

};
#endif
