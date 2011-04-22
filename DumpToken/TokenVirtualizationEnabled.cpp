#include "Utils.h"
#include <stdio.h>
#include <crtdbg.h>

//*****************************************************************************
//* Function Name: DumpTokenVirtualizationEnabled
//*   Description: 
//*****************************************************************************
void DumpTokenVirtualizationEnabled (
	HANDLE	p_hToken,
	LPVOID	p_pTokenInformation,
	DWORD	p_dwTokenInformationLength)
{
	_ASSERTE (p_dwTokenInformationLength == sizeof (DWORD));
	LPDWORD l_pdwTokenVirtualizationEnabled = reinterpret_cast<LPDWORD>(p_pTokenInformation);
	(void) _tprintf (_T("TokenVirtualizationEnabled: %ld (0x%08lX)\n"), *l_pdwTokenVirtualizationEnabled, *l_pdwTokenVirtualizationEnabled);
}
