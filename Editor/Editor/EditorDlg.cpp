
// EditorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Editor.h"
#include "EditorDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CEditorDlg dialog
static const TCHAR* g_strCardType[] = 
{
	_T("None"),
	_T("Monster Level 1"),
	_T("Monster Level 2"),
	_T("Monster Level 3"),
	_T("Magic"),
	_T("Trap"),
};



CEditorDlg::CEditorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEditorDlg::IDD, pParent)
	, m_strName(_T(""))
	, m_strSeries(_T(""))
	, m_strAttack(_T(""))
	, m_strDesc(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CEditorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_TYPE, m_cboxType);
	DDX_Text(pDX, IDC_EDIT1, m_strName);
	DDX_Text(pDX, IDC_EDIT2, m_strSeries);
	DDX_Text(pDX, IDC_EDIT3, m_strAttack);
	DDX_Text(pDX, IDC_EDIT4, m_strDesc);
	DDX_Control(pDX, IDC_COMBO_FILTER, m_cboxFilter);
	DDX_Control(pDX, IDC_LIST_CARD, m_listCard);
	DDV_MaxChars(pDX, m_strName, 20);
	DDV_MaxChars(pDX, m_strSeries, 20);
	DDV_MaxChars(pDX, m_strAttack, 20);
	DDV_MaxChars(pDX, m_strDesc, 200);
}

BEGIN_MESSAGE_MAP(CEditorDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_PIC, &CEditorDlg::OnBnClickedButtonPic)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CEditorDlg::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_REMOVE, &CEditorDlg::OnBnClickedButtonRemove)
	ON_CBN_SELCHANGE(IDC_COMBO_TYPE, &CEditorDlg::OnCbnSelchangeComboType)
	ON_CBN_SELCHANGE(IDC_COMBO_FILTER, &CEditorDlg::OnCbnSelchangeComboFilter)
	ON_BN_CLICKED(IDC_BUTTON_PREVIEW, &CEditorDlg::OnBnClickedButtonPreview)
END_MESSAGE_MAP()


// CEditorDlg message handlers

BOOL CEditorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	int nSize = sizeof(g_strCardType) / sizeof (g_strCardType[0]);
	for (int i = 1; i < nSize; ++i)
	{
		m_cboxType.AddString(g_strCardType[i]);
	}
	for (int i = 0; i < nSize; ++i)
	{
		m_cboxFilter.AddString(g_strCardType[i]);
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CEditorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CEditorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CEditorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CEditorDlg::OnBnClickedButtonPic()
{
	// TODO: Add your control notification handler code here
}

void CEditorDlg::OnBnClickedButtonSave()
{
	// TODO: Add your control notification handler code here
}

void CEditorDlg::OnBnClickedButtonRemove()
{
	// TODO: Add your control notification handler code here
}

void CEditorDlg::OnCbnSelchangeComboType()
{
	// TODO: Add your control notification handler code here
}

void CEditorDlg::OnCbnSelchangeComboFilter()
{
	// TODO: Add your control notification handler code here
}

void CEditorDlg::OnBnClickedButtonPreview()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	//static_cast<CEdit*>(GetDlgItem(IDC_EDIT_TYPE))->SetWindowText(m_cboxType.GetWindowText());
	static_cast<CEdit*>(GetDlgItem(IDC_EDIT_NAME))->SetWindowText(m_strName);
	static_cast<CEdit*>(GetDlgItem(IDC_EDIT_SERIES))->SetWindowText(m_strSeries);
	static_cast<CEdit*>(GetDlgItem(IDC_EDIT_ATTACK))->SetWindowText(m_strAttack);
	static_cast<CEdit*>(GetDlgItem(IDC_EDIT_DESC))->SetWindowText(m_strDesc);
}
