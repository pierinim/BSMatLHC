#! /usr/bin/env python
import os
import sys
# IMPORTANT: SET ROOTSYS FIRST!!!!
# FOR MACOSX gfortran is needed to compile softsusy

# CURRENT DIRECTORY
BSMDIR =  os.environ['PWD']

# 64bit?
m64 = True
for i in range(len(sys.argv)):
    if sys.argv[i].find("--m32") != -1: m64 = False
    continue

## external code: softsusy-3.4.0
#os.system("cp extraCode/softsusy-3.4.0.tar.gz . ; tar -xzf softsusy-3.4.0.tar.gz; rm softsusy-3.4.0.tar.gz")
#os.system("mv softsusy-3.4.0 softsusy")
#os.chdir("softsusy")
#options = "CXXFLAGS=-m32"
#if m64: options = "CXXFLAGS=-m64"
#os.system("./configure %s; make" %options)
#os.chdir(BSMDIR)

# get external code: HepMC 2.06.08
os.system("mkdir hepmc")
os.chdir("hepmc")
os.system("cp ../extraCode/HepMC-2.06.08.tar.gz .; tar -xzf HepMC-2.06.08.tar.gz; rm HepMC-2.06.08.tar.gz")
os.system("mkdir build")
sourcedir = os.environ['PWD']+"/hepmc/HepMC-2.06.08"
builddir = os.environ['PWD']+"/hepmc/build"
os.system("cmake -m64 -DCMAKE_INSTALL_PREFIX=%s %s -Dmomentum:STRING=GEV -Dlength:STRING=MM" %(builddir, sourcedir))
os.system("make; make install")
os.chdir(BSMDIR)

#get external code: PYTHIA 8.180
os.system("cp extraCode/pythia8180.tgz .; tar -xzf pythia8180.tgz; rm pythia8180.tgz")
os.system("mv pythia8180 pythia; cd pythia;  ./configure --enable-64bits --with-hepmc="+BSMDIR+"/hepmc/build --with-hepmcversion=2.06.08; make")

#Compile BSMGen
os.system("cd BSMGen; source ../pythia/examples/config.sh; make")

# fastjet
os.chdir("BSMApp")
os.system("cp ../extraCode/fastjet-3.0.6.tar.gz .")
os.system("tar -xzf fastjet-3.0.6.tar.gz; mkdir fastjet; cd fastjet-3.0.6; ./configure CXXFLAGS=-m64 --prefix=%s/BSMApp/fastjet/; make; make check; make install" %BSMDIR)
os.system("rm -r fastjet-3.0.6.tar.gz fastjet-3.0.6")

#Compile BSMApp
os.system("make")
