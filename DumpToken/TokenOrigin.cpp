#include "Utils.h"
#include <stdio.h>

//*****************************************************************************
//* Function Name: DumpTokenOrigin
//*   Description: 
//*****************************************************************************
void DumpTokenOrigin (
	HANDLE	p_hToken,
	LPVOID	p_pTokenInformation,
	DWORD	p_dwTokenInformationLength)
{
	PTOKEN_ORIGIN l_pTokenOrigin = reinterpret_cast<PTOKEN_ORIGIN>(p_pTokenInformation);
	(void) _tprintf (_T("TOKEN_ORIGIN.OriginatingLogonSession.LowPart: %ld (0x%08lX)\n"), l_pTokenOrigin->OriginatingLogonSession.LowPart, l_pTokenOrigin->OriginatingLogonSession.LowPart);
	(void) _tprintf (_T("TOKEN_ORIGIN.OriginatingLogonSession.HighPart: %ld (0x%08lX)\n"), l_pTokenOrigin->OriginatingLogonSession.HighPart, l_pTokenOrigin->OriginatingLogonSession.HighPart);
}
