#include <vector.h>
using namespace std;

void makeEffTable(string filename) {
  TFile* file = new TFile(filename.c_str());
  TTree* fChain = (TTree*) file->Get("CMS_JetMETAnalysis/effTree");

  // Declaration of leaf types
   Int_t           Nev;
   Int_t           Nev_Trigger;
   Int_t           Nev_EEMF;
   Int_t           Nev_ECHF;
   Int_t           Nev_MET;
   Int_t           Nev_3j;
   Int_t           Nev_eta1stjet;
   Int_t           Nev_QCD1;
   Int_t           Nev_QCD2;
   Int_t           Nev_QCD3;
   Int_t           Nev_ILV;
   Int_t           Nev_ILVEMF;
   Int_t           Nev_1stjetEt;
   Int_t           Nev_2ndjetEt;
   Int_t           Nev_ht;

   // List of branches
   TBranch        *b_Nev;   //!
   TBranch        *b_Nev_Trigger;   //!
   TBranch        *b_Nev_EEMF;   //!
   TBranch        *b_Nev_ECHF;   //!
   TBranch        *b_Nev_MET;   //!
   TBranch        *b_Nev_3j;   //!
   TBranch        *b_Nev_eta1stjet;   //!
   TBranch        *b_Nev_QCD1;   //!
   TBranch        *b_Nev_QCD2;   //!
   TBranch        *b_Nev_QCD3;   //!
   TBranch        *b_Nev_ILV;   //!
   TBranch        *b_Nev_ILVEMF;   //!
   TBranch        *b_Nev_1stjetEt;   //!
   TBranch        *b_Nev_2ndjetEt;   //!
   TBranch        *b_Nev_ht;   //!

   fChain->SetBranchAddress("Nev", &Nev, &b_Nev);
   fChain->SetBranchAddress("Nev_Trigger", &Nev_Trigger, &b_Nev_Trigger);
   fChain->SetBranchAddress("Nev_EEMF", &Nev_EEMF, &b_Nev_EEMF);
   fChain->SetBranchAddress("Nev_ECHF", &Nev_ECHF, &b_Nev_ECHF);
   fChain->SetBranchAddress("Nev_MET", &Nev_MET, &b_Nev_MET);
   fChain->SetBranchAddress("Nev_3j", &Nev_3j, &b_Nev_3j);
   fChain->SetBranchAddress("Nev_eta1stjet", &Nev_eta1stjet, &b_Nev_eta1stjet);
   fChain->SetBranchAddress("Nev_QCD1", &Nev_QCD1, &b_Nev_QCD1);
   fChain->SetBranchAddress("Nev_QCD2", &Nev_QCD2, &b_Nev_QCD2);
   fChain->SetBranchAddress("Nev_QCD3", &Nev_QCD3, &b_Nev_QCD3);
   fChain->SetBranchAddress("Nev_ILV", &Nev_ILV, &b_Nev_ILV);
   fChain->SetBranchAddress("Nev_ILVEMF", &Nev_ILVEMF, &b_Nev_ILVEMF);
   fChain->SetBranchAddress("Nev_1stjetEt", &Nev_1stjetEt, &b_Nev_1stjetEt);
   fChain->SetBranchAddress("Nev_2ndjetEt", &Nev_2ndjetEt, &b_Nev_2ndjetEt);
   fChain->SetBranchAddress("Nev_ht", &Nev_ht, &b_Nev_ht);
   
  vector<string> cuts;
  //  cuts.push_back("Two Reconstructed Electrons");
  cuts.push_back("Trigger" );
  cuts.push_back("MET > 200 GeV");
  cuts.push_back(">= 3jets");
  cuts.push_back("1st jet \|\eta\|<1.7");
  //  cuts.push_back("QCD1");
  //  cuts.push_back("QCD2");
  cuts.push_back("QCD3");
  cuts.push_back("Indirect Lepton Veto");
  //  cuts.push_back("Et>180 1st jet");
  cuts.push_back("Et1>180 & Et2>110");
  cuts.push_back("HT>500");

  //   cuts.push_back("Event EM fraction");
  //   cuts.push_back("Event Charged fraction");
  //   cuts.push_back("Indirect Lepton Veto EMF");
  //   cuts.push_back("SoB");

  int Ntotal = 0;

  vector<int> Npassed;
  for(int i=0; i< int(cuts.size()); i++)
    Npassed.push_back(0.);
  
  for(int i=0; i< fChain->GetEntries(); i++) {
    fChain->GetEntry(i);

    Ntotal += Nev;

    Npassed[0]  += Nev_Trigger;
    Npassed[1]  += Nev_MET;
    Npassed[2]  += Nev_3j;
    Npassed[3]  += Nev_eta1stjet;
    Npassed[4]  += Nev_QCD3;
    Npassed[5]  += Nev_ILV;
    //    Npassed[6] += Nev_1stjetEt; 
    //    Npassed[7] += Nev_2ndjetEt; 
    Npassed[6] += Nev_2ndjetEt; 

    Npassed[7] += Nev_ht; 

    //    Npassed[0]  += Nev_EEMF;
    //    Npassed[1]  += Nev_ECHF;
    //    Npassed[5]  += Nev_QCD1;
    //    Npassed[6]  += Nev_QCD2;
    //    Npassed[9] += Nev_ILVEMF;
  }

  cout << " Selection Summary" << endl;
  cout << " ------------------------------------------------------------------------" << endl;
  cout << " Cut                        |    Relative Eff.     |   Cumulative Eff    " << endl;
  cout << " ------------------------------------------------------------------------" << endl;

  cout << cuts[0] << " | " << double(Npassed[0])/Ntotal << " +/- " << sqrt(double(Npassed[0])/Ntotal*(1.-double(Npassed[0])/Ntotal)/Ntotal) << " | "
         << double(Npassed[0])/Ntotal   << " +/- " << sqrt(double(Npassed[0])/Ntotal*(1.-double(Npassed[0])/Ntotal)/Ntotal) << endl;

  cout << " ------------------------------------------------------------------------" << endl;
  for(int i=1; i< int(Npassed.size()); i++) {
    cout << cuts[i] << " | "
         << double(Npassed[i])/Npassed[i-1] << " +/- " << sqrt(double(Npassed[i])/Npassed[i-1]*(1.-double(Npassed[i])/Npassed[i-1])/Npassed[i-1]) << " | "
         << double(Npassed[i])/Ntotal   << " +/- " << sqrt(double(Npassed[i])/Ntotal*(1.-double(Npassed[i])/Ntotal)/Ntotal) << endl;
    cout << " ------------------------------------------------------------------------" << endl;
  }

}
