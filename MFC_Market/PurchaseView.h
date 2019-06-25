#pragma once
#include <afxext.h>
#include "resource.h"
#include "Groups.h"
#include "MainFrm.h"
#include "Goods.h"

class PurchaseView : public CFormView
{
	DECLARE_DYNCREATE(PurchaseView)

protected:
	PurchaseView();
	virtual ~PurchaseView() {};

public:
	enum { IDD = IDD_PURCHASE };
	virtual void OnInitialUpdate();
	
	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedFilterButton();
	afx_msg void OnBnClickedSortButton();
	afx_msg void OnBnClickedTocartButton();
	afx_msg void OnBnClickedDeleteButton();
	afx_msg void OnBnClickedIncartButton();
	afx_msg void OnBnClickedBuyButto();
	afx_msg void OnConfirm(WPARAM wParam, LPARAM lParam);
	

private:
	GoodsList totalList, filterList, cart;
	CListCtrl *chooseList, *cartList;
	int sortOrder = 1, sortCol = 0;

	void ReloadLists();	
	
public:
	afx_msg void OnNMClickGoodsList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMClickCartList(NMHDR* pNMHDR, LRESULT* pResult);

};
