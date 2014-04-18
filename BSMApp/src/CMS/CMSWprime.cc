#include <string>
#include <iostream>
#include <TTree.h>
#include "CMSWprime.hh"

CMSWprime::CMSWprime(TTree *tree, bool vecbosFlag) : CMSReco(tree, vecbosFlag) {
  writeLL = false;
}

CMSWprime::~CMSWprime(){
}


bool CMSWprime::isCMSMuon(int iMu){
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
  if(momentumRecoMuon[iMu].Pt()>25.) {
    // eta
    if(fabs(momentumRecoMuon[iMu].Eta())<2.1) {
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
      if( (trkIsoGEN+Muon_SumEt[iMu])/momentumRecoMuon[iMu].Pt() < 0.15) {
	ret=true;
      }
    }
  }

  return ret;

}

// loop over events - real analysis
void CMSWprime::Loop(string outFileName) {

  if(fChain == 0) return;

  //Eff tree
  double weight=1;
  double Npassed_In=0;
  double Npassed_Muon=0;
  double Npassed_MEtPtRatio=0;
  double Npassed_deltaPhi=0;
  double Npassed_MT390=0;
  double Npassed_MT450=0;
  double Npassed_MT470=0;
  double Npassed_MT500=0;
  double Npassed_MT530=0;
  double Npassed_MT590=0;
  double Npassed_MT610=0;
  double Npassed_MT630=0;
  double Npassed_MT680=0;
  double Npassed_MT690=0;
  
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

    for(int iMu=0; iMu< momentumRecoMuon.size(); iMu++){
      if(isCMSMuon(iMu))Muons.push_back(momentumRecoMuon[iMu]);
    }

    if(Muons.size()!=1)continue;
    Npassed_Muon+=weight;

    //MET-MuonPt Ratio
    if((Muons[0].Pt()/Met.Et()) > 1.5 || (Muons[0].Pt()/Met.Et()) < 0.4)continue;
    Npassed_MEtPtRatio+=weight;

    //Met-Muon Angle
    double deltaPhi=Met.DeltaPhi(Muons[0]);
    if(deltaPhi <= 2.5)continue;
    Npassed_deltaPhi+=weight;

    //MT cut
    double MT=sqrt(2.0*Muons[0].Pt()*Met.Et()*(cos(1-deltaPhi)));
    if(MT < 390.0)continue;
    Npassed_MT390+=weight;
    if(MT > 450.0)Npassed_MT450+=weight;
    if(MT > 470.0)Npassed_MT470+=weight;
    if(MT > 500.0)Npassed_MT500+=weight;
    if(MT > 530.0)Npassed_MT530+=weight;
    if(MT > 590.0)Npassed_MT590+=weight;
    if(MT > 610.0)Npassed_MT610+=weight;
    if(MT > 630.0)Npassed_MT630+=weight;
    if(MT > 680.0)Npassed_MT680+=weight;
    if(MT > 690.0)Npassed_MT690+=weight;
  }
 
  // efficiency tree
  TTree* nevTree = new TTree("effTree","effTree");
  
  nevTree->Branch("Npassed_In", &Npassed_In, "Npassed_In/D");
  nevTree->Branch("Npassed_Muon", &Npassed_Muon, "Npassed_Muon/D");
  nevTree->Branch("Npassed_MEtPtRatio", &Npassed_MEtPtRatio, "Npassed_MEtPtRatio/D");
  nevTree->Branch("Npassed_deltaPhi", &Npassed_deltaPhi, "Npassed_deltaPhi/D");
  nevTree->Branch("Npassed_MT390", &Npassed_MT390, "Npassed_MT390/D");
  nevTree->Branch("Npassed_MT450", &Npassed_MT450, "Npassed_MT450/D");
  nevTree->Branch("Npassed_MT470", &Npassed_MT390, "Npassed_MT470/D");
  nevTree->Branch("Npassed_MT500", &Npassed_MT500, "Npassed_MT500/D");
  nevTree->Branch("Npassed_MT530", &Npassed_MT530, "Npassed_MT530/D");
  nevTree->Branch("Npassed_MT590", &Npassed_MT590, "Npassed_MT590/D");
  nevTree->Branch("Npassed_MT610", &Npassed_MT610, "Npassed_MT610/D");
  nevTree->Branch("Npassed_MT630", &Npassed_MT630, "Npassed_MT630/D");
  nevTree->Branch("Npassed_MT680", &Npassed_MT680, "Npassed_MT680/D");
  nevTree->Branch("Npassed_MT690", &Npassed_MT690, "Npassed_MT690/D");

  nevTree->Fill();
  
  TFile *file = new TFile(outFileName.c_str(),"UPDATE");
  nevTree->Write();
  file->Close();

}
