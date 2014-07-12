#include <vector>
#include <stdexcept>
#include <algorithm>
#include <set>
#include <cmath>//abs()

using namespace std;
#include "CharProbability.hpp"
#include "stuff.hpp"




vector<CharProbability> getProbabilities(const vector<wchar_t> &text){
	uint64_t length = text.size();
	vector<CharProbability> stats;
	for(auto ch : text){
		bool isExist = false;
		for(auto &charStat : stats)
			if(charStat.ch == ch){
				charStat.probability += 1. / length;
				isExist = true;
				break;
			}
		if(isExist == false)
			stats.emplace_back(ch, 1. / length);
	}
	return stats;
}


vector<wchar_t> mbVtowcV(const vector<char> &mbText){
	mblen(nullptr, 0);
	mbtowc(nullptr, nullptr, 0);//reset

	vector<wchar_t> wText;

	size_t pos = 0;
	while(pos < mbText.size()){
		int currentMultiByteCharLength = mblen(&mbText[pos], MB_CUR_MAX);
		if(currentMultiByteCharLength == -1)
			throw runtime_error("Not valid multi byte sequence fount at " + to_string(pos));
		if(currentMultiByteCharLength == 0)
			currentMultiByteCharLength = sizeof('\0');//костыль

		wchar_t t;

		int res = mbtowc(&t, &mbText[pos], currentMultiByteCharLength);
		if(res == -1)
			throw runtime_error("Not valid multi byte sequence fount at " + to_string(pos));

		pos += currentMultiByteCharLength;
		wText.push_back(t);
	}

	return wText;
}

vector<char> wcVtombV(const vector<wchar_t> &wcText){
	mblen(nullptr, 0);
	mbtowc(nullptr, nullptr, 0);//reset

	vector<char> mbText;

	char buffer[MB_CUR_MAX];
	for(auto wchar : wcText){
		int length = wctomb(buffer, wchar);
		if(length == -1)
			throw runtime_error("there is no character correspondence");

		for(int i = 0; i < length; ++i)
			mbText.push_back(buffer[i]);
	}

	return mbText;
}



string wc2string(const wchar_t wchar){
	mblen(nullptr, 0);
	mbtowc(nullptr, nullptr, 0);//reset

	char buffer[MB_CUR_MAX];
	int length = wctomb(buffer, wchar);
	if(length == -1)
		throw runtime_error("there is no character correspondence");

	string res;

	for(uint16_t i = 0; i < length; ++i)
		res.push_back(buffer[i]);

	return res;
}


uint32_t GCD(const vector<uint32_t> &src){
	return GCD(src.cbegin(), src.cend());
}


uint32_t GCD(const vector<uint32_t>::const_iterator beg, const vector<uint32_t>::const_iterator end){
	for(uint32_t currentDivider = *min_element(beg, end); currentDivider > 1; --currentDivider){
		bool isCurrentDividerCommon = true;
		for(auto it = beg; it != end; ++it)
			if(*it % currentDivider != 0){
				isCurrentDividerCommon = false;
				break;
			}

		if(isCurrentDividerCommon)
			return currentDivider;
	}
	return 1;
}

uint32_t GCD(const uint32_t n1, const uint32_t n2){
	for(uint32_t currentDivider = min(n1, n2); currentDivider > 1; --currentDivider)
		if((n1 % currentDivider == 0) && (n2 % currentDivider == 0))
			return currentDivider;

	return 1;
}


uint32_t mostProbablyGCD(const vector<uint32_t>::const_iterator beg, const vector<uint32_t>::const_iterator end){
	if(beg == end)
		throw runtime_error("Empty src");

	multiset<uint32_t> supposes;
	set<uint32_t> supposesList;

	for(auto outer = beg; outer != end - 1; ++outer)
		for(auto inner = outer + 1; inner != end; ++inner){
			uint32_t suppose = GCD(*outer, *inner);
			supposes.insert(suppose);
			supposesList.insert(suppose);
		}

	return *max_element(supposesList.cbegin(), supposesList.cend(), [&supposes](const uint32_t &rhs, const uint32_t &lhs){
		return supposes.count(rhs) < supposes.count(lhs);
	});
}


uint32_t mostProbablyGCD(const vector<uint32_t> &src){
	return mostProbablyGCD(src.cbegin(), src.cend());
}



vector<wchar_t> findCharsNear(const vector<CharProbability> &probs, double prob, double bound){
	if(probs.empty())
		throw runtime_error("'findCharsNear' : 'probs' is empty");

	vector<wchar_t> res;
	for(auto &cp : probs)
		if((cp.probability > prob - bound) && (cp.probability < prob + bound))
			res.push_back(cp.ch);

	if(res.empty()){//если в пределах границ ничего не найдено - ищем ближайший элемент
		double distance = abs(prob - probs.front().probability);
		wchar_t closest = probs.front().ch;
		for(auto it = probs.cbegin() + 1; it != probs.cend(); ++it){
			double currentDistance = abs(prob - it->probability);
			if(currentDistance < distance){
				distance = currentDistance;
				closest = it->ch;
			}
		}
		res.push_back(closest);
	}



	return res;
}






