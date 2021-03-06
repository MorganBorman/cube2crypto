#include "cube2crypto.h"
#include <stdlib.h>
#include <iostream>

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

void help()
{
	std::cout << "Usage: hashstring <seed>\n";
}

int main(int argc, char **argv)
{
	if(argc != 2 || !argv[1])
	{
		help();
		return EXIT_FAILURE;
	}

	char *answer = cube2crypto_hashstring(argv[1]);

	std::cout << "hash value:\t" << answer << "\n";

	free(answer);

	return EXIT_SUCCESS;
}
