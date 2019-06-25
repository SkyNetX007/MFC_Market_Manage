#pragma once
#include <afxext.h>
#include "Resource.h"
#include <string>
#include "Groups.h"
#include <fstream>
#include "MainFrm.h"

class LogoutView : public CFormView
{
	DECLARE_DYNCREATE(LogoutView)

protected:
	LogoutView();
	virtual ~LogoutView() {};

public:
	enum { IDD = IDD_LOGOUT };
	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedOk2();
};

