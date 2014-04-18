#include "CommonTools/DetectorReco.hh"

//using namespace std;
//using namespace stdcomb;

DetectorReco::DetectorReco(TTree *tree) { 

  verbose = false;  
  Init(tree);

  // Initialize the random seed
  int jobpid = getpid();
  TDatime *now = new TDatime();
  int today = now->GetDate();
  int clock = now->GetTime();
  int seed = today+clock+jobpid;
  gRandom = new TRandom3(seed);

}

DetectorReco::~DetectorReco() {
}

// to write outpur file
void DetectorReco::WriteOut(bool write) {
  writeOut = write;
}

void DetectorReco::SetVerbose(bool v){
  verbose = v;
}

void DetectorReco::SetDR(double myDR){
  dR = myDR;
}

void DetectorReco::GenMET() {
  double genMET_x = 0.;
  double genMET_y = 0.;
  double genMET_nomuon_x = 0.;
  double genMET_nomuon_y = 0.;
  for (int i=0; i<Particle; i++) {
    // check that the particle has non-zero pT
    if(sqrt(ParticlePx[i]*ParticlePx[i]+ParticlePy[i]*ParticlePy[i]) <=0) continue;
    genMET_x += ParticlePx[i];
    genMET_y += ParticlePy[i];
    if(fabs(ParticlePdgId[i])-13 > 0.5) {
      genMET_nomuon_x += ParticlePx[i];
      genMET_nomuon_y += ParticlePy[i];
    }
  }
  genMET = fastjet::PseudoJet(-genMET_x, -genMET_y, 0., sqrt(genMET_x*genMET_x+genMET_y*genMET_y));
  genMET_nomuon = fastjet::PseudoJet(-genMET_nomuon_x, -genMET_nomuon_y, 0., sqrt(genMET_nomuon_x*genMET_nomuon_x+genMET_nomuon_y*genMET_nomuon_y));
}

double DetectorReco::RelGenIso(TLorentzVector p, double DeltaRmax, bool removeParticle) {
  double momFlow = 0.;
  for (int i=0; i<Particle; i++) {
    // check that the particle has a "detectable" pT
     if(sqrt(ParticlePx[i]*ParticlePx[i]+ParticlePx[i]*ParticlePy[i]) <=0.1) continue;
    TLorentzVector myparticle = TLorentzVector(double(ParticlePx[i]), double(ParticlePy[i]), double(ParticlePz[i]), double(ParticleE[i]));
    if (myparticle.DeltaR(p)<DeltaRmax) momFlow += myparticle.Pt();
  }
  if(removeParticle) momFlow -= p.Pt();
  return momFlow/p.Pt();
}

fastjet::ClusterSequence  DetectorReco::JetMaker(vector<fastjet::PseudoJet> particles, fastjet::JetDefinition jet_def) {
  // run the clustering, extract the jets
  return fastjet::ClusterSequence(particles, jet_def);
}

vector<fastjet::PseudoJet> DetectorReco::GenJetConstituents(bool noMuon) {
  vector<fastjet::PseudoJet> particles;
  for (int i=0; i<Particle; i++) {
    // check that the particle has non-zero pT
    if(sqrt(ParticlePx[i]*ParticlePx[i]+ParticlePx[i]*ParticlePy[i]) <=0) continue;
    if(!noMuon ||  fabs(ParticlePdgId[i])-13 > 0.5) 
      particles.push_back(fastjet::PseudoJet(double(ParticlePx[i]), double(ParticlePy[i]), double(ParticlePz[i]), double(ParticleE[i])));
  }

  return particles;
}

fastjet::PseudoJet DetectorReco::ConvertToPseudoJet(TLorentzVector v) {
  return fastjet::PseudoJet(v.Px(), v.Py(), v.Pz(), v.E());
}

vector<fastjet::PseudoJet> DetectorReco::ConvertToPseudoJet(vector<TLorentzVector> v) {
  vector<fastjet::PseudoJet> pseudojets;
  for(int i=0; i<v.size(); i++) {
    pseudojets.push_back(ConvertToPseudoJet(v[i]));
  }
  return pseudojets;
}

TLorentzVector DetectorReco::ConvertTo4Vector(fastjet::PseudoJet v) {
  return TLorentzVector(v.px(), v.py(), v.pz(), v.e());
}

vector<TLorentzVector> DetectorReco::ConvertTo4Vector(vector<fastjet::PseudoJet> v) {
  vector<TLorentzVector> fourvec;
  for(int i=0; i<v.size(); i++) {
    fourvec.push_back(ConvertTo4Vector(v[i]));
  }
  return fourvec;
}

vector<fastjet::PseudoJet> DetectorReco::SelectByAcceptance(vector<fastjet::PseudoJet> v, double pT, double eta){
  vector<fastjet::PseudoJet> vOUT;
  for(int i = 0; i < v.size(); i++){
    if(v[i].pt() > pT && fabs(v[i].eta()) < eta){
      vOUT.push_back(v[i]);
    }
  }
  return vOUT;
}

vector<TLorentzVector> DetectorReco::SelectByAcceptance(vector<TLorentzVector> v, double pT, double eta){
  vector<TLorentzVector> vOUT;
  for(int i = 0; i < v.size(); i++){
    if(v[i].Pt() > pT && fabs(v[i].Eta()) < eta){
      vOUT.push_back(v[i]);
    }
  }
  return vOUT;
}

vector<TLorentzVector> DetectorReco::SortByPt(vector<TLorentzVector> v){
  vector<TLorentzVector> sorted;
  vector<pair<double,int> > pT;
  int N = v.size();
  for(int i=0; i<N; i++) {
    double pt = v[i].Pt();
    pT.push_back(std::make_pair(pt,i));
  }
  // sort from smallest to larger, then reverse.
  std::sort(pT.begin(), pT.end());
  std::reverse(pT.begin(), pT.end());
  for(int i=0; i<pT.size(); i++) 
    sorted.push_back(v[pT.at(i).second]);
  return sorted;
}

vector<TLorentzVector> DetectorReco::SortByEt(vector<TLorentzVector> v){
  vector<TLorentzVector> sorted;
  vector<pair<double,int> > pT;
  int N = v.size();
  for(int i=0; i<N; i++) {
    double pt = v[i].Et(); // No need to change variable names.
    pT.push_back(std::make_pair(pt,i));
  }
  // sort from smallest to larger, then reverse.
  std::sort(pT.begin(), pT.end());
  std::reverse(pT.begin(), pT.end());
  for(int i=0; i<pT.size(); i++) 
    sorted.push_back(v[pT.at(i).second]);
  return sorted;
}

bool DetectorReco::IsCharged(int pdgid){
  int id = abs(pdgid);
  if(id == 12 || // nu_e
     id == 14 || // nu_mu
     id == 16 || // nu_tau
     id == 22 || // photon
     id ==  130 || // KL
     id ==  2112 || // n
     id == 1000021 || // gluino
     id == 1000022 || // chi0_1
     id == 1000039 || // gravitino
     id ==  39 || // graviton
     id ==  111 // pi0
     ) return false;
  // the others should be charged or unstable
  return true;
}

// check if there is a b in the jet
bool DetectorReco::IsBJet(fastjet::PseudoJet j, double dR, double minPt) {
  bool btag = false;
  for(int i=0; i<b; i++) {
    fastjet::PseudoJet thisQuarkB(bPx[i], bPy[i], bPz[i], bE[i]);
    if(j.delta_R(thisQuarkB) < dR && thisQuarkB.pt()>minPt) btag = true;
  }
  return btag;
}

// check if there is a c in the jet
bool DetectorReco::IsCJet(fastjet::PseudoJet j, double dR, double minPt) {
  bool ctag = false;
  for(int i=0; i<c; i++) {
    fastjet::PseudoJet thisQuarkC(cPx[i], cPy[i], cPz[i], cE[i]);
    if(j.delta_R(thisQuarkC) < dR && thisQuarkC.pt()>minPt) ctag = true;
  }
  return ctag;
}

vector<TLorentzVector> DetectorReco::FindECALneutrals(double minPt) {
  vector<TLorentzVector> NeuParticles;
  for(int i=0; i<Particle; i++) {
    // only charged particles
    if(fabs(ParticlePdgId[i]) == 11 || // ele
       //       fabs(ParticlePdgId[i]) == 111 || // pi0
       fabs(ParticlePdgId[i]) == 22){ // photon
      if(sqrt(ParticlePx[i]*ParticlePx[i]+ParticlePy[i]*ParticlePy[i])<minPt) continue;
      double energy = sqrt(ParticlePx[i]*ParticlePx[i]+ParticlePy[i]*ParticlePy[i]+ParticlePz[i]*ParticlePz[i]);
      NeuParticles.push_back(TLorentzVector(ParticlePx[i], ParticlePy[i],ParticlePz[i],energy));
    }
  }
  return NeuParticles;
}

vector<TLorentzVector> DetectorReco::ChargedParticles(double minPt) {
  vector<TLorentzVector> ChParticles;
  for(int i=0; i<Particle; i++) {
    // only charged particles
    //    if(IsCharged(ParticlePdgId[i])) {
    //    cout <<  ParticlePdgId[i] << " " << fabs(ParticlePdgId[i]) << endl;
    if(fabs(ParticlePdgId[i]) == 11 ||
       fabs(ParticlePdgId[i]) == 321 ||
       fabs(ParticlePdgId[i]) == 211 ||
       fabs(ParticlePdgId[i]) == 2212 ||
       fabs(ParticlePdgId[i]) == 11 ||
       fabs(ParticlePdgId[i]) == 13) {
      // at least pT>500 MeV to reconstuct the track
      if(sqrt(ParticlePx[i]*ParticlePx[i]+ParticlePy[i]*ParticlePy[i])<minPt) continue;
      double energy = sqrt(ParticlePx[i]*ParticlePx[i]+ParticlePy[i]*ParticlePy[i]+ParticlePz[i]*ParticlePz[i]);
      ChParticles.push_back(TLorentzVector(ParticlePx[i], ParticlePy[i],ParticlePz[i],energy));
    }
  }
  return ChParticles;
}

fastjet::PseudoJet DetectorReco::AngularMatching(vector<fastjet::PseudoJet> j, fastjet::PseudoJet V) {
  double DRmin = 99999999999.;
  int iGOOD = -99;
  for(int i=0; i< j.size(); i++) {
    if(j[i].delta_R(V)<DRmin) {
      DRmin = j[i].delta_R(V);
      iGOOD = i;
    }
  }
  return j[iGOOD];
}

// check if there is a b in the jet
bool DetectorReco::IsZbbJet(fastjet::PseudoJet j, double dR) {
  int nbquark = 0;
  int nZ = 0;
  for(int i=0; i<b; i++) {
    if(bM1PdgId[i] != 23) continue;
    fastjet::PseudoJet thisQuarkB(bPx[i], bPy[i], bPz[i], bE[i]);
    if(j.delta_R(thisQuarkB) < dR) nbquark++;
  }
  for(int i=0; i<GenTreeParticle; i++) {
    if(GenTreeParticlePdgId[i] != 23) continue;
    fastjet::PseudoJet thisZ(GenTreeParticlePx[i], GenTreeParticlePy[i], GenTreeParticlePz[i], GenTreeParticleE[i]);
    if(j.delta_R(thisZ) < dR) nZ++;
  }
  if(nZ>=1 && nbquark >= 2) return true;
  return false;
}

bool DetectorReco::IsHbbJet(fastjet::PseudoJet j, double dR) {
  int nbquark = 0;
  int nH = 0;
  for(int i=0; i<b; i++) {
    if(bM1PdgId[i] != 25) continue;
    fastjet::PseudoJet thisQuarkB(bPx[i], bPy[i], bPz[i], bE[i]);
    if(j.delta_R(thisQuarkB) < dR) nbquark++;
  }
  for(int i=0; i<GenTreeParticle; i++) {
    if(GenTreeParticlePdgId[i] != 25) continue;
    fastjet::PseudoJet thisH(GenTreeParticlePx[i], GenTreeParticlePy[i], GenTreeParticlePz[i], GenTreeParticleE[i]);
    if(j.delta_R(thisH) < dR) nH++;
  }
  if(nH>=1 && nbquark >= 2) return true;
  return false;
}

bool DetectorReco::IsTopJet(fastjet::PseudoJet j, double dR) {
  int nt = 0;
  for(int i=0; i<GenTreeParticle; i++) {
    if(abs(GenTreeParticlePdgId[i]) != 5) continue;
    fastjet::PseudoJet thisTop(GenTreeParticlePx[i], GenTreeParticlePy[i], GenTreeParticlePz[i], GenTreeParticleE[i]);
    if(j.delta_R(thisTop) < dR) nt++;
  }
  if(nt == 1) return true;
  return false;
}

// check if there is a b in the jet
bool DetectorReco::IsWcsJet(fastjet::PseudoJet j, double dR) {
  int ncquark = 0;
  int nW = 0;
  for(int i=0; i<c; i++) {
    if(abs(bM1PdgId[i]) != 24) continue;
    fastjet::PseudoJet thisQuarkC(cPx[i], cPy[i], cPz[i], cE[i]);
    if(j.delta_R(thisQuarkC) < dR) ncquark++;
  }
  for(int i=0; i<GenTreeParticle; i++) {
    if(abs(GenTreeParticlePdgId[i]) != 24) continue;
    fastjet::PseudoJet thisW(GenTreeParticlePx[i], GenTreeParticlePy[i], GenTreeParticlePz[i], GenTreeParticleE[i]);
    if(j.delta_R(thisW) < dR) nW++;
  }
  if(nW>=1 && ncquark >= 1) return true;
  return false;
}
