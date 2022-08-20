// inst.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <ws2spi.h>
#include "..\instguid.h"

int main(int argc, char* argv[])
{
	WSCInstallNameSpace
	(
		L"BHM NSP",
		L"bhmnsp.dll",
		0x0c,
		1,
		&BHMNSPGuid
	);

//	WSCUnInstallNameSpace(&BHMNSPGuid);

	return 0;
}

