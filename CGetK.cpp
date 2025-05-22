// CGetK.cpp: 实现文件
//
#include "CGetK.h"


// CGetK 对话框

IMPLEMENT_DYNAMIC(CGetK, CDialogEx)

CGetK::CGetK(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GETK, pParent)
{

}

CGetK::~CGetK()
{
}

void CGetK::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, K);
}


BEGIN_MESSAGE_MAP(CGetK, CDialogEx)
	ON_BN_CLICKED(IDOK, &CGetK::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CGetK::OnBnClickedCancel)
	ON_EN_CHANGE(IDC_EDIT1, &CGetK::OnEnChangeEdit1)
END_MESSAGE_MAP()


// CGetK 消息处理程序


void CGetK::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CString temp;
	this->K.GetWindowText(temp);
	this->out = atof(temp);
	CDialogEx::OnOK();
}


void CGetK::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	this->out = -1;
	CDialogEx::OnCancel();
}




void CGetK::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	CString temp;
	this->K.GetWindowText(temp);
	int pcnt = 0;
	int length = temp.GetLength();
	//输入小数点唯一
	for (int i = 0; i < length; i++)
	{
		if (temp[i] == '.')
		{
			pcnt++;
			if (pcnt > 1)
			{
				CString newtemp;
				newtemp = temp.Left(i);
				newtemp += temp.Right(temp.GetLength() - i - 1);
				this->K.SetWindowText(newtemp);
				return;
			}
		}
	}
	//禁止输入数字和小数点以外的字符
	for (int i = 0; i < length; i++)
	{
		if (temp[i] != '.' && ( temp[i] > '9' || temp[i] < '0' ))
		{
			temp = temp.Left(i) + temp.Right(temp.GetLength() - i - 1);
			this->K.SetWindowText(temp);
			return;
		}
	}

}
