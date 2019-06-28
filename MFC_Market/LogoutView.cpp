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


void LogoutView::OnBnClickedOk()//退出登陆
{
	/*
	char title[65] = "\0";
	GetWindowTextA(AfxGetMainWnd()->GetSafeHwnd(), LPSTR(title), 64);
	string strTitle = title;
	*/
	if (!((CMainFrame*)AfxGetMainWnd())->currentUser->ACCOUNT.Compare(TEXT("DEFAULTUSER")))
	{
		MessageBox(TEXT("请先登陆！"),TEXT("ERROR!"), MB_ICONEXCLAMATION);
		return;
	}
	//((CMainFrame*)AfxGetMainWnd())->currentUser->Edit(0, TEXT("DEFAULTUSER"), TEXT("0"), TEXT("guest"), "0");
	((CMainFrame*)AfxGetMainWnd())->currentUser->ACCOUNT = TEXT("DEFAULTUSER");
	((CMainFrame*)AfxGetMainWnd())->currentUser->GroupType = TEXT("guest");
	SetWindowTextA(AfxGetMainWnd()->GetSafeHwnd(), "未登陆 - MFC_Market_Management");
	MessageBox(TEXT("登出成功！"));
	::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), EDIT_LOGIN, EDIT_LOGIN, 0);
	// TODO: 在此添加控件通知处理程序代码
}


void LogoutView::OnBnClickedOk2()//修改密码
{
	/*
	char title[65] = "\0";
	GetWindowTextA(AfxGetMainWnd()->GetSafeHwnd(), LPSTR(title), 64);
	string strTitle = title;
	if (strTitle == "未登陆 - MFC_Market_Management" || strTitle == "未登陆")
	{
		MessageBox(TEXT("请先登陆！"), TEXT("ERROR!"), MB_ICONEXCLAMATION);
		return;
	}
	CString Username;
	Username = FindBetween(title, 65, '：', ' ');
	*/
	if (!((CMainFrame*)AfxGetMainWnd())->currentUser->ACCOUNT.Compare(TEXT("DEFAULTUSER")))
	{
		MessageBox(TEXT("请先登陆！"), TEXT("ERROR!"), MB_ICONEXCLAMATION);
		return;
	}
	CString Username = ((CMainFrame*)AfxGetMainWnd())->currentUser->ACCOUNT;

	CString passwd1, passwd2;
	GetDlgItemText(IDC_EDIT3, passwd1);
	GetDlgItemText(IDC_EDIT4, passwd2);
	if (passwd1.Compare(passwd2))
	{
		MessageBox(TEXT("两次密码输入不同！"), TEXT("ERROR!"), MB_ICONEXCLAMATION);
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
	MessageBox(TEXT("密码修改成功！"));
}
