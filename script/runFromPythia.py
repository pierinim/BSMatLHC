#!/usr/bin/env python
##########################################################################################################
# AUTHOR: Maurizio Pierini (CERN)                                                                        #
# DESCRIPTION:                                                                                           #
# Script to generate PYTHIA events and process them through BSMApp                                       #
##########################################################################################################

import os, sys

if __name__ == '__main__':
    # Look for arguments and exit if there are none:
    if (len(sys.argv) < 6):
        print 'Run as:'
        print ' '+sys.argv[0]+' <pythia card> <number of events> <CM Energy> <RECO APP> <output file dir>'
        sys.exit(0)

    # Get the slha name and number of events from the arguments:
    pwd = os.environ['PWD']
    slhaname = sys.argv[1]
    myslha = slhaname.split("/")[-1]
    nevents = sys.argv[2]
    CMEnergy = sys.argv[3]
    outdir = sys.argv[4]
    if outdir[0] != "/": outdir = pwd+"/"+outdir

    # Set the directories of the different packages:
    susygendir = pwd+'/BSMGen/'
    susyappdir = pwd+'/BSMApp/'

    #Copy the SLHA file in BSMGen/data
    os.system("cp %s %s" %(slhaname,outdir))
    slhaname = outdir+"/"+slhaname.split("/")[-1]

    #create the PYTHIA8 card from templa
    pythiaCardName =  outdir+"/"+myslha+"_"+CMEnergy+".pythia"
    pythiaCard = open(pythiaCardName, "w")
    pythiaTemplate = open("BSMGen/data/pythiaCards/SLHAGen_LHC7TeV.pythia")
    for line in pythiaTemplate:
        if line.find("SLHA:file = ") != -1: pythiaCard.write("SLHA:file =%s\n" %slhaname)
        elif line.find("Beams:eCM =") != -1: pythiaCard.write("Beams:eCM = %s\n" %CMEnergy)
        elif line.find("Main:numberOfEvents =") != -1: pythiaCard.write("Main:numberOfEvents = %s\n" %nevents)
        elif line.find("SLHA:useDecayTable =") != -1: pythiaCard.write("SLHA:useDecayTable = on\n")
        else: pythiaCard.write(line)
    pythiaCard.close()
    pythiaTemplate.close()

    # Run SLHAGen to generate events:
    print pythiaCardName
    command = "source setup.sh; ./SLHAGen %s %s >& %s " %(pythiaCardName, pythiaCardName.replace(".pythia",""), pythiaCardName.replace(".pythia","_pythia.log"))
    print command
    os.chdir(susygendir)
    os.system("source ../script/setupHepmc.sh;"+command)

    # Run CMSApp to do apply the CMS analyses to the generated sample
    os.chdir(susyappdir)
    outfilename = "%s" %(pythiaCardName.replace(".pythia","_cmsout"))
    #command = "./CMSApp %s --monojet --razor -Output=%s.root >> %s.log" %(pythiaCardName.replace(".pythia","_GenTree.root"),outfilename,outfilename)
    command = "./CMSApp %s  --razor -Output=%s.root >> %s.log" %(pythiaCardName.replace(".pythia","_GenTree.root"),outfilename,outfilename)
    print command
    os.system("touch %s.log" %outfilename)
    os.system(command)
 
