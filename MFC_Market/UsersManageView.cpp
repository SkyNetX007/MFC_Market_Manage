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

	listBox = (CComboBox*)GetDlgItem(IDC_NEWACCESS);
	listBox->ResetContent();
	listBox->AddString(TEXT("guest"));
	listBox->AddString(TEXT("user"));
	listBox->AddString(TEXT("admin"));

	listBox = (CComboBox*)GetDlgItem(IDC_CHANGED_ACCESS);
	listBox->ResetContent();
	listBox->AddString(TEXT("guest"));
	listBox->AddString(TEXT("user"));
	listBox->AddString(TEXT("admin"));
}

void UsersManageView::OnBnClickedAddButton()
{
	CString newAccount, newComment, newGroupType, newUID, newPsd;

	GetDlgItemText(IDC_NEWUID, newUID);
	GetDlgItemText(IDC_NEWACCOUNT, newAccount);
	GetDlgItemText(IDC_NEWCOMMENT, newComment);
	GetDlgItemText(IDC_NEWACCESS, newGroupType);
	GetDlgItemText(IDC_NEWPSD, newPsd);
	string STRnewPsd = CStringA(newPsd);
	int int_newUID = _ttoi(newUID);

	if (newAccount.IsEmpty() || !cstrIsalnum(newAccount) || newComment.IsEmpty() || newGroupType.IsEmpty() || newUID.IsEmpty() || !(!newGroupType.Compare(TEXT("admin")) || !newGroupType.Compare(TEXT("user")) || !newGroupType.Compare(TEXT("guest"))))
		MessageBox(TEXT("Insufficient input!"));
	else {
		list<ACCESS>::iterator it = currentList.FindUID(newUID);
		if (it != currentList.getEnd()) {
			MessageBox(TEXT("UID already exists!"));
			SetDlgItemText(IDC_NEWUID, NULL);
			return;
		}

		string buf = "..\\etc\\md5.exe " + STRnewPsd;
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

		currentList.Add(int_newUID, newAccount, newComment, newGroupType, md5_cache);
		ReloadListBox();
		SetDlgItemText(IDC_NEWUID, NULL);
		SetDlgItemText(IDC_NEWACCOUNT, NULL);
		SetDlgItemText(IDC_NEWCOMMENT, NULL);
		SetDlgItemText(IDC_NEWPSD, NULL);
		SetDlgItemText(IDC_NEWACCESS, NULL);
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

	GetDlgItemText(IDC_CHANGED_UID, cstrUID);
	GetDlgItemText(IDC_CHANGED_ACCOUNT, cstrAccount);
	GetDlgItemText(IDC_CHANGED_COMMENT, cstrComment);
	GetDlgItemText(IDC_CHANGED_ACCESS, cstrGroupType);
	GetDlgItemText(IDC_CHANGED_PSD, cstrPsd);
	string newPsd = CStringA(cstrPsd);
	int int_newUID = _ttoi(cstrUID);

	if (cstrAccount.IsEmpty() || !cstrIsalnum(cstrAccount) || cstrComment.IsEmpty() || cstrGroupType.IsEmpty() || cstrUID.IsEmpty() || !(!cstrGroupType.Compare(TEXT("admin")) || !cstrGroupType.Compare(TEXT("user")) || !cstrGroupType.Compare(TEXT("guest"))))
		MessageBox(TEXT("Insufficient input!"));
	else {
		list<ACCESS>::iterator it = currentList.FindUID(cstrUID);
		if (it != currentList.getEnd() && it->ACCOUNT != currentUsers->ACCOUNT) {
			MessageBox(TEXT("UID already exists!"));
			SetDlgItemText(IDC_CHANGED_UID, NULL);
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
	
}


void UsersManageView::OnCbnSelchangeChangedAccess()
{
	
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
		SetDlgItemText(IDC_CHANGED_ACCESS, currentUsers->GroupType);
	}
}

void UsersManageView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	if (((CMainFrame*)AfxGetMainWnd())->currentUser->GroupType != TEXT("admin"))
	{
		MessageBox(TEXT("Permission denied!"));
		::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), EDIT_LOGIN, EDIT_LOGIN, 0);
	}
	currentList.ReadFile();
	listBox = (CComboBox*)GetDlgItem(IDC_USERSLIST);

	ReloadListBox();
}
