#CXXFLAGS=-I`octave-config -p OCTINCLUDEDIR` -Ofast
CXXFLAGS=-I`octave-config -p OCTINCLUDEDIR` -g
#LDFLAGS=-loctave -loctinterp -march=native -flto -Ofast
LDFLAGS=-loctave -loctinterp 
all:
	g++ -c $(CXXFLAGS) synthhammer.cpp
	g++ synthhammer.o  $(LDFLAGS) -o a.out
