#include <windows.h>
#include <stdio.h>
#include <sddl.h>
#include <aclapi.h>
#include <comdef.h>

#include "Utils.h"

typedef struct {
	long	lEnum;
	LPCTSTR lpszEnum;
} ENUM_TABLE_ENTRY;

#define CREATE_ENUM_TABLE_ENTRY(e) { e, _T(#e) }
#define ENUM_TABLE_AND_SIZE(EnumTable) (EnumTable), (sizeof ((EnumTable)) / sizeof (*(EnumTable)))

// TOKEN_INFORMATION_CLASS values.
static const ENUM_TABLE_ENTRY g_EnumTableTokenInformationClass[] = {
	CREATE_ENUM_TABLE_ENTRY (TokenUser),
	CREATE_ENUM_TABLE_ENTRY (TokenGroups),
	CREATE_ENUM_TABLE_ENTRY (TokenPrivileges),
	CREATE_ENUM_TABLE_ENTRY (TokenOwner),
	CREATE_ENUM_TABLE_ENTRY (TokenPrimaryGroup),
	CREATE_ENUM_TABLE_ENTRY (TokenDefaultDacl),
	CREATE_ENUM_TABLE_ENTRY (TokenSource),
	CREATE_ENUM_TABLE_ENTRY (TokenType),
	CREATE_ENUM_TABLE_ENTRY (TokenImpersonationLevel),
	CREATE_ENUM_TABLE_ENTRY (TokenStatistics),
	CREATE_ENUM_TABLE_ENTRY (TokenRestrictedSids),
	CREATE_ENUM_TABLE_ENTRY (TokenSessionId),
	CREATE_ENUM_TABLE_ENTRY (TokenGroupsAndPrivileges),
	CREATE_ENUM_TABLE_ENTRY (TokenSessionReference),
	CREATE_ENUM_TABLE_ENTRY (TokenSandBoxInert),
	CREATE_ENUM_TABLE_ENTRY (TokenAuditPolicy),
	CREATE_ENUM_TABLE_ENTRY (TokenOrigin),
	CREATE_ENUM_TABLE_ENTRY (TokenElevationType),
	CREATE_ENUM_TABLE_ENTRY (TokenLinkedToken),
	CREATE_ENUM_TABLE_ENTRY (TokenElevation),
	CREATE_ENUM_TABLE_ENTRY (TokenHasRestrictions),
	CREATE_ENUM_TABLE_ENTRY (TokenAccessInformation),
	CREATE_ENUM_TABLE_ENTRY (TokenVirtualizationAllowed),
	CREATE_ENUM_TABLE_ENTRY (TokenVirtualizationEnabled),
	CREATE_ENUM_TABLE_ENTRY (TokenIntegrityLevel),
	CREATE_ENUM_TABLE_ENTRY (TokenUIAccess),
	CREATE_ENUM_TABLE_ENTRY (TokenMandatoryPolicy),
	CREATE_ENUM_TABLE_ENTRY (TokenLogonSid)
};


// TOKEN_TYPE values.
static const ENUM_TABLE_ENTRY g_EnumTableTokenType[] = {
	CREATE_ENUM_TABLE_ENTRY (TokenPrimary),
	CREATE_ENUM_TABLE_ENTRY (TokenImpersonation)
};


// TOKEN_ELEVATION_TYPE values.
static const ENUM_TABLE_ENTRY g_EnumTableTokenElevationType[] = {
	CREATE_ENUM_TABLE_ENTRY (TokenElevationTypeDefault),
	CREATE_ENUM_TABLE_ENTRY (TokenElevationTypeFull),
	CREATE_ENUM_TABLE_ENTRY (TokenElevationTypeLimited)
};


// SECURITY_IMPERSONATION_LEVEL values.
static const ENUM_TABLE_ENTRY g_EnumTableSecurityImpersonationLevel[] = {
	CREATE_ENUM_TABLE_ENTRY (SecurityAnonymous),
	CREATE_ENUM_TABLE_ENTRY (SecurityIdentification),
	CREATE_ENUM_TABLE_ENTRY (SecurityImpersonation),
	CREATE_ENUM_TABLE_ENTRY (SecurityDelegation)
};


static const ENUM_TABLE_ENTRY g_EnumTableMandatoryPolicy[] = {
	CREATE_ENUM_TABLE_ENTRY (TOKEN_MANDATORY_POLICY_OFF),
	CREATE_ENUM_TABLE_ENTRY (TOKEN_MANDATORY_POLICY_NO_WRITE_UP),
	CREATE_ENUM_TABLE_ENTRY (TOKEN_MANDATORY_POLICY_NEW_PROCESS_MIN),
};


static const ENUM_TABLE_ENTRY g_EnumTableLuidAttributes[] = {
	CREATE_ENUM_TABLE_ENTRY (SE_PRIVILEGE_ENABLED_BY_DEFAULT),
	CREATE_ENUM_TABLE_ENTRY (SE_PRIVILEGE_ENABLED),
	CREATE_ENUM_TABLE_ENTRY (SE_PRIVILEGE_USED_FOR_ACCESS)
};


static const ENUM_TABLE_ENTRY g_EnumTableSidAttributes[] = {
	CREATE_ENUM_TABLE_ENTRY (SE_GROUP_MANDATORY),
	CREATE_ENUM_TABLE_ENTRY (SE_GROUP_ENABLED_BY_DEFAULT),
	CREATE_ENUM_TABLE_ENTRY (SE_GROUP_ENABLED),
	CREATE_ENUM_TABLE_ENTRY (SE_GROUP_OWNER),
	CREATE_ENUM_TABLE_ENTRY (SE_GROUP_USE_FOR_DENY_ONLY),
	CREATE_ENUM_TABLE_ENTRY (SE_GROUP_INTEGRITY),
	CREATE_ENUM_TABLE_ENTRY (SE_GROUP_INTEGRITY_ENABLED),
	CREATE_ENUM_TABLE_ENTRY (SE_GROUP_LOGON_ID),
	CREATE_ENUM_TABLE_ENTRY (SE_GROUP_RESOURCE)
};

// SID_NAME_USE values.
static const ENUM_TABLE_ENTRY g_EnumTableSidNameUse[] = {
	CREATE_ENUM_TABLE_ENTRY (SidTypeUser),
	CREATE_ENUM_TABLE_ENTRY (SidTypeGroup),
	CREATE_ENUM_TABLE_ENTRY (SidTypeDomain),
	CREATE_ENUM_TABLE_ENTRY (SidTypeAlias),
	CREATE_ENUM_TABLE_ENTRY (SidTypeWellKnownGroup),
	CREATE_ENUM_TABLE_ENTRY (SidTypeDeletedAccount),
	CREATE_ENUM_TABLE_ENTRY (SidTypeInvalid),
	CREATE_ENUM_TABLE_ENTRY (SidTypeUnknown),
	CREATE_ENUM_TABLE_ENTRY (SidTypeComputer),
	CREATE_ENUM_TABLE_ENTRY (SidTypeLabel)
};


static const ENUM_TABLE_ENTRY g_EnumTableAceType[] = {
	CREATE_ENUM_TABLE_ENTRY (ACCESS_ALLOWED_ACE_TYPE),
	CREATE_ENUM_TABLE_ENTRY (ACCESS_DENIED_ACE_TYPE),
	CREATE_ENUM_TABLE_ENTRY (SYSTEM_AUDIT_ACE_TYPE)
};


static const ENUM_TABLE_ENTRY g_EnumTableAceFlags[] = {
	CREATE_ENUM_TABLE_ENTRY (OBJECT_INHERIT_ACE),
	CREATE_ENUM_TABLE_ENTRY (CONTAINER_INHERIT_ACE),
	CREATE_ENUM_TABLE_ENTRY (NO_PROPAGATE_INHERIT_ACE),
	CREATE_ENUM_TABLE_ENTRY (INHERIT_ONLY_ACE),
	CREATE_ENUM_TABLE_ENTRY (INHERITED_ACE),
	CREATE_ENUM_TABLE_ENTRY (SUCCESSFUL_ACCESS_ACE_FLAG),
	CREATE_ENUM_TABLE_ENTRY (FAILED_ACCESS_ACE_FLAG)
};


static const ENUM_TABLE_ENTRY g_EnumTableAccessMask[] = {
	CREATE_ENUM_TABLE_ENTRY (DELETE),
	CREATE_ENUM_TABLE_ENTRY (READ_CONTROL),
	CREATE_ENUM_TABLE_ENTRY (WRITE_DAC),
	CREATE_ENUM_TABLE_ENTRY (WRITE_OWNER),
	CREATE_ENUM_TABLE_ENTRY (SYNCHRONIZE),
	CREATE_ENUM_TABLE_ENTRY (ACCESS_SYSTEM_SECURITY),
	CREATE_ENUM_TABLE_ENTRY (MAXIMUM_ALLOWED),
	CREATE_ENUM_TABLE_ENTRY (GENERIC_ALL),
	CREATE_ENUM_TABLE_ENTRY (GENERIC_EXECUTE),
	CREATE_ENUM_TABLE_ENTRY (GENERIC_WRITE),
	CREATE_ENUM_TABLE_ENTRY (GENERIC_READ)
};


static const ENUM_TABLE_ENTRY g_EnumTableAccessMode[] = {
	CREATE_ENUM_TABLE_ENTRY (NOT_USED_ACCESS),
	CREATE_ENUM_TABLE_ENTRY (GRANT_ACCESS),
	CREATE_ENUM_TABLE_ENTRY (SET_ACCESS),
	CREATE_ENUM_TABLE_ENTRY (DENY_ACCESS),
	CREATE_ENUM_TABLE_ENTRY (REVOKE_ACCESS),
	CREATE_ENUM_TABLE_ENTRY (SET_AUDIT_SUCCESS),
	CREATE_ENUM_TABLE_ENTRY (SET_AUDIT_FAILURE)
};


static const ENUM_TABLE_ENTRY g_EnumTableMultipleTrusteeOperation[] = {
	CREATE_ENUM_TABLE_ENTRY (NO_MULTIPLE_TRUSTEE),
	CREATE_ENUM_TABLE_ENTRY (TRUSTEE_IS_IMPERSONATE)
};


static const ENUM_TABLE_ENTRY g_EnumTableTrusteeForm[] = {
	CREATE_ENUM_TABLE_ENTRY (TRUSTEE_IS_SID),
	CREATE_ENUM_TABLE_ENTRY (TRUSTEE_IS_NAME),
	CREATE_ENUM_TABLE_ENTRY (TRUSTEE_BAD_FORM),
	CREATE_ENUM_TABLE_ENTRY (TRUSTEE_IS_OBJECTS_AND_SID),
	CREATE_ENUM_TABLE_ENTRY (TRUSTEE_IS_OBJECTS_AND_NAME)
};


static const ENUM_TABLE_ENTRY g_EnumTableTrusteeType[] = {
	CREATE_ENUM_TABLE_ENTRY (TRUSTEE_IS_UNKNOWN),
	CREATE_ENUM_TABLE_ENTRY (TRUSTEE_IS_USER),
	CREATE_ENUM_TABLE_ENTRY (TRUSTEE_IS_GROUP),
	CREATE_ENUM_TABLE_ENTRY (TRUSTEE_IS_DOMAIN),
	CREATE_ENUM_TABLE_ENTRY (TRUSTEE_IS_ALIAS),
	CREATE_ENUM_TABLE_ENTRY (TRUSTEE_IS_WELL_KNOWN_GROUP),
	CREATE_ENUM_TABLE_ENTRY (TRUSTEE_IS_DELETED),
	CREATE_ENUM_TABLE_ENTRY (TRUSTEE_IS_INVALID),
	CREATE_ENUM_TABLE_ENTRY (TRUSTEE_IS_COMPUTER)
};


static const ENUM_TABLE_ENTRY g_EnumTableAuthenticationService[] = {
	CREATE_ENUM_TABLE_ENTRY (RPC_C_AUTHN_NONE),
	CREATE_ENUM_TABLE_ENTRY (RPC_C_AUTHN_DCE_PRIVATE),
	CREATE_ENUM_TABLE_ENTRY (RPC_C_AUTHN_DCE_PUBLIC),
	CREATE_ENUM_TABLE_ENTRY (RPC_C_AUTHN_DEC_PUBLIC),
	CREATE_ENUM_TABLE_ENTRY (RPC_C_AUTHN_GSS_NEGOTIATE),
	CREATE_ENUM_TABLE_ENTRY (RPC_C_AUTHN_WINNT),
	CREATE_ENUM_TABLE_ENTRY (RPC_C_AUTHN_GSS_SCHANNEL),
	CREATE_ENUM_TABLE_ENTRY (RPC_C_AUTHN_GSS_KERBEROS),
	CREATE_ENUM_TABLE_ENTRY (RPC_C_AUTHN_DPA),
	CREATE_ENUM_TABLE_ENTRY (RPC_C_AUTHN_MSN),
	CREATE_ENUM_TABLE_ENTRY (RPC_C_AUTHN_DIGEST),
	CREATE_ENUM_TABLE_ENTRY (RPC_C_AUTHN_MQ),
	CREATE_ENUM_TABLE_ENTRY (RPC_C_AUTHN_DEFAULT)
};


static const ENUM_TABLE_ENTRY g_EnumTableAuthorizationService[] = {
	CREATE_ENUM_TABLE_ENTRY (RPC_C_AUTHZ_NONE),
	CREATE_ENUM_TABLE_ENTRY (RPC_C_AUTHZ_NAME),
	CREATE_ENUM_TABLE_ENTRY (RPC_C_AUTHZ_DCE),
	CREATE_ENUM_TABLE_ENTRY (RPC_C_AUTHZ_DEFAULT)
};


static const ENUM_TABLE_ENTRY g_EnumTableAuthorizationLevel[] = {
	CREATE_ENUM_TABLE_ENTRY (RPC_C_AUTHN_LEVEL_DEFAULT),
	CREATE_ENUM_TABLE_ENTRY (RPC_C_AUTHN_LEVEL_NONE),
	CREATE_ENUM_TABLE_ENTRY (RPC_C_AUTHN_LEVEL_CONNECT),
	CREATE_ENUM_TABLE_ENTRY (RPC_C_AUTHN_LEVEL_CALL),
	CREATE_ENUM_TABLE_ENTRY (RPC_C_AUTHN_LEVEL_PKT),
	CREATE_ENUM_TABLE_ENTRY (RPC_C_AUTHN_LEVEL_PKT_INTEGRITY),
	CREATE_ENUM_TABLE_ENTRY (RPC_C_AUTHN_LEVEL_PKT_PRIVACY)
};


static const ENUM_TABLE_ENTRY g_EnumTableImpersonationLevel[] = {
	CREATE_ENUM_TABLE_ENTRY (RPC_C_IMP_LEVEL_DEFAULT),
	CREATE_ENUM_TABLE_ENTRY (RPC_C_IMP_LEVEL_ANONYMOUS),
	CREATE_ENUM_TABLE_ENTRY (RPC_C_IMP_LEVEL_IDENTIFY),
	CREATE_ENUM_TABLE_ENTRY (RPC_C_IMP_LEVEL_IMPERSONATE),
	CREATE_ENUM_TABLE_ENTRY (RPC_C_IMP_LEVEL_DELEGATE)
};


static const ENUM_TABLE_ENTRY g_EnumTableEOleAuthenticationCapabilities[] = {
	CREATE_ENUM_TABLE_ENTRY (EOAC_NONE),
	CREATE_ENUM_TABLE_ENTRY (EOAC_MUTUAL_AUTH),
	CREATE_ENUM_TABLE_ENTRY (EOAC_STATIC_CLOAKING),
	CREATE_ENUM_TABLE_ENTRY (EOAC_DYNAMIC_CLOAKING),
	CREATE_ENUM_TABLE_ENTRY (EOAC_ANY_AUTHORITY),
	CREATE_ENUM_TABLE_ENTRY (EOAC_MAKE_FULLSIC),
	CREATE_ENUM_TABLE_ENTRY (EOAC_DEFAULT),
	CREATE_ENUM_TABLE_ENTRY (EOAC_SECURE_REFS),
	CREATE_ENUM_TABLE_ENTRY (EOAC_ACCESS_CONTROL),
	CREATE_ENUM_TABLE_ENTRY (EOAC_APPID),
	CREATE_ENUM_TABLE_ENTRY (EOAC_DYNAMIC),
	CREATE_ENUM_TABLE_ENTRY (EOAC_REQUIRE_FULLSIC),
	CREATE_ENUM_TABLE_ENTRY (EOAC_AUTO_IMPERSONATE),
	CREATE_ENUM_TABLE_ENTRY (EOAC_NO_CUSTOM_MARSHAL),
	CREATE_ENUM_TABLE_ENTRY (EOAC_DISABLE_AAA)
};


//*****************************************************************************
//* Function Name: EnumToString
//*   Description: Convert a given enumeration value to a string using the
//*                given table of values and matching string representations.
//*****************************************************************************
static _bstr_t EnumToString (
	long					p_lEnum,
	const ENUM_TABLE_ENTRY*	p_EnumTable,
	int						p_iEnumTableSize,
	BOOL					p_bEnumIsBitFlags)
{
	_bstr_t l_sbstrResult ((p_bEnumIsBitFlags) ? L"" : L"<unknown>");

	for (int i = 0; i < p_iEnumTableSize; i++)
	{
		const ENUM_TABLE_ENTRY* l_pEnumTableEntry = &p_EnumTable[i];

		if (p_bEnumIsBitFlags && l_pEnumTableEntry->lEnum != 0)
		{
			if ((l_pEnumTableEntry->lEnum & p_lEnum) == l_pEnumTableEntry->lEnum)
			{
				if (l_sbstrResult.length () > 0)
				{
					l_sbstrResult += L" | ";
				}

				l_sbstrResult += l_pEnumTableEntry->lpszEnum;
			}
		}
		else
		{
			if (l_pEnumTableEntry->lEnum == p_lEnum)
			{
				l_sbstrResult = l_pEnumTableEntry->lpszEnum;
				break;
			}
		}
	}

	return l_sbstrResult;
}


//*****************************************************************************
//* Function Name: TokenInformationClassToString
//*   Description: Convert the given token information class to a string.
//*****************************************************************************
_bstr_t TokenInformationClassToString (TOKEN_INFORMATION_CLASS p_eTokenInformation)
{
	return EnumToString (
		p_eTokenInformation,
		ENUM_TABLE_AND_SIZE (g_EnumTableTokenInformationClass),
		FALSE /* p_bEnumIsBitFlags */);
}


//*****************************************************************************
//* Function Name: TokenTypeToString
//*   Description: Convert the given token type to a string.
//*****************************************************************************
_bstr_t TokenTypeToString (TOKEN_TYPE p_eTokenType)
{
	return EnumToString (
		p_eTokenType,
		ENUM_TABLE_AND_SIZE (g_EnumTableTokenType),
		FALSE /* p_bEnumIsBitFlags */);
}


//*****************************************************************************
//* Function Name: TokenElevationTypeToString
//*   Description: Convert the given elevation level to a string.
//*****************************************************************************
_bstr_t TokenElevationTypeToString (TOKEN_ELEVATION_TYPE p_eTokenElevationType)
{
	return EnumToString (
		p_eTokenElevationType,
		ENUM_TABLE_AND_SIZE (g_EnumTableTokenElevationType),
		FALSE /* p_bEnumIsBitFlags */);
}


//*****************************************************************************
//* Function Name: SecurityImpersonationLevelToString
//*   Description: Convert the given impersonation level to a string.
//*****************************************************************************
_bstr_t SecurityImpersonationLevelToString (SECURITY_IMPERSONATION_LEVEL p_eSecurityImpersonationLevel)
{
	return EnumToString (
		p_eSecurityImpersonationLevel,
		ENUM_TABLE_AND_SIZE (g_EnumTableSecurityImpersonationLevel),
		FALSE /* p_bEnumIsBitFlags */);
}


//*****************************************************************************
//* Function Name: SecurityImpersonationLevelToString
//*   Description: Convert the given impersonation level to a string.
//*****************************************************************************
_bstr_t MandatoryPolicyToString (DWORD p_dwMandatoryPolicy)
{
	return EnumToString (
		p_dwMandatoryPolicy,
		ENUM_TABLE_AND_SIZE (g_EnumTableMandatoryPolicy),
		TRUE /* p_bEnumIsBitFlags */);
}


//*****************************************************************************
//* Function Name: LuidAttributesToString
//*   Description: Convert the given LUID attributes to a string.
//*****************************************************************************
_bstr_t LuidAttributesToString (DWORD p_dwLuidAttributes)
{
	return EnumToString (
		p_dwLuidAttributes,
		ENUM_TABLE_AND_SIZE (g_EnumTableLuidAttributes),
		TRUE /* p_bEnumIsBitFlags */);
}


//*****************************************************************************
//* Function Name: SidAttributesToString
//*   Description: Convert the given SID attributes to a string.
//*****************************************************************************
_bstr_t SidAttributesToString (DWORD p_dwSidAttributes)
{
	return EnumToString (
		p_dwSidAttributes,
		ENUM_TABLE_AND_SIZE (g_EnumTableSidAttributes),
		TRUE /* p_bEnumIsBitFlags */);
}


//*****************************************************************************
//* Function Name: SidNameUseToString
//*   Description: Convert the given SID_NAME_USE value to a string.
//*****************************************************************************
_bstr_t SidNameUseToString (SID_NAME_USE p_eSidNameUse)
{
	return EnumToString (
		p_eSidNameUse,
		ENUM_TABLE_AND_SIZE (g_EnumTableSidNameUse),
		FALSE /* p_bEnumIsBitFlags */);
}


//*****************************************************************************
//* Function Name: AceTypeToString
//*   Description: Convert the given ACE type value to a string.
//*****************************************************************************
_bstr_t AceTypeToString (DWORD p_dwAceType)
{
	return EnumToString (
		p_dwAceType,
		ENUM_TABLE_AND_SIZE (g_EnumTableAceType),
		FALSE /* p_bEnumIsBitFlags */);
}


//*****************************************************************************
//* Function Name: AceFlagsToString
//*   Description: Convert the given ACE flags to a string.
//*****************************************************************************
_bstr_t AceFlagsToString (DWORD p_dwAceFlags)
{
	return EnumToString (
		p_dwAceFlags,
		ENUM_TABLE_AND_SIZE (g_EnumTableAceFlags),
		TRUE /* p_bEnumIsBitFlags */);
}


//*****************************************************************************
//* Function Name: AccessMaskToString
//*   Description: Convert the given ACE access mask value to a string.
//*****************************************************************************
_bstr_t AccessMaskToString (DWORD p_dwAccessMask)
{
	return EnumToString (
		p_dwAccessMask,
		ENUM_TABLE_AND_SIZE (g_EnumTableAccessMask),
		TRUE /* p_bEnumIsBitFlags */);
}


//*****************************************************************************
//* Function Name: AccessModeToString
//*   Description: Convert the given ACE access mode value to a string.
//*****************************************************************************
_bstr_t AccessModeToString (DWORD p_dwAccessMode)
{
	return EnumToString (
		p_dwAccessMode,
		ENUM_TABLE_AND_SIZE (g_EnumTableAccessMode),
		FALSE /* p_bEnumIsBitFlags */);
}


//*****************************************************************************
//* Function Name: MultipleTrusteeOperationToString
//*   Description: Convert the given Trustee multiple trustee operation value
//*                to a string.
//*****************************************************************************
_bstr_t MultipleTrusteeOperationToString (MULTIPLE_TRUSTEE_OPERATION p_eMultipleTrusteeOperation)
{
	return EnumToString (
		p_eMultipleTrusteeOperation,
		ENUM_TABLE_AND_SIZE (g_EnumTableMultipleTrusteeOperation),
		FALSE /* p_bEnumIsBitFlags */);
}


//*****************************************************************************
//* Function Name: TrusteeFormToString
//*   Description: Convert the given trustee form value to a string.
//*****************************************************************************
_bstr_t TrusteeFormToString (TRUSTEE_FORM p_eTrusteeForm)
{
	return EnumToString (
		p_eTrusteeForm,
		ENUM_TABLE_AND_SIZE (g_EnumTableTrusteeForm),
		FALSE /* p_bEnumIsBitFlags */);
}


//*****************************************************************************
//* Function Name: TrusteeTypeToString
//*   Description: Convert the given trustee type value to a string.
//*****************************************************************************
_bstr_t TrusteeTypeToString (TRUSTEE_TYPE p_eTrusteeType)
{
	return EnumToString (
		p_eTrusteeType,
		ENUM_TABLE_AND_SIZE (g_EnumTableTrusteeType),
		FALSE /* p_bEnumIsBitFlags */);
}


//*****************************************************************************
//* Function Name: AuthenticationServiceToString
//*   Description: 
//*****************************************************************************
_bstr_t AuthenticationServiceToString (DWORD p_dwAuthenticationService)
{
	return EnumToString (
		p_dwAuthenticationService,
		ENUM_TABLE_AND_SIZE (g_EnumTableAuthenticationService),
		FALSE /* p_bEnumIsBitFlags */);
}


//*****************************************************************************
//* Function Name: AuthorizationServiceToString
//*   Description: 
//*****************************************************************************
_bstr_t AuthorizationServiceToString (DWORD p_dwAuthorizationService)
{
	return EnumToString (
		p_dwAuthorizationService,
		ENUM_TABLE_AND_SIZE (g_EnumTableAuthorizationService),
		FALSE /* p_bEnumIsBitFlags */);
}


//*****************************************************************************
//* Function Name: AuthorizationLevelToString
//*   Description: Convert the given authorization level value to a string.
//*****************************************************************************
_bstr_t AuthorizationLevelToString (DWORD p_dwAuthorizationLevel)
{
	return EnumToString (
		p_dwAuthorizationLevel,
		ENUM_TABLE_AND_SIZE (g_EnumTableAuthorizationLevel),
		FALSE /* p_bEnumIsBitFlags */);
}


//*****************************************************************************
//* Function Name: ImpersonationLevelToString
//*   Description: Convert the given impersonation level value to a string.
//*****************************************************************************
_bstr_t ImpersonationLevelToString (DWORD p_dwImpersonationLevel)
{
	return EnumToString (
		p_dwImpersonationLevel,
		ENUM_TABLE_AND_SIZE (g_EnumTableImpersonationLevel),
		FALSE /* p_bEnumIsBitFlags */);
}


//*****************************************************************************
//* Function Name: EOleAuthenticationCapabilitiesToString
//*   Description: Convert the given CoInitializeSecurity capabilities value
//*                to a string.
//*****************************************************************************
_bstr_t EOleAuthenticationCapabilitiesToString (EOLE_AUTHENTICATION_CAPABILITIES p_eEOleAuthenticationCapabilities)
{
	return EnumToString (
		p_eEOleAuthenticationCapabilities,
		ENUM_TABLE_AND_SIZE (g_EnumTableEOleAuthenticationCapabilities),
		TRUE /* p_bEnumIsBitFlags */);
}


//*****************************************************************************
//* Function Name: ReportWin32Error
//*   Description: Format a Win32 error code and write it to stderr.
//*****************************************************************************
void ReportWin32Error (
	LPCTSTR p_lpszFunctionName,
	DWORD p_dwLastError /* = GetLastError () */)
{
	TCHAR l_szErrorMessage[256];
	DWORD l_dwFlags = FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS;

	if (FormatMessage (	l_dwFlags,			// dwFlags
						NULL,				// lpSource
						p_dwLastError,		// dwMessageId
						0,					// dwLanguageId
						l_szErrorMessage,	// lpBuffer
						256,				// nSize
						NULL))				// Arguments
	{
		int cch = lstrlen (l_szErrorMessage);
		if (cch >= 2)
		{
			if (l_szErrorMessage[cch - 2] == _T('\r') &&
				l_szErrorMessage[cch - 1] == _T('\n'))
			{
				l_szErrorMessage[cch -2] = _T('\0');
			}
		}

		(void)_ftprintf (	stderr,
							_T("%s failed with %ld: %s\n"),
							p_lpszFunctionName,
							p_dwLastError,
							l_szErrorMessage);
	}
	else
	{
		(void)_ftprintf (	stderr,
							_T("%s failed with %ld\n"),
							p_lpszFunctionName,
							p_dwLastError);
	}
}


//*****************************************************************************
//* Function Name: RevertIfNecessary
//*   Description: 
//*****************************************************************************
static BOOL RevertIfNecessary ()
{
	BOOL l_bReverted = FALSE;

	IServerSecurityPtr l_spServerSecurity;
	HRESULT l_hr = CoGetCallContext (__uuidof (l_spServerSecurity), reinterpret_cast<void**>(&l_spServerSecurity));

	if (SUCCEEDED (l_hr))
	{
		l_bReverted = l_spServerSecurity->IsImpersonating ();
	}

	if (l_bReverted)
	{
		l_hr = l_spServerSecurity->RevertToSelf ();
		if (FAILED (l_hr))
		{
			(void) _ftprintf (stderr, _T("IServerSecurity::RevertToSelf() failed with 0x%08lX\n"), l_hr);
			l_bReverted = FALSE;
		}
	}

	return l_bReverted;
}


//*****************************************************************************
//* Function Name: Reimpersonate
//*   Description: 
//*****************************************************************************
static void Reimpersonate ()
{
	IServerSecurityPtr l_spServerSecurity;
	HRESULT l_hr = CoGetCallContext (__uuidof (l_spServerSecurity), reinterpret_cast<void**>(&l_spServerSecurity));

	l_hr = l_spServerSecurity->ImpersonateClient ();
	if (FAILED (l_hr))
	{
		(void) _ftprintf (stderr, _T("IServerSecurity::ImpersonateClient() failed with 0x%08lX\n"), l_hr);
	}
}


//*****************************************************************************
//* Function Name: GetPrivilegeDisplayName
//*   Description: Given a LUID, return the corresponding display name of the
//*                privilege.
//*****************************************************************************
_bstr_t GetPrivilegeDisplayName (PLUID p_pluid)
{
	BOOL l_bReverted = RevertIfNecessary ();

	_bstr_t l_sbstrResult (L"Unknown");

	TCHAR l_szName[256] = {0};
	DWORD l_dwName = 256;

	if (LookupPrivilegeName (NULL, p_pluid, l_szName, &l_dwName))
	{
		TCHAR l_szDisplayName[256] = {0};
		DWORD l_dwDisplayName = 256;
		DWORD l_dwLanguageId = 0;
		if (LookupPrivilegeDisplayName (NULL, l_szName, l_szDisplayName, &l_dwDisplayName, &l_dwLanguageId))
		{
			l_sbstrResult = l_szDisplayName;
		}
		else
		{
			ReportWin32Error (_T("LookupPrivilegeDisplayName"));
		}
	}
	else
	{
		DWORD l_dwLastError = GetLastError ();
		if (l_dwLastError != ERROR_NONE_MAPPED) {
			ReportWin32Error (_T("LookupPrivilegeName"), l_dwLastError);
		}
	}

	if (l_bReverted)
		Reimpersonate ();

	return l_sbstrResult;
}


//*****************************************************************************
//* Function Name: DumpSid
//*   Description: Dump information about the given SID.
//*****************************************************************************
void DumpSid (PSID p_pSid, LPCTSTR p_lpszLabel)
{
	BOOL l_bReverted = RevertIfNecessary ();

	(void) _tprintf (_T("%s\n"), p_lpszLabel);

	LPTSTR l_lpszStringSid = NULL;
	if (ConvertSidToStringSid (p_pSid, &l_lpszStringSid))
	{
		(void) _tprintf (_T("\tSid: %s\n"), l_lpszStringSid);
		LocalFree (l_lpszStringSid);
		l_lpszStringSid = NULL;
	}

	TCHAR l_szName[256] = {0};
	TCHAR l_szReferencedDomainName[256] = {0};
	DWORD l_dwName = 256;
	DWORD l_dwReferencedDomainName = 256;
	SID_NAME_USE l_eSidNameUse;

	if (LookupAccountSid (
		NULL,
		p_pSid,
		l_szName,
		&l_dwName,
		l_szReferencedDomainName,
		&l_dwReferencedDomainName,
		&l_eSidNameUse))
	{
		_bstr_t l_sbstrSidNameUse = SidNameUseToString (l_eSidNameUse);
		LPCTSTR l_lpszSidNameUse = static_cast<LPCTSTR>(l_sbstrSidNameUse);

		if (l_dwReferencedDomainName > 0) {
			(void) _tprintf (_T("\tSid: %s\\%s (%s)\n"), l_szReferencedDomainName, l_szName, l_lpszSidNameUse);
		}
		else {
			(void) _tprintf (_T("\tSid: %s (%s)\n"), l_szName, l_lpszSidNameUse);
		}
	}
	else
	{
		DWORD l_dwLastError = GetLastError ();
		if (l_dwLastError != ERROR_NONE_MAPPED) {
			ReportWin32Error (_T("LookupAccountSid"), l_dwLastError);
		}
	}

	if (l_bReverted)
		Reimpersonate ();
}


//*****************************************************************************
//* Function Name: DumpSidAndAttributes
//*   Description: Dump information about the given SID and its attributes.
//*****************************************************************************
void DumpSidAndAttributes (PSID_AND_ATTRIBUTES p_pSidAndAttributes, LPCTSTR p_lpszLabel)
{
	DumpSid (p_pSidAndAttributes->Sid, p_lpszLabel);

	(void) _tprintf (
		_T("\tAttributes: %s (0x%08lX)\n"),
		static_cast<LPCTSTR>(SidAttributesToString (p_pSidAndAttributes->Attributes)),
		p_pSidAndAttributes->Attributes);
}


//*****************************************************************************
//* Function Name: DumpSidAndAttributesHash
//*   Description: 
//*****************************************************************************
void DumpSidAndAttributesHash (PSID_AND_ATTRIBUTES_HASH p_pSidAndAttributesHash, LPCTSTR p_lpszLabel)
{
	(void) _tprintf (_T("%s\n"), p_lpszLabel);

	(void) _tprintf (_T("\tSidCount: %ld\n"), p_pSidAndAttributesHash->SidCount);

	for (DWORD i = 0; i < p_pSidAndAttributesHash->SidCount; i++)
	{
		TCHAR l_szLabel[100] = {0};
		(void) _stprintf_s (l_szLabel, 100, _T("\tSidAttr[%ld]"), i);

		PSID_AND_ATTRIBUTES l_pSidAndAttributes = &p_pSidAndAttributesHash->SidAttr[i];
		DumpSidAndAttributes (l_pSidAndAttributes, l_szLabel);
	}

	for (DWORD i = 0; i < p_pSidAndAttributesHash->SidCount; i++)
	{
#if defined(_WIN64)
		// typedef unsigned __int64 ULONG_PTR;
		(void) _tprintf (_T("\tHash[%ld]: %I64d (0x%016I64X)\n"), i, p_pSidAndAttributesHash->Hash[i], p_pSidAndAttributesHash->Hash[i]);
#else
		// typedef unsigned long ULONG_PTR;
		(void) _tprintf (_T("\tHash[%ld]: %ld (0x%08lX)\n"), i, p_pSidAndAttributesHash->Hash[i], p_pSidAndAttributesHash->Hash[i]);
#endif
	}
}


//*****************************************************************************
//* Function Name: DumpLuidAndAttributes
//*   Description: 
//*****************************************************************************
void DumpLuidAndAttributes (PLUID_AND_ATTRIBUTES p_pLuidAndAttributes, LPCTSTR p_lpszLabel)
{
	(void) _tprintf (
		_T("%s.Luid: \"%s\" %ld (0x%08lX), %ld (0x%08lX)\n"),
		p_lpszLabel,
		static_cast<LPCTSTR>(GetPrivilegeDisplayName (&p_pLuidAndAttributes->Luid)),
		p_pLuidAndAttributes->Luid.LowPart,
		p_pLuidAndAttributes->Luid.LowPart,
		p_pLuidAndAttributes->Luid.HighPart,
		p_pLuidAndAttributes->Luid.HighPart);

	(void) _tprintf (
		_T("%s.Attributes: %s (0x%08lX)\n"),
		p_lpszLabel,
		static_cast<LPCTSTR>(LuidAttributesToString (p_pLuidAndAttributes->Attributes)),
		p_pLuidAndAttributes->Attributes);
}


//*****************************************************************************
//* Function Name: DumpAcl
//*   Description: Dump an ACL using GetExplicitEntriesFromAcl().
//*****************************************************************************
void DumpAcl (PACL p_pAcl, LPCTSTR p_lpszLabel)
{
	(void) _tprintf (_T("%s\n"), p_lpszLabel);

	ULONG l_ulCountOfExplicitEntries = 0;
	PEXPLICIT_ACCESS l_rgExplicitEntries = NULL;

	DWORD l_dwResult = GetExplicitEntriesFromAcl (p_pAcl, &l_ulCountOfExplicitEntries, &l_rgExplicitEntries);

	if (l_dwResult == ERROR_SUCCESS)
	{
		for (ULONG i = 0; i < l_ulCountOfExplicitEntries; i++)
		{
			PEXPLICIT_ACCESS l_pExplicitEntry = &l_rgExplicitEntries[i];

			(void) _tprintf (
				_T("\tACE[%ld].grfAccessPermissions: %s (0x%08lX)\n"),
				i,
				static_cast<LPCTSTR>(AccessMaskToString (l_pExplicitEntry->grfAccessPermissions)),
				l_pExplicitEntry->grfAccessPermissions);

			(void) _tprintf (
				_T("\tACE[%ld].grfAccessMode: %s (0x%08X)\n"),
				i,
				static_cast<LPCTSTR>(AccessModeToString (l_pExplicitEntry->grfAccessMode)),
				l_pExplicitEntry->grfAccessMode);

			(void) _tprintf (
				_T("\tACE[%ld].grfInheritance: %s (0x%08lX)\n"),
				i,
				static_cast<LPCTSTR>(AceFlagsToString (l_pExplicitEntry->grfInheritance)),
				l_pExplicitEntry->grfInheritance);

			(void) _tprintf (
				_T("\tACE[%ld].Trustee.MultipleTrusteeOperation: %s (0x%08X)\n"),
				i,
				static_cast<LPCTSTR>(MultipleTrusteeOperationToString (l_pExplicitEntry->Trustee.MultipleTrusteeOperation)),
				l_pExplicitEntry->Trustee.MultipleTrusteeOperation);

			(void) _tprintf (
				_T("\tACE[%ld].Trustee.TrusteeForm: %s (0x%08X)\n"),
				i,
				static_cast<LPCTSTR>(TrusteeFormToString (l_pExplicitEntry->Trustee.TrusteeForm)),
				l_pExplicitEntry->Trustee.TrusteeForm);

			(void) _tprintf (
				_T("\tACE[%ld].Trustee.TrusteeType: %s (0x%08X)\n"),
				i,
				static_cast<LPCTSTR>(TrusteeTypeToString (l_pExplicitEntry->Trustee.TrusteeType)),
				l_pExplicitEntry->Trustee.TrusteeType);

			switch (l_pExplicitEntry->Trustee.TrusteeForm)
			{
				case TRUSTEE_IS_SID:
					DumpSid (l_pExplicitEntry->Trustee.ptstrName, _T("\tTrustee.ptstrName"));
					break;
				case TRUSTEE_IS_NAME:
					(void) _tprintf (_T("\tTrustee.ptstrName: \"%s\""), l_pExplicitEntry->Trustee.ptstrName);
					break;
				case TRUSTEE_IS_OBJECTS_AND_SID:
					// TODO: Complete this...
					break;
				case TRUSTEE_IS_OBJECTS_AND_NAME:
					// TODO: Complete this...
					break;
			}

			(void) _tprintf (_T("\n"));
		}

		LocalFree (l_rgExplicitEntries);
		l_rgExplicitEntries = NULL;
	}
	else
	{
		ReportWin32Error (_T("GetExplicitEntriesFromAcl"), l_dwResult);
	}
}


//*****************************************************************************
//* Function Name: DumpAcl2
//*   Description: Dump an ACL using GetAclInformation(), GetAce(), etc.
//*****************************************************************************
void DumpAcl2 (PACL p_pAcl, LPCTSTR p_lpszLabel)
{
	(void) _tprintf (_T("%s\n"), p_lpszLabel);

	ACL_SIZE_INFORMATION l_AclSizeInformation = {0};

	if (GetAclInformation (
		p_pAcl,
		&l_AclSizeInformation,
		sizeof (l_AclSizeInformation),
		AclSizeInformation))
	{
		for (DWORD i = 0; i < l_AclSizeInformation.AceCount; i++)
		{
			LPVOID l_pAce = NULL;
			if (GetAce (p_pAcl, i, &l_pAce))
			{
				PACE_HEADER l_pAceHeader = reinterpret_cast<PACE_HEADER>(l_pAce);
				(void) _tprintf (_T("\tACE[%ld].Header.AceType: %s (%ld)\n"), i, static_cast<LPCTSTR>(AceTypeToString (l_pAceHeader->AceType)), l_pAceHeader->AceType);
				(void) _tprintf (_T("\tACE[%ld].Header.AceFlags: %s (0x%08lX)\n"), i, static_cast<LPCTSTR>(AceFlagsToString (l_pAceHeader->AceFlags)), l_pAceHeader->AceFlags);
				(void) _tprintf (_T("\tACE[%ld].Header.AceSize: %ld (0x%08lX)\n"), i, l_pAceHeader->AceSize, l_pAceHeader->AceSize);

				TCHAR l_szLabel[100];
				(void) _stprintf_s (l_szLabel, 100, _T("\tACE[%ld].Sid"), i);

				switch (l_pAceHeader->AceType)
				{
					case ACCESS_ALLOWED_ACE_TYPE:
						{
							PACCESS_ALLOWED_ACE l_pAccessAllowedAce = reinterpret_cast<PACCESS_ALLOWED_ACE>(l_pAce);
							(void) _tprintf (_T("\tACE[%ld].Mask: %s (0x%08lX)\n"), i, static_cast<LPCTSTR>(AccessMaskToString (l_pAccessAllowedAce->Mask)), l_pAccessAllowedAce->Mask);
							DumpSid (&l_pAccessAllowedAce->SidStart, l_szLabel);
						}
						break;

					case ACCESS_DENIED_ACE_TYPE:
						{
							PACCESS_DENIED_ACE l_pAccessDeniedAce = reinterpret_cast<PACCESS_DENIED_ACE>(l_pAce);
							(void) _tprintf (_T("\tACE[%ld].Mask: %s (0x%08lX)\n"), i, static_cast<LPCTSTR>(AccessMaskToString (l_pAccessDeniedAce->Mask)), l_pAccessDeniedAce->Mask);
							DumpSid (&l_pAccessDeniedAce->SidStart, l_szLabel);
						}
						break;

					case SYSTEM_AUDIT_ACE_TYPE:
						{
							PSYSTEM_AUDIT_ACE l_pSystemAuditAce = reinterpret_cast<PSYSTEM_AUDIT_ACE>(l_pAce);
							(void) _tprintf (_T("\tACE[%ld].Mask: %s (0x%08lX)\n"), i, static_cast<LPCTSTR>(AccessMaskToString (l_pSystemAuditAce->Mask)), l_pSystemAuditAce->Mask);
							DumpSid (&l_pSystemAuditAce->SidStart, l_szLabel);
						}
						break;
				}

				(void) _tprintf (_T("\n"));
			}
			else
			{
				ReportWin32Error (_T("GetAce"));
			}
		}
	}
	else
	{
		ReportWin32Error (_T("GetAclInformation"));
	}
}


//*****************************************************************************
//* Function Name: IsImpersonationToken
//*   Description: Return TRUE if the given token is an impersonation token.
//*****************************************************************************
BOOL IsImpersonationToken (HANDLE p_hToken)
{
	BOOL l_bResult = FALSE;

	TOKEN_TYPE l_TokenType;
	DWORD l_dwTokenInformationLength = sizeof (l_TokenType);
	DWORD l_dwReturnLength = 0;

	if (GetTokenInformation (
		p_hToken,
		TokenType,
		&l_TokenType,
		l_dwTokenInformationLength,
		&l_dwReturnLength))
	{
		l_bResult = (l_TokenType == TokenImpersonation);
	}

	return l_bResult;
}
