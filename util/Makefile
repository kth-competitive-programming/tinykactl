.PHONY: all clean lgrind

util: lgrind stripcode adler linecode

always: .

clean:
	cd lgrind; make clean

spotless: clean
	rm -f lgrind/source/lgrind lgrind/source/lgrind.exe
	rm -f stripcode stripcode.exe
	rm -f adler adler.exe
	rm -f linecode linecode.exe

lgrind: always
	cd lgrind && $(MAKE) lgrind

stripcode: stripcode.cpp
	g++ -o stripcode stripcode.cpp

adler: adler.cpp
	g++ -o adler adler.cpp

linecode: linecode.cpp linecodesafe.cpp
	g++ -o linecode linecodesafe.cpp

LGSTRIP=header
SUMSTRIP=header comments
UTIL=.
include $(UTIL)/makecode
