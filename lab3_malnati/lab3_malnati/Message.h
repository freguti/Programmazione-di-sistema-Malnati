#ifndef MESSAGE
#define MESSAGE
#include "Symbol.h"
class Message
{
public:
	Message();
	~Message();
	int siteid;
	Symbol symbol;
	int action; //1->add 2->delete
};
#endif
