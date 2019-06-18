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
	
	controlTree = &GetTreeCtrl();

	HICON icon = AfxGetApp()->LoadIconW(IDI_EDIT);	
	imageList->Create(30, 30, ILC_COLOR16, 1, 1);
	imageList->Add(icon);

	controlTree->InsertItem(TEXT("BUY"),0, 0, NULL);

	// TODO: 在此添加专用代码和/或调用基类
}
