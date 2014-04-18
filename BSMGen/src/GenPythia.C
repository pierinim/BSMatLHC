#include "Pythia8/Pythia.h"
#include "Pythia8/Pythia8ToHepMC.h"

#include "HepMC/GenEvent.h"
#include "HepMC/IO_GenEvent.h"
#include "HepMC/Units.h"

#include <TFile.h>
#include <TTree.h>
#include <GenTree.hh>
#include <GenCandidateFiller.hh>

#include <stdio.h>
#include <string.h>

using namespace Pythia8; 

int main(int argc, char* argv[]) {

  // Check that correct number of command-line arguments
  if (argc != 3) {
    cerr << " To run the code provide the name of the input pythia card and the output LHE file. \n"
	 << " example: ./GenPythia data/pythiaCards/EXO/RSGraviton_gg_EXAMPLE.pythia outFile.root \n" << endl;
    return 1;
  }

  // Check that the provided input name corresponds to an existing file.
  ifstream is(argv[1]);  
  if (!is) {
    cerr << " Command-line file " << argv[1] << " was not found. \n"
         << " Program stopped! " << endl;
    return 1;
  }

  // Interface for conversion from Pythia8::Event to HepMC one. 
  HepMC::Pythia8ToHepMC ToHepMC;
  // Switch off warnings for parton-level events.
  ToHepMC.set_print_inconsistency(false);
  ToHepMC.set_free_parton_warnings(false);

  // Confirm that external files will be used for input and output.
  cout << " PYTHIA settings will be read from file " << argv[1] << endl;
 
  // Generator. 
  Pythia pythia;

  // Read in commands from external file.
  pythia.readFile(argv[1]);    

  // Initialize. Beam parameters set in .pythia file.
  pythia.init();

  // Extract settings to be used in the main program.
  int nEvent   = pythia.mode("Main:numberOfEvents");
  int nList    = pythia.mode("Main:numberToList");
  int nShow    = pythia.mode("Main:timesToShow");
  int nAbort   = pythia.mode("Main:timesAllowErrors"); 
  bool showCS  = pythia.flag("Main:showChangedSettings");
  bool showAS  = pythia.flag("Main:showAllSettings");
  bool showCPD = pythia.flag("Main:showChangedParticleData");
  bool showAPD = pythia.flag("Main:showAllParticleData");  

  // List settings.
  if (showCS) pythia.settings.listChanged();
  if (showAS) pythia.settings.listAll();

  // List particle data.  
  if (showCPD) pythia.particleData.listChanged();
  if (showAPD) pythia.particleData.listAll();

  // the output file 
  char name[256];
  sprintf(name,"%s", argv[2]);
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
  GenCandidateFiller* cFiller = new GenCandidateFiller(myTree,"c");
  GenCandidateFiller* photonFiller = new GenCandidateFiller(myTree,"Photon");
  GenCandidateFiller* neutrinoFiller = new GenCandidateFiller(myTree,"Neutrino");
  GenCandidateFiller* susyFiller = new GenCandidateFiller(myTree,"SUSY");
  GenCandidateFiller* gentreeparticleFiller = new GenCandidateFiller(myTree,"GenTreeParticle");
  GenCandidateFiller* particleFiller = new GenCandidateFiller(myTree,"Particle");

  // Begin event loop.
  int nPace = max(1, nEvent / max(1, nShow) ); 
  int iAbort = 0;
  for (int iEvent = 0; iEvent < nEvent; ++iEvent) {
    if (nShow > 0 && iEvent%nPace == 0) 
      cout << " Now begin event " << iEvent << endl;

    // Generate events. Quit if many failures.
    if (!pythia.next()) {
      // First few failures write off as "acceptable" errors, then quit.
      if (++iAbort < nAbort) continue;
      cout << " Event generation aborted prematurely, owing to error!\n"; 
      break;
    }
 
    // List first few events.
    if (iEvent < nList) { 
      pythia.info.list();
      pythia.event.list();
    }

    // Construct new empty HepMC event. 
    HepMC::GenEvent* hepmcevt = new HepMC::GenEvent();
    // Fill HepMC event, including PDF info.
    ToHepMC.fill_next_event( pythia, hepmcevt );
    
    // write event to root file
    muonFiller->FillEvent(hepmcevt);
    electronFiller->FillEvent(hepmcevt);
    tauFiller->FillEvent(hepmcevt);
    bFiller->FillEvent(hepmcevt);
    cFiller->FillEvent(hepmcevt);
    photonFiller->FillEvent(hepmcevt);
    neutrinoFiller->FillEvent(hepmcevt);
    susyFiller->FillEvent(hepmcevt);
    gentreeparticleFiller->FillEvent(hepmcevt);
    particleFiller->FillEvent(hepmcevt);

    // write data in TTree
    myTree->dumpData();

    // Clear the event from memory
    muonFiller->ClearEvent();
    electronFiller->ClearEvent();
    tauFiller->ClearEvent();
    bFiller->ClearEvent();
    cFiller->ClearEvent();
    photonFiller->ClearEvent();
    neutrinoFiller->ClearEvent();
    susyFiller->ClearEvent();
    gentreeparticleFiller->ClearEvent();
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
