#pragma once
#include <afxwin.h>
#include "afxdialogex.h"
#include "resource.h"

// CGetBF 对话框

class CGetBF : public CDialogEx
{
	DECLARE_DYNAMIC(CGetBF)

public:
	CGetBF(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CGetBF();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GETBF };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString Text1;
	CString Text2;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CEdit Value_d;
	CEdit Value_r;
	int out_d;
	int out_r;
};
