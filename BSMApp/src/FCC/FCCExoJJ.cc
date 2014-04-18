#include <string>
#include <iostream>
#include <TTree.h>
#include <TFile.h>
#include "FCC/FCCExoJJ.hh"
#include "CommonTools/JetSubstructure.hh"
#include <math.h>

#include <fastjet/tools/Pruner.hh>

FCCExoJJ::FCCExoJJ(TTree *tree) : FCCReco(tree) {
  verbose = false;
}

FCCExoJJ::~FCCExoJJ(){
}

// loop over events - real analysis
void FCCExoJJ::Loop(string outFileName) {

  Float_t PMass, Tau21, RawMass;
  vector<TTree*> PMassTau21;
  vector<TTree*> PMassTau21Mass;
  vector<TTree*> TRKPMassTau21;

  // GEN-LEVEL PLOTS
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
    moverpGenJet.push_back(new TH1D(name, name, 500, 0.01, 1.));
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

    // Jet Radius Optimization (check dijet mass resolution and pruned-jet mass resolution vs jet R)
    vector<fastjet::PseudoJet> genJetsConst = GenJetConstituents(false);
    if(genJetsConst.size() <= 0) continue;
    for(int k=0; k<iRad; k++) {
      fastjet::JetDefinition CA_def(fastjet::cambridge_algorithm, jetRadius[k]);
      fastjet::ClusterSequence genJetClusterSequence = JetMaker(genJetsConst, CA_def);
      vector<fastjet::PseudoJet> myJets = SelectByAcceptance(fastjet::sorted_by_pt(genJetClusterSequence.inclusive_jets()),100.,8.0);
      fastjet::Pruner pruner(CA_def, 0.1, 0.25);
      if(myJets.size()<2) continue;
      // take the two highest-pT jets

      // pruned tau2/tau1 1st jet
      fastjet::PseudoJet J1 = myJets[0];
      fastjet::PseudoJet p1 = pruner(J1);
      JetSubstructure* subStruct1 = new JetSubstructure(J1,genJetsConst,jetRadius[k]);
      JetSubstructure* subStruct1_Pruned = new JetSubstructure(p1,genJetsConst,jetRadius[k]);
      Tau21 = subStruct1_Pruned->Nsubjettiness(2)/subStruct1_Pruned->Nsubjettiness(1);
      PMass = p1.m();
      RawMass = J1.m();
      // Fill Trees
      //      PMassTau21[k]->Fill();
      //      PMassTau21Mass[k]->Fill();
      // Fill Histograms
      moverpGenJet[k]->Fill(RawMass/J1.pt());
      moverpPrunedGenJet[k]->Fill(PMass/p1.pt());
      massGenJet[k]->Fill(RawMass);
      massPrunedGenJet[k]->Fill(PMass);
      massGenJet_WideRange[k]->Fill(RawMass);
      massPrunedGenJet_WideRange[k]->Fill(PMass);
      tau21[k]->Fill(subStruct1->Nsubjettiness(2)/subStruct1->Nsubjettiness(1));
      tau21_Pruned[k]->Fill(Tau21);
      if(PMass>70 && PMass <100.) tau21_Pruned_WithMassCut[k]->Fill(Tau21);

      // pruned tau2/tau1 2nd jet
      fastjet::PseudoJet J2 = myJets[1];
      fastjet::PseudoJet p2 = pruner(J2);
      JetSubstructure* subStruct2 = new JetSubstructure(J2,genJetsConst,jetRadius[k]);      
      JetSubstructure* subStruct2_Pruned = new JetSubstructure(p2,genJetsConst,jetRadius[k]);      
      Tau21 = subStruct1_Pruned->Nsubjettiness(2)/subStruct1_Pruned->Nsubjettiness(1);
      PMass = p2.m();
      RawMass = J2.m();
      // Fill Trees
      //      PMassTau21[k]->Fill();
      //      PMassTau21Mass[k]->Fill();
      // Fill Histograms
      moverpGenJet[k]->Fill(RawMass/J2.pt());
      moverpPrunedGenJet[k]->Fill(PMass/p2.pt());
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
    if(tracks.size() <= 0) continue;
    for(int k=0; k<iRad; k++) {
      fastjet::JetDefinition CA_def(fastjet::cambridge_algorithm, jetRadius[k]);
      fastjet::ClusterSequence genJetClusterSequence = JetMaker(tracks, CA_def);
      vector<fastjet::PseudoJet> myJets = SelectByAcceptance(fastjet::sorted_by_pt(genJetClusterSequence.inclusive_jets()),100.,8.0);
      fastjet::Pruner pruner(CA_def, 0.1, 0.25);
      if(myJets.size()<2) continue;


      // pruned tau2/tau1 1st jet
      fastjet::PseudoJet J1 = myJets[0];
      fastjet::PseudoJet p1 = pruner(J1);
      JetSubstructure* subStruct1 = new JetSubstructure(J1,genJetsConst,jetRadius[k]);
      JetSubstructure* subStruct1_Pruned = new JetSubstructure(p1,genJetsConst,jetRadius[k]);
      Tau21 = subStruct1_Pruned->Nsubjettiness(2)/subStruct1_Pruned->Nsubjettiness(1);
      PMass = p1.m();
      RawMass = J1.m();
      // Fill Trees
      //      TRKPMassTau21[k]->Fill();
      //      TRKPMassTau21Mass[k]->Fill();
      // Fill Histograms
      TRKmoverpGenJet[k]->Fill(RawMass/J1.pt());
      TRKmassGenJet[k]->Fill(RawMass);
      TRKmassPrunedGenJet[k]->Fill(PMass);
      TRKmassGenJet_WideRange[k]->Fill(RawMass);
      TRKmassPrunedGenJet_WideRange[k]->Fill(PMass);
      TRKtau21[k]->Fill(subStruct1->Nsubjettiness(2)/subStruct1->Nsubjettiness(1));
      TRKtau21_Pruned[k]->Fill(Tau21);
      if(PMass>70 && PMass <100.) TRKtau21_Pruned_WithMassCut[k]->Fill(Tau21);

      // pruned tau2/tau1 2nd jet
      fastjet::PseudoJet J2 = myJets[1];
      fastjet::PseudoJet p2 = pruner(J2);
      JetSubstructure* subStruct2 = new JetSubstructure(J2,genJetsConst,jetRadius[k]);      
      JetSubstructure* subStruct2_Pruned = new JetSubstructure(p2,genJetsConst,jetRadius[k]);      
      Tau21 = subStruct1_Pruned->Nsubjettiness(2)/subStruct1_Pruned->Nsubjettiness(1);
      PMass = p2.m();
      RawMass = J2.m();
      // Fill Trees
      //      TRKPMassTau21[k]->Fill();
      //      TRKPMassTau21Mass[k]->Fill();
      // Fill Histograms
      TRKmoverpGenJet[k]->Fill(RawMass/J2.pt());
      TRKmassGenJet[k]->Fill(RawMass);
      TRKmassGenJet_WideRange[k]->Fill(RawMass);
      TRKmassPrunedGenJet[k]->Fill(PMass);
      TRKmassPrunedGenJet_WideRange[k]->Fill(PMass);
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


    // TrkJets [perfect resolution]
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
      vector<fastjet::PseudoJet> myJets = SelectByAcceptance(fastjet::sorted_by_pt(genJetClusterSequence.inclusive_jets()),100.,8.0);
      fastjet::Pruner pruner(CA_def, 0.1, 0.25);
      if(myJets.size()<2) continue;


      // pruned tau2/tau1 1st jet
      fastjet::PseudoJet J1 = myJets[0];
      fastjet::PseudoJet p1 = pruner(J1);
      JetSubstructure* subStruct1 = new JetSubstructure(J1,genJetsConst,jetRadius[k]);
      JetSubstructure* subStruct1_Pruned = new JetSubstructure(p1,genJetsConst,jetRadius[k]);
      Tau21 = subStruct1_Pruned->Nsubjettiness(2)/subStruct1_Pruned->Nsubjettiness(1);
      PMass = p1.m();
      RawMass = J1.m();
      // Fill Trees
      //      TRKPMassTau21[k]->Fill();
      //      TRKPMassTau21Mass[k]->Fill();
      // Fill Histograms
      EGTRKmoverpGenJet[k]->Fill(RawMass/J1.pt());
      EGTRKmassGenJet[k]->Fill(RawMass);
      EGTRKmassPrunedGenJet[k]->Fill(PMass);
      EGTRKmassGenJet_WideRange[k]->Fill(RawMass);
      EGTRKmassPrunedGenJet_WideRange[k]->Fill(PMass);
      EGTRKtau21[k]->Fill(subStruct1->Nsubjettiness(2)/subStruct1->Nsubjettiness(1));
      EGTRKtau21_Pruned[k]->Fill(Tau21);
      if(PMass>70 && PMass <100.) EGTRKtau21_Pruned_WithMassCut[k]->Fill(Tau21);

      // pruned tau2/tau1 2nd jet
      fastjet::PseudoJet J2 = myJets[1];
      fastjet::PseudoJet p2 = pruner(J2);
      JetSubstructure* subStruct2 = new JetSubstructure(J2,genJetsConst,jetRadius[k]);      
      JetSubstructure* subStruct2_Pruned = new JetSubstructure(p2,genJetsConst,jetRadius[k]);      
      Tau21 = subStruct1_Pruned->Nsubjettiness(2)/subStruct1_Pruned->Nsubjettiness(1);
      PMass = p2.m();
      RawMass = J2.m();
      // Fill Trees
      //      EGTRKPMassTau21[k]->Fill();
      //      EGTRKPMassTau21Mass[k]->Fill();
      // Fill Histograms
      EGTRKmoverpGenJet[k]->Fill(RawMass/J2.pt());
      EGTRKmassGenJet[k]->Fill(RawMass);
      EGTRKmassGenJet_WideRange[k]->Fill(RawMass);
      EGTRKmassPrunedGenJet[k]->Fill(PMass);
      EGTRKmassPrunedGenJet_WideRange[k]->Fill(PMass);
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
  }


  TFile *fileOUT = new TFile(outFileName.c_str(),"RECREATE");
  // GEN PLOTS
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
  // for(int j=0; j<iRad; j++) {
  //   PMassTau21[j]->Write();
  //   PMassTau21Mass[j]->Write();
  //   TRKPMassTau21[j]->Write();
  // }
  fileOUT->Close();
}

