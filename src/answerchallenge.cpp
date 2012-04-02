#include "cube2crypto.h"
#include <iostream>

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

void help()
{
	std::cout << "Usage: answerchallenge <privkey> <challenge>\n";
}

int main(int argc, char **argv)
{
	if(argc != 3 || !argv[1])
	{
		help();
		return EXIT_FAILURE;
	}
	char *answerstr;

	answerstr = cube2crypto_answerchallenge(argv[1], argv[2]);

	std::cout << "answer:\t " << answerstr << "\n";
	return EXIT_SUCCESS;
}

