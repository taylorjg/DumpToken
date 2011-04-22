#include "Utils.h"
#include <stdio.h>

//*****************************************************************************
//* Function Name: DumpTokenGroups
//*   Description: 
//*****************************************************************************
void DumpTokenGroups (
	HANDLE	p_hToken,
	LPVOID	p_pTokenInformation,
	DWORD	p_dwTokenInformationLength)
{
	PTOKEN_GROUPS l_pTokenGroups = reinterpret_cast<PTOKEN_GROUPS>(p_pTokenInformation);

	(void) _tprintf (_T("TOKEN_GROUPS.GroupCount: %ld\n"), l_pTokenGroups->GroupCount);

	for (DWORD i = 0; i < l_pTokenGroups->GroupCount; i++)
	{
		PSID_AND_ATTRIBUTES l_pSidAndAttributes = &l_pTokenGroups->Groups[i];

		TCHAR l_szLabel[50] = {0};
		(void) _stprintf_s (l_szLabel, 50, _T("TOKEN_GROUPS.Group[%ld]"), i);

		DumpSidAndAttributes (l_pSidAndAttributes, l_szLabel);
	}
}
