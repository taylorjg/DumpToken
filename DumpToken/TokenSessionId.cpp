#include "Utils.h"
#include <stdio.h>
#include <crtdbg.h>

//*****************************************************************************
//* Function Name: DumpTokenSessionId
//*   Description: 
//*****************************************************************************
void DumpTokenSessionId (
	HANDLE	p_hToken,
	LPVOID	p_pTokenInformation,
	DWORD	p_dwTokenInformationLength)
{
	_ASSERTE (p_dwTokenInformationLength == sizeof (DWORD));
	LPDWORD l_pdwTokenSessionId = reinterpret_cast<LPDWORD>(p_pTokenInformation);
	(void) _tprintf (_T("TokenSessionId: %ld (0x%08lX)\n"), *l_pdwTokenSessionId, *l_pdwTokenSessionId);
}
