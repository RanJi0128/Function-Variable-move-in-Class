
// myTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "myTest.h"
#include "myTestDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
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

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CmyTestDlg dialog



CmyTestDlg::CmyTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CmyTestDlg::IDD, pParent)
	, m_replaceStr(_T(""))
	, m_findStr(_T(""))
	, m_classChecked(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CmyTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_replaceStr);
	DDX_Text(pDX, IDC_EDIT3, m_findStr);
	DDX_Control(pDX, IDC_EDIT4, m_changeFile);
	DDX_Control(pDX, IDC_EDIT5, m_methodName);
}

BEGIN_MESSAGE_MAP(CmyTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CmyTestDlg::OnBnClickedOk)
	
	ON_BN_CLICKED(IDCANCEL, &CmyTestDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_RADIO1, &CmyTestDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CmyTestDlg::OnBnClickedRadio2)
END_MESSAGE_MAP()


// CmyTestDlg message handlers

BOOL CmyTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

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

	CButton* pButton1 = (CButton*)GetDlgItem(IDC_RADIO1);
	pButton1->SetCheck(1);

	CStatic *pStatic = (CStatic *)GetDlgItem(IDC_STATIC4);
	
	pStatic->ShowWindow(0);

	m_methodName.ShowWindow(0);

	m_classChecked = 1;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CmyTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CmyTestDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CmyTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CmyTestDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	TCHAR szDirectory[MAX_PATH] = L"";
	::GetCurrentDirectory(sizeof(szDirectory)-1, szDirectory);

	
	CStdioFile file; 

	CString sWindowText;
	m_changeFile.GetWindowText(sWindowText);
	
	file.Open(CString(szDirectory) + "\\" + sWindowText, CFile::modeReadWrite | CFile::typeText | CFile::shareDenyNone);

	
	CString m_readStr, chLine;

	file.SeekToBegin();
	//Get each lines from the file
	while (file.ReadString(chLine))
	{
		m_readStr += chLine;
		m_readStr += "\n";
	}
	

	if (m_readStr.GetLength() == 0) {

		AfxMessageBox(L"You must specify the text.");
		return;
	}

	
	if (m_classChecked)
	{
		
		m_readStr.Replace(m_replaceStr , m_findStr );

		file.Seek(0, CStdioFile::begin);
	    file.WriteString(m_readStr);
	}
	else
	{
		CString mWindowText;
		m_methodName.GetWindowText(mWindowText);

		m_readStr.Replace(m_replaceStr + "::" + mWindowText , m_findStr + "::" + mWindowText);

		file.Seek(0, CStdioFile::begin);
		file.WriteString(m_readStr);
		
	}
		
	file.Close();

	UpdateData(FALSE);

}




void CmyTestDlg::OnBnClickedCancel()
{
	
	CDialog::OnOK();
}


void CmyTestDlg::OnBnClickedRadio1()
{
	CStatic *pStatic = (CStatic *)GetDlgItem(IDC_STATIC2);
	pStatic->SetWindowText(L"Old Class Name");

	pStatic = (CStatic *)GetDlgItem(IDC_STATIC3);
	pStatic->SetWindowText(L"New Class Name");

	pStatic = (CStatic *)GetDlgItem(IDC_STATIC4);
	pStatic->ShowWindow(0);

	m_methodName.ShowWindow(0);

	CButton *pButton = (CButton *)GetDlgItem(IDOK);
	pButton->SetWindowText(L"Replace");
	
	m_classChecked = 1;
	// TODO: Add your control notification handler code here
}


void CmyTestDlg::OnBnClickedRadio2()
{
	CStatic *pStatic = (CStatic *)GetDlgItem(IDC_STATIC2);
	pStatic->SetWindowText(L"Before Move Class Name");

	pStatic = (CStatic *)GetDlgItem(IDC_STATIC3);
	pStatic->SetWindowText(L"After Move Class Name");

	pStatic = (CStatic *)GetDlgItem(IDC_STATIC4);
	pStatic->ShowWindow(1);

	m_methodName.ShowWindow(1);

	CButton *pButton = (CButton *)GetDlgItem(IDOK);
	pButton->SetWindowText(L"Move");

	m_classChecked = 0;
	// TODO: Add your control notification handler code here
}
