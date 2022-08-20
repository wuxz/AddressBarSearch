#if !defined(AFX_REQUESTSOCKET_H__9299B2F6_9823_11D3_A7FE_0080C8763FA4__INCLUDED_)
#define AFX_REQUESTSOCKET_H__9299B2F6_9823_11D3_A7FE_0080C8763FA4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RequestSocket.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CRequestSocket command target
#define BUFFERSIZE 1024

class CCDNSServerSet;

class CRequestSocket : public CAsyncSocket
{
// Attributes
public:

// Operations
public:
	CRequestSocket(CCDNSServerSet * pSet);
	virtual ~CRequestSocket();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRequestSocket)
	public:
	virtual void OnClose(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	virtual void OnSend(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CRequestSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
	void SearchText();
	// The buffer contains the data to be sent.
	char m_pBuf[BUFFERSIZE];

	// The bytes to be sent.
	int m_nBufLen;

	// The rowset pointer;
	CCDNSServerSet * m_pSet;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REQUESTSOCKET_H__9299B2F6_9823_11D3_A7FE_0080C8763FA4__INCLUDED_)
