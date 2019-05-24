#include "pch.h"
#include "NetworkServer.h"


NetworkServer::NetworkServer()
{
}


NetworkServer::~NetworkServer()
{
}

int NetworkServer::Connect(weak_ptr<SharedEditor> pEditor)
{
	int unique_code = rand() * 10000;
	int i = 0;
	while (Check_code(unique_code) != false)
	{
		unique_code = rand() * 10000;
		if (i++ >= 1000)
			return -1;
	}
	vEditor.insert(vEditor.end(), pEditor.lock());
	return unique_code;
}

void NetworkServer::Disconnect(weak_ptr<SharedEditor> pEditor)
{
	shared_ptr<SharedEditor> editor;
	for (auto tmp = vEditor.begin(); tmp < vEditor.end(); tmp++)
	{
		editor = *tmp;
		if (editor->GetSiteid() == pEditor.lock()->GetSiteid())
		{
			editor.reset();
			vEditor.erase(tmp);
			break;
		}
	}
}

bool NetworkServer::Check_code(int unique_code)
{
	shared_ptr<SharedEditor> editor;
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