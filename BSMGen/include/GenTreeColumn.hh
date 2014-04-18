// -*- C++ -*-
//---------------------------------------------------------------------------------
//
// Description:
//    Class GenTreeColumn
//    Nested class hierarchy to hold information about GenTree columns.
// Author:
//    Emanuele Di Marco        (inspired by his GenTreeColumn)
//
//---------------------------------------------------------------------------------

#ifndef GenTreeColumn_h
#define GenTreeColumn_h

#include <vector>
#include <string>

class TTree;
class TBranch;

using namespace std;

// Parent class (abstract):
class GenTreeColumn {
public:
  GenTreeColumn( const char* l ) : 
    label( l ), useDefValue( false ), pointer( 0 ), brp( 0 ) {}
  virtual ~GenTreeColumn() {}
  virtual const std::string & getLabel() const { return label; }
  virtual TBranch* getBrPointer() { return brp; }
  virtual void* getPointer() { return pointer; }
  virtual void setPointer( void* p ) { pointer= p; }
  virtual void setUseDefValue( bool b ) { useDefValue= b; }
  virtual const bool & getUseDefValue() const { return useDefValue; }
  virtual void setDefValue() = 0;
  virtual void setValue( const void*, GenTreeColumn* cp= 0 ) = 0;
protected:
  std::string label; 
  bool useDefValue;
  void *pointer;
  TBranch* brp;
};

// Classes for bool:
class BoolGenTreeColumn : public GenTreeColumn {
public:
  BoolGenTreeColumn( const char*, const bool &, const bool &, TTree* );
  virtual ~BoolGenTreeColumn() { delete (char*)pointer; }
  virtual void setDefValue() { *(char*)pointer= defValue; }
  virtual void setValue( const void* p, GenTreeColumn* cp= 0 ) { 
    *(char*)pointer= *(const bool*)p;
  }
private:
  bool defValue;
};
class BoolArrGenTreeColumn : public GenTreeColumn {
public:
  BoolArrGenTreeColumn( const char*, const vector<bool> &, const bool &, 
		 TTree* );
  virtual ~BoolArrGenTreeColumn() { delete[] (char*)pointer; }
  virtual void setDefValue() { 
    for( int i= 0; i < nmax; ++i ) ((char*)pointer)[i]= defValue; 
  }
  virtual void setValue( const void*, GenTreeColumn* cp= 0 );
private:
  bool defValue;
  int nmax;
};
class BoolDynArrGenTreeColumn : public GenTreeColumn {
public:
  BoolDynArrGenTreeColumn( const char*, const vector<bool> &,
		    const bool &, GenTreeColumn*, TTree* );
  virtual ~BoolDynArrGenTreeColumn() { delete[] (char*)pointer; }
  virtual void setDefValue();
  virtual void setValue( const void*, GenTreeColumn* cp= 0 );
private:
  bool defValue;
  GenTreeColumn* indexp;
};

// Classes for int:
class IntGenTreeColumn : public GenTreeColumn {
public:
  IntGenTreeColumn( const char*, const int &, const int &, TTree* );
  virtual ~IntGenTreeColumn() { delete (int*)pointer; }
  virtual void setDefValue() { *(int*)pointer= defValue; }
  virtual void setValue( const void* p, GenTreeColumn* cp= 0 ) { 
    *(int*)pointer= *(const int*)p;
  }
private:
  int defValue;
};
class IntArrGenTreeColumn : public GenTreeColumn {
public:
  IntArrGenTreeColumn( const char*, const vector<int> &, const int &, 
		TTree* );
  virtual ~IntArrGenTreeColumn() { delete[] (int*)pointer; }
  virtual void setDefValue() { 
    for( int i= 0; i < nmax; ++i ) ((int*)pointer)[i]= defValue; 
  }
  virtual void setValue( const void*, GenTreeColumn* cp= 0 );
private:
  int defValue;
  int nmax;
};
class IntDynArrGenTreeColumn : public GenTreeColumn {
public:
  IntDynArrGenTreeColumn( const char*, const vector<int> &,
		   const int &, GenTreeColumn*, TTree* );
  virtual ~IntDynArrGenTreeColumn() { delete[] (int*)pointer; }
  virtual void setDefValue();
  virtual void setValue( const void*, GenTreeColumn* cp= 0 );
private:
  int defValue;
  GenTreeColumn* indexp;
};

// Classes for float:
class FloatGenTreeColumn : public GenTreeColumn {
public:
  FloatGenTreeColumn( const char*, const float &, const float &, TTree* );
  virtual ~FloatGenTreeColumn() { delete (float*)pointer; }
  virtual void setDefValue() { *(float*)pointer= defValue; }
  virtual void setValue( const void* p, GenTreeColumn* cp= 0 ) { 
    *(float*)pointer= *(const float*)p; 
  }
private:
  float defValue;
};
class FloatArrGenTreeColumn : public GenTreeColumn {
public:
  FloatArrGenTreeColumn( const char*, const vector<float> &, const float &, 
		  TTree* );
  virtual ~FloatArrGenTreeColumn() { delete[] (float*)pointer; }
  virtual void setDefValue() { 
    for( int i= 0; i < nmax; ++i ) ((float*)pointer)[i]= defValue; 
  }
  virtual void setValue( const void*, GenTreeColumn* cp= 0 );
private:
  float defValue;
  int nmax;
};
class FloatDynArrGenTreeColumn : public GenTreeColumn {
public:
  FloatDynArrGenTreeColumn( const char*, const vector<float> &,
		     const float &, GenTreeColumn*, TTree* );
  virtual ~FloatDynArrGenTreeColumn() { delete[] (float*)pointer; }
  virtual void setDefValue();
  virtual void setValue( const void*, GenTreeColumn* cp= 0 );
private:
  float defValue;
  GenTreeColumn* indexp;
};

// Classes for double:
class DoubleGenTreeColumn : public GenTreeColumn {
public:
  DoubleGenTreeColumn( const char*, const double &, const double &, TTree* );
  virtual ~DoubleGenTreeColumn() { delete (double*)pointer; }
  virtual void setDefValue() { *(double*)pointer= defValue; }
  virtual void setValue( const void* p, GenTreeColumn* cp= 0 ) { 
    *(double*)pointer= *(const double*)p; 
  }
private:
  double defValue;
};
class DoubleArrGenTreeColumn : public GenTreeColumn {
public:
  DoubleArrGenTreeColumn( const char*, const vector<double> &, 
		   const double &, TTree* );
  virtual ~DoubleArrGenTreeColumn() { delete[] (double*)pointer; }
  virtual void setDefValue() { 
    for( int i= 0; i < nmax; ++i ) ((double*)pointer)[i]= defValue; 
  }
  virtual void setValue( const void*, GenTreeColumn* cp= 0 );
private:
  double defValue;
  int nmax;
};
class DoubleDynArrGenTreeColumn : public GenTreeColumn {
public:
  DoubleDynArrGenTreeColumn( const char*, const vector<double> &,
		      const double &, GenTreeColumn*, TTree* );
  virtual ~DoubleDynArrGenTreeColumn() { delete[] (double*)pointer; }
  virtual void setDefValue();
  virtual void setValue( const void*, GenTreeColumn* cp= 0 );
private:
  double defValue;
  GenTreeColumn* indexp;
};

// Classes for string:
class StringGenTreeColumn : public GenTreeColumn {
public:
  StringGenTreeColumn( const char*, const string &, const string &, TTree* );
  virtual ~StringGenTreeColumn() { delete[] (char*)pointer; }
  virtual void setDefValue();
  virtual void setValue( const void* p, GenTreeColumn* cp= 0 );
private:
  string defValue;
};

#endif  // GenTreeColumn_h
