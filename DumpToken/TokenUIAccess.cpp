#include "Utils.h"
#include <stdio.h>
#include <crtdbg.h>

//*****************************************************************************
//* Function Name: DumpTokenUIAccess
//*   Description: 
//*****************************************************************************
void DumpTokenUIAccess (
	HANDLE	p_hToken,
	LPVOID	p_pTokenInformation,
	DWORD	p_dwTokenInformationLength)
{
	_ASSERTE (p_dwTokenInformationLength == sizeof (DWORD));
	LPDWORD l_pdwTokenUIAccess = reinterpret_cast<LPDWORD>(p_pTokenInformation);
	(void) _tprintf (_T("TokenUIAccess: %ld (0x%08lX)\n"), *l_pdwTokenUIAccess, *l_pdwTokenUIAccess);
}
