// CGetValue2.cpp: 实现文件
//
#include "CGetValue2.h"



// CGetValue2 对话框

IMPLEMENT_DYNAMIC(CGetValue2, CDialogEx)

CGetValue2::CGetValue2(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GETVALUE2, pParent)
	, Text1(_T("Red"))
	, Text2(_T("Green"))
	, Text3(_T("Blue"))
{

}

CGetValue2::~CGetValue2()
{
}

void CGetValue2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_TEXT1, Text1);
	DDX_Text(pDX, IDC_TEXT2, Text2);
	DDX_Text(pDX, IDC_TEXT3, Text3);
	DDX_Control(pDX, IDC_EDIT1, Value1);
	DDX_Control(pDX, IDC_EDIT2, Value2);
	DDX_Control(pDX, IDC_EDIT3, Value3);
}


BEGIN_MESSAGE_MAP(CGetValue2, CDialogEx)
	ON_BN_CLICKED(IDOK, &CGetValue2::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CGetValue2::OnBnClickedCancel)
END_MESSAGE_MAP()


// CGetValue2 消息处理程序


void CGetValue2::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CString temp;
	this->Value1.GetWindowText(temp);
	this->Red = atoi(temp);
	this->Value2.GetWindowText(temp);
	this->Green = atoi(temp);
	this->Value3.GetWindowText(temp);
	this->Blue = atoi(temp);
	CDialogEx::OnOK();
}


void CGetValue2::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	this->Red = -1;
	this->Green = -1;
	this->Blue = -1;
	CDialogEx::OnCancel();
}
