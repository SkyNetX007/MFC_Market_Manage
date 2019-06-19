#include "pch.h"
#include "Goods.h"
#pragma warning(disable:4996)

void Goods::Edit(CString _name, CString _ID, double _price, double _discount, int _stock, CString _type)
{
	name = _name, ID = _ID, type = _type;
	price = _price, discount = _discount, stock = _stock;
}

void GoodsList::ReadFile()
{
	FILE* file = fopen(_GOODS_LIST_FILE, "r+");
	Goods temp;
	char tempName[100] = "\0", tempID[30] = "\0", tempType[100] = "\0";
	if (!file) {
		return;
	}
	while (!feof(file))
	{
		fscanf(file, "%s%s%s%lf%lf%d", tempName, tempID,tempType, &temp.price, &temp.discount, &temp.stock);
		temp.name = tempName;
		temp.ID = tempID;
		temp.type = tempType;
		content.push_back(temp);
		length++;
	}
	fclose(file);
}

void GoodsList::WriteFile() 
{
	FILE* file = fopen(_GOODS_LIST_FILE, "w+");
	string tempsName, tempsID, tempsType;
	Goods temp;
	
	if (!file)
		return ;
	int tempLength = length;
	for (list<Goods>::iterator it = content.begin(); tempLength>0; it++) 
	{
		tempsName = CStringA(it->name), tempsID = CStringA(it->ID), tempsType = CStringA(it->type);
		fprintf(file, "\n%s %s %s", tempsName.c_str(), tempsID.c_str(), tempsType.c_str());
		fprintf(file, "\n%lf %lf %d", it->price, it->discount, it->stock);
		tempLength--;
	}

	fclose(file);
}



void GoodsList::Sort(char*mode)
{
	
}

void GoodsList::Add(CString& name, CString& ID, double& price, int& stock, CString type)
{
	Goods newGoods;
	newGoods.Edit(name, ID, price, 0.0, stock, type);
	content.push_back(newGoods);
	length++;
}

int GoodsList::GetLength()
{
	return length;
}


