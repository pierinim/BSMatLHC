//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Nov  2 18:17:04 2010 by ROOT version 5.22/00d
// from TTree Trigger/Analysis tree
// found on file: pippo.root
//////////////////////////////////////////////////////////

#ifndef TriggerBase_h
#define TriggerBase_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
   const Int_t kMaxTrigResult = 5;

class TriggerBase {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           TrigResult_;
   Int_t           TrigResult_Accepted[kMaxTrigResult];   //[TrigResult_]
   Int_t           TrigResult_size;

   // List of branches
   TBranch        *b_TrigResult_;   //!
   TBranch        *b_TrigResult_Accepted;   //!
   TBranch        *b_TrigResult_size;   //!

   TriggerBase(TTree *tree=0);
   virtual ~TriggerBase();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef TriggerBase_cxx
TriggerBase::TriggerBase(TTree *tree)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("pippo.root");
      if (!f) {
         f = new TFile("pippo.root");
      }
      tree = (TTree*)gDirectory->Get("Trigger");

   }
   Init(tree);
}

TriggerBase::~TriggerBase()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t TriggerBase::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t TriggerBase::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (!fChain->InheritsFrom(TChain::Class()))  return centry;
   TChain *chain = (TChain*)fChain;
   if (chain->GetTreeNumber() != fCurrent) {
      fCurrent = chain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void TriggerBase::Init(TTree *tree)
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

   fChain->SetBranchAddress("TrigResult", &TrigResult_, &b_TrigResult_);
   fChain->SetBranchAddress("TrigResult.Accepted", TrigResult_Accepted, &b_TrigResult_Accepted);
   fChain->SetBranchAddress("TrigResult_size", &TrigResult_size, &b_TrigResult_size);
   Notify();
}

Bool_t TriggerBase::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void TriggerBase::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t TriggerBase::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef TriggerBase_cxx
