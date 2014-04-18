//-------------------------------------------------------
// Description:  CMS Zprime analysis
// Authors:      Raffaele Tito D'Agnolo, SNS
//-------------------------------------------------------

#ifndef CMSZprime_h
#define CMSZprime_h

#include <vector>
#include <TVector3.h>
#include <TLorentzVector.h>

#include "CMSReco.hh"
#include "DelphesGenTree.hh"
using namespace std;

class CMSZprime : public CMSReco {

public:
  
  //! constructor
  CMSZprime(TTree *tree=0, bool vecbosFlag=false);
  //! destructor
  virtual ~CMSZprime();
  //! loop over events
  void Loop(string outFileName);
  //Muon identification
  bool isCMSMuon(int iMu);

private:

};
#endif
