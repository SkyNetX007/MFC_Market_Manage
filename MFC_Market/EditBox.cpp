// EditBox.cpp: 实现文件
//

#include "pch.h"
#include "MFC_Market.h"
#include "EditBox.h"


// EditBox

IMPLEMENT_DYNCREATE(EditBox, CScrollView)

EditBox::EditBox()
{

}

EditBox::~EditBox()
{
}


BEGIN_MESSAGE_MAP(EditBox, CScrollView)
END_MESSAGE_MAP()


// EditBox 绘图

void EditBox::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO:  计算此视图的合计大小
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}

void EditBox::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO:  在此添加绘制代码
}


// EditBox 诊断

#ifdef _DEBUG
void EditBox::AssertValid() const
{
	CScrollView::AssertValid();
}

#ifndef _WIN32_WCE
void EditBox::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}
#endif
#endif //_DEBUG


// EditBox 消息处理程序
