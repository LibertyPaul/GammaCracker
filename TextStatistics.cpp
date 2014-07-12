#include <vector>
#include <cstdint>
#include <ostream>




using namespace std;
#include "CharProbability.hpp"
#include "TextStatistics.hpp"



TextStatistics::TextStatistics(const vector<char16_t> &text): text(text){}



vector<CharProbability> TextStatistics::getProbabilities(){
	vector<CharProbability> stats;
	for(auto ch : text){
		bool isExist = false;
		for(auto &charStat : stats)
			if(charStat.ch == ch){
				++charStat.probability;
				isExist = true;
				break;
			}
		if(isExist == false)
			stats.emplace_back(ch);
	}
	return stats;
}
