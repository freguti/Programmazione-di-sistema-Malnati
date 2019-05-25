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
	case eTypeWrite:
		break;
	case eTypeDelete:
		break;
	default:
		cout << "errore\n";
	}
}

void SharedEditor::LocalInsert(int index, char value)
{
	Symbol tmp;
	float fractional;
	bool bfound = true;
	tmp.symbol = value;
	if (_symbols[index].uindex == 0)
	{
		//non esiste l'elemento
		tmp.fIndex[0] = index + '0'; //trasformo l'intero in carattere
		tmp.fIndex[1] = ',';
	}
	else
	{
		//esiste l'elemento
		if (_symbols[index - 1].uindex != 0)
		{
			//se esiste il precedente mi metto in mezzo ai 2
			fractional = (float)(TranslateFractional(_symbols[index].fIndex) + TranslateFractional(_symbols[index - 1].fIndex)) / 2; //mi piazzo in mezzo ai 2 fract
			
		}
		else
		{
			//se non esiste l'elemento prima mi piazzo comuque come se ci fosse (tanto io divento il nuovo index, lasciando index-1 vuoto)
			fractional = (float)(TranslateFractional(_symbols[index].fIndex) + (float)(index-1) )/ 2; 
		}
		memcpy(tmp.fIndex.data(), &fractional, sizeof(fractional)); //in teoria converte fractional to vetor
	}

	//assegno id univoco
	while (bfound)
	{
		tmp.uindex = rand() * 1000;
		bfound = Check_code(tmp.uindex);
	}

	//inserisco in index
	auto tmps = _symbols.begin();
	_symbols.insert(tmps + index,tmp);
	Message M;
	M.siteid = this->GetSiteid();
	M.action = eTypeWrite;
	M.symbol = tmp;
	_server.Send(M);
}

bool SharedEditor::Check_code(int unique_code)
{
	Symbol symb;
	for (auto tmp = _symbols.begin(); tmp < _symbols.end(); tmp++)
	{
		symb = *tmp;
		if (symb.uindex == unique_code)
		{
			return true;
		}
	}
	return false;
}