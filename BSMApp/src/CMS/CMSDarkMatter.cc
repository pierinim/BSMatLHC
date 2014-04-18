#include <string>
#include <iostream>
#include <TTree.h>
#include <TFile.h>
#include "CMS/CMSHemisphere.hh"
#include "CMS/CMSDarkMatter.hh"
#include "CommonTools/JetSubstructure.hh"
#include <fastjet/tools/Pruner.hh>


CMSDarkMatter::CMSDarkMatter(TTree *tree, string ModelName, double Lumi, string analysis) : CMSReco(tree) {
  _ModelName = ModelName;
  _Lumi = Lumi;
  verbose = false;
}

CMSDarkMatter::~CMSDarkMatter(){
}

// loop over events - real analysis
void CMSDarkMatter::Loop(string outFileName) {

  TFile* DMfile = new TFile(outFileName.c_str(),"RECREATE");

  // tree with run info (e.g. number of events)
  TTree* EvtInfo = new TTree("EvtInfo", "EvtInfo");

  // tree with event-by-event info MONOJET
  double MET;
  double JETPT;
  int Htag, tTag, bTag, Vtag;
  TTree* monojetTree = new TTree("Monojet","Monojet");
  monojetTree->Branch("MET", &MET, "MET/D");
  monojetTree->Branch("JETPT", &JETPT, "JETPT/D");
  monojetTree->Branch("Htag", &Htag, "Htag/I");
  monojetTree->Branch("Vtag", &Vtag, "Vtag/I");
  monojetTree->Branch("tTag", &tTag, "tTag/I");
  monojetTree->Branch("bTag", &bTag, "bTag/I");

  // tree with event-by-event info RAZOR
  double MR, RSQ, MRNEW, RSQNEW;
  TTree* razorTree = new TTree("RazorDM","RazorDM");
  razorTree->Branch("MR", &MR, "MR/D");
  razorTree->Branch("RSQ", &RSQ, "RSQ/D");
  razorTree->Branch("MRNEW", &MRNEW, "MRNEW/D");
  razorTree->Branch("RSQNEW", &RSQNEW, "RSQNEW/D");
  razorTree->Branch("Htag", &Htag, "Htag/I");
  razorTree->Branch("Vtag", &Vtag, "Vtag/I");
  razorTree->Branch("tTag", &tTag, "tTag/I");
  razorTree->Branch("bTag", &bTag, "bTag/I");

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

    // Build the event at generator level
    PFReco();
    vector<fastjet::PseudoJet> empty;
    vector<fastjet::PseudoJet> JetsConst = PFJetConstituents(empty,empty,empty);

    // wide jets
    fastjet::JetDefinition CA08_def(fastjet::cambridge_algorithm, 0.8);
    fastjet::ClusterSequence pfCA08ClusterSequence = JetMaker(JetsConst, CA08_def);
    vector<fastjet::PseudoJet> pfCA08 = SelectByAcceptance(fastjet::sorted_by_pt(pfCA08ClusterSequence.inclusive_jets()),40., 2.4);
    fastjet::Pruner pruner(CA08_def, 0.1, 0.25);

    // narrow jets
    fastjet::JetDefinition AK04_def(fastjet::antikt_algorithm, 0.4);
    fastjet::ClusterSequence pfAK04ClusterSequence = JetMaker(JetsConst, AK04_def);
    vector<fastjet::PseudoJet> pfAK04 = SelectByAcceptance(fastjet::sorted_by_pt(pfAK04ClusterSequence.inclusive_jets()),40., 2.4);

    // for subjets btag
    fastjet::JetDefinition AK03_def(fastjet::antikt_algorithm, 0.3);


    if(pfAK04.size()<1) continue;
    // TO DO: compute PFMET from PFcandidates rather than smearing the genkjet?
    // MET IS WHAT HERE????

    GenMET();
    PFMET = genMET;

    if(pfAK04.size()>1 && pfAK04[1].pt() > 80.) {

      // razor DM
      // 1a) cluster hemispheres using kT in exclusive mode, using jets as ingredients
      // some backward compatibility test will be needed here
      fastjet::ClusterSequence cs(pfAK04, fastjet::JetDefinition(fastjet::kt_algorithm, 1.0));
      vector<TLorentzVector> hemNEW =  ConvertTo4Vector(fastjet::sorted_by_pt(cs.exclusive_jets(2)));
      // 1b) traditional hemispheres
      CMSHemisphere* myHem = new CMSHemisphere(ConvertTo4Vector(pfAK04));
      myHem->CombineMinMass();
      vector<TLorentzVector> hem = myHem->GetHemispheres();
      delete myHem;
      // 2a) compute new RSQ and MR
      TLorentzVector j1 = hemNEW[0];
      TLorentzVector j2 = hemNEW[1];  
      MRNEW = CalcMR(j1, j2);
      RSQNEW = pow(CalcMRT(j1, j2, PFMET),2.)/MR/MR;
      // 2b) compute traditional RSQ and MR
      j1 = hem[0];
      j2 = hem[1];  
      MR = CalcMR(j1, j2);
      RSQ = pow(CalcMRT(j1, j2, PFMET),2.)/MR/MR;

      Htag = 0;
      Vtag = 0;
      tTag = 0;
      bTag = 0;
      if(BTagCSVM(pfAK04[0], 0.4)) bTag++;
      if(BTagCSVM(pfAK04[1], 0.4)) bTag++;
      if(pfCA08.size() >=2) {
	// match the AK4 jet to a CA8 jet
	fastjet::PseudoJet FatJet0 = AngularMatching(pfCA08,pfAK04[0]);
	vector<fastjet::PseudoJet> constituents0 = pfCA08ClusterSequence.constituents(FatJet0);
	fastjet::PseudoJet FatJet0PRUNED = pruner(FatJet0);
	JetSubstructure* subStruct0 = new JetSubstructure(FatJet0PRUNED, constituents0, 0.8);

	fastjet::PseudoJet FatJet1 = AngularMatching(pfCA08,pfAK04[1]);
	vector<fastjet::PseudoJet> constituents1 = pfCA08ClusterSequence.constituents(FatJet1);
	fastjet::PseudoJet FatJet1PRUNED = pruner(FatJet1);
	JetSubstructure* subStruct1 = new JetSubstructure(FatJet1PRUNED, constituents1, 0.8);

	// taggers
	if(HTag(FatJet0PRUNED,subStruct0) && BtagSubJets(constituents0,AK03_def,10., 2.4, 2)) Htag++;
	if(HTag(FatJet1PRUNED,subStruct1) && BtagSubJets(constituents1,AK03_def,10., 2.4, 2)) Htag++;
	if(VTag(FatJet0PRUNED,subStruct0)) Vtag++;
	if(VTag(FatJet1PRUNED,subStruct1)) Vtag++;
	if(TopTagTypeI(FatJet0PRUNED,subStruct0)) tTag++;
	if(TopTagTypeI(FatJet1PRUNED,subStruct1)) tTag++;
	delete subStruct0;
	delete subStruct1;
      }

      // Fill the event
      razorTree->Fill();

    } else if(pfAK04[0].pt() > 110.) {
      // monojet selection
      // 1) veto third jet with pT>40 GeV
      if(pfAK04.size()>2) continue;
      // 2)  baseline MET cut
      if(PFMET.pt()<250.) continue;
      // 3) DelphaPhi(j,j)
      if(pfAK04.size() ==2 && pfAK04[0].delta_phi_to(pfAK04[1])>=2.5) continue;
      // 4) Electron VETO
      EleReco();
      int iEle = 0;
      for(int i=0; i< EleWP80.size(); i++) {
	if(EleWP80[i].Pt()>10.) iEle++;
      }
      if(iEle>0) continue;
      // cleanup inefficiency
      //      if(!_statTools->HitOrMiss(0.975)) continue;
      // 5) Muon VETO
      MuReco();
      int iMu = 0;
      for(int i=0; i< TightMu.size(); i++) {
	if(TightMu[i].Pt()>10.) iMu++;
      }
      if(iMu>0) continue;
      // 6) iso-track veto (for taus)
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
      // Save Monojet Tree
      // MET
      MET = PFMET.pt();
      JETPT = pfAK04[0].pt();

      // taggers
      Htag = 0;
      Vtag = 0;
      tTag = 0;
      bTag = 0;
      if(BTagCSVM(pfAK04[0], 0.4)) bTag++;
      if(pfCA08.size() >=1) {
	fastjet::PseudoJet FatJet0 = AngularMatching(pfCA08,pfAK04[0]);
	vector<fastjet::PseudoJet> constituents0 = pfCA08ClusterSequence.constituents(FatJet0);
	fastjet::PseudoJet FatJet0PRUNED = pruner(FatJet0);
	JetSubstructure* subStruct0 = new JetSubstructure(FatJet0PRUNED, constituents0, 0.8);
	if(HTag(FatJet0PRUNED,subStruct0) && BtagSubJets(constituents0,AK03_def,10., 2.4, 2)) Htag++;
	if(VTag(FatJet0PRUNED,subStruct0)) Vtag++;
	if(TopTagTypeI(FatJet0PRUNED,subStruct0)) tTag++;
	delete subStruct0;
      }
      monojetTree->Fill();
    }
  }

  monojetTree->Write();
  razorTree->Write();
  EvtInfo->Write();
  DMfile->Close();

}

bool CMSDarkMatter::TopTagTypeI(fastjet::PseudoJet prunedjet, 
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

bool CMSDarkMatter::VTag(fastjet::PseudoJet prunedjet, 
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

bool CMSDarkMatter::HTag(fastjet::PseudoJet prunedjet, 
			JetSubstructure* subStruct) {
  bool tagged = true;
  // jet mass
  if(prunedjet.m() < 110) tagged = false;
  if(prunedjet.m() > 135) tagged = false;
  // tau2/tau1
  double Tau21 = subStruct->Nsubjettiness(2)/subStruct->Nsubjettiness(1);
  if(Tau21>0.5)  tagged = false;
  return tagged;
}

bool CMSDarkMatter::BtagSubJets(vector<fastjet::PseudoJet> particles,
			       fastjet::JetDefinition jetdef, double minpT,
			       double maxEta, int nBtag) {

  fastjet::ClusterSequence subjetsClusterSequence = JetMaker(particles,jetdef);
  vector<fastjet::PseudoJet> subjets = SelectByAcceptance(fastjet::sorted_by_pt(subjetsClusterSequence.inclusive_jets()),minpT, maxEta);
  if(subjets.size() < nBtag) return false;
  int ntagged = 0;
  for(int i=0;i<subjets.size(); i++) {
    // TO DO: FIX ME
    if(BTagCSVM(subjets[i],0.3)) ntagged++;
  }
  if(ntagged>=nBtag) return true;
  return false;
}
