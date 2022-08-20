// ChooseAddrDlg.cpp : implementation file
//

#include "stdafx.h"
#include "cDNSCli.h"
#include "ChooseAddrDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChooseAddrDlg dialog


CChooseAddrDlg::CChooseAddrDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChooseAddrDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChooseAddrDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_nTimer = NULL;
}


void CChooseAddrDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChooseAddrDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChooseAddrDlg, CDialog)
	//{{AFX_MSG_MAP(CChooseAddrDlg)
	ON_WM_TIMER()
	ON_LBN_DBLCLK(IDC_LIST_ADDRESS, OnDblclkListAddress)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChooseAddrDlg message handlers

BOOL CChooseAddrDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// Init the list box.
	CListBox * pList = (CListBox *)GetDlgItem(IDC_LIST_ADDRESS);
	pList->ResetContent();

	for (int i = 0; i < m_arAddr.GetSize(); i ++)
		pList->AddString(m_arAddr[i]);

	pList->SetCurSel(0);

	// Show the window.
	SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
	SetForegroundWindow();

	// Start the timeout timer.
	m_nTimer = SetTimer(0x1234, m_nTimeout * 1000, NULL);
	if (!m_nTimer)
		return FALSE;

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CChooseAddrDlg::OnOK() 
{
	m_nSel = ((CListBox *)GetDlgItem(IDC_LIST_ADDRESS))->GetCurSel();
	
	CDialog::OnOK();
}

void CChooseAddrDlg::OnTimer(UINT nIDEvent) 
{
	if (nIDEvent == m_nTimer)
		OnCancel();

	CDialog::OnTimer(nIDEvent);
}

BOOL CChooseAddrDlg::DestroyWindow() 
{
	if (m_nTimer)
	{
		KillTimer(m_nTimer);
		m_nTimer = NULL;
	}

	return CDialog::DestroyWindow();
}

void CChooseAddrDlg::OnDblclkListAddress() 
{
	// Double click means choosing ok.
	OnOK();	
}
