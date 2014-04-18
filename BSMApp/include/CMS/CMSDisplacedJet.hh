//-------------------------------------------------------
// Description:  CMS  DisplacedJet analysis 
// Authors:      Maurizio Pierini, CERN
//-------------------------------------------------------

///  The CMSDisplacedJet class implements the search
///  for DisplacedJets in CMS, looking at missing hits
///  in the Pixel for the tracks in a jet

#ifndef CMSDisplacedJet_h
#define CMSDisplacedJet_h

#include <vector>
#include <TVector3.h>
#include <TLorentzVector.h>

#include "CMS/CMSReco.hh"
#include "CMS/CMSHemisphere.hh"

using namespace std;

class CMSDisplacedJet : public CMSReco {
public:
  
  //! constructor
  CMSDisplacedJet(TTree *tree=0);
  //! destructor
  virtual ~CMSDisplacedJet();
  //! loop over events
  void Loop(string outFileName);
  /// Get the output TTree with R and MR by box
  TTree* GetTree();

private:
  /// output TTree
  TTree* outTree;

};
#endif
