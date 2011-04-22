#include "Utils.h"
#include <stdio.h>

//*****************************************************************************
//* Function Name: DumpTokenLogonSid
//*   Description: 
//*****************************************************************************
void DumpTokenLogonSid (
	HANDLE	p_hToken,
	LPVOID	p_pTokenInformation,
	DWORD	p_dwTokenInformationLength)
{
	PSID l_pTokenLogonSid = reinterpret_cast<PSID>(p_pTokenInformation);
	DumpSid (l_pTokenLogonSid, _T("TokenLogonSid"));
}
