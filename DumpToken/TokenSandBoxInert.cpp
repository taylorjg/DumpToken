#include "Utils.h"
#include <stdio.h>
#include <crtdbg.h>

//*****************************************************************************
//* Function Name: DumpTokenSandBoxInert
//*   Description: 
//*****************************************************************************
void DumpTokenSandBoxInert (
	HANDLE	p_hToken,
	LPVOID	p_pTokenInformation,
	DWORD	p_dwTokenInformationLength)
{
	_ASSERTE (p_dwTokenInformationLength == sizeof (DWORD));
	LPDWORD l_pdwTokenSandBoxInert = reinterpret_cast<LPDWORD>(p_pTokenInformation);
	(void) _tprintf (_T("TokenSandBoxInert: %ld (0x%08lX)\n"), *l_pdwTokenSandBoxInert, *l_pdwTokenSandBoxInert);
}
