#! /usr/bin/env python
##########################################################################################################
# AUTHOR: Maurizio Pierini (CERN)                                                                        #
# DESCRIPTION:                                                                                           #
# Script to run a set of CMS analyses on a Simplified Model                                              #
##########################################################################################################

import os, sys

def supportedModels():
    print ''
    print 'The following models are supported'
    print '- T1      gluino-gluino production -> 4j+2LSP'
    print '- T1bbbb  gluino-gluino production -> 4b+2LSP'
    print '- T1tttt  gluino-gluino production -> 4t+2LSP'
    print '- T2      squark-squark production -> 2j+2LSP'
    print '- T2bb    sbottom-sbottom production -> 2b+2LSP'
    print '- T2tt    stop-stop production -> 2t+2LSP'
    print '- T2cc    stop-stop production -> 2c+2LSP'
    print '- TChiwz  chi+/chi20 pairs -> W/Z + LSP '
    print 'In case you want to scan m(produced) vs mass split, specify: --compressed'
    print ''

def supportedAnalyses():
    print ''
    print 'The following analyses are supported'
    print '--razor   CMS Razor Inclusive Analysis SUS-12-005'
    print '--razB    CMS Razor b+jets Analysis SUS-11-024'
    print '--monojet CMS Monojet Analysis EXO-11-059'
    print '--ssdilepbtag  CMS SS dilepton btag Analysis SUS-11-020'
    print '--displaced XXX'
    print ''

def analyses(argv):
    analyses = ""
    for i in range(0,len(argv)):
        if argv[i] == "--compressed": analyses = "%s --compressed" %analyses
        if argv[i] == "--razor": analyses = "%s --razor" %analyses
        if argv[i] == "--razB": analyses = "%s --razB" %analyses
        if argv[i] == "--monojet": analyses = "%s --monojet" %analyses
        if argv[i] == "--displaced":  analyses = "%s --displaced" %analyses
    return analyses

def runSM(argv, ParticleName,useDecaySLHA, extraLines = []):
    # get input parameters
    pwd = os.environ['PWD']
    SMname = argv[1]
    mP = argv[2]
    mlsp = argv[3]
    energy = argv[4]
    nevents = argv[5]
    outdir = argv[6]
    if outdir[0] != "/": outdir = pwd+"/"+outdir

    # which analyses should we run
    analysisToRun = analyses(sys.argv)
    if analysisToRun.find("compressed") != -1: SMname = "C"+SMname

    # Set the directories of the different packages:
    susygendir = pwd+'/BSMGen/'
    susyappdir = pwd+'/BSMApp/'

    # check that the Neutralino is the LSP
    if float(mP)<float(mlsp):
        print "Error: the Neutralino is NOT the LSP of the model requested"
        print "Exiting"
        sys.exit(0)
    # create the SLHA from template
    template = open("BSMGen/data/pythiaCards/SUSY/SimplifiedModels/simplifiedModel.%s.slha" %SMname)
    # open the SLHA file
    slhaname = "%s/sm%s_%s_%s_%s.slha" %(outdir,SMname,mP,mlsp,energy)
    myfile = open(slhaname,"w")
    for line in template:
        myfile.write(line.replace("LSP",mlsp).replace("%s" %ParticleName,mP))
        continue
    myfile.close()
    template.close()
    #create the PYTHIA card
    pythiaCardName = outdir+"/sm"+SMname+"_"+mP+"_"+mlsp+"_"+energy+".pythia"
    pythiaCard = open(pythiaCardName, "w")
    pythiaTemplate = open("BSMGen/data/pythiaCards/SUSY/SLHAGen_LHC7TeV.pythia")
    for line in pythiaTemplate:
        if line.find("SLHA:file = ") != -1: pythiaCard.write("SLHA:file =%s\n" %slhaname)
        elif line.find("Beams:eCM =") != -1: pythiaCard.write("Beams:eCM = %s\n" %energy)
        elif line.find("Main:numberOfEvents =") != -1: pythiaCard.write("Main:numberOfEvents = %s\n" %nevents)
        elif line.find("SLHA:useDecayTable =") != -1: 
            if useDecaySLHA: pythiaCard.write("SLHA:useDecayTable = on\n")
            else: pythiaCard.write("SLHA:useDecayTable = off\n")
        elif line.find("SUSY:all") != -1: 
            if SMname.find("T1") != -1: pythiaCard.write("SUSY:gg2gluinogluino = on\n SUSY:qqbar2gluinogluino = on\n")
            elif SMname.find("T2") != -1: 
                pythiaCard.write("SUSY:gg2squarkantisquark = on\n")
                pythiaCard.write("SUSY:qqbar2squarkantisquark = on\n")
        else: pythiaCard.write(line)
    # ADD EXTRA LINES: 
    for line in extraLines: pythiaCard.write(line)
    pythiaCard.close()
    pythiaTemplate.close()
    #os.system("more "+pythiaCardName)

    # Run GenPythia  to generate events:
    command = "source setup.sh; ./GenPythia %s %s" %(pythiaCardName, pythiaCardName.replace(".pythia","_Gen.root"))
    print command
    os.chdir(susygendir)
    os.system(command)
    
    ## Run CMSApp 
    #os.chdir(susyappdir)
    #outfilename = "%s/sm%s_%s_%s_%s_cmsout" %(outdir,SMname,mP,mlsp,energy)
    ##command = "./CMSApp %s %s -Output=%s.root >> %s.log" %(pythiaCardName.replace(".pythia",".pythia_GenTree.root"),analysisToRun, outfilename,outfilename)
    #command = "./CMSApp %s %s -Output=%s.root" %(pythiaCardName.replace(".pythia",".pythia_GenTree.root"),analysisToRun, outfilename)
    #print command
    #os.system("touch %s.log" %outfilename)
    #os.system(command)
 
if __name__ == '__main__':
    # Look for arguments and exit if there are none:
    if len(sys.argv) < 7:
        print 'Run as:'
        print ' '+sys.argv[0]+' <model name> <mass produced particle> <LSP mass> <Energy> <Nevents> <output file dir>'
        supportedModels()
        supportedAnalyses()
        sys.exit(0)
    if sys.argv[1].find("TChiwz") != -1: runSM(sys.argv, "EWKINO", True)#, ["SUSY:qqbar2chi0chi0 = on\n", "SUSY:qqbar2chi+-chi0 = on\n", "SUSY:qqbar2chi+chi- = on\n"])
    elif sys.argv[1].find("T1") != -1: runSM(sys.argv, "GLUINO", True)
    elif sys.argv[1].find("T2") != -1: runSM(sys.argv, "SQUARK", True)



