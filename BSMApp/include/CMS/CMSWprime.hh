//-------------------------------------------------------
// Description:  CMS Wprime analysis
// Authors:      Raffaele Tito D'Agnolo, SNS
//-------------------------------------------------------

#ifndef CMSWprime_h
#define CMSWprime_h

#include <vector>
#include <TVector3.h>
#include <TLorentzVector.h>

#include "CMSReco.hh"
#include "DelphesGenTree.hh"
using namespace std;

class CMSWprime : public CMSReco {

public:
  
  //! constructor
  CMSWprime(TTree *tree=0, bool vecbosFlag=false);
  //! destructor
  virtual ~CMSWprime();
  //! loop over events
  void Loop(string outFileName);
  //Muon identification
  bool isCMSMuon(int iMu);

private:

};
#endif

