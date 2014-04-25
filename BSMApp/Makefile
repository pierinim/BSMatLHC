ROOTCFLAGS    = $(shell $(ROOTSYS)/bin/root-config --cflags)
ROOTLIBS      = $(shell $(ROOTSYS)/bin/root-config --libs)
ROOTGLIBS     = $(shell $(ROOTSYS)/bin/root-config --glibs)

FASTJETFLAGS = $(shell fastjet/bin/fastjet-config --cxxflags)
FASTJETLIBS  = $(shell fastjet/bin/fastjet-config --libs --plugins)

CXX           = g++
CXXFLAGS      = -fPIC -Wno-deprecated -O -ansi -D_GNU_SOURCE -O2
CXXFLAGS      += $(ROOTCFLAGS)
LD            = g++ 
LDFLAGS       = -g
SOFLAGS       = -shared

ARCH         := $(shell root-config --arch)
PLATFORM     := $(shell root-config --platform)

CXXFLAGS      += $(ROOTCFLAGS)
LIBS           = $(ROOTLIBS) 

NGLIBS         = $(ROOTGLIBS) 
NGLIBS        += -lMinuit
GLIBS          = $(filter-out -lNew, $(NGLIBS))

INCLUDEDIR       = ./include
SRCDIR           = ./src/
CXX	         += -I$(INCLUDEDIR) -I.
OUTLIB	         = ./lib/

.SUFFIXES: .cc,.C, .hh
.PREFIXES: ./lib/

#lib CMSApp
all: CMSLikMaker lib CMSApp FCCApp

fcc: fcclib FCCApp

fccee: fcceelib FCCeeApp

CMSApp:$(SRCDIR)CMS/CMSApp.C \
	$(OUTLIB)StatTools.o \
	$(OUTLIB)DataAnalysis.o \
	$(OUTLIB)CountingExperiment.o \
	$(OUTLIB)CMSRazorLikelihood.o \
	$(OUTLIB)DetectorBase.o \
	$(OUTLIB)DetectorReco.o \
	$(OUTLIB)CMSHemisphere.o \
	$(OUTLIB)CMSDetectorResponse.o \
	$(OUTLIB)CMSReco.o \
	$(OUTLIB)CMSDarkMatter.o \
	$(OUTLIB)CMSRazor.o \
    	$(OUTLIB)CMSSUSYVars.o \
	$(OUTLIB)CMSSubstructure.o 
	$(CXX) $(CXXFLAGS) $(FASTJETFLAGS) -o CMSApp $(OUTLIB)/*.o $(GLIBS) $(FASTJETLIBS) $ $<

#	$(OUTLIB)CMSMonoJet.o 
#	$(OUTLIB)CMSSSDilepBtag.o 
#	$(OUTLIB)CMSDisplacedJet.o 

CMSLikMaker:$(SRCDIR)CMS/CMSLikMaker.C \
	$(OUTLIB)StatTools.o \
	$(OUTLIB)CountingExperiment.o \
	$(OUTLIB)CMSRazorLikelihood.o 
	$(CXX) $(CXXFLAGS) -o CMSLikMaker $(OUTLIB)CMSRazorLikelihood.o $(OUTLIB)CountingExperiment.o $(OUTLIB)StatTools.o $(GLIBS) $ $<

lib:	$(OUTLIB)StatTools.o \
	$(OUTLIB)DataAnalysis.o \
	$(OUTLIB)CountingExperiment.o \
	$(OUTLIB)CMSRazorLikelihood.o \
	$(OUTLIB)DetectorBase.o \
	$(OUTLIB)DetectorReco.o \
	$(OUTLIB)JetSubstructure.o \
	$(OUTLIB)CMSHemisphere.o \
	$(OUTLIB)CMSDetectorResponse.o \
	$(OUTLIB)CMSReco.o \
	$(OUTLIB)CMSHemisphere.o \
	$(OUTLIB)CMSDarkMatter.o \
	$(OUTLIB)CMSRazor.o \
    	$(OUTLIB)CMSSUSYVars.o \
	$(OUTLIB)CMSSubstructure.o 
#	$(OUTLIB)CMSMonoJet.o 
#	$(OUTLIB)CMSSSDilepBtag.o 
#	$(OUTLIB)CMSDisplacedJet.o 

# basic statistics tools 
$(OUTLIB)StatTools.o: $(SRCDIR)CommonTools/StatTools.cc
	$(CXX) $(CXXFLAGS) $(FASTJETFLAGS) -c -I$(INCLUDEDIR) -o $(OUTLIB)StatTools.o $<

$(OUTLIB)CountingExperiment.o: $(SRCDIR)CommonTools/CountingExperiment.cc $(OUTLIB)StatTools.o $<
	$(CXX) $(CXXFLAGS) -c -I$(INCLUDEDIR) -o $(OUTLIB)CountingExperiment.o $<

$(OUTLIB)CMSRazorLikelihood.o: $(SRCDIR)CMS/CMSRazorLikelihood.cc $(OUTLIB)CountingExperiment.o $(OUTLIB)StatTools.o $<
	$(CXX) $(CXXFLAGS) -c -I$(INCLUDEDIR) -o $(OUTLIB)CMSRazorLikelihood.o $<

# base class with ntuple structure
$(OUTLIB)DetectorBase.o: $(SRCDIR)CommonTools/DetectorBase.cc $<
	$(CXX) $(CXXFLAGS) $(FASTJETFLAGS) -c -I$(INCLUDEDIR) -o $(OUTLIB)DetectorBase.o $<

# main Detector functions
$(OUTLIB)DetectorReco.o: $(SRCDIR)CommonTools/DetectorReco.cc $(OUTLIB)DetectorBase.o  $<
	$(CXX) $(CXXFLAGS) $(FASTJETFLAGS) -c -I$(INCLUDEDIR) -o $(OUTLIB)DetectorReco.o $<

$(OUTLIB)CMSHemisphere.o: $(SRCDIR)CMS/CMSHemisphere.cc 
	$(CXX) $(CXXFLAGS) $(FASTJETFLAGS) -c -I$(INCLUDEDIR) -o $(OUTLIB)CMSHemisphere.o $<

$(OUTLIB)CMSDetectorResponse.o: $(SRCDIR)CMS/CMSDetectorResponse.cc $ 
	$(CXX) $(CXXFLAGS) $(FASTJETFLAGS) -c -I$(INCLUDEDIR) -o $(OUTLIB)CMSDetectorResponse.o $<

$(OUTLIB)CMSReco.o: $(SRCDIR)CMS/CMSReco.cc $(OUTLIB)CMSDetectorResponse.o $(OUTLIB)CMSHemisphere.o $(OUTLIB)DetectorReco.o $(OUTLIB)StatTools.o $<
	$(CXX) $(CXXFLAGS) $(FASTJETFLAGS) -c -I$(INCLUDEDIR) -o $(OUTLIB)CMSReco.o $<

# generic Data Analysis (Abs Class)
$(OUTLIB)DataAnalysis.o: $(SRCDIR)CommonTools/DataAnalysis.cc	
	$(CXX) $(CXXFLAGS) $(FASTJETFLAGS) -c -I$(INCLUDEDIR) -o $(OUTLIB)DataAnalysis.o $<	

# CMS Analyses
$(OUTLIB)CMSRazor.o: $(SRCDIR)CMS/CMSRazor.cc $(OUTLIB)CMSReco.o $(OUTLIB)CMSRazorLikelihood.o $<
	$(CXX) $(CXXFLAGS) $(FASTJETFLAGS) -c -I$(INCLUDEDIR) -o $(OUTLIB)CMSRazor.o $<

$(OUTLIB)CMSSUSYVars.o: $(SRCDIR)CMS/CMSSUSYVars.cc $(OUTLIB)CMSReco.o $(OUTLIB)CMSRazorLikelihood.o $<
	$(CXX) $(CXXFLAGS) $(FASTJETFLAGS) -c -I$(INCLUDEDIR) -o $(OUTLIB)CMSSUSYVars.o $<

$(OUTLIB)CMSDisplacedJet.o: $(SRCDIR)CMS/CMSDisplacedJet.cc $(OUTLIB)CMSReco.o $<
	$(CXX) $(CXXFLAGS) $(FASTJETFLAGS) -c -I$(INCLUDEDIR) -o $(OUTLIB)CMSDisplacedJet.o $<

$(OUTLIB)CMSMonoJet.o: $(SRCDIR)CMS/CMSMonoJet.cc $(OUTLIB)CMSReco.o $<
	$(CXX) $(CXXFLAGS) $(FASTJETFLAGS) -c -I$(INCLUDEDIR) -o $(OUTLIB)CMSMonoJet.o $<

$(OUTLIB)CMSDarkMatter.o: $(SRCDIR)CMS/CMSDarkMatter.cc $(OUTLIB)CMSReco.o $<
	$(CXX) $(CXXFLAGS) $(FASTJETFLAGS) -c -I$(INCLUDEDIR) -o $(OUTLIB)CMSDarkMatter.o $<

$(OUTLIB)CMSSubstructure.o: $(SRCDIR)CMS/CMSSubstructure.cc $(OUTLIB)CMSReco.o $<
	$(CXX) $(CXXFLAGS) $(FASTJETFLAGS) -c -I$(INCLUDEDIR) -o $(OUTLIB)CMSSubstructure.o $<

$(OUTLIB)CMSSSDilepBtag.o: $(SRCDIR)CMS/CMSSSDilepBtag.cc $(OUTLIB)CMSReco.o $<
	$(CXX) $(CXXFLAGS) $(FASTJETFLAGS) -c -I$(INCLUDEDIR) -o $(OUTLIB)CMSSSDilepBtag.o $<

#$(OUTLIB)CMSWprime.o: $(SRCDIR)CMSWprime.cc
#	$(CXX) $(CXXFLAGS) $(FASTJETFLAGS) -c -I$(INCLUDEDIR) -o $(OUTLIB)CMSWprime.o $<

#$(OUTLIB)CMSZprime.o: $(SRCDIR)CMSZprime.cc
#	$(CXX) $(CXXFLAGS) $(FASTJETFLAGS) -c -I$(INCLUDEDIR) -o $(OUTLIB)CMSZprime.o $<

fcclib:	$(OUTLIB)DetectorBase.o \
	$(OUTLIB)DetectorReco.o \
	$(OUTLIB)DetectorResponse.o \
	$(OUTLIB)JetSubstructure.o \
	$(OUTLIB)FCCReco.o \
	$(OUTLIB)FCCExoVV.o \
	$(OUTLIB)FCCExoJJ.o 

fcceelib: $(OUTLIB)DetectorBase.o \
	$(OUTLIB)DetectorReco.o \
	$(OUTLIB)DetectorResponse.o \
	$(OUTLIB)JetSubstructure.o \
	$(OUTLIB)FCCReco.o \
	$(OUTLIB)FCCExoVV.o \
	$(OUTLIB)FCCExoJJ.o 

################################
# FCC STUDIES
################################
$(OUTLIB)DetectorResponse.o: $(SRCDIR)CommonTools/DetectorResponse.cc $< 
	$(CXX) $(CXXFLAGS) $(FASTJETFLAGS) -c -I$(INCLUDEDIR) -o $(OUTLIB)DetectorResponse.o $<

$(OUTLIB)JetSubstructure.o: $(SRCDIR)CommonTools/JetSubstructure.cc $< 
	$(CXX) $(CXXFLAGS) $(FASTJETFLAGS) -c -I$(INCLUDEDIR) -o $(OUTLIB)JetSubstructure.o $<

$(OUTLIB)FCCReco.o: $(SRCDIR)FCC/FCCReco.cc $(OUTLIB)DetectorResponse.o $(OUTLIB)DetectorReco.o $<
	$(CXX) $(CXXFLAGS) $(FASTJETFLAGS) -c -I$(INCLUDEDIR) -o $(OUTLIB)FCCReco.o $<

$(OUTLIB)FCCExoVV.o: $(SRCDIR)FCC/FCCExoVV.cc $(OUTLIB)FCCReco.o $(OUTLIB)JetSubstructure.o $<
	$(CXX) $(CXXFLAGS) $(FASTJETFLAGS) -c -I$(INCLUDEDIR) -o $(OUTLIB)FCCExoVV.o $<

$(OUTLIB)FCCExoJJ.o: $(SRCDIR)FCC/FCCExoJJ.cc $(OUTLIB)FCCReco.o $(OUTLIB)JetSubstructure.o $<
	$(CXX) $(CXXFLAGS) $(FASTJETFLAGS) -c -I$(INCLUDEDIR) -o $(OUTLIB)FCCExoJJ.o $<

fccclean: 
	rm -f $(OUTLIB)*.o FCCApp

FCCApp:$(SRCDIR)FCC/FCCApp.C \
	$(OUTLIB)FCCExoVV.o \
	$(OUTLIB)FCCExoJJ.o 
	$(CXX) $(CXXFLAGS) $(FASTJETFLAGS) -o FCCApp $(OUTLIB)/*.o $(GLIBS) $(FASTJETLIBS) $ $<

################################
# FCCee STUDIES
################################
$(OUTLIB)FCCeeRazor3D.o: $(SRCDIR)FCCee/FCCeeRazor3D.cc $(OUTLIB)FCCReco.o $<
	$(CXX) $(CXXFLAGS) $(FASTJETFLAGS) -c -I$(INCLUDEDIR) -o $(OUTLIB)FCCeeRazor3D.o $<

fcceeclean: 
	rm -f $(OUTLIB)*.o FCCeeApp

FCCeeApp:$(SRCDIR)FCCee/FCCeeApp.C \
	$(OUTLIB)FCCeeRazor3D.o 
	$(CXX) $(CXXFLAGS) $(FASTJETFLAGS) -o FCCeeApp $(OUTLIB)/*.o $(GLIBS) $(FASTJETLIBS) $ $<

#################################

CMSApp.clean:
	rm -f CMSApp 

clean:
	rm -f $(OUTLIB)*.o 
	rm -f CMSApp CMSLikMaker FCCApp
