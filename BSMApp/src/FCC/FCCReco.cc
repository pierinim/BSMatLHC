#include "FCC/FCCReco.hh"

using namespace std;
using namespace stdcomb;

FCCReco::FCCReco(TTree *tree) : DetectorReco(tree) {
  dR = 0.5;
  fccDetector = new DetectorResponse(99999);
  // we sould set the resolution here
}

FCCReco::~FCCReco() {
  delete fccDetector;
}

void FCCReco::RecoTracks() {
  Track.clear();
  // fill the Track collection with all tracks with pT> 0.5 GeV
  Track = ChargedParticles(0.500);
  // apply the smearing: TODO
}

void FCCReco::RecoECALneutrals() {
  ECALneutrals.clear();
  // fill the Track collection with all tracks with pT> 0.5 GeV
  ECALneutrals = FindECALneutrals(0.5);
  // apply the smearing: TODO
}

void FCCReco::ClusterTrackJet(fastjet::JetDefinition jet_def, double minPt, double maxEta) {
  // cluster the tracks into jets 
  TrackJet = SelectByAcceptance(JetMaker(ConvertToPseudoJet(Track), jet_def).inclusive_jets(),minPt,maxEta);
}

void FCCReco::CleanEvent() {
  TrackJet.clear();
  ECALneutrals.clear();
  Track.clear();
}
