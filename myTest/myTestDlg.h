
// myTestDlg.h : header file
//

#pragma once
#include "afxwin.h"


// CmyTestDlg dialog
class CmyTestDlg : public CDialogEx
{
// Construction
public:
	CmyTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_MYTEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	
	CString m_replaceStr;
	afx_msg void OnBnClickedCancel();
	CString m_findStr;
	CEdit m_changeFile;
	bool m_classChecked;
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	CEdit m_methodName;
};
