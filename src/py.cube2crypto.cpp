/*
* py.cube2crypto.cpp
* Python wrapper for cube2crypto.
* Copyright (c) 2012 Morgan Borman
* E-mail: morgan.borman@gmail.com
*
* This software is licensed under the terms of the Zlib license.
* http://en.wikipedia.org/wiki/Zlib_License
*/

#include <Python.h>
#include "cube2crypto.h"

static PyObject *hashstring(PyObject *self, PyObject *args)
{
	char *str;

	if (!PyArg_ParseTuple(args, "s", &str)) return NULL;

	char *hash = cube2crypto_hashstring(str);

	PyObject *phash = Py_BuildValue("s", hash);

	free(hash);

	return phash;
}

static PyObject *genkeypair(PyObject *self, PyObject *args)
{
	char *seed;

	if (!PyArg_ParseTuple(args, "s", &seed)) return NULL;

	stringpair answer = cube2crypto_genkeypair(seed);

	PyObject *keypair = Py_BuildValue("(ss)", answer.first, answer.second);

	free(answer.first);
	free(answer.second);

	return keypair;
}

static PyObject *getpubkey(PyObject *self, PyObject *args)
{
	char *privkey;

	if (!PyArg_ParseTuple(args, "s", &privkey)) return NULL;

	char *pubkey = cube2crypto_getpubkey(privkey);

	PyObject *ppubkey = Py_BuildValue("s", pubkey);

	free(pubkey);

	return ppubkey;
}

static PyObject *genchallenge(PyObject *self, PyObject *args)
{
	char *pubkey;
	char *seed;

	if (!PyArg_ParseTuple(args, "ss", &pubkey, &seed)) return NULL;

	stringpair challenge = cube2crypto_genchallenge(pubkey, seed);

	PyObject *pchallenge = Py_BuildValue("(ss)", challenge.first, challenge.second);

	free(challenge.first);
	free(challenge.second);

	return pchallenge;
}

static PyObject *answerchallenge(PyObject *self, PyObject *args)
{
	char *privkey;
	char *challenge;

	if (!PyArg_ParseTuple(args, "ss", &privkey, &challenge)) return NULL;

	char *answer = cube2crypto_answerchallenge(privkey, challenge);

	PyObject *panswer = Py_BuildValue("s", answer);

	free(answer);

	return panswer;
}

#define def(NAME, DOC)  {#NAME, NAME, METH_VARARGS, DOC}

static PyMethodDef ModuleMethods[] = 
{
	def(hashstring, 	"Hash a string given the string and the length of the desired hash."),
	def(genkeypair, 	"Generate an auth key pair given a seed string."),
	def(getpubkey, 		"Get the public key given the private one."),
	def(genchallenge, 	"Generate a challenge answer pair given the public key, and a seed string."),
	def(answerchallenge, 	"Generate the answer to a challenge given the private key and the challenge."),
	{NULL, NULL, 0, NULL}        /* Sentinel */
};

PyMODINIT_FUNC initcube2crypto(void)
{
	//PyObject *m = 
	Py_InitModule("cube2crypto", ModuleMethods);
}
