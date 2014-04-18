#include "Pythia.h"
#include <stdio.h>
#include <string.h>

using namespace Pythia8; 

int main(int argc, char* argv[]) {

  // Check that correct number of command-line arguments
  if (argc != 3) {
    cerr << " To run the code provide the name of the input pythia card and the output LHE file. \n"
	 << " example: ./SLHAGen data/pythiaCards/SLHAGen_LHC7TeV.pythia outLHE.lhe \n" << endl;
    return 1;
  }

  // Check that the provided input name corresponds to an existing file.
  ifstream is(argv[1]);  
  if (!is) {
    cerr << " Command-line file " << argv[1] << " was not found. \n"
         << " Program stopped! " << endl;
    return 1;
  }

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

  // Switch off generation of steps subsequent to the process level one. 
  // (These will not be stored anyway, so only steal time.)
  pythia.readString("PartonLevel:all = off");

  // Create an LHAup object that can access relevant information in pythia. 
  LHAupFromPYTHIA8 myLHA(&pythia.process, &pythia.info);

  // Open a file on which LHEF events should be stored, and write header. 
  myLHA.openLHEF(argv[2]);
  
  // Store initialization info in the LHAup object. 
  myLHA.setInit();

  // Write out this initialization info on the file. 
  myLHA.initLHEF();

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

    // Store event info in the LHAup object.                                                                                                
    myLHA.setEvent();

    // Write out this event info on the file.                                                                                               
    myLHA.eventLHEF();
 
    // List first few events.
    if (iEvent < nList) { 
      pythia.info.list();
      pythia.event.list();
    }

  }
  
  // Give statistics. 
  pythia.statistics();

  // Update the cross section info based on Monte Carlo integration during run.                                                             
  myLHA.updateSigma();
  
  // Write endtag. Overwrite initialization info with new cross sections.                                                                   
  myLHA.closeLHEF(true);
  
  // Done.
  return 0;
}
