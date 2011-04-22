#include "Utils.h"
#include <stdio.h>

//*****************************************************************************
//* Function Name: DumpTokenGroupsAndPrivileges
//*   Description: 
//*****************************************************************************
void DumpTokenGroupsAndPrivileges (
	HANDLE	p_hToken,
	LPVOID	p_pTokenInformation,
	DWORD	p_dwTokenInformationLength)
{
	PTOKEN_GROUPS_AND_PRIVILEGES l_pTokenGroupsAndPrivileges = reinterpret_cast<PTOKEN_GROUPS_AND_PRIVILEGES>(p_pTokenInformation);

	(void) _tprintf (_T("TOKEN_GROUPS_AND_PRIVILEGES.SidCount: %ld\n"), l_pTokenGroupsAndPrivileges->SidCount);
	(void) _tprintf (_T("TOKEN_GROUPS_AND_PRIVILEGES.SidLength: %ld\n"), l_pTokenGroupsAndPrivileges->SidLength);
	for (DWORD i = 0; i < l_pTokenGroupsAndPrivileges->SidCount; i++)
	{
		TCHAR l_szLabel[100] = {0};
		(void) _stprintf_s (l_szLabel, 100, _T("TOKEN_GROUPS_AND_PRIVILEGES.Sids[%ld]"), i);

		PSID_AND_ATTRIBUTES l_pSidAndAttributes = &l_pTokenGroupsAndPrivileges->Sids[i];
		DumpSidAndAttributes (l_pSidAndAttributes, l_szLabel);
	}

	(void) _tprintf (_T("TOKEN_GROUPS_AND_PRIVILEGES.RestrictedSidCount: %ld\n"), l_pTokenGroupsAndPrivileges->RestrictedSidCount);
	(void) _tprintf (_T("TOKEN_GROUPS_AND_PRIVILEGES.RestrictedSidLength: %ld\n"), l_pTokenGroupsAndPrivileges->RestrictedSidLength);
	for (DWORD i = 0; i < l_pTokenGroupsAndPrivileges->RestrictedSidCount; i++)
	{
		TCHAR l_szLabel[100] = {0};
		(void) _stprintf_s (l_szLabel, 100, _T("TOKEN_GROUPS_AND_PRIVILEGES.RestrictedSids[%ld]"), i);

		PSID_AND_ATTRIBUTES l_pSidAndAttributes = &l_pTokenGroupsAndPrivileges->RestrictedSids[i];
		DumpSidAndAttributes (l_pSidAndAttributes, l_szLabel);
	}

	(void) _tprintf (_T("TOKEN_GROUPS_AND_PRIVILEGES.PrivilegeCount: %ld\n"), l_pTokenGroupsAndPrivileges->PrivilegeCount);
	(void) _tprintf (_T("TOKEN_GROUPS_AND_PRIVILEGES.PrivilegeLength: %ld\n"), l_pTokenGroupsAndPrivileges->PrivilegeLength);

	for (DWORD i = 0; i < l_pTokenGroupsAndPrivileges->PrivilegeCount; i++)
	{
		TCHAR l_szLabel[100] = {0};
		(void) _stprintf_s (l_szLabel, 100, _T("TOKEN_GROUPS_AND_PRIVILEGES.Privileges[%ld]"), i);

		PLUID_AND_ATTRIBUTES l_pLuidAndAttributes = &l_pTokenGroupsAndPrivileges->Privileges[i];
		DumpLuidAndAttributes (l_pLuidAndAttributes, l_szLabel);
	}

	(void) _tprintf (_T("TOKEN_GROUPS_AND_PRIVILEGES.AuthenticationId.LowPart: %ld (0x%08lX)\n"), l_pTokenGroupsAndPrivileges->AuthenticationId.LowPart, l_pTokenGroupsAndPrivileges->AuthenticationId.LowPart);
	(void) _tprintf (_T("TOKEN_GROUPS_AND_PRIVILEGES.AuthenticationId.HighPart: %ld (0x%08lX)\n"), l_pTokenGroupsAndPrivileges->AuthenticationId.HighPart, l_pTokenGroupsAndPrivileges->AuthenticationId.HighPart);
}
