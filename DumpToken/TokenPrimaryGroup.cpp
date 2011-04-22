#include "Utils.h"
#include <stdio.h>

//*****************************************************************************
//* Function Name: DumpTokenPrimaryGroup
//*   Description: 
//*****************************************************************************
void DumpTokenPrimaryGroup (
	HANDLE	p_hToken,
	LPVOID	p_pTokenInformation,
	DWORD	p_dwTokenInformationLength)
{
	PTOKEN_PRIMARY_GROUP l_pTokenPrimaryGroup = reinterpret_cast<PTOKEN_PRIMARY_GROUP>(p_pTokenInformation);
	DumpSid (l_pTokenPrimaryGroup->PrimaryGroup, _T("TOKEN_PRIMARY_GROUP.PrimaryGroup"));
}
