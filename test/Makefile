# Makefile for test

all: \
 $(patsubst %.cpp,%.exe,$(wildcard *.cpp)) \
 $(patsubst SCCS/s.%.cpp,%.exe,$(wildcard SCCS/s.*.cpp))

random.exe: random.cpp
	g++ -Wall -o $@ $<

bigint_compare.exe: bigint_compare.cpp
	g++ -Wall -o $@ $<

Testplate.exe: Testplate.cpp
	echo NONE > $@

%.exe: %.cpp
	g++ -Wall -pedantic-errors -o $@ $<

clean: \
	rm *.exe




