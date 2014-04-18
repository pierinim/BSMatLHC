// -*- C++ -*-
//---------------------------------------------------------------------------------
//
// Description:
//    Class CmsTreeColumn
//    Nested class hierarchy to hold information about CmsTree columns.
// Author:
//    Emanuele Di Marco        (inspired by his GenTreeColumn)
//
//---------------------------------------------------------------------------------

#include <memory>

#include <GenTreeColumn.hh>
#include <TTree.h>
#include <TBranch.h>
#include <iostream>

using namespace std;


// Bool columns, stored as char (= 8 bit signed int):
BoolGenTreeColumn::BoolGenTreeColumn( const char* l, const bool & v, const bool & d, 
			TTree* tp ) : 
  GenTreeColumn( l ), defValue( d ) {
				 
  // Create a new branch:
  pointer= new char;
  *(char*)pointer= v;
  std::string leafs( l ) ;
  leafs+= "/b";
  brp= tp->Branch( label.c_str(), pointer, leafs.c_str(), 8000 );

}
BoolArrGenTreeColumn::BoolArrGenTreeColumn( const char* l, 
			      const vector<bool> & v, 
			      const bool & d, TTree* tp ) :
  GenTreeColumn( l ), defValue( d ) {

  // Create a new branch:
  nmax= v.size();
  char* bp= new char[nmax];
  pointer= bp;
  for( int i= 0; i < nmax; ++i ) bp[i]= v[i];
  std::string leafs( label.c_str() );
  leafs+= "[";
  char buf[33];
  sprintf( buf, "%i", nmax );
  leafs+= buf;
  leafs+= "]/b";
  brp= tp->Branch( label.c_str(), &bp[0], leafs.c_str(), 8000 );

}
void BoolArrGenTreeColumn::setValue( const void* p, GenTreeColumn* cp ) { 

  const vector<bool>* vp= (const vector<bool>*) p;
  if( (int)vp->size() < nmax ) {
    std::cerr << "BoolArrGenTreeColumn::setValue: input vector too short, "
	 << "use default values" << std::endl;
    setDefValue();
  }
  else {
    for( int i= 0; i < nmax; ++i ) ((char*)pointer)[i]= (*vp)[i];
  }

}
BoolDynArrGenTreeColumn::BoolDynArrGenTreeColumn( const char* l, 
				    const vector<bool> & v, 
				    const bool & d, GenTreeColumn* inp,
				    TTree* tp ) :
  GenTreeColumn( l ), defValue( d ), indexp( inp ) {

  // Make a new branch:
  int* np= (int*) indexp->getPointer();
  char* bp= new char[*np];
  pointer= bp;
  for( int i= 0; i < *np; ++i ) bp[i]= v[i];
  std::string leafs( label.c_str() );
  leafs+= "[";
  leafs+= indexp->getLabel();
  leafs+= "]/b";
  brp= tp->Branch( label.c_str(), &bp[0], leafs.c_str(), 8000 );

}
void BoolDynArrGenTreeColumn::setDefValue() {

  if( pointer ) delete [] (char*)pointer;
  int nmax= *((int*)(indexp->getPointer()));
  char* bp= new char[nmax];
  pointer= bp;
  for( int i= 0; i < nmax; ++i ) bp[i]= defValue; 
  brp->SetAddress( &bp[0] );

}
void BoolDynArrGenTreeColumn::setValue( const void* p, GenTreeColumn* cp ) {

  const vector<bool>* vp= (const vector<bool>*) p;
  int* np= (int*) cp->getPointer();
  if( *np > (int)vp->size() ) {
    std::cerr << "BoolDynArrGenTreeColumn::setValue: input vector too short, "
	 << "use default values" << std::endl;
    setDefValue();
  }
  else {
    char* bp= new char[*np];
    if( pointer ) delete[] (char*)pointer;
    pointer= bp;
    for( int i= 0; i < *np; ++i ) bp[i]= (*vp)[i];
    brp->SetAddress(  &bp[0] );
  }

}


// Int columns:
IntGenTreeColumn::IntGenTreeColumn( const char* l, const int & v, const int & d, 
		      TTree* tp ) : 
  GenTreeColumn( l ), defValue( d ) {
				 
  // Create a new branch:
  pointer= new int;
  *(int*)pointer= v;
  std::string leafs( l ) ;
  leafs+= "/I";
  brp= tp->Branch( label.c_str(), pointer, leafs.c_str(), 8000 );

}
IntArrGenTreeColumn::IntArrGenTreeColumn( const char* l, 
			    const vector<int> & v, 
			    const int & d, TTree* tp ) :
  GenTreeColumn( l ), defValue( d ) {

  // Create a new branch:
  nmax= v.size();
  int* ip= new int[nmax];
  pointer= ip;
  for( int i= 0; i < nmax; ++i ) ip[i]= v[i];
  std::string leafs( label.c_str() );
  leafs+= "[";
  char buf[33];
  sprintf( buf, "%i", nmax );
  leafs+= buf;
  leafs+= "]/I";
  brp= tp->Branch( label.c_str(), &ip[0], leafs.c_str(), 8000 );
  
}
void IntArrGenTreeColumn::setValue( const void* p, GenTreeColumn* cp ) { 

  const vector<int>* vp= (const vector<int>*) p;
  if( (int)vp->size() < nmax ) {
    std::cerr << "IntArrGenTreeColumn::setValue: input vector too short, "
	 << "use default values" << std::endl;
    setDefValue();
  }
  else {
    for( int i= 0; i < nmax; ++i ) ((int*)pointer)[i]= (*vp)[i];
  }

}
IntDynArrGenTreeColumn::IntDynArrGenTreeColumn( const char* l, 
				  const vector<int> & v, 
				  const int & d, GenTreeColumn* inp,
				  TTree* tp ) :
  GenTreeColumn( l ), defValue( d ), indexp( inp ) {

  // Make a new branch:
  int* np= (int*) indexp->getPointer();
  int* ip= new int[*np];
  pointer= ip;
  for( int i= 0; i < *np; ++i ) ip[i]= v[i];
  std::string leafs( label.c_str() );
  leafs+= "[";
  leafs+= indexp->getLabel();
  leafs+= "]/I";
  brp= tp->Branch( label.c_str(), &ip[0], leafs.c_str(), 8000 );

}
void IntDynArrGenTreeColumn::setDefValue() {

  if( pointer ) delete [] (int*)pointer;
  int nmax= *((int*)(indexp->getPointer()));
  int* ip= new int[nmax];
  pointer= ip;
  for( int i= 0; i < nmax; ++i ) ip[i]= defValue; 
  brp->SetAddress( &ip[0] );

}
void IntDynArrGenTreeColumn::setValue( const void* p, GenTreeColumn* cp ) {

  const vector<int>* vp= (const vector<int>*) p;
  int* np= (int*) cp->getPointer();
  if( *np > (int)vp->size() ) {
    std::cerr << "IntDynArrGenTreeColumn::setValue: input vector too short, "
	 << "use default values" << std::endl;
    setDefValue();
  }
  else {
    int* ip= new int[*np];
    if( pointer ) delete[] (int*)pointer;
    pointer= ip;
    for( int i= 0; i < *np; ++i ) ip[i]= (*vp)[i];
    brp->SetAddress(  &ip[0] );
  }

}

// Float columns:
FloatGenTreeColumn::FloatGenTreeColumn( const char* l, const float & v, 
			  const float & d, 
			  TTree* tp ) : 
  GenTreeColumn( l ), defValue( d ) {
				 
  // Create a new branch:
  pointer= new float;
  *(float*)pointer= v;
  std::string leafs( l ) ;
  leafs+= "/F";
  brp= tp->Branch( label.c_str(), pointer, leafs.c_str(), 8000 );

}
FloatArrGenTreeColumn::FloatArrGenTreeColumn( const char* l, 
				const vector<float> & v, 
				const float & d, TTree* tp ) :
  GenTreeColumn( l ), defValue( d ) {

  // Create a new branch:
  nmax= v.size();
  float* fp= new float[nmax];
  pointer= fp;
  for( int i= 0; i < nmax; ++i ) fp[i]= v[i];
  std::string leafs( label.c_str() );
  leafs+= "[";
  char buf[33];
  sprintf( buf, "%i", nmax );
  leafs+= buf;
  leafs+= "]/F";
  brp= tp->Branch( label.c_str(), &fp[0], leafs.c_str(), 8000 );
  
}
void FloatArrGenTreeColumn::setValue( const void* p, GenTreeColumn* cp ) { 

  const vector<float>* vp= (const vector<float>*) p;
  if( (int)vp->size() < nmax ) {
    std::cerr << "FloatArrGenTreeColumn::setValue: input vector too short, "
	 << "use default values" << std::endl;
    setDefValue();
  }
  else {
    for( int i= 0; i < nmax; ++i ) ((float*)pointer)[i]= (*vp)[i];
  }

}
FloatDynArrGenTreeColumn::FloatDynArrGenTreeColumn( const char* l, 
				      const vector<float> & v, 
				      const float & d, GenTreeColumn* ip,
				      TTree* tp ) :
  GenTreeColumn( l ), defValue( d ), indexp( ip ) {

  // Make a new branch:
  int* np= (int*) indexp->getPointer();
  float* fp= new float[*np];
  pointer= fp;
  for( int i= 0; i < *np; ++i ) fp[i]= v[i];
  std::string leafs( label.c_str() );
  leafs+= "[";
  leafs+= indexp->getLabel();
  leafs+= "]/F";
  brp= tp->Branch( label.c_str(), &fp[0], leafs.c_str(), 8000 );

}
void FloatDynArrGenTreeColumn::setDefValue() {

  if( pointer ) delete [] (float*)pointer;
  int nmax= *((int*)(indexp->getPointer()));
  float* fp= new float[nmax];
  pointer= fp;
  for( int i= 0; i < nmax; ++i ) fp[i]= defValue; 
  brp->SetAddress( &fp[0] );

}
void FloatDynArrGenTreeColumn::setValue( const void* p, GenTreeColumn* cp ) {

  const vector<float>* vp= (const vector<float>*) p;
  int* np= (int*) cp->getPointer();
  if( *np > (int)vp->size() ) {
    std::cerr << "IntDynArrGenTreeColumn::setValue: input vector too short, "
	 << "use default values" << std::endl;
    setDefValue();
  }
  else {
    float* fp= new float[*np];
    if( pointer ) delete[] (float*)pointer;
    pointer= fp;
    for( int i= 0; i < *np; ++i ) fp[i]= (*vp)[i];
    brp->SetAddress(  &fp[0] );
  }

}


// Double columns:
DoubleGenTreeColumn::DoubleGenTreeColumn( const char* l, const double & v, 
			    const double & d, TTree* tp ) : 
  GenTreeColumn( l ), defValue( d ) {
				 
  // Create a new branch:
  pointer= new double;
  *(double*)pointer= v;
  std::string leafs( l ) ;
  leafs+= "/D";
  brp= tp->Branch( label.c_str(), pointer, leafs.c_str(), 8000 );

}
DoubleArrGenTreeColumn::DoubleArrGenTreeColumn( const char* l, 
				  const vector<double> & v, 
				  const double & d, TTree* tp ) :
  GenTreeColumn( l ), defValue( d ) {

  // Create a new branch:
  nmax= v.size();
  double* dp= new double[nmax];
  pointer= dp;
  for( int i= 0; i < nmax; ++i ) dp[i]= v[i];
  std::string leafs( label.c_str() );
  leafs+= "[";
  char buf[33];
  sprintf( buf, "%i", nmax );
  leafs+= buf;
  leafs+= "]/D";
  brp= tp->Branch( label.c_str(), &dp[0], leafs.c_str(), 8000 );
  
}
void DoubleArrGenTreeColumn::setValue( const void* p, GenTreeColumn* cp ) { 

  const vector<double>* vp= (const vector<double>*) p;
  if( (int)vp->size() < nmax ) {
    std::cerr << "DoubleArrGenTreeColumn::setValue: input vector too short, "
	 << "use default values" << std::endl;
    setDefValue();
  }
  else {
    for( int i= 0; i < nmax; ++i ) ((double*)pointer)[i]= (*vp)[i];
  }

}
DoubleDynArrGenTreeColumn::DoubleDynArrGenTreeColumn( const char* l, 
					const vector<double> & v, 
					const double & d, GenTreeColumn* ip,
					TTree* tp ) :
  GenTreeColumn( l ), defValue( d ), indexp( ip ) {

  // Make a new branch:
  int* np= (int*)(indexp->getPointer());
  double* dp= new double[*np];
  pointer= dp;
  for( int i= 0; i < *np; ++i ) dp[i]= v[i];
  std::string leafs( label.c_str() );
  leafs+= "[";
  leafs+= indexp->getLabel();
  leafs+= "]/D";
  brp= tp->Branch( label.c_str(), &dp[0], leafs.c_str(), 8000 );

}
void DoubleDynArrGenTreeColumn::setDefValue() {

  if( pointer ) delete [] (double*)pointer;
  int nmax= *((int*)(indexp->getPointer()));
  double* dp= new double[nmax];
  pointer= dp;
  for( int i= 0; i < nmax; ++i ) dp[i]= defValue; 
  brp->SetAddress( &dp[0] );

}
void DoubleDynArrGenTreeColumn::setValue( const void* p, GenTreeColumn* cp ) {

  const vector<double>* vp= (const vector<double>*) p;
  int* np= (int*) cp->getPointer();
  if( *np > (int)vp->size() ) {
    std::cerr << "IntDynArrGenTreeColumn::setValue: input vector too short, "
	 << "use default values" << std::endl;
    setDefValue();
  }
  else {
    double* dp= new double[*np];
    if( pointer ) delete[] (double*)pointer;
    pointer= dp;
    for( int i= 0; i < *np; ++i ) dp[i]= (*vp)[i];
    brp->SetAddress(  &dp[0] );
  }

}


// String columns:
StringGenTreeColumn::StringGenTreeColumn( const char* lb, const string & v, 
                                          const string & d, TTree* tp ) : 
  GenTreeColumn( lb ), defValue( d ) {
				 
  // Create a new branch:
  int l = v.length();
  char* cp = new char[l+1];
  pointer= cp;
  strcpy( cp, v.c_str() );
  std::string leafs( lb ) ;
  leafs+= "/C";
  brp= tp->Branch( label.c_str(), pointer, leafs.c_str(), 8000 );

}

void StringGenTreeColumn::setDefValue() {

  if( pointer ) delete[] (char*)pointer;
  int l= defValue.length();
  char* cp= new char[l+1];
  pointer= cp;
  strcpy( cp, defValue.c_str() );
  brp->SetAddress( &cp[0] );

}

void StringGenTreeColumn::setValue( const void* p, GenTreeColumn* cp ) {

  const char* cpin= (const char*) p;
  if( pointer ) delete[] (char*)pointer;
  int l= strlen( cpin );
  char* chp= new char[l+1];
  pointer= chp;
  strcpy( chp, cpin );
  brp->SetAddress( &chp[0] );

}
