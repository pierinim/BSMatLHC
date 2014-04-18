// Take the spectrum of SUSY events as input
// and generate the table of decays

#include "Pythia8/Pythia.h"
#include <stdio.h>
#include <string.h>

using namespace Pythia8; 

int main(int argc, char* argv[]) {

  // Check that correct number of command-line arguments
  if (argc < 2) {
    cerr << " Unexpected number of command-line arguments. \n You are"
         << " expected to provide one input SLHA file name. \n"
         << " Program stopped! " << endl;
    return 1;
  }

  bool verbose = false;
  bool doDecay = false;
  float energy = 14000.;
  for (int i=1;i<argc;i++){  
    if (strncmp(argv[i],"--verbose",9)==0)  verbose = true;
    if (strncmp(argv[i],"--doDecay",9)==0)  doDecay = true;
    if (strncmp(argv[i],"-setEnergy=",11)==0)  {
      sscanf(argv[i],"-setEnergy=%f",&energy);
    }
  }

  // Check that the provided input name corresponds to an existing file.
  ifstream is(argv[1]);  
  if (!is) {
    cerr << " Command-line file " << argv[1] << " was not found. \n"
	 << " Program stopped! " << endl;
    return 1;
  }
  
  // Confirm that external files will be used for input and output.
  cout << " SLHA file " << argv[1] << " will be processes" << endl;
  if(doDecay) cout << "Pythia will compute BR for SUSY decays" << endl;

  string option = "SLHA:file = "+string(argv[1]);

  // Generator. 
  Pythia pythia;
  pythia.readString("SUSY:all = on");
  pythia.readString("SLHA:readFrom = 3");
  pythia.readString(option.c_str());
  if(doDecay) {
    pythia.readString("SLHA:useDecayTable = off");
  } else {
    pythia.readString("SLHA:useDecayTable = on");
  }
  if(verbose) pythia.readString(" SLHA:verbose = 3");
  if(verbose) cout << "ciaoooo" << endl;
  // Initialize. Beam parameters set in .pythia file.
  pythia.init(2212, 2212, energy);

  // List settings.
  pythia.settings.listChanged();
  //  pythia.settings.listAll();

  // List particle data.  
  pythia.particleData.listChanged();
  //  pythia.particleData.listAll();

  // Generate one dummy event
  pythia.next();  
  pythia.info.list();
  //  pythia.event.list();

  // Done.
  return 0;
}
