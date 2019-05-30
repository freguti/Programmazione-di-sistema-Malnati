#include "pch.h"
#include "SharedEditor.h"
#include <iostream>

SharedEditor::SharedEditor(NetworkServer& server) : _server(const_cast <NetworkServer&>(server))
{
	//shared_ptr<SharedEditor> tmp(this);
	//sThis = tmp;
	_siteid = server.Connect(this);
}


SharedEditor::~SharedEditor() = default;


//vector<unsigned char> SharedEditor::GetFractional(int index) //ANDAVANO BENE MA ERANO LIMITATE DAL NUMERO DI CIFRE
//{
//	for (auto tmp = _symbols.begin(); tmp < _symbols.end(); tmp++)
//	{
//		if (tmp->uindex == index)
//		{
//			return tmp->fIndex;
//		}
//	}
//	return { 0 };
//}
//
//float SharedEditor::TranslateFractional(vector<unsigned char> index)
//{
//	float val = 0;
//	int pos = 0;
//	bool bAfter = false;
//	for (int i = 0; i < index.size(); i++)
//	{
//		if (index[i] == ',')
//		{
//			pos = i;
//			bAfter = true;
//			continue;
//		}
//		if (bAfter == false)
//		{
//			val *= 10;
//			val += index[i] - '0';
//		}
//		else
//		{
//			val += (float)((index[i] - '0') / (i - pos));
//		}
//	}
//	return val;
//}

void SharedEditor::Process(const Message &M)
{
	float f1, f2;
	if (M.action == eTypeWrite)
	{
		int count = 0;
		for (auto tmp = _symbols.begin(); tmp < _symbols.end(); tmp++)
		{
			memcpy(&f2, tmp->fIndex.data(), sizeof(f2));
			memcpy(&f1, M.symbol.fIndex.data(), sizeof(f2));
			if (f2 < f1)
			{
				count++;
			}
		}
		auto tmp_s = _symbols.begin();
		_symbols.insert(tmp_s + count, M.symbol);
	}
	else if (M.action == eTypeDelete)
	{
		for (auto tmp = _symbols.begin(); tmp < _symbols.end(); tmp++)
		{
			if (tmp->uindex == M.symbol.uindex)
			{
				_symbols.erase(tmp);
			}
		}
	}
	else
		cout << "errore\n";
}

void SharedEditor::LocalInsert(int index, char value)
{
	Symbol tmp;
	float fractional,f2;
	bool bfound = true;
	tmp.symbol = value;
	int count = 0;
	vector<Symbol>::iterator tmp2;
	vector<char>::iterator iter;
	for (tmp2 = _symbols.begin(); tmp2 < _symbols.end(); tmp2++)
	{
		count++;
	}



	if (index >= count) //inserisco alla fine
	{
		index = count; //se inserisco un indice alto lo cappa
		//inserisco in index
		
		/*iter = tmp.fIndex.begin();
		tmp.fIndex.insert(iter, '0'); //trasformo l'intero in carattere
		iter = tmp.fIndex.begin();
		tmp.fIndex.insert(iter, ',');
		//controlli per numeri a piu cifre
		//PARTE INTERA

		iter = tmp.fIndex.begin();
		tmp.fIndex.insert(iter, index + '0');*/
		float findex = (float)index;
		tmp.fIndex.resize(sizeof(findex));
		
		memcpy(tmp.fIndex.data(),&findex, sizeof(findex));
	}
	else
	{
		//fractional = (float)(TranslateFractional(_symbols[index].fIndex) + TranslateFractional(_symbols[index - 1].fIndex)) / 2; //mi piazzo in mezzo ai 2 fract
		memcpy(&fractional, _symbols[index].fIndex.data(), sizeof(fractional)); // converte vector in float (lo riscrive). i byte rimangono quelli, quindi per i calcoli è giusto
		memcpy(&f2, _symbols[index-1].fIndex.data(), sizeof(f2));
		fractional = (fractional + f2) / 2;
		tmp.fIndex.resize(sizeof(fractional));
		memcpy(tmp.fIndex.data(), &fractional, sizeof(fractional)); //converte float in vector (lo salva)
	}
	//assegno id univoco
	while (bfound)
	{
		tmp.uindex = rand() * 1000;
		bfound = Check_code(tmp.uindex);
	}
	tmp2 = _symbols.begin();
	_symbols.insert(tmp2 + index, tmp);
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