//--------------------------------------------------------------
// DeScription:  CMS detector response
// Authors:      Maurizio Pierini, CERN
//--------------------------------------------------------------

#ifndef CMSDetectorResponse_h
#define CMSDetectorResponse_h

// std includes
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <unistd.h>
#include <algorithm>
#include <numeric>
#include <list>
#include "CommonTools/combination.hh"

// ROOT includes
#include <TFile.h>
#include <TH1D.h>
#include <TF1.h>
#include <TRandom3.h>
#include <TGraphAsymmErrors.h>

#include "CommonTools/DetectorReco.hh"
#include <CommonTools/StatTools.hh>

using namespace std;

class CMSDetectorResponse {

public:

  /// Class Constructor
  CMSDetectorResponse(int seed);
  /// Class Destructor
  virtual ~CMSDetectorResponse();
  
  /// Returned smeared PFJet
  TLorentzVector PFJetReco(TLorentzVector pIN);

  /// Returned smeared CaloJet
  TLorentzVector CaloJetReco(TLorentzVector pIN);

  /// Returned smeared PFMET
  TLorentzVector PFMETReco(TLorentzVector pIN);

  /// Returned smeared CaloMET
  TLorentzVector CaloMETReco(TLorentzVector pIN);

  /// Returned smeared Electron
  TLorentzVector ElectronReco(TLorentzVector pIN);

  /// Returned smeared Muon
  TLorentzVector MuonReco(TLorentzVector pIN);

  /// Apply muon reconstruction inefficiency through hit-or-miss
  bool MuonEff(TLorentzVector pIN, double isoGen, string Selector);

  /// Apply electron reconstruction inefficiency through hit-or-miss
  bool EleEff(TLorentzVector pIN, double isoGen, string Selector);

  /// Apply Pixel efficiency (95% flat)
  bool PixelHit();

  /// Tagging efficiency for CSV medium working point for b quarks
  bool BTagCSVM_b(TLorentzVector j);

  /// Tagging efficiency for CSV medium working point for c quarks
  bool BTagCSVM_c(TLorentzVector j);

  /// Tagging efficiency for CSV medium working point for udsg quarks
  bool BTagCSVM_udsg(TLorentzVector j);

  /// double b tagging efficiency for H->bb
  bool BTagHbb_Hbb(TLorentzVector j);

  /// double b tagging efficiency for Z->bb
  bool BTagHbb_Zbb(TLorentzVector j);

  /// double b tagging efficiency for top
  bool BTagHbb_Top(TLorentzVector j);

  /// double b tagging efficiency for W->cs
  bool BTagHbb_Wcs(TLorentzVector j);

  /// double b tagging efficiency for QCD jets
  bool BTagHbb_udcsg(TLorentzVector j);

  /// apply tracking efficiency vs d0
  bool TrackReco(double d0);

private:
  /// Random number generator
  TRandom3* gRandom;

  /// smear a four-vector (energy and Pt) using a Gaussian response function
  TLorentzVector SmearNoBias(TLorentzVector pIN, TH1D* response);
  /// smear a scalar using a Gaussian response function
  double SmearNoBias(double pIN, TH1D* response);

  // CaloJet
  TH1D*   CaloJetResponse_0p0_eta_1p4;
  TH1D*   CaloJetResponse_1p4_eta_2p4;
  TH1D*   CaloJetResponse_2p4_eta_3p0;
  TH1D*   CaloJetResponse_3p0_eta_5p0;
  // PFJET
  TH1D*   PFJetResponse_0p0_eta_1p4;
  TH1D*   PFJetResponse_1p4_eta_2p4;
  TH1D*   PFJetResponse_2p4_eta_3p0;
  TH1D*   PFJetResponse_3p0_eta_5p0;
  // MET
  TH1D*   PFMETResponse;
  TH1D*   CaloMETResponse;
  // Electrons
  TH1D*   EleResponse_Barrel;
  TH1D*   EleResponse_Endcap;
  // Muons
  TH1D*   MuResponse;
  
  // Tight Muon Efficiency
  TGraphAsymmErrors*   TightMuEffLowGenIsoBarrel;
  TGraphAsymmErrors*   TightMuEffMidGenIsoBarrel;
  TGraphAsymmErrors*   TightMuEffHigGenIsoBarrel;
  TGraphAsymmErrors*   TightMuEffLowGenIsoEndcap;
  TGraphAsymmErrors*   TightMuEffMidGenIsoEndcap;
  TGraphAsymmErrors*   TightMuEffHigGenIsoEndcap;
  // Loose Muon Efficiency
  TGraphAsymmErrors*   LooseMuEffBarrel;
  TGraphAsymmErrors*   LooseMuEffEndcap;
  // WP80 Electron
  TGraphAsymmErrors*   WP80EleEffLowGenIsoBarrel;
  TGraphAsymmErrors*   WP80EleEffMidGenIsoBarrel;
  TGraphAsymmErrors*   WP80EleEffHigGenIsoBarrel;
  TGraphAsymmErrors*   WP80EleEffLowGenIsoEndcap;
  TGraphAsymmErrors*   WP80EleEffMidGenIsoEndcap;
  TGraphAsymmErrors*   WP80EleEffHigGenIsoEndcap;
  // WP95 Electron
  TGraphAsymmErrors*   WP95EleEffLowGenIsoBarrel;
  TGraphAsymmErrors*   WP95EleEffMidGenIsoBarrel;
  TGraphAsymmErrors*   WP95EleEffHigGenIsoBarrel;
  TGraphAsymmErrors*   WP95EleEffLowGenIsoEndcap;
  TGraphAsymmErrors*   WP95EleEffMidGenIsoEndcap;
  TGraphAsymmErrors*   WP95EleEffHigGenIsoEndcap;

  /// BTag efficiency vs pT jet
  TF1* BTagEffCSVM_b;
  TF1* BTagEffCSVM_c;
  TF1* BTagEffCSVM_udsg;

  TF1* BTagEffHbb_H;
  TF1* BTagEffHbb_Z;
  TF1* BTagEffHbb_t;
  TF1* BTagEffHbb_W;
  TF1* BTagEffHbb_udcsg;

  /// Tracking eff vs transverse flight lenght
  TH1D* trkEffvsd0;

  /// Statistics Tools
  StatTools* _statTools;

};

#endif
