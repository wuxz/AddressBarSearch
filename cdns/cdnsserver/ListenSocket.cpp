// ListenSocket.cpp : implementation file
//

#include "stdafx.h"
#include "CDNSServer.h"
#include "ListenSocket.h"
#include "requestsocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListenSocket

CListenSocket::CListenSocket(CCDNSServerSet * pSet)
{
	m_pSet = pSet;
}

CListenSocket::~CListenSocket()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CListenSocket, CAsyncSocket)
	//{{AFX_MSG_MAP(CListenSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CListenSocket member functions

void CListenSocket::OnAccept(int nErrorCode) 
/*
Routine Description:
	Called by the framework to notify a listening socket that it can 
	accept pending connection requests by calling the Accept member 
	function.

	Here, we create a new CRequestSocket object and let it to do the
	rest work.

Parameters:
	nErrorCode
	
		The most recent error on a socket. The following error codes 
		applies to the OnAccept member function: 

		0	The function executed successfully.

		WSAENETDOWN		The Windows Sockets implementation detected that 
		the network subsystem failed. 

Return Value:
	None.
*/
{
	// Create a new request socket each time OnAccept.
	CRequestSocket* pRequest = new CRequestSocket(m_pSet);

	// Accept this socket.
	if (Accept(*pRequest))
	{
		// Let the system notify the request socket when it's ready
		// for reading or closing.
		pRequest->AsyncSelect( FD_READ|FD_CLOSE );
	}
	
	CAsyncSocket::OnAccept(nErrorCode);
}
