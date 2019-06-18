// SelectBox.cpp: 实现文件
//

#include "pch.h"
#include "MFC_Market.h"
#include "SelectBox.h"


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
	controlTree->InsertItem(TEXT("EDIT_GOODS"), 1, 1, NULL);
	controlTree->InsertItem(TEXT("BUY"), 6, 6, NULL);

	// TODO: 在此添加专用代码和/或调用基类
}


void SelectBox::OnTvnSelchanged(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	HTREEITEM nowSelected = controlTree->GetSelectedItem();
}
