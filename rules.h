//@author   Alim Ozdemir 150140807
//@date     23.04.2017
//@desc
#include <map>
#include <string.h>

enum RULES {
	DT, NN, VR, PR, AD,
	NP, PP, VP, S,
	NONE
};

static std::multimap<RULES, std::pair<RULES, RULES>> ruleMap;
std::pair < RULES, std::pair<RULES, RULES>> generateKey(RULES r1, RULES r2, RULES r3);
std::pair < std::string, RULES> generateWordKey(std::string, RULES);

static std::map< std::string, RULES > wordMap;
static std::map<RULES, std::string> RS;
//All rules
void init() {

	if (RS.size() == 0) {
#define INSERT_ENUM_STRING(e) RS[e] = #e
		INSERT_ENUM_STRING(DT);
		INSERT_ENUM_STRING(NN);
		INSERT_ENUM_STRING(VR);
		INSERT_ENUM_STRING(PR);
		INSERT_ENUM_STRING(AD);
		INSERT_ENUM_STRING(NP);
		INSERT_ENUM_STRING(PP);
		INSERT_ENUM_STRING(VP);
		INSERT_ENUM_STRING(S);
#undef INSERT_ENUM_STRING
	}

	if (ruleMap.size() == 0) {

		ruleMap.insert(generateKey(RULES::NP, RULES::NN, RULES::NN));
		ruleMap.insert(generateKey(RULES::NP, RULES::AD, RULES::NN));
		ruleMap.insert(generateKey(RULES::NP, RULES::AD, RULES::NP));
		ruleMap.insert(generateKey(RULES::NP, RULES::DT, RULES::NP));
		ruleMap.insert(generateKey(RULES::NP, RULES::DT, RULES::NN));

		ruleMap.insert(generateKey(RULES::PP, RULES::PR, RULES::NN));
		ruleMap.insert(generateKey(RULES::PP, RULES::PR, RULES::NP));


		ruleMap.insert(generateKey(RULES::VP, RULES::VR, RULES::PP));
		ruleMap.insert(generateKey(RULES::VP, RULES::NN, RULES::VR));
		ruleMap.insert(generateKey(RULES::VP, RULES::NP, RULES::VR));
		ruleMap.insert(generateKey(RULES::VP, RULES::VR, RULES::NP));

		//ruleMap.insert(generateKey(RULES::VP, RULES::NP, RULES::VP));

		ruleMap.insert(generateKey(RULES::S, RULES::NP, RULES::VP));
		ruleMap.insert(generateKey(RULES::S, RULES::NN, RULES::VP));
	}

	if (wordMap.size() == 0) {
		wordMap.insert(generateWordKey("that", RULES::DT));
		wordMap.insert(generateWordKey("this", RULES::DT));
		wordMap.insert(generateWordKey("a", RULES::DT));
		wordMap.insert(generateWordKey("the", RULES::DT));

		wordMap.insert(generateWordKey("book", RULES::NN));
		wordMap.insert(generateWordKey("flight", RULES::NN));
		wordMap.insert(generateWordKey("cat", RULES::NN));
		wordMap.insert(generateWordKey("mat", RULES::NN));
		wordMap.insert(generateWordKey("i", RULES::NN));
		wordMap.insert(generateWordKey("you", RULES::NN));
		wordMap.insert(generateWordKey("they", RULES::NN));

		wordMap.insert(generateWordKey("booked", RULES::VR));
		wordMap.insert(generateWordKey("included", RULES::VR));
		wordMap.insert(generateWordKey("preferred", RULES::VR));
		wordMap.insert(generateWordKey("sat", RULES::VR));


		wordMap.insert(generateWordKey("from", RULES::PR));
		wordMap.insert(generateWordKey("to", RULES::PR));
		wordMap.insert(generateWordKey("on", RULES::PR));
		wordMap.insert(generateWordKey("near", RULES::PR));
		wordMap.insert(generateWordKey("through", RULES::PR));


		wordMap.insert(generateWordKey("big", RULES::AD));
		wordMap.insert(generateWordKey("heavy", RULES::AD));
		wordMap.insert(generateWordKey("beautiful", RULES::AD));
		wordMap.insert(generateWordKey("cheap", RULES::AD));
	}
}

std::pair < RULES, std::pair<RULES, RULES>> generateKey(RULES r1, RULES r2, RULES r3) {

	auto pp = std::pair<RULES, RULES>(r2, r3);
	return std::pair < RULES, std::pair<RULES, RULES>>(r1, pp);
}

std::pair < std::string, RULES> generateWordKey(std::string word, RULES r) {
	return std::pair < std::string, RULES >(word, r);
}

RULES find_rule(RULES r1, RULES r2) {
	RULES result = RULES::NONE;
	
	auto it = ruleMap.begin();
	for (; it != ruleMap.end(); it++) {
		if ((*it).second.first == r1 && (*it).second.second == r2) {
			result = (*it).first;
			break;
		}
	}
	
	
	return result;
}