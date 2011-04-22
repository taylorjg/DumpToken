#include "Utils.h"
#include <stdio.h>

//*****************************************************************************
//* Function Name: DumpTokenOwner
//*   Description: 
//*****************************************************************************
void DumpTokenOwner (
	HANDLE	p_hToken,
	LPVOID	p_pTokenInformation,
	DWORD	p_dwTokenInformationLength)
{
	PTOKEN_OWNER l_pTokenOwner = reinterpret_cast<PTOKEN_OWNER>(p_pTokenInformation);
	DumpSid (l_pTokenOwner->Owner, _T("TOKEN_OWNER.Owner"));
}
