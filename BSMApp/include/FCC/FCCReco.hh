//----------------------------------------------------------------------------
// Description:  Generic Reconstruction algorithms for FCC detector studies
// Authors:      Maurizio Pierini, CERN
//----------------------------------------------------------------------------

/// The FCCReco class includes generic algorithms for
/// data analysis (eg isolation, btagging, etc) finalized to
/// the design of a generic detector (e.g. 100 TeV pp collider for FCC studies)

#ifndef FCCReco_h
#define FCCReco_h

// std includes
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <unistd.h>
#include <algorithm>
#include <numeric>
#include <list>
#include "CommonTools/combination.hh"

// FCCRecoApp includes
#include <CommonTools/DetectorReco.hh>
#include <CommonTools/DetectorResponse.hh>

using namespace std;

class FCCReco : public DetectorReco{

public:

  /// Class Constructor
  FCCReco(TTree *tree=0);
  /// Class Destructor
  virtual ~FCCReco();

protected:
  
  /// Reco tracks (stable charged particles with pt>500 GeV and detector smearing)
  void RecoTracks();

  /// Reco electrons, photons, and pi0s
  void RecoECALneutrals();

  /// Cluster Tracks into anti-kT jets of given radius
  void ClusterTrackJet(fastjet::JetDefinition jet_def, double minPt, double maxEta);

  /// Compute N-subjettiness
  //double Nsubjet(vector<TLorentzVector> constituents, vector<TLorentzVector> Njets, double dR);
  void CleanEvent();

  DetectorResponse* fccDetector;

  /// verbosity flag
  bool _verbose;

  // TrackBlock
  vector<TLorentzVector> Track;  
  // ECALneutrals
  vector<TLorentzVector> ECALneutrals;  
  // Jet Block
  vector<fastjet::PseudoJet> TrackJet; 

};

#endif
