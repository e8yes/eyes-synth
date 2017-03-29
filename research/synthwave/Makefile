CXXFLAGS=-I`octave-config -p OCTINCLUDEDIR` -Ofast
LDFLAGS=-loctave -loctinterp -march=native -flto -Ofast
all:
	g++ -c $(CXXFLAGS) synthwave.cpp
	g++ synthwave.o  $(LDFLAGS) -o a.out
