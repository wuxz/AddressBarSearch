#ifndef __BHMNSP_H
#define __BHMNSP_H

//	The window handle which receive the search message. It searches 
//	the	correspond address and return it to me using shared memory.
//	So this variable should be shared in all instance.
#pragma data_seg(".shared")
	static HWND m_hWndMain = NULL;
#pragma data_seg()

#pragma comment(linker, "/SECTION:.shared,RWS")

BOOL IsChineseString(LPCWSTR szStr);
void SearchAddr(LPWSTR szSearch);

// The registered search message.
const UINT WM_SEARCH = RegisterWindowMessage(_T("SearchCNAddr"));

// The handle of the NSP called by me to do jobs.
HINSTANCE m_hNextLayerNSP = NULL;

// The GUID of the next layer NSP.
GUID m_NextLayerNSPGuid =
{
//	0xff017de2,
//	0xca9e,
//	0x11cf,
//	{0x8a, 0x99, 0x0, 0xaa, 0x0, 0x62, 0xc6, 0x09}
	0x4a2a9951,
	0x8573,
	0x11d0,
	{0xa7, 0xeb, 0x0, 0x0, 0xf8, 0x75, 0x0b, 0x21}
};

// The dispatch table of the exported functions of the next layer NSP.
NSP_ROUTINE m_NextLayerNSPRoutine;

// The reference count for NSPStartup and NSPCleanup;
ULONG m_nRef = 0;

#endif