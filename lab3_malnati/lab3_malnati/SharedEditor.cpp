#include "pch.h"
#include "SharedEditor.h"
#include <iostream>

SharedEditor::SharedEditor(NetworkServer& server) : _server(const_cast <NetworkServer&>(server))
{
	shared_ptr<SharedEditor> tmp(this);
	sThis = tmp;
	_siteid = server.Connect(sThis);
}


SharedEditor::~SharedEditor()
{
}

vector<char> SharedEditor::GetFractional(int index)
{
	for (auto tmp = _symbols.begin(); tmp < _symbols.end(); tmp++)
	{
		if (tmp->uindex == index)
		{
			return tmp->fIndex;
		}
	}
	return { -1 };
}

float SharedEditor::TranslateFractional(vector<char> index)
{
	float val = 0;
	int pos = 0;
	bool bAfter = false;
	for (int i = 0; i < index.size(); i++)
	{
		if (index[i] == ',')
		{
			pos = i;
			bAfter = true;
			continue;
		}
		if (bAfter == false)
		{
			val *= 10;
			val += index[i] - '0';
		}
		else
		{
			val += (float)((index[i] - '0') / (i - pos));
		}
	}
	return val;
}

void SharedEditor::Process(const Message &M)
{
	switch (M.action)
	{
	case 1: //add
		break;
	case 2: //delete
		break;
	default:
		cout << "errore\n";
	}
}

void SharedEditor::LocalInsert(int index, char value)
{
	if (_symbols[index].uindex == 0)
	{
		//non esiste l'elemento
		_symbols[index].uindex = _symbols[index].uindex;
		//NetworkServer::Check_code(_symbols[index].uindex);
	}
	else
	{

	}
}