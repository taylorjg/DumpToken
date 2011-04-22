#include "Utils.h"
#include "DumpToken.h"
#include <stdio.h>

//*****************************************************************************
//* Function Name: DumpTokenLinkedToken
//*   Description: 
//*****************************************************************************
void DumpTokenLinkedToken (
	HANDLE	p_hToken,
	LPVOID	p_pTokenInformation,
	DWORD	p_dwTokenInformationLength)
{
	PTOKEN_LINKED_TOKEN l_pTokenLinkedToken = reinterpret_cast<PTOKEN_LINKED_TOKEN>(p_pTokenInformation);

	if (l_pTokenLinkedToken->LinkedToken != NULL)
	{
		(void) _tprintf (_T("******************** TOKEN_LINKED_TOKEN.LinkedToken (start) ********************\n"));
		DumpToken (l_pTokenLinkedToken->LinkedToken, FALSE);
		(void) _tprintf (_T("******************** TOKEN_LINKED_TOKEN.LinkedToken (end) ********************\n"));
	}
	else
	{
		(void) _tprintf (_T("TOKEN_LINKED_TOKEN.LinkedToken: NULL\n"));
	}
}
