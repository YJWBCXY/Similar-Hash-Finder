#include <iostream>
#include <string>
#include <vector>

#include "sha256.h"

int main()
{
	std::vector<std::string> out = sha256("test");
	int i = 0;

	for (std::string _string : out) {
		std::cout << _string;
		std::cout << "\n";
	}

	return 0;
}