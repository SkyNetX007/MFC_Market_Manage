#pragma once


// SelectBox 视图

class SelectBox : public CTreeView
{
	DECLARE_DYNCREATE(SelectBox)

protected:
	SelectBox();           // 动态创建所使用的受保护的构造函数
	virtual ~SelectBox();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()

private:
	CTreeCtrl* controlTree = nullptr;
	CImageList* imageList = nullptr;
public:
	virtual void OnInitialUpdate();
};


