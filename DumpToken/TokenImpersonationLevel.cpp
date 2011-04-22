#include "Utils.h"
#include <stdio.h>

//*****************************************************************************
//* Function Name: DumpTokenImpersonationLevel
//*   Description: 
//*****************************************************************************
void DumpTokenImpersonationLevel (
	HANDLE	p_hToken,
	LPVOID	p_pTokenInformation,
	DWORD	p_dwTokenInformationLength)
{
	PSECURITY_IMPERSONATION_LEVEL l_pSecurityImpersonationLevel = reinterpret_cast<PSECURITY_IMPERSONATION_LEVEL>(p_pTokenInformation);
	(void) _tprintf (_T("SECURITY_IMPERSONATION_LEVEL: %s\n"), static_cast<LPCTSTR>(SecurityImpersonationLevelToString (*l_pSecurityImpersonationLevel)));
}
