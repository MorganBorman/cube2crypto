#include "cube2crypto.h"
#include <stdlib.h>
#include <iostream>

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

void help()
{
	std::cout << "Usage: getpubkey <privkey>\n";
}

int main(int argc, char **argv)
{
	if(argc != 2 || !argv[1])
	{
		help();
		return EXIT_FAILURE;
	}
	char *answerstr;

	answerstr = cube2crypto_getpubkey(argv[1]);

	std::cout << "public key:\t " << answerstr << "\n";

	free(answerstr);

	return EXIT_SUCCESS;
}

