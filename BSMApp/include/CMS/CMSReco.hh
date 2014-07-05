//--------------------------------------------------------------
// Description:  CMS-specific Reconstruction algorithms 
// Authors:      Maurizio Pierini, CERN
//--------------------------------------------------------------

/// The CMSReco class includes generic algorithms for
/// CMS data analysis (eg isolation, btagging, etc)

#ifndef CMSReco_h
#define CMSReco_h

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

// CMSRecoApp includes
#include <CommonTools/DetectorReco.hh>
#include <CMS/CMSDetectorResponse.hh>

using namespace std;

class CMSReco : public DetectorReco{

public:

  /// Class Constructor
  CMSReco(TTree *tree=0);
  /// Class Destructor
  virtual ~CMSReco();

protected:
  
  /// CMS Electron selectors
  bool EleSelector(int iEle,string Selector);
  /// CMS Muon Selector
  bool MuonSelector(int iMu, string Selector);
  /// PFMET reconstruction
  void PFMETReco();
  /// CaloMET reconstruction
  void CaloMETReco();
  /// Muon Reconstruction: Tight and Loose muons
  void MuReco();
  /// Electron Reconstruction: WP80 and WP95
  void EleReco();
  /// Track Reconstruction
  void TrackReco(double minPt = 0.5);
  /// PF reconstruction (gen particles -> 5 classes of PF candidates)
  void PFReco();
  /// Return list of pfcandidates (to be used eg to cluster jets or compute MET)
  vector<fastjet::PseudoJet> PFJetConstituents(vector<fastjet::PseudoJet> muToRemove,
					     vector<fastjet::PseudoJet> eleToRemove,
					       vector<fastjet::PseudoJet> photonToRemove);

  void GenReturn(int &gen1, vector<double> &gen2, vector<double> &gen3, vector<double> &gen4, vector<double> &gen5, vector<int> &gen6, vector<int> &gen7);
	

  /// Compute missing pixel hits for a give track
  /// due to detector inefficiency and/or track displacement
  int MissingPixelHits(int iTrack);

  // SUSY kinematic variables

  /// Compute Missing Ht = |Sum_jet pT| [used in SUSY searches]
  fastjet::PseudoJet CalcMHT(vector<fastjet::PseudoJet> jets);
  /// Compute Ht = Sum_jet |pT| [used in SUSY searches]
  double CalcHT(vector<fastjet::PseudoJet> jets);
  /// Compute Alpha_T [used in SUSY searches]
  double CalcAlphaT(fastjet::PseudoJet ja, fastjet::PseudoJet jb);
  /// Compute MR  [used in SUSY searches]
  double CalcMR(fastjet::PseudoJet ja, fastjet::PseudoJet jb);
  /// Compute MR invariant (use energies in place of |p| for each hemisphere
  double CalcMR_zinvariant(fastjet::PseudoJet ja, fastjet::PseudoJet jb);
  /// Compute MR' [used in SUSY searches]
  double CalcMRP(fastjet::PseudoJet ja, fastjet::PseudoJet jb, fastjet::PseudoJet met);
  /// Compute MR_T  [used in SUSY searches]
  double CalcMRT(fastjet::PseudoJet ja, fastjet::PseudoJet jb, fastjet::PseudoJet met);

  // Jet Tagging

  /// b Tagging Algorithms
  bool BTagCSVM(fastjet::PseudoJet j, double dR);

  /// b Tagging Algorithms
  bool BTagHiggs(fastjet::PseudoJet j, double dR);

  /// bootsed top tagging algorithm with substructure
  /// bootsed W/Z tagging algorithm with substructure
  /// bootsed H tagging algorithm with substructure

  /// Clean the event-related content (jets, MET, etc) from memory
  void CleanEvent();

  CMSDetectorResponse* cms;

  /// verbosity flag
  bool _verbose;

  // Electron block
  vector<int>            idxEleWP80;
  vector<TLorentzVector> EleWP80;
  vector<int>            idxEleWP95;
  vector<TLorentzVector> EleWP95;

  // Muon Block
  vector<int>            idxTightMu;
  vector<TLorentzVector> TightMu;
  vector<int>            idxLooseMu;
  vector<TLorentzVector> LooseMu;

  // TrackBlock
  vector<int>            idxRecoTrack;
  vector<TLorentzVector> Track;
  
  // Tau Block
  //  vector<int>            idxTau;
  //  vector<TLorentzVector> recoTau;

  // Photon block
  //  vector<TLorentzVector> recoPhoton;
  //  vector<TVector3>       vtxRecoPhoton;    

  // PFMET
  fastjet::PseudoJet PFMET;
  fastjet::PseudoJet PFMET_nomuon;
  fastjet::PseudoJet CaloMET;

  // PF candidates
  vector<fastjet::PseudoJet> _PFElectrons;
  vector<fastjet::PseudoJet> _PFMuons;
  vector<fastjet::PseudoJet> _PFPhotons;
  vector<fastjet::PseudoJet> _PFChHadrons;
  vector<fastjet::PseudoJet> _PFNeuHadrons;

private:
  bool FoundParticle(fastjet::PseudoJet p, vector<fastjet::PseudoJet> q, double dR);

};

#endif
