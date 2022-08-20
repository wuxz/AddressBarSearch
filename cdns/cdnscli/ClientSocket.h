#if !defined(AFX_CLIENTSOCKET_H__7FD85F8F_9779_11D3_A7FE_0080C8763FA4__INCLUDED_)
#define AFX_CLIENTSOCKET_H__7FD85F8F_9779_11D3_A7FE_0080C8763FA4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ClientSocket.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CClientSocket command target

class CClientSocket
{
// Attributes
public:

// Operations
public:
	CClientSocket();
	virtual ~CClientSocket();

// Overrides
public:
	int Receive(LPSTR pszBuf, int nBuf);
	void Close();
	BOOL Send(LPCSTR pszBuf, int nBuf);
	BOOL Connect(LPCTSTR pszHostAddress, int nPort = 110);
	BOOL Create();
	BOOL IsReadible(BOOL& bReadible);
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientSocket)
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CClientSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
	BOOL Connect(const SOCKADDR* lpSockAddr, int nSockAddrLen);
	SOCKET m_hSocket;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENTSOCKET_H__7FD85F8F_9779_11D3_A7FE_0080C8763FA4__INCLUDED_)
