
// MainFrm.h: CMainFrame 类的接口
//

#pragma once
#include "Groups.h"

#define EDIT_LOGIN (WM_USER+100)
#define EDIT_LOGOUT (WM_USER+101)
#define EDIT_USERS_MANAGEMENT (WM_USER+102)
#define EDIT_GOODS_MANAGEMENT (WM_USER+103)
#define EDIT_PURCHASE (WM_USER+104)
#define EDIT_RECEIPT_REFUND (WM_USER+105)

#define PURCHASE_CONFIRM (WM_USER+106)

class CMainFrame : public CFrameWnd
{
	
protected: // 仅从序列化创建
	CMainFrame() noexcept;
	DECLARE_DYNCREATE(CMainFrame)

// 特性
public:
	ACCESS* currentUser = new ACCESS;
	template<class T>
	void SetLeftPage();

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 控件条嵌入成员
	CStatusBar        m_wndStatusBar;

// 生成的消息映射函数
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()

	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);

private:
	CSplitterWnd windowSplitter;
	CCreateContext cContext;
	afx_msg LRESULT OnEditChanges(WPARAM message, LPARAM lparam);
};


