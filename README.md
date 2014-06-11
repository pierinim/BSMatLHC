BSMatLHC
========

Tools for Beyond Standard Model event generation and analysis at LHC and other colliders!


TO COMPILE THE CODE
---------------------

0) you need cmake and ROOT   
   > http://www.cmake.org/cmake/resources/software.html
   > http://root.cern.ch/drupal/content/downloading-root
   
1) set the ROOTSYS environment variable in your shell 

2) from the BSMatLHC directory run the script

   > python script/ToBuild/compile.py

   This is a python script, so you need python.
   Moreover, the script will try to download
   external software (eg PYTHIA) so a Network
   connection is required

The compilation workflow was succesfully tested under Linux SL5


BEFORE RUNNING BSMGEN
-----------------------

Before running BSMGen, you need to source a configuration
script from pythia, to load the hepMc shared library.
The script to source depends on the shell you use
> cd BSMGen
> source pythia/examples/config.(c)sh


TO RUN THE FULL CHAIN FROM A SLHA FILE
---------------------------------------

> python python/runSLHA.py <SLHA name> <number of events> <CM Energy> <output file dir>

**You will need to create a directory named <output file dir>

TO RUN THE FULL CHAIN FROM A LHE FILE
---------------------------------------

> python python/runLHE.py <LHE name> <output file dir>


TO CLEANUP the installation 
--------------------------- 
you can run the cleanup script

   > python script/ToBuild/cleanup.py 

IMPORTANT: this will require to rerun from scratch the compilation
script. If you just need to recompile (one of) the code(s) then just
do

   > make clean

in the appropriate directory