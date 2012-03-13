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

	char *cube2crypto_hashstring(const char *str, int hashlen);
	char *cube2crypto_hashpassword(int cn, int sessionid, const char *pwd);
	char *cube2crypto_genkeypair(char *seed);
	char *cube2crypto_getpubkey(char *privkey);
	char *cube2crypto_genchallenge(char *pubkey, char *seed);
	char *cube2crypto_answerchallenge(char *privkey, char *challenge);

#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif
