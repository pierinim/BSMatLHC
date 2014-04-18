//-------------------------------------------------------
// Description:
// Authors:
//-------------------------------------------------------

// C++ includes
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>

// ROOT includes
#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TChain.h>

#include "CommonTools/DetectorReco.hh"
#include "FCC/FCCExoVV.hh"
#include "FCC/FCCExoJJ.hh"

using namespace std;

/// Main function that runs the analysis algorithm on the
/// specified input files
int main(int argc, char* argv[]) {

  if ( argc < 2 ){
    cout << "To run FCCApp please specify the input file and the output file" << endl; 
    cout << "Example:        ./FCCApp myBSMGenfile.root output.root [OPTIONS]" << endl;
    cout << "OPTIONS:        " << endl;
    cout << "--verbose       Increase verbosity level for debug" << endl;
    cout << "--exovv         Run EXO X->VV Analysis with substructure" << endl;
    cout << "--exojj         Run EXO X->JJ Analysis with substructure (bjg study of X->VV)" << endl;
    return 1;
  }

  char inputFCC[150];
  strcpy(inputFCC,argv[1]);
  char outFileName[150];
  strcpy(outFileName,argv[2]);

  bool verbose  = false;
  bool writeOut = false;
  bool exovv = false;
  bool exojj = false;

  for (int i=3;i<argc;i++){
    if (strncmp(argv[i],"--verbose",9)==0)      verbose = true;
    if (strncmp(argv[i],"--exovv",7)==0)        exovv = true;
    if (strncmp(argv[i],"--exojj",7)==0)        exojj = true;
  }

 if(strncmp(inputFCC,"none",4)!=0) {
   
    // RECO Tree
    TChain *fccChain;
    fccChain = new TChain("GenEvent");
    fccChain->Add(inputFCC);

    // Open Output file
    if(writeOut) {
      TFile *file = new TFile(outFileName,"RECREATE");
      file->Close();
    }
   
    // EXO X->VV analysis with substructure
    if(exovv) {
      FCCExoVV exovv(fccChain);
      if(verbose) exovv.SetVerbose(true);
      exovv.Loop(outFileName);
    }
    // EXO X->JJ analysis with substructure (bkg study to X -> VV)
    if(exojj) {
      FCCExoJJ exojj(fccChain);
      if(verbose) exojj.SetVerbose(true);
      exojj.Loop(outFileName);
    }
 }
 return 0;
}
