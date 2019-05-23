#pragma once
#include "SharedEditor.h"
#include <vector>
#include <memory>

using namespace std;

class NetworkServer
{
public:
	NetworkServer();
	~NetworkServer();
protected:
	vector<unique_ptr<SharedEditor>> vClients;
public:
	int Connect(unique_ptr<SharedEditor> pClient);
	int Disconnect(unique_ptr<SharedEditor> pClient);
};

