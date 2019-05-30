#include "pch.h"
#include <iostream>
#include "NetworkServer.h"
#include "SharedEditor.h"
int main()
{
	NetworkServer network;
	SharedEditor ed1(network);
	SharedEditor ed2(network);
	ed1.LocalInsert(0, 'c');
	ed1.LocalInsert(1, 'a');
	ed1.LocalInsert(2, 't'); //la insert alla fine va
	network.DispatchMessages();
	ed1.LocalInsert(1, 'h');

	return 0;
}
