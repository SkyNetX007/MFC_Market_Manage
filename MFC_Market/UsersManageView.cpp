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
	ON_CBN_SELCHANGE(IDC_USERSLIST, &UsersManageView::OnCbnSelchangeUserslist)
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
	CString newAccount, newComment, newGroupType, newUID;
	string newPsd;
	int int_newUID = _ttoi(newUID);
	SetDlgItemText(IDC_CHANGED_UID, NULL);
	SetDlgItemText(IDC_CHANGED_ACCOUNT, NULL);
	SetDlgItemText(IDC_CHANGED_COMMENT, NULL);
	SetDlgItemText(IDC_CHANGED_PSD, NULL);
	if (newAccount.IsEmpty() || newComment.IsEmpty() || newGroupType.IsEmpty() || newUID.IsEmpty())
		MessageBox(TEXT("Insufficient input!"));
	else {
		list<ACCESS>::iterator it = currentList.FindUID(newUID);
		if (it != currentList.getEnd()) {
			MessageBox(TEXT("UID already exists!"));
			SetDlgItemText(IDC_NEWUID, NULL);
			return;
		}
		currentList.Add(int_newUID, newAccount, newComment, newGroupType, newPsd);
		ReloadListBox();
		SetDlgItemText(IDC_CHANGED_UID, NULL);
		SetDlgItemText(IDC_CHANGED_ACCOUNT, NULL);
		SetDlgItemText(IDC_CHANGED_COMMENT, NULL);
		SetDlgItemText(IDC_CHANGED_PSD, NULL);
	}
}


void UsersManageView::OnBnClickedDeleteButton()
{
	currentList.Delete(currentUsers);
	currentUsers = currentList.getFirstUser();
	ReloadListBox();
}


void UsersManageView::OnBnClickedChangeButton()
{
	CString cstrAccount, cstrComment, cstrGroupType, cstrUID, cstrPsd;
	string newPsd = CStringA(cstrPsd);
	int int_newUID = _ttoi(cstrUID);
	GetDlgItemText(IDC_CHANGED_UID, cstrUID);
	GetDlgItemText(IDC_CHANGED_ACCOUNT, cstrAccount);
	GetDlgItemText(IDC_CHANGED_COMMENT, cstrComment);
	GetDlgItemText(IDC_CHANGED_PSD, cstrPsd);
	if (cstrAccount.IsEmpty() || cstrComment.IsEmpty() || cstrGroupType.IsEmpty() || cstrUID.IsEmpty())
		MessageBox(TEXT("Insufficient input!"));
	else {
		list<ACCESS>::iterator it = currentList.FindUID(cstrUID);
		if (it != currentList.getEnd() && it->ACCOUNT != currentUsers->ACCOUNT) {
			MessageBox(TEXT("UID already exists!"));
			SetDlgItemText(IDC_NEWUID, NULL);
			return;
		}

		string buf = "..\\etc\\md5.exe " + newPsd;
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

		bool checkChangePsd = 1;
		if (cstrPsd.Compare(TEXT("******")))
		{
			checkChangePsd = 0;
		}
		currentUsers->Edit(int_newUID, cstrAccount, cstrComment, cstrGroupType, checkChangePsd, md5_cache);
		ReloadListBox();
	}
}


void UsersManageView::OnBnClickedSaveButton()
{
	currentList.WriteFile();
}


void UsersManageView::OnCbnSelchangeNewaccess()
{
	// TODO: 在此添加控件通知处理程序代码
}


void UsersManageView::OnCbnSelchangeChangedAccess()
{
	// TODO: 在此添加控件通知处理程序代码
}

void UsersManageView::OnCbnSelchangeUserslist()
{
	listBox = (CComboBox*)GetDlgItem(IDC_USERSLIST);
	int num = listBox->GetCurSel();
	CString sUsers;
	listBox->GetLBText(num, sUsers);
	currentUsers = currentList.Find(sUsers);

	if (sUsers) {
		CString cstrUID;
		cstrUID.Format(TEXT("%d"), currentUsers->UID);
		SetDlgItemText(IDC_CHANGED_ACCOUNT, currentUsers->ACCOUNT);
		SetDlgItemText(IDC_CHANGED_UID, cstrUID);
		SetDlgItemText(IDC_CHANGED_COMMENT, currentUsers->COMMENT);
		SetDlgItemText(IDC_CHANGED_PSD,TEXT("******"));
	}
}

void UsersManageView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	currentList.ReadFile();
	listBox = (CComboBox*)GetDlgItem(IDC_USERSLIST);

	ReloadListBox();
}
