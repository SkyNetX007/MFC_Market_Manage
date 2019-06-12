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
