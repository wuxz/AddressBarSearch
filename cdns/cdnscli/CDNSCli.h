// CDNSCli.h : main header file for the CDNSCli application
//

#if !defined(AFX_CDNSCli_H__1A905BC5_929F_11D3_A7FE_0080C8763FA4__INCLUDED_)
#define AFX_CDNSCli_H__1A905BC5_929F_11D3_A7FE_0080C8763FA4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CCDNSCliApp:
// See CDNSCli.cpp for the implementation of this class
//

class CCDNSCliApp : public CWinApp
{
public:
	CCDNSCliApp();

protected:
	// Atom indicates if our program is running already.
	ATOM m_atom;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCDNSCliApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CCDNSCliApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CDNSCli_H__1A905BC5_929F_11D3_A7FE_0080C8763FA4__INCLUDED_)
