#pragma once
#include <afxext.h>
#include "Resource.h"
#include "Groups.h"
#include <string>

class UsersManageView : public CFormView
{
	friend class CMainFrame;

	DECLARE_DYNCREATE(UsersManageView)

protected:
	UsersManageView();
	virtual ~UsersManageView() {};

private:
	UsersList currentList;
	CComboBox* listBox = nullptr;
	list<ACCESS>::iterator currentUsers;

	void ReloadListBox();

public:
	enum { IDD = IDD_USERS_MANAGEMENT };
	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedAddButton();
	afx_msg void OnBnClickedDeleteButton();
	afx_msg void OnBnClickedChangeButton();
	afx_msg void OnBnClickedSaveButton();
	afx_msg void OnCbnSelchangeNewaccess();
	afx_msg void OnCbnSelchangeChangedAccess();
	virtual void OnInitialUpdate();
	//	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
};

