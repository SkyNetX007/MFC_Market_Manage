#pragma once
#include <iostream>
#include <afx.h>
#include <list>

#define _GOODS_LIST_FILE "../etc/GoodsList.txt"

using namespace std;

class Goods
{
	friend class GoodsList;

	CString name = TEXT("\0");
	CString ID = TEXT("\0");
	CString type = TEXT("\0");
	double price = 0;
	double discount = 0;
	int stock = 0;

	void Edit(CString _name, CString _ID, double _price, double _discount, int _stock, CString _type = TEXT("0"));
};

class GoodsList
{
	list<Goods> content;
	int length = 0;

public:
	void ReadFile();
	void WriteFile();

	void Sort(char*mode);
	void Add(CString& name, CString& ID, double& price, int& stock, CString type = TEXT("0"));
	int GetLength();

};

