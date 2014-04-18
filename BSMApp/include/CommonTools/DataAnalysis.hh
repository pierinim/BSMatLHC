//--------------------------------------------------------------
// Description:  Generic Data Analysis 
// Authors:      Maurizio Pierini, CERN
//--------------------------------------------------------------

#ifndef DataAnalysis_h
#define DataAnalysis_h

#include "StatTools.hh"

class DataAnalysis {

public:
  //! constructor
  DataAnalysis();
  //! destructor
  ~DataAnalysis();
  
protected:
  // luminosity
  double _Lumi;
  // Basic Statistics Tools
  StatTools* _statTools;
  // analysis name
  string _analysis;


private:

};

#endif
