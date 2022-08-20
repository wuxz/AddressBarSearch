// CDNSServerView.cpp : implementation of the CCDNSServerView class
//

#include "stdafx.h"
#include "CDNSServer.h"

#include "CDNSServerSet.h"
#include "CDNSServerDoc.h"
#include "CDNSServerView.h"
#include "listensocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCDNSServerView

IMPLEMENT_DYNCREATE(CCDNSServerView, COleDBRecordView)

BEGIN_MESSAGE_MAP(CCDNSServerView, COleDBRecordView)
	//{{AFX_MSG_MAP(CCDNSServerView)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCDNSServerView construction/destruction

CCDNSServerView::CCDNSServerView()
	: COleDBRecordView(CCDNSServerView::IDD)
{
	//{{AFX_DATA_INIT(CCDNSServerView)
	m_pSet = NULL;
	//}}AFX_DATA_INIT

	m_pListen = NULL;
}

CCDNSServerView::~CCDNSServerView()
{
	StopListening();
}

void CCDNSServerView::DoDataExchange(CDataExchange* pDX)
{
	COleDBRecordView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCDNSServerView)
	//}}AFX_DATA_MAP
}

BOOL CCDNSServerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return COleDBRecordView::PreCreateWindow(cs);
}

void CCDNSServerView::OnInitialUpdate()
{
	m_pSet = &GetDocument()->m_cDNSServerSet;
	{
		CWaitCursor wait;
		HRESULT hr = m_pSet->Open();
#ifdef _DEBUG
		if (hr != S_OK)
		{
			AfxMessageBox(_T("Record set failed to open."), MB_OK);
			// Disable the Next and Previous record commands,
			// since attempting to change the current record without an
			// open RecordSet will cause a crash.
			m_bOnFirstRecord = TRUE;
			m_bOnLastRecord = TRUE;
		}
#endif
	}

	COleDBRecordView::OnInitialUpdate();

	// Start the listening.
	StartListening();
}

/////////////////////////////////////////////////////////////////////////////
// CCDNSServerView diagnostics

#ifdef _DEBUG
void CCDNSServerView::AssertValid() const
{
	COleDBRecordView::AssertValid();
}

void CCDNSServerView::Dump(CDumpContext& dc) const
{
	COleDBRecordView::Dump(dc);
}

CCDNSServerDoc* CCDNSServerView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCDNSServerDoc)));
	return (CCDNSServerDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCDNSServerView database support
CRowset* CCDNSServerView::OnGetRowset()
{
	return m_pSet;
}


/////////////////////////////////////////////////////////////////////////////
// CCDNSServerView message handlers

void CCDNSServerView::StopListening()
/*
Routine Description:
	Stop the listening socket.

Parameters:
	None.

Return value:
	None.
*/
{
	if (m_pListen != NULL)
	{
		m_pListen->Close();
		delete m_pListen;
		m_pListen = NULL;
	}
}

BOOL CCDNSServerView::StartListening()
/*
Routine Description:
	Start the listening process.

Parameters:
	None.

Return value:
	If successes, return TRUE; Otherwise, return FALSE.
*/
{
	// If we are succeeded.
	BOOL bRet = FALSE;

	// Stop the ongoing listen first, if any.
	StopListening();

	// Create the new listening socket.
	m_pListen = new CListenSocket(m_pSet);

	if (m_pListen)
	{
		// Create the socket.
		if (m_pListen->Create(21234, SOCK_STREAM, FD_ACCEPT))
			// Listen
			bRet = m_pListen->Listen();

		if (!bRet)
		{
			CString strMsg;
			int nErr = m_pListen->GetLastError();

			if ( nErr == WSAEADDRINUSE )
				// Port is being used.
				strMsg = _T("Port 1234 is already in use");
			else
				strMsg = _T("Can't listen to port 1234");

			AfxMessageBox(strMsg, MB_OK|MB_ICONSTOP);
			m_pListen->Close();
			delete m_pListen;
			m_pListen = NULL;
		}
	}
	else
		AfxMessageBox(_T("Can't listen"), MB_OK|MB_ICONSTOP );

	return bRet;
}
