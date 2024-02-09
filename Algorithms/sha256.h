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

	const std::vector<std::bitset<32>> k = {
		std::bitset<32>(1116352408),std::bitset<32>(1899447441),
		std::bitset<32>(3049323471),std::bitset<32>(3921009573),
		std::bitset<32>(961987163),std::bitset<32>(1508970993),
		std::bitset<32>(2453635748),std::bitset<32>(2870763221),
		std::bitset<32>(3624381080),std::bitset<32>(310598401),
		std::bitset<32>(607225278),std::bitset<32>(1426881987),
		std::bitset<32>(1925078388),std::bitset<32>(2162078206),
		std::bitset<32>(2614888103),std::bitset<32>(3248222580),
		std::bitset<32>(3835390401),std::bitset<32>(4022224774),
		std::bitset<32>(264347078),std::bitset<32>(604807628),
		std::bitset<32>(770255983),std::bitset<32>(1249150122),
		std::bitset<32>(1555081692),std::bitset<32>(1996064986),
		std::bitset<32>(2554220882),std::bitset<32>(2821834349),
		std::bitset<32>(2952996808),std::bitset<32>(3210313671),
		std::bitset<32>(3336571891),std::bitset<32>(3584528711),
		std::bitset<32>(113926993),std::bitset<32>(338241895),
		std::bitset<32>(666307205),std::bitset<32>(773529912),
		std::bitset<32>(1294757372),std::bitset<32>(1396182291),
		std::bitset<32>(1695183700),std::bitset<32>(1986661051),
		std::bitset<32>(2177026350),std::bitset<32>(2456956037),
		std::bitset<32>(2730485921),std::bitset<32>(2820302411),
		std::bitset<32>(3259730800),std::bitset<32>(3345764771),
		std::bitset<32>(3516065817),std::bitset<32>(3600352804),
		std::bitset<32>(4094571909),std::bitset<32>(275423344),
		std::bitset<32>(430227734),std::bitset<32>(506948616),
		std::bitset<32>(659060556),std::bitset<32>(883997877),
		std::bitset<32>(958139571),std::bitset<32>(1322822218),
		std::bitset<32>(1537002063),std::bitset<32>(1747873779),
		std::bitset<32>(1955562222),std::bitset<32>(2024104815),
		std::bitset<32>(2227730452),std::bitset<32>(2361852424),
		std::bitset<32>(2428436474),std::bitset<32>(2756734187),
		std::bitset<32>(3204031479),std::bitset<32>(3329325298)
	};
	//hash value
	std::vector<std::bitset<32>> hash = {
		std::bitset<32>(1779033703),
		std::bitset<32>(3144134277),
		std::bitset<32>(1013904242),
		std::bitset<32>(2773480762),
		std::bitset<32>(1359893119),
		std::bitset<32>(2600822924),
		std::bitset<32>(528734635),
		std::bitset<32>(1541459225)
	};
	//working variables
	std::bitset<32>
		a = hash[0],
		b = hash[1],
		c = hash[2],
		d = hash[3],
		e = hash[4],
		f = hash[5],
		g = hash[6],
		h = hash[7];
	while (i < lenght) {
		std::vector <std::bitset<32>> w(64);
		int w0 = 0, w1 = 1, w9 = 9, w14 = 14, w16 = 16;
		for (int j = 0;j < 16;j++, i++) {
			w[j] = bin_out[i];
		}
		std::bitset<32> sigma0, sigma1;
		while (w16 < 64) {
			sigma0 = bit_rotate_right(w[w1], 7) ^ bit_rotate_right(w[w1], 18) ^ (w[w1] >> 3);
			sigma1 = bit_rotate_right(w[w14], 17) ^ bit_rotate_right(w[w14], 19) ^ (w[w14] >> 10);
			w[w16] = bit_adder(bit_adder(bit_adder(w[w0], sigma0), w[w9]), sigma1);
			w0++;w1++;w9++;w14++;w16++;
		}
		std::bitset<32> tmp1, tmp2, majority;
	}

	return k;
}