#if !defined(AFX_LISTENSOCKET_H__9299B2F5_9823_11D3_A7FE_0080C8763FA4__INCLUDED_)
#define AFX_LISTENSOCKET_H__9299B2F5_9823_11D3_A7FE_0080C8763FA4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ListenSocket.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CListenSocket command target
class CCDNSServerSet;

class CListenSocket : public CAsyncSocket
{
// Attributes
public:

// Operations
public:
	CListenSocket(CCDNSServerSet * pSet);
	virtual ~CListenSocket();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListenSocket)
	public:
	virtual void OnAccept(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CListenSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
	// The rowset pointer;
	CCDNSServerSet * m_pSet;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTENSOCKET_H__9299B2F5_9823_11D3_A7FE_0080C8763FA4__INCLUDED_)
