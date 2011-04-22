#include "Utils.h"
#include <stdio.h>

//*****************************************************************************
//* Function Name: DumpTokenStatistics
//*   Description: 
//*****************************************************************************
void DumpTokenStatistics (
	HANDLE	p_hToken,
	LPVOID	p_pTokenInformation,
	DWORD	p_dwTokenInformationLength)
{
	PTOKEN_STATISTICS l_pTokenStatistics = reinterpret_cast<PTOKEN_STATISTICS>(p_pTokenInformation);

	(void) _tprintf (_T("TOKEN_STATISTICS.TokenId.LowPart: %ld (0x%08lX)\n"), l_pTokenStatistics->TokenId.LowPart, l_pTokenStatistics->TokenId.LowPart);
	(void) _tprintf (_T("TOKEN_STATISTICS.TokenId.HighPart: %ld (0x%08lX)\n"), l_pTokenStatistics->TokenId.HighPart, l_pTokenStatistics->TokenId.HighPart);
	(void) _tprintf (_T("TOKEN_STATISTICS.AuthenticationId.LowPart: %ld (0x%08lX)\n"), l_pTokenStatistics->AuthenticationId.LowPart, l_pTokenStatistics->AuthenticationId.LowPart);
	(void) _tprintf (_T("TOKEN_STATISTICS.AuthenticationId.HighPart: %ld (0x%08lX)\n"), l_pTokenStatistics->AuthenticationId.HighPart, l_pTokenStatistics->AuthenticationId.HighPart);
	(void) _tprintf (_T("TOKEN_STATISTICS.ExpirationTime.LowPart: %ld (0x%08lX)\n"), l_pTokenStatistics->ExpirationTime.LowPart, l_pTokenStatistics->ExpirationTime.LowPart);
	(void) _tprintf (_T("TOKEN_STATISTICS.ExpirationTime.HighPart: %ld (0x%08lX)\n"), l_pTokenStatistics->ExpirationTime.HighPart, l_pTokenStatistics->ExpirationTime.HighPart);
	(void) _tprintf (_T("TOKEN_STATISTICS.TokenType: %s\n"), static_cast<LPCTSTR>(TokenTypeToString (l_pTokenStatistics->TokenType)));
	(void) _tprintf (_T("TOKEN_STATISTICS.ImpersonationLevel: %s\n"), static_cast<LPCTSTR>(SecurityImpersonationLevelToString (l_pTokenStatistics->ImpersonationLevel)));
	(void) _tprintf (_T("TOKEN_STATISTICS.DynamicCharged: %ld (0x%08lX)\n"), l_pTokenStatistics->DynamicCharged);
	(void) _tprintf (_T("TOKEN_STATISTICS.DynamicAvailable: %ld (0x%08lX)\n"), l_pTokenStatistics->DynamicAvailable);
	(void) _tprintf (_T("TOKEN_STATISTICS.GroupCount: %ld\n"), l_pTokenStatistics->GroupCount);
	(void) _tprintf (_T("TOKEN_STATISTICS.PrivilegeCount: %ld\n"), l_pTokenStatistics->PrivilegeCount);
	(void) _tprintf (_T("TOKEN_STATISTICS.ModifiedId.LowPart: %ld (0x%08lX)\n"), l_pTokenStatistics->ModifiedId.LowPart, l_pTokenStatistics->ModifiedId.LowPart);
	(void) _tprintf (_T("TOKEN_STATISTICS.ModifiedId.HighPart: %ld (0x%08lX)\n"), l_pTokenStatistics->ModifiedId.HighPart, l_pTokenStatistics->ModifiedId.HighPart);
}
