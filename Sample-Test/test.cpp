#include "pch.h"

#include "../Algorithms/sha256.h"

namespace Algorithms {
	TEST(sha256, EmptyString) {
		std::string hash;
		hash = sha256("");
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
			result.push_back(sha256(input[i]));
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
			result.push_back(sha256(input[i]));
			ASSERT_EQ(result[i], test[i]);
		}
	}
}