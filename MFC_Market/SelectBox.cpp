// SelectBox.cpp: 实现文件
//

#include "pch.h"
#include "MFC_Market.h"
#include "SelectBox.h"
#include "MainFrm.h"

// SelectBox

IMPLEMENT_DYNCREATE(SelectBox, CTreeView)

SelectBox::SelectBox()
{
	
}

SelectBox::~SelectBox()
{
}

BEGIN_MESSAGE_MAP(SelectBox, CTreeView)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, &SelectBox::OnTvnSelchanged)
END_MESSAGE_MAP()


// SelectBox 诊断

#ifdef _DEBUG
void SelectBox::AssertValid() const
{
	CTreeView::AssertValid();
}

#ifndef _WIN32_WCE
void SelectBox::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif
#endif //_DEBUG


// SelectBox 消息处理程序


void SelectBox::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();

	imageList->Create(30, 30, ILC_COLOR32, 1, 7);
	HICON icon;
	for (int i = 0; i < 7; i++) {
		icon = AfxGetApp()->LoadIconW(IDI_APERTURE + i);
		imageList->Add(icon);
	}
	
	controlTree = &GetTreeCtrl();
	controlTree->SetImageList(imageList, TVSIL_NORMAL);

	controlTree->InsertItem(TEXT("LOGIN"), 3, 3, NULL);
	controlTree->InsertItem(TEXT("LOGOUT"), 4, 4, NULL);
	controlTree->InsertItem(TEXT("USERS_MANAGEMENT"), 1, 1, NULL);
	controlTree->InsertItem(TEXT("GOODS_MANAGEMENT"), 1, 1, NULL);
	controlTree->InsertItem(TEXT("PURCHASE"), 6, 6, NULL);
	controlTree->InsertItem(TEXT("RECEIPT_REFUND"), 5, 5, NULL);

	// TODO: 在此添加专用代码和/或调用基类
}


void SelectBox::OnTvnSelchanged(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	HTREEITEM nowSelected = controlTree->GetSelectedItem();
	CString title = controlTree->GetItemText(nowSelected);

	if (title == TEXT("LOGIN")) {
		::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), EDIT_LOGIN, EDIT_LOGIN, 0);
	}
	else if (title == TEXT("LOGOUT")) {
		::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), EDIT_LOGOUT, EDIT_LOGOUT, 0);
	}
	else if (title == TEXT("USERS_MANAGEMENT")) {
		::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), EDIT_USERS_MANAGEMENT, EDIT_USERS_MANAGEMENT, 0);
	}
	else if (title == TEXT("GOODS_MANAGEMENT")) {
		::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), EDIT_GOODS_MANAGEMENT, EDIT_GOODS_MANAGEMENT, 0);
	}
	else if (title == TEXT("PURCHASE")) {
		::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), EDIT_PURCHASE, EDIT_PURCHASE, 0);
	}
	else if (title == TEXT("RECEIPT_REFUND")) {
		::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), EDIT_RECEIPT_REFUND, EDIT_RECEIPT_REFUND, 0);
	}
}
