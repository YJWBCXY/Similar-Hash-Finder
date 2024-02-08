#pragma once
#include <string>
#include <vector>
#include <bitset>


std::vector<std::string> sha256_str_to_bin(std::string input) {
	std::vector<std::string> tmp,
		out;
	int i = 0,
		k = 1,
		left,
		size;

	for (char& _char : input) {
		tmp.push_back(std::bitset<8>(_char).to_string());
		i++;
	}
	tmp.push_back("10000000");



	while ((i + 1 + 8) > k * 64) {
		k++;
	}
	left = k * 64 - (i + 1 + 8);

	for (int j = 0;left > j;j++) {
		tmp.push_back("00000000");
	}

	size = tmp.size();
	for (int j = 0;j < size;j += 4) {
		out.push_back(tmp[j] + tmp[j + 1] + tmp[j + 2] + tmp[j + 3]);
	}


	std::string length;
	length = std::bitset<64>(i * 8).to_string();
	out.push_back(length.substr(0, 32));
	out.push_back(length.substr(32));

	return out;
}

std::vector<std::string> sha256(std::string message) {

	std::vector<std::string> out;

	out = sha256_str_to_bin(message);

	return out;
}