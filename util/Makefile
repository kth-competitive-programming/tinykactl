CC = g++
CXX = g++

.PHONY: all clean lgrind

util: lgrind stripcode breakcode adler linecode

always: .

spotless: clean
	rm -f lgrind/source/lgrind lgrind/source/lgrind.exe
	rm -f stripcode stripcode.exe
	rm -f breakcode breakcode.exe
	rm -f adler adler.exe
	rm -f linecode linecode.exe

lgrind: always
	make lgrind -C lgrind

LGSTRIP=header
SUMSTRIP=header comments
include $(BASEDIR)/Makefile.inc
