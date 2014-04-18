//-----------------------------------------------------------------
// Description:  Conatiner of Jet substructure variables calculation
// Authors:      Maurizio Pierini, CERN
//-----------------------------------------------------------------

#ifndef JetSubstructure_h
#define JetSubstructure_h

// FASTJET includes     
#include "fastjet/include/fastjet/PseudoJet.hh"
#include "fastjet/include/fastjet/ClusterSequence.hh"

using namespace std;

class JetSubstructure {
public:
  //! constructor
  JetSubstructure(fastjet::PseudoJet Jet, vector<fastjet::PseudoJet> constituents, double jetRadius);
  //! destructor
  virtual ~JetSubstructure();

  /// Compute N-subjettiness
  double Nsubjettiness(int N);

protected:
  /// jet constituents
  vector<fastjet::PseudoJet> _constituents;
  /// size of the original jet
  double _R;

};
#endif
