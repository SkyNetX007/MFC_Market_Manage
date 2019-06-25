#include "pch.h"
#include "UsersManageView.h"

// UsersManageView

using namespace std;

IMPLEMENT_DYNCREATE(UsersManageView, CFormView)

UsersManageView::UsersManageView()
	: CFormView(UsersManageView::IDD)
{

}
BEGIN_MESSAGE_MAP(UsersManageView, CFormView)
	ON_BN_CLICKED(IDC_ADD_BUTTON, &UsersManageView::OnBnClickedAddButton)
	ON_BN_CLICKED(IDC_DELETE_BUTTON, &UsersManageView::OnBnClickedDeleteButton)
	ON_BN_CLICKED(IDC_CHANGE_BUTTON, &UsersManageView::OnBnClickedChangeButton)
	ON_BN_CLICKED(IDC_SAVE_BUTTON, &UsersManageView::OnBnClickedSaveButton)
	ON_CBN_SELCHANGE(IDC_NEWACCESS, &UsersManageView::OnCbnSelchangeNewaccess)
	ON_CBN_SELCHANGE(IDC_CHANGED_ACCESS, &UsersManageView::OnCbnSelchangeChangedAccess)
END_MESSAGE_MAP()

void UsersManageView::ReloadListBox()
{
	listBox = (CComboBox*)GetDlgItem(IDC_USERSLIST);
	listBox->ResetContent();
	int tempLength = currentList.GetLength();
	list<ACCESS>::iterator it = currentList.getFirstUser();
	for (; tempLength > 0; it++, tempLength--) {
		listBox->AddString(it->ACCOUNT);
	}
	SetDlgItemText(IDC_CHANGED_UID, NULL);
	SetDlgItemText(IDC_CHANGED_ACCOUNT, NULL);
	SetDlgItemText(IDC_CHANGED_COMMENT, NULL);
	SetDlgItemText(IDC_CHANGED_PSD, NULL);
}

void UsersManageView::OnBnClickedAddButton()
{
	// TODO: 在此添加控件通知处理程序代码
}


void UsersManageView::OnBnClickedDeleteButton()
{
	// TODO: 在此添加控件通知处理程序代码
}


void UsersManageView::OnBnClickedChangeButton()
{
	// TODO: 在此添加控件通知处理程序代码
}


void UsersManageView::OnBnClickedSaveButton()
{
	// TODO: 在此添加控件通知处理程序代码
}


void UsersManageView::OnCbnSelchangeNewaccess()
{
	// TODO: 在此添加控件通知处理程序代码
}


void UsersManageView::OnCbnSelchangeChangedAccess()
{
	// TODO: 在此添加控件通知处理程序代码
}

void UsersManageView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	currentList.ReadFile();
	listBox = (CComboBox*)GetDlgItem(IDC_USERSLIST);

	ReloadListBox();
}