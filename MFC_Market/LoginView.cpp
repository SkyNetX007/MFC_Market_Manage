#include "pch.h"
#include "LoginView.h"
#include "md5.h"
#include <string>
#include "Groups.h"

// LoginView

using namespace std;

IMPLEMENT_DYNCREATE(LoginView, CFormView)

ACCESS CurrentUser(0, TEXT("DEFAULTUSER"), TEXT("\0"), TEXT("guest"), NULL);

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
	if (inUsername.Compare(TEXT("\0")) == 0)
	{
		return;
	}
	CMD5Crypt MD5Encryption;
	MD5Encryption.GetMd5String(CpsdMD5, inPasswd);
	psdMD5 = CStringA(CpsdMD5);

	UsersList Userslist;
	Userslist.ReadFile();
	if (Userslist.Find(inUsername)->PASSWORD_MD5 == psdMD5)
	{
		CurrentUser.Edit(Userslist.Find(inUsername)->UID, Userslist.Find(inUsername)->ACCOUNT, Userslist.Find(inUsername)->COMMENT, Userslist.Find(inUsername)->GroupType, Userslist.Find(inUsername)->PASSWORD_MD5);
	}
	else
	{
		return;
	}
}
