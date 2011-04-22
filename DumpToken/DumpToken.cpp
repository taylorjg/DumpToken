//*****************************************************************************
//* Description: DumpToken - dump information about a process/thread token.   *
//*                                                                           *
//* Author: Jon                                    Creation Date: 11-Apr-2011 *
//*****************************************************************************

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>
#include <comdef.h>

#include "Utils.h"

typedef void (*GET_TOKEN_INFORMATION_HANDLER)(
	HANDLE	p_hToken,
	LPVOID	p_pTokenInformation,
	DWORD	p_dwTokenInformationLength);

extern void DumpTokenUser					(HANDLE p_hToken, LPVOID p_pTokenInformation, DWORD p_dwTokenInformationLength);
extern void DumpTokenGroups					(HANDLE p_hToken, LPVOID p_pTokenInformation, DWORD p_dwTokenInformationLength);
extern void DumpTokenPrivileges				(HANDLE p_hToken, LPVOID p_pTokenInformation, DWORD p_dwTokenInformationLength);
extern void DumpTokenOwner					(HANDLE p_hToken, LPVOID p_pTokenInformation, DWORD p_dwTokenInformationLength);
extern void DumpTokenPrimaryGroup			(HANDLE p_hToken, LPVOID p_pTokenInformation, DWORD p_dwTokenInformationLength);
extern void DumpTokenDefaultDacl			(HANDLE p_hToken, LPVOID p_pTokenInformation, DWORD p_dwTokenInformationLength);
extern void DumpTokenSource					(HANDLE p_hToken, LPVOID p_pTokenInformation, DWORD p_dwTokenInformationLength);
extern void DumpTokenType					(HANDLE p_hToken, LPVOID p_pTokenInformation, DWORD p_dwTokenInformationLength);
extern void DumpTokenImpersonationLevel		(HANDLE p_hToken, LPVOID p_pTokenInformation, DWORD p_dwTokenInformationLength);
extern void DumpTokenStatistics				(HANDLE p_hToken, LPVOID p_pTokenInformation, DWORD p_dwTokenInformationLength);
extern void DumpTokenRestrictedSids			(HANDLE p_hToken, LPVOID p_pTokenInformation, DWORD p_dwTokenInformationLength);
extern void DumpTokenSessionId				(HANDLE p_hToken, LPVOID p_pTokenInformation, DWORD p_dwTokenInformationLength);
extern void DumpTokenGroupsAndPrivileges	(HANDLE p_hToken, LPVOID p_pTokenInformation, DWORD p_dwTokenInformationLength);
extern void DumpTokenSandBoxInert			(HANDLE p_hToken, LPVOID p_pTokenInformation, DWORD p_dwTokenInformationLength);
extern void DumpTokenElevationType			(HANDLE p_hToken, LPVOID p_pTokenInformation, DWORD p_dwTokenInformationLength);
extern void DumpTokenLinkedToken			(HANDLE p_hToken, LPVOID p_pTokenInformation, DWORD p_dwTokenInformationLength);
extern void DumpTokenOrigin					(HANDLE p_hToken, LPVOID p_pTokenInformation, DWORD p_dwTokenInformationLength);
extern void DumpTokenElevation				(HANDLE p_hToken, LPVOID p_pTokenInformation, DWORD p_dwTokenInformationLength);
extern void DumpTokenHasRestrictions		(HANDLE p_hToken, LPVOID p_pTokenInformation, DWORD p_dwTokenInformationLength);
extern void DumpTokenAccessInformation		(HANDLE p_hToken, LPVOID p_pTokenInformation, DWORD p_dwTokenInformationLength);
extern void DumpTokenVirtualizationAllowed	(HANDLE p_hToken, LPVOID p_pTokenInformation, DWORD p_dwTokenInformationLength);
extern void DumpTokenVirtualizationEnabled	(HANDLE p_hToken, LPVOID p_pTokenInformation, DWORD p_dwTokenInformationLength);
extern void DumpTokenIntegrityLevel			(HANDLE p_hToken, LPVOID p_pTokenInformation, DWORD p_dwTokenInformationLength);
extern void DumpTokenUIAccess				(HANDLE p_hToken, LPVOID p_pTokenInformation, DWORD p_dwTokenInformationLength);
extern void DumpTokenUIAccess				(HANDLE p_hToken, LPVOID p_pTokenInformation, DWORD p_dwTokenInformationLength);
extern void DumpTokenMandatoryPolicy		(HANDLE p_hToken, LPVOID p_pTokenInformation, DWORD p_dwTokenInformationLength);
extern void DumpTokenLogonSid				(HANDLE p_hToken, LPVOID p_pTokenInformation, DWORD p_dwTokenInformationLength);

//*****************************************************************************
//* Function Name: DumpTokenInformation
//*   Description: 
//*****************************************************************************
static void DumpTokenInformation (
	HANDLE							p_hToken,
	TOKEN_INFORMATION_CLASS			p_eTokenInformation,
	GET_TOKEN_INFORMATION_HANDLER	p_pfnTokenInformationHandler)
{
	BOOL l_bContinue = TRUE;
	DWORD l_dwRequiredSize = 0;

	// GetTokenInformation() fails with ERROR_BAD_LENGTH for some types of
	// information. And l_dwRequiredSize remains set to 0. These guys are all
	// just DWORDs so bypass the first call to GetTokenInformation() and
	// hardcode the required size to the size of a DWORD.
	if (p_eTokenInformation == TokenSessionId		||
		p_eTokenInformation == TokenSandBoxInert	||
		p_eTokenInformation == TokenLinkedToken		||
		p_eTokenInformation == TokenElevation)
	{
		l_dwRequiredSize = sizeof (DWORD);
	}
	else
	{
		if (GetTokenInformation (p_hToken, p_eTokenInformation, NULL, 0, &l_dwRequiredSize))
		{
			// We should never get here because we didn't pass in a buffer!
		}
		else
		{
			DWORD l_dwLastError = GetLastError ();

			if (l_dwLastError != ERROR_INSUFFICIENT_BUFFER)
			{
				_bstr_t l_sbstrTokenInformation = TokenInformationClassToString (p_eTokenInformation);
				LPCTSTR l_lpszTokenInformation = l_sbstrTokenInformation;

				TCHAR l_szFunctionName[100] = {0};
				(void) _stprintf_s (l_szFunctionName, 100, _T("GetTokenInformation(%s)"), l_lpszTokenInformation);

				ReportWin32Error (l_szFunctionName, l_dwLastError);

				l_bContinue = FALSE;
			}
		}
	}

	if (l_bContinue)
	{
		LPBYTE l_pTokenInformation = new BYTE[l_dwRequiredSize];
		DWORD l_dwTokenInformationLength = l_dwRequiredSize;
		DWORD l_dwReturnLength = 0;

		if (GetTokenInformation (
			p_hToken,
			p_eTokenInformation,
			l_pTokenInformation,
			l_dwTokenInformationLength,
			&l_dwReturnLength))
		{
			(*p_pfnTokenInformationHandler) (p_hToken, l_pTokenInformation, l_dwReturnLength);
		}
		else
		{
			DWORD l_dwLastError = GetLastError ();

			_bstr_t l_sbstrTokenInformation = TokenInformationClassToString (p_eTokenInformation);
			LPCTSTR l_lpszTokenInformation = l_sbstrTokenInformation;

			TCHAR l_szFunctionName[100] = {0};
			(void) _stprintf_s (l_szFunctionName, 100, _T("GetTokenInformation(%s)"), l_lpszTokenInformation);

			ReportWin32Error (l_szFunctionName, l_dwLastError);
		}

		delete[] l_pTokenInformation;
		l_pTokenInformation = NULL;
	}

	(void) _tprintf (_T("\n"));
}


//*****************************************************************************
//* Function Name: DumpToken
//*   Description: Dump all information about the given token to stdout.
//*****************************************************************************
void DumpToken (HANDLE p_hToken, BOOL p_bDumpLinkedToken)
{
	DumpTokenInformation (p_hToken, TokenUser,					&DumpTokenUser);
	DumpTokenInformation (p_hToken, TokenGroups,				&DumpTokenGroups);
	DumpTokenInformation (p_hToken, TokenPrivileges,			&DumpTokenPrivileges);
	DumpTokenInformation (p_hToken, TokenOwner,					&DumpTokenOwner);
	DumpTokenInformation (p_hToken, TokenPrimaryGroup,			&DumpTokenPrimaryGroup);
	DumpTokenInformation (p_hToken, TokenDefaultDacl,			&DumpTokenDefaultDacl);
	DumpTokenInformation (p_hToken, TokenSource,				&DumpTokenSource);
	DumpTokenInformation (p_hToken, TokenType,					&DumpTokenType);

	// Only makes sense for an impersonation token.
	if (IsImpersonationToken (p_hToken))
		DumpTokenInformation (p_hToken, TokenImpersonationLevel, &DumpTokenImpersonationLevel);

	DumpTokenInformation (p_hToken, TokenStatistics,			&DumpTokenStatistics);
	DumpTokenInformation (p_hToken, TokenRestrictedSids,		&DumpTokenRestrictedSids);
	DumpTokenInformation (p_hToken, TokenSessionId,				&DumpTokenSessionId);
	DumpTokenInformation (p_hToken, TokenGroupsAndPrivileges,	&DumpTokenGroupsAndPrivileges);
	// TokenSessionReference (Reserved)
	DumpTokenInformation (p_hToken, TokenSandBoxInert,			&DumpTokenSandBoxInert);
	// TokenAuditPolicy (Reserved)
	DumpTokenInformation (p_hToken, TokenOrigin,				&DumpTokenOrigin);
	DumpTokenInformation (p_hToken, TokenElevationType,			&DumpTokenElevationType);

	if (p_bDumpLinkedToken)
		DumpTokenInformation (p_hToken, TokenLinkedToken, &DumpTokenLinkedToken);

	DumpTokenInformation (p_hToken, TokenElevation,				&DumpTokenElevation);
	DumpTokenInformation (p_hToken, TokenHasRestrictions,		&DumpTokenHasRestrictions);
	DumpTokenInformation (p_hToken, TokenAccessInformation,		&DumpTokenAccessInformation);
	DumpTokenInformation (p_hToken, TokenVirtualizationAllowed,	&DumpTokenVirtualizationAllowed);
	DumpTokenInformation (p_hToken, TokenVirtualizationEnabled,	&DumpTokenVirtualizationEnabled);
	DumpTokenInformation (p_hToken, TokenIntegrityLevel,		&DumpTokenIntegrityLevel);
	DumpTokenInformation (p_hToken, TokenUIAccess,				&DumpTokenUIAccess);
	DumpTokenInformation (p_hToken, TokenMandatoryPolicy,		&DumpTokenMandatoryPolicy);
	DumpTokenInformation (p_hToken, TokenLogonSid,				&DumpTokenLogonSid);
}


//*****************************************************************************
//* Function Name: DumpProxyBlanket
//*   Description: Dump the COM security settings that are in effect for a
//*                given proxy object.
//*****************************************************************************
void DumpProxyBlanket (IUnknown* p_pUnknown, LPCTSTR p_lpszLabel)
{
	DWORD l_dwAuthnSvc = 0;
	DWORD l_dwAuthzSvc = 0;
	DWORD l_dwAuthnLevel = 0;
	DWORD l_dwImpLevel = 0;
	DWORD l_dwCapabilities = 0;

	HRESULT l_hr = CoQueryProxyBlanket (
		p_pUnknown,
		&l_dwAuthnSvc,
		&l_dwAuthzSvc,
		NULL,
		&l_dwAuthnLevel,
		&l_dwImpLevel,
		NULL,
		&l_dwCapabilities);

	if (SUCCEEDED (l_hr))
	{
		(void) _tprintf (_T("%s\n"), p_lpszLabel);
		(void) _tprintf (_T("Authentication Service: %s (%ld)\n"), static_cast<LPCTSTR>(AuthenticationServiceToString (l_dwAuthnSvc)), l_dwAuthnSvc);
		(void) _tprintf (_T("Authorization Service: %s (%ld)\n"), static_cast<LPCTSTR>(AuthorizationServiceToString (l_dwAuthzSvc)), l_dwAuthzSvc);
		(void) _tprintf (_T("Authorization Level: %s (%ld)\n"), static_cast<LPCTSTR>(AuthorizationLevelToString (l_dwAuthnLevel)), l_dwAuthnLevel);
		(void) _tprintf (_T("Impersonation Level: %s (%ld)\n"), static_cast<LPCTSTR>(ImpersonationLevelToString (l_dwImpLevel)), l_dwImpLevel);
		(void) _tprintf (_T("Capabilities: %s (%ld)\n"), static_cast<LPCTSTR>(EOleAuthenticationCapabilitiesToString (static_cast<EOLE_AUTHENTICATION_CAPABILITIES>(l_dwCapabilities))), l_dwCapabilities);
	}
}


//*****************************************************************************
//* Function Name: DumpClientBlanket
//*   Description: Dump the COM security settings that the client used when
//*                making the current COM method invokation.
//*****************************************************************************
void DumpClientBlanket ()
{
	DWORD l_dwAuthnSvc = 0;
	DWORD l_dwAuthzSvc = 0;
	LPOLESTR l_lposzServerPrincName = NULL;
	DWORD l_dwAuthnLevel = 0;
	// DWORD l_dwImpLevel = 0;
	DWORD l_dwCapabilities = 0;

	// The documentation says this regarding the 5th parameter (pImpLevel) :-
	//
	// pImpLevel 
	// [out] Must be NULL. This parameter is reserved for future use.
	//

	HRESULT l_hr = CoQueryClientBlanket (
		&l_dwAuthnSvc,
		&l_dwAuthzSvc,
		&l_lposzServerPrincName,
		&l_dwAuthnLevel,
		NULL, // &l_dwImpLevel,
		NULL,
		&l_dwCapabilities);

	if (SUCCEEDED (l_hr))
	{
		(void) _tprintf (_T("CoQueryClientBlanket() :-\n"));
		(void) _tprintf (_T("Authentication Service: %s (%ld)\n"), static_cast<LPCTSTR>(AuthenticationServiceToString (l_dwAuthnSvc)), l_dwAuthnSvc);
		(void) _tprintf (_T("Authorization Service: %s (%ld)\n"), static_cast<LPCTSTR>(AuthorizationServiceToString (l_dwAuthzSvc)), l_dwAuthzSvc);

		if (l_lposzServerPrincName == NULL)
			(void) _tprintf (_T("Server Principle Name: NULL\n"));
		else
			(void) _tprintf (_T("Server Principle Name: %s\n"), static_cast<LPCTSTR>(_bstr_t (l_lposzServerPrincName)));

		(void) _tprintf (_T("Authorization Level: %s (%ld)\n"), static_cast<LPCTSTR>(AuthorizationLevelToString (l_dwAuthnLevel)), l_dwAuthnLevel);
		// (void) _tprintf (_T("Impersonation Level: %s (%ld)\n"), static_cast<LPCTSTR>(ImpersonationLevelToString (l_dwImpLevel)), l_dwImpLevel);
		(void) _tprintf (_T("Capabilities: %s (%ld)\n"), static_cast<LPCTSTR>(EOleAuthenticationCapabilitiesToString (static_cast<EOLE_AUTHENTICATION_CAPABILITIES>(l_dwCapabilities))), l_dwCapabilities);

		CoTaskMemFree (l_lposzServerPrincName);
	}
}
