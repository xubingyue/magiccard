
// EditorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Editor.h"
#include "EditorDlg.h"
#include "CardData.h"

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
	ON_EN_CHANGE(IDC_EDIT1, &CEditorDlg::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, &CEditorDlg::OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT3, &CEditorDlg::OnEnChangeEdit3)
	ON_EN_CHANGE(IDC_EDIT4, &CEditorDlg::OnEnChangeEdit4)
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
	int nSize = sizeof(g_szCardType) / sizeof (g_szCardType[0]);
	for (int i = 1; i < nSize; ++i)
	{
		m_cboxType.AddString(g_szCardType[i]);
	}
	m_cboxType.SetCurSel(0);
	for (int i = 0; i < nSize; ++i)
	{
		m_cboxFilter.AddString(g_szCardType[i]);
	}
	m_cboxFilter.SetCurSel(0);

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
		CDialog::UpdateWindow();
		ShowPicture();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CEditorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CEditorDlg::ShowPicture()
{
	if (m_strPictPathName.IsEmpty())
	{
		return;
	}

	CDC* pDC = GetDlgItem(IDC_PICTURE)->GetDC();

	CRect rect;
	GetDlgItem(IDC_PICTURE)->GetClientRect(&rect);

	CImage image; 
	HRESULT hr = image.Load(m_strPictPathName);
	if (S_OK == hr)
	{
		pDC->SetStretchBltMode(COLORONCOLOR); 
		image.Draw(pDC->GetSafeHdc(), rect);
	}
	else
	{
		pDC->DrawText(m_strPictPathName, rect, DT_WORDBREAK | DT_EDITCONTROL | DT_CENTER);
	}
	ReleaseDC(pDC);
}

void CEditorDlg::OnBnClickedButtonPic()
{
	// TODO: Add your control notification handler code here
	static TCHAR szFilter[] = _T("JPG Files (*.jpg)|*.jpg|BMP Files (*.bmp)|*.bmp|PNG Files (*.png)|*.png|All Files (*.*)|*.*||");
	CFileDialog dlg(TRUE, _T("BMP"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter);
	if (dlg.DoModal() == IDOK)
	{
		m_strPictPathName = dlg.GetPathName();
		Invalidate();
	}
}

void CEditorDlg::Preview()
{
	UpdateData(TRUE);

	CString strType;
	m_cboxType.GetLBText(m_cboxType.GetCurSel(), strType);

	static_cast<CEdit*>(GetDlgItem(IDC_EDIT_TYPE))->SetWindowText(strType);
	static_cast<CEdit*>(GetDlgItem(IDC_EDIT_NAME))->SetWindowText(m_strName);
	static_cast<CEdit*>(GetDlgItem(IDC_EDIT_SERIES))->SetWindowText(m_strSeries);
	static_cast<CEdit*>(GetDlgItem(IDC_EDIT_ATTACK))->SetWindowText(m_strAttack);
	static_cast<CEdit*>(GetDlgItem(IDC_EDIT_DESC))->SetWindowText(m_strDesc);
}

void CEditorDlg::OnBnClickedButtonSave()
{
	// TODO: Add your control notification handler code here
	CString strType;
	m_cboxType.GetLBText(m_cboxType.GetCurSel(), strType);

	SCard aCard;
	aCard.uId = 0;
	aCard.nType = StringToType(strType.GetBuffer());
	aCard.strName = m_strName.GetBuffer();
	aCard.strSeries = m_strSeries.GetBuffer();
	aCard.strDesc = m_strDesc.GetBuffer();
	aCard.strFileName = m_strPictPathName.GetBuffer();
	aCard.nAttack = _wtoi(m_strAttack.GetBuffer());

	CCardData::Instance().AddCard(aCard);
}

void CEditorDlg::OnBnClickedButtonRemove()
{
	// TODO: Add your control notification handler code here
	m_strName.Empty();
	m_strSeries.Empty();
	m_strDesc.Empty();
	m_strAttack.Empty();

	UpdateData(FALSE);

	static_cast<CEdit*>(GetDlgItem(IDC_EDIT_TYPE))->SetWindowText(_T(""));
	static_cast<CEdit*>(GetDlgItem(IDC_EDIT_NAME))->SetWindowText(m_strName);
	static_cast<CEdit*>(GetDlgItem(IDC_EDIT_SERIES))->SetWindowText(m_strSeries);
	static_cast<CEdit*>(GetDlgItem(IDC_EDIT_ATTACK))->SetWindowText(m_strAttack);
	static_cast<CEdit*>(GetDlgItem(IDC_EDIT_DESC))->SetWindowText(m_strDesc);
}

void CEditorDlg::OnCbnSelchangeComboType()
{
	// TODO: Add your control notification handler code here
	Preview();
}

void CEditorDlg::OnCbnSelchangeComboFilter()
{
	// TODO: Add your control notification handler code here
}

void CEditorDlg::OnBnClickedButtonPreview()
{
	// TODO: Add your control notification handler code here
	Preview();
}


void CEditorDlg::OnEnChangeEdit1()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	Preview();
}

void CEditorDlg::OnEnChangeEdit2()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	Preview();
}

void CEditorDlg::OnEnChangeEdit3()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	Preview();
}

void CEditorDlg::OnEnChangeEdit4()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	Preview();
}
