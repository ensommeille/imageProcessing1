#pragma once
#include <afxwin.h>
#include "afxdialogex.h"
#include "resource.h"

// CGetModel 对话框

class CGetModel : public CDialogEx
{
	DECLARE_DYNAMIC(CGetModel)

public:
	CGetModel(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CGetModel();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GETMODEL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString Text1;
	CString Text2;
	afx_msg void OnBnClickedModel1();
	afx_msg void OnBnClickedModel2();
	int model;
	afx_msg void OnBnClickedCancel();
	CEdit NewWidth;
	CEdit NewHeight;
	int Width;
	int Height;
};
