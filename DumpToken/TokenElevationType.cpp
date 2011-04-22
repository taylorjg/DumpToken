#include "Utils.h"
#include <stdio.h>

//*****************************************************************************
//* Function Name: DumpTokenElevationType
//*   Description: 
//*****************************************************************************
void DumpTokenElevationType (
	HANDLE	p_hToken,
	LPVOID	p_pTokenInformation,
	DWORD	p_dwTokenInformationLength)
{
	PTOKEN_ELEVATION_TYPE l_pTokenElevationType = reinterpret_cast<PTOKEN_ELEVATION_TYPE>(p_pTokenInformation);
	(void) _tprintf (_T("TOKEN_ELEVATION_TYPE: %s\n"), static_cast<LPCTSTR>(TokenElevationTypeToString (*l_pTokenElevationType)));
}
