// CDNSCli.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "CDNSCli.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define ATOMNAME _T("Chinese DNS")

/////////////////////////////////////////////////////////////////////////////
// CCDNSCliApp

BEGIN_MESSAGE_MAP(CCDNSCliApp, CWinApp)
	//{{AFX_MSG_MAP(CCDNSCliApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCDNSCliApp construction

CCDNSCliApp::CCDNSCliApp()
{
	m_atom = NULL;
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CCDNSCliApp object

CCDNSCliApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CCDNSCliApp initialization

BOOL CCDNSCliApp::InitInstance()
{
/*	
	// Atom exits, which means that this is one instance running, so
	// exit.
	if (GlobalFindAtom(ATOMNAME))
		return FALSE;

	// Register our instance with atom.
	m_atom = GlobalAddAtom(ATOMNAME);
	if (!m_atom)
		return FALSE;
*/
	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	SetRegistryKey(_T("BHM"));

	LoadStdProfileSettings(0);  // Load standard INI file options (including MRU)

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
//	if (!ProcessShellCommand(cmdInfo))
//		return FALSE;

	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CCDNSCliApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CCDNSCliApp message handlers


int CCDNSCliApp::ExitInstance() 
{
	if (m_atom)
		GlobalDeleteAtom(m_atom);

	return CWinApp::ExitInstance();
}
