#include "pch.h"
#include "LoginView.h"
//#include "md5.h"

// LoginView

using namespace std;

IMPLEMENT_DYNCREATE(LoginView, CFormView)

int CheckPsd(CString inUsername, CString inPasswd, ACCESS cache_User)
{
	string Username = CStringA(inUsername);
	string Password = CStringA(inPasswd);
	string buf = "..\\etc\\md5.exe " + Password;
	//char tmp[] = buf;
	/*
	PROCESS_INFORMATION pi;
	STARTUPINFO si;
	memset(&si, 0, sizeof(si));
	si.cb = sizeof(si);
	si.wShowWindow = SW_SHOW;
	si.dwFlags = STARTF_USESHOWWINDOW;
	CreateProcess(LPCWSTR(buf.c_str()), NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, NULL, &si, &pi);
	*/
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
	if (cache_User.PASSWORD_MD5==md5_cache)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


LoginView::LoginView()
	: CFormView(LoginView::IDD)
{

}
BEGIN_MESSAGE_MAP(LoginView, CFormView)
ON_BN_CLICKED(IDOK, &LoginView::OnBnClickedOk)
END_MESSAGE_MAP()


void LoginView::OnBnClickedOk()
{
	CString inUsername = TEXT("\0"), inPasswd = TEXT("\0"), CpsdMD5;
	//string psdMD5;
	GetDlgItemText(IDC_EDIT1, inUsername);
	GetDlgItemText(IDC_EDIT2, inPasswd);
	if (inUsername.IsEmpty())
	{
		MessageBox(TEXT("Please input valid username!"),TEXT("ERROR!"), MB_ICONEXCLAMATION);
		return;
	}

	//CMD5Crypt MD5Encryption;
	//MD5Encryption.GetMd5String(CpsdMD5, inPasswd);
	//psdMD5 = CStringA(CpsdMD5);
	//psdMD5 = CStringA(inPasswd);

	UsersList currentList;
	currentList.ReadFile();
	list<ACCESS>::iterator it = currentList.Find(inUsername);
	if (it == currentList.getEnd())
	{
		MessageBox(TEXT("User does not exist!"), TEXT("Warning"), MB_ICONEXCLAMATION);
		return;
	}
	else
	{
		ACCESS cache_User = *it;
		if (!CheckPsd(inUsername, inPasswd, cache_User))
		{
			MessageBox(TEXT("密码错误！"), TEXT("Warning"), MB_ICONEXCLAMATION);
			return;
		}
		
		*currentUser = *it;
		string title = "已登陆用户：" + CStringA(currentUser->ACCOUNT) + " [" + CStringA(currentUser->GroupType) + "]";
		SetDlgItemText(IDC_EDIT1, TEXT(""));
		SetDlgItemText(IDC_EDIT2, TEXT(""));
		SetWindowTextA(AfxGetMainWnd()->GetSafeHwnd(), title.c_str());
		CString Msg=TEXT("用户 ");
		Msg.Append(currentUser->ACCOUNT);
		Msg.Append(TEXT(" 登陆成功！"));
		MessageBox(Msg,TEXT("Sign In"));
	}
}
