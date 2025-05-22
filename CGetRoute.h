#pragma once
#include <afxwin.h>
#include "afxdialogex.h"
#include "resource.h"

// CGetRoute 对话框

class CGetRoute : public CDialogEx
{
	DECLARE_DYNAMIC(CGetRoute)

public:
	CGetRoute(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CGetRoute();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GetRoute };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CEdit FileRoute;
	CString out;

	CString Text;
};
