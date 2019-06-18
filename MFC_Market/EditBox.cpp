// EditBox.cpp: 实现文件
//

#include "pch.h"
#include "MFC_Market.h"
#include "EditBox.h"


// EditBox

//IMPLEMENT_DYNCREATE(EditBox, CFormView)

EditBox::~EditBox()
{
}


BEGIN_MESSAGE_MAP(EditBox, CFormView)
END_MESSAGE_MAP()


// EditBox 绘图

void EditBox::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

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
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void EditBox::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// EditBox 消息处理程序
