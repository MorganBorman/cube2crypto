/*
* cube2crypto.h
* Main header for crypto.cpp.
* Copyright (c) 2012 Morgan Borman
* E-mail: morgan.borman@gmail.com
*
* This software is licensed under the terms of the Zlib license.
* http://en.wikipedia.org/wiki/Zlib_License
*/

#ifdef __cplusplus
extern "C" {
#endif

	struct stringpair
	{
		char *first;
		char *second;
	};

	char *cube2crypto_hashstring(const char *str, int hashlen);
	stringpair cube2crypto_genkeypair(const char *seed);
	char *cube2crypto_getpubkey(const char *privkey);
	stringpair cube2crypto_genchallenge(const char *pubkey, const char *seed);
	char *cube2crypto_answerchallenge(const char *privkey, const char *challenge);

#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif
