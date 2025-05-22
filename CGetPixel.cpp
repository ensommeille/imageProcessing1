// CGetPixel.cpp: 实现文件
//

#include "CGetPixel.h"


// CGetPixel 对话框

IMPLEMENT_DYNAMIC(CGetPixel, CDialogEx)

CGetPixel::CGetPixel(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GetPixel, pParent)
	, Text_x(_T("x"))
	, Text_y(_T("y"))
{

}

CGetPixel::~CGetPixel()
{
}

void CGetPixel::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, GetX);
	DDX_Control(pDX, IDC_EDIT2, GetY);
	DDX_Text(pDX, IDC_TEXT1, Text_x);
	DDX_Text(pDX, IDC_TEXT2, Text_y);
}


BEGIN_MESSAGE_MAP(CGetPixel, CDialogEx)
	ON_BN_CLICKED(IDOK, &CGetPixel::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CGetPixel::OnBnClickedCancel)
END_MESSAGE_MAP()


// CGetPixel 消息处理程序


void CGetPixel::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CString temp;
	this->GetX.GetWindowText(temp);
	this->X = atoi(temp);
	this->GetY.GetWindowText(temp);
	this->Y = atoi(temp);
	CDialogEx::OnOK();
}


void CGetPixel::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	this->X = -1;
	this->Y = -1;
	CDialogEx::OnCancel();
}
