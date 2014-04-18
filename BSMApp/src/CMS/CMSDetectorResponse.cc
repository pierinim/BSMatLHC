#include "CMS/CMSDetectorResponse.hh"

using namespace std;
using namespace stdcomb;

CMSDetectorResponse::CMSDetectorResponse(int seed) {
  
  // intialize the seed
  if(seed < 0){
    int jobpid = getpid();
    TDatime *now = new TDatime();
    int today = now->GetDate();
    int clock = now->GetTime();
    int myseed = today+clock+jobpid;
    gRandom = new TRandom3(myseed);
    _statTools = new StatTools(myseed);
  } else {
    gRandom = new TRandom3(seed);
    _statTools = new StatTools(seed);
  }

  // get the CMS performance histograms
  TFile* CMSinput = new TFile("data/CMSDetector.root");
  
  // resolution
  CaloJetResponse_0p0_eta_1p4 = (TH1D*) CMSinput->Get("CaloJetResponse_0p0_eta_1p4RES");
  CaloJetResponse_1p4_eta_2p4 = (TH1D*) CMSinput->Get("CaloJetResponse_1p4_eta_2p4RES");
  CaloJetResponse_2p4_eta_3p0 = (TH1D*) CMSinput->Get("CaloJetResponse_2p4_eta_3p0RES");
  CaloJetResponse_3p0_eta_5p0 = (TH1D*) CMSinput->Get("CaloJetResponse_3p0_eta_5p0RES");
  PFJetResponse_0p0_eta_1p4 = (TH1D*) CMSinput->Get("PFJetResponse_0p0_eta_1p4RES");
  PFJetResponse_1p4_eta_2p4 = (TH1D*) CMSinput->Get("PFJetResponse_1p4_eta_2p4RES");
  PFJetResponse_2p4_eta_3p0 = (TH1D*) CMSinput->Get("PFJetResponse_2p4_eta_3p0RES");
  PFJetResponse_3p0_eta_5p0 = (TH1D*) CMSinput->Get("PFJetResponse_3p0_eta_5p0RES");
  PFMETResponse = (TH1D*) CMSinput->Get("PFMETResponseRES");
  CaloMETResponse = (TH1D*) CMSinput->Get("CaloMETResponseRES");
  EleResponse_Barrel = (TH1D*) CMSinput->Get("EleResponse_BarrelRES");
  EleResponse_Endcap = (TH1D*) CMSinput->Get("EleResponse_EndcapRES");
  MuResponse = (TH1D*) CMSinput->Get("MuResponseRES");

  // Efficiency
  TightMuEffLowGenIsoBarrel = (TGraphAsymmErrors*) CMSinput->Get("TightMuEffLowGenIsoBarrel");	
  TightMuEffMidGenIsoBarrel = (TGraphAsymmErrors*) CMSinput->Get("TightMuEffMidGenIsoBarrel");	
  TightMuEffHigGenIsoBarrel = (TGraphAsymmErrors*) CMSinput->Get("TightMuEffHigGenIsoBarrel");	
  TightMuEffLowGenIsoEndcap = (TGraphAsymmErrors*) CMSinput->Get("TightMuEffLowGenIsoEndcap");	
  TightMuEffMidGenIsoEndcap = (TGraphAsymmErrors*) CMSinput->Get("TightMuEffMidGenIsoEndcap");	
  TightMuEffHigGenIsoEndcap = (TGraphAsymmErrors*) CMSinput->Get("TightMuEffHigGenIsoEndcap");	
  LooseMuEffBarrel = (TGraphAsymmErrors*) CMSinput->Get("LooseMuEffBarrel");	
  LooseMuEffEndcap = (TGraphAsymmErrors*) CMSinput->Get("LooseMuEffEndcap");	
  WP80EleEffLowGenIsoBarrel = (TGraphAsymmErrors*) CMSinput->Get("WP80EleEffLowGenIsoBarrel");	
  WP80EleEffMidGenIsoBarrel = (TGraphAsymmErrors*) CMSinput->Get("WP80EleEffMidGenIsoBarrel");	
  WP80EleEffHigGenIsoBarrel = (TGraphAsymmErrors*) CMSinput->Get("WP80EleEffHigGenIsoBarrel");	
  WP80EleEffLowGenIsoEndcap = (TGraphAsymmErrors*) CMSinput->Get("WP80EleEffLowGenIsoEndcap");	
  WP80EleEffMidGenIsoEndcap = (TGraphAsymmErrors*) CMSinput->Get("WP80EleEffMidGenIsoEndcap");	
  WP80EleEffHigGenIsoEndcap = (TGraphAsymmErrors*) CMSinput->Get("WP80EleEffHigGenIsoEndcap");	
  WP95EleEffLowGenIsoBarrel = (TGraphAsymmErrors*) CMSinput->Get("WP95EleEffLowGenIsoBarrel");	
  WP95EleEffMidGenIsoBarrel = (TGraphAsymmErrors*) CMSinput->Get("WP95EleEffMidGenIsoBarrel");	
  WP95EleEffHigGenIsoBarrel = (TGraphAsymmErrors*) CMSinput->Get("WP95EleEffHigGenIsoBarrel");	
  WP95EleEffLowGenIsoEndcap = (TGraphAsymmErrors*) CMSinput->Get("WP95EleEffLowGenIsoEndcap");	
  WP95EleEffMidGenIsoEndcap = (TGraphAsymmErrors*) CMSinput->Get("WP95EleEffMidGenIsoEndcap");	
  WP95EleEffHigGenIsoEndcap = (TGraphAsymmErrors*) CMSinput->Get("WP95EleEffHigGenIsoEndcap");	

  // tracking eff vs transverse flight lenght
  double d0MAX[19];
  double trkEff[18];
  int i = 0;
  d0MAX[i] = 0;  i++;
  d0MAX[i] = 2;  trkEff[i-1] = 0.96; i++;
  d0MAX[i] = 4;  trkEff[i-1] = 0.93; i++;
  d0MAX[i] = 6;  trkEff[i-1] = 0.90; i++;
  d0MAX[i] = 8;  trkEff[i-1] = 0.85; i++;
  d0MAX[i] = 10; trkEff[i-1] = 0.80; i++;
  d0MAX[i] = 12; trkEff[i-1] = 0.78; i++;
  d0MAX[i] = 14; trkEff[i-1] = 0.75; i++;
  d0MAX[i] = 16; trkEff[i-1] = 0.73; i++;
  d0MAX[i] = 18; trkEff[i-1] = 0.70; i++;
  d0MAX[i] = 20; trkEff[i-1] = 0.65; i++;
  d0MAX[i] = 22; trkEff[i-1] = 0.55; i++;
  d0MAX[i] = 24; trkEff[i-1] = 0.43; i++;
  d0MAX[i] = 26; trkEff[i-1] = 0.41; i++;
  d0MAX[i] = 28; trkEff[i-1] = 0.27; i++;
  d0MAX[i] = 30; trkEff[i-1] = 0.10; i++;
  d0MAX[i] = 32; trkEff[i-1] = 0.04; i++;
  d0MAX[i] = 34; trkEff[i-1] = 0.01; i++;
  d0MAX[i] = 20000; trkEff[i-1] = 0.00; i++;
  trkEffvsd0 = new TH1D("trkEffvsd0", "trkEffvsd0", 18, d0MAX);
  for(int i=1; i<19;i++) {
    trkEffvsd0->SetBinContent(i,trkEff[i-1]);
  }
  
  // BTAG efficiency
  BTagEffCSVM_b = new TF1("BTagCSVM_b", "0.448485+0.00703298*x-6.25339e-05*x*x+2.6502e-07*x*x*x-6.00979e-10*x*x*x*x+6.8982e-13*x*x*x*x*x-3.13703e-16*x*x*x*x*x*x");
  BTagEffCSVM_c = new TF1("BTagCSVM_c", "0.133334+0.00149626*x-1.02697e-05*x*x+2.84023e-08*x*x*x-3.59024e-11*x*x*x*x+1.69781e-14*x*x*x*x*x");
  BTagEffCSVM_udsg = new TF1("BTagCSVM_udsg", "0.0807031+0.000477001*x-1.11788e-07*x*x");
  
  BTagEffHbb_H = new TF1("BTagEffHbb_H", "0.78126-0.000856154*max(300.,min(x,800.))+8.74252e-07*max(300.,min(x,800.))*max(300.,min(x,800.))");
  BTagEffHbb_Z = new TF1("BTagEffHbb_Z", "0.210992-0.000232036*max(300.,min(x,800.))+2.45799e-07*max(300.,min(x,800.))*max(300.,min(x,800.))");
  BTagEffHbb_t = new TF1("BTagEffHbb_t", "0.0626695-3.76002e-05*max(300.,min(x,800.))+1.78382e-07*max(300.,min(x,800.))*max(300.,min(x,800.))");
  BTagEffHbb_W = new TF1("BTagEffHbb_W", "0.303135-0.00179216*max(300.,min(x,800.))+3.59073e-06*pow(max(300.,min(x,800.)),2.)-2.09699e-09*pow(max(300.,min(x,800.)),3.)");
  BTagEffHbb_udcsg = new TF1("BTagEffHbb_udscg", "0.029146-5.73377e-05*max(300.,min(x,800.))+1.06809e-07*max(300.,min(x,800.))*max(300.,min(x,800.))");

}

CMSDetectorResponse::~CMSDetectorResponse() {
  delete _statTools;
  delete   CaloJetResponse_0p0_eta_1p4;
  delete   CaloJetResponse_1p4_eta_2p4;
  delete   CaloJetResponse_2p4_eta_3p0;
  delete   CaloJetResponse_3p0_eta_5p0;
  delete   PFJetResponse_0p0_eta_1p4;
  delete   PFJetResponse_1p4_eta_2p4;
  delete   PFJetResponse_2p4_eta_3p0;
  delete   PFJetResponse_3p0_eta_5p0;
  delete   PFMETResponse;
  delete   CaloMETResponse;
  delete   EleResponse_Barrel;
  delete   EleResponse_Endcap;
  delete   MuResponse;
  
  // Efficiency
  delete   TightMuEffLowGenIsoBarrel;
  delete   TightMuEffMidGenIsoBarrel;
  delete   TightMuEffHigGenIsoBarrel;
  delete   LooseMuEffBarrel;
  delete   LooseMuEffEndcap;
  delete   WP80EleEffLowGenIsoBarrel;
  delete   WP80EleEffMidGenIsoBarrel;
  delete   WP80EleEffHigGenIsoBarrel;
  delete   WP95EleEffLowGenIsoBarrel;
  delete   WP95EleEffMidGenIsoBarrel;
  delete   WP95EleEffHigGenIsoBarrel;
  delete   WP80EleEffLowGenIsoEndcap;
  delete   WP80EleEffMidGenIsoEndcap;
  delete   WP80EleEffHigGenIsoEndcap;
  delete   WP95EleEffLowGenIsoEndcap;
  delete   WP95EleEffMidGenIsoEndcap;
  delete   WP95EleEffHigGenIsoEndcap;
  
}

TLorentzVector CMSDetectorResponse::SmearNoBias(TLorentzVector pIN, TH1D* response) {
  TLorentzVector pOUT = pIN;
  double smear = SmearNoBias(pIN.Pt(), response);
  pOUT.SetPtEtaPhiE(smear, pIN.Eta(), pIN.Phi(), smear/pIN.Pt()*pIN.E());
  return pOUT;
}

double CMSDetectorResponse::SmearNoBias(double pIN, TH1D* response) {
  int ibin = response->FindBin(pIN);
  double mean = pIN;
  double sigma = response->GetBinContent(ibin);
  double smear = gRandom->Gaus(mean,sigma);
  return smear;
}

TLorentzVector CMSDetectorResponse::PFJetReco(TLorentzVector pIN) {
  if(fabs(pIN.Eta())<1.4) return SmearNoBias(pIN, PFJetResponse_0p0_eta_1p4);
  else if(fabs(pIN.Eta())<2.4) return SmearNoBias(pIN, PFJetResponse_1p4_eta_2p4);
  else if(fabs(pIN.Eta())<3.0) return SmearNoBias(pIN, PFJetResponse_2p4_eta_3p0);
  else if(fabs(pIN.Eta())<5.0) return SmearNoBias(pIN, PFJetResponse_3p0_eta_5p0);
  cout << "WARNING in CMSDetectorResponse::PFJetReco: Jet outside acceptance (Eta = " << pIN.Eta() << ")" << endl;
  return TLorentzVector(0.1, 0.0, 0.0, 0.1);
}

TLorentzVector CMSDetectorResponse::CaloJetReco(TLorentzVector pIN) {
  if(fabs(pIN.Eta())<1.4) return SmearNoBias(pIN, CaloJetResponse_0p0_eta_1p4);
  else if(fabs(pIN.Eta())<2.4) return SmearNoBias(pIN, CaloJetResponse_1p4_eta_2p4);
  else if(fabs(pIN.Eta())<3.0) return SmearNoBias(pIN, CaloJetResponse_2p4_eta_3p0);
  else if(fabs(pIN.Eta())<5.0) return SmearNoBias(pIN, CaloJetResponse_3p0_eta_5p0);
  cout << "WARNING in CMSDetectorResponse::CaloJetReco: Jet outside acceptance (Eta = " << pIN.Eta() << ")" << endl;
  return TLorentzVector(0.1, 0.0, 0.0, 0.1);
}

TLorentzVector CMSDetectorResponse::PFMETReco(TLorentzVector pIN) {
  return SmearNoBias(pIN, PFMETResponse);
}

TLorentzVector CMSDetectorResponse::CaloMETReco(TLorentzVector pIN) {
  return SmearNoBias(pIN, CaloMETResponse);
}

TLorentzVector CMSDetectorResponse::MuonReco(TLorentzVector pIN) {
  if(fabs(pIN.Eta())<2.1) return SmearNoBias(pIN, MuResponse);
  cout << "WARNING in CMSDetectorResponse::MuonReco: Muon outside acceptance (Eta = " << pIN.Eta() << ")" << endl;
  return TLorentzVector(0.1, 0.0, 0.0, 0.1);
}

TLorentzVector CMSDetectorResponse::ElectronReco(TLorentzVector pIN) {
  if(fabs(pIN.Eta())<1.4442) return SmearNoBias(pIN, EleResponse_Barrel);
  else if(fabs(pIN.Eta())>1.566 || fabs(pIN.Eta())<2.5) return SmearNoBias(pIN, EleResponse_Endcap);
  cout << "WARNING in CMSDetectorResponse::ElectronReco: Electron outside fiducial region (Eta = " << pIN.Eta() << ")" << endl;
  return TLorentzVector(0.1, 0.0, 0.0, 0.1);
}

bool CMSDetectorResponse::MuonEff(TLorentzVector pIN, double isoGen, string Selector) {
  if(Selector == "Loose") {
    if(fabs(pIN.Eta())>2.1) return false;
    else if(fabs(pIN.Eta())<1.4) return true;//_statTools->HitOrMiss(LooseMuEffBarrel->Eval(pIN.Pt()));
    else return _statTools->HitOrMiss(LooseMuEffEndcap->Eval(pIN.Pt()));
  } else if(Selector == "Tight") {
    if(fabs(pIN.Eta())>2.1) return false;
    else if(fabs(pIN.Eta())<1.4) {
      if(isoGen<0.10) return _statTools->HitOrMiss(TightMuEffLowGenIsoBarrel->Eval(pIN.Pt()));
      else if(isoGen<0.20) return _statTools->HitOrMiss(TightMuEffMidGenIsoBarrel->Eval(pIN.Pt()));
      else return _statTools->HitOrMiss(TightMuEffHigGenIsoBarrel->Eval(pIN.Pt()));
    } else {
      if(isoGen<0.10) return _statTools->HitOrMiss(TightMuEffLowGenIsoEndcap->Eval(pIN.Pt()));
      else if(isoGen<0.20) return _statTools->HitOrMiss(TightMuEffMidGenIsoEndcap->Eval(pIN.Pt()));
      else return _statTools->HitOrMiss(TightMuEffHigGenIsoEndcap->Eval(pIN.Pt()));
    }
  }  
  cout << "Error in CMSDetectorResponse::MuonEff: Selector " << Selector << " not known. Returning true" << endl;
  return true;
}

bool CMSDetectorResponse::EleEff(TLorentzVector pIN, double isoGen, string Selector) {
  if(Selector == "WP95") {
    if(fabs(pIN.Eta())>2.5 || (fabs(pIN.Eta())>1.4442 && fabs(pIN.Eta())<1.566)) return false;
    else if(fabs(pIN.Eta())<1.4) {
      if(isoGen<0.10) return _statTools->HitOrMiss(WP95EleEffLowGenIsoBarrel->Eval(pIN.Pt()));
      else if(isoGen<0.20) return _statTools->HitOrMiss(WP95EleEffMidGenIsoBarrel->Eval(pIN.Pt()));
      else return _statTools->HitOrMiss(0.0*WP95EleEffHigGenIsoBarrel->Eval(pIN.Pt()));
   } else {
      if(isoGen<0.10) return _statTools->HitOrMiss(WP95EleEffLowGenIsoEndcap->Eval(pIN.Pt()));
      else if(isoGen<0.20) return _statTools->HitOrMiss(WP95EleEffMidGenIsoEndcap->Eval(pIN.Pt()));
      else return _statTools->HitOrMiss(WP95EleEffHigGenIsoEndcap->Eval(pIN.Pt()));
    }
  } else if(Selector == "WP80") {
    if(fabs(pIN.Eta())>2.5 || (fabs(pIN.Eta())>1.4442 && fabs(pIN.Eta())<1.566)) return false;
    else if(fabs(pIN.Eta())<1.4) {
      if(isoGen<0.10) return _statTools->HitOrMiss(WP80EleEffLowGenIsoBarrel->Eval(pIN.Pt()));
      else if(isoGen<0.20) return _statTools->HitOrMiss(WP80EleEffMidGenIsoBarrel->Eval(pIN.Pt()));
      else return _statTools->HitOrMiss(WP80EleEffHigGenIsoBarrel->Eval(pIN.Pt()));
    } else {
      if(isoGen<0.10) return _statTools->HitOrMiss(WP80EleEffLowGenIsoEndcap->Eval(pIN.Pt()));
      else if(isoGen<0.20) return _statTools->HitOrMiss(WP80EleEffMidGenIsoEndcap->Eval(pIN.Pt()));
      else return _statTools->HitOrMiss(WP80EleEffHigGenIsoEndcap->Eval(pIN.Pt()));
    }
  }
  cout << "Error in CMSDetectorResponse::MuonEff: Selector " << Selector << " not known. Returning true" << endl;
  return true;
}

bool CMSDetectorResponse::BTagCSVM_b(TLorentzVector j) {
  double eff = 0.0;
  double pT = j.Pt();
  if(pT>600.) pT=600;
  eff = BTagEffCSVM_b->Eval(pT);
  if(eff>0.0) return _statTools->HitOrMiss(eff);
  return false;
}

bool CMSDetectorResponse::BTagCSVM_c(TLorentzVector j) {
  double eff = 0.0;
  double pT = j.Pt();
  if(pT>600.) pT=600;
  eff = BTagEffCSVM_c->Eval(pT);
  if(eff>0.0) return _statTools->HitOrMiss(eff);
  return false;
}

bool CMSDetectorResponse::BTagCSVM_udsg(TLorentzVector j) {
  double eff = 0.0;
  double pT = j.Pt();
  if(pT>600.) pT=600;
  eff = BTagEffCSVM_udsg->Eval(pT);
  if(eff>0.0) return _statTools->HitOrMiss(eff);
  return false;
}

bool CMSDetectorResponse::BTagHbb_Hbb(TLorentzVector j) {
  double eff = 0.0;
  double pT = j.Pt();
  eff = BTagEffHbb_H->Eval(pT);
  if(eff>0.0) return _statTools->HitOrMiss(eff);
  return false;
}

bool CMSDetectorResponse::BTagHbb_Zbb(TLorentzVector j) {
  double eff = 0.0;
  double pT = j.Pt();
  eff = BTagEffHbb_Z->Eval(pT);
  if(eff>0.0) return _statTools->HitOrMiss(eff);
  return false;
}

bool CMSDetectorResponse::BTagHbb_Top(TLorentzVector j) {
  double eff = 0.0;
  double pT = j.Pt();
  eff = BTagEffHbb_t->Eval(pT);
  if(eff>0.0) return _statTools->HitOrMiss(eff);
  return false;
}

bool CMSDetectorResponse::BTagHbb_Wcs(TLorentzVector j) {
  double eff = 0.0;
  double pT = j.Pt();
  eff = BTagEffHbb_W->Eval(pT);
  if(eff>0.0) return _statTools->HitOrMiss(eff);
  return false;
}

bool CMSDetectorResponse::BTagHbb_udcsg(TLorentzVector j) {
  double eff = 0.0;
  double pT = j.Pt();
  eff = BTagEffHbb_udcsg->Eval(pT);
  if(eff>0.0) return _statTools->HitOrMiss(eff);
  return false;
}

bool CMSDetectorResponse::TrackReco(double d0) {
  double eff = trkEffvsd0->GetBinContent(trkEffvsd0->FindBin(d0));
  if(eff>0) return _statTools->HitOrMiss(eff);
 return false;
} 

bool CMSDetectorResponse::PixelHit() {
  // apply pixel-detector inefficiency on single hits
  // we use 95% for any layer
  return _statTools->HitOrMiss(0.95);
}
