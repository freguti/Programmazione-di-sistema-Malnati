#include <iostream>

#pragma once

using namespace std;

class CBase
{
protected:
	CBase();
public:
	~CBase();
	string getName()const { return sName; };
	virtual int mType()const = 0;
	virtual void ls(int indent = 0)const = 0;
protected:
	string sName;
};

