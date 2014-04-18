//-------------------------------------------------------------
// Description:  FCC study of X->VV with jet substructure
// Authors:      Maurizio Pierini, CERN
//-------------------------------------------------------------

///  The FCCExoVV class implements the study of arXiv:XXXX

#ifndef FCCExoVV_h
#define FCCExoVV_h

#include <vector>
#include <TVector3.h>
#include <TLorentzVector.h>

#include "FCC/FCCReco.hh"

using namespace std;

class FCCExoVV : public FCCReco {
public:
  
  //! constructor
  FCCExoVV(TTree *tree);
  //! destructor
  virtual ~FCCExoVV();
  //! loop over events
  void Loop(string outFileName);
  
private:
  /// Find the index of the first V boson in the list
  /// of gen particles, other than the otherV index
  int FindVindex(int otherV);

  /// check if a Z decayed to leptons
  bool leptonZDecay();
  /// check if a W decayed to leptons
  bool leptonWDecay();


};
#endif
