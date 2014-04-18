#include "CommonTools/DetectorResponse.hh"

#include <stdio.h>

using namespace std;
using namespace stdcomb;

DetectorResponse::DetectorResponse(int seed) {
  
  // intialize the seed
  if(seed < 0){
    int jobpid = getpid();
    TDatime *now = new TDatime();
    int today = now->GetDate();
    int clock = now->GetTime();
    int myseed = today+clock+jobpid;
    gRandom = new TRandom3(myseed);
  } else {
    gRandom = new TRandom3(seed);
  }
}

DetectorResponse::~DetectorResponse() {
}

void DetectorResponse::ReadDetectorCard(string fileName) {

  ifstream myReadFile;
  myReadFile.open(fileName.c_str());
  char ID1[30];
  char ID2[30];
  char thisFORMULA[200];
  vector<string> NAME;
  vector<string> FORMULA;
  if (myReadFile.is_open()) {
    while (!myReadFile.eof()) {
      myReadFile >> ID1 >> ID2 >> thisFORMULA;
      NAME.push_back(string(ID1)+string("_")+string(ID2));
      FORMULA.push_back(string(thisFORMULA));
    }
  }
  for(int i=0; i<FORMULA.size(); i++) {
    if(NAME[i] == "TRACK_PT") _ptResFunTRACK = new TF1("ptResFunTRACKS",FORMULA[i].c_str(),0.,100000.);
    if(NAME[i] == "TRACK_ETA") _etaResFunTRACK = new TF1("etaResFunTRACKS",FORMULA[i].c_str(),0.,100000.);
    if(NAME[i] == "TRACK_PHI") _phiResFunTRACK = new TF1("phiResFunTRACKS",FORMULA[i].c_str(),0.,100000.);
    //
    if(NAME[i] == "ELECTRON_PT") _ptResFunELECTRON = new TF1("ptResFunELECTRON",FORMULA[i].c_str(),0.,100000.);
    if(NAME[i] == "ELECTRON_ETA") _etaResFunELECTRON = new TF1("etaResFunELECTRON",FORMULA[i].c_str(),0.,100000.);
    if(NAME[i] == "ELECTRON_PHI") _phiResFunELECTRON = new TF1("phiResFunELECTRON",FORMULA[i].c_str(),0.,100000.);
    //
    if(NAME[i] == "PHOTON_PT") _ptResFunPHOTON = new TF1("ptResFunPHOTON",FORMULA[i].c_str(),0.,100000.);
    if(NAME[i] == "PHOTON_ETA") _etaResFunPHOTON = new TF1("etaResFunPHOTON",FORMULA[i].c_str(),0.,100000.);
    if(NAME[i] == "PHOTON_PHI") _phiResFunPHOTON = new TF1("phiResFunPHOTON",FORMULA[i].c_str(),0.,100000.);
    //
    if(NAME[i] == "MUON_PT") _ptResFunMUON = new TF1("ptResFunMUON",FORMULA[i].c_str(),0.,100000.);
    if(NAME[i] == "MUON_ETA") _etaResFunMUON = new TF1("etaResFunMUON",FORMULA[i].c_str(),0.,100000.);
    if(NAME[i] == "MUON_PHI") _phiResFunMUON = new TF1("phiResFunMUON",FORMULA[i].c_str(),0.,100000.);
    //
    if(NAME[i] == "ChHADRON_PT") _ptResFunChHAD = new TF1("ptResFunChHAD",FORMULA[i].c_str(),0.,100000.);
    if(NAME[i] == "ChHADRON_ETA") _etaResFunChHAD = new TF1("etaResFunChHAD",FORMULA[i].c_str(),0.,100000.);
    if(NAME[i] == "ChHADRON_PHI") _phiResFunChHAD = new TF1("phiResFunChHAD",FORMULA[i].c_str(),0.,100000.);
    //
    if(NAME[i] == "NeuHADRON_PT") _ptResFunNeuHAD = new TF1("ptResFunNeuHAD",FORMULA[i].c_str(),0.,100000.);
    if(NAME[i] == "NeuHADRON_ETA") _etaResFunNeuHAD = new TF1("etaResFunNeuHAD",FORMULA[i].c_str(),0.,100000.);
    if(NAME[i] == "NeuHADRON_PHI") _phiResFunNeuHAD = new TF1("phiResFunNeuHAD",FORMULA[i].c_str(),0.,100000.);
    //
    if(NAME[i] == "CALOJET_PT") _ptResFunCALOJET = new TF1("ptResFunCALOJET",FORMULA[i].c_str(),0.,100000.);
    if(NAME[i] == "CALOJET_ETA") _etaResFunCALOJET = new TF1("etaResFunCALOJET",FORMULA[i].c_str(),0.,100000.);
    if(NAME[i] == "CALOJET_PHI") _phiResFunCALOJET = new TF1("phiResFunCALOJET",FORMULA[i].c_str(),0.,100000.);
    //
    if(NAME[i] == "CALOMET_PT") _ptResFunCALOMET = new TF1("ptResFunCALOMET",FORMULA[i].c_str(),0.,100000.);
    if(NAME[i] == "CALOMET_PHI") _phiResFunCALOMET = new TF1("phiResFunCALOMET",FORMULA[i].c_str(),0.,100000.);
    //
    if(NAME[i] == "PFJET_PT") _ptResFunPFJET = new TF1("ptResFunPFJET",FORMULA[i].c_str(),0.,100000.);
    if(NAME[i] == "PFJET_ETA") _etaResFunPFJET = new TF1("etaResFunPFJET",FORMULA[i].c_str(),0.,100000.);
    if(NAME[i] == "PFJET_PHI") _phiResFunPFJET = new TF1("phiResFunPFJET",FORMULA[i].c_str(),0.,100000.);
    //
    if(NAME[i] == "PFMET_PT") _ptResFunPFMET = new TF1("ptResFunPFMET",FORMULA[i].c_str(),0.,100000.);
    if(NAME[i] == "PFMET_PHI") _phiResFunPFMET = new TF1("phiResFunPFMET",FORMULA[i].c_str(),0.,100000.);
    //
    if(NAME[i] == "TAU_PT") _ptResFunTAU = new TF1("ptResFunTAU",FORMULA[i].c_str(),0.,100000.);
    if(NAME[i] == "TAU_ETA") _etaResFunTAU = new TF1("etaResFunTAU",FORMULA[i].c_str(),0.,100000.);
    if(NAME[i] == "TAU_PHI") _phiResFunTAU = new TF1("phiResFunTAU",FORMULA[i].c_str(),0.,100000.);
  }
}



TF1* DetectorResponse::SetResolutionFunction(string name, vector<double> pars, double xmin, double xmax) {
  int nPars = int(pars.size());
  string function = "[0]+";
  for(int i=1; i<nPars; i++) {
    char* thisPar;
    sprintf(thisPar, "+[%i]",i);
    function = function + string(thisPar);
    for(int j=0; j<i; j++) function = function+"*x";
  }
  TF1* f1 = new TF1(name.c_str(), function.c_str(), xmin, xmax);
  for(int i=0; i<nPars; i++) f1->SetParameter(i, pars[i]);
  return f1;
}

TLorentzVector DetectorResponse::SmearNoBias(TLorentzVector pIN, TH1D* response) {
  TLorentzVector pOUT = pIN;
  double smear = SmearNoBias(pIN.Pt(), response);
  pOUT.SetPtEtaPhiE(smear, pIN.Eta(), pIN.Phi(), smear/pIN.Pt()*pIN.E());
  return pOUT;
}

double DetectorResponse::SmearNoBias(double pIN, TH1D* response) {
  int ibin = response->FindBin(pIN);
  double mean = pIN;
  double sigma = response->GetBinContent(ibin);
  double smear = gRandom->Gaus(mean,sigma);
  return smear;
}

