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
	vector<unique_ptr<SharedEditor>> vServers;

};

