#include <string>
#include <iostream>
#include <TTree.h>
#include <TFile.h>
#include "FCC/FCCExoVV.hh"
#include "CommonTools/JetSubstructure.hh"
#include <math.h>
#include <fastjet/tools/Pruner.hh>

FCCExoVV::FCCExoVV(TTree *tree) : FCCReco(tree) {
  verbose = false;
}

FCCExoVV::~FCCExoVV(){
}

// loop over events - real analysis
void FCCExoVV::Loop(string outFileName) {

  Double_t PMass, Tau21, RawMass;
  vector<TTree*> PMassTau21;
  vector<TTree*> TRKPMassTau21;
  vector<TTree*> PMassTau21Mass;

  // GEN-LEVEL PLOTS
  TH1D* X_mass = new TH1D("X_mass", "X_mass", 2000, 0., 100000.);
  TH1D* X_eta = new TH1D("X_eta", "X_eta", 50, -10., 10.);
  TH1D* X_pt = new TH1D("X_pt", "X_pt", 200, 0., 15000.);
  TH1D* X_ptDaugh1 = new TH1D("X_ptDaugh1", "X_ptDaugh1", 200, 0., 15000.);
  TH1D* X_ptDaugh2 = new TH1D("X_ptDaugh2", "X_ptDaugh2", 200, 0., 15000.);
  TH1D* X_DRdaugh = new TH1D("X_DRdaugh", "X_DRdaugh", 100, 0., 0.3);
  vector<TH1D*> moverpGenJet;
  vector<TH1D*> moverpPrunedGenJet;
  vector<TH1D*> massDiGenJet;
  vector<TH1D*> massGenJet;
  vector<TH1D*> massPrunedGenJet;
  vector<TH1D*> massDiPrunedGenJet;
  vector<TH1D*> massGenJet_WideRange;
  vector<TH1D*> massPrunedGenJet_WideRange;
  vector<TH1D*> tau21;
  vector<TH1D*> tau21_Pruned;
  vector<TH1D*> tau21_Pruned_WithMassCut;

  vector<TH1D*> TRKmoverpGenJet;
  vector<TH1D*> TRKmassDiGenJet;
  vector<TH1D*> TRKmassGenJet;
  vector<TH1D*> TRKmassPrunedGenJet;
  vector<TH1D*> TRKmassDiPrunedGenJet;
  vector<TH1D*> TRKmassGenJet_WideRange;
  vector<TH1D*> TRKmassPrunedGenJet_WideRange;
  vector<TH1D*> TRKtau21;
  vector<TH1D*> TRKtau21_Pruned;
  vector<TH1D*> TRKtau21_Pruned_WithMassCut;

  vector<TH1D*> EGTRKmoverpGenJet;
  vector<TH1D*> EGTRKmassDiGenJet;
  vector<TH1D*> EGTRKmassGenJet;
  vector<TH1D*> EGTRKmassPrunedGenJet;
  vector<TH1D*> EGTRKmassDiPrunedGenJet;
  vector<TH1D*> EGTRKmassGenJet_WideRange;
  vector<TH1D*> EGTRKmassPrunedGenJet_WideRange;
  vector<TH1D*> EGTRKtau21;
  vector<TH1D*> EGTRKtau21_Pruned;
  vector<TH1D*> EGTRKtau21_Pruned_WithMassCut;

  const int iRad = 1;
  //  double jetRadius[iRad] = {0.1,0.2,0.4,0.6};
  double jetRadius[iRad] = {0.2};
  for(int k=0; k<iRad; k++) {
    char name[256];
    sprintf(name, "moverpGenJet_DR_0_%i",int(10.*jetRadius[k]));
    moverpGenJet.push_back(new TH1D(name, name, 500, 0.0, 1.));
    sprintf(name, "moverpPrunedGenJet_DR_0_%i",int(10.*jetRadius[k]));
    moverpPrunedGenJet.push_back(new TH1D(name, name, 500, 0.01, 1.));
    sprintf(name, "massDiGenJet_DR_0_%i",int(10.*jetRadius[k]));
    massDiGenJet.push_back(new TH1D(name, name, 1000, 0., 100.));
    sprintf(name, "massGenJet_DR_0_%i",int(10.*jetRadius[k]));
    massGenJet.push_back(new TH1D(name, name, 150, 0., 150.));
    sprintf(name, "massPrunedGenJet_DR_0_%i",int(10.*jetRadius[k]));
    massPrunedGenJet.push_back(new TH1D(name, name, 150, 0., 150.));
    sprintf(name, "massDiPrunedGenJet_DR_0_%i",int(10.*jetRadius[k]));
    massDiPrunedGenJet.push_back(new TH1D(name, name, 1000, 0., 100.));
    sprintf(name, "massPrunedGenJet_WideRange_DR_0_%i",int(10.*jetRadius[k]));
    massPrunedGenJet_WideRange.push_back(new TH1D(name, name, 200, 0., 2000.));
    sprintf(name, "massGenJet_WideRange_DR_0_%i",int(10.*jetRadius[k]));
    massGenJet_WideRange.push_back(new TH1D(name, name, 200, 0., 2000.));
    sprintf(name, "tau21_DR_0_%i",int(10.*jetRadius[k]));
    tau21.push_back(new TH1D(name, name, 100, 0., 1.));
    sprintf(name, "tau21_Pruned_DR_0_%i",int(10.*jetRadius[k]));
    tau21_Pruned.push_back(new TH1D(name, name, 100, 0., 1.));
    sprintf(name, "tau21_Pruned_WithMassCut_DR_0_%i",int(10.*jetRadius[k]));
    tau21_Pruned_WithMassCut.push_back(new TH1D(name, name, 100, 0.,1.));
    // TRACK ONLY
    sprintf(name, "TRKmoverpGenJet_DR_0_%i",int(10.*jetRadius[k]));
    TRKmoverpGenJet.push_back(new TH1D(name, name, 500, 0.0, 1.));
    sprintf(name, "TRKmassDiGenJet_DR_0_%i",int(10.*jetRadius[k]));
    TRKmassDiGenJet.push_back(new TH1D(name, name, 1000, 0., 100.));
    sprintf(name, "TRKmassGenJet_DR_0_%i",int(10.*jetRadius[k]));
    TRKmassGenJet.push_back(new TH1D(name, name, 150, 0., 150.));
    sprintf(name, "TRKmassPrunedGenJet_DR_0_%i",int(10.*jetRadius[k]));
    TRKmassPrunedGenJet.push_back(new TH1D(name, name, 150, 0., 150.));
    sprintf(name, "TRKmassDiPrunedGenJet_DR_0_%i",int(10.*jetRadius[k]));
    TRKmassDiPrunedGenJet.push_back(new TH1D(name, name, 1000, 0., 100.));
    sprintf(name, "TRKmassPrunedGenJet_WideRange_DR_0_%i",int(10.*jetRadius[k]));
    TRKmassPrunedGenJet_WideRange.push_back(new TH1D(name, name, 200, 0., 1000.));
    sprintf(name, "TRKmassGenJet_WideRange_DR_0_%i",int(10.*jetRadius[k]));
    TRKmassGenJet_WideRange.push_back(new TH1D(name, name, 200, 0., 1000.));
    sprintf(name, "TRKtau21_DR_0_%i",int(10.*jetRadius[k]));
    TRKtau21.push_back(new TH1D(name, name, 100, 0., 1.));
    sprintf(name, "TRKtau21_Pruned_DR_0_%i",int(10.*jetRadius[k]));
    TRKtau21_Pruned.push_back(new TH1D(name, name, 100, 0., 1.));
    sprintf(name, "TRKtau21_Pruned_WithMassCut_DR_0_%i",int(10.*jetRadius[k]));
    TRKtau21_Pruned_WithMassCut.push_back(new TH1D(name, name, 100, 0.,1.));
    // TRACK +EG
    sprintf(name, "EGTRKmoverpGenJet_DR_0_%i",int(10.*jetRadius[k]));
    EGTRKmoverpGenJet.push_back(new TH1D(name, name, 500, 0.0, 1.));
    sprintf(name, "EGTRKmassDiGenJet_DR_0_%i",int(10.*jetRadius[k]));
    EGTRKmassDiGenJet.push_back(new TH1D(name, name, 1000, 0., 100.));
    sprintf(name, "EGTRKmassGenJet_DR_0_%i",int(10.*jetRadius[k]));
    EGTRKmassGenJet.push_back(new TH1D(name, name, 150, 0., 150.));
    sprintf(name, "EGTRKmassPrunedGenJet_DR_0_%i",int(10.*jetRadius[k]));
    EGTRKmassPrunedGenJet.push_back(new TH1D(name, name, 150, 0., 150.));
    sprintf(name, "EGTRKmassDiPrunedGenJet_DR_0_%i",int(10.*jetRadius[k]));
    EGTRKmassDiPrunedGenJet.push_back(new TH1D(name, name, 1000, 0., 100.));
    sprintf(name, "EGTRKmassPrunedGenJet_WideRange_DR_0_%i",int(10.*jetRadius[k]));
    EGTRKmassPrunedGenJet_WideRange.push_back(new TH1D(name, name, 200, 0., 1000.));
    sprintf(name, "EGTRKmassGenJet_WideRange_DR_0_%i",int(10.*jetRadius[k]));
    EGTRKmassGenJet_WideRange.push_back(new TH1D(name, name, 200, 0., 1000.));
    sprintf(name, "EGTRKtau21_DR_0_%i",int(10.*jetRadius[k]));
    EGTRKtau21.push_back(new TH1D(name, name, 100, 0., 1.));
    sprintf(name, "EGTRKtau21_Pruned_DR_0_%i",int(10.*jetRadius[k]));
    EGTRKtau21_Pruned.push_back(new TH1D(name, name, 100, 0., 1.));
    sprintf(name, "EGTRKtau21_Pruned_WithMassCut_DR_0_%i",int(10.*jetRadius[k]));
    EGTRKtau21_Pruned_WithMassCut.push_back(new TH1D(name, name, 100, 0.,1.));
    /*
    // trees
    // TTrees for optimization
    sprintf(name, "PMassTau21_DR_0_%i",int(10.*jetRadius[k]));
    PMassTau21.push_back(new TTree(name, name));
    PMassTau21[k]->Branch("PMass",&PMass,"PMass/D");
    PMassTau21[k]->Branch("Tau21",&Tau21,"Tau21/D");
    // TTrees for optimization
    sprintf(name, "PMassTau21Mass_DR_0_%i",int(10.*jetRadius[k]));
    PMassTau21Mass.push_back(new TTree(name, name));
    PMassTau21Mass[k]->Branch("PMass",&PMass,"PMass/D");
    PMassTau21Mass[k]->Branch("Tau21",&Tau21,"Tau21/D");
    PMassTau21Mass[k]->Branch("RawMass",&RawMass,"RawMass/D");
    // TRK
    // TTrees for optimization
    sprintf(name, "TRKPMassTau21_DR_0_%i",int(10.*jetRadius[k]));
    TRKPMassTau21.push_back(new TTree(name, name));
    TRKPMassTau21[k]->Branch("PMass",&PMass,"PMass/D");
    TRKPMassTau21[k]->Branch("Tau21",&Tau21,"Tau21/D");
    */
  }

  if(fChain == 0) return;
  
  // loop over entries
  Long64_t nbytes = 0, nb = 0;
  Long64_t nentries = fChain->GetEntries();
  std::cout << "Number of entries = " << nentries << std::endl;
  for (Long64_t jentry=0; jentry<nentries;jentry+=1) {
  //  for (Long64_t jentry=0; jentry<1000;jentry+=1) {
    if(verbose) { 
      cout << "new event:" << jentry << endl;
      cout << "Particles: " << Particle << endl;
      cout << "Muon : " << Muon << endl;
      cout << "Electron : " << Electron << endl;
      cout << "Electron : " << Electron << endl;
      cout << "b : " << b << endl;
      cout << "Photon : " << Photon << endl;
      cout << "Neutrino : " << Neutrino << endl;
      cout << "SUSY : " << SUSY << endl;
      cout << "GenTreeParticle : " << GenTreeParticle << endl;
    }

    // clean physics-objects blocks
    CleanEvent();

    // get new event
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    if (jentry%1000 == 0) std::cout << ">>> Processing event # " << jentry << std::endl;

    // gen plots first
    int iV1 = FindVindex(-99);
    int iV2 = FindVindex(iV1);
   
    //    cout << leptonZDecay() << endl;
    if(leptonZDecay()) continue;

    if(iV1 == -99 || iV2 == -99) continue;
    TLorentzVector V1(GenTreeParticlePx[iV1], GenTreeParticlePy[iV1], GenTreeParticlePz[iV1], GenTreeParticleE[iV1]);
    TLorentzVector V2(GenTreeParticlePx[iV2], GenTreeParticlePy[iV2], GenTreeParticlePz[iV2], GenTreeParticleE[iV2]);
    X_mass->Fill((V1+V2).M());
    X_eta->Fill((V1+V2).Eta());
    X_pt->Fill((V1+V2).Pt());
    if(V1.Pt()>V2.Pt()) {
      X_ptDaugh1->Fill(V1.Pt());
      X_ptDaugh2->Fill(V2.Pt());
    } else {
      X_ptDaugh1->Fill(V2.Pt());
      X_ptDaugh2->Fill(V1.Pt());
      int tmpINDEX = iV1;
      iV1 = iV2;
      iV2 = tmpINDEX;
    }
    // V daughters
    bool leptonicDecay = false;
    for(int i=0; i< GenTreeParticle-1; i++) {
      if((GenTreeParticleM1PdgId[i] == 23 && GenTreeParticleM1PdgId[i+1] == 23) ||
	 (GenTreeParticleM1PdgId[i] == 24 && GenTreeParticleM1PdgId[i] == 24) ||  
	 (GenTreeParticleM1PdgId[i] == -24 && GenTreeParticleM1PdgId[i] == -24)) {
	TLorentzVector D1(GenTreeParticlePx[i], GenTreeParticlePy[i], GenTreeParticlePz[i], GenTreeParticleE[i]);
	TLorentzVector D2(GenTreeParticlePx[i+1], GenTreeParticlePy[i+1], GenTreeParticlePz[i+1], GenTreeParticleE[i+1]);
	X_DRdaugh->Fill(D1.DeltaR(D2));
	i++;
	if(abs(GenTreeParticlePdgId[i])>8) leptonicDecay = true;
      }
    }

    // reject events with leptonic decays 
    if(leptonicDecay) continue;

    // Jet Radius Optimization (check dijet mass resolution and pruned-jet mass resolution vs jet R)
    vector<fastjet::PseudoJet> genJetsConst = GenJetConstituents(false);
    if(genJetsConst.size() <= 0) continue;
    for(int k=0; k<iRad; k++) {
      fastjet::JetDefinition CA_def(fastjet::cambridge_algorithm, jetRadius[k]);
      fastjet::ClusterSequence genJetClusterSequence = JetMaker(genJetsConst, CA_def);
      vector<fastjet::PseudoJet> myJets = SelectByAcceptance(fastjet::sorted_by_pt(genJetClusterSequence.inclusive_jets()),30.,8.0);
      fastjet::Pruner pruner(CA_def, 0.1, 0.25);
      if(myJets.size()<2) continue;

      // pruned tau2/tau1 1st jet
      fastjet::PseudoJet J1 = AngularMatching(myJets, ConvertToPseudoJet(V1));
      fastjet::PseudoJet p1 = pruner(J1);
      JetSubstructure* subStruct1 = new JetSubstructure(J1,genJetsConst,jetRadius[k]);
      JetSubstructure* subStruct1_Pruned = new JetSubstructure(p1,genJetsConst,jetRadius[k]);
      Tau21 = subStruct1_Pruned->Nsubjettiness(2)/subStruct1_Pruned->Nsubjettiness(1);
      RawMass = J1.m();
      PMass = p1.m();

      // Fill Trees
      //      PMassTau21[k]->Fill();
      //      PMassTau21Mass[k]->Fill();
      // Fill Histograms
      moverpGenJet[k]->Fill(RawMass/J1.pt());
      moverpPrunedGenJet[k]->Fill(RawMass/J1.pt());
      massGenJet[k]->Fill(RawMass);
      massGenJet_WideRange[k]->Fill(RawMass);
      massPrunedGenJet[k]->Fill(PMass);
      massPrunedGenJet_WideRange[k]->Fill(PMass);
      tau21[k]->Fill(subStruct1->Nsubjettiness(2)/subStruct1->Nsubjettiness(1));
      tau21_Pruned[k]->Fill(Tau21);
      if(PMass>70 && PMass <100.) tau21_Pruned_WithMassCut[k]->Fill(Tau21);

      // pruned tau2/tau1 2nd jet
      fastjet::PseudoJet J2 = AngularMatching(myJets, ConvertToPseudoJet(V2));
      fastjet::PseudoJet p2 = pruner(J2);
      JetSubstructure* subStruct2 = new JetSubstructure(J2,genJetsConst,jetRadius[k]);      
      JetSubstructure* subStruct2_Pruned = new JetSubstructure(p2,genJetsConst,jetRadius[k]);      
      Tau21 = subStruct1_Pruned->Nsubjettiness(2)/subStruct1_Pruned->Nsubjettiness(1);
      RawMass = J2.m();
      PMass = p2.m();
      // Fill Trees
      //      PMassTau21[k]->Fill();
      //      PMassTau21Mass[k]->Fill();
      // Fill Histograms
      moverpGenJet[k]->Fill(RawMass/J2.pt());
      moverpPrunedGenJet[k]->Fill(RawMass/J2.pt());
      massGenJet[k]->Fill(RawMass);
      massGenJet_WideRange[k]->Fill(RawMass);
      massPrunedGenJet[k]->Fill(PMass);
      massPrunedGenJet_WideRange[k]->Fill(PMass);
      tau21[k]->Fill(subStruct2->Nsubjettiness(2)/subStruct2->Nsubjettiness(1));
      tau21_Pruned[k]->Fill(Tau21);
      if(PMass>70 && PMass <100.) tau21_Pruned_WithMassCut[k]->Fill(Tau21);

      // DiJet Histos
      massDiPrunedGenJet[k]->Fill((p1+p2).m()/1000.);
      massDiGenJet[k]->Fill((J1+J2).m()/1000.);

      delete subStruct1;
      delete subStruct1_Pruned;
      delete subStruct2;
      delete subStruct2_Pruned;
    }

    // TrkJets [perfect resolution]
    RecoTracks();
    vector<fastjet::PseudoJet> tracks = ConvertToPseudoJet(Track);
    //    RecoECALneutrals();
    //    vector<fastjet::PseudoJet> tracks = ConvertToPseudoJet(ECALneutrals);
    //    cout << Track.size() << " " << ECALneutrals.size() << " " << Particle << endl;
    if(tracks.size() <= 0) continue;
    for(int k=0; k<iRad; k++) {
      fastjet::JetDefinition CA_def(fastjet::cambridge_algorithm, jetRadius[k]);
      fastjet::ClusterSequence genJetClusterSequence = JetMaker(tracks, CA_def);
      vector<fastjet::PseudoJet> myJets = SelectByAcceptance(fastjet::sorted_by_pt(genJetClusterSequence.inclusive_jets()),30.,8.0);
      fastjet::Pruner pruner(CA_def, 0.1, 0.25);
      if(myJets.size()<2) continue;

      // pruned tau2/tau1 1st jet
      fastjet::PseudoJet J1 = AngularMatching(myJets, ConvertToPseudoJet(V1));
      fastjet::PseudoJet p1 = pruner(J1);
      JetSubstructure* subStruct1 = new JetSubstructure(J1,genJetsConst,jetRadius[k]);
      JetSubstructure* subStruct1_Pruned = new JetSubstructure(p1,genJetsConst,jetRadius[k]);
      Tau21 = subStruct1_Pruned->Nsubjettiness(2)/subStruct1_Pruned->Nsubjettiness(1);
      RawMass = J1.m();
      PMass = p1.m();
      // Fill Trees
      //      TRKPMassTau21[k]->Fill();
      // Fill Histograms
      TRKmoverpGenJet[k]->Fill(RawMass/J1.pt());
      TRKmassGenJet[k]->Fill(RawMass);
      TRKmassPrunedGenJet[k]->Fill(PMass);
      TRKtau21[k]->Fill(subStruct1->Nsubjettiness(2)/subStruct1->Nsubjettiness(1));
      TRKtau21_Pruned[k]->Fill(Tau21);
      if(PMass>70 && PMass <100.) TRKtau21_Pruned_WithMassCut[k]->Fill(Tau21);

      // pruned tau2/tau1 2nd jet
      fastjet::PseudoJet J2 = AngularMatching(myJets, ConvertToPseudoJet(V2));
      fastjet::PseudoJet p2 = pruner(J2);
      JetSubstructure* subStruct2 = new JetSubstructure(J2,genJetsConst,jetRadius[k]);
      JetSubstructure* subStruct2_Pruned = new JetSubstructure(p2,genJetsConst,jetRadius[k]);      
      Tau21 = subStruct1_Pruned->Nsubjettiness(2)/subStruct1_Pruned->Nsubjettiness(1);
      RawMass = J2.m();
      PMass = p2.m();
      // Fill Trees
      //      TRKPMassTau21[k]->Fill();
      // Fill Histograms
      TRKmoverpGenJet[k]->Fill(RawMass/J2.pt());
      TRKmassGenJet[k]->Fill(RawMass);
      TRKmassPrunedGenJet[k]->Fill(PMass);
      TRKtau21[k]->Fill(subStruct2->Nsubjettiness(2)/subStruct2->Nsubjettiness(1));
      TRKtau21_Pruned[k]->Fill(Tau21);
      if(PMass>70 && PMass <100.) TRKtau21_Pruned_WithMassCut[k]->Fill(Tau21);

      // DiJet Histos
      TRKmassDiPrunedGenJet[k]->Fill((p1+p2).m()/1000.);
      TRKmassDiGenJet[k]->Fill((J1+J2).m()/1000.);

      delete subStruct1;
      delete subStruct1_Pruned;
      delete subStruct2;
      delete subStruct2_Pruned;
    }

    // (EG+Trk)Jets [perfect resolution]
    RecoECALneutrals();
    vector<fastjet::PseudoJet> eg = ConvertToPseudoJet(ECALneutrals);
    for(int iEG=0; iEG<eg.size();iEG++) {
      tracks.push_back(eg[iEG]);
    }
    if(tracks.size() <= 0) continue;
    for(int k=0; k<iRad; k++) {
      fastjet::JetDefinition CA_def(fastjet::cambridge_algorithm, jetRadius[k]);
      fastjet::ClusterSequence genJetClusterSequence = JetMaker(tracks, CA_def);
      vector<fastjet::PseudoJet> myJets = SelectByAcceptance(fastjet::sorted_by_pt(genJetClusterSequence.inclusive_jets()),30.,8.0);
      fastjet::Pruner pruner(CA_def, 0.1, 0.25);
      if(myJets.size()<2) continue;

      // pruned tau2/tau1 1st jet
      fastjet::PseudoJet J1 = AngularMatching(myJets, ConvertToPseudoJet(V1));
      fastjet::PseudoJet p1 = pruner(J1);
      JetSubstructure* subStruct1 = new JetSubstructure(J1,genJetsConst,jetRadius[k]);
      JetSubstructure* subStruct1_Pruned = new JetSubstructure(p1,genJetsConst,jetRadius[k]);
      Tau21 = subStruct1_Pruned->Nsubjettiness(2)/subStruct1_Pruned->Nsubjettiness(1);
      RawMass = J1.m();
      PMass = p1.m();
      // Fill Trees
      //      EGTRKPMassTau21[k]->Fill();
      // Fill Histograms
      EGTRKmoverpGenJet[k]->Fill(RawMass/J1.pt());
      EGTRKmassGenJet[k]->Fill(RawMass);
      EGTRKmassPrunedGenJet[k]->Fill(PMass);
      EGTRKtau21[k]->Fill(subStruct1->Nsubjettiness(2)/subStruct1->Nsubjettiness(1));
      EGTRKtau21_Pruned[k]->Fill(Tau21);
      if(PMass>70 && PMass <100.) EGTRKtau21_Pruned_WithMassCut[k]->Fill(Tau21);

      // pruned tau2/tau1 2nd jet
      fastjet::PseudoJet J2 = AngularMatching(myJets, ConvertToPseudoJet(V2));
      fastjet::PseudoJet p2 = pruner(J2);
      JetSubstructure* subStruct2 = new JetSubstructure(J2,genJetsConst,jetRadius[k]);
      JetSubstructure* subStruct2_Pruned = new JetSubstructure(p2,genJetsConst,jetRadius[k]);      
      Tau21 = subStruct1_Pruned->Nsubjettiness(2)/subStruct1_Pruned->Nsubjettiness(1);
      RawMass = J2.m();
      PMass = p2.m();
      // Fill Trees
      //      EGTRKPMassTau21[k]->Fill();
      // Fill Histograms
      EGTRKmoverpGenJet[k]->Fill(RawMass/J2.pt());
      EGTRKmassGenJet[k]->Fill(RawMass);
      EGTRKmassPrunedGenJet[k]->Fill(PMass);
      EGTRKtau21[k]->Fill(subStruct2->Nsubjettiness(2)/subStruct2->Nsubjettiness(1));
      EGTRKtau21_Pruned[k]->Fill(Tau21);
      if(PMass>70 && PMass <100.) EGTRKtau21_Pruned_WithMassCut[k]->Fill(Tau21);

      // DiJet Histos
      EGTRKmassDiPrunedGenJet[k]->Fill((p1+p2).m()/1000.);
      EGTRKmassDiGenJet[k]->Fill((J1+J2).m()/1000.);

      delete subStruct1;
      delete subStruct1_Pruned;
      delete subStruct2;
      delete subStruct2_Pruned;
    }

    /*
    RecoTracks();    
    ClusterTrackJet(80., 3.0, jetRadius, "CA");

    //At least two jets 
    if(TrackJet.size()<2) continue;

    TrackJet = SortByPt(TrackJet);
    TLorentzVector DiJet[2];
    DiJet[0] = TrackJet[0];
    DiJet[1] = TrackJet[1];

    // MIN MASS
    if((DiJet[0]+DiJet[1]).Mag()<1500.) continue; 

    JetSubstructure* subStruct1 = new JetSubstructure(DiJet[0],Track,jetRadius);
    JetSubstructure* subStruct2 = new JetSubstructure(DiJet[1],Track,jetRadius);

    tau21_1st->Fill(subStruct1->Nsubjettiness(2)/subStruct1->Nsubjettiness(1));
    mass_1st->Fill(DiJet[0].Mag());

    tau21_2nd->Fill(subStruct2->Nsubjettiness(2)/subStruct2->Nsubjettiness(1));
    mass_2nd->Fill(DiJet[1].Mag());
    */
  }

  TFile *fileOUT = new TFile(outFileName.c_str(),"RECREATE");
  // GEN PLOTS
  X_mass->Write();
  X_eta->Write();
  X_pt->Write();
  X_DRdaugh->Write();
  X_ptDaugh1->Write();
  X_ptDaugh2->Write();
  fileOUT->mkdir("Particles");
  fileOUT->cd("Particles");  
  for(int j=0; j<iRad; j++) {
    moverpGenJet[j]->Write();
    moverpPrunedGenJet[j]->Write();
    massDiGenJet[j]->Write();
    massGenJet[j]->Write();
    massPrunedGenJet[j]->Write();
    massGenJet_WideRange[j]->Write();
    massPrunedGenJet_WideRange[j]->Write();
    massDiPrunedGenJet[j]->Write();
    tau21[j]->Write();
    tau21_Pruned[j]->Write();
    tau21_Pruned_WithMassCut[j]->Write();
  }
  fileOUT->cd();  
  fileOUT->mkdir("Track");
  fileOUT->cd("Track");  
  for(int j=0; j<iRad; j++) {
    TRKmoverpGenJet[j]->Write();
    TRKmassDiGenJet[j]->Write();
    TRKmassGenJet[j]->Write();
    TRKmassPrunedGenJet[j]->Write();
    TRKmassDiPrunedGenJet[j]->Write();
    TRKtau21[j]->Write();
    TRKtau21_Pruned[j]->Write();
    TRKtau21_Pruned_WithMassCut[j]->Write();
  }
  fileOUT->cd();  
  fileOUT->mkdir("EGTrack");
  fileOUT->cd("EGTrack");  
  for(int j=0; j<iRad; j++) {
    EGTRKmoverpGenJet[j]->Write();
    EGTRKmassDiGenJet[j]->Write();
    EGTRKmassGenJet[j]->Write();
    EGTRKmassPrunedGenJet[j]->Write();
    EGTRKmassDiPrunedGenJet[j]->Write();
    EGTRKtau21[j]->Write();
    EGTRKtau21_Pruned[j]->Write();
    EGTRKtau21_Pruned_WithMassCut[j]->Write();
  }
  // Trees
  // fileOUT->mkdir("TMVAtrees");
  // fileOUT->cd("TMVAtrees");
  // for(int j=0; j<5; j++) {
  //   PMassTau21[j]->Write();
  //   PMassTau21Mass[j]->Write();
  //   TRKPMassTau21[j]->Write();
  // }
  fileOUT->Close();
}

int FCCExoVV::FindVindex(int otherV) {
  for(int i=0; i< GenTreeParticle; i++) {
    // check the IDs
    if(i == otherV) continue;
    if(GenTreeParticlePdgId[i] == 23 || abs(GenTreeParticlePdgId[i]) == 24){
      return i;
    }
  }
  return -99;
}


bool FCCExoVV::leptonZDecay() {
  bool found = false;
  //  cout << "####################" << endl;
  for(int i=0; i< GenTreeParticle; i++) {
    // check the IDs
    //    cout << GenTreeParticlePdgId[i] << " " <<  GenTreeParticleM1PdgId[i] << endl;
    if(GenTreeParticleM1PdgId[i] == 23 && abs(GenTreeParticlePdgId[i]) == 11) found = true;
    if(GenTreeParticleM1PdgId[i] == 23 && abs(GenTreeParticlePdgId[i]) == 13) found = true;
    if(GenTreeParticleM1PdgId[i] == 23 && abs(GenTreeParticlePdgId[i]) == 15) found = true;
  }
  //  cout << found << endl;
  return found;
}

bool FCCExoVV::leptonWDecay() {
  for(int i=0; i< GenTreeParticle; i++) {
    // check the IDs
    if(GenTreeParticleM1PdgId[i] == 24 && abs(GenTreeParticlePdgId[i]) == 11) return true;
    if(GenTreeParticleM1PdgId[i] == 24 && abs(GenTreeParticlePdgId[i]) == 13) return true;
    if(GenTreeParticleM1PdgId[i] == 24 && abs(GenTreeParticlePdgId[i]) == 15) return true;
  }
  return false;
}
