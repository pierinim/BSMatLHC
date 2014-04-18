#define DelphesGenTree_cxx
#include <DelphesGenTree.hh>
#include <TLorentzVector.h>
#include <math.h>
#include <iostream>

using namespace std;

void DelphesGenTree::GetEvent(int i) {
  fChain->GetEntry(i);
}

bool DelphesGenTree::MatchParticle(TLorentzVector recoParticle, int idMc, bool cpSensitive) {
  bool matched = false;
  for(int i=0; i<Particle_size; i++) {
    // stable partciles
    if(Particle_Status[i] != 1) continue;
    if((cpSensitive && Particle_PID[i] == idMc) ||
       (!cpSensitive && abs(Particle_PID[i]) == idMc)) {
      // cone requirement
      TLorentzVector myGenParticle(Particle_Px[i], Particle_Py[i], Particle_Pz[i], Particle_E[i]);
      if(myGenParticle.DeltaR(recoParticle) < 0.1) {
	matched = true;
      }
    }
  }
  return matched;
}

TLorentzVector DelphesGenTree::MatchedParticle(TLorentzVector recoParticle, int idMc, bool cpSensitive) {
  TLorentzVector theGenParticle;
  for(int i=0; i<Particle_size; i++) {
    // stable partciles
    if(Particle_Status[i] != 1) continue;
    if((cpSensitive && Particle_PID[i] == idMc) ||
       (!cpSensitive && abs(Particle_PID[i]) == idMc)) {
      // cone requirement
      TLorentzVector myGenParticle(Particle_Px[i], Particle_Py[i], Particle_Pz[i], Particle_E[i]);
      if(myGenParticle.DeltaR(recoParticle) < 0.1) {
	theGenParticle = myGenParticle;
      }
    }
  }
  return theGenParticle;
}

double DelphesGenTree::ChargeParticlesIsolation(TLorentzVector recoParticle, double dR, double etaRange) {
  double coneEnergy = 0.;
  for(int i=0; i<Particle_size; i++) {
    // stable partciles
    if(Particle_Status[i] != 1) continue;
    // charged particles
    if(fabs(Particle_Charge[i])>0.) {
      // cone requirement
      TLorentzVector myGenParticle(Particle_Px[i], Particle_Py[i], Particle_Pz[i], Particle_E[i]);
      // eta range
      if(fabs(myGenParticle.Eta())<etaRange) {
	if(myGenParticle.DeltaR(recoParticle) < dR &&
	   myGenParticle.DeltaR(recoParticle) > 0.01) coneEnergy+= myGenParticle.Pt();
      }
    }
  }
  // subtract the energy of the reference Reco particle
  // to compute the energy of all the others
  return coneEnergy;
}

bool DelphesGenTree::isBJet(TLorentzVector recoJet, double dR){
  bool ret=false;
  for(int i=0; i<Particle_size; i++) {
    // stable partciles     
    if(Particle_Status[i] != 1) continue;
    // b quarks
    if(abs(Particle_PID[i])==5){
      TLorentzVector myGenParticle(Particle_Px[i], Particle_Py[i], Particle_Pz[i], Particle_E[i]);
      if(myGenParticle.DeltaR(recoJet) < dR)ret=true;
    }
  }
  
  return ret;
  
}
