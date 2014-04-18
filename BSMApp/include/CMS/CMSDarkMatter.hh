//-------------------------------------------------------
// Description:  CMS  DarkMatter analysis 
// Authors:      Maurizio Pierini, CERN
//-------------------------------------------------------

///  The CMSDarkMatter class implements the DarkMatter
///  EXO search by the CMS collaboration, EXO-11-095

#ifndef CMSDarkMatter_h
#define CMSDarkMatter_h

#include <vector>
#include <TVector3.h>
#include <TLorentzVector.h>

#include "CMS/CMSReco.hh"
#include "CommonTools/DataAnalysis.hh"
#include "CMS/CMSHemisphere.hh"
#include "CommonTools/JetSubstructure.hh"

using namespace std;

class CMSDarkMatter : public CMSReco, public DataAnalysis {
public:
  
  //! constructor
  CMSDarkMatter(TTree *tree, string ModelName, double Lumi, string analysis);
  //! destructor
  virtual ~CMSDarkMatter();
  //! loop over events
  void Loop(string outFileName);
  
private:
  // model name
  string _ModelName;

  /// 
  bool TopTagTypeI(fastjet::PseudoJet prunedjet, JetSubstructure* subStruct);
  /// 
  bool VTag(fastjet::PseudoJet prunedjet, JetSubstructure* subStruct);
  ///
  bool HTag(fastjet::PseudoJet prunedjet, JetSubstructure* subStruct);
  /// 
  bool BtagSubJets(vector<fastjet::PseudoJet> particles, fastjet::JetDefinition jetdef, double minpT, double maxEta, int nBtag);

};
#endif
