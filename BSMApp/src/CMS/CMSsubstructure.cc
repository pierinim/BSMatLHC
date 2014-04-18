#include <string>
#include <iostream>
#include <TTree.h>
#include <TFile.h>
#include "CMS/CMSHemisphere.hh"
#include "CMS/CMSSubstructure.hh"
#include "CommonTools/JetSubstructure.hh"
#include <fastjet/tools/Pruner.hh>


CMSSubstructure::CMSSubstructure(TTree *tree, string ModelName, double Lumi, string analysis) : CMSReco(tree) {
  _ModelName = ModelName;
  _Lumi = Lumi;
  verbose = false;
}

CMSSubstructure::~CMSSubstructure(){
}

// loop over events - real analysis
void CMSSubstructure::Loop(string outFileName) {

  TFile* DMfile = new TFile(outFileName.c_str(),"RECREATE");

  // tree with run info (e.g. number of events)
  TTree* EvtInfo = new TTree("EvtInfo", "EvtInfo");

  // tree with event-by-event info MONOJET
  double JETPT, JETMASS;
  int Htag, tTag, bTag, Vtag;
  TTree* jetTree = new TTree("Monojet","Monojet");
  jetTree->Branch("JETPT", &JETPT, "JETPT/D");
  jetTree->Branch("JETMASS", &JETMASS, "JETMASS/D");
  jetTree->Branch("Htag", &Htag, "Htag/I");
  jetTree->Branch("Vtag", &Vtag, "Vtag/I");
  jetTree->Branch("tTag", &tTag, "tTag/I");
  jetTree->Branch("bTag", &bTag, "bTag/I");

  if(fChain == 0) return;

  // loop over entries
  Long64_t nbytes = 0, nb = 0;
  Long64_t nentries = fChain->GetEntries();
  std::cout << "Number of entries = " << nentries << std::endl;
  for (Long64_t jentry=0; jentry<nentries;jentry+=1) {

    // clean physics-objects blocks
    CleanEvent();

    // get new event
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    if (jentry%1000 == 0 || verbose) std::cout << ">>> Processing event # " << jentry << std::endl;

    bool leptonicDecay = false;
    for(int i=0; i< GenTreeParticle; i++) {
      if(GenTreeParticleM1PdgId[i] == 23 ||
	 GenTreeParticleM1PdgId[i] == 24 || 
	 GenTreeParticleM1PdgId[i]== -24) {
	if(abs(GenTreeParticlePdgId[i])>8) leptonicDecay = true;
      }
    }

    // reject events with leptonic decays 
    if(leptonicDecay) continue;

    // find V
    int iV1 = FindVindex(-99);
    int iV2 = FindVindex(iV1);
    if(iV1 == -99 || iV2 == -99) {
      // it was not a V
      iV1 = FindHindex(-99);
      iV2 = FindHindex(iV1);
      if(iV1 == -99 || iV2 == -99) {
	// it was not a H
	iV1 = FindTindex(-99);
	iV2 = FindTindex(iV1);
      }
    }
    if(iV1 == -99 || iV2 == -99) continue;

    TLorentzVector V1(GenTreeParticlePx[iV1], GenTreeParticlePy[iV1], GenTreeParticlePz[iV1], GenTreeParticleE[iV1]);
    TLorentzVector V2(GenTreeParticlePx[iV2], GenTreeParticlePy[iV2], GenTreeParticlePz[iV2], GenTreeParticleE[iV2]);
    if(V2.Pt()>V1.Pt()) V1 = V2;


    // Build the event at generator level
    PFReco();
    vector<fastjet::PseudoJet> empty;
    vector<fastjet::PseudoJet> JetsConst = PFJetConstituents(empty,empty,empty);

    // wide jets
    fastjet::JetDefinition CA08_def(fastjet::cambridge_algorithm, 0.8);
    fastjet::ClusterSequence pfCA08ClusterSequence = JetMaker(JetsConst, CA08_def);
    vector<fastjet::PseudoJet> pfCA08 = SelectByAcceptance(fastjet::sorted_by_pt(pfCA08ClusterSequence.inclusive_jets()),40., 2.4);
    fastjet::Pruner pruner(CA08_def, 0.1, 0.25);

    Htag = 0;
    Vtag = 0;
    tTag = 0;
    if(pfCA08.size()>0) {

      // pruning
      fastjet::PseudoJet J1 = AngularMatching(pfCA08, ConvertToPseudoJet(V1));
      vector<fastjet::PseudoJet> constituents0 = pfCA08ClusterSequence.constituents(J1);
      fastjet::PseudoJet FatJet0PRUNED = pruner(J1);
      
      JETPT = J1.pt();
      JETMASS = FatJet0PRUNED.m();
      
      // taggers
      JetSubstructure* subStruct0 = new JetSubstructure(FatJet0PRUNED, constituents0, 0.8);
      if(HTag(FatJet0PRUNED,subStruct0)) Htag++;
      if(VTag(FatJet0PRUNED,subStruct0)) Vtag++;
      if(TopTagTypeI(FatJet0PRUNED,subStruct0)) tTag++;
      delete subStruct0;
    } 

    // narrow jets
    fastjet::JetDefinition AK04_def(fastjet::antikt_algorithm, 0.4);
    fastjet::ClusterSequence pfAK04ClusterSequence = JetMaker(JetsConst, AK04_def);
    vector<fastjet::PseudoJet> pfAK04 = SelectByAcceptance(fastjet::sorted_by_pt(pfAK04ClusterSequence.inclusive_jets()),40., 2.4);

    bTag = 0;
    if(pfAK04.size()>0) {
      if(BTagCSVM(pfAK04[0], 0.4)) bTag++;
    }
    jetTree->Fill();
  }

  jetTree->Write();
  EvtInfo->Write();
  DMfile->Close();

}

bool CMSSubstructure::TopTagTypeI(fastjet::PseudoJet prunedjet, 
			       JetSubstructure* subStruct) {
  bool tagged = true;
  // jet mass
  if(prunedjet.m() < 140) tagged = false;
  if(prunedjet.m() > 200) tagged = false;
  // tau3/tau2
  double Tau32 = subStruct->Nsubjettiness(3)/subStruct->Nsubjettiness(2);
  if(Tau32<0.5)  tagged = false;
  return tagged;
}

bool CMSSubstructure::VTag(fastjet::PseudoJet prunedjet, 
			JetSubstructure* subStruct) {
  bool tagged = true;
  // jet mass
  if(prunedjet.m() < 70) tagged = false;
  if(prunedjet.m() > 100) tagged = false;
  // tau2/tau1
  double Tau21 = subStruct->Nsubjettiness(2)/subStruct->Nsubjettiness(1);
  if(Tau21>0.5)  tagged = false;
  return tagged;
}

bool CMSSubstructure::HTag(fastjet::PseudoJet prunedjet, 
			JetSubstructure* subStruct) {
  bool tagged = true;
  // jet mass (shifted for Higgs, because of neutrinos)
  if(prunedjet.m() < 100) tagged = false;
  if(prunedjet.m() > 130) tagged = false;
  // tau2/tau1
  //  double Tau21 = subStruct->Nsubjettiness(2)/subStruct->Nsubjettiness(1);
  //  if(Tau21>0.5)  tagged = false;
  // btag
  if(!BTagHiggs(prunedjet, 0.8)) tagged = false;
  return tagged;
}

int CMSSubstructure::FindVindex(int otherV) {
  for(int i=0; i< GenTreeParticle; i++) {
    // check the IDs
    if(i == otherV) continue;
    if(GenTreeParticlePdgId[i] == 23 || abs(GenTreeParticlePdgId[i]) == 24){
      return i;
    }
  }
  return -99;
}

int CMSSubstructure::FindHindex(int otherV) {
  for(int i=0; i< GenTreeParticle; i++) {
    // check the IDs
    if(i == otherV) continue;
    if(GenTreeParticlePdgId[i] == 25){
      return i;
    }
  }
  return -99;
}

int CMSSubstructure::FindTindex(int otherV) {
  for(int i=0; i< GenTreeParticle; i++) {
    // check the IDs
    if(i == otherV) continue;
    if(GenTreeParticlePdgId[i] == 6 || abs(GenTreeParticlePdgId[i]) == -6){
      return i;
    }
  }
  return -99;
}
