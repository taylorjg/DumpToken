#include "Utils.h"
#include <stdio.h>

//*****************************************************************************
//* Function Name: DumpTokenType
//*   Description: 
//*****************************************************************************
void DumpTokenType (
	HANDLE	p_hToken,
	LPVOID	p_pTokenInformation,
	DWORD	p_dwTokenInformationLength)
{
	PTOKEN_TYPE l_pTokenType = reinterpret_cast<PTOKEN_TYPE>(p_pTokenInformation);
	(void) _tprintf (_T("TOKEN_TYPE: %s\n"), static_cast<LPCTSTR>(TokenTypeToString (*l_pTokenType)));
}
