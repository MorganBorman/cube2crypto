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
