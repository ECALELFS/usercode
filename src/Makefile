CC = g++
CFLAGS = -Wall -c -g

ROOFIT_INCLUDE := $(shell cd $(CMSSW_BASE); scram tool info roofitcore | grep INCLUDE= | sed 's|INCLUDE=||')
ROOFIT_LIBDIR := $(shell cd $(CMSSW_BASE); scram tool info roofitcore | grep LIBDIR= | sed 's|LIBDIR=||')

INCLUDES = -I. -I$(ROOTSYS)/include  -I$(ROOFIT_INCLUDE)/

ROOTSYS  ?= ERROR_RootSysIsNotDefined
ROOTFLAG = `${ROOTSYS}/bin/root-config --cflags --libs`
EXTRALIBS  :=  -L$(ROOTSYS)/lib -L$(ROOFIT_LIBDIR)/ -lHtml -lMathCore -lGenVector -lMinuit -lEG -lRooFitCore -lRooFit


higgsAnalysis: higgsAna.o higgsAnalysis.cpp
	$(CC) -Wall -o higgsAnalysis higgsAnalysis.cpp higgsAna.o $(ROOTFLAG)

drawPlot_MC: DrawBase.o fitTools.o drawPlot_MC.cpp
	$(CC) -Wall -I$(CMSSW_BASE)/src/UserCode/lpernie/ -o drawPlot_MC drawPlot_MC.cpp DrawBase.o fitTools.o $(ROOTFLAG) $(EXTRALIBS)

higgsAna.o: higgsAna.c
	$(CC) $(CFLAGS) higgsAna.c $(ROOTFLAG)

DrawBase.o: $(CMSSW_BASE)/src/UserCode/lpernie/CommonTools/DrawBase.C fitTools.o
	$(CC) $(CFLAGS) $(INCLUDES) fitTools.o $(CMSSW_BASE)/src/UserCode/lpernie/CommonTools/DrawBase.C $(ROOTFLAG) $(EXTRALIBS)

fitTools.o: $(CMSSW_BASE)/src/UserCode/lpernie/CommonTools/fitTools.C
	$(CC) $(CFLAGS) $(INCLUDES) $(CMSSW_BASE)/src/UserCode/lpernie/CommonTools/fitTools.C $(ROOTFLAG) $(EXTRALIBS)

clean:
	rm *.o
