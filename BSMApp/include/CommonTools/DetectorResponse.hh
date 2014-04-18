//--------------------------------------------------------------
// DeScription:  Generic detector response
// Authors:      Maurizio Pierini, CERN
//--------------------------------------------------------------

#ifndef DetectorResponse_h
#define DetectorResponse_h

// std includes

// ROOT includes
#include <TRandom3.h>
#include <TF1.h>

// BSMatLHC includes
#include "CommonTools/DetectorReco.hh"
#include <CommonTools/StatTools.hh>

using namespace std;

class DetectorResponse {

public:

  /// Class Constructor
  DetectorResponse(int seed);
  /// Class Destructor
  virtual ~DetectorResponse();  
  /// Read detector card with response functions specified
  void ReadDetectorCard(string fileName);
private:
  /// Build a Detector response function as a polynomial
  TF1* SetResolutionFunction(string name, vector<double> pars, double xmin, double xmax);

  /// Random number generator
  TRandom3* gRandom;

  /// smear a four-vector (energy and Pt) using a Gaussian response function
  TLorentzVector SmearNoBias(TLorentzVector pIN, TH1D* response);
  /// smear a scalar using a Gaussian response function
  double SmearNoBias(double pIN, TH1D* response);  

  // RESPONSE FUNCTIONS

  /// Track Momentum Resolution vs pT
  TF1* _ptResFunTRACK;
  /// Track Eta Resolution vs pT
  TF1* _etaResFunTRACK;
/// Track Phi Resolution vs pT
  TF1* _phiResFunTRACK;

  /// Ele Momentum Resolution vs pT
  TF1* _ptResFunELECTRON;
  /// Ele Eta Resolution vs pT
  TF1* _etaResFunELECTRON;
  /// Ele Phi Resolution vs pT
  TF1* _phiResFunELECTRON;

  /// Muon Momentum Resolution vs pT
  TF1* _ptResFunMUON;
  /// Muon Eta Resolution vs pT
  TF1* _etaResFunMUON;
  /// Muon Phi Resolution vs pT
  TF1* _phiResFunMUON;

  /// Photon Momentum Resolution vs pT
  TF1* _ptResFunPHOTON;
  /// Photon Eta Resolution vs pT
  TF1* _etaResFunPHOTON;
  /// Photon Phi Resolution vs pT
  TF1* _phiResFunPHOTON;

  /// Tau Momentum Resolution vs pT
  TF1* _ptResFunTAU;
  /// Tau Eta Resolution vs pT
  TF1* _etaResFunTAU;
  /// Tau Phi Resolution vs pT
  TF1* _phiResFunTAU;

  /// Ch Hadrons Momentum Resolution vs pT
  TF1* _ptResFunChHAD;
  /// Ch Hadrons Eta Resolution vs pT
  TF1* _etaResFunChHAD;
  /// Ch Hadrons Phi Resolution vs pT
  TF1* _phiResFunChHAD;

  /// Neu Hadrons Momentum Resolution vs pT
  TF1* _ptResFunNeuHAD;
  /// Neu Hadrons Eta Resolution vs pT
  TF1* _etaResFunNeuHAD;
  /// Neu Hadrons Phi Resolution vs pT
  TF1* _phiResFunNeuHAD;

  /// CaloJet Momentum Resolution vs pT
  TF1* _ptResFunCALOJET;
  /// CaloJet Eta Resolution vs pT
  TF1* _etaResFunCALOJET;
  /// CaloJet Phi Resolution vs pT
  TF1* _phiResFunCALOJET;

  /// CaloMET Momentum Resolution vs pT
  TF1* _ptResFunCALOMET;
  /// CaloMET Phi Resolution vs pT
  TF1* _phiResFunCALOMET;

  /// PFJet Momentum Resolution vs pT
  TF1* _ptResFunPFJET;
  /// PFJet Eta Resolution vs pT
  TF1* _etaResFunPFJET;
  /// PFJet Phi Resolution vs pT
  TF1* _phiResFunPFJET;

  /// PFMET Momentum Resolution vs pT
  TF1* _ptResFunPFMET;
  /// PFMET Phi Resolution vs pT
  TF1* _phiResFunPFMET;

};

#endif
