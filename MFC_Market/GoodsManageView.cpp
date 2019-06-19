#include "pch.h"
#include "GoodsManageView.h"

// GoodsManageView

using namespace std;

IMPLEMENT_DYNCREATE(GoodsManageView, CFormView)

GoodsManageView::GoodsManageView()
	: CFormView(GoodsManageView::IDD)
{

}
BEGIN_MESSAGE_MAP(GoodsManageView, CFormView)
ON_CBN_SELCHANGE(IDC_GOODSLIST, &GoodsManageView::OnCbnSelchangeGoodslist)
ON_BN_CLICKED(IDC_ADD_BUTTON, &GoodsManageView::OnBnClickedAddButton)
ON_BN_CLICKED(IDC_SAVE_BUTTON, &GoodsManageView::OnBnClickedSaveButton)
END_MESSAGE_MAP()


void GoodsManageView::OnCbnSelchangeGoodslist()
{
	
}


void GoodsManageView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView)
{
	currentList.ReadFile();
	CComboBox listBox(IDC_GOODSLIST);
	CFormView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}


void GoodsManageView::OnBnClickedAddButton()
{
	CString newName, newID, priceStr, stockStr;
	double newPrice;
	int newStock;
	GetDlgItemText(IDC_NEWNAME, newName);
	GetDlgItemText(IDC_NEWID, newID);
	GetDlgItemText(IDC_NEWPRICE, priceStr);
	GetDlgItemText(IDC_NEWQUANTITY, stockStr);
	if (newName.IsEmpty() || newID.IsEmpty() || priceStr.IsEmpty() || stockStr.IsEmpty())
		MessageBox(TEXT("Insufficient input!"));
	else {
		newPrice = _ttof(priceStr);
		newStock = _ttoi(stockStr);
		currentList.Add(newName, newID, newPrice, newStock);
		SetDlgItemText(IDC_NEWNAME, TEXT(""));
		SetDlgItemText(IDC_NEWID, TEXT(""));
		SetDlgItemText(IDC_NEWPRICE, TEXT(""));
		SetDlgItemText(IDC_NEWQUANTITY, TEXT(""));
	}
}


void GoodsManageView::OnBnClickedSaveButton()
{
	currentList.WriteFile();
}

