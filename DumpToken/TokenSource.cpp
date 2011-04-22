#include "Utils.h"
#include <stdio.h>

//*****************************************************************************
//* Function Name: DumpTokenSource
//*   Description: 
//*****************************************************************************
void DumpTokenSource (
	HANDLE	p_hToken,
	LPVOID	p_pTokenInformation,
	DWORD	p_dwTokenInformationLength)
{
	PTOKEN_SOURCE l_pTokenSource = reinterpret_cast<PTOKEN_SOURCE>(p_pTokenInformation);

	CHAR l_szSourceName[TOKEN_SOURCE_LENGTH + 1] = {0};
	CopyMemory (l_szSourceName, l_pTokenSource->SourceName, TOKEN_SOURCE_LENGTH);
	_bstr_t l_sbstrSourceName (l_szSourceName);

	(void) _tprintf (_T("TOKEN_SOURCE.SourceName: \"%s\"\n"), static_cast<LPCTSTR>(l_sbstrSourceName));

	(void) _tprintf (
		_T("TOKEN_SOURCE.SourceIdentifier.LowPart: %ld (0x%08lX)\n"),
		l_pTokenSource->SourceIdentifier.LowPart,
		l_pTokenSource->SourceIdentifier.LowPart);

	(void) _tprintf (
		_T("TOKEN_SOURCE.SourceIdentifier.HighPart: %ld (0x%08lX)\n"),
		l_pTokenSource->SourceIdentifier.HighPart,
		l_pTokenSource->SourceIdentifier.HighPart);
}
