#include <string>
#include <iostream>
#include <TTree.h>
#include "FCCee/FCCeeRazor3D.hh"
#include <fastjet/tools/Pruner.hh>

FCCeeRazor3D::FCCeeRazor3D(TTree *tree) : FCCReco(tree) {
}

FCCeeRazor3D::~FCCeeRazor3D(){
}

void FCCeeRazor3D::SetSqrts(double sqrts) {
  _sqrts = sqrts;
}

// loop over events - real analysis
void FCCeeRazor3D::Loop(string outFileName) {

  if(fChain == 0) return;

  double MR, Mslepton, MissingMass, Mll;

  // Open Output file
  TFile *file = new TFile(outFileName.c_str(),"UPDATE");

  TTree* outTree = new TTree("RazorInclusive","RazorInclusive");
  outTree->Branch("MR", &MR, "MR/D");
  outTree->Branch("Mll", &Mll, "Mll/D");
  outTree->Branch("Mslepton", &Mslepton, "Mslepton/D");
  outTree->Branch("MissingMass", &MissingMass, "MissingMass/D");

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

    // select two highest-pT electrons
    // if(Electron<2) continue;
    // int i1 = 0;
    // int i2 = 0;
    // double Emax = 0.;
    // double MAX = 0.;
    // for(int i=0; i<Electron; i++) {
    //   if(ElectronE[i]>Emax) {
    // 	i1 = i;
    // 	Emax = ElectronE[i];
    //   }
    // }
    // for(int i=0; i<Electron; i++) {
    //   if(ElectronE[i]>Emax && i != i1) {
    // 	i2 = i;
    // 	Emax = ElectronE[i];
    //   }
    // }
      
    // 2a) compute new RSQ and MR
    int i1 =0;
    int i2 = 1;
    TLorentzVector j1 = TLorentzVector(MuonPx[i1], MuonPy[i1], MuonPz[i1], MuonE[i1]);
    TLorentzVector j2 = TLorentzVector(MuonPx[i2], MuonPy[i2], MuonPz[i2], MuonE[i2]);
    TLorentzVector Ebeam = TLorentzVector(0., 0., 0., _sqrts);
    // int i1 = -99;
    // int i2 = -99;
    // for(int i=0; i<GenTreeParticle; i++) {
    //   if(GenTreeParticlePdgId[i] == 13 ) i1 = i;
    //   if(GenTreeParticlePdgId[i] == -13) i2 = i;
    // }

    // if(i1 == -99 || i2 == -99) continur;
    
    // TLorentzVector j1 = TLorentzVector(float(GenTreeParticlePx[i1]), float(GenTreeParticlePy[i1]), float(GenTreeParticlePz[i1]),float(GenTreeParticleE[i1]));
    // TLorentzVector j2 = TLorentzVector(float(GenTreeParticlePx[i2]), float(GenTreeParticlePy[i2]), float(GenTreeParticlePz[i2]),float(GenTreeParticleE[i2]));

    MR = sqrt(2.*j1.E()*j2.E()+2.*j1.Vect()*j2.Vect());
    Mslepton = _sqrts/2.*MR/(j1.E()+j2.E());
    MissingMass = (Ebeam-j1-j2).M();
    Mll = (j1+j2).M();
    // write event in the tree
    outTree->Fill();

  }

  // full event TTree
  outTree->Write();
    file->Close();

}

