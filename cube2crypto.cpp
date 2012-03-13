#include "shared/crypto.cpp"
#include <iostream>

extern "C" 
{
	char *cube2crypto_hashstring(const char *str, int hashlen)
	{
		char *hash = new char[hashlen+1];
		if(!crypto::hashstring(str, hash, sizeof(hash))) *hash = '\0';
		return hash;
	}

	char *cube2crypto_hashpassword(int cn, int sessionid, char *pwd)
	{
		char *hash = new char[MAXSTRLEN];
		char buf[2*sizeof(string)];
		formatstring(buf)("%d %d ", cn, sessionid);
		copystring(&buf[strlen(buf)], pwd);
		if(!crypto::hashstring(buf, hash, sizeof(hash))) *hash = '\0';
		return hash;
	}

	char *cube2crypto_genkeypair(char *seed)
	{
		char *keypair = new char[98];

		char *privkey = &keypair[0];
		char *pubkey = &keypair[50];

		crypto::genkeypair(seed, privkey, pubkey);		

		return keypair;
	}

	char *cube2crypto_getpubkey(char *privkey)
	{
		char *pubkey = new char[49];
		crypto::getpubkey(privkey, pubkey);

		return pubkey;
	}

	char *cube2crypto_genchallenge(char *pubkey, char *seed)
	{
		char *validation = new char[99];

		char *challengestr = &validation[0];
		char *answerstr = &validation[51];

		crypto::genchallenge(pubkey, seed, challengestr, answerstr);

		return validation;		
	}

	char *cube2crypto_answerchallenge(char *privkey, char *challenge)
	{
		char *answerstr = new char[49];

		crypto::answerchallenge(privkey, challenge, answerstr);

		return answerstr;
	}
}
