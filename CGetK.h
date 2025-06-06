﻿#pragma once
#include <afxwin.h>
#include "afxdialogex.h"
#include "resource.h"

// CGetK 对话框

class CGetK : public CDialogEx
{
	DECLARE_DYNAMIC(CGetK)

public:
	CGetK(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CGetK();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GETK };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CEdit K;
	float out;
	afx_msg void OnEnChangeEdit1();
};
