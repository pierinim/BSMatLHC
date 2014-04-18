#define STDHEP_cxx
#include <STDHEP.hh>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <GenTree.hh>
#include <GenCandidateFiller.hh>

void STDHEP::SetMinMuonPt(double value) {
  _minMuonPt = value;
}

void STDHEP::SetMinElectronPt(double value) {
  _minElectronPt = value;
}

void STDHEP::SetMinPhotonPt(double value) {
  _minPhotonPt = value;
}

void STDHEP::SetMinParticlePt(double value) {
  _minParticlePt = value;
}

void STDHEP::SetMaxParticleEta(double value) {
  _maxParticleEta = value;
}

void STDHEP::SetMinTauPt(double value) {
  _minTauPt = value;
}

void STDHEP::SetMinBJetPt(double value) {
  _minBJetPt = value;
}

TTree* STDHEP::Loop(){
  //prepare the output tree
  GenTree* myTree = new GenTree("GenEvent","GenEvent");
  GenCandidateFiller* muonFiller = new GenCandidateFiller(myTree,"Muon");
  GenCandidateFiller* electronFiller = new GenCandidateFiller(myTree,"Electron");
  GenCandidateFiller* tauFiller = new GenCandidateFiller(myTree,"Tau");
  GenCandidateFiller* bFiller = new GenCandidateFiller(myTree,"b");
  GenCandidateFiller* photonFiller = new GenCandidateFiller(myTree,"Photon");
  GenCandidateFiller* neutrinoFiller = new GenCandidateFiller(myTree,"Neutrino");
  GenCandidateFiller* susyFiller = new GenCandidateFiller(myTree,"SUSY");
  GenCandidateFiller* particleFiller = new GenCandidateFiller(myTree,"Particle");
  
  // loop over the input tree
  if (fChain == 0) return new TTree();
  Long64_t nentries = fChain->GetEntriesFast();
  
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    // if (Cut(ientry) < 0) continue;
    
    muonFiller->NewEvent();
    electronFiller->NewEvent();
    tauFiller->NewEvent();
    bFiller->NewEvent();
    photonFiller->NewEvent();
    neutrinoFiller->NewEvent();
    susyFiller->NewEvent();
    particleFiller->NewEvent();

    for(int i=0; i<GenParticle_; i++) {
      // only stable particles
      if(GenParticle_Status[i] != 1) continue;
      TLorentzVector* p = new TLorentzVector(GenParticle_Px[i], GenParticle_Py[i], GenParticle_Pz[i], GenParticle_E[i]);
      TVector3* vtx = new TVector3(GenParticle_X[i], GenParticle_Y[i], GenParticle_Z[i]);
      // check if the particle has to be considered, and in case fill the tree
      if(GenParticle_Status[i] == 1) { // stable only
	if(p->Pt() > _minMuonPt) 
	  muonFiller->FillEventSTDHEP(p,vtx,p->M(),GenParticle_PID[i],0.,GenParticle_M1[i],GenParticle_M2[i],true);
	if(p->Pt() > _minElectronPt) 
	  electronFiller->FillEventSTDHEP(p,vtx,p->M(),GenParticle_PID[i],0.,GenParticle_M1[i],GenParticle_M2[i],true);
	if(p->Pt() > _minPhotonPt) 
	  photonFiller->FillEventSTDHEP(p,vtx,p->M(),GenParticle_PID[i],0.,GenParticle_M1[i],GenParticle_M2[i],true);
	if(p->Pt() > _minParticlePt && fabs(p->Eta()) < _maxParticleEta) 
	  particleFiller->FillEventSTDHEP(p,vtx,p->M(),GenParticle_PID[i],0.,GenParticle_M1[i],GenParticle_M2[i],true);
	// invisible
	neutrinoFiller->FillEventSTDHEP(p,vtx,p->M(),GenParticle_PID[i],0.,GenParticle_M1[i],GenParticle_M2[i],true);     
	susyFiller->FillEventSTDHEP(p,vtx,p->M(),GenParticle_PID[i],0.,GenParticle_M1[i],GenParticle_M2[i],true);

      } else { // taus and b's decay 
	if(p->Pt() > _minTauPt) tauFiller->FillEventSTDHEP(p,vtx,p->M(),GenParticle_PID[i],0.,GenParticle_M1[i],GenParticle_M2[i],true);
	if(p->Pt() > _minBJetPt) bFiller->FillEventSTDHEP(p,vtx,p->M(),GenParticle_PID[i],0.,GenParticle_M1[i],GenParticle_M2[i],true);
      }
      delete p, vtx;
    }
    // Fill the tree
    muonFiller->FillTree();
    electronFiller->FillTree();
    tauFiller->FillTree();
    bFiller->FillTree();
    photonFiller->FillTree();
    neutrinoFiller->FillTree();
    susyFiller->FillTree();
    particleFiller->FillTree();
    // write data in TTree
    myTree->dumpData();
    
    // Clear the event from memory
    muonFiller->ClearEvent();
    electronFiller->ClearEvent();
    tauFiller->ClearEvent();
    bFiller->ClearEvent();
    photonFiller->ClearEvent();
    neutrinoFiller->ClearEvent();
    susyFiller->ClearEvent();
    particleFiller->ClearEvent();    
    // End of event loop.    
  }
  TTree* treeOut = myTree->getTree();
  return treeOut;
}
