#pragma once
#include <iostream>
#include <afx.h>
#include <list>

#define _GOODS_LIST_FILE "GoodsList.txt"

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
};

class GoodsList
{
	list<Goods> content;
	int length = 0;

public:
	void ReadFile();
	void WriteFile();
	void Sort(char*mode);
	int GetLength();

};

