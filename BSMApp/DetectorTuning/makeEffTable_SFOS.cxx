#include <vector.h>
using namespace std;

void makeEffTable_SFOS(string filename) {
  TFile* file = new TFile(filename.c_str());
  TTree* fChain = (TTree*) file->Get("CMS_DiLepSFOSAnalysis/effTree");

  // Declaration of leaf types
   Int_t           Nev;
   Int_t           Nev_Trigger;
   Int_t           Nev_MET;
   Int_t           Nev_2j;
   Int_t           Nev_SFOS;

   // List of branches
   TBranch        *b_Nev;   //!
   TBranch        *b_Nev_Trigger;   //!
   TBranch        *b_Nev_MET;   //!
   TBranch        *b_Nev_2j;   //!
   TBranch        *b_Nev_SFOS;   //!

   fChain->SetBranchAddress("Nev", &Nev, &b_Nev);
   fChain->SetBranchAddress("Nev_Trigger", &Nev_Trigger, &b_Nev_Trigger);
   fChain->SetBranchAddress("Nev_MET", &Nev_MET, &b_Nev_MET);
   fChain->SetBranchAddress("Nev_SFOS", &Nev_SFOS, &b_Nev_SFOS);
   fChain->SetBranchAddress("Nev_2j", &Nev_2j, &b_Nev_2j);
   
  vector<string> cuts;
  //  cuts.push_back("Two Reconstructed Electrons");
  cuts.push_back("Trigger" );
  cuts.push_back("MET > 200 GeV");
  cuts.push_back("SFOS");
  cuts.push_back(">= 2jets");

  int Ntotal = 0;

  vector<int> Npassed;
  for(int i=0; i< int(cuts.size()); i++)
    Npassed.push_back(0.);
  
  for(int i=0; i< fChain->GetEntries(); i++) {
    fChain->GetEntry(i);

    Ntotal += Nev;

    Npassed[0]  += Nev_Trigger;
    Npassed[1]  += Nev_MET;
    Npassed[2]  += Nev_SFOS;
    Npassed[3]  += Nev_2j;
  }

  if(Ntotal == 0.) return;

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
