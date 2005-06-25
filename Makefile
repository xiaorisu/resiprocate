
BUILD 	=	build
-include $(BUILD)/Makefile.conf

ifeq ($(USE_DTLS),true)
BUILD_DTLS = dtls
endif

all: repro dum tests 

rutil: contrib
	cd rutil; $(MAKE)

resiprocate: contrib rutil
	cd resiprocate; $(MAKE)

dum: resiprocate
	cd dum; $(MAKE)

repro: dum
	cd repro; $(MAKE)

tests: resiprocate
	cd resiprocate/test; $(MAKE)

presSvr: resiprocate
	cd presSvr; $(MAKE)

contrib/ares/Makefile:
	cd contrib/ares && ./configure

configure_ares: contrib/ares/Makefile

ares: configure_ares
	cd contrib/ares && $(MAKE)

contrib/dtls/Makefile:
	cd contrib/dtls && ./config

configure_dtls: contrib/dtls/Makefile

dtls: configure_dtls
	cd contrib/dtls && $(MAKE)

contrib: ares $(BUILD_DTLS)

clean: 
	cd resiprocate; $(MAKE) clean
	cd resiprocate/test; $(MAKE) clean
	cd presSvr; $(MAKE) clean

.PHONY : resiprocate tests contrib ares dtls

