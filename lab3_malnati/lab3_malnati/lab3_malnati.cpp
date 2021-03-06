#include "pch.h"
#include <iostream>
#include "NetworkServer.h"
#include "SharedEditor.h"
#include <string>
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
	ed2.LocalErase(1);
	network.DispatchMessages();
	cout << "ed1: " << ed1.ToString() <<'\n';
	cout << "ed2: " << ed2.ToString() <<'\n';
	return 0;
}
