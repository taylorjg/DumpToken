#include "Utils.h"
#include <stdio.h>

//*****************************************************************************
//* Function Name: DumpTokenIntegrityLevel
//*   Description: 
//*****************************************************************************
void DumpTokenIntegrityLevel (
	HANDLE	p_hToken,
	LPVOID	p_pTokenInformation,
	DWORD	p_dwTokenInformationLength)
{
	PTOKEN_MANDATORY_LABEL l_pTokenMandatoryLabel = reinterpret_cast<PTOKEN_MANDATORY_LABEL>(p_pTokenInformation);
	DumpSidAndAttributes (&l_pTokenMandatoryLabel->Label, _T("TOKEN_MANDATORY_LABEL.Label"));
}
