#!/bin/sh
if [ ! $?LD_LIBRARY_PATH ]; then
  export LD_LIBRARY_PATH=$PWD/hepmc/install/lib
fi
if [ $?LD_LIBRARY_PATH ]; then
  export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:$PWD/hepmc/install/lib
fi
