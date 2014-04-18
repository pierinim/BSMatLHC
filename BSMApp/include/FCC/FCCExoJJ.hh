//-------------------------------------------------------------
// Description:  FCC study of X->VV with jet substructure
// Authors:      Maurizio Pierini, CERN
//-------------------------------------------------------------

///  The FCCExoJJ class implements the bkg study of arXiv:XXXX

#ifndef FCCExoJJ_h
#define FCCExoJJ_h

#include <vector>
#include <TVector3.h>
#include <TLorentzVector.h>

#include "FCC/FCCReco.hh"

using namespace std;

class FCCExoJJ : public FCCReco {
public:
  
  //! constructor
  FCCExoJJ(TTree *tree);
  //! destructor
  virtual ~FCCExoJJ();
  //! loop over events
  void Loop(string outFileName);
  
private:

};
#endif
