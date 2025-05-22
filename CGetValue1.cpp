// CGetValue1.cpp: 实现文件
//
#include "CGetValue1.h"


// CGetValue1 对话框

IMPLEMENT_DYNAMIC(CGetValue1, CDialogEx)

CGetValue1::CGetValue1(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GETVALUE1, pParent)
	, Text(_T("请设定灰度图像像素值"))
{

}

CGetValue1::~CGetValue1()
{
}

void CGetValue1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_TEXT3, Text);
	DDX_Control(pDX, IDC_EDIT1, Value1);
}


BEGIN_MESSAGE_MAP(CGetValue1, CDialogEx)
	ON_BN_CLICKED(IDOK, &CGetValue1::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CGetValue1::OnBnClickedCancel)
END_MESSAGE_MAP()


// CGetValue1 消息处理程序


void CGetValue1::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CString temp;
	this->Value1.GetWindowText(temp);
	this->out = atoi(temp);
	CDialogEx::OnOK();
}


void CGetValue1::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	this->out = -1;
	CDialogEx::OnCancel();
}
