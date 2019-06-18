#include"pch.h"
#include "Groups.h"
using namespace std;

#pragma warning(disable:4996)

int ACCESS::DisplayUserList()
{

	return 0;
}

int ACCESS::UserAdd()
{

	return 0;
}

int ACCESS::UserDel()
{

	return 0;
}

int ACCESS::UserMod()
{

	return 0;
}

int AccountSave()
{
	FILE* AccountFile = fopen("./etc/passwd", "w+");

	return 0;
}

int PasswdSave()
{
	FILE* PasswdFile = fopen("./etc/shadow", "w+");

	return 0;
}
