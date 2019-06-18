#pragma once
#include "resource.h"

class EditBox : public CFormView
{
	DECLARE_DYNCREATE(EditBox)

protected:
	EditBox();           // protected constructor used by dynamic creation
	virtual ~EditBox() {};

public:
	enum { IDD = IDD_LOGIN };

	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedOk();
};


