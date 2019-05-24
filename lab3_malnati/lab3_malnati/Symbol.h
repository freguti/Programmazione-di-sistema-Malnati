#pragma once
#include <vector>

using namespace std;

class Symbol
{
public:
	Symbol();
	~Symbol();
	char symbol;
	vector<char> fIndex;
	int index;
};

