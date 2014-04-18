#include <string>
#include <iostream>
#include <TTree.h>
#include <TFile.h>
#include "CMSSSDilep.hh"

CMSSSDilep::CMSSSDilep(TTree *tree, string ModelName, double Lumi, string analysis) : CMSReco(tree) {
  _ModelName = ModelName;
  char name[256];
  sprintf(name, "data/%s.root", analysis.c_str());
  _fileLikelihood = TFile::Open(name);
  _Ps = (TH1D*) _fileLikelihood->Get(analysis.c_str());
  _Lumi = Lumi;
  _statTools = new StatTools(-99);
  verbose = false;
}

CMSSSDilep::~CMSSSDilep(){
  _fileLikelihood->Close();
  delete _statTools;
}

// loop over events - real analysis
void CMSSSDilep::Loop() {

  if(fChain == 0) return;

  // number of events passing the selection
  int Ns = 0;
  
  // loop over entries
  Long64_t nbytes = 0, nb = 0;
  Long64_t nentries = fChain->GetEntries();
  std::cout << "Number of entries = " << nentries << std::endl;
  for (Long64_t jentry=0; jentry<nentries;jentry+=1) {
    if(verbose) cout << "new event" << endl;

    // clean physics-objects blocks
    CleanEvent();

    // get new event
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    if (jentry%1000 == 0) std::cout << ">>> Processing event # " << jentry << std::endl;

    // Build the event at generator level
    GenJet();
    GenMET();

    //PFJetMET(110., 2.4);    
    // vector<TLorentzVector> Jet = PFJet;
    // TLorentzVector MET = PFMET_nomuon;
   
    // MET>350
    if(MET.Pt()<350.) continue;
    
    //At most two jets 
    if(Jet.size()>2) continue;
    if(Jet.size()<1) continue;
    if(Jet[1].Pt()<110.) continue;
    
    //DelphaPhi(j,j)
    if(Jet[0].DeltaPhi(Jet[1])>=2.) continue;


    // iso-track veto (for taus)
    bool isoTrack = false;
    for(int i=0; i<Particle; i++) {
      if(sqrt(ParticlePx[i]*ParticlePx[i]+ParticlePy[i]*ParticlePy[i])<10.) continue;
      double iso = 0;
      TLorentzVector p(ParticlePx[i], ParticlePy[i], ParticlePz[i], ParticleE[i]);
      for(int j=0; j<Particle; j++) {
	if(i == j) continue; 
	if(sqrt(ParticlePx[j]*ParticlePx[j]+ParticlePy[j]*ParticlePy[j])<1.) continue;
	TLorentzVector t(ParticlePx[j], ParticlePy[j], ParticlePz[j], ParticleE[j]);
	if(p.DeltaR(t)>0.02 && p.DeltaR(t)<0.3) iso += t.Pt();
      }
      if(iso/p.Pt()<0.10) {
	isoTrack = true;
	i = Particle;
      }
    }
    if(isoTrack) continue;

    // cleanup inefficiency
    if(!_statTools->HitOrMiss(0.975)) continue;
    
    Ns++;
  }    
    
  // xsec-to-yield scale factor
  double AccLumi = double(Ns)/nentries*_Lumi;
  // find the excluded xsec at 95% CL
  double xsec95CL = _statTools->FindUL(_Ps, 0.95, AccLumi);
  cout << "Model = "<< _ModelName << endl;
  cout << "Monojet Eff = " << double(Ns)/nentries << endl;
  cout << "Monojet Xsec@95% Prob. [pb-1] = " <<  xsec95CL/AccLumi << endl;

}

