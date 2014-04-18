// -*- C++ -*-
//---------------------------------------------------------------------------------
//
// Description:
//    Class GenTree
//
// The member function "column" provides the data for a column of the ntuple.
// The string is the label of the column as well as being a unique identifier
// of the column. The second argument provides the data (float or int) for
// one row in the column. Note that only one line of code is needed to
// define the column (if it has not been seen previously) and provide the
// data for each "event". 
//
// The third argument of "column()" provides the default value for that
// column (if it not provided, it defaults to 0.0). On a particular "event",
// if no call is made to "column" for a particular column, that column's
// default value is used when filling the ntuple. Therefore, the default
// value should be set to an "unphysical" number.
//
// At the end of an "event", a call should be made to either "dumpData()" or
// "clearData()". "dumpData()" dumps all the data it has stored internally
// into the ntuple and then calls "clearData()".
// "clearData()" sets all the internal column values to their defaults,
// without changing the ntuple. Therefore, if you want to keep the data
// that is presently in an NTuple, call "dumpData()"; else, call
// "clearData()". 
//
// Author:
//    Emanuele Di Marco        (inspired by his CmsTree)
//
//---------------------------------------------------------------------------------

#ifndef CmsTree_h
#define CmsTree_h

#include <GenTreeColumn.hh>
#include <vector>
#include <string>

#include <iosfwd>
class TTree;
class TBranch;


class GenTree {

public:

  // Constructor to create a root tuple with name and title:
  GenTree( const char*, const char* );

  // Destructor:
  virtual ~GenTree();

  // Column booking/filling. All these have the same name - column(...)
  // Specify the data for a column. The string is to the key to
  // the column, so it must be unique. If an existing column with the given
  // label is not found, a new one is created. The third, optional, argument
  // is the value to use if this column is not otherwise filled in for a
  // given row of the tuple.


  // ====== Bool type ======
  // Make/fill column with a single value
  virtual void column( const char* label, 
		       bool value,
		       bool defval= false,
		       const char* block= 0 );
  // Make/fill column-array. Length is fixed at creation time.
  virtual void column( const char* label, 
		       const vector<bool>& v, 
		       bool defval= false,
		       const char* block= 0 );
  // Make/fill column-array. Length is variable and is taken from 
  // another column.
  virtual void column( const char* label, 
		       const vector<bool>& v, 
		       const char* ilab,
		       bool defval= false,
		       const char* block= 0 );


  // ====== Int type ======
  // Make/fill column with a single value
  virtual void column( const char* label, 
		       int value, 
		       int defval= 0,
		       const char* block= 0);
  // Make/fill column-array. Length is fixed at creation time.
  virtual void column( const char* label, 
		       const vector<int>& v, 
		       int defval= 0,
		       const char* block= 0);
  // Make/fill column-array. Length is variable and is taken from 
  // another column.
  virtual void column( const char* label, 
		       const vector<int>& v, 
		       const char* ilab,
		       int defval= 0,
		       const char* block= 0);


  // ====== Float type ======
  // Make/fill column with a single value
  virtual void column( const char* label, 
		       float value,
		       float defval= 0.0f,
		       const char* block= 0);
  // Make/fill column-array. Length is fixed at creation time.
  virtual void column( const char* label, 
		       const vector<float>& v, 
		       float defval= 0.0f,
		       const char* block= 0);
  // Make/fill column-array. Length is variable and is taken from 
  // another column.
  virtual void column( const char* label, 
		       const vector<float>& v, 
		       const char* ilab,
		       float defval= 0.0f,
		       const char* block= 0);


  // ====== Double type ======
  // Make/fill column with a single value
  virtual void column( const char* label, 
		       double value,
		       double defval= 0.0,
		       const char* block= 0);
  // Make/fill column-array. Length is fixed at creation time.
  virtual void column(const char *label, 
		      const vector<double>& v, 
		      double defval= 0.0,
		      const char* block= 0);
  // Make/fill column-array. Length is variable and is taken from 
  // another column.
  virtual void column( const char* label, 
		       const vector<double>& v, 
		       const char* ilab,
		       double defval= 0.0,
		       const char* block= 0);


  // ====== String type ======
  // Make/fill column with a single value
  virtual void column( const char* label, 
		       string value,
		       string defval= string(""),
		       const char* block= 0);


  // Dump all the data into the ntuple and then clear:
  virtual int dumpData();
     
  // Set all the data to their default values:
  virtual void clearData();
     
  // Return the title of the ntuple:
  virtual std::string title() const;

  // Number of columns:
  virtual int nColumns() const;

  // Label for a particular column
  virtual std::string label( int ) const;

  // Print info about ntuple:
  virtual void print( std::ostream & ) const;

  // Reset the ntuple:
  virtual void reset();

  // Get the base tree
  virtual TTree* getTree() { return treep; }

private:

  // Nested class to map columns to labels:
  class LPmap {
  private:
    vector<GenTreeColumn*> map;
  public:
    LPmap(){}
    ~LPmap(){ map.clear(); }
    void append( GenTreeColumn* colp ) { map.push_back( colp ); }
    GenTreeColumn* getColumn( const char* ) const;
    const vector<GenTreeColumn*> & getMap() const { return map; }
  };

  // Data members of GenTree:
  LPmap lpmap;
  TTree* treep;

};



#endif // GenTree_h
