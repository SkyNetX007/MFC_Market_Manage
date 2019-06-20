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
	ON_BN_CLICKED(IDC_TOCART_BUTTON, &PurchaseView::OnBnClickedTocartButton)
	ON_BN_CLICKED(IDC_DELETE_BUTTON, &PurchaseView::OnBnClickedDeleteButton)
	ON_BN_CLICKED(IDC_INCART_BUTTON, &PurchaseView::OnBnClickedIncartButton)
	ON_BN_CLICKED(IDC_BUY_BUTTO, &PurchaseView::OnBnClickedBuyButto)
	ON_NOTIFY(NM_CLICK, IDC_GOODS_LIST, &PurchaseView::OnNMClickGoodsList)
	ON_NOTIFY(NM_CLICK, IDC_CART_LIST, &PurchaseView::OnNMClickCartList)
END_MESSAGE_MAP()

void PurchaseView::OnBnClickedFilterButton()
{
	CString content;
	GetDlgItemText(IDC_FILTER_CONTENT, content);
	filterList = totalList;
	list<Goods>::iterator it = filterList.getFirstGoods(), it2 = it;
	int tempLength = filterList.GetLength();
	if(!content.IsEmpty())
		for (; tempLength > 0; tempLength--) {
			it++;
			if (it2->name.Find(content) == -1) {
				filterList.Delete(it2);
			}
			it2 = it;
		}
	ReloadLists();
}

void PurchaseView::OnBnClickedSortButton()
{
	CString accord;
	GetDlgItemText(IDC_SORT_METHOD, accord);
	if (!accord.IsEmpty()) {
		chooseList = (CListCtrl*)GetDlgItem(IDC_GOODS_LIST);
		chooseList->SortItems(sort, (DWORD)chooseList);

	}
}

void PurchaseView::OnBnClickedTocartButton()
{
	CString chosenID, cNum;
	GetDlgItemText(IDC_TOCART_ID, chosenID);
	GetDlgItemText(IDC_TOCART_QUANTITY, cNum);
	int iNum = _ttoi(cNum);
	list<Goods>::iterator it = filterList.FindID(chosenID);

	if (it == filterList.getEnd()) {
		MessageBox(TEXT("Ivalid ID!"));
		return;
	}
	if (it->stock - iNum < 0) {
		MessageBox(TEXT("Insufficient stock!"));
		return;
	}

	list<Goods>::iterator it2 = cart.FindID(chosenID);
	if (it2 == cart.getEnd())
		cart.Add(it->name, it->ID, it->price * (1 - it->discount), iNum);
	else
		it2->stock += iNum;
	it->stock -= iNum;
	it = totalList.Find(it->name);
	it->stock -= iNum;
	ReloadLists();
}

void PurchaseView::OnBnClickedDeleteButton()
{
	CString chosenName;
	int chosen;
	cartList = (CListCtrl*)GetDlgItem(IDC_CART_LIST);
	chosen = cartList->GetSelectionMark();
	if (chosen != -1)
	{
		chosenName = cartList->GetItemText(chosen, 0);
		list<Goods>::iterator it = cart.Find(chosenName);
		list<Goods>::iterator it2 = totalList.Find(chosenName);
		it2->stock += it->stock;
		it2 = filterList.Find(chosenName);
		it2->stock += it->stock;
		cart.Delete(it);
		ReloadLists();
	}
	
}

void PurchaseView::OnBnClickedIncartButton()
{
	cartList = (CListCtrl*)GetDlgItem(IDC_CART_LIST);
	CString cAdd,chosenName;
	int changedNum = 0, chosen = 0;
	chosen = cartList->GetSelectionMark();
	GetDlgItemText(IDC_INCART_QUANTITY, cAdd);
	if (chosen != -1 && !cAdd.IsEmpty())
	{
		changedNum = _ttoi(cAdd);
		chosenName = cartList->GetItemText(chosen, 0);
		list<Goods>::iterator it = cart.Find(chosenName), it2 = totalList.Find(chosenName);
		if (changedNum > it->stock + it2->stock) {
			MessageBox(TEXT("Insufficient stock!"));
			return;
		}
		if (changedNum > 0) {
			it2->stock = it2->stock + it->stock - changedNum;
			it2 = filterList.Find(chosenName);
			it2->stock = it2->stock + it->stock - changedNum;
			it->stock = changedNum;
			ReloadLists();
		}
		else {
			it2->stock += it->stock;
			it2 = filterList.Find(chosenName);
			it2->stock += it->stock;
			cart.Delete(it);
			ReloadLists();
		}
	}
}

void PurchaseView::OnBnClickedBuyButto()
{
	// TODO: 在此添加控件通知处理程序代码
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

	chooseList->DeleteAllItems(), cartList->DeleteAllItems();

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
		cartList->InsertItem(i, it->name);
		cartList->SetItemText(i, 1, cNowPrice);
		cartList->SetItemText(i, 2, cStock);
		it++;
	}

	SetDlgItemText(IDC_INCART_QUANTITY, TEXT(""));
	SetDlgItemText(IDC_TOCART_QUANTITY, TEXT(""));
	SetDlgItemText(IDC_TOCART_ID, TEXT(""));
}

int sort(LPARAM lp1, LPARAM lp2, LPARAM lp3)
{
	CListCtrl* list = (CListCtrl*)lp3;
	CString ca, cb;
	ca = list->GetItemText(lp1, 0);
	cb = list->GetItemText(lp2, 0);
	return ca.Compare(cb) > 0;
}

void PurchaseView::OnNMClickGoodsList(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	chooseList = (CListCtrl*)GetDlgItem(IDC_GOODS_LIST);
	int chosen = chooseList->GetSelectionMark();
	if (chosen != -1) {
		CString chosenName;
		chosenName = chooseList->GetItemText(chosen, 0);
		list<Goods>::iterator it = filterList.Find(chosenName);
		SetDlgItemText(IDC_TOCART_ID, it->ID);
		SetDlgItemText(IDC_TOCART_QUANTITY, TEXT("1"));
	}
	else {
		SetDlgItemText(IDC_TOCART_ID, TEXT(""));
		SetDlgItemText(IDC_TOCART_QUANTITY, TEXT(""));
	}

	*pResult = 0;
}

void PurchaseView::OnNMClickCartList(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	cartList = (CListCtrl*)GetDlgItem(IDC_CART_LIST);
	int chosen, chosenNum;
	chosen = cartList->GetSelectionMark();
	if (chosen != -1) {
		CString	cNum,chosenName = cartList->GetItemText(chosen, 0);
		list<Goods>::iterator it = cart.Find(chosenName);
		chosenNum = it->stock;
		cNum.Format(TEXT("%d"), chosenNum);
		SetDlgItemText(IDC_INCART_QUANTITY, cNum);
	}
	*pResult = 0;
}
