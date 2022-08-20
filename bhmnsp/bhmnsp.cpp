// bhmnsp.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include <objbase.h>
#include <svcguid.h>
#include <tchar.h>
#include "bhmnsp.h"
#include "export.h"

#define ADDRESSMAP _T("CNAddrFileMapping")

void SetHWnd(HWND hWnd)
/*
Routine Description:
	Set the window handle which receives the search message and find 
	the correspond net address to replace the chinese address in 
	NSPLookupServiceBegin when the user is looking up a chinese net
	address.

Parameters:
	hWnd		The handle of the desired window.

Return value:
	None.
*/
{
	m_hWndMain = hWnd;
}

BOOL IsChineseString(LPCWSTR szStr)
/*
Routine description:
	Determine if the given wchar string include chinese characters.

Parameters:
	szStr		The string to process.

Return value:
	If the given string contain chinese characters, return TRUE;
	Otherwise, return FALSE;
*/
{
	if (!szStr)
		return FALSE;

	for (ULONG i = 0; i < wcslen(szStr); i ++)
	{
		if (szStr[i] > 0xff)
			return TRUE;
	}

	return FALSE;
}

BOOL APIENTRY DllMain
(
	HANDLE hModule, 
	DWORD  ul_reason_for_call, 
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_PROCESS_DETACH:
		{
			m_hNextLayerNSP = NULL;
			memset(&m_NextLayerNSPRoutine, 0, sizeof(m_NextLayerNSPRoutine));
			m_nRef = 0;
		}
	}

	return TRUE;
}

int WSPAPI NSPCleanup
(
  LPGUID lpProviderId  
)
/*
Routine Description:
	The NSPCleanup function terminates the use of a particular Windows 
	Sockets name space service provider.

Parameters:
	lpProviderId		[in] Pointer to the GUID of the name space provider 
						that is to be terminated. 

Return Value:
	If no error occurs, NSPCleanup returns a value of NO_ERROR (zero). 
	Otherwise, SOCKET_ERROR (每1) is returned and the provider must set 
	the appropriate error code using SetLastError.
*/
{
	// Decrease the reference count;
	m_nRef --;
	
	int nRet = NO_ERROR;

	if (m_NextLayerNSPRoutine.NSPCleanup)
		nRet = (*m_NextLayerNSPRoutine.NSPCleanup)(&m_NextLayerNSPGuid);

	if (m_nRef == 0)
	{
		// Unload the library loaded by me.
		if (m_hNextLayerNSP)
			FreeLibrary(m_hNextLayerNSP);
	}

	// Clear the saved dispatch table;
	memset(&m_NextLayerNSPRoutine, 0, sizeof(m_NextLayerNSPRoutine));

	return NO_ERROR;
}

int WSPAPI NSPGetServiceClassInfo
(
  IN LPGUID lpProviderId,
  IN OUT LPDWORD lpdwBufSize,
  IN OUT LPWSASERVICECLASSINFOW lpServiceClassInfo
)
/*
Routine Description:
	The NSPGetServiceClassInfo function retrieves all the pertinent 
	class information (schema) pertaining to the name space provider. 
	This call retrieves any name space-specific information that is 
	common to all instances of the service, including connection 
	information for SAP, or port information for SAP or TCP.

Parameters:
	lpProviderId		Pointer to the GUID of the specific name space 
						provider from which the service class schema 
						is to be retrieved. 

	lpdwBufSize			Number of bytes contained in the buffer pointed 
						to by lpServiceClassInfo on input. Alternately, 
						if the function fails and the error is WSAEFAULT, 
						lpdwBufSize contains the minimum number of bytes 
						to pass for the lpServiceClassInfo to retrieve 
						the record on output. 

	lpServiceClassInfo	Returns service class to name space-specific 
						mapping information. The lpServiceClassId 
						parameter must be filled in to indicate which 
						WSASERVICECLASSINFOW record should be returned. 

Return Values:
	If no error occurs, the NSPGetServiceClassInfo function returns 
	NO_ERROR (zero). Otherwise, SOCKET_ERROR (每1) is returned and it 
	must set the appropriate error code using SetLastError.
*/
{
	if (m_NextLayerNSPRoutine.NSPGetServiceClassInfo)
		return (*m_NextLayerNSPRoutine.NSPGetServiceClassInfo)
		(
			&m_NextLayerNSPGuid,
			lpdwBufSize,
			lpServiceClassInfo
		);
	else
		return NO_ERROR;
}

int WSPAPI NSPInstallServiceClass
(
  LPGUID lpProviderId,
  LPWSASERVICECLASSINFOW lpServiceClassInfo
)
/*
Routine Description:
	The NSPInstallServiceClass function registers service class schema 
	within the name space providers.

Parameters:
	lpProviderId		[in] Pointer to the GUID of the specific name 
						space provider that this service class schema 
						is being registered in. 

	lpServiceClassInfo	[in] Contains service class schema information. 

Return Values:
	The function should return NO_ERROR (zero) if the routine succeeds. 
	It should return SOCKET_ERROR (每1) if the routine fails and it must 
	set the appropriate error code using SetLastError.
*/
{
	if (m_NextLayerNSPRoutine.NSPInstallServiceClass)
		return (*m_NextLayerNSPRoutine.NSPInstallServiceClass)
		(
			&m_NextLayerNSPGuid,
			lpServiceClassInfo
		);
	else
		return NO_ERROR;
}

int WSPAPI NSPLookupServiceBegin (
  LPGUID lpProviderId,
  LPWSAQUERYSETW lpqsRestrictions,
  LPWSASERVICECLASSINFOW lpServiceClassInfo,
  DWORD dwControlFlags,
  LPHANDLE lphLookup
)
/*
Routine Description:
	The WSALookupServiceBegin function initiates a client query that 
	is constrained by the information contained within a WSAQUERYSET 
	structure.

Parameters:
	lpProviderId		[in] Contains the specific provider identifier 
						that should be used for the query. 

	lpqsRestrictions	[in] Contains the search criteria. See the following 
						for more information. 
	
	lpServiceClassInfo	[in] WSASERVICECLASSINFOW structure that contains 
						all the schema information for the service. 
	
	dwControlFlags		[in] Controls the depth of the search. LUP_DEEP 
						Query deep as opposed to just the first level. 
						
						LUP_CONTAINERS		Return containers only. 
						LUP_NOCONTAINERS	Do not return any containers. 
						LUP_FLUSHCACHE		If the provider has been 
											caching information, ignore 
											the cache and go query the 
											name space itself. 
						LUP_FLUSHPREVIOUS	Used as a value for the dwControlFlags 
											argument in NSPLookupServiceNext. 
											Setting this flag instructs 
											the provider to discard the 
											last result set, which was 
											too large for the supplied 
											buffer, and move on to the 
											next result set. 
						LUP_NEAREST			If possible, return results 
											in the order of distance. 
											The measure of distance is 
											provider specific. 
						LUP_RES_RESERVICE	Indicates whether prime response 
											is in the remote or local 
											part of CSADDR_INFO structure. 
											The other part needs to be 
											usable in either case. 
						LUP_RETURN_ALIASES	Any available alias information 
											is to be returned in successive 
											calls to NSPLookupServiceNext, 
											and each alias returned will 
											have the RESULT_IS_ALIAS 
											flag set. 
						LUP_RETURN_NAME		Retrieves the name as lpszServiceInstanceName. 
						LUP_RETURN_TYPE		Retrieves the type as lpServiceClassId. 
						LUP_RETURN_WSAVERSION	Retrieves the version as lpVersion. 
						LUP_RETURN_COMMENT	Retrieves the comment as lpszComment. 
						LUP_RETURN_ADDR		Retrieves the addresses as lpcsaBuffer. 
						LUP_RETURN_BLOB		Retrieves the private data 
											as lpBlob. 
						LUP_RETURN_ALL		Retrieves all the information. 
	
	lphLookup		[out] Handle to be used in subsequent calls to 
					NSPLookupServiceNext in order to retrieve the 
					results set. 

Return Values:
	The function should return NO_ERROR (zero) if the routine succeeds. 
	It should return SOCKET_ERROR (每1) if the routine fails and it must 
	set the appropriate error code using SetLastError.
*/
{
	if (m_NextLayerNSPRoutine.NSPLookupServiceBegin)
	{
		// Save the pointer.
		GUID idService = SVCID_INET_HOSTADDRBYNAME;
		WCHAR szAddr[256] = L"";

		// Save the original pointer.
		WCHAR * pszServiceInstanceNameSaved = lpqsRestrictions->lpszServiceInstanceName;

		// If the special name occurs, replace it with normal english
		// address name.
		if (
				IsEqualGUID
				(
					*lpqsRestrictions->lpServiceClassId,
					idService
				)
				&& IsChineseString(lpqsRestrictions->lpszServiceInstanceName)
			)
		{
			wcscpy(szAddr, lpqsRestrictions->lpszServiceInstanceName);
			SearchAddr(szAddr);
			if (wcslen(szAddr))
				lpqsRestrictions->lpszServiceInstanceName = szAddr;

			// Assign the address a new string pointer, and should 
			// restore the old pointer after calling the next layer's
			// NSPLookupServiceBegin.
		}

//		char addr[50];
//		for (ULONG i = 0; lpqsRestrictions->lpszServiceInstanceName && i < wcslen(lpqsRestrictions->lpszServiceInstanceName); i ++)
//			addr[i] = (char)lpqsRestrictions->lpszServiceInstanceName[i];
//		addr[i] = 0;

		int nRet = (*m_NextLayerNSPRoutine.NSPLookupServiceBegin)
		(
			&m_NextLayerNSPGuid,
			lpqsRestrictions,
			lpServiceClassInfo,
			dwControlFlags,
			lphLookup
		);

		// Restore the original pointer.
		lpqsRestrictions->lpszServiceInstanceName = pszServiceInstanceNameSaved;

		return nRet;
	}
	else
		return NO_ERROR;
}

int WSPAPI NSPLookupServiceEnd
(
  HANDLE hLookup
)
/*
Routine Description:
	The NSPLookupServiceEnd function is called to free the handle after 
	previous calls to NSPLookupServiceBegin and NSPLookupServiceNext.

Parameters:
	hLookup		[in] Handle previously obtained by calling NSPLookupServiceBegin. 

Return Values:
	The function should return NO_ERROR (zero) if the routine succeeds. 
	It should return SOCKET_ERROR (每1) if the routine fails and it must 
	set the appropriate error code using SetLastError.
*/
{
	if (m_NextLayerNSPRoutine.NSPLookupServiceEnd)
		return (*m_NextLayerNSPRoutine.NSPLookupServiceEnd)(hLookup);
	else
		return NO_ERROR;
}

int WSPAPI NSPLookupServiceNext
(
  HANDLE hLookup,
  DWORD dwControlFlags,
  LPDWORD lpdwBufferLength,
  LPWSAQUERYSETW lpqsResults
)
/*
Routine Description:
	The NSPLookupServiceNext function is called after obtaining a handle 
	from a previous call to NSPLookupServiceBegin in order to retrieve 
	the requested service information.

Parameters:

	hLookup				[in] Handle returned from the previous call to WSALookupServiceBegin. 

	dwControlFlags		[in] Flags to control the next operation. Currently 
						only LUP_FLUSHPREVIOUS is defined as a means to 
						cope with a result set that is too large. If an 
						application does not wish to (or cannot) supply 
						a large enough buffer, setting LUP_FLUSHPREVIOUS 
						instructs the provider to discard the last result 
						set, which was too large, and move to the next 
						set for this call. 

	lpdwBufferLength	[in/out] On input, the number of bytes contained 
						in the buffer pointed to by lpqsResults. On output, 
						if the function fails and the error is WSAEFAULT, 
						then it contains the minimum number of bytes to 
						pass for the lpqsResults to retrieve the record. 

	lpqsResults			[out] Pointer to a block of memory that will contain 
						one result set in a WSAQUERYSET structure on 
						return. 

Return Values:
	The function should return NO_ERROR (zero) if the routine succeeds. 
	It should return SOCKET_ERROR (每1) if the routine fails and it 
	must set the appropriate error code using SetLastError.
*/
{
	if (m_NextLayerNSPRoutine.NSPLookupServiceNext)
	{
		int nRet = (*m_NextLayerNSPRoutine.NSPLookupServiceNext)
		(
			hLookup,
			dwControlFlags,
			lpdwBufferLength,
			lpqsResults
		);

		return nRet;
	}
	else
		return NO_ERROR;
}

int WSPAPI NSPRemoveServiceClass
(
  IN LPGUID lpProviderId,
  IN LPGUID lpServiceClassId
)
/*
Routine Description:
	The NSPRemoveServiceClass function permanently removes a specified 
	service class from the name space.

Parameters:

	lpProviderId		[in] Pointer to the GUID of the specific name 
						space provider that this service class schema 
						is to be removed from. 

	lpServiceClassId	[in] Pointer to the GUID for the service class 
						to remove. 

Return Values:
	The function should return NO_ERROR (zero) if the routine succeeds. 
	It should return SOCKET_ERROR (每1) if the routine fails and it 
	must set the appropriate error code using SetLastError.
*/
{
	if (m_NextLayerNSPRoutine.NSPRemoveServiceClass)
		return (*m_NextLayerNSPRoutine.NSPRemoveServiceClass)
		(
			&m_NextLayerNSPGuid,
			lpServiceClassId
		);
	else
		return NO_ERROR;
}

int WSPAPI NSPSetService
(
  LPGUID lpProviderId,
  LPWSASERVICECLASSINFOW lpServiceClassInfo,
  LPWSAQUERYSETW lpqsRegInfo,
  WSAESETSERVICEOP essOperation,
  DWORD dwControlFlags
)
/*
Routine Description:
	The NSPSetService function registers or deregisters a service instance 
	within a name space.

Parameters:
	lpProviderId		[in] Pointer to the GUID of the specific name 
						space provider in which the service is being 
						registered. 

	lpServiceClassInfo	[in] Contains service class schema information. 

	lpqsRegInfo			[in] Specifies property information to be updated 
						upon registration. 

	essOperation		[in] Enumeration whose values include: 
						RNRSERVICE_REGISTER		Register the service. 
												For SAP, this means sending 
												out a periodic broadcast. 
												This is an NOP for the 
												DNS name space. For persistent 
												data stores this means 
												updating the address information. 
						
						RNRSERVICE_DEREGISTER	Deregister the service. 
												For SAP, this means stop 
												sending out the periodic 
												broadcast. This is an 
												NOP for the DNS name space. 
												For persistent data stores 
												this means deleting address 
												information. 

						RNRSERVICE_DELETE		Delete the service from 
												dynamic name and persistent 
												spaces. For services represented 
												by multiple CSADDR_INFO 
												structures (using the 
												SERVICE_MULTIPLE flag), 
												only the supplied address 
												will be deleted, and this 
												must match exactly the 
												corresponding CSADD_INFO 
												structure that was supplied 
												when the service was registered. 

	dwControlFlags		[in] Set of control flags whose values include: 
						SERVICE_MULTIPLE	Controls scope of operation. 
											A register or deregister invalidates 
											all existing addresses before 
											adding the given address set. 
											When set, the action is only 
											performed on the given address 
											set. A register does not invalidate 
											existing addresses and a deregister 
											only invalidates the given 
											set of addresses. 

Return Values:
	The function should return NO_ERROR (zero) if the routine succeeds. 
	It should return SOCKET_ERROR (每1) if the routine fails and it 
	must set the appropriate error code using SetLastError.
*/
{
	if (m_NextLayerNSPRoutine.NSPSetService)
		return (*m_NextLayerNSPRoutine.NSPSetService)
		(
			&m_NextLayerNSPGuid,
			lpServiceClassInfo,
			lpqsRegInfo,
			essOperation,
			dwControlFlags
		);
	else
		return NO_ERROR;
}

int WSPAPI NSPStartup
(
	LPGUID lpProviderId,
	LPNSP_ROUTINE lpnspRoutines
)
/*
Routine Description:
	The NSPStartup function retrieves the dynamic information about a 
	provider, such as the list of the DLL entry points.

Parameters:
	lpProviderId		[in] Indicates the desired provider for which 
						to return the entry points.

	lpnspRoutines		[out] Pointer to all the Provider entry points. 

Return Value:
	The function should return NO_ERROR (zero) if the routine succeeds. 
	It should return SOCKET_ERROR (每1) if the routine fails and it must 
	set the appropriate error code using SetLastError.
*/
{
	int (WSPAPI *pNSPStartup)(LPGUID, LPNSP_ROUTINE) = NULL;

	if (!m_hNextLayerNSP)
	{
		// Load the next layer NSP file to do tough jobs.
		m_hNextLayerNSP = LoadLibrary("wspwsp.dll");;
		if (!m_hNextLayerNSP)
			return SOCKET_ERROR;

		// Find the correspond procedure address.
		(FARPROC&)pNSPStartup = GetProcAddress(m_hNextLayerNSP, "NSPStartup");
		if (!pNSPStartup)
			return SOCKET_ERROR;
	}
	
	// Clear the saved dispatch table;
	memset(&m_NextLayerNSPRoutine, 0, sizeof(m_NextLayerNSPRoutine));
	m_NextLayerNSPRoutine.cbSize = sizeof(m_NextLayerNSPRoutine);

	// Call the correspond NSPStartup of the next layer NSP.
	int nRet = (*pNSPStartup)(&m_NextLayerNSPGuid, &m_NextLayerNSPRoutine);
	if (nRet != NO_ERROR)
	{
		int nErr = GetLastError();
		return nRet;
	}

	// Increase the reference count;
	m_nRef ++;

	// Fill the given table using my own routine.
	lpnspRoutines->NSPCleanup = NSPCleanup;
	lpnspRoutines->NSPGetServiceClassInfo = NSPGetServiceClassInfo;
	lpnspRoutines->NSPInstallServiceClass = NSPInstallServiceClass;
	lpnspRoutines->NSPLookupServiceBegin = NSPLookupServiceBegin;
	lpnspRoutines->NSPLookupServiceEnd = NSPLookupServiceEnd;
	lpnspRoutines->NSPLookupServiceNext = NSPLookupServiceNext;
	lpnspRoutines->NSPRemoveServiceClass = NSPRemoveServiceClass;
	lpnspRoutines->NSPSetService = NSPSetService;

	return NO_ERROR;
}

void SearchAddr(LPWSTR szSearch)
/*
Routine Description:
	Search the correspond net address given a chinese string.

Parameters:
	szSearch		The string used to search.

Return value:
	None.
*/
{
	if (!m_hWndMain)
		return;
	
	HANDLE hMapFile;
	LPWSTR szText;
	
	// Open mapped file.
	hMapFile = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, ADDRESSMAP);
	
	if (!hMapFile) 
	{
#ifdef _DEBUG
		MessageBox(NULL, "Could not open file-mapping object.", "bhmnsp", MB_OK);
#endif
		return;
	} 
	
	szText = (LPWSTR)MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, 0);                                // Map entire file. 
	
	if (!szText) 
	{
#ifdef _DEBUG
		MessageBox(NULL, "Could not map view of file.", "hook", MB_OK);
#endif		
		return;
	}
	
	wcscpy(szText, szSearch);
	
	// Send the search message to controling window.
	SendMessage(m_hWndMain, WM_SEARCH, NULL, NULL);
	
	// If we get the address, use it to replace the chinese string.
	wcscpy(szSearch, szText);
}
