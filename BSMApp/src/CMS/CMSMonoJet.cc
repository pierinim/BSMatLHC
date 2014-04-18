#include <string>
#include <iostream>
#include <TTree.h>
#include <TFile.h>
#include "CMS/CMSMonoJet.hh"

CMSMonoJet::CMSMonoJet(TTree *tree, string ModelName, double Lumi, string analysis) : CMSReco(tree) {
  _ModelName = ModelName;
  _statTools = new StatTools(-99);
  char name[256];
  sprintf(name, "data/%s.root", analysis.c_str());
  _fileLikelihood = TFile::Open(name);
  _Ps250 = _statTools->LogNormHistoConv((TH1D*) _fileLikelihood->Get((analysis+string("_MET250")).c_str()),0.30);
  _Ps300 = _statTools->LogNormHistoConv((TH1D*) _fileLikelihood->Get((analysis+string("_MET300")).c_str()),0.30);
  _Ps350 = _statTools->LogNormHistoConv((TH1D*) _fileLikelihood->Get((analysis+string("_MET350")).c_str()),0.30);
  _Ps400 = _statTools->LogNormHistoConv((TH1D*) _fileLikelihood->Get((analysis+string("_MET400")).c_str()),0.30);
  _Ps250MU = _statTools->LogNormHistoConv((TH1D*) _fileLikelihood->Get((analysis+string("_MET250MU")).c_str()),0.30);
  _Ps300MU = _statTools->LogNormHistoConv((TH1D*) _fileLikelihood->Get((analysis+string("_MET300MU")).c_str()),0.30);
  _Ps350MU = _statTools->LogNormHistoConv((TH1D*) _fileLikelihood->Get((analysis+string("_MET350MU")).c_str()),0.30);
  _Ps400MU = _statTools->LogNormHistoConv((TH1D*) _fileLikelihood->Get((analysis+string("_MET400MU")).c_str()),0.30);
  _Lumi = Lumi;
  verbose = false;
}

CMSMonoJet::~CMSMonoJet(){
  _fileLikelihood->Close();
  delete _statTools;
}

// loop over events - real analysis
void CMSMonoJet::Loop() {

  TH1D* muonPt = new TH1D("muonPt", "muonPt", 100, 0., 100.);

  if(fChain == 0) return;

  // number of events passing the selection
  int Ns_250 = 0;
  int Ns_300 = 0;
  int Ns_350 = 0;
  int Ns_400 = 0;
  
  int Ns_250_mu = 0;
  int Ns_300_mu = 0;
  int Ns_350_mu = 0;
  int Ns_400_mu = 0;
  
  // loop over entries
  Long64_t nbytes = 0, nb = 0;
  Long64_t nentries = fChain->GetEntries();
  std::cout << "Number of entries = " << nentries << std::endl;
  for (Long64_t jentry=0; jentry<nentries;jentry+=1) {
    if(verbose) cout << "new event" << endl;

    // clean physics-objects blocks
    CleanEvent();

    // get new event
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    if (jentry%1000 == 0) std::cout << ">>> Processing event # " << jentry << std::endl;

    // Build the event at generator level
    GenJet();
    GenMET();

    //JetMET reco: PF and Calo 
    PFJetReco(30., 2.4);
    PFMETReco();    

    vector<TLorentzVector> Jet = PFJet;
    //At most two jets 
    if(Jet.size()>2) continue;
    // at least one jet
    if(Jet.size()<1) continue;
    // Jet pT cut
    if(Jet[0].Pt()<110.) continue;
   
    // baseline MET cut
    TLorentzVector MET = PFMET_nomuon;
    if(MET.Pt()<250.) continue;

    
    //DelphaPhi(j,j)
    if(Jet.size() ==2)
      if(Jet[0].DeltaPhi(Jet[1])>=2.5) continue;

    // Electron VETO
    EleReco();
    int iEle = 0;
    for(int i=0; i< EleWP80.size(); i++) {
      if(EleWP80[i].Pt()>10.) iEle++;
    }
    if(iEle>0) continue;

    // cleanup inefficiency
    if(!_statTools->HitOrMiss(0.975)) continue;

    // Muon VETO
    MuReco();
    int iMu = 0;
    int iMuLowPt = 0;
    for(int i=0; i< TightMu.size(); i++) {
      if(TightMu[i].Pt()>10.) iMu++;
      if(TightMu[i].Pt()<=10.) iMuLowPt++;
      muonPt->Fill(TightMu[i].Pt());
    }
    if(iMu>0) continue;

    // iso-track veto (for taus)
    bool isoTrack = false;
    for(int i=0; i<Particle; i++) {
      if(sqrt(ParticlePx[i]*ParticlePx[i]+ParticlePy[i]*ParticlePy[i])<10.) continue;
      double iso = 0;
      TLorentzVector p(ParticlePx[i], ParticlePy[i], ParticlePz[i], ParticleE[i]);
      if(RelGenIso(p,0.3,true)<0.10) {
	isoTrack = true;
	i = Particle;
      }
    }

    if(isoTrack) continue;
    if(iMuLowPt>0) { 
      Ns_250_mu++;
      if(MET.Pt()>300.) Ns_300_mu++;
      if(MET.Pt()>350.) Ns_350_mu++;
      if(MET.Pt()>400.) Ns_400_mu++;
    } else {
      Ns_250++;
      if(MET.Pt()>300.) Ns_300++;
      if(MET.Pt()>350.) Ns_350++;
      if(MET.Pt()>400.) Ns_400++;
    }    
  }

  // xsec-to-yield scale factor
  double AccLumi250 = double(Ns_250)/nentries*_Lumi;
  double AccLumi300 = double(Ns_300)/nentries*_Lumi;
  double AccLumi350 = double(Ns_350)/nentries*_Lumi;
  double AccLumi400 = double(Ns_400)/nentries*_Lumi;
  double AccLumi250MU = double(Ns_250_mu)/nentries*_Lumi;
  double AccLumi300MU = double(Ns_300_mu)/nentries*_Lumi;
  double AccLumi350MU = double(Ns_350_mu)/nentries*_Lumi;
  double AccLumi400MU = double(Ns_400_mu)/nentries*_Lumi;

  TH1D* XSEC250 = new TH1D("XSEC250", "XSEC250", 100., 0., 100.);
  TH1D* XSEC300 = new TH1D("XSEC300", "XSEC300", 100., 0., 100.);
  TH1D* XSEC350 = new TH1D("XSEC350", "XSEC350", 100., 0., 100.);
  TH1D* XSEC400 = new TH1D("XSEC400", "XSEC400", 100., 0., 100.);

  for(int i=1; i<101; i++) {
    double xsec = i-0.5;
    cout << xsec*4900.*AccLumi250 << endl;
    XSEC250->SetBinContent(i, _Ps250->GetBinContent(_Ps250->FindBin(xsec*AccLumi250))*_Ps250MU->GetBinContent(_Ps250MU->FindBin(xsec*AccLumi250MU)));
    XSEC300->SetBinContent(i, _Ps250->GetBinContent(_Ps300->FindBin(xsec*AccLumi300))*_Ps250MU->GetBinContent(_Ps300MU->FindBin(xsec*AccLumi300MU)));
    XSEC350->SetBinContent(i, _Ps250->GetBinContent(_Ps350->FindBin(xsec*AccLumi350))*_Ps250MU->GetBinContent(_Ps350MU->FindBin(xsec*AccLumi350MU)));
    XSEC400->SetBinContent(i, _Ps250->GetBinContent(_Ps400->FindBin(xsec*AccLumi400))*_Ps250MU->GetBinContent(_Ps400MU->FindBin(xsec*AccLumi400MU)));
  }

  XSEC250->Scale(1./XSEC250->Integral());
  XSEC300->Scale(1./XSEC250->Integral());
  XSEC350->Scale(1./XSEC250->Integral());
  XSEC400->Scale(1./XSEC250->Integral());

  // find the excluded xsec at 95% CL
  double xsec95CL_250 = _statTools->FindUL(XSEC250, 0.95, 1.);
  double xsec95CL_300 = _statTools->FindUL(XSEC300, 0.95, 1.);
  double xsec95CL_350 = _statTools->FindUL(XSEC350, 0.95, 1.);
  double xsec95CL_400 = _statTools->FindUL(XSEC400, 0.95, 1.);

  cout << "Model = "<< _ModelName << endl;
  cout << "Mu_monojet Xsec@95% Prob. [pb-1] for MET>250 = " <<  xsec95CL_250 << endl;
  cout << "Mu_monojet Xsec@95% Prob. [pb-1] for MET>300 = " <<  xsec95CL_300 << endl;
  cout << "Mu_monojet Xsec@95% Prob. [pb-1] for MET>350 = " <<  xsec95CL_350 << endl;
  cout << "Mu_monojet Xsec@95% Prob. [pb-1] for MET>400 = " <<  xsec95CL_400 << endl;
  double bestLimit = xsec95CL_250;
  if(xsec95CL_300 < bestLimit) bestLimit = xsec95CL_300;
  if(xsec95CL_350 < bestLimit) bestLimit = xsec95CL_350;
  if(xsec95CL_400 < bestLimit) bestLimit = xsec95CL_400;
  cout << "Mu_monojet best Xsec@95% Prob. [pb-1]  = " << bestLimit  << endl;

  TFile* pippo =  new TFile("pippo.root", "recreate");
  muonPt->Write();
  XSEC250->Write();
  XSEC300->Write();
  XSEC350->Write();
  XSEC400->Write();
  pippo->Close();

}

