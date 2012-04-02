#include "cube2crypto.h"
#include <stdlib.h>
#include <iostream>

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

void help()
{
	std::cout << "Usage: genchallenge <pubkey> <seed>\n";
}

int main(int argc, char **argv)
{
	if(argc != 3 || !argv[1])
	{
		help();
		return EXIT_FAILURE;
	}

	stringpair answer = cube2crypto_genchallenge(argv[1], argv[2]);

	std::cout << "challenge:\t" << answer.first << "\n";
	std::cout << "answer:\t " << answer.second << "\n";

	free(answer.first);
	free(answer.second);

	return EXIT_SUCCESS;
}

