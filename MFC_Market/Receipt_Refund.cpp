// Receipt_Refund.cpp: 实现文件
//

#include "pch.h"
#include "MFC_Market.h"
#include "Receipt_Refund.h"
#include "afxdialogex.h"
#include<string>
#pragma warning (disable : 4996)
using namespace std;
// Receipt_Refund 对话框

IMPLEMENT_DYNCREATE(Receipt_Refund, CFormView)

Receipt_Refund::Receipt_Refund()
	: CFormView(Receipt_Refund::IDD)
	, sum_price(0)
{

}

Receipt_Refund::~Receipt_Refund()
{
}

void Receipt_Refund::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, sum_price);
	DDX_Control(pDX, IDC_LIST1, Receipt);

}


BEGIN_MESSAGE_MAP(Receipt_Refund, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &Receipt_Refund::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_EDIT1, &Receipt_Refund::OnEnChangeEdit1)
END_MESSAGE_MAP()


// Receipt_Refund 消息处理程序

void Receipt_Refund::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	//CString strTime;
	//CTime tm;
	//tm = CTime::GetCurrentTime();         //获取当前系统时间
	//strTime = tm.Format("%y年%m月%d日 %X");   //格式化系统时间。即使系统时 间按照Format中设置的格式显示
	//SetDlgItemText(IDC_TIME, strTime);        //初始化编辑框显示
	//SetTimer(1, 1000, NULL);         //启动定时器

	//列表控件的使用
	CString title[] = { TEXT("名称"),TEXT("数量"),TEXT("单价") };

	for (int i = 0; i < 3; i++)
	{
		//设置表头
		Receipt.InsertColumn(i, title[i], LVCFMT_LEFT, 150);
	}
}




void Receipt_Refund::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	fstream file;
	file.open("../etc/Last_Receipt.txt");
	CString tempName = TEXT("\0"), tempPrice = TEXT("\0"), tempNum = TEXT("\0");
	char tempChar = 0, tempChar2, tempT[128];
	int tabNum = 0;
	string line; int time = 0;
	int i = 0;
	double sumprice = 0;
	while (!file.eof())
	{
		TCHAR sz[1024 * 128] = { 0 };
		file.getline(tempT, (sizeof(sz) / sizeof(wchar_t)) - 1);
		line = tempT;
		if (!line.compare(""))
		{
			continue;
		}
		while (line.compare(0, 4, "Total", 0, 4)&&line.compare(0, 3, "User", 0, 3))
		{
			char* cstr = new char[line.length() + 1];
			std::strcpy(cstr, line.c_str());
			char* p = std::strtok(cstr, "\t");
			if (i != 0) {
				Receipt.InsertItem(i, (CString)p);
				int j = 1;
				double one_price = 0;
				int num = 0;
				while (p != 0)
				{
					p = std::strtok(NULL, "\t");
					Receipt.SetItemText(i - 1, j, (CString)p);
					if (j == 1)
						num = atoi(p);
					else if (j == 2)
						one_price = strtod(p, NULL);
					j++;
				}
				sumprice += num * one_price;
				break;
			}
			break;
		}
		i++;
	}
	CString cPrice;
	cPrice.Format(TEXT("%lf"), sumprice);
	SetDlgItemText(IDC_EDIT1, cPrice);



	file.close();
}


void Receipt_Refund::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CFormView::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
