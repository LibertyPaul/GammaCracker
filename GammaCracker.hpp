#ifndef GAMMACRACKER_HPP_INCLUDED
#define GAMMACRACKER_HPP_INCLUDED





class GammaCracker{
	const uint16_t minCollisionLength = 3;
	const uint32_t collisionMarginsMaxCount = 50;

	vector<wchar_t> encryptedText;

public:
	GammaCracker(const vector<wchar_t> &encryptedText);
	uint32_t calcGammaLength();
	vector<wchar_t> crack(vector<CharProbability> langStat);

};

#endif // GAMMACRACKER_HPP_INCLUDED
