
// EditorDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CEditorDlg dialog
class CEditorDlg : public CDialog
{
// Construction
public:
	CEditorDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_EDITOR_DIALOG };

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
	afx_msg void OnBnClickedButtonPic();
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonRemove();
	afx_msg void OnCbnSelchangeComboType();
	afx_msg void OnCbnSelchangeComboFilter();
	afx_msg void OnBnClickedButtonPreview();
	CComboBox m_cboxType;
	CString m_strName;
	CString m_strSeries;
	CString m_strAttack;
	CString m_strDesc;
	CComboBox m_cboxFilter;
	CListCtrl m_listCard;
};
