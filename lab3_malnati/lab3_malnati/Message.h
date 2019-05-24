#pragma once
#include "Symbol.h"
class Message
{
public:
	Message();
	~Message();
	int siteid;
	Symbol symbol;
	int action; //0-add 1-delete
};

