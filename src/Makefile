# Makefile
# Main Makefile for cube2crypto.
# Copyright (c) 2012 Morgan Borman
# E-mail: morgan.borman@gmail.com
#
# This software is licensed under the terms of the Zlib license.
# http://en.wikipedia.org/wiki/Zlib_License
#

all: cube2crypto_c cube2crypto_py build/shared/cube2crypto.so utils cube2crypto_js

utils: build/util/hashstring build/util/genkeypair build/util/genchallenge build/util/getpubkey build/util/answerchallenge
	
build/util/hashstring: hashstring.cpp build/c/cube2crypto.o build/c/cube2crypto.h
	mkdir -p build/util
	g++ -Wall -O2 -o build/util/hashstring build/c/cube2crypto.o -Ibuild/c hashstring.cpp

build/util/genkeypair: genkeypair.cpp build/c/cube2crypto.o build/c/cube2crypto.h
	mkdir -p build/util
	g++ -Wall -O2 -o build/util/genkeypair build/c/cube2crypto.o -Ibuild/c genkeypair.cpp
	
build/util/genchallenge: genchallenge.cpp build/c/cube2crypto.o build/c/cube2crypto.h
	mkdir -p build/util
	g++ -Wall -O2 -o build/util/genchallenge build/c/cube2crypto.o -Ibuild/c genchallenge.cpp
	
build/util/getpubkey: getpubkey.cpp build/c/cube2crypto.o build/c/cube2crypto.h
	mkdir -p build/util
	g++ -Wall -O2 -o build/util/getpubkey build/c/cube2crypto.o -Ibuild/c getpubkey.cpp

build/util/answerchallenge: answerchallenge.cpp build/c/cube2crypto.o build/c/cube2crypto.h
	mkdir -p build/util
	g++ -Wall -O2 -o build/util/answerchallenge build/c/cube2crypto.o -Ibuild/c answerchallenge.cpp

cube2crypto_c: build/c/cube2crypto.o build/c/cube2crypto.h

build/c/cube2crypto.o: cube2crypto.cpp shared/crypto.cpp shared/tools.h
	mkdir -p build/c
	g++ -Wall -O0 -g -fPIC -c -o build/c/cube2crypto.o cube2crypto.cpp

build/c/cube2crypto.h: cube2crypto.h
	cp cube2crypto.h build/c/

build/shared/cube2crypto.so: build/c/cube2crypto.o build/c/cube2crypto.h
	mkdir -p build/shared
	g++ -Wall -O2 -shared -o build/shared/cube2crypto.so build/c/cube2crypto.o

cube2crypto_js: build/js/cube2crypto.o.js build/js/cube2crypto.h.js

build/js/cube2crypto.o.js: cube2crypto.cpp shared/crypto.cpp shared/tools.h
	mkdir -p build/js
	~/git/emscripten/em++ -Wall -O2 -o build/js/cube2crypto.o.js cube2crypto.cpp -s EXPORTED_FUNCTIONS="['_cube2crypto_hashstring', '_cube2crypto_genkeypair', '_cube2crypto_getpubkey', '_cube2crypto_genchallenge', '_cube2crypto_answerchallenge']" -s PRECISE_I64_MATH=1

build/js/cube2crypto.h.js: cube2crypto.h.js
	cp cube2crypto.h.js build/js/

cube2crypto_py: cube2crypto.h py.cube2crypto.cpp setup.py
	mkdir -p build/py
	python setup.py build

clean:
	rm -rf build
	rm -rf *.o a.out

tidy:
	mkdir -p build/py
	rm -rf build/temp*
	mv -f build/lib* build/py/
	rm -rf a.out

install:
	python setup.py install
