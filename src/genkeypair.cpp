#include "cube2crypto.h"
#include <stdlib.h>
#include <iostream>

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

void help()
{
	std::cout << "Usage: genkeypair <password>\n";
}

int main(int argc, char **argv)
{
	if(argc != 2 || !argv[1])
	{
		help();
		return EXIT_FAILURE;
	}
	stringpair answer = cube2crypto_genkeypair(argv[1]);

	std::cout << "private key:\t" << answer.first << "\n";
	std::cout << "public key:\t " << answer.second << "\n";

	free(answer.first);
	free(answer.second);

	return EXIT_SUCCESS;
}

