# Makefile for tinystl-test

all: \
 $(patsubst %.cpp,%.exe,$(wildcard *.cpp)) \
 $(patsubst SCCS/s.%.cpp,%.exe,$(wildcard SCCS/s.*.cpp))

%.exe: %.cpp
	g++2 -ansi -pedantic -lm -Wall -o $@ $<

clean: ;
	rm -f *.exe




