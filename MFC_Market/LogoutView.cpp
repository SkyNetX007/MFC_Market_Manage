#include "pch.h"
#include "LogoutView.h"

// LogoutView

using namespace std;

IMPLEMENT_DYNCREATE(LogoutView, CFormView)

LogoutView::LogoutView()
	: CFormView(LogoutView::IDD)
{

}BEGIN_MESSAGE_MAP(LogoutView, CFormView)
ON_BN_CLICKED(IDOK, &LogoutView::OnBnClickedOk)
ON_BN_CLICKED(IDOK2, &LogoutView::OnBnClickedOk2)
END_MESSAGE_MAP()


void LogoutView::OnBnClickedOk()//退出登陆
{
	// TODO: 在此添加控件通知处理程序代码
}


void LogoutView::OnBnClickedOk2()//修改密码
{
	CString passwd1, passwd2;
	GetDlgItemText(IDC_EDIT3, passwd1);
	GetDlgItemText(IDC_EDIT4, passwd2);

}
