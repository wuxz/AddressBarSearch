// CDNSServer.h : main header file for the CDNSSERVER application
//

#if !defined(AFX_CDNSSERVER_H__9299B2E4_9823_11D3_A7FE_0080C8763FA4__INCLUDED_)
#define AFX_CDNSSERVER_H__9299B2E4_9823_11D3_A7FE_0080C8763FA4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CCDNSServerApp:
// See CDNSServer.cpp for the implementation of this class
//

class CCDNSServerApp : public CWinApp
{
public:
	CCDNSServerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCDNSServerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CCDNSServerApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CDNSSERVER_H__9299B2E4_9823_11D3_A7FE_0080C8763FA4__INCLUDED_)
