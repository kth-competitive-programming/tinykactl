# Makefile for test

.PHONY: all kylix_all gcc_all

all: kylix_all gcc_all

kexe=$(patsubst %.cpp,%.kexe,$(wildcard *.cpp)) \
	$(patsubst SCCS/s.%.cpp,%.kexe,$(wildcard SCCS/s.*.cpp))

exe=$(patsubst %.cpp,%.exe,$(wildcard *.cpp)) \
	$(patsubst SCCS/s.%.cpp,%.exe,$(wildcard SCCS/s.*.cpp))

kylix_all: $(kexe)

kylix_test: $(patsubst data/%.in,data/%.kout,$(wildcard data/*.in))

gcc_all: $(exe)

gcc_test: $(patsubst data/%.in,data/%.out,$(wildcard data/*.in))


kylix_diff:
	for x in $(patsubst data/%.ans,%,$(wildcard data/*.ans)); \
		do echo $$x:; diff data/$$x.kout data/$$x.ans; done

gcc_diff:
	for x in $(patsubst data/%.ans,%,$(wildcard data/*.ans)); \
		do echo $$x:; diff data/$$x.out data/$$x.ans; done

random.exe: random.cpp
	g++ -Wall -o $@ $<

bigint_compare.exe: bigint_compare.cpp
	g++ -Wall -o $@ $<

Testplate.exe: Testplate.cpp
	echo NONE > $@

Testplate.kexe: Testplate.cpp
	echo NONE > $@

%.exe: %.cpp
	g++ -Wall -pedantic-errors -o $@ $<

%.kexe: %.cpp
	bc++ -q -lq -O2 -w-par- -w-pia- -w-ovf- -e$@ $<; rm $(patsubst %.cpp,%.o,$<)

clean:
	rm -f *.kexe *.exe *.o

data/%.out: %.exe data/%.in
	./$< <$(patsubst %.exe,data/%.in,$<) >$@

data/%.kout: %.kexe data/%.in
	./$< <$(patsubst %.kexe,data/%.in,$<) >$@
