//--------------------------------------------------------------
// Description:  Generic Detector class
// Authors:      Maurizio Pierini, CERN
//--------------------------------------------------------------

/// The DetectorReco class is a generic class which contains basic
/// functionality for any analysis. It provides the common interface
/// between the supported input data formats (Delphes and Vecbos)
/// and the specific detectors

#ifndef DetectorReco_h
#define DetectorReco_h

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
#include "combination.hh"

// ROOT includes
#include <TROOT.h>
#include <TRandom3.h>
#include <TVector3.h>
#include <TLorentzVector.h>
#include <TVector2.h>

// FASTJET includes     
#include "fastjet/include/fastjet/PseudoJet.hh"
#include "fastjet/include/fastjet/ClusterSequence.hh"
#include "fastjet/include/fastjet/ClusterSequenceActiveArea.hh"

// DetectorRecoApp includes
#include "DetectorBase.hh"

using namespace std;
using namespace stdcomb;

/// The DetectorReco class is an auxiliary class which contains basic
/// functionality useful for any analysis of DetectorReco+jets events.
/// It derives from DetectorBase.
/// More specialized analysis classes should derive from DetectorReco.
class DetectorReco : public DetectorBase {

public:

  /// Class Constructor
  DetectorReco(TTree *tree=0);
  /// Class Destructor
  virtual ~DetectorReco();
  //! write the outpur file   
  void WriteOut(bool write);
  /// Set verbosity level.
  void SetVerbose(bool v);
  /// Set the size of the jets in the input jet collection
  void SetDR(double myDR);
  /// compute the particle-based isolation at generator level
  /// with tunable cone size, removing or not the reference partcile
  /// from the momentum flow
  double RelGenIso(TLorentzVector p, double DeltaRmax, bool removeParticle = true);

protected:

  /// Verbosity of printouts.
  bool verbose; 

  /// Write output file
  bool   writeOut;

  /// Random number generator
  TRandom3* gRandom;
  
  /// Angular matching between a list of jets and a reference jet
  /// The closests jet to the reference jet is returned. DR is used as distance
  fastjet::PseudoJet AngularMatching(vector<fastjet::PseudoJet> j, fastjet::PseudoJet V);

  /// List of stable charged particles with pt>minPt
  vector<TLorentzVector> ChargedParticles(double minPt = 0.5);

  /// List of stable charged particles with pt>minPt
  vector<TLorentzVector> FindECALneutrals(double minPt = 0.5);

  /// Check if a GenJet has b quarks inside
  bool IsBJet(fastjet::PseudoJet j, double dR, double minPt);

  /// Check if a GenJet has c quarks inside
  bool IsCJet(fastjet::PseudoJet j, double dR, double minPt);

  /// Check if a GenJet is a boosted Z->bb 
  bool IsZbbJet(fastjet::PseudoJet j, double dR);

  /// Check if a GenJet is a boosted H->bb 
  bool IsHbbJet(fastjet::PseudoJet j, double dR);

  /// Check if a GenJet is a boosted top
  bool IsTopJet(fastjet::PseudoJet j, double dR);

  /// Check if a GenJet is a boosted W-> cs
  bool IsWcsJet(fastjet::PseudoJet j, double dR);

  /// Cluster sequence from a generic list of constituents (for the moment antiKt only!!!)
  fastjet::ClusterSequence JetMaker(vector<fastjet::PseudoJet> p, fastjet::JetDefinition jet_def);

  /// Convert a vector of TLorentzVectors to a vector of fastjet pseudojets
  vector<fastjet::PseudoJet> ConvertToPseudoJet(vector<TLorentzVector> v);
  /// Convert a TLorentzVectors to a fastjet pseudojets
  fastjet::PseudoJet ConvertToPseudoJet(TLorentzVector v);
  /// Convert a vector of fastjet pseudojets  to a vector of TLorentzVectors
  vector<TLorentzVector> ConvertTo4Vector(vector<fastjet::PseudoJet> v);
  /// Convert a fastjet pseudojets to a TLorentzVectors
  TLorentzVector ConvertTo4Vector(fastjet::PseudoJet v);

  /// Select visible gen particles (with or without muons)
  vector<fastjet::PseudoJet> GenJetConstituents(bool noMuon);

  /// Compute the MET at generator level
  void GenMET();

   /// Generator-level met
  fastjet::PseudoJet genMET;
  /// Generator-level met calculated ignoring muons
  fastjet::PseudoJet genMET_nomuon;

  /// Jet Size (to set to the value used in Delphes/Vecbos)
  double  dR;
  
  // Some useful templates. The comparators work both with Jets and
  // with TLorentzVectors. Some work with TVector2, TVector3 as well.

  /// Delta phi in radians in between two angles.
  template <typename T> 
  T DeltaPhi(T phi1, T phi2); /// Delta phi in radians in between two angles.

  /// Delta R in between two pairs (eta,phi).
  template <typename T>
  T DeltaR(T eta1, T phi1, T eta2, T phi2); 

  // Compute HT from a collection of Jets
  //  double HT(vector<Jet> jets);

  /// Sorts a vector of Particles by Pt
  vector<TLorentzVector> SortByPt(vector<TLorentzVector> v);
  /// Sorts a vector of Partciles by Et.
  vector<TLorentzVector> SortByEt(vector<TLorentzVector> v);

  /// Select  acording to specified (pT, eta, emFrac) thresholds
  vector<TLorentzVector> SelectByAcceptance(vector<TLorentzVector> v, double pT=0., double eta=10);
  /// Select  acording to specified (pT, eta, emFrac) thresholds
  vector<fastjet::PseudoJet> SelectByAcceptance(vector<fastjet::PseudoJet> v, double pT=0., double eta=10);

  /// Check if a Particle has em charge (not stored by HepMC!!!!)
  bool IsCharged(int pdgid);

};

template <typename T>
T DetectorReco::DeltaPhi(T phi1, T phi2) {
  T result = phi1 - phi2;
  while (result > M_PI) result -= 2*M_PI;
  while (result <= -M_PI) result += 2*M_PI;
  return result;
}

template <typename T>
T DetectorReco::DeltaR(T eta1, T phi1, T eta2, T phi2) {
  T dphi = DeltaPhi(phi1,phi2);
  T result = sqrt((eta1-eta2)*(eta1-eta2)+dphi*dphi);
  return result;
}

#endif
