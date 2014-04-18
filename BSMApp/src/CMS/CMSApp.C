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

// Supported Analyses
#include "CMS/CMSRazor.hh"
//#include "CMS/CMSMonoJet.hh"
//#include "CMS/CMSSSDilepBtag.hh"
//#include "CMS/CMSDisplacedJet.hh"
// 
#include "CMS/CMSDarkMatter.hh"
#include "CMS/CMSSubstructure.hh"

using namespace std;

/// Main function that runs the analysis algorithm on the
/// specified input files
int main(int argc, char* argv[]) {

  if ( argc < 2 ){
    cout << "To run CMSApp please specify the input file" << endl; 
    cout << "Example:        ./CMSApp myBSMGenfile.root" << endl;
    cout << "OPTIONS:        " << endl;
    cout << "--verbose       Increase verbosity level for debug" << endl;
    cout << "--razor         Run Razor Analysis" << endl;
    cout << "--monojet       Run MonoJet Analysis" << endl;
    cout << "--darkmatter    Run Dark Matter future study" << endl;
    cout << "--substructure  Run Substructure tagger analysis on jets" << endl;
    cout << "--ssdilepbtag   Run the SS dilepton btag Analysis" << endl;
    cout << "--displaced     Run DSisplaced Jet Analysis" << endl;
    cout << "-sqrts          sqrts of collisions" << endl;
    cout << "-Output         Name of the output file (none created if not specified)" << endl;
    return 1;
  }

  char inputCMS[150];
  strcpy(inputCMS,argv[1]);

  char outFileName[150]= "none";

  bool verbose  = false;
  bool writeOut = false;
  bool razor = false;
  bool monojet = false;
  bool darkmatter = false;
  bool substructure = false;
  bool ssdilepbtag = false;
  bool displaced = false;
  double sqrts = 13000.;

  for (int i=1;i<argc;i++){
    if (strncmp(argv[i],"-Output",7)==0) {
      sscanf(argv[i],"-Output=%s",outFileName);
      writeOut = true;
    }
    if (strncmp(argv[i],"-sqrts=",7)==0)  {
      sscanf(argv[i],"-sqrts=%d",&sqrts);
    }
    if (strncmp(argv[i],"--verbose",9)==0)      verbose = true;
    if (strncmp(argv[i],"--monojet",9)==0)      monojet = true;
    if (strncmp(argv[i],"--substructure",14)==0) substructure = true;
    if (strncmp(argv[i],"--darkmatter",12)==0)  darkmatter = true;
    if (strncmp(argv[i],"--displaced",11)==0)   displaced = true;
    if (strncmp(argv[i],"--ssdilepbtag",13)==0) ssdilepbtag = true;
    if (strncmp(argv[i],"--razor",7)==0)        razor = true;
  }
  
  if(strncmp(inputCMS,"none",4)!=0) {
    
    // RECO Tree
    TChain *cmsChain;
    cmsChain = new TChain("GenEvent");
    cmsChain->Add(inputCMS);
    
    // Open Output file
    if(writeOut) {
      TFile *file = new TFile(outFileName,"RECREATE");
      file->Close();
    }

    // SUS-12-005: Razor analysis
    if(razor) {
      //      CMSRazor cmsRazor(cmsChain, 4600., "CMSRazor_HadLik_SUS_12_005");
      CMSRazor cmsRazor(cmsChain, 0., "");
      if(!writeOut) {
	cout << "please specify output file" << endl;
	return 0;
      }
      if(verbose) cmsRazor.SetVerbose(true);
      cmsRazor.SetSqrts(sqrts);
      cmsRazor.Loop(outFileName);
    }

    /*    
    // EXO-11-059: MonoJet analysis
    if(monojet) {
      CMSMonoJet cmsMonoJet(cmsChain, inputCMS, 4980., "CMSmonojet_EXO_11_059");
      if(verbose) cmsMonoJet.SetVerbose(true);
      cmsMonoJet.Loop();
    }

    // SUS-11-020: SUSY Dilep SS + Btag
    if(ssdilepbtag) {
      CMSSSDilepBtag cmsSSDilepBtag(cmsChain, inputCMS, 4980., "CMSSSDilepBTag_SUS_11_020");
      if(verbose) cmsSSDilepBtag.SetVerbose(true);
      cmsSSDilepBtag.Loop();
    }

    // Displaced search
    if(displaced) {
      CMSDisplacedJet cmsDisplacedJet(cmsChain);
      if(!writeOut) {
	cout << "please specify output file" << endl;
	return 0;
      }
      cmsDisplacedJet.Loop(outFileName);
    }
*/

    // Dark Matter future studies
    if(darkmatter) {
      CMSDarkMatter cmsDarkMatter(cmsChain, inputCMS, 4980., "CMSmonojet_EXO_11_059");
      if(verbose) cmsDarkMatter.SetVerbose(true);
      cmsDarkMatter.Loop(outFileName);
    }

    // Dark Matter future studies
    if(substructure) {
      CMSSubstructure cmsSubstructure(cmsChain, inputCMS, 4980., "CMSsubstructure");
      if(verbose) cmsSubstructure.SetVerbose(true);
      cmsSubstructure.Loop(outFileName);
    }

  }
  
  return 0;
}
