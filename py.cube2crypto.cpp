#include <Python.h>
#include "cube2crypto.h"

static PyObject *hashstring(PyObject *self, PyObject *args)
{
	char *str;
	int hashlen;

	if (!PyArg_ParseTuple(args, "si", &str, &hashlen)) return NULL;

	char *hash = cube2crypto_hashstring(str, hashlen);

	PyObject *phash = Py_BuildValue("s", hash);

	free(hash);

	return phash;
}

static PyObject *hashpassword(PyObject *self, PyObject *args)
{
	int cn, sessionid;
	char *str;

	if (!PyArg_ParseTuple(args, "iis", &cn, &sessionid, &str)) return NULL;

	char *hash = cube2crypto_hashpassword(cn, sessionid, str);

	PyObject *phash = Py_BuildValue("s", hash);

	free(hash);

	return phash;
}

static PyObject *genkeypair(PyObject *self, PyObject *args)
{
	char *seed;

	if (!PyArg_ParseTuple(args, "s", &seed)) return NULL;

	char *pair = cube2crypto_genkeypair(seed);

	char *privkey = &pair[0];
	char *pubkey = &pair[50];

	PyObject *keypair = Py_BuildValue("(ss)", privkey, pubkey);

	free(pair);

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

	char *challenge = cube2crypto_genchallenge(pubkey, seed);

	//char *challenge = challenge[0];
	char *answer = &challenge[51];

	PyObject *pchallenge = Py_BuildValue("(ss)", challenge, answer);

	free(challenge);

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
	def(hashpassword, 	"Hash a password using the same pattern as the cube2 engine given the cn, sessionid, and password."),
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
