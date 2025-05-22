// CGetWindow.cpp: 实现文件
//
#include "CGetWindow.h"


// CGetWindow 对话框

IMPLEMENT_DYNAMIC(CGetWindow, CDialogEx)

CGetWindow::CGetWindow(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GETWINDOW, pParent)
{

}

CGetWindow::~CGetWindow()
{
}

void CGetWindow::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, Value);
}


BEGIN_MESSAGE_MAP(CGetWindow, CDialogEx)
	ON_BN_CLICKED(IDOK, &CGetWindow::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CGetWindow::OnBnClickedCancel)
END_MESSAGE_MAP()


// CGetWindow 消息处理程序


void CGetWindow::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CString temp;
	this->Value.GetWindowText(temp);
	this->out = atoi(temp);
	CDialogEx::OnOK();
}


void CGetWindow::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	this->out = -1;
	CDialogEx::OnCancel();
}
