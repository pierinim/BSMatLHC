#include <string>
#include <iostream>
#include <TTree.h>
#include "CMSZprime.hh"

CMSZprime::CMSZprime(TTree *tree, bool vecbosFlag) : CMSReco(tree, vecbosFlag) {
  writeLL = false;
}

CMSZprime::~CMSZprime(){
}


bool CMSZprime::isCMSMuon(int iMu){
  bool ret=false;
  // find the closest track
  double dRMin = 999999999.;
  int iTk = -99;
  for(int i=0; i<momentumRecoTrack.size(); i++) {
    if(momentumRecoMuon[iMu].DeltaR(momentumRecoTrack[i])<dRMin) {
      iTk = i;
      dRMin = momentumRecoMuon[iMu].DeltaR(momentumRecoTrack[i]);
    }
  }
  //pT
  if(momentumRecoMuon[iMu].Pt()>20.) {
    // eta
    if(fabs(momentumRecoMuon[iMu].Eta())<2.4) {
      // compute calo iso
      double caloIso = 0.;
      for(int i=0; i< CaloTower_; i++) {
	if(CaloTower_ET[i]<1.5) continue;
	TLorentzVector myCT;
	myCT.SetPtEtaPhiM(CaloTower_ET[i]-1.5, CaloTower_Eta[i], CaloTower_Phi[i], 0.);
	if(myCT.DeltaR(momentumRecoMuon[iMu]) < 0.3) caloIso += myCT.Pt();
      }
      // compute Trk iso at withn charged Gen particles
      double trkIsoGEN = _genTree->ChargeParticlesIsolation(momentumRecoMuon[iMu], 0.3, 2.5);
      // cut on combined isolation
      if( (trkIsoGEN+Muon_SumEt[iMu])/momentumRecoMuon[iMu].Pt() < 0.10) {
	ret=true;
      }
    }
  }

  return ret;

}

// loop over events - real analysis
void CMSZprime::Loop(string outFileName) {

  if(fChain == 0) return;

  //Eff tree
  double weight=1;
  double Npassed_In=0;
  double Npassed_TwoMuon=0;
  double Npassed_Charge=0;
  double Npassed_MMuMu120=0;
  double Npassed_MMuMu200=0;

  // loop over entries
  Long64_t nbytes = 0, nb = 0;
  Long64_t nentries = fChain->GetEntries();
  std::cout << "Number of entries = " << nentries << std::endl;
  for (Long64_t jentry=0; jentry<nentries;jentry+=1) {

    // load the correspnding GenTree entry
    _genTree->GetEntry(jentry);

    Npassed_In+=weight;

    // clean physics-objects blocks
    CleanBlocks();
    
    // get new event
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    if (jentry%1000 == 0) std::cout << ">>> Processing event # " << jentry << std::endl;
    
    // CMS reco
    if(useVecbos) LoadVecbosParticles();      
    else LoadDelphesParticles();

    //Two Muons
    vector <TLorentzVector> Muons;
    vector <Int_t> MuCharge;
    for(int iMu=0; iMu< momentumRecoMuon.size(); iMu++){
      if(isCMSMuon(iMu)){
	Muons.push_back(momentumRecoMuon[iMu]);
	MuCharge.push_back(Muon_Charge[iMu]);
      }
      
    }

    if(Muons.size()!=2)continue;
    Npassed_TwoMuon+=weight;

    if(MuCharge[0]==MuCharge[1])continue;
    Npassed_Charge+=weight;

    //DiLepton Mass
    TLorentzVector Z= Muons[0]+Muons[1];
    if(Z.M() < 120.0)continue;
    Npassed_MMuMu120+=weight;
    if(Z.M() > 200.0)Npassed_MMuMu200+=weight;

  }
 
  // efficiency tree
  TTree* nevTree = new TTree("effTree","effTree");
  
  nevTree->Branch("Npassed_In", &Npassed_In, "Npassed_In/D");
  nevTree->Branch("Npassed_TwoMuon", &Npassed_TwoMuon, "Npassed_TwoMuon/D");
  nevTree->Branch("Npassed_Charge", &Npassed_Charge, "Npassed_Charge/D");
  nevTree->Branch("Npassed_MMuMu120", &Npassed_MMuMu120, "Npassed_MMuMu120/D");
  nevTree->Branch("Npassed_MMuMu200", &Npassed_MMuMu200, "Npassed_MMuMu200/D");

  nevTree->Fill();
  
  TFile *file = new TFile(outFileName.c_str(),"UPDATE");
  nevTree->Write();
  file->Close();

}
