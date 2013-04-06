#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../src/build/c/cube2crypto.h"

//Some test data
////////////////////////////////////////////////////////////////////////////////////////

static struct stringhash
{
	const char *string;
	const char *hash;
} stringhashes[] =
{
	{"", 								"2339ca36c0310f42f529bb1b67e66161a7e48594d2ed373f"},
	{"a", 								"77ebbffee2e78fbae28c9fb35f787acf16e342f7f5428790"},
	{"abc", 							"a2ba41488e1c852ffb8b5cff145ba725159231c159b7f539"},
	{"message digest", 						"9d188fbc8702a159d0fc038457e144c115f7aca15aa5926f"},
	{"abcdefghijklmnopqrstuvwxyz", 					"71414a27ee5ed703404021fbcc5530a2b01106f23fb7ee9e"},
	{"abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq", 	"f0b79f1ab9c9852f7b16d07f8ef4a03c7ac136e1b7357fe8"},
};

#define NUMSTRINGHASHES ((int)(sizeof(stringhashes)/sizeof(stringhashes[0])))

static struct authkey
{
	const char *pwd;
	const char *privkey;
	const char *pubkey;
} authkeys[] =
{
	{"", 										"f373de2d49584e7a16166e76b1bb925f24f0130c63ac9332", "+2c1fb1dd4f2a7b9d81320497c64983e92cda412ed50f33aa"},
	{"a", 										"0978245f7f243e61fca787f53bf9c82eabf87e2eeffbbe77", "-afe5929327bd76371626cce7585006067603daf76f09c27e"},
	{"abc", 									"935f7b951c132951527ab541ffc5b8bff258c1e88414ab2a", "-d954ee56eddf2b71e206e67d48aaf4afe1cc70f8ca9d1058"},
	{"message digest", 								"f6295aa51aca7f511c441e754830cf0d951a2078cbf881d9", "-454c98466c45fce242724e6e989bdd9f841304a1fcba4787"},
	{"abcdefghijklmnopqrstuvwxyz", 							"e9ee7bf32f60110b2a0355ccbf120404307de5ee72a41417", "+15fda493cb1095ca40f652b0d208769bd42b9e234e48d1a8"},
	{"abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq", 			"8ef7537b1e631ca7c30a4fe8f70d61b7f2589c9ba1f97b0f", "+643d99cb21178557f4e965eb6dc1ec1e4f57b3b05375fafb"},
};

#define NUMAUTHKEYS ((int)(sizeof(authkeys)/sizeof(authkeys[0])))

int main(int argc, char *argv[])
{

	int passes = 0; //keep a count of those tests which passed.
	int failures = 0; //keep a count of those tests which failed.

	int ix; //used for iterating through each of the test data sets.
	char *result; //used for storing the returned data from each data set.
	stringpair resultpair;
	
	printf("String Hashing\n---------------------------------------------------------------------\n");
	
	for (ix = 0; ix < NUMSTRINGHASHES; ix++)
	{
		printf("Hashing: '%s'\nExpecting: '%s'\n", stringhashes[ix].string, stringhashes[ix].hash);
		result = cube2crypto_hashstring(stringhashes[ix].string);
		printf("Received: '%s'\n\n", result);
		if(!strcmp(result, stringhashes[ix].hash))
		{
			passes++;
			printf("pass\n\n");
		}
		else
		{
			failures++;
			printf("fail\n\n");
		}
		
		free(result);
		result = NULL;
	}
	
	printf("Keygen\n---------------------------------------------------------------------\n");
	
	for (ix = 0; ix < NUMAUTHKEYS; ix++)
	{
		printf("Seed: '%s'\nExpected Private: '%s'\nExpected Public: '%s'\n", authkeys[ix].pwd, authkeys[ix].privkey, authkeys[ix].pubkey);
		resultpair = cube2crypto_genkeypair(authkeys[ix].pwd);
		printf("Received Private: '%s'\n", resultpair.first);
		printf("Received Public: '%s'\n\n", resultpair.second);
		if(!strcmp(resultpair.first, authkeys[ix].privkey) && !strcmp(resultpair.second, authkeys[ix].pubkey))
		{
			passes++;
			printf("pass\n\n");
		}
		else
		{
			failures++;
			printf("fail\n\n");
		}

		free(resultpair.first);
		free(resultpair.second);
		resultpair.first = NULL;
		resultpair.second = NULL;
	}
	
	printf("Get public key\n---------------------------------------------------------------------\n");
	
	for (ix = 0; ix < NUMAUTHKEYS; ix++)
	{
		printf("Given Private: '%s'\nExpected Public: '%s'\n", authkeys[ix].privkey, authkeys[ix].pubkey);
		result = cube2crypto_getpubkey(authkeys[ix].privkey);
		printf("Received Public: '%s'\n\n", result);
		if(!strcmp(result, authkeys[ix].pubkey))
		{
			passes++;
			printf("pass\n\n");
		}
		else
		{
			failures++;
			printf("fail\n\n");
		}
		
		free(result);
		result = NULL;
	}
	
	printf("Challenges\n---------------------------------------------------------------------\n");
	
	for (ix = 0; ix < NUMAUTHKEYS; ix++)
	{
		printf("Public: '%s'\n", authkeys[ix].pubkey);
		resultpair = cube2crypto_genchallenge(authkeys[ix].pubkey, authkeys[ix].pwd);
		printf("Challenge: '%s'\n", resultpair.first);
		printf("Expected Answer: '%s'\n", resultpair.second);
		
		result = cube2crypto_answerchallenge(authkeys[ix].privkey, resultpair.first);
		printf("Given Answer: '%s'\n\n", result);
		
		if(!strcmp(result, resultpair.second))
		{
			passes++;
			printf("pass\n\n");
		}
		else
		{
			failures++;
			printf("fail\n\n");
		}
		
		free(result);
		result = NULL;
		free(resultpair.first);
		free(resultpair.second);
		resultpair.first = NULL;
		resultpair.second = NULL;
	}

	printf("Overall results\n---------------------------------------------------------------------\n\n");
	printf("Passes: %d\n", passes);
	printf("Failures: %d\n", failures);
}
