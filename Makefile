# Makefile
# Main Makefile for cube2crypto.
# Copyright (c) 2012 Morgan Borman
# E-mail: morgan.borman@gmail.com
#
# This software is licensed under the terms of the Zlib license.
# http://en.wikipedia.org/wiki/Zlib_License
#

all: cube2crypto_c cube2crypto_py build/shared/cube2crypto.so cube2crypto_js 

cube2crypto_c: build/c/cube2crypto.o build/c/cube2crypto.h

build/c/cube2crypto.o: cube2crypto.cpp shared/crypto.cpp shared/tools.h
	mkdir -p build/c
	g++ -Wall -O3 -fPIC -c -o build/c/cube2crypto.o cube2crypto.cpp

build/c/cube2crypto.h: cube2crypto.h
	cp cube2crypto.h build/c/

build/shared/cube2crypto.so: build/c/cube2crypto.o build/c/cube2crypto.h
	mkdir -p build/shared
	g++ -Wall -O3 -shared -o build/shared/cube2crypto.so build/c/cube2crypto.o

cube2crypto_js: build/js/cube2crypto.o.js build/js/cube2crypto.h.js

build/js/cube2crypto.o.js: cube2crypto.cpp shared/crypto.cpp shared/tools.h
	mkdir -p build/js
	~/git/emscripten/em++ -Wall -O3 -o build/js/cube2crypto.o.js cube2crypto.cpp -s EXPORTED_FUNCTIONS="['_cube2crypto_hashstring', '_cube2crypto_hashpassword', '_cube2crypto_genkeypair', '_cube2crypto_getkeypair', '_cube2crypto_genchallenge', '_cube2crypto_answerchallenge']"

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
