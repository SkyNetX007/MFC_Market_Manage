#pragma once
#include <afxext.h>
#include "Resource.h"
#include "Goods.h"

class GoodsManageView : public CFormView
{
	DECLARE_DYNCREATE(GoodsManageView)

protected:
	GoodsManageView();
	virtual ~GoodsManageView() {};

private:
	GoodsList currentList;
	
public:
	enum { IDD = IDD_GOODS_MANAGEMENT };
	DECLARE_MESSAGE_MAP()
	afx_msg void OnCbnSelchangeGoodslist();
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	afx_msg void OnBnClickedAddButton();
	afx_msg void OnBnClickedSaveButton();
};

