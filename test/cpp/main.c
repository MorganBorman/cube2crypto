#include <stdio.h>
#include <stdlib.h>
#include "../../build/c/cube2crypto.h"

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
	{"abc", 							"a0a2f0872ff799f2f853ea9aa76ce9b0ff6a1b0eb5af7417"},
	{"message digest", 						"a033b07c17cf5c6f6f2bdde50922eb9509d00bec803303f7"},
	{"abcdefghijklmnopqrstuvwxyz", 					"845ffe56cce48f566d2d5b4dae629b8e8e52bde17283aeb4"},
	{"abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq", 	"dd61d98336b2c88a5407ab5c9d9cd52829b66c20f65a9f2e"},
};

#define NUMSTRINGHASHES ((int)(sizeof(stringhashes)/sizeof(stringhashes[0])))

static struct passwordhash
{
	int cn;
	int sessionid;
	const char *pwd;
	const char *hash;
} passwordhashes[] =
{
	{0, 	0, 	"", 								"8818313ef4b23397d349affb4436256e3d7d5c645c8b8278"},
	{1, 	13333, 	"a", 								"210246fac5d808b283683e38da7236672aaf41aa6d27bf3b"},
	{5, 	112211, "abc", 								"da46fcd0c145d5fefe74759660272d07302d5836b6365c45"},
	{21, 	323344, "message digest", 						"d753158e72f042bbea50f19675ec1a785213e3999d23ee30"},
	{117, 	13243, 	"abcdefghijklmnopqrstuvwxyz", 					"8225119b22966d3418fcc94762c629fbbf2942c68db0d247"},
	{0, 	12345, 	"abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq", 	"1fae21a15070bd4415efa2259bb02ac3ad3bcf50798cbe0a"},
};

#define NUMPASSWORDHASHES ((int)(sizeof(passwordhashes)/sizeof(passwordhashes[0])))

static struct authkey
{
	const char *pwd;
	const char *private;
	const char *public;
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
	
	printf("String Hashing\n---------------------------------------------------------------------\n");
	
	for (ix = 0; ix < NUMSTRINGHASHES; ix++)
	{
		printf("Hashing: '%s'\nExpecting: '%s'\n", stringhashes[ix].string, stringhashes[ix].hash);
		result = cube2crypto_hashstring(stringhashes[ix].string, 512);
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
	}
	
	printf("Password Hashing\n---------------------------------------------------------------------\n");
	
	for (ix = 0; ix < NUMPASSWORDHASHES; ix++)
	{
		printf("Hashing: '%s'\nWith cn: %d\nWith sessionid: %d\nExpecting: '%s'\n", passwordhashes[ix].pwd, passwordhashes[ix].cn, passwordhashes[ix].sessionid, passwordhashes[ix].hash);
		result = cube2crypto_hashpassword(passwordhashes[ix].cn, passwordhashes[ix].sessionid, passwordhashes[ix].pwd);
		printf("Received: '%s'\n\n", result);
		if(!strcmp(result, passwordhashes[ix].hash))
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
	}
	
	printf("Keygen\n---------------------------------------------------------------------\n");
	
	for (ix = 0; ix < NUMAUTHKEYS; ix++)
	{
		printf("Seed: '%s'\nExpected Private: '%s'\nExpected Public: '%s'\n", authkeys[ix].pwd, authkeys[ix].private, authkeys[ix].public);
		result = cube2crypto_genkeypair(authkeys[ix].pwd);
		printf("Received Private: '%s'\n", result);
		printf("Received Public: '%s'\n\n", result+50);
		if(!strcmp(result, authkeys[ix].private) && !strcmp(result+50, authkeys[ix].public))
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
	}
	
	printf("Get public key\n---------------------------------------------------------------------\n");
	
	for (ix = 0; ix < NUMAUTHKEYS; ix++)
	{
		printf("Given Private: '%s'\nExpected Public: '%s'\n", authkeys[ix].private, authkeys[ix].public);
		result = cube2crypto_getpubkey(authkeys[ix].private);
		printf("Received Public: '%s'\n\n", result);
		if(!strcmp(result, authkeys[ix].public))
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
	}
	
	printf("Challenges\n---------------------------------------------------------------------\n");
	
	char *given_answer;
	
	for (ix = 0; ix < NUMAUTHKEYS; ix++)
	{
		printf("Public: '%s'\n", authkeys[ix].public);
		result = cube2crypto_genchallenge(authkeys[ix].public, authkeys[ix].pwd);
		printf("Challenge: '%s'\n", result);
		printf("Expected Answer: '%s'\n", result+51);
		
		given_answer = cube2crypto_answerchallenge(authkeys[ix].private, result);
		printf("Given Answer: '%s'\n\n", given_answer);
		
		if(!strcmp(result+51, given_answer))
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
	}

	printf("Overall results\n---------------------------------------------------------------------\n\n");
	printf("Passes: %d\n", passes);
	printf("Failures: %d\n", failures);
}
