#include "Utils.h"
#include <stdio.h>

//*****************************************************************************
//* Function Name: DumpTokenDefaultDacl
//*   Description: 
//*****************************************************************************
void DumpTokenDefaultDacl (
	HANDLE	p_hToken,
	LPVOID	p_pTokenInformation,
	DWORD	p_dwTokenInformationLength)
{
	PTOKEN_DEFAULT_DACL l_pTokenDefaultDacl = reinterpret_cast<PTOKEN_DEFAULT_DACL>(p_pTokenInformation);
	DumpAcl (l_pTokenDefaultDacl->DefaultDacl, _T("TOKEN_DEFAULT_DACL"));
	DumpAcl2 (l_pTokenDefaultDacl->DefaultDacl, _T("TOKEN_DEFAULT_DACL"));
}
