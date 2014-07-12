#include <ostream>
#include <istream>
#include <cstring>
#include <stdexcept>


using namespace std;
#include "CharProbability.hpp"

void CharProbability::show(ostream &o) const{
	char mbbuffer[MB_CUR_MAX];
	wctomb(nullptr, 0);//reset
	size_t mbLength = wctomb(mbbuffer, ch);
	if(mbLength == (size_t) -1)
		throw runtime_error("Unconvertable wide character");

	o << "'";
	for(uint16_t i = 0; i < mbLength; ++i)
		o << mbbuffer[i];
	o << "' :   \t" << probability;

	o << endl;
}


bool CharProbability::operator<(const CharProbability &cp) const{
	return this->probability < cp.probability;
}

ostream &operator<<(ostream &o, const CharProbability &cp){
	o.write(reinterpret_cast<const char *>(&cp), sizeof(cp));
	return o;
}


istream &operator>>(istream &i, CharProbability &cp){
	i.read(reinterpret_cast<char *>(&cp), sizeof(cp));
	return i;
}
