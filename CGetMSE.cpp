// CGetMSE.cpp: 实现文件
//
#include "CGetMSE.h"


// CGetMSE 对话框

IMPLEMENT_DYNAMIC(CGetMSE, CDialogEx)

CGetMSE::CGetMSE(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GETMSE, pParent)
{

}

CGetMSE::~CGetMSE()
{
}

void CGetMSE::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, MSEValue);
}


BEGIN_MESSAGE_MAP(CGetMSE, CDialogEx)
	ON_BN_CLICKED(IDOK, &CGetMSE::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CGetMSE::OnBnClickedCancel)
END_MESSAGE_MAP()


// CGetMSE 消息处理程序


void CGetMSE::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CString temp;
	this->MSEValue.GetWindowText(temp);
	this->out = atoi(temp);
	CDialogEx::OnOK();
}


void CGetMSE::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	this->out = -1;
	CDialogEx::OnCancel();
}
