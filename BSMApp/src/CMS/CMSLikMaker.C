//-------------------------------------------------------
// Description:
// Authors:
//-------------------------------------------------------

// C++ includes
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <sstream>

// ROOT includes
#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TChain.h>

#include "CommonTools/CountingExperiment.hh"
#include "CMS/CMSRazorLikelihood.hh"

using namespace std;

/// Main function that runs the analysis algorithm on the
/// specified input files
int main(int argc, char* argv[]) {

  string InputFileName("none");
  for(int i=0; i< argc; i++) {
    if (string(argv[i]) == "-i") {
      if(i+1 < argc) InputFileName = argv[i+1];
    }
  }

  // read counting experiments from input file
  if(InputFileName != "none") {
    // open file
    ifstream myfile(InputFileName.c_str());
    if (myfile.is_open()) {
      string rootFileName;
      string analysisName;
      int n;
      double b, db;
      double mins, maxs;
      string line;
      string oldrootFileName("none");
      while(myfile.good()) {
	getline(myfile,line);
	if(line.find("#") == 0) continue;
	stringstream ss(line);
	ss >> rootFileName >> analysisName >> n >> b >> db >> mins >> maxs;
	CountingExperiment* cexp = new CountingExperiment(n, b, db, mins, maxs);
	if(oldrootFileName != rootFileName) {
	  cexp->CreatePosteriors(rootFileName, analysisName, "recreate");
	  oldrootFileName = rootFileName;
	} else {
	  cexp->CreatePosteriors(rootFileName, analysisName, "update");
	}
      }
    }
    myfile.close();
  }

  // Razor analysis
  CMSRazorLikelihood cmsRazorLikelihood("data/ExpectedObserved_RazorHad_Winter2012.root", "hEXP", "hOBS");
  cmsRazorLikelihood.CreatePosteriors("data/RazorLikelihood_RazorHad_Winter2012.root");
  return 0;
}
