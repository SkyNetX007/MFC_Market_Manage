#include "md5.cpp"
#include "Groups.h"

int Login(FILE* userList, ACCESS* currentUser, string Username, string psd)
{
	if (userList == NULL) {
		FILE* initList = fopen("/etc/shadow", "w+");
		fprintf(initList, "root:admin\n");
		fclose(initList);
		return -1;
	}

	string tmpUser;
	string tmpPsd;
	//cout << "Username: ";
	currentUser->ACCOUNT = Username;
	bool UserExist = 0;
	while (!feof(userList)) {
		fscanf(userList, "%s:", tmpUser);
		fscanf(userList, "%s\n", tmpPsd);
		if (currentUser->ACCOUNT.compare(tmpUser) == 0)
		{
			UserExist = 1;
			break;
		}
	}
	if (!UserExist)
	{
		// << "Invalid Username!" << endl;
		system("pause");
		return 0;
	}
	//cout << "Password: ";
	//psd = GetPasswd();
	if (encrypt(psd).compare(tmpPsd) == 0)
	{
		return 1;
	}
	else
	{
		//cout << "Invalid Password!" << endl;
		//system("pause");
		return 0;
	}
}

ACCESS* Authentication(string Username, string psd)
{
	LinkList* userList = new LinkList;
	ACCESS* currentUser = new ACCESS;

	FILE* Passwd = fopen("/etc/passwd", "r");
	if (Passwd == NULL) {
		FILE* initList = fopen("/etc/passwd", "w+");
		fprintf(initList, "root:x:0:admin\n");
		fclose(initList);
		return 0;
	}
	else {
		ACCESS* tempUser = new ACCESS;
		int listlength = 0;
		while (!feof(Passwd)) {
			fscanf(Passwd, "%s:", tempUser->ACCOUNT);
			fscanf(Passwd, "x:%s:", tempUser->UID);
			fscanf(Passwd, "%s:", tempUser->COMMENT);
			userList->Insert(tempUser, listlength);
			listlength++;
		}
	}
	fclose(Passwd);

	if (Login(fopen("/etc/shadow", "r"), currentUser, Username, psd) == 1)
	{
		Node* temp = userList->head;
		while (temp->next) {
			if (temp->val->ACCOUNT.compare(currentUser->ACCOUNT) == 0)
			{
				currentUser = temp->val;
				break;
			}
			else
			{
				temp = temp->next;
			}
		}
		return currentUser;
	}
	else
	{
		//cout << "Forced Logout";
		//exit(0);
		return nullptr;
	}
}