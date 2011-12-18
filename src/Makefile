CC = g++
CFLAGS = -Wall -c -g

ROOFIT_INCLUDE := $(shell cd $(CMSSW_BASE); scram tool info roofitcore | grep INCLUDE= | sed 's|INCLUDE=||')
ROOFIT_LIBDIR := $(shell cd $(CMSSW_BASE); scram tool info roofitcore | grep LIBDIR= | sed 's|LIBDIR=||')

INCLUDES = -I. -I$(ROOTSYS)/include  -I$(ROOFIT_INCLUDE)/

ROOTSYS  ?= ERROR_RootSysIsNotDefined
ROOTFLAG = `${ROOTSYS}/bin/root-config --cflags --libs`
EXTRALIBS  :=  -L$(ROOTSYS)/lib -L$(ROOFIT_LIBDIR)/ -lHtml -lMathCore -lGenVector -lMinuit -lEG -lRooFitCore -lRooFit


ZZ_Finalizer: ZZ_Finalize.o Analysis_Electron.o Analysis_Muon.o ZZ_Finalizer.cpp
	$(CC) -Wall -o ZZ_Finalizer ZZ_Finalizer.cpp ZZ_Finalize.o Analysis_Electron.o Analysis_Muon.o $(ROOTFLAG)

drawPlot_MC: DrawBase.o fitTools.o drawPlot_MC.cpp
	$(CC) -Wall -I$(CMSSW_BASE)/src/UserCode/lpernie/ -o drawPlot_MC drawPlot_MC.cpp DrawBase.o fitTools.o $(ROOTFLAG) $(EXTRALIBS)

ZZ_Finalize.o: ZZ_Finalize.C
	$(CC) $(CFLAGS) ZZ_Finalize.C $(ROOTFLAG)

DrawBase.o: $(CMSSW_BASE)/src/UserCode/lpernie/CommonTools/DrawBase.C fitTools.o
	$(CC) $(CFLAGS) $(INCLUDES) fitTools.o $(CMSSW_BASE)/src/UserCode/lpernie/CommonTools/DrawBase.C $(ROOTFLAG) $(EXTRALIBS)

fitTools.o: $(CMSSW_BASE)/src/UserCode/lpernie/CommonTools/fitTools.C
	$(CC) $(CFLAGS) $(INCLUDES) $(CMSSW_BASE)/src/UserCode/lpernie/CommonTools/fitTools.C $(ROOTFLAG) $(EXTRALIBS)

Analysis_Electron.o: Analysis_Electron.cc Analysis_Lepton.o
	$(CC) $(CFLAGS) Analysis_Electron.cc $(ROOTFLAG)

Analysis_Muon.o: Analysis_Muon.cc Analysis_Lepton.o
	$(CC) $(CFLAGS) Analysis_Muon.cc $(ROOTFLAG)

Analysis_Lepton.o: Analysis_Lepton.h
	$(CC) $(CFLAGS) Analysis_Lepton.h $(ROOTFLAG)

clean:
	rm *.o
