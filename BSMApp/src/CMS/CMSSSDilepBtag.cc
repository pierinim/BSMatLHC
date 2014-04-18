#include <string>
#include <iostream>
#include <TTree.h>
#include <TFile.h>
#include "CMS/CMSSSDilepBtag.hh"

// THIS IS THE IMPLEMENTATION OF SUS-11-020
// http://arxiv.org/pdf/1205.3933.pdf

CMSSSDilepBtag::CMSSSDilepBtag(TTree *tree, string ModelName, double Lumi, string analysis) : CMSReco(tree) {
  _ModelName = ModelName;
  char name[256];
  // TO CHANGE
  sprintf(name, "data/%s.root", analysis.c_str());
  _fileLikelihood = TFile::Open(name);
  _Ps0 = (TH1D*) _fileLikelihood->Get("SR0");
  _Ps1 = (TH1D*) _fileLikelihood->Get("SR1");
  _Ps2 = (TH1D*) _fileLikelihood->Get("SR2");
  _Ps3 = (TH1D*) _fileLikelihood->Get("SR3");
  _Ps4 = (TH1D*) _fileLikelihood->Get("SR4");
  _Ps5 = (TH1D*) _fileLikelihood->Get("SR5");
  _Ps6 = (TH1D*) _fileLikelihood->Get("SR6");
  _Ps7 = (TH1D*) _fileLikelihood->Get("SR7");
  _Ps8 = (TH1D*) _fileLikelihood->Get("SR8");
  _Lumi = Lumi;
  _statTools = new StatTools(-99);
  verbose = false;
}

CMSSSDilepBtag::~CMSSSDilepBtag(){
  _fileLikelihood->Close();
  delete _statTools;
}

// loop over events - real analysis
void CMSSSDilepBtag::Loop() {

  if(fChain == 0) return;

  // number of events passing the selection
  double Nsr[9];
  Nsr[0] = 0;
  Nsr[1] = 0;
  Nsr[2] = 0;
  Nsr[3] = 0;
  Nsr[4] = 0;
  Nsr[5] = 0;
  Nsr[6] = 0;
  Nsr[7] = 0;
  Nsr[8] = 0;
  
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
    
    vector<TLorentzVector> recoJets = SelectByAcceptance(genJet,40., 2.5);
    double GenHTValue = CalcHT(recoJets);
    double GenMetValue = genMET.Pt();

    // at least two jets
    if(recoJets.size() < 2.) continue;

    // at least two SS leptons
    // since we need the charges, we do hit or miss
    int ChLepPlus = 0;
    int ChLepMinus = 0;
    for(int i=0; i<Muon;i++) {
      TLorentzVector mu(MuonPx[i], MuonPy[i], MuonPz[i], MuonE[i]);
      if(fabs(mu.Eta())>2.4) continue;
      double wMu = weightMuon(mu.Pt());
      if(gRandom->Rndm() <= wMu) {
	if(MuonPdgId[i]>0) ChLepPlus++;
	else ChLepMinus++;
      }
    }
    for(int i=0; i<Electron;i++) {
      TLorentzVector ele(ElectronPx[i], ElectronPy[i], ElectronPz[i], ElectronE[i]);
      if(fabs(ele.Eta())>2.4) continue;
      if(fabs(ele.Eta())>1.442 && fabs(ele.Eta())<1.566) continue;
      double wEle = weightElectron(sqrt(pow(double(ElectronPx[i]),2)+pow(double(ElectronPy[i]),2.)));
      if(gRandom->Rndm() <= wEle) {
	if(ElectronPdgId[i]>0) ChLepPlus++;
	else ChLepMinus++;
      }
    }

    // at least two SS leptons
    if(ChLepPlus<2 && ChLepMinus<2) continue;
    bool PlusPlus = false;
    if(ChLepPlus>=2) PlusPlus = true;

    // compute the btag weight
    int nBtag = 0.;
    for(int i=0; i<recoJets.size(); i++) {
      if(IsBJet(recoJets[i],0.5,20.) && fabs(recoJets[i].Eta())<2.4 && gRandom->Rndm() <= weightBtag(recoJets[i].Pt())) nBtag ++;
    }
    // at least two btags
    if(nBtag < 2) continue;
    
    bool GenMet30 = weightMET(GenMetValue,30.);
    bool GenMet50 = weightMET(GenMetValue,50.);
    bool GenMet120 = weightMET(GenMetValue,120.);

    bool GenHT200 = weightHT(GenHTValue,200.);
    bool GenHT320 = weightHT(GenHTValue,320.);

    // SR yields
    Nsr[0] ++;
    Nsr[1] += GenMet30;
    Nsr[2] += GenMet30*PlusPlus;
    Nsr[3] += GenMet120*GenHT200;
    Nsr[4] += GenMet50*GenHT200;
    Nsr[5] += GenMet50*GenHT320;
    Nsr[6] += GenMet120*GenHT320;
    if(nBtag > 2) Nsr[7] += GenMet50*GenHT200;
    Nsr[8] += GenHT320;
  }
 
  TH1D* Ps[9];
  Ps[0] = _statTools->LogNormHistoConv(_Ps0,0.3);
  Ps[1] = _statTools->LogNormHistoConv(_Ps1,0.3);
  Ps[2] = _statTools->LogNormHistoConv(_Ps2,0.3);
  Ps[3] = _statTools->LogNormHistoConv(_Ps3,0.3);
  Ps[4] = _statTools->LogNormHistoConv(_Ps4,0.3);
  Ps[5] = _statTools->LogNormHistoConv(_Ps5,0.3);
  Ps[6] = _statTools->LogNormHistoConv(_Ps6,0.3);
  Ps[7] = _statTools->LogNormHistoConv(_Ps7,0.3);
  Ps[8] = _statTools->LogNormHistoConv(_Ps8,0.3);

  double xsec95CL = 9999999999999999.;
  double limits[9];
  for(int i=0; i<9; i++) {    
    // xsec-to-yield scale factor
    double AccLumi = double(Nsr[i])/nentries*_Lumi;
    // find the excluded xsec at 95% CL
    double THISxsec95CL = _statTools->FindUL(Ps[i], 0.95, 1./AccLumi);
    cout << THISxsec95CL* AccLumi << endl;
    limits[i] = THISxsec95CL;
    if(THISxsec95CL < xsec95CL) {
      xsec95CL = THISxsec95CL;
    }
  }
  cout << "Model = "<< _ModelName << endl;
  for(int i=0; i<9; i++) {
    cout << "SR" << i << " Eff = " << double(Nsr[i])/nentries;
    cout << " Limit = " << limits[i] << " pb-1" << endl;
  }
  cout << "SSDilepBtag Xsec@95% Prob. [pb-1] = " <<  xsec95CL << endl;
}

double CMSSSDilepBtag::weightBtag(double thisPt) {
  if(thisPt<90.) return 0.62+0.0051*(thisPt-90.);
  else if(thisPt<170.) return 0.62;
  else return 0.62-0.0012*(thisPt-170.);
}

double CMSSSDilepBtag::weightElectron(double thisPt) {
  if(thisPt<20.) return 0.;
  return 0.66*erf((thisPt-20.)/32.) + 0.32*(1.-erf((thisPt-20.)/32.));
}

double CMSSSDilepBtag::weightMuon(double thisPt) {
  if(thisPt<20.) return 0.;
  return 0.67*erf((thisPt-20.)/23.) + 0.44*(1.-erf((thisPt-20.)/23.));
}

double CMSSSDilepBtag::weightMET(double thisMET, double METmin) {
  double y = 0.;
  if(METmin == 30.)  y = turnOn(thisMET, 13., 44.);
  else if(METmin == 50.) y =  turnOn(thisMET, 43., 39.);
  else if(METmin == 120.) y = turnOn(thisMET, 123., 37.);
  else {
    cout << "No turn-on curve is given for METcut " << thisMET << endl;
    return 0.;
  }
  if(gRandom->Rndm() <=  y) return 1.;
  return 0.;
}

double CMSSSDilepBtag::weightHT(double thisHT, double HTmin) {
  double y = 0.;  
  if(HTmin == 200.) y = turnOn(thisHT, 188., 88.);
  else if(HTmin == 320.) y = turnOn(thisHT, 308., 102.);
  else {
    cout << "No turn-on curve is given for HTcut " << thisHT << endl;
    return 0.;
  }
  if(gRandom->Rndm() <=  y) return 1.;
  return 0.;
}

double CMSSSDilepBtag::turnOn(double x, double x12, double sigma) {
  return 0.5*(erf((x-x12)/sigma)+1.);
}
