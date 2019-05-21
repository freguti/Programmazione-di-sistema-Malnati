#pragma once
#include "Base.h"
class CFile :
	public CBase
{
private:
	CFile();
public:
	CFile(string name, uintmax_t size) {
		sName = name;
		uiSize = size;
	};
	~CFile();

public:
	uintmax_t getSize() const { return uiSize; };
	void ls(int indent = 0)const override;
	int mType() const override { return 2; }; //1-folder 2-file
private:
	uintmax_t uiSize;
};

