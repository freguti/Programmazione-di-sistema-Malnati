#include "pch.h"
#include <iostream>
#include <memory>
#include <string>
#include "Directory.h"
#include "File.h"

using namespace std;

shared_ptr<CDirectory> CDirectory::root = 0;
int main()
{
	//funzionano le funzioni get e add, manca da implementare solo delete e ls
	shared_ptr<CDirectory> root = CDirectory::getRoot();
	auto alfa = root->addDirectory("alfa");
	alfa->addDirectory("beta")->addFile("beta1", 100);
	alfa->getDir("beta")->addFile("beta2", 200); //la get ha un problema
	alfa->getDir("beta")->addDirectory("beta3");
	alfa->addDirectory("gamma");
	alfa->getDir("beta")->getDir("beta3")->addFile("beta4", 1);
	alfa->getDir("..")->ls(); //ls va ma non indenta
	alfa->remove("beta");
	root->ls();
	return 0;
}

