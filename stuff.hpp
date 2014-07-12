#ifndef STUFF_HPP_INCLUDED
#define STUFF_HPP_INCLUDED

vector<CharProbability> getProbabilities(const vector<wchar_t> &text);

vector<wchar_t> mbVtowcV(const vector<char> &mbText);
vector<char> wcVtombV(const vector<wchar_t> &wcText);

string wc2string(const wchar_t wchar);

uint32_t GCD(const vector<uint32_t>::const_iterator beg, const vector<uint32_t>::const_iterator end);
uint32_t GCD(const vector<uint32_t> &src);

uint32_t GCD(const uint32_t n1, const uint32_t n2);
uint32_t mostProbablyGCD(const vector<uint32_t>::const_iterator beg, const vector<uint32_t>::const_iterator end);
uint32_t mostProbablyGCD(const vector<uint32_t> &src);

vector<wchar_t> findCharsNear(const vector<CharProbability> &probs, double prob, double bound);


#endif // STUFF_HPP_INCLUDED
