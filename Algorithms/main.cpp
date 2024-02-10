#include <iostream>
#include <string>
#include <vector>
#include <bitset>

#include "sha256.h"

int main()
{
	std::string hash = sha256("`1234567890-=qwertyuiop[]\\asdfghjkl;'zxcvbnm,./~!@#$%^&*()_+QWERTYUIOP{}|ASDFGHJKL:\"ZXCVBNM<>?");

	std::cout << hash;

	return 0;
}