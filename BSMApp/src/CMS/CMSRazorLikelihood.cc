#include <string>
#include <iostream>
#include <TTree.h>
#include "CMS/CMSRazorLikelihood.hh"

CMSRazorLikelihood::CMSRazorLikelihood(TString inputFname, TString nHname, TString bHname) {
  fileIN = TFile::Open(inputFname);
  nH = (TH2D*) fileIN->Get(nHname)->Clone();
  bH = (TH2D*) fileIN->Get(bHname)->Clone();
  _statTools = new StatTools(-99);
}

CMSRazorLikelihood::~CMSRazorLikelihood(){
  fileIN->Close();
  delete _statTools;
}

void CMSRazorLikelihood::CreatePosteriors(TString outputFname) {

  int nx = nH->GetXaxis()->GetNbins();
  int ny = nH->GetYaxis()->GetNbins();
  for(int ix=1; ix<=nx; ix++) {
    for(int iy=1; iy<=ny; iy++) {
      char name[256];
      sprintf(name, "lik_%i_%i", ix-1, iy-1);
      TH1D* thisHisto = _statTools->LogNormPoissonConv(TString(name), nH->GetBinContent(ix, iy), bH->GetBinContent(ix, iy), bH->GetBinError(ix, iy));
      TString openMode = (ix == 1 && iy == 1 ? TString("recreate") : TString("update"));
      TFile* outFile = new TFile(outputFname, openMode);
      thisHisto->Write();
      outFile->Close();
      delete thisHisto;
    }
  }
}
