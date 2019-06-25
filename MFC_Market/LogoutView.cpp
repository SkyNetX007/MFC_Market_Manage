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
	char title[65] = "\0";
	GetWindowTextA(AfxGetMainWnd()->GetSafeHwnd(), LPSTR(title), 64);
	string strTitle = title;
	if (strTitle == "未登陆 - MFC_Market_Management" || strTitle == "未登陆")
	{
		MessageBox(TEXT("请先登陆！"),TEXT("ERROR!"), MB_ICONEXCLAMATION);
		return;
	}
	SetWindowTextA(AfxGetMainWnd()->GetSafeHwnd(), "未登陆");
	MessageBox(TEXT("登出成功！"));
	// TODO: 在此添加控件通知处理程序代码
}


void LogoutView::OnBnClickedOk2()//修改密码
{
	char title[65] = "\0";
	GetWindowTextA(AfxGetMainWnd()->GetSafeHwnd(), LPSTR(title), 64);
	string strTitle = title;
	if (strTitle == "未登陆 - MFC_Market_Management" || strTitle == "未登陆")
	{
		MessageBox(TEXT("请先登陆！"), TEXT("ERROR!"), MB_ICONEXCLAMATION);
		return;
	}
	CString Username;/*
	Username = CStringA(strTitle.c_str());
	int begin = Username.Find(TEXT("："));
	int end = Username.Find(TEXT(" ["));
	Username = Username.Mid(begin+1, end);*/
	string tmp=strTitle.substr(strTitle.find("：")+2, strTitle.find("["));
	
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
	SetDlgItemText(IDC_EDIT3, TEXT(""));
	SetDlgItemText(IDC_EDIT4, TEXT(""));
	MessageBox(TEXT("密码修改成功！"));
}
