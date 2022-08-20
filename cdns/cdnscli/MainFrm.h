// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__1A905BC9_929F_11D3_A7FE_0080C8763FA4__INCLUDED_)
#define AFX_MAINFRM_H__1A905BC9_929F_11D3_A7FE_0080C8763FA4__INCLUDED_

#include "SystemTray.h"	// Added by ClassView
#include "ClientSocket.h"	// Added by ClassView

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMainFrame : public CFrameWnd
{
	
public:
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	void RegisterHost(hostent * pHost);
	
	// The handler for search message.
	LRESULT OnSearch(long wParam, long lParam);

	// Find the address.
	void SearchCDNS(WCHAR * pText);

	// Process the response.
	void ProcessAddress(char * pszBuffer, CString& strResult);

	// Read the response from host.
	BOOL ReadResponse(int nExpectedCode, char * pszBuffer);

	// Send the request out.
	BOOL SendMsg(CString& pszMsg);

	// Disconnect from the host.
	BOOL Disconnect();

	// Connect to the host.
	BOOL Connect();

protected:
	// The tray icon object.
	CSystemTray m_TrayIcon;

	// If the service is started.
	BOOL m_bStarted;

	// Tha shared file mapping handles.
	HANDLE m_hShareMap, m_hShareIPMap;

	// The action when find multiple address.
	int m_nMultiChoose;

	// The timeout seconds before the user choose one address from
	// multiple result address.
	int m_nTimeout, m_nConnectTimeout;

	// The socket object.
	CClientSocket m_Sock;

	// If we are connected to server.
	BOOL m_bConnected;

	// The proxy server.
	CString m_strProxy;

	// The port of proxy server.
	UINT m_nProxyPort;

	// If we use proxy server.
	BOOL m_bUseProxy;

	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTrayStart();
	afx_msg void OnUpdateTrayStart(CCmdUI* pCmdUI);
	afx_msg void OnTrayOptions();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	friend class COptionsDlg;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__1A905BC9_929F_11D3_A7FE_0080C8763FA4__INCLUDED_)
