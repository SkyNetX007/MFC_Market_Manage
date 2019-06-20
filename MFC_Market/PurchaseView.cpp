#include "pch.h"
#include "PurchaseView.h"

// PurchaseView

using namespace std;

IMPLEMENT_DYNCREATE(PurchaseView, CFormView)

PurchaseView::PurchaseView()
	: CFormView(PurchaseView::IDD)
{

}

BEGIN_MESSAGE_MAP(PurchaseView, CFormView)
	ON_BN_CLICKED(IDC_FILTER_BUTTON, &PurchaseView::OnBnClickedFilterButton)
	ON_BN_CLICKED(IDC_SORT_BUTTON, &PurchaseView::OnBnClickedSortButton)
	ON_NOTIFY(UDN_DELTAPOS, IDC_TOCART_SPIN, &PurchaseView::OnDeltaposTocartSpin)
	ON_BN_CLICKED(IDC_TOCART_BUTTON, &PurchaseView::OnBnClickedTocartButton)
	ON_BN_CLICKED(IDC_DELETE_BUTTON, &PurchaseView::OnBnClickedDeleteButton)
	ON_NOTIFY(UDN_DELTAPOS, IDC_INCART_SPIN, &PurchaseView::OnDeltaposIncartSpin)
	ON_BN_CLICKED(IDC_INCART_BUTTON, &PurchaseView::OnBnClickedIncartButton)
	ON_BN_CLICKED(IDC_BUY_BUTTO, &PurchaseView::OnBnClickedBuyButto)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_GOODS_LIST, &PurchaseView::OnLvnItemchangedGoodsList)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_CART_LIST, &PurchaseView::OnLvnItemchangedCartList)
END_MESSAGE_MAP()


void PurchaseView::OnBnClickedFilterButton()
{
	CString content;
	GetDlgItemText(IDC_FILTER_CONTENT, content);

}


void PurchaseView::OnBnClickedSortButton()
{
	// TODO: 在此添加控件通知处理程序代码
}


void PurchaseView::OnDeltaposTocartSpin(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void PurchaseView::OnBnClickedTocartButton()
{
	// TODO: 在此添加控件通知处理程序代码
}


void PurchaseView::OnBnClickedDeleteButton()
{
	// TODO: 在此添加控件通知处理程序代码
}


void PurchaseView::OnDeltaposIncartSpin(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void PurchaseView::OnBnClickedIncartButton()
{
	// TODO: 在此添加控件通知处理程序代码
}


void PurchaseView::OnBnClickedBuyButto()
{
	// TODO: 在此添加控件通知处理程序代码
}


void PurchaseView::OnLvnItemchangedGoodsList(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void PurchaseView::OnLvnItemchangedCartList(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void PurchaseView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	totalList.ReadFile();
	filterList = totalList;

	chooseList = (CListCtrl*)GetDlgItem(IDC_GOODS_LIST);
	cartList = (CListCtrl*)GetDlgItem(IDC_CART_LIST);
	CString columnHeads[6] = { TEXT("名称"),TEXT("原价"),TEXT("折扣"),TEXT("现价"),TEXT("库存"),TEXT("数目") };
	for (int i = 0; i < 5; i++)
		chooseList->InsertColumn(i, columnHeads[i], 0, 80, 0);
	cartList->InsertColumn(0, columnHeads[1], 0, 80, 0);
	cartList->InsertColumn(1, columnHeads[3], 0, 80, 0);
	cartList->InsertColumn(2, columnHeads[5], 0, 80, 0);

	ReloadLists();
}

void PurchaseView::ReloadLists()
{
	chooseList = (CListCtrl*)GetDlgItem(IDC_GOODS_LIST);
	cartList = (CListCtrl*)GetDlgItem(IDC_CART_LIST);

	CString cPrice, cStock, cNowPrice, cDiscount;
	double dNowPrice;

	list<Goods>::iterator it = filterList.getFirstGoods();
	int tempLength = filterList.GetLength();
	for (int i = 0; i < tempLength; i++) {
		dNowPrice = it->price * (1 - it->discount);
		cPrice.Format(TEXT("%.2lf"), it->price);
		cStock.Format(TEXT("%d"), it->stock);
		cDiscount.Format(TEXT("%.1lf"), it->discount*100);
		cDiscount.Append(TEXT("%"));
		cNowPrice.Format(TEXT("%.2lf"), dNowPrice);
		chooseList->InsertItem(i, it->name);
		chooseList->SetItemText(i, 1, cPrice);
		chooseList->SetItemText(i, 2, cDiscount);
		chooseList->SetItemText(i, 3, cNowPrice);
		chooseList->SetItemText(i, 4, cStock);
		it++;
	}

	it = cart.getFirstGoods();
	tempLength = cart.GetLength();
	for (int i = 0; i < tempLength; i++) {
		dNowPrice = it->price * (1 - it->discount);
		cStock.Format(TEXT("%d"), it->stock);
		cNowPrice.Format(TEXT("%.2lf"), dNowPrice);
		chooseList->InsertItem(i, it->name);
		chooseList->SetItemText(i, 1, cNowPrice);
		chooseList->SetItemText(i, 2, cStock);
		it++;
	}

	SetDlgItemText(IDC_INCART_QUANTITY, TEXT(""));
	SetDlgItemText(IDC_TOCART_QUANTITY, TEXT(""));
	SetDlgItemText(IDC_TOCART_ID, TEXT(""));
}
