//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Mar 15 18:36:17 2012 by ROOT version 5.32/00
// from TTree GenEvent/GenEvent
// found on file: pippo.root_GenTree.root
//////////////////////////////////////////////////////////

#ifndef DetectorBase_h
#define DetectorBase_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class DetectorBase {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           Muon;
   Float_t         MuonE[30];   //[Muon]
   Float_t         MuonPx[30];   //[Muon]
   Float_t         MuonPy[30];   //[Muon]
   Float_t         MuonPz[30];   //[Muon]
   Float_t         MuonX[30];   //[Muon]
   Float_t         MuonY[30];   //[Muon]
   Float_t         MuonMass[30];   //[Muon]
   Int_t           MuonPdgId[30];   //[Muon]
   Int_t           MuonDecayLmm[30];   //[Muon]
   Int_t           MuonM1PdgId[30];   //[Muon]
   Int_t           MuonM2PdgId[30];   //[Muon]
   Int_t           Electron;
   Float_t         ElectronE[30];   //[Electron]
   Float_t         ElectronPx[30];   //[Electron]
   Float_t         ElectronPy[30];   //[Electron]
   Float_t         ElectronPz[30];   //[Electron]
   Float_t         ElectronX[30];   //[Electron]
   Float_t         ElectronY[30];   //[Electron]
   Float_t         ElectronMass[30];   //[Electron]
   Int_t           ElectronPdgId[30];   //[Electron]
   Int_t           ElectronDecayLmm[30];   //[Electron]
   Int_t           ElectronM1PdgId[30];   //[Electron]
   Int_t           ElectronM2PdgId[30];   //[Electron]
   Int_t           Tau;
   Float_t         TauE[30];   //[Tau]
   Float_t         TauPx[30];   //[Tau]
   Float_t         TauPy[30];   //[Tau]
   Float_t         TauPz[30];   //[Tau]
   Float_t         TauX[30];   //[Tau]
   Float_t         TauY[30];   //[Tau]
   Float_t         TauMass[30];   //[Tau]
   Int_t           TauPdgId[30];   //[Tau]
   Int_t           TauDecayLmm[30];   //[Tau]
   Int_t           TauM1PdgId[30];   //[Tau]
   Int_t           TauM2PdgId[30];   //[Tau]
   Int_t           b;
   Float_t         bE[100];   //[b]
   Float_t         bPx[100];   //[b]
   Float_t         bPy[100];   //[b]
   Float_t         bPz[100];   //[b]
   Float_t         bX[100];   //[b]
   Float_t         bY[100];   //[b]
   Float_t         bMass[100];   //[b]
   Int_t           bPdgId[100];   //[b]
   Int_t           bDecayLmm[100];   //[b]
   Int_t           bM1PdgId[100];   //[b]
   Int_t           bM2PdgId[100];   //[b]
   Int_t           c;
   Float_t         cE[100];   //[c]
   Float_t         cPx[100];   //[c]
   Float_t         cPy[100];   //[c]
   Float_t         cPz[100];   //[c]
   Float_t         cX[100];   //[c]
   Float_t         cY[100];   //[c]
   Float_t         cMass[100];   //[c]
   Int_t           cPdgId[100];   //[c]
   Int_t           cDecayLmm[100];   //[c]
   Int_t           cM1PdgId[100];   //[c]
   Int_t           cM2PdgId[100];   //[c]
   Int_t           Photon;
   Float_t         PhotonE[800];   //[Photon]
   Float_t         PhotonPx[800];   //[Photon]
   Float_t         PhotonPy[800];   //[Photon]
   Float_t         PhotonPz[800];   //[Photon]
   Float_t         PhotonX[800];   //[Photon]
   Float_t         PhotonY[800];   //[Photon]
   Float_t         PhotonMass[800];   //[Photon]
   Int_t           PhotonPdgId[800];   //[Photon]
   Int_t           PhotonDecayLmm[800];   //[Photon]
   Int_t           PhotonM1PdgId[800];   //[Photon]
   Int_t           PhotonM2PdgId[800];   //[Photon]
   Int_t           Neutrino;
   Float_t         NeutrinoE[50];   //[Neutrino]
   Float_t         NeutrinoPx[50];   //[Neutrino]
   Float_t         NeutrinoPy[50];   //[Neutrino]
   Float_t         NeutrinoPz[50];   //[Neutrino]
   Float_t         NeutrinoX[50];   //[Neutrino]
   Float_t         NeutrinoY[50];   //[Neutrino]
   Float_t         NeutrinoMass[50];   //[Neutrino]
   Int_t           NeutrinoPdgId[50];   //[Neutrino]
   Int_t           NeutrinoDecayLmm[50];   //[Neutrino]
   Int_t           NeutrinoM1PdgId[50];   //[Neutrino]
   Int_t           NeutrinoM2PdgId[50];   //[Neutrino]
   Int_t           SUSY;
   Float_t         SUSYE[20];   //[SUSY]
   Float_t         SUSYPx[20];   //[SUSY]
   Float_t         SUSYPy[20];   //[SUSY]
   Float_t         SUSYPz[20];   //[SUSY]
   Float_t         SUSYX[20];   //[SUSY]
   Float_t         SUSYY[20];   //[SUSY]
   Float_t         SUSYMass[20];   //[SUSY]
   Int_t           SUSYPdgId[20];   //[SUSY]
   Int_t           SUSYDecayLmm[20];   //[SUSY]
   Int_t           SUSYM1PdgId[20];   //[SUSY]
   Int_t           SUSYM2PdgId[20];   //[SUSY]
   Int_t           GenTreeParticle;
   Float_t         GenTreeParticleE[50];   //[GenTreeParticle]
   Float_t         GenTreeParticlePx[50];   //[GenTreeParticle]
   Float_t         GenTreeParticlePy[50];   //[GenTreeParticle]
   Float_t         GenTreeParticlePz[50];   //[GenTreeParticle]
   Float_t         GenTreeParticleX[50];   //[GenTreeParticle]
   Float_t         GenTreeParticleY[50];   //[GenTreeParticle]
   Float_t         GenTreeParticleMass[50];   //[GenTreeParticle]
   Int_t           GenTreeParticlePdgId[50];   //[GenTreeParticle]
   Int_t           GenTreeParticleDecayLmm[50];   //[GenTreeParticle]
   Int_t           GenTreeParticleM1PdgId[50];   //[GenTreeParticle]
   Int_t           GenTreeParticleM2PdgId[50];   //[GenTreeParticle]
   Int_t           Particle;
   Float_t         ParticleE[4000];   //[Particle]
   Float_t         ParticlePx[4000];   //[Particle]
   Float_t         ParticlePy[4000];   //[Particle]
   Float_t         ParticlePz[4000];   //[Particle]
   Float_t         ParticleX[4000];   //[Particle]
   Float_t         ParticleY[4000];   //[Particle]
   Float_t         ParticleMass[4000];   //[Particle]
   Int_t           ParticlePdgId[4000];   //[Particle]
   Int_t           ParticleDecayLmm[4000];   //[Particle]
   Int_t           ParticleM1PdgId[4000];   //[Particle]
   Int_t           ParticleM2PdgId[4000];   //[Particle]

   // List of branches
   TBranch        *b_Muon;   //!
   TBranch        *b_MuonE;   //!
   TBranch        *b_MuonPx;   //!
   TBranch        *b_MuonPy;   //!
   TBranch        *b_MuonPz;   //!
   TBranch        *b_MuonX;   //!
   TBranch        *b_MuonY;   //!
   TBranch        *b_MuonMass;   //!
   TBranch        *b_MuonPdgId;   //!
   TBranch        *b_MuonDecayLmm;   //!
   TBranch        *b_MuonM1PdgId;   //!
   TBranch        *b_MuonM2PdgId;   //!
   TBranch        *b_Electron;   //!
   TBranch        *b_ElectronE;   //!
   TBranch        *b_ElectronPx;   //!
   TBranch        *b_ElectronPy;   //!
   TBranch        *b_ElectronPz;   //!
   TBranch        *b_ElectronX;   //!
   TBranch        *b_ElectronY;   //!
   TBranch        *b_ElectronMass;   //!
   TBranch        *b_ElectronPdgId;   //!
   TBranch        *b_ElectronDecayLmm;   //!
   TBranch        *b_ElectronM1PdgId;   //!
   TBranch        *b_ElectronM2PdgId;   //!
   TBranch        *b_Tau;   //!
   TBranch        *b_TauE;   //!
   TBranch        *b_TauPx;   //!
   TBranch        *b_TauPy;   //!
   TBranch        *b_TauPz;   //!
   TBranch        *b_TauX;   //!
   TBranch        *b_TauY;   //!
   TBranch        *b_TauMass;   //!
   TBranch        *b_TauPdgId;   //!
   TBranch        *b_TauDecayLmm;   //!
   TBranch        *b_TauM1PdgId;   //!
   TBranch        *b_TauM2PdgId;   //!
   TBranch        *b_b;   //!
   TBranch        *b_bE;   //!
   TBranch        *b_bPx;   //!
   TBranch        *b_bPy;   //!
   TBranch        *b_bPz;   //!
   TBranch        *b_bX;   //!
   TBranch        *b_bY;   //!
   TBranch        *b_bMass;   //!
   TBranch        *b_bPdgId;   //!
   TBranch        *b_bDecayLmm;   //!
   TBranch        *b_bM1PdgId;   //!
   TBranch        *b_bM2PdgId;   //!
   TBranch        *b_c;   //!
   TBranch        *b_cE;   //!
   TBranch        *b_cPx;   //!
   TBranch        *b_cPy;   //!
   TBranch        *b_cPz;   //!
   TBranch        *b_cX;   //!
   TBranch        *b_cY;   //!
   TBranch        *b_cMass;   //!
   TBranch        *b_cPdgId;   //!
   TBranch        *b_cDecayLmm;   //!
   TBranch        *b_cM1PdgId;   //!
   TBranch        *b_cM2PdgId;   //!
   TBranch        *b_Photon;   //!
   TBranch        *b_PhotonE;   //!
   TBranch        *b_PhotonPx;   //!
   TBranch        *b_PhotonPy;   //!
   TBranch        *b_PhotonPz;   //!
   TBranch        *b_PhotonX;   //!
   TBranch        *b_PhotonY;   //!
   TBranch        *b_PhotonMass;   //!
   TBranch        *b_PhotonPdgId;   //!
   TBranch        *b_PhotonDecayLmm;   //!
   TBranch        *b_PhotonM1PdgId;   //!
   TBranch        *b_PhotonM2PdgId;   //!
   TBranch        *b_Neutrino;   //!
   TBranch        *b_NeutrinoE;   //!
   TBranch        *b_NeutrinoPx;   //!
   TBranch        *b_NeutrinoPy;   //!
   TBranch        *b_NeutrinoPz;   //!
   TBranch        *b_NeutrinoX;   //!
   TBranch        *b_NeutrinoY;   //!
   TBranch        *b_NeutrinoMass;   //!
   TBranch        *b_NeutrinoPdgId;   //!
   TBranch        *b_NeutrinoDecayLmm;   //!
   TBranch        *b_NeutrinoM1PdgId;   //!
   TBranch        *b_NeutrinoM2PdgId;   //!
   TBranch        *b_SUSY;   //!
   TBranch        *b_SUSYE;   //!
   TBranch        *b_SUSYPx;   //!
   TBranch        *b_SUSYPy;   //!
   TBranch        *b_SUSYPz;   //!
   TBranch        *b_SUSYX;   //!
   TBranch        *b_SUSYY;   //!
   TBranch        *b_SUSYMass;   //!
   TBranch        *b_SUSYPdgId;   //!
   TBranch        *b_SUSYDecayLmm;   //!
   TBranch        *b_SUSYM1PdgId;   //!
   TBranch        *b_SUSYM2PdgId;   //!
   TBranch        *b_GenTreeParticle;   //!
   TBranch        *b_GenTreeParticleE;   //!
   TBranch        *b_GenTreeParticlePx;   //!
   TBranch        *b_GenTreeParticlePy;   //!
   TBranch        *b_GenTreeParticlePz;   //!
   TBranch        *b_GenTreeParticleX;   //!
   TBranch        *b_GenTreeParticleY;   //!
   TBranch        *b_GenTreeParticleMass;   //!
   TBranch        *b_GenTreeParticlePdgId;   //!
   TBranch        *b_GenTreeParticleDecayLmm;   //!
   TBranch        *b_GenTreeParticleM1PdgId;   //!
   TBranch        *b_GenTreeParticleM2PdgId;   //!
   TBranch        *b_Particle;   //!
   TBranch        *b_ParticleE;   //!
   TBranch        *b_ParticlePx;   //!
   TBranch        *b_ParticlePy;   //!
   TBranch        *b_ParticlePz;   //!
   TBranch        *b_ParticleX;   //!
   TBranch        *b_ParticleY;   //!
   TBranch        *b_ParticleMass;   //!
   TBranch        *b_ParticlePdgId;   //!
   TBranch        *b_ParticleDecayLmm;   //!
   TBranch        *b_ParticleM1PdgId;   //!
   TBranch        *b_ParticleM2PdgId;   //!

   DetectorBase(TTree *tree=0);
   virtual ~DetectorBase();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef DetectorBase_cxx
DetectorBase::DetectorBase(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("pippo.root_GenTree.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("pippo.root_GenTree.root");
      }
      f->GetObject("GenEvent",tree);

   }
   Init(tree);
}

DetectorBase::~DetectorBase()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t DetectorBase::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t DetectorBase::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void DetectorBase::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("Muon", &Muon, &b_Muon);
   fChain->SetBranchAddress("MuonE", MuonE, &b_MuonE);
   fChain->SetBranchAddress("MuonPx", MuonPx, &b_MuonPx);
   fChain->SetBranchAddress("MuonPy", MuonPy, &b_MuonPy);
   fChain->SetBranchAddress("MuonPz", MuonPz, &b_MuonPz);
   fChain->SetBranchAddress("MuonX", MuonX, &b_MuonX);
   fChain->SetBranchAddress("MuonY", MuonY, &b_MuonY);
   fChain->SetBranchAddress("MuonMass", MuonMass, &b_MuonMass);
   fChain->SetBranchAddress("MuonPdgId", MuonPdgId, &b_MuonPdgId);
   fChain->SetBranchAddress("MuonDecayLmm", MuonDecayLmm, &b_MuonDecayLmm);
   fChain->SetBranchAddress("MuonM1PdgId", MuonM1PdgId, &b_MuonM1PdgId);
   fChain->SetBranchAddress("MuonM2PdgId", MuonM2PdgId, &b_MuonM2PdgId);
   fChain->SetBranchAddress("Electron", &Electron, &b_Electron);
   fChain->SetBranchAddress("ElectronE", ElectronE, &b_ElectronE);
   fChain->SetBranchAddress("ElectronPx", ElectronPx, &b_ElectronPx);
   fChain->SetBranchAddress("ElectronPy", ElectronPy, &b_ElectronPy);
   fChain->SetBranchAddress("ElectronPz", ElectronPz, &b_ElectronPz);
   fChain->SetBranchAddress("ElectronX", ElectronX, &b_ElectronX);
   fChain->SetBranchAddress("ElectronY", ElectronY, &b_ElectronY);
   fChain->SetBranchAddress("ElectronMass", ElectronMass, &b_ElectronMass);
   fChain->SetBranchAddress("ElectronPdgId", ElectronPdgId, &b_ElectronPdgId);
   fChain->SetBranchAddress("ElectronDecayLmm", ElectronDecayLmm, &b_ElectronDecayLmm);
   fChain->SetBranchAddress("ElectronM1PdgId", ElectronM1PdgId, &b_ElectronM1PdgId);
   fChain->SetBranchAddress("ElectronM2PdgId", ElectronM2PdgId, &b_ElectronM2PdgId);
   fChain->SetBranchAddress("Tau", &Tau, &b_Tau);
   fChain->SetBranchAddress("TauE", TauE, &b_TauE);
   fChain->SetBranchAddress("TauPx", TauPx, &b_TauPx);
   fChain->SetBranchAddress("TauPy", TauPy, &b_TauPy);
   fChain->SetBranchAddress("TauPz", TauPz, &b_TauPz);
   fChain->SetBranchAddress("TauX", TauX, &b_TauX);
   fChain->SetBranchAddress("TauY", TauY, &b_TauY);
   fChain->SetBranchAddress("TauMass", TauMass, &b_TauMass);
   fChain->SetBranchAddress("TauPdgId", TauPdgId, &b_TauPdgId);
   fChain->SetBranchAddress("TauDecayLmm", TauDecayLmm, &b_TauDecayLmm);
   fChain->SetBranchAddress("TauM1PdgId", TauM1PdgId, &b_TauM1PdgId);
   fChain->SetBranchAddress("TauM2PdgId", TauM2PdgId, &b_TauM2PdgId);
   fChain->SetBranchAddress("b", &b, &b_b);
   fChain->SetBranchAddress("bE", bE, &b_bE);
   fChain->SetBranchAddress("bPx", bPx, &b_bPx);
   fChain->SetBranchAddress("bPy", bPy, &b_bPy);
   fChain->SetBranchAddress("bPz", bPz, &b_bPz);
   fChain->SetBranchAddress("bX", bX, &b_bX);
   fChain->SetBranchAddress("bY", bY, &b_bY);
   fChain->SetBranchAddress("bMass", bMass, &b_bMass);
   fChain->SetBranchAddress("bPdgId", bPdgId, &b_bPdgId);
   fChain->SetBranchAddress("bDecayLmm", bDecayLmm, &b_bDecayLmm);
   fChain->SetBranchAddress("bM1PdgId", bM1PdgId, &b_bM1PdgId);
   fChain->SetBranchAddress("bM2PdgId", bM2PdgId, &b_bM2PdgId);
   fChain->SetBranchAddress("c", &c, &b_c);
   fChain->SetBranchAddress("cE", cE, &b_cE);
   fChain->SetBranchAddress("cPx", cPx, &b_cPx);
   fChain->SetBranchAddress("cPy", cPy, &b_cPy);
   fChain->SetBranchAddress("cPz", cPz, &b_cPz);
   fChain->SetBranchAddress("cX", cX, &b_cX);
   fChain->SetBranchAddress("cY", cY, &b_cY);
   fChain->SetBranchAddress("cMass", cMass, &b_cMass);
   fChain->SetBranchAddress("cPdgId", cPdgId, &b_cPdgId);
   fChain->SetBranchAddress("cDecayLmm", cDecayLmm, &b_cDecayLmm);
   fChain->SetBranchAddress("cM1PdgId", cM1PdgId, &b_cM1PdgId);
   fChain->SetBranchAddress("cM2PdgId", cM2PdgId, &b_cM2PdgId);
   fChain->SetBranchAddress("Photon", &Photon, &b_Photon);
   fChain->SetBranchAddress("PhotonE", PhotonE, &b_PhotonE);
   fChain->SetBranchAddress("PhotonPx", PhotonPx, &b_PhotonPx);
   fChain->SetBranchAddress("PhotonPy", PhotonPy, &b_PhotonPy);
   fChain->SetBranchAddress("PhotonPz", PhotonPz, &b_PhotonPz);
   fChain->SetBranchAddress("PhotonX", PhotonX, &b_PhotonX);
   fChain->SetBranchAddress("PhotonY", PhotonY, &b_PhotonY);
   fChain->SetBranchAddress("PhotonMass", PhotonMass, &b_PhotonMass);
   fChain->SetBranchAddress("PhotonPdgId", PhotonPdgId, &b_PhotonPdgId);
   fChain->SetBranchAddress("PhotonDecayLmm", PhotonDecayLmm, &b_PhotonDecayLmm);
   fChain->SetBranchAddress("PhotonM1PdgId", PhotonM1PdgId, &b_PhotonM1PdgId);
   fChain->SetBranchAddress("PhotonM2PdgId", PhotonM2PdgId, &b_PhotonM2PdgId);
   fChain->SetBranchAddress("Neutrino", &Neutrino, &b_Neutrino);
   fChain->SetBranchAddress("NeutrinoE", NeutrinoE, &b_NeutrinoE);
   fChain->SetBranchAddress("NeutrinoPx", NeutrinoPx, &b_NeutrinoPx);
   fChain->SetBranchAddress("NeutrinoPy", NeutrinoPy, &b_NeutrinoPy);
   fChain->SetBranchAddress("NeutrinoPz", NeutrinoPz, &b_NeutrinoPz);
   fChain->SetBranchAddress("NeutrinoX", NeutrinoX, &b_NeutrinoX);
   fChain->SetBranchAddress("NeutrinoY", NeutrinoY, &b_NeutrinoY);
   fChain->SetBranchAddress("NeutrinoMass", NeutrinoMass, &b_NeutrinoMass);
   fChain->SetBranchAddress("NeutrinoPdgId", NeutrinoPdgId, &b_NeutrinoPdgId);
   fChain->SetBranchAddress("NeutrinoDecayLmm", NeutrinoDecayLmm, &b_NeutrinoDecayLmm);
   fChain->SetBranchAddress("NeutrinoM1PdgId", NeutrinoM1PdgId, &b_NeutrinoM1PdgId);
   fChain->SetBranchAddress("NeutrinoM2PdgId", NeutrinoM2PdgId, &b_NeutrinoM2PdgId);
   fChain->SetBranchAddress("SUSY", &SUSY, &b_SUSY);
   fChain->SetBranchAddress("SUSYE", SUSYE, &b_SUSYE);
   fChain->SetBranchAddress("SUSYPx", SUSYPx, &b_SUSYPx);
   fChain->SetBranchAddress("SUSYPy", SUSYPy, &b_SUSYPy);
   fChain->SetBranchAddress("SUSYPz", SUSYPz, &b_SUSYPz);
   fChain->SetBranchAddress("SUSYX", SUSYX, &b_SUSYX);
   fChain->SetBranchAddress("SUSYY", SUSYY, &b_SUSYY);
   fChain->SetBranchAddress("SUSYMass", SUSYMass, &b_SUSYMass);
   fChain->SetBranchAddress("SUSYPdgId", SUSYPdgId, &b_SUSYPdgId);
   fChain->SetBranchAddress("SUSYDecayLmm", SUSYDecayLmm, &b_SUSYDecayLmm);
   fChain->SetBranchAddress("SUSYM1PdgId", SUSYM1PdgId, &b_SUSYM1PdgId);
   fChain->SetBranchAddress("SUSYM2PdgId", SUSYM2PdgId, &b_SUSYM2PdgId);
   fChain->SetBranchAddress("GenTreeParticle", &GenTreeParticle, &b_GenTreeParticle);
   fChain->SetBranchAddress("GenTreeParticleE", GenTreeParticleE, &b_GenTreeParticleE);
   fChain->SetBranchAddress("GenTreeParticlePx", GenTreeParticlePx, &b_GenTreeParticlePx);
   fChain->SetBranchAddress("GenTreeParticlePy", GenTreeParticlePy, &b_GenTreeParticlePy);
   fChain->SetBranchAddress("GenTreeParticlePz", GenTreeParticlePz, &b_GenTreeParticlePz);
   fChain->SetBranchAddress("GenTreeParticleX", GenTreeParticleX, &b_GenTreeParticleX);
   fChain->SetBranchAddress("GenTreeParticleY", GenTreeParticleY, &b_GenTreeParticleY);
   fChain->SetBranchAddress("GenTreeParticleMass", GenTreeParticleMass, &b_GenTreeParticleMass);
   fChain->SetBranchAddress("GenTreeParticlePdgId", GenTreeParticlePdgId, &b_GenTreeParticlePdgId);
   fChain->SetBranchAddress("GenTreeParticleDecayLmm", GenTreeParticleDecayLmm, &b_GenTreeParticleDecayLmm);
   fChain->SetBranchAddress("GenTreeParticleM1PdgId", GenTreeParticleM1PdgId, &b_GenTreeParticleM1PdgId);
   fChain->SetBranchAddress("GenTreeParticleM2PdgId", GenTreeParticleM2PdgId, &b_GenTreeParticleM2PdgId);
   fChain->SetBranchAddress("Particle", &Particle, &b_Particle);
   fChain->SetBranchAddress("ParticleE", ParticleE, &b_ParticleE);
   fChain->SetBranchAddress("ParticlePx", ParticlePx, &b_ParticlePx);
   fChain->SetBranchAddress("ParticlePy", ParticlePy, &b_ParticlePy);
   fChain->SetBranchAddress("ParticlePz", ParticlePz, &b_ParticlePz);
   fChain->SetBranchAddress("ParticleX", ParticleX, &b_ParticleX);
   fChain->SetBranchAddress("ParticleY", ParticleY, &b_ParticleY);
   fChain->SetBranchAddress("ParticleMass", ParticleMass, &b_ParticleMass);
   fChain->SetBranchAddress("ParticlePdgId", ParticlePdgId, &b_ParticlePdgId);
   fChain->SetBranchAddress("ParticleDecayLmm", ParticleDecayLmm, &b_ParticleDecayLmm);
   fChain->SetBranchAddress("ParticleM1PdgId", ParticleM1PdgId, &b_ParticleM1PdgId);
   fChain->SetBranchAddress("ParticleM2PdgId", ParticleM2PdgId, &b_ParticleM2PdgId);
   Notify();
}

Bool_t DetectorBase::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void DetectorBase::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t DetectorBase::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef DetectorBase_cxx
