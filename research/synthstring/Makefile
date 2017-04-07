CXXFLAGS=-I`octave-config -p OCTINCLUDEDIR` -Ofast
LDFLAGS=-loctave -loctinterp -march=native -flto -Ofast
all:
	g++ -c $(CXXFLAGS) synthstring.cpp
	g++ synthstring.o  $(LDFLAGS) -o a.out
