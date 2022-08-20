// ClientSocket.cpp : implementation file
//

#include "stdafx.h"
#include "CDNSCli.h"
#include "ClientSocket.h"
#include <afxpriv.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClientSocket

CClientSocket::CClientSocket()
{
	m_hSocket = INVALID_SOCKET; //default to an invalid scoket descriptor
}

CClientSocket::~CClientSocket()
{
	Close();
}


/////////////////////////////////////////////////////////////////////////////
// CClientSocket member functions

BOOL CClientSocket::IsReadible(BOOL &bReadible)
/*
Routine Description:
	Determines if the readability of this socket.

Parameters:
	bReadible	Determines if socket has data.

Return Value:
	If the socket is readible, return TRUE; Otherwise, return FALSE.
*/
{
	// The timeout value.
	timeval timeout = {0, 0};

	// Fill the needed parameter.
	fd_set fds;
	FD_ZERO(&fds);
	FD_SET(m_hSocket, &fds);

	// Are there any socket readible?
	// Use 0 as timeout means return immediately.
	int nStatus = select(0, &fds, NULL, NULL, &timeout);

	if (nStatus == SOCKET_ERROR)
	{
		return FALSE;
	}
	else
	{
		bReadible = !(nStatus == 0);
		return TRUE;
	}
}

BOOL CClientSocket::Create()
{
	m_hSocket = socket(AF_INET, SOCK_STREAM, 0);
	return (m_hSocket != INVALID_SOCKET);
}

BOOL CClientSocket::Connect(LPCTSTR pszHostAddress, int nPort)
{
	//For correct operation of the T2A macro, see MFC Tech Note 59
	USES_CONVERSION;
	
	//must have been created first
	ASSERT(m_hSocket != INVALID_SOCKET);
	
	LPSTR lpszAscii = T2A((LPTSTR)pszHostAddress);
	
	//Determine if the address is in dotted notation
	SOCKADDR_IN sockAddr;
	ZeroMemory(&sockAddr, sizeof(sockAddr));
	sockAddr.sin_family = AF_INET;
	sockAddr.sin_port = htons((u_short)nPort);
	sockAddr.sin_addr.s_addr = inet_addr(lpszAscii);
	
	//If the address is not dotted notation, then do a DNS 
	//lookup of it.
	if (sockAddr.sin_addr.s_addr == INADDR_NONE)
	{
		LPHOSTENT lphost;
		lphost = gethostbyname(lpszAscii);
		if (lphost != NULL)
			sockAddr.sin_addr.s_addr = ((LPIN_ADDR)lphost->h_addr)->s_addr;
		else
		{
//			WSASetLastError(WSAEINVAL); 
			return FALSE;
		}
	}
	
	//Call the protected version which takes an address 
	//in the form of a standard C style struct.
	return Connect((SOCKADDR*)&sockAddr, sizeof(sockAddr));
}

BOOL CClientSocket::Send(LPCSTR pszBuf, int nBuf)
{
	//must have been created first
	ASSERT(m_hSocket != INVALID_SOCKET);
	
	return (send(m_hSocket, pszBuf, nBuf, 0) != SOCKET_ERROR);
}

void CClientSocket::Close()
{
	if (m_hSocket != INVALID_SOCKET)
	{
		VERIFY(SOCKET_ERROR != closesocket(m_hSocket));
		m_hSocket = INVALID_SOCKET;
	}
}

int CClientSocket::Receive(LPSTR pszBuf, int nBuf)
{
	//must have been created first
	ASSERT(m_hSocket != INVALID_SOCKET);
	
	return recv(m_hSocket, pszBuf, nBuf, 0); 
}

BOOL CClientSocket::Connect(const SOCKADDR *lpSockAddr, int nSockAddrLen)
{
	return (connect(m_hSocket, lpSockAddr, nSockAddrLen) != SOCKET_ERROR);
}
