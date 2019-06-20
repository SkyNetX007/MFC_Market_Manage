#pragma once
#include <afxext.h>
#include "resource.h"
#include "Goods.h"
class PurchaseView : public CFormView
{
	DECLARE_DYNCREATE(PurchaseView)

protected:
	PurchaseView();
	virtual ~PurchaseView() {};

public:
	enum { IDD = IDD_PURCHASE };
	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedFilterButton();
	afx_msg void OnBnClickedSortButton();
	afx_msg void OnDeltaposTocartSpin(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedTocartButton();
	afx_msg void OnBnClickedDeleteButton();
	afx_msg void OnDeltaposIncartSpin(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedIncartButton();
	afx_msg void OnBnClickedBuyButto();
	afx_msg void OnLvnItemchangedGoodsList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLvnItemchangedCartList(NMHDR* pNMHDR, LRESULT* pResult);
};

