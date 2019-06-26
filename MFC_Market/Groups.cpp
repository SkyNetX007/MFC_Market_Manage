#include "pch.h"
#include "Groups.h"

#pragma warning(disable:4996)

ACCESS::ACCESS(int _UID, CString _ACCOUNT, CString _COMMENT, CString _GroupType, string _PASSWORD_MD5)
{
	UID = _UID;
	ACCOUNT = _ACCOUNT;
	COMMENT = _COMMENT;
	GroupType = _GroupType;
	PASSWORD_MD5 = _PASSWORD_MD5;
}

void ACCESS::Edit(int _UID, CString _ACCOUNT, CString _COMMENT, CString _GroupType, bool DoChangePassword, string _PASSWORD_MD5)
{
	UID = _UID;
	ACCOUNT = _ACCOUNT;
	COMMENT = _COMMENT;
	GroupType = _GroupType;
	if (DoChangePassword)
	{
		PASSWORD_MD5 = _PASSWORD_MD5;
	}
}

void UsersList::ReadFile()
{
	FILE* file = fopen(_ACCOUNT_LIST_FILE, "r+");
	ACCESS temp;
	char tmpUsername[33] = "\0", tmpCMT[100] = "\0", tmpGroupType[9] = "guest", tmpPsd[33] = "\0";
	if (!file) {
		return;
	}
	while (!feof(file))
	{
		fscanf(file, "%d%s%s%s%s", &temp.UID, tmpUsername, tmpCMT, tmpGroupType, tmpPsd);
		temp.ACCOUNT = tmpUsername;
		temp.COMMENT = tmpCMT;
		temp.GroupType = tmpGroupType;
		temp.PASSWORD_MD5 = tmpPsd;
		content.push_back(temp);
		length++;
	}
	fclose(file);
}

void UsersList::WriteFile()
{
	FILE* file = fopen(_ACCOUNT_LIST_FILE, "w+");
	string tmpUsername, tmpCMT, tmpGroupType;

	if (!file)
		return;
	int tempLength = length;
	for (list<ACCESS>::iterator it = content.begin(); tempLength > 0; it++)
	{
		tmpUsername = CStringA(it->ACCOUNT), tmpCMT = CStringA(it->COMMENT), tmpGroupType = CStringA(it->GroupType);
		fprintf(file, "%d %s %s %s %s\n", it->UID, tmpUsername.c_str(), tmpCMT.c_str(), tmpGroupType.c_str(), it->PASSWORD_MD5.c_str());
		tempLength--;
	}
	fclose(file);
}

void UsersList::Sort(CString mode)
{
}

void UsersList::Delete(list<ACCESS>::iterator _Account)
{
	content.erase(_Account);
	length--;
}

void UsersList::Add(int _UID, CString _ACCOUNT, CString _COMMENT, CString _GroupType, string _PASSWORD_MD5)
{
	ACCESS newACCOUNT;
	bool DoChangePassword = 1;
	newACCOUNT.Edit(_UID, _ACCOUNT, _COMMENT, _GroupType, DoChangePassword, _PASSWORD_MD5);
	content.push_back(newACCOUNT);
	length++;
}

int UsersList::GetLength()
{
	return length;
}

list<ACCESS>::iterator UsersList::Find(CString _Username)
{
	list<ACCESS>::iterator it = content.begin();
	int tempLength = length;
	while (1)
	{
		if (tempLength == 0)
			return content.end();
		if (it->ACCOUNT == _Username)
			return it;
		it++, tempLength--;
	}
}

list<ACCESS>::iterator UsersList::FindUID(CString _UID)
{
	list<ACCESS>::iterator it = content.begin();
	int tempLength = length;
	while (1)
	{
		if (tempLength == 0)
			return content.end();
		if (it->UID == _UID)
			return it;
		it++, tempLength--;
	}
}

bool cstrIsalnum(CString str)
{
	for (int i = 0; i < str.GetLength(); i++)
	{
		if (!((str[i] > '0' && str[i] < '9') || (str[i] > 'a' && str[i] < 'z') || (str[i] > 'A' && str[i] < 'Z') || (str[i] == '_')))
			return FALSE;
	}
	return TRUE;
}