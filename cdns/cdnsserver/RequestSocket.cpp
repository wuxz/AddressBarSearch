// RequestSocket.cpp : implementation file
//

#include "stdafx.h"
#include "CDNSServer.h"
#include "RequestSocket.h"
#include "CDNSServerSet.h"
#include <afxpriv.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRequestSocket

CRequestSocket::CRequestSocket(CCDNSServerSet * pSet)
{
	m_pSet = pSet;

	ZeroMemory(m_pBuf, BUFFERSIZE);
	m_nBufLen = 0;
}

CRequestSocket::~CRequestSocket()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CRequestSocket, CAsyncSocket)
	//{{AFX_MSG_MAP(CRequestSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CRequestSocket member functions

void CRequestSocket::OnClose(int nErrorCode) 
/*
Routine Description:
	Called by the framework to notify this socket that the connected 
	socket is closed by its process.

Parameters:
	nErrorCode
  
	The most recent error on a socket. The following error codes apply 
	to the OnClose member function: 
	
	0	The function executed successfully.
	  
	WSAENETDOWN		The Windows Sockets implementation detected that 
	the network subsystem failed.
		
	WSAECONNRESET	The connection was reset by the remote side.
		  
	WSAECONNABORTED	The connection was aborted due to timeout or 
	other failure. 
			
Return Value:
	None.
*/
{
	// The socket is closed, delete this pointer allocated by "new"
	// operator.
	delete this;
}

void CRequestSocket::OnReceive(int nErrorCode)
/*
Routine Description:
	Called by the framework to notify this socket that there is data 
	in the buffer that can be retrieved by calling the Receive member 
	function. 

Parameters:
	nErrorCode
  
	The most recent error on a socket. The following error codes 
	apply to the OnReceive member function: 
	
	0	The function executed successfully.
	  
	WSAENETDOWN		The Windows Sockets implementation detected that 
	the network subsystem failed. 
		
Return Value:
	None.
*/
{
	// Reset the buffer;
	ZeroMemory(m_pBuf, BUFFERSIZE);
	m_nBufLen = 0;

	// get the bytes....
	int nBytes = Receive(m_pBuf, BUFFERSIZE - 1);

	if (nBytes != SOCKET_ERROR)
	{
		// We get incoming data now.

		// The header should be "CDNS:".
		if (nBytes <= 10 || memcmp(m_pBuf, "GET /CDNS:", 10))
			return;

		// Send my data back;
		SearchText();

		// I am ready for sending data out.
		AsyncSelect(FD_WRITE | FD_CLOSE);
	}
	else
		nBytes = GetLastError();
}

void CRequestSocket::OnSend(int nErrorCode) 
/*
Routine Description:
	Called by the framework to notify the socket that it can now send 
	data by calling the Send member function.

Parameters:
	nErrorCode

		The most recent error on a socket. The following error codes 
		apply to the OnSend member function: 

		0   The function executed successfully.

		WSAENETDOWN   The Windows Sockets implementation detected that 
		the network subsystem failed. 

Return Value:
	None.
*/
{
	if (m_nBufLen == 0)
	{
		// No data to be sent.
		// We should wait.
//		AsyncSelect(FD_WRITE | FD_CLOSE);

		return;
	}

	// The bytes sent out.
	int nBytes = Send(m_pBuf, m_nBufLen);

	if (nBytes == SOCKET_ERROR)
	{
		if (GetLastError() != WSAEWOULDBLOCK)
		{
			ShutDown(both);
			delete this;
		}
//		else
			// We should wait.
//			AsyncSelect(FD_WRITE | FD_CLOSE);
	}
	else if (nBytes < m_nBufLen)
	{
		// still got some left.

		// Update the left length.
		m_nBufLen -= nBytes;

		// Move the rest data to head.
		MoveMemory(m_pBuf, m_pBuf + nBytes, m_nBufLen);

		// set up for next write.
//		AsyncSelect( FD_WRITE | FD_CLOSE );
	}
	else
	{
		// There is no data left.

		ZeroMemory(m_pBuf, BUFFERSIZE);
		m_nBufLen = 0;

		ShutDown(both);
	}
}

void CRequestSocket::SearchText()
/*
Routine Description:
	Search the text in m_pBuf, fill m_pBuf with the result address and
	private information.

Parameters:
	None.

Return Value:
	None.
*/
{
	USES_CONVERSION;

	// The text to search;
	TCHAR strText[1024] = _T("");

	sscanf(m_pBuf + 10, "%s", strText);
	strText[1023] = 0;
	
	// The result text;
	// 200 is the success code.
	CString strResult = "200";

	HRESULT hr = m_pSet->Open(strText);

	while (hr == S_OK)
	{
		strResult += m_pSet->m_Address;
		strResult += "\t";
		hr = m_pSet->MoveNext();
	}

	// The end sign.
	strResult += "\n";

	// Copy the result string into m_pBuf.
	strcpy(m_pBuf, strResult.Left(1022));

	// We should also send a '\0'.
	m_nBufLen = strlen(m_pBuf) + 1;
}
