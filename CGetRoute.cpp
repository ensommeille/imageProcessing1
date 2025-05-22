// CGetRoute.cpp: 实现文件
//

#include "CGetRoute.h"


// CGetRoute 对话框

IMPLEMENT_DYNAMIC(CGetRoute, CDialogEx)

CGetRoute::CGetRoute(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GetRoute, pParent)
	, Text(_T("请输入存储路径与文件名(不含后缀)!"))
{
}

CGetRoute::~CGetRoute()
{
}

void CGetRoute::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EDIT1, FileRoute);
	DDX_Text(pDX, IDC_TEXT, Text);
}


BEGIN_MESSAGE_MAP(CGetRoute, CDialogEx)
	ON_BN_CLICKED(IDOK, &CGetRoute::OnBnClickedOk)
END_MESSAGE_MAP()


// CGetRoute 消息处理程序


void CGetRoute::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	this->FileRoute.GetWindowText(this->out);
	CDialogEx::OnOK();
}

