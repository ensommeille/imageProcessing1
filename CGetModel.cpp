// CGetModel.cpp: 实现文件
//
#include "CGetModel.h"


// CGetModel 对话框

IMPLEMENT_DYNAMIC(CGetModel, CDialogEx)

CGetModel::CGetModel(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GETMODEL, pParent)
	, Text1(_T("NewWidth(x)"))
	, Text2(_T("NewHeight(y)"))
{

}

CGetModel::~CGetModel()
{
}

void CGetModel::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_TEXT1, Text1);
	DDX_Text(pDX, IDC_TEXT2, Text2);
	DDX_Control(pDX, IDC_EDIT1, NewWidth);
	DDX_Control(pDX, IDC_EDIT2, NewHeight);
}


BEGIN_MESSAGE_MAP(CGetModel, CDialogEx)
	ON_BN_CLICKED(IDC_MODEL1, &CGetModel::OnBnClickedModel1)
	ON_BN_CLICKED(IDC_MODEL2, &CGetModel::OnBnClickedModel2)
	ON_BN_CLICKED(IDCANCEL, &CGetModel::OnBnClickedCancel)
END_MESSAGE_MAP()


// CGetModel 消息处理程序


void CGetModel::OnBnClickedModel1()
{
	// TODO: 在此添加控件通知处理程序代码
	this->model = 0;
	CString temp;
	this->NewWidth.GetWindowText(temp);
	this->Width = atoi(temp);
	this->NewHeight.GetWindowText(temp);
	this->Height = atoi(temp);
	CDialogEx::OnOK();
}


void CGetModel::OnBnClickedModel2()
{
	// TODO: 在此添加控件通知处理程序代码
	this->model = 1;
	CString temp;
	this->NewWidth.GetWindowText(temp);
	this->Width = atoi(temp);
	this->NewHeight.GetWindowText(temp);
	this->Height = atoi(temp);
	CDialogEx::OnOK();
}


void CGetModel::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}
