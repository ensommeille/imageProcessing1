// CGetBF.cpp: 实现文件
//
#include "CGetBF.h"


// CGetBF 对话框

IMPLEMENT_DYNAMIC(CGetBF, CDialogEx)

CGetBF::CGetBF(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GETBF, pParent)
	, Text1(_T("sigma_d"))
	, Text2(_T("sigma_r"))
{

}

CGetBF::~CGetBF()
{
}

void CGetBF::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_TEXT1, Text1);
	DDX_Text(pDX, IDC_TEXT2, Text2);
	DDX_Control(pDX, IDC_EDIT1, Value_d);
	DDX_Control(pDX, IDC_EDIT2, Value_r);
}


BEGIN_MESSAGE_MAP(CGetBF, CDialogEx)
	ON_BN_CLICKED(IDOK, &CGetBF::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CGetBF::OnBnClickedCancel)
END_MESSAGE_MAP()


// CGetBF 消息处理程序


void CGetBF::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CString temp;
	this->Value_d.GetWindowText(temp);
	this->out_d = atoi(temp);
	this->Value_r.GetWindowText(temp);
	this->out_r = atoi(temp);
	CDialogEx::OnOK();
}


void CGetBF::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	this->out_d = -1;
	this->out_r = -1;
	CDialogEx::OnCancel();
}
