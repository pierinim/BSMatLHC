// generate a sample of gamma*/Z/Z' 
// following example manin02.cc  and main17.cc from pythia8

#include "Pythia8/Pythia.h"
#include "Pythia8/Pythia8ToHepMC.h"

#include "HepMC/GenEvent.h"
#include "HepMC/IO_GenEvent.h"
#include "HepMC/Units.h"

#include <TFile.h>
#include <TTree.h>
#include <TDatime.h>
#include <GenTree.hh>
#include <GenCandidateFiller.hh>

#include <stdio.h>
#include <string.h>
#include <unistd.h>

using namespace Pythia8; 

int main(int argc, char* argv[]) {

  if (argc < 3) {
    cerr << " Unexpected number of command-line arguments. \n You are"
	 << " expected to provide a number of events and an output file. \n"
	 << " To set the beam energy specify \n -setEnergy= *AFTER* the other options."
	 << " Supported Processes are:\n"
	 << " --W \n "
	 << "--DY \n"       
	 << " --WJets \n "
	 << "--DYJets \n"       
	 << " To set the min Pt^:\n"
	 << " -pTmin=\n"
	 << " Additional PYTHIA options can be loaded as: \n"
	 << "-pythiaCard=\n" 
	 << endl;
      //	 << "--TTJets (NOT YET)" 
      return 1;
  }

  int Nevents = 0;
  sscanf(argv[1],"%i",&Nevents);
  
  float energy = 8000.;
  vector<string> process;
  char tmpString[512];
  char pythiaCard[512] = "none";
  float pTmin = -1.;
  for (int i=1;i<argc;i++){  
    if(strncmp(argv[i],"-pTmin=",6)==0) {
      sscanf(argv[i],"-pTmin=%f",&pTmin);
      sprintf(tmpString, "PhaseSpace:pTHatMin = %f", pTmin);
      process.push_back(string(tmpString));
    }
    if(strncmp(argv[i],"-setEnergy=",11)==0) sscanf(argv[i],"-setEnergy=%f",&energy);
    if(strncmp(argv[i],"--WJets",7)==0) {
      sprintf(tmpString,"WeakBosonAndParton:qqbar2Wg = on"); process.push_back(string(tmpString));
      sprintf(tmpString,"WeakBosonAndParton:qg2Wq = on"); process.push_back(string(tmpString));
      sprintf(tmpString,"WeakBosonAndParton:ffbar2Wgm = on"); process.push_back(string(tmpString));
      sprintf(tmpString,"WeakBosonAndParton:fgm2Wf = on"); process.push_back(string(tmpString));
      process.push_back("24:mMin = 20.");
    } else if(strncmp(argv[i],"--W",3)==0) sprintf(tmpString,"WeakSingleBoson:ffbar2W = on"); process.push_back(string(tmpString));

    if (strncmp(argv[i],"--DYJets",8)==0) {
      sprintf(tmpString,"WeakBosonAndParton:qqbar2gmZg = on"); process.push_back(string(tmpString));
      sprintf(tmpString,"WeakBosonAndParton:qg2gmZq = on"); process.push_back(string(tmpString));
      sprintf(tmpString,"WeakBosonAndParton:ffbar2gmZgm = on"); process.push_back(string(tmpString));
      sprintf(tmpString,"WeakBosonAndParton:fgm2gmZf = on"); process.push_back(string(tmpString));
    } else if(strncmp(argv[i],"--DY",3)==0) sprintf(tmpString,"WeakSingleBoson:ffbar2gmZ = on");  process.push_back(string(tmpString));
    if (strncmp(argv[i],"-pythiaCard=",11)==0) sscanf(argv[i],"-pythiaCard=%s",pythiaCard);
  }

  if(process.size() == 0) {
    cout << "Nothing to Generate (please specify a process). Exiting." <<endl;
    return 0;
  }

  // Interface for conversion from Pythia8::Event to HepMC one. 
  HepMC::Pythia8ToHepMC ToHepMC;
    
  // Generator. 
  Pythia pythia;
  // setup process
  
  for(int i=0; i<process.size(); i++) {
    if(process[i] != string("none")) pythia.readString(process[i].c_str()); 
  }
  // setup beams
  pythia.init(2212, 2212, energy);
  // Random Seed
  int jobpid = getpid();
  TDatime *now = new TDatime();
  int today = now->GetDate();
  int clock = now->GetTime();
  int myseed = today+clock+jobpid;
  if(myseed>900000000) myseed = myseed - 900000000;
  pythia.readString("Random:setSeed=on");
  char command[512];
  sprintf(command,"Random:seed=%i",myseed);
  pythia.readString(command);
  
  // force W-> mu nu
  pythia.readString("24:onMode = off");
  pythia.readString("24:onIfAny = 13 14");


  // Load additional PYTHIA setting
  cout << "THE PROCESS IS " << pythiaCard << endl;
  if(string(pythiaCard)  != string("none")) pythia.readFile(pythiaCard); 

  // List settings.
  pythia.settings.listChanged();
  pythia.particleData.listChanged();

  // the output file 
  char name[256];
  sprintf(name,"%s_GenTree.root", argv[2]);
  TFile* treeOut = new TFile(name,"recreate");

  // the output TTree with information on the model
  double xsec;
  TTree* infoTree = new TTree("infoTree", "infoTree");
  infoTree->Branch("xsec", &xsec, "xsec/D");

  // the event TTree
  GenTree* myTree = new GenTree("GenEvent","GenEvent");
  GenCandidateFiller* muonFiller = new GenCandidateFiller(myTree,"Muon");
  GenCandidateFiller* electronFiller = new GenCandidateFiller(myTree,"Electron");
  GenCandidateFiller* tauFiller = new GenCandidateFiller(myTree,"Tau");
  GenCandidateFiller* bFiller = new GenCandidateFiller(myTree,"b");
  GenCandidateFiller* photonFiller = new GenCandidateFiller(myTree,"Photon");
  GenCandidateFiller* neutrinoFiller = new GenCandidateFiller(myTree,"Neutrino");
  GenCandidateFiller* susyFiller = new GenCandidateFiller(myTree,"SUSY");
  GenCandidateFiller* particleFiller = new GenCandidateFiller(myTree,"Particle");

  // Begin event loop.
  for (int iEvent = 0; iEvent < Nevents; ++iEvent) {
    if (!pythia.next()) continue;
    
    // Construct new empty HepMC event. 
    HepMC::GenEvent* hepmcevt = new HepMC::GenEvent();
    // Fill HepMC event, including PDF info.
    ToHepMC.fill_next_event( pythia, hepmcevt );
    
 // write event to root file
    muonFiller->FillEvent(hepmcevt);
    electronFiller->FillEvent(hepmcevt);
    tauFiller->FillEvent(hepmcevt);
    bFiller->FillEvent(hepmcevt);
    photonFiller->FillEvent(hepmcevt);
    neutrinoFiller->FillEvent(hepmcevt);
    susyFiller->FillEvent(hepmcevt);
    particleFiller->FillEvent(hepmcevt);

      // write data in TTree
    myTree->dumpData();

    // Clear the event from memory
    muonFiller->ClearEvent();
    electronFiller->ClearEvent();
    tauFiller->ClearEvent();
    bFiller->ClearEvent();
    photonFiller->ClearEvent();
    neutrinoFiller->ClearEvent();
    susyFiller->ClearEvent();
    particleFiller->ClearEvent();
    delete hepmcevt;

    // End of event loop.
  }

  // Write output file
  infoTree->Fill();
  TTree* roottree = myTree->getTree();
  roottree->Write();
  infoTree->Write();
  treeOut->Close();

  // Give statistics. 
  pythia.statistics();

  // Done.
  return 0;
}
