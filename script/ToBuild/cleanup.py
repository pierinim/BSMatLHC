#!/bin/env python
import os, sys
# remove auxiliary code
os.system("rm -rf pythia hepmc softsusy BSMApp/fastjet/")
# clean BSMGen and BSMApp build
os.chdir("BSMGen")
os.system("make clean")
os.chdir("../BSMApp")
os.system("make clean")
