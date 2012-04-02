# Makefile
# Main Makefile for cube2crypto.
# Copyright (c) 2012 Morgan Borman
# E-mail: morgan.borman@gmail.com
#
# This software is licensed under the terms of the Zlib license.
# http://en.wikipedia.org/wiki/Zlib_License
#

BUILDC = build/c
BUILDU = build/util
BUILDP = build/py
BUILDJ = build/js
BUILDS = build/shared

UTILDEPS = ${BUILDC}/cube2crypto.o ${BUILDC}/cube2crypto.h

all: cube2crypto_c cube2crypto_py ${BUILDS}/cube2crypto.so utils #cube2crypto_js

utils: ${BUILDU}/hashstring ${BUILDU}/genkeypair ${BUILDU}/genchallenge ${BUILDU}/getpubkey ${BUILDU}/answerchallenge
	
${BUILDU}/hashstring: hashstring.cpp ${BUILDC}/cube2crypto.o ${BUILDC}/cube2crypto.h
	mkdir -p ${BUILDU}
	g++ -Wall -O2 -o $@ $^

${BUILDU}/genkeypair: genkeypair.cpp ${UTILDEPS}
	mkdir -p ${BUILDU}
	g++ -Wall -O2 -o $@ $^
	
${BUILDU}/genchallenge: genchallenge.cpp ${UTILDEPS}
	mkdir -p ${BUILDU}
	g++ -Wall -O2 -o $@ $^
	
${BUILDU}/getpubkey: getpubkey.cpp ${UTILDEPS}
	mkdir -p ${BUILDU}
	g++ -Wall -O2 -o $@ $^

${BUILDU}/answerchallenge: answerchallenge.cpp ${UTILDEPS}
	mkdir -p ${BUILDU}
	g++ -Wall -O2 -o $@ $^

cube2crypto_c: ${UTILDEPS}

${BUILDC}/cube2crypto.o: cube2crypto.cpp shared/crypto.cpp shared/tools.h
	mkdir -p ${BUILDC}
	g++ -Wall -O0 -g -fPIC -c -o $@ $<

${BUILDC}/cube2crypto.h: cube2crypto.h
	cp cube2crypto.h ${BUILDC}/

${BUILDS}/cube2crypto.so: ${UTILDEPS}
	mkdir -p ${BUILDS}
	g++ -Wall -O2 -shared -o $@ $<

cube2crypto_js: ${BUILDJ}/cube2crypto.o.js ${BUILDJ}/cube2crypto.h.js

${BUILDJ}/cube2crypto.o.js: cube2crypto.cpp shared/crypto.cpp shared/tools.h
	mkdir -p ${BUILDJ}
	~/git/emscripten/em++ -Wall -O2 -o ${BUILDJ}/cube2crypto.o.js cube2crypto.cpp -s EXPORTED_FUNCTIONS="['_cube2crypto_hashstring', '_cube2crypto_genkeypair', '_cube2crypto_getpubkey', '_cube2crypto_genchallenge', '_cube2crypto_answerchallenge']" -s PRECISE_I64_MATH=1

${BUILDJ}/cube2crypto.h.js: cube2crypto.h.js
	cp cube2crypto.h.js ${BUILDJ}/

cube2crypto_py: cube2crypto.h py.cube2crypto.cpp setup.py
	mkdir -p ${BUILDP}
	python setup.py build

ifneq ("$(wildcard build/lib*)", "")
  MOVELIBS = mv -f build/lib* ${BUILDP}/
endif

tidy:
	mkdir -p ${BUILDP}
	rm -rf build/temp*
	
	#only move the lib* folders if they exist
	${MOVELIBS}
	
	rm -rf a.out

clean: tidy
	rm -rf build/c
	rm -rf build/py
	rm -rf build/util
	rm -rf build/shared
	rm -rf *.o a.out

install:
	python setup.py install
