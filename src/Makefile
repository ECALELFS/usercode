CC = g++
CFLAGS = -Wall -c -g

ROOFIT_INCLUDE := $(shell cd $(CMSSW_BASE); scram tool info roofitcore | grep INCLUDE= | sed 's|INCLUDE=||')
ROOFIT_LIBDIR := $(shell cd $(CMSSW_BASE); scram tool info roofitcore | grep LIBDIR= | sed 's|LIBDIR=||')

INCLUDES = -I. -I$(ROOTSYS)/include  -I$(ROOFIT_INCLUDE)/

ROOTSYS  ?= ERROR_RootSysIsNotDefined

ROOTFLAG = `${ROOTSYS}/bin/root-config --cflags --libs`

EXTRALIBS  :=  -L$(ROOTSYS)/lib -L$(ROOFIT_LIBDIR)/ -lHtml -lMathCore -lGenVector -lMinuit -lEG -lRooFitCore -lRooFit

ZZ_Finalizer: ZZ_Finalize.o Analysis_Electron.o Analysis_Muon.o ZZ_Finalizer.cpp
	$(CC) -Wall -o ZZ_Finalizer ZZ_Finalizer.cpp ZZ_Finalize.o Analysis_Electron.o Analysis_Muon.o $(ROOTFLAG) $(EXTRALIBS)

drawHWWlvjj: DrawBase.o fitTools.o drawHWWlvjj.cpp
	$(CC) -Wall -I$(CMSSW_BASE)/src/UserCode/lpernie/src/ -o drawHWWlvjj drawHWWlvjj.cpp DrawBase.o fitTools.o $(ROOTFLAG) $(EXTRALIBS)

drawHWWlvjj_DATA: DrawBase.o fitTools.o drawHWWlvjj_DATA.cpp
	$(CC) -Wall -I$(CMSSW_BASE)/src/UserCode/lpernie/src/ -o drawHWWlvjj_DATA drawHWWlvjj_DATA.cpp DrawBase.o fitTools.o $(ROOTFLAG) $(EXTRALIBS)

DrawLP: DrawLPBase.o DrawLP.cpp
	$(CC) -Wall -I$(CMSSW_BASE)/src/UserCode/lpernie/src/ -o DrawLP DrawLP.cpp DrawLPBase.o $(ROOTFLAG) $(EXTRALIBS)

EffMet: DrawLPBase.o EffMet.cpp
	$(CC) -Wall -I$(CMSSW_BASE)/src/UserCode/lpernie/src/ -o EffMet EffMet.cpp DrawLPBase.o $(ROOTFLAG) $(EXTRALIBS)

ZZ_Finalize.o: ZZ_Finalize.C
	$(CC) $(CFLAGS) ZZ_Finalize.C $(ROOTFLAG) $(EXTRALIBS)

DrawBase.o: $(CMSSW_BASE)/src/UserCode/lpernie/src/CommonTools/DrawBase.C fitTools.o
	$(CC) $(CFLAGS) $(INCLUDES) fitTools.o $(CMSSW_BASE)/src/UserCode/lpernie/src/CommonTools/DrawBase.C $(ROOTFLAG) $(EXTRALIBS)

fitTools.o: $(CMSSW_BASE)/src/UserCode/lpernie/src/CommonTools/fitTools.C
	$(CC) $(CFLAGS) $(INCLUDES) $(CMSSW_BASE)/src/UserCode/lpernie/src/CommonTools/fitTools.C $(ROOTFLAG) $(EXTRALIBS)

DrawLPBase.o: $(CMSSW_BASE)/src/UserCode/lpernie/src/CommonTools/DrawLPBase.C
	$(CC) $(CFLAGS) $(INCLUDES) $(CMSSW_BASE)/src/UserCode/lpernie/src/CommonTools/DrawLPBase.C $(ROOTFLAG) $(EXTRALIBS)

Analysis_Electron.o: Analysis_Electron.cc Analysis_Lepton.o
	$(CC) $(CFLAGS) Analysis_Electron.cc $(ROOTFLAG)

Analysis_Muon.o: Analysis_Muon.cc Analysis_Lepton.o
	$(CC) $(CFLAGS) Analysis_Muon.cc $(ROOTFLAG)

Analysis_Lepton.o: Analysis_Lepton.h
	$(CC) $(CFLAGS) Analysis_Lepton.h $(ROOTFLAG)

clean:
	rm *.o
