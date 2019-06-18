#include "pch.h"
#include "LoginView.h"
#include "LoginView.h"

// LoginView

using namespace std;

IMPLEMENT_DYNCREATE(LoginView, CFormView)

LoginView::LoginView()
	: CFormView(LoginView::IDD)
{

}BEGIN_MESSAGE_MAP(LoginView, CFormView)
ON_BN_CLICKED(IDOK, &LoginView::OnBnClickedOk)
END_MESSAGE_MAP()


void LoginView::OnBnClickedOk()
{
	CString inUsername, inPasswd;
	GetDlgItemText(IDC_EDIT1, inUsername);
	GetDlgItemText(IDC_EDIT2, inPasswd);

	
}
