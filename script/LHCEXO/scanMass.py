#!/usr/bin/python
import os
import sys
from ROOT import *
from optparse import OptionParser

##########################################################################################################
# AUTHOR: Maurizio Pierini (CERN)                                                                        #
# DESCRIPTION:                                                                                           #
# Script to scan the mass value of a resonance production model                                          #
##########################################################################################################

class Marker(object):
    pass

def defineParser():
    parser = OptionParser()
    parser.add_option('--massPoints',dest="nMass",type="int", default=1, help="Number of intermediate mass points")
    parser.add_option('--massMin',dest="massMin",type="float", default=1000., help="Min mass value to scan")
    parser.add_option('--massMax',dest="massMax",type="float", default=5000., help="Max mass value to scan")
    parser.add_option('-e','--energy',dest="energy",type="float", default=8000., help="Center-of-Mass energy")
    parser.add_option('-n','--nevents',dest="nevents",type="int", default=10000., help="Number of events to generate")
    parser.add_option('-o','--outdir',dest="outdir",type='string', default="OUTPUT", help="Path to the output directory")
    parser.add_option('-p','--pythiacard',dest="pythiacard",type='string', default=None, help="Path to pythia card")    
    return parser

if __name__ == '__main__':

    parser = defineParser()
    (options,args) = parser.parse_args()    

    if options.pythiacard: 
        print 'Scan the resonance mass range [%f,%f] with %i steps using the pythia card %s' %(options.massMin,options.massMax,options.nMass,options.pythiacard)
        predir = ""
        pwd = os.environ['PWD']
        if options.outdir[0] != "/": predir = pwd+"/"
        OUTDIR = predir+options.outdir
        PYTHIACARD = predir+options.pythiacard

        gROOT.Reset()
        os.system("mkdir %s" %(OUTDIR))
        for iMass in range(0,int(options.nMass)) :
            mX = options.massMin + float(iMass)/(options.nMass-1)*(options.massMax-options.massMin)
            # create template cars
            outCard = open('%s/MASS_%f.pythia' %(OUTDIR,mX),'w')
            templateCard = open(PYTHIACARD)
            for line in templateCard:
                if line.find("Main:numberOfEvents") != -1: outCard.write("Main:numberOfEvents = %i\n" %options.nevents)
                elif line.find("Beams:eCM = ") != -1: outCard.write("Beams:eCM = %f\n" %options.energy)
                elif line.find("m0") != -1: outCard.write("%s = %f\n" %(line.split("=")[0], mX))
                else: outCard.write(line)
            outCard.close()
            templateCard.close()
            os.chdir("%s/BSMGen" %os.environ['PWD'])
            os.system("source setup.sh; ./GenPythia %s/MASS_%f.pythia %s/MASS_%f_Gen.root" %(OUTDIR,mX,OUTDIR,mX))
            os.chdir(pwd)
    else:
        parser.print_help()
