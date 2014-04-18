#!/bin/csh
if( ! $?LD_LIBRARY_PATH ) then
  setenv LD_LIBRARY_PATH $PWD/hepmc/install/lib
else
  setenv LD_LIBRARY_PATH ${LD_LIBRARY_PATH}:$PWD/hepmc/install/lib
endif
