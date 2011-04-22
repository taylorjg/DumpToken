#include "Utils.h"
#include <stdio.h>
#include <crtdbg.h>

//*****************************************************************************
//* Function Name: DumpTokenHasRestrictions
//*   Description: 
//*****************************************************************************
void DumpTokenHasRestrictions (
	HANDLE	p_hToken,
	LPVOID	p_pTokenInformation,
	DWORD	p_dwTokenInformationLength)
{
	// LPDWORD l_pdwTokenHasRestrictions = reinterpret_cast<LPDWORD>(p_pTokenInformation);
	// (void) _tprintf (_T("TokenHasRestrictions: %ld (0x%08lX)\n"), *l_pdwTokenHasRestrictions, *l_pdwTokenHasRestrictions);

	// The documentation says that this is a DWORD. But in practice, it seems
	// to be just a single byte.
	_ASSERTE (p_dwTokenInformationLength == 1);
	LPBYTE l_pbyTokenHasRestrictions = reinterpret_cast<LPBYTE>(p_pTokenInformation);
	(void) _tprintf (_T("TokenHasRestrictions: %d\n"), *l_pbyTokenHasRestrictions);
}
