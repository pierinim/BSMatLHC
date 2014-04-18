// generate a sample of gamma*/Z/Z' 
// following example manin02.cc  and main17.cc from pythia8


#include "Pythia.h"
#include "HepMCInterface.h"

#include "HepMC/GenEvent.h"
#include "HepMC/IO_GenEvent.h"
#include "HepMC/Units.h"

#include <stdio.h>
#include <string.h>

using namespace Pythia8; 

int main(int argc, char* argv[]) {

  if (argc < 3) {
    cerr << " Unexpected number of command-line arguments. \n You are"
	 << " expected to provide a number of events and an output file. \n"
         << "By default, this executable generates events wil 800<m(ff)<100"
	 << " and no Z'."
	 << "To generate a Z', pass a positive value of Z' mass:"
	 << " -massZp=MASSVALUE"
	 << "To extend the mass range:"
	 << " -mMin=MinMass"
	 << " -mMax=MaxMass"
       << " Program stopped! " << endl;
    return 1;
  }

  int Nevents = 0;
  sscanf(argv[1],"%i",&Nevents);
  string hepmcout(string(argv[2])+".hepmc");
  
  float energy = 14000.;
  float mMin = 80.;
  float mMax = 100;
  float massZp = -99.;
  for (int i=1;i<argc;i++){  
    if (strncmp(argv[i],"-setEnergy=",11)==0) sscanf(argv[i],"-setEnergy=%f",&energy);
    if (strncmp(argv[i],"-massZp=",8)==0)  {
      sscanf(argv[i],"-massZp=%f",&massZp);
      cout << "WARNING: gamma*/Z/Z' (with Z'mass " << massZp << ") will be generated" << endl;
    } else {
      cout << "WARNING: gamma*/Z will be generated" << endl;
    }
    if (strncmp(argv[i],"-mMin=",5)==0)       sscanf(argv[i],"-mMin=%f",&mMin);
    if (strncmp(argv[i],"-mMax=",5)==0)       sscanf(argv[i],"-mMax=%f",&mMax);
  }

  // Interface for conversion from Pythia8::Event to HepMC one. 
  HepMC::I_Pythia8 ToHepMC;
  
  // Specify file where HepMC events will be stored.
  HepMC::IO_GenEvent ascii_io(hepmcout.c_str(), std::ios::out);

  // Generator. 
  Pythia pythia;
  char command[512];
  if(massZp<0.) {
    pythia.readString("WeakSingleBoson:ffbar2gmZ = on"); 
    sprintf(command, "PhaseSpace:mHatMin = %f", mMin);  
    pythia.readString(command);    
    sprintf(command, "PhaseSpace:mHatMax = %f", mMax);  
    pythia.readString(command);    
  } else {
    pythia.readString("NewGaugeBoson:ffbar2gmZZprime = on ! full gamma*/Z^0/Z'^0 production");
    sprintf(command, "32:m0 = 1000.                      ! Z' mass", massZp);  
    pythia.readString(command);    
    sprintf(command, "32:mMin = %f ", mMin);  
    pythia.readString(command);    
    sprintf(command, "32:mMax = %f ", mMax);  
    pythia.readString(command);    
  }
  // setup energy
  pythia.init(2212, 2212, energy);

  // List settings.
  pythia.settings.listChanged();

  // List particle data.  
  pythia.particleData.listChanged();
  for (int iEvent = 0; iEvent < Nevents; ++iEvent) {
    if (!pythia.next()) continue;
    
    // Construct new empty HepMC event. 
    HepMC::GenEvent* hepmcevt = new HepMC::GenEvent();
    // Fill HepMC event, including PDF info.
    ToHepMC.fill_next_event( pythia, hepmcevt );
    
    // Write the HepMC event to file. Done with it.
    ascii_io << hepmcevt;
    delete hepmcevt;

    // End of event loop.
  }

    // Give statistics. 
  pythia.statistics();
 
  // run Delphes
  string OUTPUT_ATLAS = string(argv[2])+"_DelphesATLAS.root";
  string OUTPUT_CMS   = string(argv[2])+"_DelphesCMS.root";

  system(string(string("echo ")+string(hepmcout)+string(" >> ")+string(hepmcout)+string(".list")).c_str());
  system(string(string("cd Delphes; ./Delphes ")+string(hepmcout)+string(".list ")+OUTPUT_ATLAS+string(" data/DetectorCard_ATLAS.dat data/TriggerCard_ATLAS.dat")).c_str());
  system(string(string("cd Delphes; ./Delphes ")+string(hepmcout)+string(".list ")+OUTPUT_CMS+string(" data/DetectorCard_CMS.dat data/TriggerCard_CMS.dat")).c_str());
  system(string(string("rm ")+string(hepmcout)+string(".list")).c_str());

  // Done.
  return 0;
}
