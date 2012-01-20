
MAKE=make -f ../ProjectMakefile -C

.PHONY: all clean cpps

all: cpps

clean: cpps-clean

configure: cpps-configure

cpps:
	$(MAKE) cpps

cpps-clean:
	$(MAKE) cpps clean

cpps-configure:
	$(MAKE) cpps -k configure
