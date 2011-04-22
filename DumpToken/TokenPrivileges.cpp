#include "Utils.h"
#include <stdio.h>

//*****************************************************************************
//* Function Name: DumpTokenPrivileges
//*   Description: 
//*****************************************************************************
void DumpTokenPrivileges (
	HANDLE	p_hToken,
	LPVOID	p_pTokenInformation,
	DWORD	p_dwTokenInformationLength)
{
	PTOKEN_PRIVILEGES l_pTokenPrivileges = reinterpret_cast<PTOKEN_PRIVILEGES>(p_pTokenInformation);

	(void) _tprintf (_T("TOKEN_PRIVILEGES.PrivilegeCount: %ld\n"), l_pTokenPrivileges->PrivilegeCount);

	for (DWORD i = 0; i < l_pTokenPrivileges->PrivilegeCount; i++)
	{
		TCHAR l_szLabel[100] = {0};
		(void) _stprintf_s (l_szLabel, 100, _T("TOKEN_PRIVILEGES.Privileges[%ld]"), i);

		PLUID_AND_ATTRIBUTES l_pLuidAndAttributes = &l_pTokenPrivileges->Privileges[i];
		DumpLuidAndAttributes (l_pLuidAndAttributes, l_szLabel);
	}
}
