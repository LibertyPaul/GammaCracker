#ifndef TEXTSTATISTICS_HPP_INCLUDED
#define TEXTSTATISTICS_HPP_INCLUDED

class TextStatistics{
	vector<char16_t> text;


public:
	TextStatistics(const vector<char16_t> &text);

	vector<CharProbability> getProbabilities();
};

#endif // TEXTSTATISTICS_HPP_INCLUDED
