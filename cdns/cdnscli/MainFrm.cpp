// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "CDNSCli.h"

typedef DWORD* DWORD_PTR;
#include <afxinet.h>

#include <afxpriv.h>
#include <shlobj.h>
#include "\wxz\bhmnsp\export.h"

#include "MainFrm.h"
#include "chooseaddrdlg.h"
#include "optionsdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// The icon notify message.
#define	WM_ICON_NOTIFY			WM_USER+10

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

// The customized search message.
const UINT WM_SEARCH = RegisterWindowMessage(_T("SearchCDNS"));
#define ADDRESSMAP _T("CDNSFileMapping")
#define IPMAP _T("CDNSFileMapping_IP")

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_TRAY_START, OnTrayStart)
	ON_UPDATE_COMMAND_UI(ID_TRAY_START, OnUpdateTrayStart)
	ON_COMMAND(ID_TRAY_OPTIONS, OnTrayOptions)
	//}}AFX_MSG_MAP
	ON_REGISTERED_MESSAGE(WM_SEARCH, OnSearch)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	m_bStarted = FALSE;	
	m_hShareMap = NULL;
	m_hShareIPMap = NULL;

	m_bConnected = FALSE;
}

CMainFrame::~CMainFrame()
{
	// Clear the window handle.
	SetHWnd(NULL);

	// Disconnect from server.
	if (m_bConnected)
		Disconnect();

	// Close the file mapping.
	if (m_hShareMap)
		CloseHandle(m_hShareMap);

	if (m_hShareIPMap)
		CloseHandle(m_hShareIPMap);

	CWinApp * pApp = AfxGetApp();
	pApp->WriteProfileInt(
		_T("Chinese Address"),
		_T("Multiple Address Choose"),
		m_nMultiChoose
		);

	pApp->WriteProfileInt(
		_T("Chinese Address"),
		_T("Timeout"),
		m_nTimeout
		);


	pApp->WriteProfileInt(
		_T("Chinese Address"),
		_T("UseProxy"),
		m_bUseProxy
		);


	pApp->WriteProfileString(
		_T("Chinese Address"),
		_T("Proxy"),
		m_strProxy
		);


	pApp->WriteProfileInt(
		_T("Chinese Address"),
		_T("Proxy Port"),
		m_nProxyPort
		);

	pApp->WriteProfileInt(
		_T("Chinese Address"),
		_T("Connect Timeout"),
		m_nConnectTimeout
		);
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// Create the tray icon
	if (!m_TrayIcon.Create(
		NULL, // Parent window
		WM_ICON_NOTIFY,	// Icon notify message to use
		_T("Chinese Address"), // tooltip
		LoadIcon(NULL, IDI_ASTERISK), // Icon to use
		IDR_MENU_TRAY) // ID of tray icon
		)
		return -1;

	// Set the default menu item to start/end command.
	m_TrayIcon.SetMenuDefaultItem(ID_TRAY_START, FALSE);

	// Create the file mapping for share memory.
	m_hShareMap = CreateFileMapping(
		INVALID_HANDLE_VALUE,
		NULL,
		PAGE_READWRITE, 
		0,
		255,
		ADDRESSMAP
		);

	if (!m_hShareMap)
	{
		// Failed to create file mapping.
		AfxMessageBox("Failed to create shared memory");
		return -1;
	}

	m_hShareIPMap = CreateFileMapping(
		INVALID_HANDLE_VALUE,
		NULL,
		PAGE_READWRITE, 
		0,
		1024,
		IPMAP
		);

	if (!m_hShareIPMap)
	{
		// Failed to create file mapping.
		AfxMessageBox("Failed to create shared memory");
		return -1;
	}

	CWinApp * pApp = AfxGetApp();
	m_nMultiChoose = pApp->GetProfileInt(
		_T("Chinese Address"),
		_T("Multiple Address Choose"),
		0
		);

	m_nTimeout = pApp->GetProfileInt(
		_T("Chinese Address"),
		_T("Timeout"),
		10
		);

	m_bUseProxy = pApp->GetProfileInt(
		_T("Chinese Address"),
		_T("UseProxy"),
		0
		);

	m_strProxy = pApp->GetProfileString(
		_T("Chinese Address"),
		_T("Proxy"),
		""
		);

	m_nProxyPort = pApp->GetProfileInt(
		_T("Chinese Address"),
		_T("Proxy Port"),
		80
		);

	m_nConnectTimeout = pApp->GetProfileInt(
		_T("Chinese Address"),
		_T("Connect Timeout"),
		10
		);

	OnTrayStart();

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


void CMainFrame::OnTrayStart() 
/*
Routine Description:
	Handle the start/stop command.
	If the command is "Start", then start the service, otherwise stop
	the service.

Parameters:
	None.

Return value:
	none.
*/
{
	if (m_bStarted)
	{
		// The service is stopped.
		m_bStarted = FALSE;
		
		// Clear the window handle to prevent the NSP from searching.
		SetHWnd(NULL);

		// Modify the icon to represent the change.
		m_TrayIcon.SetIcon(LoadIcon(NULL, IDI_HAND));
	}
	else
	{
		// The service is started.
		m_bStarted = TRUE;

		// Set the window handle to allow the NSP from searching.
		SetHWnd(m_hWnd);

		// Modify the icon to represent the change.
		m_TrayIcon.SetIcon(LoadIcon(NULL, IDI_ASTERISK));
	}
}

void CMainFrame::SearchCDNS(WCHAR *pText)
/*
Routine Description:
	Search the correspond english address according to the chinese
	string in pText.

Parameters:
	pText		The WCHAR string which containes the chinese net address.

Return value:
	None.
*/
{
	USES_CONVERSION;

	// The buffer to receive the response.
	char pszBuffer[1024];
	
	CString strResult;

	CString strMsg = W2A(pText);
	wcscpy(pText, L"");

	// Send the message to host.
	if (!SendMsg(strMsg))
		goto exit;

	//check the response to the request
	if (!ReadResponse(200, pszBuffer))
		goto exit;

	ProcessAddress(pszBuffer, strResult);
		
	wcscpy(pText, T2W(strResult));

exit:
	
	// Disconnect from server;
	Disconnect();
}

LRESULT CMainFrame::OnSearch(long wParam, long lParam)
/*
Routine Description:
	The handler for search message.

Parameters:
	wParam		Not used.
	lParam		Not used.

Return value:
	Always return 0L.
*/
{
	if (!m_hShareMap)
		return 0L;

	WCHAR * pText = (WCHAR *)MapViewOfFile(
		m_hShareMap,
		FILE_MAP_ALL_ACCESS,
		0,
		0,
		0
		);
 
	if (!pText)
		return 0L;

	// pText points to the share memory.
	SearchCDNS(pText);

	return 0L;
}

void CMainFrame::OnUpdateTrayStart(CCmdUI* pCmdUI) 
/*
Routine Descripiton:
	Update the checked status of "Start" menu item.

Parameters:
	pCmdUI		The pointer containes the command UI data to be changed.

Return Value:
	None.
*/
{
	// If the menu pointer is not NULL, update the checked status.
	if (pCmdUI->m_pMenu)
		pCmdUI->m_pMenu->CheckMenuItem(
			ID_TRAY_START,
			MF_BYCOMMAND | (m_bStarted ? MF_CHECKED : MF_UNCHECKED)
			);
}

void CMainFrame::OnTrayOptions() 
{
	// Create options dialog;
	COptionsDlg dlg;
	dlg.m_pMainFrame = this;

	dlg.DoModal();

	m_strProxy.TrimLeft();
	m_strProxy.TrimRight();
}

void CMainFrame::RegisterHost(hostent *pHost)
{
	// Access the shared memory.
	if (!m_hShareIPMap)
		return;

	char * pIP = (char *)MapViewOfFile(
		m_hShareIPMap,
		FILE_MAP_ALL_ACCESS,
		0,
		0,
		0
		);

	// If the given IP address already exist, just return.
	for (int i = 0; i <= 1020; i += 4)
	{
		if (
			*(DWORD *)(pIP + i) == *(DWORD *)pHost->h_addr_list[0]
			)
			return;
	}

	// Looking for a empty entry.
	for (i = 0; i <= 1020; i += 4)
	{
		if (*(DWORD *)(pIP + i) == 0)
			break;
	}

	// If the register table is full, write the new data at the begin.
	if (i > 1020)
		i = 0;

	// Write the IP address into table.
	memcpy(pIP + i, pHost->h_addr_list[0], 4);
}

BOOL CMainFrame::Connect()
/*
Routine Description:
	Connect to the server.

Parameters:
	None.

Return Value:
	If succeeded, return TRUE; Otherwise, return FALSE;
*/
{
	//Create the socket
	if (!m_Sock.Create())
		return FALSE;
	
	//Connect to the host or proxy server.
	if (m_bUseProxy && m_strProxy.GetLength())
	{
		if (!m_Sock.Connect(m_strProxy, m_nProxyPort))
			return FALSE;
	}
	else
	{
		if (!m_Sock.Connect(_T("202.99.11.10"), 21234))
			return FALSE;
	}

	//We're now connected !!
	m_bConnected = TRUE;
		
	return TRUE;
}

BOOL CMainFrame::Disconnect()
/*
Routine Description:
	Disconnect from the server.

Parameters:
	None.

Return Value:
	If succeeded, return TRUE; Otherwise, return FALSE.
*/
{
	//disconnect from the server if connected 
	if (m_bConnected)
	{
		//Reset all the state variables
		m_bConnected = FALSE;
	}
	
	//free up our socket
	m_Sock.Close();
	
	return TRUE;
}

BOOL CMainFrame::SendMsg(CString& strMsg)
/*
Routine Description:
	Send the request out, then read the feedback.

Parameters:
	None.

Return Value:
	If succeeded, return TRUE; Otherwise, return FALSE;
*/
{
	if (strMsg.IsEmpty())
		return FALSE;

	if (!m_bConnected && !Connect())
		return FALSE;

	//paramater validity checking
	ASSERT(m_bConnected); //Must be connected to send a message

	CString strMessage = "GET ";
	
	if (m_bUseProxy && m_strProxy.GetLength())
		strMessage += "http://202.99.11.10:21234";
	
	strMessage += "/CDNS:";

	strMessage += strMsg;
	strMessage += "\r\n";
	if (!m_Sock.Send(strMessage, strlen(strMessage)))
		return FALSE;

	return TRUE;
}

BOOL CMainFrame::ReadResponse(int nExpectedCode, char * pszBuffer)
{
	ZeroMemory(pszBuffer, 1024);

	//must have been created first
	ASSERT(m_bConnected);

	//retrieve the reponse using until we
	//get the terminator or a timeout occurs

	BOOL bFoundTerminator = FALSE;
	
	// The bytes received.
	int nReceived = 0;

	// The clock ticks.
	DWORD dwStartTicks = ::GetTickCount(), dwTimeout = m_nConnectTimeout * 1000;

	// The terminator.
	LPCSTR pszTerminator = "\n";
	
	while (!bFoundTerminator)
	{
		//timeout has occured
		if ((::GetTickCount() - dwStartTicks) >	dwTimeout)
		{
			pszBuffer[nReceived] = '\0';
			SetLastError(WSAETIMEDOUT);

			return FALSE;
		}
		
		//check the socket for readability
		BOOL bReadible;
		if (!m_Sock.IsReadible(bReadible))
		{
			pszBuffer[nReceived] = '\0';

			return FALSE;
		}
		else if (!bReadible) //no data to receive, just loop around
		{
			Sleep(0); //Yield up our time slice to other running apps
			//helps to improve performance of system
			continue;
		}
		
		//receive the data from the socket
		int nData = m_Sock.Receive(
			pszBuffer + nReceived,
			1000 - nReceived);

		if (nData == SOCKET_ERROR)
		{
			pszBuffer[nReceived] = '\0';

			return FALSE; 
		}
		else
		{
			//Reset the idle timeout.
			if (nData)
				dwStartTicks = ::GetTickCount();
			
			//Increment the count of data received.
			nReceived += nData;
		}
		
		//temporarily NULL terminate the string.
		pszBuffer[nReceived] = '\0';

		//so that strstr works
		bFoundTerminator = (strstr(pszBuffer, pszTerminator) != NULL);
	}
	
	//Remove the terminator from the response data
	pszBuffer[nReceived - strlen(pszTerminator) - 1] = '\0';
	
	//determine if the response is an error
	char sCode[4];

	// The response code.
	int nResponseCode;

	// Retrieve the success code.
	strncpy(sCode, pszBuffer, 3);
	sCode[3] = '\0';
	sscanf(sCode, "%d", &nResponseCode);
	BOOL bSuccess = (nResponseCode == nExpectedCode);
	
	if (!bSuccess)
		SetLastError(WSAEPROTONOSUPPORT);
	
	return bSuccess;
}

void CMainFrame::ProcessAddress(char *pszBuffer, CString& strResult)
/*
Routine Description:
	Process the buffer, retrieve each address which are delimited by
	'\t'.

Parameters:
	pszBuffer		The buffer contains the string to be processed.

	strResult		The buffer receives the result address.

Return Value:
	None.
*/
{
	// Create a dialog to choose address if the number of returned 
	// address is more than one.
	CChooseAddrDlg dlg;
	dlg.m_arAddr.RemoveAll(); // The array contains each address.
	dlg.m_nTimeout = m_nTimeout;
	
	// Now process the buffer and get the address.
	
	int nReceived = strlen(pszBuffer);
	
	CString strAddress;
	for (int i = 3; i < nReceived; i ++)
	{
		if (pszBuffer[i] == '\t')
		{
			// The address terminator appears.
			
			dlg.m_arAddr.Add(strAddress);
			strAddress.Empty();
		}
		else
			strAddress += pszBuffer[i];
	}
	
	// Add the last address.
	if (strAddress.GetLength())
		dlg.m_arAddr.Add(strAddress);

	int nSize = dlg.m_arAddr.GetSize();
	if (nSize)
	{
		// If the size > 1, show the dialog for choosing.
		if (nSize > 1 && m_nMultiChoose && dlg.DoModal() == IDOK)
			strResult = dlg.m_arAddr[dlg.m_nSel];
		else
			strResult = dlg.m_arAddr[0];
		
		// Looking for the IP address of this domain
		hostent * pHost = gethostbyname(strResult);
		
		// Register the IP address, later we will add something 
		// when we receive data from there.
		if (pHost)
			RegisterHost(pHost);
	}
}

//void CMainFrame::OnTrayTest() 
//{
//	WCHAR szText[1024] = L"ÑÅ»¢";

//	SearchCDNS(szText);
//}
