.PHONY: all clean lgrind

all: lgrind stripcode adler

clean:
	cd lgrind; make clean

spotless: clean
	rm -f lgrind/source/lgrind lgrind/source/lgrind.exe
	rm -f stripcode stripcode.exe
	rm -f adler adler.exe

lgrind: .
	cd lgrind; make lgrind

stripcode: stripcode.cpp
	g++ -o stripcode stripcode.cpp

adler: adler.cpp
	g++ -o adler adler.cpp
