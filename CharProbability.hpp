#ifndef CHARPROBABILITY_HPP_INCLUDED
#define CHARPROBABILITY_HPP_INCLUDED

struct CharProbability{
	wchar_t ch;
	double probability;

	CharProbability(){}
	CharProbability(wchar_t ch, double probability): ch(ch), probability(probability){}

	void show(ostream &o) const;

	bool operator<(const CharProbability &cp) const;
};

ostream &operator<<(ostream &o, const CharProbability &cp);
istream &operator>>(istream &i, CharProbability &cp);

#endif // CHARPROBABILITY_HPP_INCLUDED
