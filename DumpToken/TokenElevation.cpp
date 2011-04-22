#include "Utils.h"
#include <stdio.h>

//*****************************************************************************
//* Function Name: DumpTokenElevation
//*   Description: 
//*****************************************************************************
void DumpTokenElevation (
	HANDLE	p_hToken,
	LPVOID	p_pTokenInformation,
	DWORD	p_dwTokenInformationLength)
{
	PTOKEN_ELEVATION l_pTokenElevation = reinterpret_cast<PTOKEN_ELEVATION>(p_pTokenInformation);
	(void) _tprintf (_T("TOKEN_ELEVATION.TokenIsElevated: %ld\n"), l_pTokenElevation->TokenIsElevated);
}
