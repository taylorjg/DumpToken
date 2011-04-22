#include "Utils.h"
#include <stdio.h>

//*****************************************************************************
//* Function Name: DumpTokenAccessInformation
//*   Description: 
//*****************************************************************************
void DumpTokenAccessInformation (
	HANDLE	p_hToken,
	LPVOID	p_pTokenInformation,
	DWORD	p_dwTokenInformationLength)
{
	PTOKEN_ACCESS_INFORMATION l_pTokenAccessInformation = reinterpret_cast<PTOKEN_ACCESS_INFORMATION>(p_pTokenInformation);

	DumpSidAndAttributesHash (l_pTokenAccessInformation->SidHash, _T("TOKEN_ACCESS_INFORMATION.SidHash"));
	DumpSidAndAttributesHash (l_pTokenAccessInformation->RestrictedSidHash, _T("TOKEN_ACCESS_INFORMATION.RestrictedSidHash"));

	PTOKEN_PRIVILEGES l_pTokenPrivileges = l_pTokenAccessInformation->Privileges;

	(void) _tprintf (_T("TOKEN_ACCESS_INFORMATION.Privileges.PrivilegeCount: %ld\n"), l_pTokenPrivileges->PrivilegeCount);

	for (DWORD i = 0; i < l_pTokenPrivileges->PrivilegeCount; i++)
	{
		PLUID_AND_ATTRIBUTES l_pLuidAndAttributes = &l_pTokenPrivileges->Privileges[i];

		(void) _tprintf (
			_T("TOKEN_ACCESS_INFORMATION.Privileges[%ld].Luid: \"%s\"\n"),
			i,
			static_cast<LPCTSTR>(GetPrivilegeDisplayName (&l_pLuidAndAttributes->Luid)));

		(void) _tprintf (
			_T("TOKEN_ACCESS_INFORMATION.Privileges[%ld].Attributes: %s (0x%08lX)\n"),
			i,
			static_cast<LPCTSTR>(LuidAttributesToString (l_pLuidAndAttributes->Attributes)),
			l_pLuidAndAttributes->Attributes);
	}

	(void) _tprintf (_T("TOKEN_ACCESS_INFORMATION.AuthenticationId.LowPart: %ld (0xl%08X)\n"), l_pTokenAccessInformation->AuthenticationId.LowPart, l_pTokenAccessInformation->AuthenticationId.LowPart);
	(void) _tprintf (_T("TOKEN_ACCESS_INFORMATION.AuthenticationId.HighPart: %ld (0x%08lX)\n"), l_pTokenAccessInformation->AuthenticationId.HighPart, l_pTokenAccessInformation->AuthenticationId.HighPart);
	(void) _tprintf (_T("TOKEN_ACCESS_INFORMATION.TokenType: %s\n"), static_cast<LPCTSTR>(TokenTypeToString (l_pTokenAccessInformation->TokenType)));
	(void) _tprintf (_T("TOKEN_ACCESS_INFORMATION.ImpersonationLevel: %s\n"), static_cast<LPCTSTR>(SecurityImpersonationLevelToString (l_pTokenAccessInformation->ImpersonationLevel)));
	(void) _tprintf (_T("TOKEN_ACCESS_INFORMATION.MandatoryPolicy.Policy: %s\n"), static_cast<LPCTSTR>(MandatoryPolicyToString (l_pTokenAccessInformation->MandatoryPolicy.Policy)));
	(void) _tprintf (_T("TOKEN_ACCESS_INFORMATION.Flags: %ld (0x%08lX)\n"), l_pTokenAccessInformation->Flags, l_pTokenAccessInformation->Flags);
}
