#include "CMS/CMSReco.hh"

using namespace std;
using namespace stdcomb;

CMSReco::CMSReco(TTree *tree) : DetectorReco(tree) {
  dR = 0.5;
  cms = new CMSDetectorResponse(99999);
}

CMSReco::~CMSReco() {
  delete cms;
}

void CMSReco::EleReco() {
  for(int i=0; i< Electron; i++) {
    if(sqrt(ElectronPx[i]*ElectronPx[i]+ElectronPy[i]*ElectronPy[i])<5.) continue;
    bool wp95 = false;
    if(EleSelector(i,"WP95") ) {
      EleWP95.push_back(cms->ElectronReco(TLorentzVector(ElectronPx[i],ElectronPy[i],ElectronPz[i],ElectronE[i])));
      idxEleWP95.push_back(i);
      wp95 = true;
    }
    if(EleSelector(i,"WP80") && wp95) {
      EleWP80.push_back(cms->ElectronReco(TLorentzVector(ElectronPx[i],ElectronPy[i],ElectronPz[i],ElectronE[i])));
      idxEleWP80.push_back(i);
    }
  }
}

void CMSReco::TrackReco(double minPt) {
  for(int i=0; i<Particle; i++) {
    // only charged particles
    if(IsCharged(ParticlePdgId[i])) {
      // we need to convert from mm to cm
      double d0 = sqrt(ParticleX[i]*ParticleX[i]+ParticleY[i]*ParticleY[i])/10.;
      // at least pT>500 MeV to reconstuct the track
      if(sqrt(ParticlePx[i]*ParticlePx[i]+ParticlePy[i]*ParticlePy[i])<minPt) continue;
      if(cms->TrackReco(d0)) {
	idxRecoTrack.push_back(i);
	Track.push_back(TLorentzVector(ParticlePx[i], ParticlePy[i],ParticlePz[i],ParticleE[i]));
      }
    }
  }
}

int CMSReco::MissingPixelHits(int iTrack) {
  double d0 = sqrt(ParticleX[iTrack]*ParticleX[iTrack]+ParticleY[iTrack]*ParticleY[iTrack])/10.;
  int missingLayers = 0;
  if(d0 > 4.) missingLayers++;
  if(d0 > 7.) missingLayers++;
  if(d0 > 11.) missingLayers++;
  int crossedLayers = 3-missingLayers;
  for(int i=0; i<crossedLayers; i++) if(!cms->PixelHit()) missingLayers++;
  return missingLayers;
}

void CMSReco::MuReco() {
  for(int i=0; i< Muon; i++) {
    if(sqrt(MuonPx[i]*MuonPx[i]+MuonPy[i]*MuonPy[i])<5.) continue;
    TLorentzVector myMuon(MuonPx[i],MuonPy[i],MuonPz[i],MuonE[i]);
    if(fabs(myMuon.Eta())>2.1) continue;
    bool looseMu = false;
    TLorentzVector recoMuon;
    if(MuonSelector(i,"Loose")) {
      recoMuon = cms->MuonReco(myMuon);
      LooseMu.push_back(recoMuon);
      idxLooseMu.push_back(i);
      if(MuonSelector(i,"Tight")) { 
	TightMu.push_back(recoMuon);
	idxTightMu.push_back(i);
      }
    }
  }
}

void CMSReco::PFReco() {
  // list of gen muons
  for(int i=0; i<Muon; i++) {
    fastjet::PseudoJet p(MuonPx[i], MuonPy[i], MuonPz[i], MuonE[i]);
    if(p.pt()>0.5) _PFMuons.push_back(p);
  }
  
  // list of gen electrons
  for(int i=0; i<Electron; i++) {
    fastjet::PseudoJet p(ElectronPx[i], ElectronPy[i], ElectronPz[i], ElectronE[i]);
    if(p.pt()>0.5) _PFElectrons.push_back(p);
  }

  // list of gen photons
  for(int i=0; i<Photon; i++) {
    fastjet::PseudoJet p(PhotonPx[i], PhotonPy[i], PhotonPz[i], PhotonE[i]);
    if(p.pt()>0.5) _PFPhotons.push_back(p);
  }

  // list of gen charged/neutral hadrons
  for(int i=0; i<Particle; i++) {
    fastjet::PseudoJet p(ParticlePx[i], ParticlePy[i], ParticlePz[i], ParticleE[i]);
    if(p.pt()<0.5) continue;
    if(abs(ParticlePdgId[i]) == 11) continue; // already included as electron
    if(abs(ParticlePdgId[i]) == 13) continue; // already included as muon
    if(abs(ParticlePdgId[i]) == 22) continue; // already included as photon
    if(IsCharged(ParticlePdgId[i])) _PFChHadrons.push_back(p);
    else _PFNeuHadrons.push_back(p);
  }
  
  // smear each particle category

}

vector<fastjet::PseudoJet> CMSReco::PFJetConstituents(vector<fastjet::PseudoJet> muToRemove,
						      vector<fastjet::PseudoJet> eleToRemove,
						      vector<fastjet::PseudoJet> photonToRemove) {
  vector<fastjet::PseudoJet> PFcands;
  for(int i=0; i<_PFElectrons.size(); i++) {
    if(!FoundParticle(_PFElectrons[i], eleToRemove, 0.01))  
      PFcands.push_back(_PFElectrons[i]);
  }
  for(int i=0; i<_PFMuons.size(); i++) {
    if(!FoundParticle(_PFMuons[i], muToRemove, 0.01)) 
      PFcands.push_back(_PFMuons[i]);
  }
  for(int i=0; i<_PFPhotons.size(); i++) {
    if(!FoundParticle(_PFPhotons[i], photonToRemove, 0.01)) 
      PFcands.push_back(_PFPhotons[i]);
  }
  for(int i=0; i<_PFChHadrons.size(); i++) PFcands.push_back(_PFChHadrons[i]);
  for(int i=0; i<_PFNeuHadrons.size(); i++) PFcands.push_back(_PFNeuHadrons[i]);
  return PFcands;
}

bool CMSReco::FoundParticle(fastjet::PseudoJet p, vector<fastjet::PseudoJet> q, double dR) {
  bool found = false;
  for(int i=0; i<q.size(); i++) {
    if(p.delta_R(p)<dR) found = true;
  }
  return found;
}

void CMSReco::CaloMETReco() {
  CaloMET = ConvertToPseudoJet(cms->CaloMETReco(ConvertTo4Vector(genMET_nomuon)));
}

void CMSReco::PFMETReco() {
  PFMET = ConvertToPseudoJet(cms->PFMETReco(ConvertTo4Vector(genMET)));
  PFMET_nomuon =  ConvertToPseudoJet(cms->PFMETReco(ConvertTo4Vector(genMET_nomuon)));
}

// The isolation is the only variable correlated to kinematic
// the rest of the selection can be described by an inefficiency factor
bool CMSReco::EleSelector(int iEle, string Selector){
  if(Selector != "WP80" && Selector != "WP95") {
    cout << "Error in CMSReco::EleSelector: selector " << Selector << " not implemented. Returning TRUE by default" << endl;
    return true;
  }
  TLorentzVector Ele(ElectronPx[iEle], ElectronPy[iEle],ElectronPz[iEle],ElectronE[iEle]);
  // ele eff vs gen-level particle-based isolation
  double genIso = RelGenIso(Ele, 0.3, true);
  return cms->EleEff(Ele, genIso, Selector);
}

// The isolation and the transverse impact parameter are the only variables correlated to kinematic
// the rest of the selection can be described by an inefficiency factor
bool CMSReco::MuonSelector(int iMu, string Selector) {
  if(Selector != "Tight" && Selector != "Loose") {
    cout << "Error in CMSReco::MuonSelector: Selector " << Selector << " not implemented. Returning TRUE by default" << endl;
    return true;
  }
  TLorentzVector Mu(MuonPx[iMu], MuonPy[iMu], MuonPz[iMu], MuonE[iMu]);  
  // apply muon efficiency vs isolation
  double genIso = RelGenIso(Mu, 0.3, true);
  return cms->MuonEff(Mu, genIso, Selector);
}

fastjet::PseudoJet CMSReco::CalcMHT(vector<fastjet::PseudoJet> jets){
  double px=0.;
  double py=0.;
  for(int i=0; i<jets.size(); i++) {
    px += jets[i].px();
    py += jets[i].py();
  }
  return fastjet::PseudoJet(-px,-py, 0., sqrt(px*px+py*py));
}

double CMSReco::CalcHT(vector<fastjet::PseudoJet> jets){
  double HT=0;
  for(int i=0; i<jets.size(); i++) {
    HT += jets[i].pt();
  }
  return HT;
}

double CMSReco::CalcAlphaT(fastjet::PseudoJet ja, fastjet::PseudoJet jb){
  fastjet::PseudoJet jT = ja+jb;
  double MT = sqrt(jT.Et()*jT.Et()-
		   jT.px()*jT.px()-
		   jT.py()*jT.py());
  return jb.Et()/MT;
}

double CMSReco::CalcMR(fastjet::PseudoJet j1, fastjet::PseudoJet j2){
  TLorentzVector ja,jb;
  ja.SetPtEtaPhiE(j1.pt(), j1.eta(), j1.phi(), sqrt(j1.pz()*j1.pz()+j1.perp2()));
  jb.SetPtEtaPhiE(j2.pt(), j2.eta(), j2.phi(), sqrt(j2.pz()*j2.pz()+j2.perp2()));
  return sqrt((ja.P()+jb.P())*(ja.P()+jb.P())-(ja.Pz()+jb.Pz())*(ja.Pz()+jb.Pz()));
}


double CMSReco::CalcMRT(fastjet::PseudoJet j1, fastjet::PseudoJet j2, fastjet::PseudoJet met){
  TLorentzVector ja,jb;
  ja.SetPtEtaPhiE(j1.pt(), j1.eta(), j1.phi(), sqrt(j1.pz()*j1.pz()+j1.perp2()));
  jb.SetPtEtaPhiE(j2.pt(), j2.eta(), j2.phi(), sqrt(j2.pz()*j2.pz()+j2.perp2()));
  TLorentzVector tSum(ja.Px()+jb.Px(), ja.Py()+jb.Py(), 0., 0.);
  return sqrt((met.pt()*(ja.Pt()+jb.Pt()) - met.px()*tSum.Px()-met.py()*tSum.Py())/2.);
}

// apply btag efficiency  
bool CMSReco::BTagCSVM(fastjet::PseudoJet j, double dR) {
  bool btag = true;
  if(IsBJet(j, dR, 20.)) {
      btag = cms->BTagCSVM_b(ConvertTo4Vector(j));
  } else if(IsCJet(j, dR, 20.)) {
    btag = cms->BTagCSVM_c(ConvertTo4Vector(j));
  } else {
    btag = cms->BTagCSVM_udsg(ConvertTo4Vector(j));
  }	
  return btag;
}

// apply btag efficiency  
bool CMSReco::BTagHiggs(fastjet::PseudoJet j, double dR) {
  bool btag = true;
  if(IsHbbJet(j, dR)) {
    btag = cms->BTagHbb_Hbb(ConvertTo4Vector(j));
  } else if(IsZbbJet(j, dR)) {
    btag = cms->BTagHbb_Zbb(ConvertTo4Vector(j));
  } else if(IsTopJet(j, dR)) {
    btag = cms->BTagHbb_Top(ConvertTo4Vector(j));
  } else if(IsWcsJet(j, dR)) {
    btag = cms->BTagHbb_Wcs(ConvertTo4Vector(j));
  } else {
    btag = cms->BTagHbb_udcsg(ConvertTo4Vector(j));
  }	
  return btag;
}

void CMSReco::CleanEvent() {
  idxEleWP80.clear();
  EleWP80.clear();
  idxEleWP95.clear();
  EleWP95.clear();
  idxTightMu.clear();
  TightMu.clear();
  idxLooseMu.clear();
  LooseMu.clear();
  idxRecoTrack.clear();
  Track.clear();
  _PFElectrons.clear();
  _PFMuons.clear();
  _PFPhotons.clear();
  _PFChHadrons.clear();
  _PFNeuHadrons.clear();

}
