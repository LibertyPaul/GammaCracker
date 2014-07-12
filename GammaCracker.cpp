#include <vector>
#include <fstream>
#include <cstdint>
#include <iostream>
#include <algorithm>
#include <set>



using namespace std;
#include "CharProbability.hpp"
#include "stuff.hpp"
#include "GammaCracker.hpp"

GammaCracker::GammaCracker(const vector<wchar_t> &encryptedText): encryptedText(encryptedText){
	cout << "Initialising GammaCracker class instance with parameters:" << endl;
	cout << "minCollisionLength = " << minCollisionLength << endl;
	cout << "collisionMarginsMaxCount = " << collisionMarginsMaxCount << endl;

}



uint32_t GammaCracker::calcGammaLength(){
	vector<pair<uint32_t, uint32_t>> collisionMargins;
	for(auto currentPos = encryptedText.cbegin(); currentPos != encryptedText.cend(); ++currentPos){
		//ищем совпадения по первому символу последовательности
		for(auto it = currentPos + 1; it < encryptedText.cend(); ++it){
			if(*currentPos == *it){//найдено совпадение 1го символа, считаем длинну совпадения
				auto first = currentPos + 1, second = it + 1;
				uint32_t count = 1;
				while(first != encryptedText.cend() && second != encryptedText.cend() && *first == *second){
					++count;
					++first;
					++second;
				}

				if(count >= minCollisionLength)
					collisionMargins.push_back(pair<uint32_t, uint32_t>(it - currentPos, count));
			}
		}
	}

	if(collisionMargins.empty())
		throw logic_error("Не найдено совпадающих фрагментов");


	if(collisionMargins.size() > collisionMarginsMaxCount){
		sort(collisionMargins.rbegin(), collisionMargins.rend(), [](const pair<uint32_t, uint32_t> &rhs, const pair<uint32_t, uint32_t> &lhs){
			return rhs > lhs;
		});
		collisionMargins.resize(collisionMarginsMaxCount);
	}


	vector<uint32_t> margins;
	for(auto &margin : collisionMargins)
		margins.push_back(margin.first);
	//uint32_t gcd = GCD(collisionMargins);
	uint32_t gcd = mostProbablyGCD(margins);

	return gcd;
}



vector<wchar_t> GammaCracker::crack(vector<CharProbability> langStat){
	sort(langStat.begin(), langStat.end());


	uint32_t gammaLength;
	try{
		gammaLength = calcGammaLength();
	}catch(logic_error &le){
		throw logic_error(string("Не удалось найти длинну гаммы: ") + le.what());
	}

	vector<wchar_t> key(gammaLength);

	for(uint32_t i = 0; i < gammaLength; ++i){
		multiset<wchar_t> charSet;
		set<wchar_t> alphabet;
		for(auto it = encryptedText.begin() + i; it < encryptedText.end(); it += gammaLength){
			charSet.insert(*it);
			alphabet.insert(*it);
		}

		vector<CharProbability> encryptedTextStat;
		for(auto wchar : alphabet){
			double prob = static_cast<double>(charSet.count(wchar)) / encryptedText.size();
			CharProbability cp(wchar, prob);
			encryptedTextStat.push_back(cp);
		}


		multiset<wchar_t> candidates;
		set<wchar_t> candidatesList;

		for(auto &charStat : encryptedTextStat){
			for(auto &symbol : langStat){
				wchar_t charCandidate = symbol.ch ^ charStat.ch;
				candidates.insert(charCandidate);
				candidatesList.insert(charCandidate);
			}
		}

		wchar_t keyChar = *max_element(candidatesList.begin(), candidatesList.end(), [&candidates](const wchar_t &rhs, const wchar_t &lhs){
			return candidates.count(rhs) < candidates.count(lhs);
		});

		key.at(i) = keyChar;
	}


	return key;
}
