#include "pch.h"
#include "LoginView.h"
#include "md5.h"
#include <string>

// LoginView

using namespace std;

IMPLEMENT_DYNCREATE(LoginView, CFormView)


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
	string psdMD5;
	GetDlgItemText(IDC_EDIT1, inUsername);
	GetDlgItemText(IDC_EDIT2, inPasswd);
	if (inUsername.IsEmpty())
	{
		MessageBox(TEXT("Please insert username"),_T("Warning"));
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
		MessageBox(TEXT("User does not exist!"));
		return;
	}
	
}
