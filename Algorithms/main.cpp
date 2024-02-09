#include <iostream>
#include <string>
#include <vector>
#include <bitset>

#include "sha256.h"

int main()
{
	std::vector<std::bitset<32>> out = sha256("test");
	int i = 0;

	for (std::bitset<32> _bitset : out) {
		std::cout << _bitset;
		std::cout << "\n";
		i++;
	}
	std::cout << i;

	return 0;
}