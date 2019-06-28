#pragma once

#include<afxext.h>

#include "MFC_Market.h"
#include "afxdialogex.h"
#include "Goods.h"
#include <fstream>       //提供文件头文件
#include <iostream>
#include <cstring>
// Receipt_Refund 对话框

class Receipt_Refund : public CFormView
{
	DECLARE_DYNCREATE(Receipt_Refund)

public:
	Receipt_Refund();   // 标准构造函数
	virtual ~Receipt_Refund();

	enum { IDD = IDD_RECEIPT_REFUND };


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	double sum_price;
	CString User;
public:
	virtual void OnInitialUpdate();
private:
	CListCtrl Receipt;

public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnEnChangeEdit1();

};
