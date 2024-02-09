#pragma once
#include <string>
#include <vector>
#include <bitset>


std::vector<std::string> sha256_str_to_bin(std::string& input) {
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

std::bitset<32> bit_rotate_right(const std::bitset<32>& value, const int& shift) {
	return (value >> shift) | (value << (32 - shift));
}

std::bitset<32> bit_adder(const std::bitset<32>& a, const std::bitset<32>& b) {
	std::bitset<32> result,
		carry = 0;
	int i = 0;
	for (;i < 31;i++) {
		result[i] = a[i] ^ b[i] ^ carry[i];
		carry[i + 1] = (a[i] & b[i]) | ((a[i] ^ b[i]) & carry[i]);
	}
	result[i] = a[i] ^ b[i] ^ carry[i];
	return result;
}

std::vector<std::bitset<32>> sha256( std::string message) {

	std::vector<std::string> out;

	out = sha256_str_to_bin(message);

	std::vector<std::bitset<32>> bin_out;
	for (std::string _string : out) {
		bin_out.push_back(std::bitset<32>(_string));
	}

	int i = 0,
		lenght = out.size();
		std::vector <std::bitset<32>> w(64);
	while (i < lenght) {
		int w0 = 0, w1 = 1, w9 = 9, w14 = 14, w16 = 16;
		for (int j = 0;j < 16;j++, i++) {
			w[j] = bin_out[i];
		}
		while (w16 < 64) {
			std::bitset<32> sigma0, sigma1;
			sigma0 = bit_rotate_right(w[w1], 7) ^ bit_rotate_right(w[w1], 18) ^ (w[w1] >> 3);
			sigma1 = bit_rotate_right(w[w14], 17) ^ bit_rotate_right(w[w14], 19) ^ (w[w14] >> 10);
			w[w16] = bit_adder(bit_adder(bit_adder(w[w0], sigma0), w[w9]), sigma1);
			w0++;w1++;w9++;w14++;w16++;
		}
	}

	return w;
}