#pragma once
#include <afxwin.h>
#include "afxdialogex.h"
#include "resource.h"

// CGetValue1 对话框

class CGetValue1 : public CDialogEx
{
	DECLARE_DYNAMIC(CGetValue1)

public:
	CGetValue1(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CGetValue1();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GETVALUE1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString Text;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CEdit Value1;
	int out;
};
