#pragma once
#include <iostream>
#include <afx.h>
#include <list>

#define _GOODS_LIST_FILE "../etc/GoodsList.txt"

using namespace std;

class Goods
{
	friend class GoodsList;

public:
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

	list<Goods>::iterator getFirstGoods() { return content.begin(); }
	list<Goods>::iterator getLastGoods() { return --content.end(); }
	list<Goods>::iterator Find(CString _name);
	void Delete(list<Goods>::iterator item);
	void Add(CString& name, CString& ID, double& price, int& stock, CString type = TEXT("0"));
	int GetLength();
	
};

