#include "Utils.h"
#include <stdio.h>
#include <crtdbg.h>

//*****************************************************************************
//* Function Name: DumpTokenVirtualizationAllowed
//*   Description: 
//*****************************************************************************
void DumpTokenVirtualizationAllowed (
	HANDLE	p_hToken,
	LPVOID	p_pTokenInformation,
	DWORD	p_dwTokenInformationLength)
{
	_ASSERTE (p_dwTokenInformationLength == sizeof (DWORD));
	LPDWORD l_pdwTokenVirtualizationAllowed = reinterpret_cast<LPDWORD>(p_pTokenInformation);
	(void) _tprintf (_T("TokenVirtualizationAllowed: %ld (0x%08lX)\n"), *l_pdwTokenVirtualizationAllowed, *l_pdwTokenVirtualizationAllowed);
}
