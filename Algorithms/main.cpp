#include <bitset>
#include <iostream>
#include <string>
#include <vector>

#include "base.hpp"
#include "sha256.h"

int main() {
    std::string input = "`1234567890-=qwertyuiop[]\\asdfghjkl;'zxcvbnm,./"
                        "~!@#$%^&*()_+QWERTYUIOP{}|ASDFGHJKL:\"ZXCVBNM<>?";
    std::string bin_hash = sha256_to_bin(input);
    std::string hash = sha256_to_hex(input);
    std::string base91_hash = sha256_to_base91(input);


    std::cout << bin_hash << "\n";
    std::cout << hash << "\n";
    std::cout << base91_hash << "\n";

    return 0;
}