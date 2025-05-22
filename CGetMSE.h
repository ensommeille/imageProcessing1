#pragma once
#include <afxwin.h>
#include "afxdialogex.h"
#include "resource.h"

// CGetMSE 对话框

class CGetMSE : public CDialogEx
{
	DECLARE_DYNAMIC(CGetMSE)

public:
	CGetMSE(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CGetMSE();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GETMSE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CEdit MSEValue;
	int out;
};
