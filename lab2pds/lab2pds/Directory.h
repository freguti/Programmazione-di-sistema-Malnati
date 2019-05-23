#pragma once
#include "Base.h"
#include "File.h"
#include <list>
#include <iostream>
#include <memory>

using namespace std;

class CDirectory: public CBase 
{
protected:
	static shared_ptr<CDirectory> root;
	CDirectory() { sName = "root"; };
	CDirectory(weak_ptr<CDirectory> spFather, string nome);
public:
	~CDirectory();

private:
	list<shared_ptr<CBase>> lspBase;
	weak_ptr<CDirectory> wpFather; //da fare nel costr
	weak_ptr<CDirectory> wpItself; //da fare nel costr

public:
	static shared_ptr<CDirectory>getRoot()
	{
		if (root == 0)
		{
			root = shared_ptr<CDirectory>(new CDirectory());
			root->wpItself = root;
			
		}
		return root;
	}
	shared_ptr<CDirectory> addDirectory(string sNome);
	shared_ptr<CFile> addFile(string sNome, uintmax_t uiSize);
	shared_ptr<CBase> get(string sNome);
	shared_ptr<CDirectory> getDir(string sNome);
	shared_ptr<CFile> getFile(std::string sNome);
	void remove(string sNome);
	void remove();
	void ls(int indent = 0) const override;
	int mType() const override { return 1; }; //1-folder 2-file
};

