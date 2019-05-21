#include "pch.h"
#include "File.h"
#include <iostream>     
#include <iomanip>      
#include <string>  

using namespace std;

CFile::CFile()
{
}


CFile::~CFile()
{
}

void CFile::ls(int indent)const
{
	//indent++;
	for (int i = 0; i < indent; i++)
		cout << ' ';
	//setfill(' ') << setw(indent + this->getName().length()) <<
	cout << this->getName()<< ' ' <<this->getSize() << '\n';
}