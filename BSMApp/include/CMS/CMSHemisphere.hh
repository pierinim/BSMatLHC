//-------------------------------------------------------
// Description:  CMS Hemisphere calculator
// Authors:      Maurizio Pierini, CERN
// Authors:      Christopher Rogan, Caltech
//-------------------------------------------------------

///  The CMSHemisphere class implements the 
///  algorithm to combine jets in hemispheres
///  as defined in CMS SUSY  searches

#ifndef CMSHemisphere_h
#define CMSHemisphere_h

#include <vector>
#include <iostream>
#include <TLorentzVector.h>

using namespace std;

class CMSHemisphere {

public:
  /// Constructor
  CMSHemisphere(vector<TLorentzVector> jets);

  /// Destructor
  ~CMSHemisphere();

  /// Return the hemisphere TLorentzVector;
  vector<TLorentzVector> GetHemispheres();

  /// Combining the jets in two hemispheres minimizing the 
  /// sum of the invariant masses of the two hemispheres
  void CombineMinMass();

  /// Combining the jets in two hemispheres minimizing the 
  /// difference of HT for the two hemispheres
  void CombineMinHT();

private:

  /// Combine the jets in all the possible pairs of hemispheres
  void Combine();

  vector<TLorentzVector> jIN;
  vector<TLorentzVector> jOUT;
  vector<TLorentzVector> j1;
  vector<TLorentzVector> j2;

};

#endif
