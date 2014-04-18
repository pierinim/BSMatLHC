#include <string>
#include <iostream>
#include <TTree.h>
#include "CMS/CMSRazor.hh"
#include <fastjet/tools/Pruner.hh>

CMSRazor::CMSRazor(TTree *tree, double Lumi, string analysis) : CMSReco(tree) {
  _Lumi = Lumi;
  _statTools = new StatTools(-99);
  _analysis = analysis;
}

CMSRazor::~CMSRazor(){
}

void CMSRazor::SetSqrts(double sqrts) {
  _sqrts = sqrts;
}

// loop over events - real analysis
void CMSRazor::Loop(string outFileName) {

  if(fChain == 0) return;

  double MR, RSQ, MRNEW, RSQNEW;
  int BOX_NUM;
  double W_EFF;

  // Open Output file
  TFile *file = new TFile(outFileName.c_str(),"UPDATE");

  TTree* outTree = new TTree("RazorInclusive","RazorInclusive");
  outTree->Branch("MR", &MR, "MR/D");
  outTree->Branch("RSQ", &RSQ, "RSQ/D");
  outTree->Branch("MRNEW", &MRNEW, "MRNEW/D");
  outTree->Branch("RSQNEW", &RSQNEW, "RSQNEW/D");
  outTree->Branch("BOX_NUM", &BOX_NUM, "BOX_NUM/I");
  outTree->Branch("W_EFF", &W_EFF, "W_EFF/D");

  double xedge[17] = {300, 350, 400.,450.,500.,550.,600.,650.,700.,800.,900.,1000.,1200.,1600.,2000.,2800.,3500.};
  double yedge[6] = {0.11,0.18,0.20,0.30,0.40,0.50};
  TH2D* pdfHad = new TH2D("pdfHad","pdfHad",16,xedge,5,yedge);
  TH2D* pdfMuMu = new TH2D("pdfMuMu","pdfMuEle",16,xedge,5,yedge);
  TH2D* pdfMuEle = new TH2D("pdfMuEle","pdfMuEle",16,xedge,5,yedge);
  TH2D* pdfMu = new TH2D("pdfMu","pdfMu",16,xedge,5,yedge);
  TH2D* pdfEleEle = new TH2D("pdfEleEle","pdfEleEle",16,xedge,5,yedge);
  TH2D* pdfEle = new TH2D("pdfEle","pdfEle",16,xedge,5,yedge);

  // loop over entries
  Long64_t nbytes = 0, nb = 0;
  Long64_t nentries = fChain->GetEntries();
  std::cout << "Number of entries = " << nentries << std::endl;

  // set the by-event weight
  W_EFF = 1./nentries;
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

    if(pfAK04.size()<2) continue;

    GenMET();
    PFMET = genMET;

    // Ele reco: WP80 and WP95
    EleReco();

    //cout << "Ele Done" << endl;

    // Mu reco: Tight and Loose
    MuReco();
    
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
    
    // Boxes
    BOX_NUM = 5; // Had by default
    if(MUELEBox()) BOX_NUM = 0;
    else if(MUMUBox()) BOX_NUM = 1;
    else if(ELEELEBox()) BOX_NUM = 2;
    else if(MUBox()) BOX_NUM = 3;
    else if(ELEBox()) BOX_NUM = 4;

    // write event in the tree
    outTree->Fill();

    // fill PDF histograms
    bool fillBox = SignalRegion(MR, RSQ, BOX_NUM);
    if(BOX_NUM == 0 && fillBox) pdfMuEle->Fill(MR, RSQ);
    if(BOX_NUM == 1 && fillBox) pdfMuMu->Fill(MR, RSQ);
    if(BOX_NUM == 2 && fillBox) pdfEleEle->Fill(MR, RSQ);
    if(BOX_NUM == 3 && fillBox) pdfMu->Fill(MR, RSQ);
    if(BOX_NUM == 4 && fillBox) pdfEle->Fill(MR, RSQ);
    if(BOX_NUM == 5 && fillBox) pdfHad->Fill(MR, RSQ);

  }

  // full event TTree
  outTree->Write();
  
  // eff TTree
  double effMuEle = pdfMuEle->Integral()/double(nentries);
  double effMuMu = pdfMuMu->Integral()/double(nentries);
  double effMu = pdfMu->Integral()/double(nentries);
  double effEleEle = pdfEleEle->Integral()/double(nentries);
  double effEle = pdfEle->Integral()/double(nentries);
  double effHad = pdfHad->Integral()/double(nentries);

  // normalize the PDFs
  if(pdfMuEle->Integral()>0)  pdfMuEle->Scale(1./pdfMuEle->Integral());
  if(pdfMuMu->Integral()>0)  pdfMuMu->Scale(1./pdfMuMu->Integral());
  if(pdfMu->Integral()>0)  pdfMu->Scale(1./pdfMu->Integral());
  if(pdfEle->Integral()>0)  pdfEle->Scale(1./pdfEle->Integral());
  if(pdfEleEle->Integral()>0)  pdfEleEle->Scale(1./pdfEleEle->Integral());
  if(pdfHad->Integral()>0)  pdfHad->Scale(1./pdfHad->Integral());

  // write the PDFs
  pdfMuEle->Write();  
  pdfMuMu->Write();
  pdfMu->Write();
  pdfEle->Write();
  pdfEleEle->Write();
  pdfHad->Write();

  char name[256];
  sprintf(name,"data/%s.root", _analysis.c_str());
  //  TH1D* xsecProb = XsecProb(pdfHad, effHad,name, 1000, 0., 1.);
  // Open Output file again 
  file->cd();
  double xsecULHad = 0.;//_statTools->FindUL(xsecProb, 0.95, 1.);

  TTree* effTree = new TTree("RazorInclusiveEfficiency","RazorInclusiveEfficiency");
  effTree->Branch("effMuEle", &effMuEle, "effMuEle/D");
  effTree->Branch("effMuMu", &effMuMu, "effMuMu/D");
  effTree->Branch("effEleEle", &effEleEle, "effEleEle/D");
  effTree->Branch("effMu", &effMu, "effMu/D");
  effTree->Branch("effEle", &effEle, "effEle/D");
  effTree->Branch("effHad", &effHad, "effHad/D");
  effTree->Branch("xsecULHad", &xsecULHad, "xsecULHad/D");
  effTree->Fill();
  effTree->Write();

  //  xsecProb->Write();
  file->Close();

}

bool CMSRazor::ELEELEBox() {
  int iEle = 0;
  for(int j=0; j< EleWP95.size(); j++) {
    if(EleWP95[j].Pt()>10.) iEle++;
  }
  return ELEBox()*(iEle>1? true : false);
}

bool CMSRazor::MUBox() {
  int iMu = 0;
  for(int i=0; i< TightMu.size(); i++) {
    if(TightMu[i].Pt()>12.) iMu++;
  }
  return (iMu>0 ? true : false);
}

bool CMSRazor::ELEBox() {
  int iEle = 0;
  for(int i=0; i< EleWP80.size(); i++) {
    if(EleWP80[i].Pt()>20.) iEle++;
  }
  return (iEle>0 ? true : false);
}

bool CMSRazor::MUELEBox() {
  return MUBox()*ELEBox();
}

bool CMSRazor::MUMUBox() {
  int iMu = 0;
  for(int i=0; i< LooseMu.size(); i++) {
    if(LooseMu[i].Pt()>10.) iMu++;
  }
  if(iMu<2) return false;
  iMu = 0;
  for(int i=0; i< TightMu.size(); i++) {
    if(TightMu[i].Pt()>15.) iMu++;
  }
  if(iMu<1) return false;
  return true;
}

bool CMSRazor::SignalRegion(double mr, double rsq, double ibox){
  if(ibox == 4 || ibox == 3) return SignalRegionLep(mr, rsq);
  else if(ibox == 5) return SignalRegionHad(mr, rsq);
  else if(ibox >=0 && ibox <=2) return SignalRegionDiLep(mr, rsq);
  cout <<"Error on CMSRazor::SignalRegion : invalid box number " << ibox << endl;
  return false;
}

bool CMSRazor::SignalRegionHad(double mr, double rsq){
  // tighter baseline cuts
  if(rsq<0.18) return false;
  if(mr<500.) return false;
  return SignalRegionLep(mr, rsq);
}

bool CMSRazor::SignalRegionLep(double mr, double rsq){
  if(rsq>0.5) return false;
  if(rsq<0.11) return false;
  if(mr>1000.) return true;
  if(rsq>0.2 && mr>650.) return true;
  if(rsq>0.3 && mr>450.) return true; 
  return false;
}

bool CMSRazor::SignalRegionDiLep(double mr, double rsq){
  if(rsq>0.5) return false;
  if(rsq<0.11) return false;
  if(mr>650.) return true;
  if(rsq>0.2 && mr>450.) return true;
  if(rsq>0.3 && mr>400.) return true; 
  return false;
}

TH1D* CMSRazor::XsecProb(TH2D* sigPdf, double eff, TString Filename, int ibin, double xmin, double xmax) {

  int ibinX = sigPdf->GetXaxis()->GetNbins();
  int ibinY = sigPdf->GetYaxis()->GetNbins();

  TH1D* probVec = new TH1D("probVec", "probVec", ibin, xmin, xmax);

  TFile* likFile = new TFile(Filename);  
  gROOT->cd();
  // a loop over xsec should go here... 
  for(int i=0; i<ibin; i++) {
    double xsec = xmin + (i+0.5)/ibin*(xmax-xmin);
    double prob = 1;
    for(int ix=0; ix<ibinX; ix++) {
      for(int iy=0; iy<ibinY; iy++) {
	double sBin = _Lumi*xsec*eff*sigPdf->GetBinContent(ix,iy);
	if(sBin <= 0.) continue;
	char name[256];
	sprintf(name, "lik_%i_%i", ix, iy);
	TH1D* binProb = (TH1D*) likFile->Get(name);
	if(prob < 10.e-30) prob = 0.;
	if(prob <= 0) continue;
	prob *= binProb->GetBinContent(binProb->FindBin(sBin));
	delete binProb;
      }
    }
    probVec->SetBinContent(i+1,prob);
  }
  likFile->Close();
  return probVec;
}
