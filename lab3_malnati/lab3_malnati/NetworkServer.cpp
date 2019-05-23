#include "pch.h"
#include "NetworkServer.h"


NetworkServer::NetworkServer()
{
}


NetworkServer::~NetworkServer()
{
}

int NetworkServer::Connect(unique_ptr<SharedEditor> pClient)
{
	for(auto tmp = vClients::iterator; )
}