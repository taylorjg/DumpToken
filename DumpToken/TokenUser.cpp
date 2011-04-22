#include "Utils.h"
#include <stdio.h>

//*****************************************************************************
//* Function Name: DumpTokenUser
//*   Description: 
//*****************************************************************************
void DumpTokenUser (
	HANDLE	p_hToken,
	LPVOID	p_pTokenInformation,
	DWORD	p_dwTokenInformationLength)
{
	PTOKEN_USER l_pTokenUser = reinterpret_cast<PTOKEN_USER>(p_pTokenInformation);
	DumpSidAndAttributes (&l_pTokenUser->User, _T("TOKEN_USER.User"));
}
