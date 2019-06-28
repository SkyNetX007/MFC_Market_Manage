#include "pch.h"
#include "LogoutView.h"

// LogoutView

using namespace std;

IMPLEMENT_DYNCREATE(LogoutView, CFormView)
/*
char* FindBetween(char* input, int length, char start, char end)
{
	char* result = new char[length], current = 0;
	int resultLength = 0;
	bool read = 0;
	for (int i = 0; i < length; i++)
	{
		current = input[i];
		if (current == end || current == 0)
			break;
		if (read)
		{
			result[resultLength] = current;
			resultLength++;
		}
		if (current == start)
			read = 1;
	}
	result[resultLength] = 0;
	return result;
}
*/

LogoutView::LogoutView()
	: CFormView(LogoutView::IDD)
{

}BEGIN_MESSAGE_MAP(LogoutView, CFormView)
ON_BN_CLICKED(IDOK, &LogoutView::OnBnClickedOk)
ON_BN_CLICKED(IDOK2, &LogoutView::OnBnClickedOk2)
END_MESSAGE_MAP()


void LogoutView::OnBnClickedOk()//�˳���½
{
	/*
	char title[65] = "\0";
	GetWindowTextA(AfxGetMainWnd()->GetSafeHwnd(), LPSTR(title), 64);
	string strTitle = title;
	*/
	if (!((CMainFrame*)AfxGetMainWnd())->currentUser->ACCOUNT.Compare(TEXT("DEFAULTUSER")))
	{
		MessageBox(TEXT("���ȵ�½��"),TEXT("ERROR!"), MB_ICONEXCLAMATION);
		return;
	}
	//((CMainFrame*)AfxGetMainWnd())->currentUser->Edit(0, TEXT("DEFAULTUSER"), TEXT("0"), TEXT("guest"), "0");
	((CMainFrame*)AfxGetMainWnd())->currentUser->ACCOUNT = TEXT("DEFAULTUSER");
	((CMainFrame*)AfxGetMainWnd())->currentUser->GroupType = TEXT("guest");
	SetWindowTextA(AfxGetMainWnd()->GetSafeHwnd(), "δ��½ - MFC_Market_Management");
	MessageBox(TEXT("�ǳ��ɹ���"));
	::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), EDIT_LOGIN, EDIT_LOGIN, 0);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void LogoutView::OnBnClickedOk2()//�޸�����
{
	/*
	char title[65] = "\0";
	GetWindowTextA(AfxGetMainWnd()->GetSafeHwnd(), LPSTR(title), 64);
	string strTitle = title;
	if (strTitle == "δ��½ - MFC_Market_Management" || strTitle == "δ��½")
	{
		MessageBox(TEXT("���ȵ�½��"), TEXT("ERROR!"), MB_ICONEXCLAMATION);
		return;
	}
	CString Username;
	Username = FindBetween(title, 65, '��', ' ');
	*/
	if (!((CMainFrame*)AfxGetMainWnd())->currentUser->ACCOUNT.Compare(TEXT("DEFAULTUSER")))
	{
		MessageBox(TEXT("���ȵ�½��"), TEXT("ERROR!"), MB_ICONEXCLAMATION);
		return;
	}
	CString Username = ((CMainFrame*)AfxGetMainWnd())->currentUser->ACCOUNT;

	CString passwd1, passwd2;
	GetDlgItemText(IDC_EDIT3, passwd1);
	GetDlgItemText(IDC_EDIT4, passwd2);
	if (passwd1.Compare(passwd2))
	{
		MessageBox(TEXT("�����������벻ͬ��"), TEXT("ERROR!"), MB_ICONEXCLAMATION);
		return;
	}
	UsersList currentList;
	currentList.ReadFile();
	list<ACCESS>::iterator it = currentList.Find(Username);
	string Password = CStringA(passwd1);
	string buf = "..\\etc\\md5.exe " + Password;
	system(buf.c_str());
	fstream cache("..\\MFC_Market\\cache");
	if (!cache.is_open())
	{
		//exit(1);
	}
	char tmp[33] = "\0";
	cache >> tmp;
	cache.close();
	DeleteFile(TEXT("..\\MFC_Market\\cache"));

	string md5_cache = tmp;
	it->PASSWORD_MD5 = md5_cache;
	currentList.WriteFile();

	SetDlgItemText(IDC_EDIT3, TEXT(""));
	SetDlgItemText(IDC_EDIT4, TEXT(""));
	MessageBox(TEXT("�����޸ĳɹ���"));
}
