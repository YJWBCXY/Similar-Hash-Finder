#include "pch.h"

#include "../Algorithms/sha256.h"

namespace Algorithms {
	TEST(sha256, EmptyString) {
		std::string hash;
		hash = sha256_to_hex("");
		ASSERT_EQ(hash, "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855");
	}
	TEST(sha256, OneChunkMessageBlock) {
		std::vector<std::string> input = {
			"Lorem ipsum dolor sit amet, consectetur adipiscing ut.",
			"8PreT;TdB@}YPLzHti_xkH/Qkz.ia",
			"@/(hCRMAD[9zz/2E,-WD!&SYbC{4EG0yE%T!!:7TkDG",
			"UzRG!Z{*rbmuvMkDBrQ8teRLFYk03:mEcpDgF3",
			"]/WmN/;X",
			"/YprdBw",
			".kAi:nu/]L3@U$HYM=8Kj",
			"w*RSEn},,17J"
		}, test = {
			"59fff55d6ad9adffb0a5cf64c457ca85c97406884ec023611820c9d0846a4597",
			"b621a68637f21b260219a31d52f5dc29a105b6566b974fbc2cafadcd1fc922a5",
			"df1f2ac600e1e2fe7fe38ce92726a1fae292f772df1ada37c3f96315f2246efb",
			"dc9430dc852f53b43e5b51ed6cf6e11c1b541e11c2b2e0056046d6e077e905b0",
			"6a5fbf796818f0471461022407e37f6d42ad1215cd02cad3a845080fce6fbbcc",
			"701b432e624bf28f8d51ff182d5ed5ce112bf4f22069bf9abc91600ef38c1200",
			"f280b639b2248ecaf8f27f047f59458a5a8ecdb7cf75fa8c0635b5160c41cf3f",
			"5217b27bd5a87930dee9fb61591e05f19a39eb3b46ca729be5befa4cd120d523"
		}, result;
		int lenght = input.size();
		for (int i = 0;i < lenght;i++) {
			result.push_back(sha256_to_hex(input[i]));
			ASSERT_EQ(result[i], test[i]);
		}
	}
	TEST(sha256, MultipleChunkMessageBlock) {
		std::vector<std::string> input = {
			"Lorem ipsum dolor sit amet, consectetur adipiscing elit. In ornare metus sapien, vitae semper mi posuere at massa nunc.",
			"Lorem ipsum dolor sit amet, consectetur adipiscing elit. Vestibulum placerat tortor eu sem rutrum cursus. Cras sodales magna enim, id feugiat augue consectetur vitae. Orci varius nam.",
			"}.v6(D?1=PD$pK/(&8QV6HQ9XtqpdANBJyN?mmy_:+_cm0JtU;UmN8mGW6r+?7iN=(]b%]a+{.T!U7,(i@:{kMx(-72eGr2SweyT3%rw5Bvt,LySGz@=_i7wg4RRUN,Ehr#L+h/ad=)r8]SN?(V",
			"qE3=hiP,D}P!gvfAUv#WwL.yM5i?kuyTyZ#C0&B$U}[{jAr1]yhRBi[938]a;TagHW)];Zwt*[0&",
			"cVyn#dt;?6c1hxjZ*G#:ar_M,-wdRuL&[TR_AX@Y;FV%p,JtF8&tE@3bBQc7Tra1v&}k04Pz-0JByUtauHufQqHA,T$bB,(62k;k",
			"=0:0ixwq%[Mh9A.7(!!!Ef-U75[$jw20Y5vQwV{J2WF:=)%$9NBCN,b727z$#j%]aE81Y2?d04X2Hi3Ah.3b[EX$vuHAE*{AL14/+;,e68(QBB&RH",
			"M:#t)QyMBy(en*w.%{7Mtk,!&y5)rKM)tt{W{!gNbz)5Dd,5_D!xBZg+.k8",
			"}2HKXrSn.(%V[tYXt+:adwiM@4av2t()3#Gn,?V68%A?H[hj4NFG6KV5E9*Zg?tgW&we]6S&Y2u[3eJEhaHu{LnPg[6q6$umPw#d/T0!.rU"
		}, test = {
			"3541ab899ffbc19fab75d9f3bba6cb389056d441bbcc426713339ce6cbd5c5ad",
			"d5c0a7e9f4c1697e0a19c3e40d4a9391355a76c825ecc99d5746e47226eb15ad",
			"8d0855d43337481388d43c0fc173ae26f32edf21be131a163e36e4b185f80103",
			"9d70a95e8ed76ac78b576db8a10e0ea8c44d04160caa4d235c11e50a25fe3f98",
			"1974c3adfd8a9199ef3305456013ec445603a954f33543e9ba4b0e52c0acd267",
			"cc445211c41b5650cb7ec0bfae44715c2b6e55765a577c0083b6161f5ada9270",
			"813f5b1827aa52109f941bee0330214ffb0c13d7ccdd6fce81158d533b61a725",
			"bc9bc5ef051236a4725df6c65ca7ac5d885918b7afbe97b0a389b4719cdf388a"
		}, result;
		int lenght = input.size();
		for (int i = 0;i < lenght;i++) {
			result.push_back(sha256_to_hex(input[i]));
			ASSERT_EQ(result[i], test[i]);
		}
	}
	TEST(sha256, BinaryOutput) {
		std::vector<std::string> input = {
			"Lorem ipsum dolor sit amet, consectetur adipiscing ut.",
			"8PreT;TdB@}YPLzHti_xkH/Qkz.ia",
			"@/(hCRMAD[9zz/2E,-WD!&SYbC{4EG0yE%T!!:7TkDG",
			"UzRG!Z{*rbmuvMkDBrQ8teRLFYk03:mEcpDgF3",
			"]/WmN/;X",
			"/YprdBw",
			".kAi:nu/]L3@U$HYM=8Kj",
			"w*RSEn},,17J"
		}, test = {
			"0101100111111111111101010101110101101010110110011010110111111111"
			"1011000010100101110011110110010011000100010101111100101010000101"
            "1100100101110100000001101000100001001110110000000010001101100001"
			"0001100000100000110010011101000010000100011010100100010110010111",
			"1011011000100001101001101000011000110111111100100001101100100110"
			"0000001000011001101000110001110101010010111101011101110000101001"
			"1010000100000101101101100101011001101011100101110100111110111100"
			"0010110010101111101011011100110100011111110010010010001010100101",
			"1101111100011111001010101100011000000000111000011110001011111110"
			"0111111111100011100011001110100100100111001001101010000111111010"
			"1110001010010010111101110111001011011111000110101101101000110111"
			"1100001111111001011000110001010111110010001001000110111011111011",
			"1101110010010100001100001101110010000101001011110101001110110100"
			"0011111001011011010100011110110101101100111101101110000100011100"
			"0001101101010100000111100001000111000010101100101110000000000101"
			"0110000001000110110101101110000001110111111010010000010110110000",
			"0110101001011111101111110111100101101000000110001111000001000111"
			"0001010001100001000000100010010000000111111000110111111101101101"
			"0100001010101101000100100001010111001101000000101100101011010011"
			"1010100001000101000010000000111111001110011011111011101111001100",
			"0111000000011011010000110010111001100010010010111111001010001111"
			"1000110101010001111111110001100000101101010111101101010111001110"
			"0001000100101011111101001111001000100000011010011011111110011010"
			"1011110010010001011000000000111011110011100011000001001000000000",
			"1111001010000000101101100011100110110010001001001000111011001010"
			"1111100011110010011111110000010001111111010110010100010110001010"
			"0101101010001110110011011011011111001111011101011111101010001100"
			"0000011000110101101101010001011000001100010000011100111100111111",
			"0101001000010111101100100111101111010101101010000111100100110000"
			"1101111011101001111110110110000101011001000111100000010111110001"
			"1001101000111001111010110011101101000110110010100111001010011011"
			"1110010110111110111110100100110011010001001000001101010100100011"
		}, result;
		int lenght = input.size();
		for (int i = 0;i < lenght;i++) {
			result.push_back(sha256_to_bin(input[i]));
			ASSERT_EQ(result[i], test[i]);
		}
	}
	TEST(sha256, Base91Output) {
		std::vector<std::string> input = {
			"Lorem ipsum dolor sit amet, consectetur adipiscing ut.",
			"8PreT;TdB@}YPLzHti_xkH/Qkz.ia",
			"@/(hCRMAD[9zz/2E,-WD!&SYbC{4EG0yE%T!!:7TkDG",
			"UzRG!Z{*rbmuvMkDBrQ8teRLFYk03:mEcpDgF3",
			"]/WmN/;X",
			"/YprdBw",
			".kAi:nu/]L3@U$HYM=8Kj",
			"w*RSEn},,17J"
		}, test = {
			"R}Ls/:^={sB1M2F*IdYiM]Nt/NayYEaLUv!4:wdD",
			":E47EnT(#GQjn#?cq[Qa|D*l@#_Va129rmbZqY5D",
			"8~$wxAJI_~}*&1BH5uvh7zg17$h#JS_}He73&m*C",
			"!6YELE_R$fdm<7bmvFF+N7aGLi'tXAiMRuvQHC`B",
			"i}dnr/y'dGZ)yWYu>~cb_8Z7D#E08xWMNV;|]%WC",
			"R=]yE*]Md+!YUL>PK8!oae4Q/yR~/zWzoohVENAA",
			"8Cymdj0?3j#,5y8sEPP5IK]rw[U]$/6S@#zX(3kB",
			"3%P^K8f2vI[6dWnfkOS&uoF(fMo,I#L(ukkS?7,A"
		}, result;
		int lenght = input.size();
		for (int i = 0;i < lenght;i++) {
			result.push_back(sha256_to_base91(input[i]));
			ASSERT_EQ(result[i], test[i]);
		}
	}
	TEST(Tools, BitRotateRight) {
		std::vector<std::bitset<32>> input = {
			std::bitset<32>(1426881987),
			std::bitset<32>(3144134277),
			std::bitset<32>(3600352804),
			std::bitset<32>(607225278)
		};
		std::vector<std::vector<std::bitset<32>>> test{
			{ std::bitset<32>(1788972984), std::bitset<32>(2109953292), std::bitset<32>(1893024543), std::bitset<32>(838274388) },
			{ std::bitset<32>(3077371344), std::bitset<32>(2927999847), std::bitset<32>(2708396523), std::bitset<32>(2662995693) },
			{ std::bitset<32>(2597527748), std::bitset<32>(103077529), std::bitset<32>(2301994561), std::bitset<32>(1679332186) },
			{ std::bitset<32>(3297128631), std::bitset<32>(2243830833), std::bitset<32>(1871252577), std::bitset<32>(3323394192) }
		}, result(4);
		std::vector<int> shift = { 3,16,10,22 };

		int lenght = input.size();
		for (int i = 0;i < lenght;i++) {
			for (int j = 0;j < lenght;j++) {
				result[i].push_back(bit_rotate_right(input[i], shift[j]));
				ASSERT_EQ(result[i][j], test[i][j]) << "i:" << i << " j:" << j;
			}
		}
	}
	TEST(Tools, BitAdder) {
		std::vector<std::bitset<32>> input = {
			std::bitset<32>(2428436474),
			std::bitset<32>(3336571891),
			std::bitset<32>(1996064986),
			std::bitset<32>(3584528711)
		};
		std::vector<std::vector<std::bitset<32>>> test{
			{ std::bitset<32>(561905652), std::bitset<32>(1470041069), std::bitset<32>(129534164), std::bitset<32>(1717997889) },
			{ std::bitset<32>(1470041069), std::bitset<32>(2378176486), std::bitset<32>(1037669581), std::bitset<32>(2626133306) },
			{ std::bitset<32>(129534164), std::bitset<32>(1037669581), std::bitset<32>(3992129972), std::bitset<32>(1285626401) },
			{ std::bitset<32>(1717997889), std::bitset<32>(2626133306), std::bitset<32>(1285626401), std::bitset<32>(2874090126) },
		}, result(4);

			int lenght = input.size();
			for (int i = 0;i < lenght;i++) {
				for (int j = 0;j < lenght;j++) {
					result[i].push_back(bit_adder(input[i], input[j]));
					ASSERT_EQ(result[i][j], test[i][j]) << "i:" << i << " j:" << j;
				}
			}
	}
}