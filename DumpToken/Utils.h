#ifndef __UTILS_H__
#define __UTILS_H__

#include <windows.h>
#include <tchar.h>
#include <comdef.h>
#include <accctrl.h>

extern void ReportWin32Error (LPCTSTR p_lpszFunctionName, DWORD p_dwLastError = GetLastError ());

extern _bstr_t GetPrivilegeDisplayName (PLUID p_pluid);

extern _bstr_t TokenInformationClassToString (TOKEN_INFORMATION_CLASS p_eTokenInformation);
extern _bstr_t TokenTypeToString (TOKEN_TYPE p_eTokenType);
extern _bstr_t TokenElevationTypeToString (TOKEN_ELEVATION_TYPE p_eTokenElevationType);
extern _bstr_t SecurityImpersonationLevelToString (SECURITY_IMPERSONATION_LEVEL p_eSecurityImpersonationLevel);
extern _bstr_t MandatoryPolicyToString (DWORD p_dwMandatoryPolicy);
extern _bstr_t LuidAttributesToString (DWORD p_dwLuidAttributes);
extern _bstr_t SidAttributesToString (DWORD p_dwSidAttributes);
extern _bstr_t SidNameUseToString(SID_NAME_USE p_eSidNameUse);
extern _bstr_t AceTypeToString (DWORD p_dwAceType);
extern _bstr_t AceFlagsToString (DWORD p_dwAceFlags);
extern _bstr_t AccessMaskToString (DWORD p_dwAccessMask);
extern _bstr_t AccessModeToString (DWORD p_dwAccessMode);
extern _bstr_t MultipleTrusteeOperationToString (MULTIPLE_TRUSTEE_OPERATION p_eMultipleTrusteeOperation);
extern _bstr_t TrusteeFormToString (TRUSTEE_FORM p_eTrusteeForm);
extern _bstr_t TrusteeTypeToString (TRUSTEE_TYPE p_eTrusteeType);
extern _bstr_t AuthenticationServiceToString (DWORD p_dwAuthenticationService);
extern _bstr_t AuthorizationServiceToString (DWORD p_dwAuthorizationService);
extern _bstr_t AuthorizationLevelToString (DWORD p_dwAuthorizationLevel);
extern _bstr_t ImpersonationLevelToString (DWORD p_dwImpersonationLevel);
extern _bstr_t EOleAuthenticationCapabilitiesToString (EOLE_AUTHENTICATION_CAPABILITIES p_eEOleAuthenticationCapabilities);

extern void DumpSid (PSID p_pSid, LPCTSTR p_lpszLabel);
extern void DumpSidAndAttributes (PSID_AND_ATTRIBUTES p_pSidAndAttributes, LPCTSTR p_lpszLabel);
extern void DumpSidAndAttributesHash (PSID_AND_ATTRIBUTES_HASH p_pSidAndAttributesHash, LPCTSTR p_lpszLabel);
extern void DumpLuidAndAttributes (PLUID_AND_ATTRIBUTES p_pLuidAndAttributes, LPCTSTR p_lpszLabel);
extern void DumpAcl (PACL p_pAcl, LPCTSTR p_lpszLabel);
extern void DumpAcl2 (PACL p_pAcl, LPCTSTR p_lpszLabel);

extern BOOL IsImpersonationToken (HANDLE p_hToken);

#endif
