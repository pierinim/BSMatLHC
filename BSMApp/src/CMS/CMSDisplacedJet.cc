#include <string>
#include <iostream>
#include <TTree.h>
#include "CMS/CMSDisplacedJet.hh"

CMSDisplacedJet::CMSDisplacedJet(TTree *tree) : CMSReco(tree) {
}

CMSDisplacedJet::~CMSDisplacedJet(){
}

TTree* CMSDisplacedJet::GetTree() {
  return outTree;
}

// loop over events - real analysis
void CMSDisplacedJet::Loop(string outFileName) {

  if(fChain == 0) return;

  double fMiss1;
  double fMiss2;
  double fMiss3;
  double Pt;
  double Eta;
  double Phi;
  double E;
  int nTrk;
  int nRecoTrk;
  int evtNumber;

  // Open Output file
  TFile *file = new TFile(outFileName.c_str(),"UPDATE");

  outTree = new TTree("DisplacedJetInclusive","DisplacedJetInclusive");
  outTree->Branch("fMiss1", &fMiss1, "fMiss1/D");
  outTree->Branch("fMiss2", &fMiss2, "fMiss2/D");
  outTree->Branch("fMiss3", &fMiss3, "fMiss3/D");
  outTree->Branch("Pt", &Pt, "Pt/D");
  outTree->Branch("Eta", &Eta, "Eta/D");
  outTree->Branch("Phi", &Phi, "Phi/D");
  outTree->Branch("E", &E, "E/D");
  outTree->Branch("nTrk", &nTrk, "nTrk/I");
  outTree->Branch("nRecoTrk", &nRecoTrk, "nRecoTrk/I");

  // loop over entries
  Long64_t nbytes = 0, nb = 0;
  Long64_t nentries = fChain->GetEntries();
  std::cout << "Number of entries = " << nentries << std::endl;

  // set the by-event weight
  for (Long64_t jentry=0; jentry<nentries;jentry+=1) {

    if(verbose) cout << "new event" << endl;

    // clean physics-objects blocks
    CleanEvent();

    // get new event
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    if (jentry%1000 == 0) std::cout << ">>> Processing event # " << jentry << std::endl;
    evtNumber = jentry;

    // Build the event at generator level
    GenJet();

    //PFJet reco
    PFJetReco(40., 3.0);
    // Track Reco
    TrackReco();

    for(int i=0; i<PFJet.size(); i++) {
      int NmisHit1 = 0;
      int NmisHit2 = 0;
      int NmisHit3 = 0;
      int Ntot = 0;
      for(int j=0; j<idxRecoTrack.size(); j++) {
	// keep only tracks inside the jet
	if(Track[j].DeltaR(PFJet[i])>0.5) continue;
	Ntot++;
	// get the missing hits for the track
	int misHit = MissingPixelHits(idxRecoTrack[j]);
	if(misHit>= 1) NmisHit1++;
	if(misHit>= 2) NmisHit2++;
	if(misHit>= 3) NmisHit3++;
      }
      // ignore jets with no track, whatever they are
      if(Ntot == 0) continue;
      fMiss1 = double(NmisHit1)/Ntot;
      fMiss2 = double(NmisHit2)/Ntot;
      fMiss3 = double(NmisHit3)/Ntot;
      nRecoTrk = Ntot;
      nTrk = 0;
      for(int k=0; k<Particle; k++) {
	if(fabs(ParticleCharge[k])>0) nTrk++;
      }
      Pt  = PFJet[i].Pt();
      Eta = PFJet[i].Eta();
      Phi = PFJet[i].Phi();
      
      // write jet in the tree
      outTree->Fill();
    }
  }
  outTree->Write();
  file->Close();
}
