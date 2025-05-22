#pragma once
#include <afxwin.h>
#include "afxdialogex.h"
#include "resource.h"

// CGetValue2 对话框

class CGetValue2 : public CDialogEx
{
	DECLARE_DYNAMIC(CGetValue2)

public:
	CGetValue2(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CGetValue2();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GETVALUE2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString Text1;
	CString Text2;
	CString Text3;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CEdit Value1;
	CEdit Value2;
	CEdit Value3;
	int Red;
	int Green;
	int Blue;
};
