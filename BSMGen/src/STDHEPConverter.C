// Generate a sample of SUSY events, starting from 
// a SUSY LH file and write the output in a ROOT file

#include <TFile.h>
#include <TTree.h>
#include <GenTree.hh>
#include <GenCandidateFiller.hh>
#include <STDHEP.hh>

#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]) {

  // Check that correct number of command-line arguments
  if (argc != 3) {
    cerr << " Unexpected number of command-line arguments. \n You are"
         << " expected to provide the name of the input STDHEP file and the output ROOT file. \n"
	 << " example: ./STDHEPConverter STDHEPConverter_LHC7TeV.stdhep.root STDHEPConverter_LHC7TeV.root \n"
         << " Program stopped! " << endl;
    return 1;
  }

  // Check that the provided input name corresponds to an existing file.
  ifstream is(argv[1]);  
  if (!is) {
    cerr << " Command-line file " << argv[1] << " was not found. \n"
         << " Program stopped! " << endl;
    return 1;
  }

  // Get The STDHEP tree
  TFile* inputFile = TFile::Open(argv[1]);
  TTree* inputTree = (TTree*) inputFile->Get("STDHEP");
  STDHEP* stdHepTree = new STDHEP(inputTree);
  /*
  stdHepTree->SetMinMuonPt(0.);
  stdHepTree->SetMinElectronPt(0.);
  stdHepTree->SetMinPhotonPt(0.);
  stdHepTree->SetMinTauPt(0.);
  stdHepTree->SetMinBJetPt(0.);
  stdHepTree->SetMaxParticleEta(10.);
  stdHepTree->SetMinParticlePt(0.);
  */
  
  // MET
  stdHepTree->SetMinParticlePt(3.0);
  stdHepTree->SetMaxParticleEta(3.1);
  // PHOTON
  stdHepTree->SetMinPhotonPt(15.);
  // TAUS
  stdHepTree->SetMinTauPt(15.);
  // LEPTONS
  stdHepTree->SetMinMuonPt(5.);
  stdHepTree->SetMinElectronPt(5.);
  // Bs
  stdHepTree->SetMinBJetPt(15.);
  

  // the output file 
  char name[256];
  sprintf(name,"%s_GenTree.root", argv[2]);
  TFile* treeOut = new TFile(name,"recreate");
  // the event TTree
  TTree* myTree = stdHepTree->Loop();
  myTree->Write();
  treeOut->Close();

  // Done.
  return 0;
}
