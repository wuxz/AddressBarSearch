// OptionsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "cDNSCli.h"
#include "OptionsDlg.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COptionsDlg dialog


void AFXAPI DDV_Proxy(CDataExchange* pDX, CString const& value)
{
	LPCTSTR strValue = value;

	for (UINT i = 0; i < strlen(strValue); i ++)
	{
		// Can not contain chinese character.
		if (strValue[i] < 0)
		{
			CString prompt;
			prompt.LoadString(IDS_INVALIDPROXY);
			AfxMessageBox(prompt, MB_ICONEXCLAMATION, MB_OK);
			pDX->Fail();
		}
	}
}

COptionsDlg::COptionsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COptionsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(COptionsDlg)
	//}}AFX_DATA_INIT
	m_pMainFrame = NULL;
}


void COptionsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COptionsDlg)
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_EDIT_TIMEOUT, m_pMainFrame->m_nTimeout);
	DDV_MinMaxInt(pDX, m_pMainFrame->m_nTimeout, 3, 30);

	DDX_Radio(pDX, IDC_RADIO_USEFIRST, m_pMainFrame->m_nMultiChoose);

	DDX_Check(pDX, IDC_CHECK_USEPROXY, m_pMainFrame->m_bUseProxy);

	DDX_CBString(pDX, IDC_COMBO_PROXY, m_pMainFrame->m_strProxy);
	DDV_Proxy(pDX, m_pMainFrame->m_strProxy);

	DDX_Text(pDX, IDC_EDIT_CONNECT_TIMEOUT, m_pMainFrame->m_nConnectTimeout);
	DDV_MinMaxInt(pDX, m_pMainFrame->m_nConnectTimeout, 3, 30);

	DDX_Text(pDX, IDC_EDIT_CONNECT_PORT, m_pMainFrame->m_nProxyPort);
	DDV_MinMaxInt(pDX, m_pMainFrame->m_nProxyPort, 1, 65536);

	if (!pDX->m_bSaveAndValidate)
	{
		if (m_pMainFrame->m_nMultiChoose)
			OnRadioLetmechoose();
		else
			OnRadioUsefirst();
	}
}


BEGIN_MESSAGE_MAP(COptionsDlg, CDialog)
	//{{AFX_MSG_MAP(COptionsDlg)
	ON_BN_CLICKED(IDC_RADIO_LETMECHOOSE, OnRadioLetmechoose)
	ON_BN_CLICKED(IDC_RADIO_USEFIRST, OnRadioUsefirst)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptionsDlg message handlers

void COptionsDlg::OnRadioLetmechoose() 
{
	GetDlgItem(IDC_EDIT_TIMEOUT)->EnableWindow();	
	GetDlgItem(IDC_SPIN_TIMEOUT)->EnableWindow();	
}

void COptionsDlg::OnRadioUsefirst() 
{
	GetDlgItem(IDC_EDIT_TIMEOUT)->EnableWindow(FALSE);	
	GetDlgItem(IDC_SPIN_TIMEOUT)->EnableWindow(FALSE);	
}
