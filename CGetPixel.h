#pragma once
#include <afxwin.h>
#include "afxdialogex.h"
#include "resource.h"

// CGetPixel 对话框

class CGetPixel : public CDialogEx
{
	DECLARE_DYNAMIC(CGetPixel)

public:
	CGetPixel(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CGetPixel();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GetPixel };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit GetX;
	CEdit GetY;
	afx_msg void OnBnClickedOk();
	int X, Y;
	CString Text_x;
	CString Text_y;
	afx_msg void OnBnClickedCancel();
};
