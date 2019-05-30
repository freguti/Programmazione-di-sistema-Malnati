#include "pch.h"
#include "NetworkServer.h"

NetworkServer::NetworkServer()
{
}


NetworkServer::~NetworkServer()
{ 
	//shared_ptr<SharedEditor> Tmp;
	//for (auto tmp = vEditor.begin(); tmp < vEditor.end(); tmp++)
	//{
	//	Tmp = *tmp;
	//	this->Disconnect(Tmp);
	//}
}

int NetworkServer::Connect(SharedEditor* pEditor)
{
	int unique_code = rand() * 10000;
	int i = 0;
	while (Check_code(unique_code) != false)
	{
		unique_code = rand() * 10000;
		if (i++ >= 1000)
			return -1;
	}
	vEditor.insert(vEditor.end(), pEditor);
	return unique_code;
}

void NetworkServer::Disconnect(SharedEditor* pEditor)
{
	SharedEditor* editor;
	for (auto tmp = vEditor.begin(); tmp < vEditor.end(); tmp++)
	{
		editor = *tmp;
		if (editor->GetSiteid() == pEditor->GetSiteid())
		{
			vEditor.erase(tmp);
			return;
		}
	}
}

bool NetworkServer::Check_code(int unique_code)
{
	SharedEditor* editor;
	for (auto tmp = vEditor.begin(); tmp < vEditor.end(); tmp++)
	{
		editor = *tmp;
		if (editor->GetSiteid() == unique_code)
		{
			return true;
		}
	}
	return false;
}

void NetworkServer::Send(const Message& M)
{
	vMessage.insert(vMessage.end(), M);
}

void NetworkServer::DispatchMessages()
{
	for (auto tmp = vMessage.begin(); tmp < vMessage.end(); tmp = vMessage.begin())//non metto l'incremento
	{
		for (auto tmp2 = vEditor.begin(); tmp2 < vEditor.end(); tmp2++)
		{
			SharedEditor* Stmp = *tmp2;
			if (tmp->siteid != Stmp->GetSiteid()) //lo invio a tutti quelli diversi dal mittente
			{
				Stmp->Process(*tmp);
			}
		}
		vMessage.erase(tmp);
	}
}