# setup.py
# Bare bones distutils script for cube2crypto.
# Copyright (c) 2012 Morgan Borman
# E-mail: morgan.borman@gmail.com
#
# This software is licensed under the terms of the Zlib license.
# http://en.wikipedia.org/wiki/Zlib_License

from distutils.core import setup, Extension

cube2crypto_module = Extension(	'cube2crypto', 
				sources = ['py.cube2crypto.cpp'],
				libraries = [],
				library_dirs = [],
				extra_objects = ['build/c/cube2crypto.o'],
				)

setup (name = 'cube2crypto',
       version = '1.0',
       description = 'This is a package providing convenient access to the cryptographic and authentication functions build into the cube2 engine.',
       ext_modules = [cube2crypto_module])
