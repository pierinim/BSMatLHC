//-------------------------------------------------------
// Description:  CMS  Razor analysis 
// Authors:      Maurizio Pierini, CERN
// Authors:      Christopher Rogan, Caltech
//-------------------------------------------------------

///  The FCCeeRazor3D class implements the Razor-based
///  SUSY search by the CMS collaboration.
///  http://arxiv.org/abs/1006.2727
///  MISSING ANALYSIS REFERENCE HERE

#ifndef FCCeeRazor3D_h
#define FCCeeRazor3D_h

#include <vector>
#include <TVector3.h>
#include <TLorentzVector.h>

#include "FCC/FCCReco.hh"
#include "CommonTools/DataAnalysis.hh"

using namespace std;

class FCCeeRazor3D : public FCCReco {
public:
  
  //! constructor
  FCCeeRazor3D(TTree *tree);
  //! destructor
  virtual ~FCCeeRazor3D();
  //! loop over events
  void Loop(string outFileName);
  //! Set collision energy
  void SetSqrts(double sqrts);

private:
  /// Luminosity
  double _Lumi;
  /// Collision energy
  double _sqrts;

};
#endif
