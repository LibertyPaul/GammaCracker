#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include <sstream>
#include <cstring>
#include <ostream>
#include <algorithm>
#include <set>
#include <cstdlib>
#include <memory>

#include <random>
#include <chrono>


using namespace std;
#include "CharProbability.hpp"
#include "stuff.hpp"
#include "GammaCracker.hpp"


void man(const string &progName){
	cout << "Usage: " << progName << " srcFileName languageStatsFileName" << endl;
}


int main(int argc, const char **argv){
	setlocale (LC_ALL, "");//подорожник

	const string progName(argv[0]);
	if(argc < 3){
		man(progName);
		return 0;
	}

	string fName(argv[1]);
	string langStatsFileName(argv[2]);


	ifstream srcFile(fName, ios_base::in | ios_base::binary);
	ifstream langStatsFile(langStatsFileName, ios_base::in | ios_base::binary);

	if(!srcFile || !langStatsFile)
		throw runtime_error("File openning error");

	langStatsFile.seekg(0, langStatsFile.end);
	size_t langStatFileSize = langStatsFile.tellg();
	langStatsFile.seekg(0, langStatsFile.beg);

	if(langStatFileSize % sizeof(CharProbability) != 0)
		throw runtime_error("Language statistics file is broken");


	vector<CharProbability> langStat(langStatFileSize / sizeof(CharProbability));
	langStatsFile.read(reinterpret_cast<char *>(&langStat[0]), langStatFileSize);



	srcFile.seekg(0, srcFile.end);
	size_t fSize = srcFile.tellg();
	srcFile.seekg(0, srcFile.beg);

	if(fSize % sizeof(wchar_t) != 0)
		throw runtime_error("File is broken");


	vector<wchar_t> encText(fSize / sizeof(wchar_t));
	srcFile.read(reinterpret_cast<char *>(&encText[0]), fSize);
	srcFile.close();





	GammaCracker gc(encText);
	vector<wchar_t> predictedGamma = gc.crack(langStat);

	cout << "Полученный ключ в десятичном представлении:" << endl;
	for(auto wchar : predictedGamma)
		cout << wchar << endl;

	cout << "Пробую конвертировать ключ в UTF-8..." << endl;

	string key;
	try{
		for(auto wchar : predictedGamma)
			key += wc2string(wchar);
	}catch(runtime_error &re){
		cout << "Конвертация не удалась. " << re.what() << endl;
		return 0;
	}

	cout << "Конвертация удалась. Ключ: " << key << endl;


}
