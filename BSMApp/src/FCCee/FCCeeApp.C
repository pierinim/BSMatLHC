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
#include "FCCee/FCCeeRazor3D.hh"

using namespace std;

/// Main function that runs the analysis algorithm on the
/// specified input files
int main(int argc, char* argv[]) {

  if ( argc < 2 ){
    cout << "To run FCCeeApp please specify the input file and the output file" << endl; 
    cout << "Example:        ./FCCeeApp myBSMGenfile.root output.root [OPTIONS]" << endl;
    cout << "OPTIONS:        " << endl;
    cout << "--verbose       Increase verbosity level for debug" << endl;
    cout << "--razor3D       Run Razor3D study" << endl;
    cout << "-sqrts          sqrts of collisions" << endl;
    return 1;
  }

  char inputFCC[150];
  strcpy(inputFCC,argv[1]);
  char outFileName[150];
  strcpy(outFileName,argv[2]);

  bool verbose  = false;
  bool writeOut = false;
  bool razor3D = false;
  float sqrts = 13000.;

  for (int i=3;i<argc;i++){
    if (strncmp(argv[i],"-sqrts=",7)==0)  {
      sscanf(argv[i],"-sqrts=%f",&sqrts);
    }
    if (strncmp(argv[i],"--verbose",9)==0)      verbose = true;
    if (strncmp(argv[i],"--razor3D",9)==0)      razor3D = true;
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
    if(razor3D) {
      FCCeeRazor3D razor3D(fccChain);
      if(verbose) razor3D.SetVerbose(true);
      razor3D.SetSqrts(double(sqrts));
      razor3D.Loop(outFileName);
    }
 }
 return 0;
}
