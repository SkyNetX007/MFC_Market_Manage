#pragma once
#include <afxext.h>
#include "Resource.h"
#include "Groups.h"

class LoginView : public CFormView
{
	DECLARE_DYNCREATE(LoginView)

protected:
	LoginView();
	virtual ~LoginView() {};

public:
	ACCESS* currentUser = new ACCESS;

	enum { IDD = IDD_LOGIN };
	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedOk();
};