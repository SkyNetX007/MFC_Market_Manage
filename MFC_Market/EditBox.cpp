#include "pch.h"
#include "MainFrm.h"
#include "EditBox.h"
#include "resource.h"

IMPLEMENT_DYNCREATE(EditBox, CFormView)

EditBox::EditBox()
	: CFormView(EditBox::IDD)
{

}



void EditBox::AssertValid() const
{
	CFormView::AssertValid();

	// TODO: 在此添加专用代码和/或调用基类
}


void EditBox::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);

	// TODO: 在此添加专用代码和/或调用基类
}
BEGIN_MESSAGE_MAP(EditBox, CFormView)
	ON_BN_CLICKED(IDOK, &EditBox::OnBnClickedOk)
END_MESSAGE_MAP()

void EditBox::OnBnClickedOk()
{
	CString inUsername, inPasswd;
	GetDlgItemText(IDC_EDIT1, inUsername);
	GetDlgItemText(IDC_EDIT2, inPasswd);
	MessageBox(inUsername + inPasswd);
}
