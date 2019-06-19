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
ON_BN_CLICKED(IDC_DELETE_BUTTON, &GoodsManageView::OnBnClickedDeleteButton)
ON_BN_CLICKED(IDC_CHANGE_BUTTON, &GoodsManageView::OnBnClickedChangeButton)
END_MESSAGE_MAP()


void GoodsManageView::ReloadListBox()
{
	listBox = (CComboBox*)GetDlgItem(IDC_GOODSLIST);
	listBox->ResetContent();
	int tempLength = currentList.GetLength();
	list<Goods>::iterator it = currentList.getFirstGoods();
	for (; tempLength > 0; it++, tempLength--) {
		listBox->AddString(it->name);
	}
	SetDlgItemText(IDC_CHANGED_NAME, TEXT(""));
	SetDlgItemText(IDC_CHANGED_ID, TEXT(""));
	SetDlgItemText(IDC_CHANGED_PRICE, TEXT(""));
	SetDlgItemText(IDC_CHANGED_DISCOUNT, TEXT(""));
	SetDlgItemText(IDC_CHANGED_QUANTITY, TEXT(""));
}

void GoodsManageView::OnCbnSelchangeGoodslist()
{
	listBox = (CComboBox*)GetDlgItem(IDC_GOODSLIST);
	int num = listBox->GetCurSel();
	CString sGoods;
	listBox->GetLBText(num, sGoods);
	currentGoods = currentList.Find(sGoods);

	if (sGoods) {
		CString priceStr, discountStr, stockStr;
		priceStr.Format(TEXT("%lf"), currentGoods->price);
		discountStr.Format(TEXT("%lf"), currentGoods->discount);
		stockStr.Format(TEXT("%d"), currentGoods->stock);
		SetDlgItemText(IDC_CHANGED_NAME, currentGoods->name);
		SetDlgItemText(IDC_CHANGED_ID, currentGoods->ID);
		SetDlgItemText(IDC_CHANGED_PRICE, priceStr);
		SetDlgItemText(IDC_CHANGED_QUANTITY, stockStr);
		SetDlgItemText(IDC_CHANGED_DISCOUNT, discountStr);
	}
}


//void GoodsManageView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView)
//{
//	
//
//	CFormView::OnActivateView(bActivate, pActivateView, pDeactiveView);
//}


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
		ReloadListBox();
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



void GoodsManageView::OnBnClickedDeleteButton()
{
	currentList.Delete(currentGoods);
	currentGoods = currentList.getFirstGoods();
	ReloadListBox();
}


void GoodsManageView::OnBnClickedChangeButton()
{
	CString cName, cID, cPrice, cDiscount, cStock;
	GetDlgItemText(IDC_CHANGED_NAME, cName);
	GetDlgItemText(IDC_CHANGED_ID, cID);
	GetDlgItemText(IDC_CHANGED_PRICE, cPrice);
	GetDlgItemText(IDC_CHANGED_DISCOUNT, cDiscount);
	GetDlgItemText(IDC_CHANGED_QUANTITY, cStock);
	if (cName.IsEmpty() || cID.IsEmpty() || cPrice.IsEmpty() || cDiscount.IsEmpty() || cStock.IsEmpty()) {
		MessageBox(TEXT("Insuffient input!"));
	}
	else {
		double dPrice, dDiscount;
		int iStock;
		dPrice = _ttof(cPrice), dDiscount = _ttof(cDiscount);
		iStock = _ttoi(cStock);
		currentGoods->Edit(cName, cID, dPrice, dDiscount, iStock);
		ReloadListBox();
	}
}


void GoodsManageView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	
	currentList.ReadFile();
	listBox = (CComboBox*)GetDlgItem(IDC_GOODSLIST);

	ReloadListBox();
}
