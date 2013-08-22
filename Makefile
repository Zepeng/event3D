UNAME := $(shell uname)
CXX=g++
CC=gcc

OPTIONS = -fPIC -Wall 
ROOTCFLAGS   = $(shell root-config --cflags)
ROOTMAIN     = $(shell root-config --libs)
ROOTGMAIN     = $(shell root-config --glibs)
CERNLIB = `cernlib pawlib graflib packlib mathlib kernlib` -lg2c -lm
INC = includes/
# Root, glui, glut libraries are OS dependent
#ifeq ($(UNAME), Linux)
#ROOTLIBS = -L/usr/lib/root -lNew $(ROOTMAIN) $(ROOTGMAIN) -lMinuit -L/usr/lib/root/5.18
#endif
#ifeq ($(UNAME), Darwin)
ROOTLIBS = -L$(ROOTSYS)/lib $(ROOTMAIN) $(ROOTGMAIN) -lMinuit
INCLUDES = -I$(ROOTSYS)/include -I$(INC) 
#endif


LDLIBS +=  $(JHF2KMLIB) $(ROOTLIBS)
OBJS = main.o handleroot.o residualtime.o  oglHistogram.o RGBcolorSpectrum.o glutstuff.o pointmodification.o drawevent.o
ALL = $(OPTIONS) $(LDLIBS) $(GLLIBS) $(INCLUDES)
ifeq ($(shell uname),Darwin)
	GLLIBS = -framework OpenGL -framework GLUT -framework GLUI
else
	GLLIBS = libglui.a /usr/lib64/libglut.so.3.8.0 -lGLU
endif


SO = libWCMap.so

standard: main clean

main: $(OBJS)
	g++ $(OBJS) $(ALL) -o runme

%.o: $(INC)/%.cc
	g++ $(ALL) -c $(INC)/$*.cc

%.o: %.cpp
	g++ $(ALL) -c $*.cpp

clean:
	rm -f *.o
