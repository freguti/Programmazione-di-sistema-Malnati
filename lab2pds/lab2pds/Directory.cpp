#include "pch.h"
#include "Directory.h"
#include <string>
#include <iomanip>  

using namespace std;

CDirectory::CDirectory(weak_ptr<CDirectory> spFather,string nome)
{
	sName = nome;
	wpFather = spFather;
}


CDirectory::~CDirectory()
{
}

shared_ptr<CBase> CDirectory::get(string sNome)
{
	shared_ptr<CBase> spbTmp, spbElement = 0;
	if (sNome == ".")
	{
		spbElement = dynamic_pointer_cast<CBase>(this->wpItself.lock()); //lock crea uno shared da un weak

	}
	else if (sNome == "..") 
	{
		spbElement = dynamic_pointer_cast<CBase>(this->wpFather.lock());
	}
	else
	{
		for (auto tmp = this->lspBase.begin(); tmp != this->lspBase.end(); tmp++)
		{
			spbTmp = *tmp;
			if (spbTmp->getName() == sNome)
			{
				spbElement = spbTmp;
				break;
			}
		}
	}
	return spbElement;
}

shared_ptr<CDirectory> CDirectory::getDir(string sNome)
{
	shared_ptr<CDirectory> spdTmp = dynamic_pointer_cast<CDirectory>(this->get(sNome));
	return spdTmp;
}

shared_ptr<CFile> CDirectory::getFile(string sNome)
{
	weak_ptr<CBase> spbTmp = this->get(sNome);
	shared_ptr<CFile>  spfTmp = dynamic_pointer_cast<CFile>(spbTmp.lock());
	return spfTmp;
}

void CDirectory::ls(int indent) const
{
	shared_ptr<CBase> spbTmp;
	shared_ptr<CFile>  file;
	shared_ptr<CDirectory>  directory;
	if (this->getName() == "root")
		cout << "[+] \\\n";
	else
	{
		for (int i = 0; i < indent; i++)
			cout << ' ';
		//setfill(' ') << setw(indent + this->getName().length()) <<
		cout << "[+]" << this->getName() << '\n'; //PRIMA STAMPO IL NOME DELLA CARTELLA
	}
	indent+=5;
	//ESEGUO UN CICLO SULLA LISTA E CHIAMO L'LS PER OGNUNO DI LORO
	for (auto tmp = this->lspBase.begin(); tmp != this->lspBase.end(); tmp++)
	{
		spbTmp = *tmp;
		if (spbTmp->mType() == 1) //Directory
		{
			//casto a CDirectory
			directory = dynamic_pointer_cast<CDirectory>(spbTmp);
			directory->ls(indent);
		}
		else if (spbTmp->mType() == 2) //File
		{
			file = dynamic_pointer_cast<CFile>(spbTmp);
			file->ls(indent);
		}
	}
	return;
}


void CDirectory::remove()
{
	shared_ptr<CBase> spbTmp;
		while( !this->lspBase.empty())
		{
			auto tmp = this->lspBase.begin();
			spbTmp = *tmp;
			if (spbTmp->mType() == 1) //Directory
			{
				//directory: chiamo la delete della mia directory e alla fine mi elimino
				shared_ptr<CDirectory>  spfTmp = dynamic_pointer_cast<CDirectory>(spbTmp);
				spfTmp->remove();
				spfTmp.reset();
				spbTmp.reset();
				this->lspBase.erase(tmp);
			}
			else if (spbTmp->mType() == 2) //File
			{
				//file: condizione di terminazione
				spbTmp.reset();
				this->lspBase.erase(tmp);
			}
		}
	return;
}


void CDirectory::remove(string sNome)
{
	shared_ptr<CBase> spbTmp;
	for (auto tmp = this->lspBase.begin(); tmp != this->lspBase.end(); tmp++)
	{
		spbTmp = *tmp;
		if (spbTmp->mType() == 1 && spbTmp->getName() == sNome) //Directory
		{
			//directory: chiamo la delete della mia directory e alla fine mi elimino
			shared_ptr<CDirectory>  spfTmp = dynamic_pointer_cast<CDirectory>(spbTmp);
			spfTmp->remove();
			spfTmp.reset();
			spbTmp.reset();
			this->lspBase.erase(tmp);
			break;
		}
		else if (spbTmp->mType() == 2 && spbTmp->getName() == sName) //File
		{
			//file: condizione di terminazione
			spbTmp.reset();
			this->lspBase.erase(tmp);
			break;
		}
	}
	return;
}

shared_ptr<CFile> CDirectory::addFile(string sNome, uintmax_t uiSize)
{
	bool bfound = false;
	shared_ptr<CBase> spfTmp;
	shared_ptr<CFile> file;
	for (auto tmp = this->lspBase.begin(); tmp != this->lspBase.end(); tmp++)
	{
		spfTmp = *tmp;
		if (spfTmp->getName() == sNome)
		{
			bfound = true;
		}
	}
	if (!bfound)
	{
		file = shared_ptr<CFile>(new CFile(sNome, uiSize));
		auto tmp = this->lspBase.begin();
		this->lspBase.insert(tmp, file);
	}
	else
	{
		file = 0;
		cout << "esiste già un oggetto con quel nome\n";
	}
	return file;
}

shared_ptr<CDirectory> CDirectory::addDirectory(string sNome) 
{
	bool bfound = false;
	shared_ptr<CBase> spdTmp;
	shared_ptr<CDirectory> spdDirectory;
	//shared_ptr<CDirectory> wpthis(this);

	for (auto tmp = this->lspBase.begin(); tmp != this->lspBase.end(); tmp++)
	{
		spdTmp = *tmp;
		if (spdTmp->getName() == sNome)
		{
			bfound = true;
		}
	}
	if (!bfound)
	{
		//list<shared_ptr<CBase>>::iterator tmp2;
		auto tmp = this->lspBase.begin();
		spdDirectory = shared_ptr<CDirectory>(new CDirectory(this->wpItself,sNome));
		spdDirectory->wpItself = spdDirectory;
		this->lspBase.insert(tmp, spdDirectory);
		return spdDirectory;
	}
	else
	{
		spdDirectory = 0;
		cout << "esiste già un oggetto con quel nome\n";
	}
	return spdDirectory;
}