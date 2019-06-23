#pragma once
#include <iostream>
#include <afx.h>
#include <list>

#define _ACCOUNT_LIST_FILE "../etc/passwd"

using namespace std;

class ACCESS
{
	friend class UsersList;

public:
	int UID = 0;
	CString ACCOUNT = TEXT("DEFAULTUSER");
	CString COMMENT = TEXT("\0");
	CString GroupType = TEXT("guest");
	string PASSWORD_MD5 = 0;

	ACCESS(int _UID, CString _ACCOUNT, CString _COMMENT, CString _GroupType = TEXT("guest"), string _PASSWORD_MD5 = 0);
	ACCESS() { }
	void Edit(int _UID, CString _ACCOUNT, CString _COMMENT, CString _GroupType = TEXT("guest"), string _PASSWORD_MD5 = 0);
};

class UsersList
{
	list<ACCESS> content;
	int length = 0;

public:
	void ReadFile();
	void WriteFile();

	list<ACCESS>::iterator getFirstUser() { return content.begin(); }
	list<ACCESS>::iterator getLastUser() { return --content.end(); }
	list<ACCESS>::iterator Find(CString _Username);
	void Sort(CString mode);
	void Delete(list<ACCESS>::iterator _Account);
	void Add(int _UID, CString _ACCOUNT, CString _COMMENT, CString _GroupType = TEXT("guest"), string _PASSWORD_MD5 = 0);
	int GetLength();
};