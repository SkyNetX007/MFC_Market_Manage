#pragma once
#include <afxext.h>
#include "Resource.h"
#include "Goods.h"
#include "MainFrm.h"
#include "Groups.h"

class GoodsManageView : public CFormView
{
	friend class CMainFrame;

	DECLARE_DYNCREATE(GoodsManageView)

protected:
	GoodsManageView();
	virtual ~GoodsManageView() {};

private:
	GoodsList currentList;
	CComboBox* listBox = nullptr;
	list<Goods>::iterator currentGoods;

	void ReloadListBox();
	
public:
	enum { IDD = IDD_GOODS_MANAGEMENT };
	DECLARE_MESSAGE_MAP()
	afx_msg void OnCbnSelchangeGoodslist();
//	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	afx_msg void OnBnClickedAddButton();
	afx_msg void OnBnClickedSaveButton();
	afx_msg void OnBnClickedDeleteButton();
	afx_msg void OnBnClickedChangeButton();
	virtual void OnInitialUpdate();
};

