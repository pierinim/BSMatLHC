#include "CommonTools/StatTools.hh"
#include <iostream>
#include <unistd.h>

StatTools::StatTools(int seed) {
   // intialize the seed
  if(seed < 0){
    int jobpid = getpid();
    TDatime *now = new TDatime();
    int today = now->GetDate();
    int clock = now->GetTime();
    int myseed = today+clock+jobpid;
    gRandom = new TRandom3(myseed);
    delete now;
  } else {
    gRandom = new TRandom3(seed);
  }
}

StatTools::~StatTools() {
  delete gRandom;
}

bool StatTools::HitOrMiss(double y) {
  double this_y = gRandom->Rndm();
  return (this_y < y ? true : false);
}

double StatTools::FindUL(TH1D* Lik, double CL, double scale) {

  int ibin = Lik->GetNbinsX();

  int iLimit = -99;
  double prob = 0.;
  double binFraction = 0;
  for(int i=1; i<=ibin; i++){
    prob += Lik->GetBinContent(i)/Lik->Integral();
    if(prob >= CL && iLimit == -99) {
      iLimit = i;
      binFraction = (prob-CL)/Lik->GetBinContent(i);
    }
  }

  double xmin = Lik->GetXaxis()->GetXmin();
  double xmax = Lik->GetXaxis()->GetXmax();
  return scale*(xmin + (iLimit-1.0+binFraction)/ibin*(xmax+xmin));
}

TH1D* StatTools::LogNormPoissonConv(TString name, double n, Double_t CenB, Double_t SigB, Double_t smin, Double_t smax) {
  // Provide the posterior on a signal s, inetgrating out the nuisance parameter
  // b (background) out of a likelihood model
  // L = P(n|s+b)*G(b|CenB, SigB)
  // where CenB +/- SigB is the expected background and n is the observed yield. A flat prior on b is assumed
  // Here we hardcode the signal. We should not have more than 30 signal events
  // so 30 is our "+infinity" for integration purposes
  int ibin = min(200, int(smax-smin));
  TH1D* histo = new TH1D(name, name, ibin, smin, smax);
  for(int i=1; i<=ibin; i++) {
    double s = smin+(i-0.5)/ibin*(smax-smin);
    // integrate numerically over b
    for(int j=0; j<5000; j++) {
      double thisb = CenB*pow(1+SigB/CenB, gRandom->Gaus(0., 1.));
      //double thisb = gRandom->Gaus(CenB,SigB);
      histo->Fill(s, TMath::Poisson(n, s+thisb));
    }
  }
  // normalize the pdf
  histo->Scale(1./histo->Integral());
  return histo;
}

TH1D* StatTools::LogNormHistoConv(TH1D* histo, double sigma) {
  // Convolution of a given pdf with a log-normal of a given error sigma,
  // representing the systematic error on the signal
  // here sigma is given in [0,1], representing the relative error
  if(sigma < 0. || sigma > 1.) {
    cout << "Sigma (relative error) is not in the range [0,1]" << endl;
    cout << " No error is applied. Returning the input histogram" << endl;
    return histo;
  }
  int ibin = histo->GetXaxis()->GetNbins();
  double smin = histo->GetXaxis()->GetXmin();
  double smax = histo->GetXaxis()->GetXmax();
  TH1D* histoOUT = new TH1D(histo->GetName()+TString("WithSignalSYS"), histo->GetTitle()+TString("WithSignalSYS"), ibin, smin, smax);
  for(int i=1; i<=ibin; i++) {
    double s = smin+(i-0.5)/ibin*(smax-smin);
    // integrate numerically over the systematic error
    for(int j=0; j<1000; j++) {
      double thisSignal = s*pow(1+sigma, gRandom->Gaus(0., 1.));
      histoOUT->Fill(thisSignal, histo->GetBinContent(histo->FindBin(s)));
    }
  }
  // normalize the pdf
  histoOUT->Scale(1./histoOUT->Integral());
  return histoOUT;
}
