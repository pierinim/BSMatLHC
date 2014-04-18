#include "CommonTools/JetSubstructure.hh"
#include <iostream>
#include <unistd.h>

JetSubstructure::JetSubstructure(fastjet::PseudoJet Jet, vector<fastjet::PseudoJet> constituents, double jetRadius) {
  //  for(int i=0; i<int(constituents.size()); i++) 
    // this should be a collection of fastjet jets
    //    if(Jet.delta_R(constituents[i])<jetRadius) 
  //    _constituents.push_back(constituents[i]);
  _constituents = constituents;
  _R = jetRadius;
}

JetSubstructure::~JetSubstructure() {
}

double JetSubstructure::Nsubjettiness(int N) {
  if(_constituents.size()<N) return -99.;
  // cluster the constituents into N kt-jets
  // when clustering in exclusive mode, R is usually set to 1
  fastjet::ClusterSequence cs(_constituents, fastjet::JetDefinition(fastjet::kt_algorithm, 1.0));
  vector<fastjet::PseudoJet> subjets = fastjet::sorted_by_pt(cs.exclusive_jets(N));

  // compute the N-subjettiness
  double Nsubj = 0.;
  double normFactor = 0.;
  for(int i=0; i<int(_constituents.size()); i++) {
    double DRmin = 99999999999.;
    for(int j=0; j<int(subjets.size()); j++) {
      if(_constituents[i].delta_R(subjets[j]) <DRmin) DRmin = _constituents[i].delta_R(subjets[j]);
    }
    Nsubj += _constituents[i].pt()*DRmin;
    normFactor += _constituents[i].pt()*_R;
  }
  return Nsubj/normFactor;
}
