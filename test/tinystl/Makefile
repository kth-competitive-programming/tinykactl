# Makefile for tinystl-test

all: \
 $(patsubst %.cpp,%.exe,$(wildcard *.cpp)) \
 $(patsubst SCCS/s.%.cpp,%.exe,$(wildcard SCCS/s.*.cpp))

%.exe: %.cpp
	g++2 -Wall -o $@ $<

clean: ;
	rm *.exe




