#ifndef SYMBOL
#define SYMBOL
#include <vector>

using namespace std;

class Symbol
{
public:
	Symbol() { uindex = 0; };
	~Symbol();
	char symbol;
	vector<unsigned char> fIndex;
	int uindex; //indice univoco
};
#endif
