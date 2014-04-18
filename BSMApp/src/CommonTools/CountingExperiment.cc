#include <string>
#include <iostream>
#include <TTree.h>
#include "CommonTools/CountingExperiment.hh"

CountingExperiment::CountingExperiment(Int_t n, Double_t b, Double_t db, Double_t mins, Double_t maxs) {
  _n = n;
  _b = b;
  _db = db;
  _mins = mins;
  _maxs = maxs;
  _statTools = new StatTools(-99);
}

CountingExperiment::~CountingExperiment(){
  //  delete _statTools;
}

void CountingExperiment::CreatePosteriors(TString outputFname, TString name, TString openMode) {
  TH1D* thisHisto = _statTools->LogNormPoissonConv(name, _n, _b, _db, _mins, _maxs);
  TFile* outFile = new TFile(outputFname, openMode);
  thisHisto->Write();
  outFile->Close();
  delete thisHisto;
}
