#include "Utils.h"
#include <stdio.h>

//*****************************************************************************
//* Function Name: DumpTokenMandatoryPolicy
//*   Description: 
//*****************************************************************************
void DumpTokenMandatoryPolicy (
	HANDLE	p_hToken,
	LPVOID	p_pTokenInformation,
	DWORD	p_dwTokenInformationLength)
{
	PTOKEN_MANDATORY_POLICY l_pTokenMandatoryPolicy = reinterpret_cast<PTOKEN_MANDATORY_POLICY>(p_pTokenInformation);

	(void) _tprintf (
		_T("TOKEN_MANDATORY_POLICY.Policy: %s (0x%08lX)\n"),
		static_cast<LPCTSTR>(MandatoryPolicyToString (l_pTokenMandatoryPolicy->Policy)),
		l_pTokenMandatoryPolicy->Policy);
}
