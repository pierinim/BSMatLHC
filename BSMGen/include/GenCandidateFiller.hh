// -*- C++ -*-
//---------------------------------------------------------------------------------
//
// Description:
//    Class GenCandidateFiller
//
// Author:
//    Emanuele Di Marco (Caltech)
//    Maurizio Pierini  (CERN)
//
//---------------------------------------------------------------------------------

#ifndef GenCandidateFiller_h
#define GenCandidateFiller_h

#include <GenTree.hh>
#include <vector>
#include "HepMC/GenEvent.h"
#include "HepMC/IO_GenEvent.h"
#include "HepMC/Units.h"
#include <TLorentzVector.h>

using namespace std;

struct GenCandidateFillerData {
  // All the vectors that will store the stuff                                                                                                                                                                         
  // going into the tree.                                                                                                                                                                                              
  vector<float> *energy, *px, *py, *pz;
  vector<float> *x, *y, *z;  
  vector<float> *mass;
  vector<int> *pdgId, *decayLenght;
  vector<int> *m1pdgId, *m2pdgId;

public:
  void newEvent();
  void clearEvent();
};


class GenCandidateFiller {

public:
  GenCandidateFiller(GenTree* genTree, string BlockName);
  ~GenCandidateFiller();
  void FillEvent(HepMC::GenEvent* hepmcevt);
  void FillEventSTDHEP(TLorentzVector* p, TVector3* v, double mass, int pdgId,
		       double decayL, int m1, int m2, bool stable);
  void FillTree();
  void ClearEvent();
  void NewEvent();

protected:
  void FillParticleBranch(HepMC::GenParticle* hepmcevt);
  void FillParticleBranchSTDHEP(TLorentzVector* p, TVector3* v, double mass, int pdgId,
				double decayL, int m1, int m2);
  bool IsStable(HepMC::GenParticle* p);
  bool isElectron(HepMC::GenParticle* p);
  bool isMuon(HepMC::GenParticle* p);
  bool isTau(HepMC::GenParticle* p);
  bool isB(HepMC::GenParticle* p);
  bool isC(HepMC::GenParticle* p);
  bool isPhoton(HepMC::GenParticle* p);
  bool isNeutrino(HepMC::GenParticle* p);
  bool isSUSY(HepMC::GenParticle* p);
  bool isParticle(int id, string particle);
  int _blockSize;

private:
  GenTree* _genTree;
  GenCandidateFillerData* _privateData;
  string _name;
};



#endif // GenCandidateFiller_h
