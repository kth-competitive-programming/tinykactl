UTIL = $(BASEDIR)/util

RECURSE = \
	@export BASEDIR;\
	for DIR in [ `ls` ];\
	do\
		if [ -d $$DIR/SCCS -a -f $$DIR/SCCS/s.Makefile -a\
		     ! -f $$DIR/Makefile ];\
		then bk co $$DIR/Makefile;\
		fi;\
		if [ -d $$DIR -a -f $$DIR/Makefile ];\
		then $(MAKE) $@ -C $$DIR BASEDIR=$(BASEDIR) FLAGS=$(FLAGS);\
		fi\
	done


clean: codeclean
	rm -f $(INTERMED)
	$(RECURSE)


code: koder texer includes
	$(RECURSE)

allcodeclean: codeclean
	$(RECURSE)

codeclean:
	rm -f *.lg *.sum *.incl


koder: \
 $(patsubst %.cpp,%.lg,$(wildcard *.cpp)) \
 $(patsubst SCCS/s.%.cpp,%.lg,$(wildcard SCCS/s.*.cpp))

summor: \
 $(patsubst %.cpp,%.sum,$(wildcard *.cpp)) \
 $(patsubst SCCS/s.%.cpp,%.sum,$(wildcard SCCS/s.*.cpp))

includes: $(UTIL)/inc_files.sed $(UTIL)/stripcode \
 $(patsubst %.cpp,%.incl,$(wildcard *.cpp)) \
 $(patsubst SCCS/s.%.cpp,%.incl,$(wildcard SCCS/s.*.cpp))

texer: \
 $(wildcard *.tex) \
 $(patsubst SCCS/s.%.tex,%.tex,$(wildcard SCCS/s.*.tex))



%.lg: %.cpp $(UTIL)/lgrind/lgrindef
	$(UTIL)/stripcode $(LGSTRIP) < $< | \
	$(UTIL)/lgrind/source/lgrind -i -l c++ -d $(UTIL)/lgrind/lgrindef - > $@

%.sum: %.cpp
	$(UTIL)/stripcode $(SUMSTRIP) < $< | $(UTIL)/adler | \
		awk -- '{printf "\\checksum{%s}",$$1};' > $@
	$(UTIL)/stripcode $(SUMSTRIP) < $< | $(UTIL)/linecode | \
		awk -F, -- '{printf "{%s}{{}",$$1; \
		{for(i=2;i<10;i++) printf "%2s,",$$i;} printf "}{{}"; \
		{for(i=10;i<17;i++) printf "%2s,",$$i;} \
		printf "%2s}\n", $$17;};' >> $@
%.incl: %.cpp 
	echo "\\includelist{" > $@
	$(UTIL)/stripcode $(SUMSTRIP) < $< | wc -l >> $@
	echo "}{" >> $@
	sed -f $(UTIL)/inc_files.sed < $< | sed '$$!s/$$/,/' >> $@
	echo "}" >> $@
