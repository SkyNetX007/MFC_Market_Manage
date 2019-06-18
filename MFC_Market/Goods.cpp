#include "pch.h"
#include "Goods.h"
#pragma warning(disable:4996)

void GoodsList::ReadFile()
{
	FILE* file = fopen(_GOODS_LIST_FILE, "r+");
	Goods temp;
	char tempName[100] = "\0", tempID[30] = "\0", tempType[100] = "\0";
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
	while (!content.empty())
	{
		temp = content.front();
		tempsName = CStringA(temp.name), tempsID = CStringA(temp.ID), tempsType = CStringA(temp.type);
		fprintf(file, "\n%s %s %s", tempsName.c_str(), tempsID.c_str(), tempsType.c_str());
		fprintf(file, "\n%lf %lf %d", temp.price, temp.discount, temp.stock);
		content.pop_front();
		length--;
	}
	fclose(file);
}

void GoodsList::Sort(char*mode)
{
	
}

int GoodsList::GetLength()
{
	return length;
}
