#define GenCandidateFiller_cxx
#include <GenCandidateFiller.hh>
#include <TLorentzVector.h>
#include <math.h>
#include <iostream>

using namespace std;

GenCandidateFiller::GenCandidateFiller(GenTree* genTree, string BlockName) {
  _genTree = genTree;
  _privateData = new GenCandidateFillerData();
  _name = BlockName;
}


GenCandidateFiller::~GenCandidateFiller() {
  delete _privateData->energy;
  delete _privateData->px;
  delete _privateData->py;
  delete _privateData->pz;
  delete _privateData->x;
  delete _privateData->y;
  delete _privateData->z;
  delete _privateData->mass;
  delete _privateData->pdgId;
  delete _privateData->decayLenght;
  delete _privateData->m1pdgId;
  delete _privateData->m2pdgId;
}

void GenCandidateFiller::ClearEvent() {
  _privateData->clearEvent();
}

bool GenCandidateFiller::isParticle(int id, string particle) {
  if(abs(id) == 11 and particle == "Electron") return true;
  if(abs(id) == 13 and particle == "Muon") return true;
  if(abs(id) == 15 and particle == "Tau") return true;
  if(abs(id) == 5 and particle == "b") return true;
  if(abs(id) == 4 and particle == "c") return true;
  if(abs(id) == 22 and particle == "Photon") return true;
  if(abs(id) == 12 and particle == "Neutrino") return true;
  if(abs(id) == 14 and particle == "Neutrino") return true;
  if(abs(id) == 16 and particle == "Neutrino") return true;
  if(abs(id) >= 1000001 && abs(id) <= 1000039 and particle == "SUSY") return true;
  return false;
}

// Return true if the input has no decay vertex
bool GenCandidateFiller::IsStable(HepMC::GenParticle* p) {
  if ( !p->end_vertex() && p->status()==1 ) return 1;
  return 0;
}

bool GenCandidateFiller::isElectron(HepMC::GenParticle* p) {
  int status = p->status();
  unsigned int pdg_id = abs(p->pdg_id());
  return status == 1 &&  pdg_id == 11;
}

bool GenCandidateFiller::isMuon(HepMC::GenParticle* p) {
  int status = p->status();
  unsigned int pdg_id = abs(p->pdg_id());
  return status == 1 &&  pdg_id == 13;
}

bool GenCandidateFiller::isTau(HepMC::GenParticle* p) {
  unsigned int pdg_id = abs(p->pdg_id());
  return pdg_id == 15;
}

bool GenCandidateFiller::isB(HepMC::GenParticle* p) {
  unsigned int pdg_id = abs(p->pdg_id());
  return pdg_id == 5;
}

bool GenCandidateFiller::isC(HepMC::GenParticle* p) {
  unsigned int pdg_id = abs(p->pdg_id());
  return pdg_id == 4;
}

bool GenCandidateFiller::isPhoton(HepMC::GenParticle* p) {
  int status = p->status();  
  unsigned int pdg_id = abs(p->pdg_id());
  return  status == 1 &&  pdg_id == 22;
}

bool GenCandidateFiller::isNeutrino(HepMC::GenParticle* p) {
  int status = p->status();
  unsigned int pdg_id = abs(p->pdg_id());
  return status == 1 &&  (pdg_id == 12 || pdg_id == 14 || pdg_id == 16) ;
}

bool GenCandidateFiller::isSUSY(HepMC::GenParticle* p) {
  // neutrinos are not considered
  bool isSUSY = false;
  int pdgId = p->pdg_id();
  // SUSY particles
  if(abs(pdgId) >= 1000001 && abs(pdgId) <= 1000039) isSUSY =  true;
  return isSUSY;
}

void GenCandidateFiller::NewEvent() {
  _privateData->newEvent();
  _blockSize = 0;
}

void GenCandidateFiller::FillEvent(HepMC::GenEvent* hepmcevt) {
  NewEvent();
  // number of particles in the event
  if(hepmcevt->particles_size() >0) { 
    int i = 0;
    // find all stable particles in the event
    int isCharged = 0;
    int isStable = 0;
    for ( HepMC::GenEvent::particle_iterator p = hepmcevt->particles_begin(); p != hepmcevt->particles_end(); ++p ) {
      bool writeParticle = false;
      // only muons, if requested
      if(_name == "Muon" && isMuon(*p)) writeParticle = true;
      // only electrons, if requested
      else if(_name == "Electron" && isElectron(*p)) writeParticle = true;
      // only photons, if requested
      else if(_name == "Photon" && isPhoton(*p)) writeParticle = true;
      // only taus, if requested [these are not stable particles, pythia will make taus decay]
      else if(_name == "Tau" && isTau(*p)) writeParticle = true;
      // only bs, if requested [these are not stable particles, pythia will make b quarks decay]
      else if(_name == "b" && isB(*p)) writeParticle = true;
      // only cs, if requested [these are not stable particles, pythia will make c quarks decay]
      else if(_name == "c" && isC(*p)) writeParticle = true;
      // invisible particles: neutrinos and stable neutral SUSY particles
      else if(_name == "Neutrino" && isNeutrino(*p)) writeParticle = true;
      // SUSY: all SUSY particles
      else if(_name == "SUSY" && isSUSY(*p)) writeParticle = true;
      // write hard-process incoming/intermediate/outgoing particles
      else if(_name == "GenTreeParticle" && (*p)->status() >= 20 && (*p)->status() < 30) writeParticle = true;
      // whatever else is stable and visbile
      //      else if(_name == "Particle" && !isSUSY(*p) && !isNeutrino(*p) && IsStable(*p)) writeParticle = true;
      else if(_name == "Particle" && !isSUSY(*p) && !isNeutrino(*p) && (*p)->status() == 1) {
	writeParticle = true;
	isStable++;
	//	cout << (*p)->pdg_id() << " " <<  (*p)->status() << " " << (*p)->end_vertex() << endl;
	//	int id = fabs((*p)->pdg_id());
	//	if(id == 221 || id == 321 || id == 11 || id == 13 || id == 2212
      }
      if(writeParticle) {
	FillParticleBranch(*p);
	_blockSize += 1;
      }
    }
  }
  FillTree();
}

void GenCandidateFiller::FillEventSTDHEP(TLorentzVector* p, TVector3* v,
					 double mass, int pdgId,
					 double decayL, int m1,
					 int m2, bool stable = true) {
  bool writeParticle = false;
  if(isParticle(pdgId,_name)) writeParticle = true;
  // whatever else is visible
  else if(_name == "Particle" && !isParticle(pdgId,"SUSY") &&
	  !isParticle(pdgId,"Neutrino") and stable) writeParticle = true;
  
  if(writeParticle) {
    FillParticleBranchSTDHEP(p,v,mass,pdgId,decayL,m1,m2);
    _blockSize += 1;
  }
}

void GenCandidateFiller::FillTree() {
  // Fill the Tree
  _genTree->column(_name.c_str(),_blockSize,0,"Gen");
  _genTree->column((_name+"E").c_str(), *_privateData->energy, _name.c_str(), 0, "Reco");
  _genTree->column((_name+"Px").c_str(), *_privateData->px, _name.c_str(), 0, "Reco");
  _genTree->column((_name+"Py").c_str(), *_privateData->py, _name.c_str(), 0, "Reco");
  _genTree->column((_name+"Pz").c_str(), *_privateData->pz, _name.c_str(), 0, "Reco");
  _genTree->column((_name+"X").c_str(), *_privateData->x, _name.c_str(), 0, "Reco");
  _genTree->column((_name+"Y").c_str(), *_privateData->y, _name.c_str(), 0, "Reco");
  _genTree->column((_name+"Z").c_str(), *_privateData->z, _name.c_str(), 0, "Reco");
  _genTree->column((_name+"Mass").c_str(), *_privateData->mass, _name.c_str(), 0, "Reco");
  _genTree->column((_name+"PdgId").c_str(), *_privateData->pdgId, _name.c_str(), 0, "Reco");
  _genTree->column((_name+"DecayLmm").c_str(), *_privateData->decayLenght, _name.c_str(), 0, "Reco"); 
  _genTree->column((_name+"M1PdgId").c_str(), *_privateData->m1pdgId, _name.c_str(), 0, "Reco");
  _genTree->column((_name+"M2PdgId").c_str(), *_privateData->m2pdgId, _name.c_str(), 0, "Reco");  
}

void GenCandidateFiller::FillParticleBranch(HepMC::GenParticle* p) {
    // Get the 4-momentum
    HepMC::FourVector momentum = p->momentum();
    _privateData->px->push_back(momentum.px());
    _privateData->py->push_back(momentum.py());
    _privateData->pz->push_back(momentum.pz());
    _privateData->energy->push_back(momentum.e());
    _privateData->mass->push_back(momentum.m());

    // PDG Id
    _privateData->pdgId->push_back(p->pdg_id());

    HepMC::GenVertex* vtxIn = p->production_vertex();
    HepMC::GenVertex* vtxOut = p->end_vertex();
    HepMC::ThreeVector vIn = vtxIn->point3d();
    HepMC::ThreeVector vOut = vtxIn->point3d();
    // get production vertex 
    _privateData->x->push_back(vIn.x());
    _privateData->y->push_back(vIn.y());
    _privateData->z->push_back(vIn.z());
    _privateData->decayLenght->push_back(sqrt(pow(vIn.x()-vOut.x(),2.)+
					      pow(vIn.y()-vOut.y(),2.)+
					      pow(vIn.z()-vOut.z(),2.)));

    // first mother info 
    HepMC::GenVertex::particles_in_const_iterator ipi = vtxIn->particles_in_const_begin();  
    _privateData->m1pdgId->push_back((*ipi)->pdg_id());
    //if(ipi != vtxIn->particles_in_const_end()) {
    //  ++ipi;
    //  _privateData->m2pdgId->push_back((*ipi)->pdg_id());
    // } else {
    _privateData->m2pdgId->push_back(-99);
    //}
}

//////////////////

void GenCandidateFiller::FillParticleBranchSTDHEP(TLorentzVector* p, TVector3* v,
						  double mass, int pdgId, double decayL, int m1, int m2) {
    // Get the 4-momentum
    _privateData->px->push_back(p->Px());
    _privateData->py->push_back(p->Py());
    _privateData->pz->push_back(p->Pz());
    _privateData->energy->push_back(p->E());
    _privateData->mass->push_back(mass);

    // PDG Id
    _privateData->pdgId->push_back(pdgId);

    // get production vertex 
    _privateData->x->push_back(v->X());
    _privateData->y->push_back(v->Y());
    _privateData->z->push_back(v->Z());
    _privateData->decayLenght->push_back(decayL);

    // first mother info 
    _privateData->m1pdgId->push_back(m1);
    _privateData->m2pdgId->push_back(m2);
}

///////////////

void  GenCandidateFillerData::newEvent() {
  energy = new vector<float>;
  px = new vector<float>;
  py = new vector<float>;
  pz = new vector<float>;
  x = new vector<float>;
  y = new vector<float>;
  z = new vector<float>;
  mass = new vector<float>;
  pdgId = new vector<int>;
  decayLenght = new vector<int>;
  m1pdgId = new vector<int>;
  m2pdgId = new vector<int>;
}

void GenCandidateFillerData::clearEvent() {
  energy->clear();
  px->clear();
  py->clear();
  pz->clear();
  x->clear();
  y->clear();
  z->clear();
  mass->clear();
  pdgId->clear();
  decayLenght->clear();
  m1pdgId->clear();
  m2pdgId->clear();
}
