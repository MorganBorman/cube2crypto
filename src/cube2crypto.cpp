/*
* cube2crypto.cpp
* Main wrapper for crypto.cpp. All compilation targets use this file.
* Copyright (c) 2012 Morgan Borman
* E-mail: morgan.borman@gmail.com
*
* This software is licensed under the terms of the Zlib license.
* http://en.wikipedia.org/wiki/Zlib_License
*/

#include "shared/crypto.cpp"
#include "cube2crypto.h"
#include <iostream>

extern "C" 
{
	char *cube2crypto_hashstring(const char *str, int hashlen)
	{
		char *hash = (char*)malloc(sizeof(char[hashlen+1]));
		if(!crypto::hashstring(str, hash, hashlen)) *hash = '\0';
		return hash;
	}

	stringpair cube2crypto_genkeypair(const char *seed)
	{
		stringpair keypair;

		keypair.first = (char*)malloc(sizeof(char[49]));
		keypair.second = (char*)malloc(sizeof(char[50]));

		crypto::genkeypair(seed, keypair.first, keypair.second);

		return keypair;
	}

	char *cube2crypto_getpubkey(const char *privkey)
	{
		char *pubkey = (char*)malloc(sizeof(char[50]));
		crypto::getpubkey(privkey, pubkey);

		return pubkey;
	}

	stringpair cube2crypto_genchallenge(const char *pubkey, const char *seed)
	{
		stringpair validation;

		validation.first = (char*)malloc(sizeof(char[50]));
		validation.second = (char*)malloc(sizeof(char[49]));

		crypto::genchallenge(pubkey, seed, validation.first, validation.second);

		return validation;
	}

	char *cube2crypto_answerchallenge(const char *privkey, const char *challenge)
	{
		char *answerstr = (char*)malloc(sizeof(char[49]));

		crypto::answerchallenge(privkey, challenge, answerstr);

		return answerstr;
	}
}
