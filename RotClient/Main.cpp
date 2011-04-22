#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <comdef.h>

#include "..\DumpToken\DumpToken.h"

#import "..\TestObjectSvr\Debug\TestObjectSvr.tlb"

//*****************************************************************************
//* Function Name: main
//*   Description: Main entry point.
//*****************************************************************************
int main ()
{
	int l_iResult = EXIT_SUCCESS;

	try {
		HRESULT l_hr = CoInitialize (NULL);
		if (FAILED (l_hr)) _com_issue_error (l_hr);

		try {
			// Retrieve ITestObject interface pointer from the ROT
			// Invoke ITestObject::DumpMyToken

			// Set process wide COM security settings.
			l_hr = CoInitializeSecurity (
				NULL,							// pSecDesc
				-1,								// cAuthSvc
				NULL,							// asAuthSvc
				NULL,							// pReserved1
				RPC_C_AUTHN_LEVEL_CONNECT,		// dwAuthnLevel
				RPC_C_IMP_LEVEL_IDENTIFY,		// dwImpLevel
				NULL,							// pAuthList
				EOAC_NONE,						// dwCapabilities
				NULL);							// pReserved3
			if (FAILED (l_hr)) _com_issue_error (l_hr);

			IRunningObjectTablePtr l_spRunningObjectTable;
			l_hr = GetRunningObjectTable (0, &l_spRunningObjectTable);
			if (FAILED (l_hr)) _com_issue_error (l_hr);

			IMonikerPtr l_spMoniker;
			l_hr = CreateFileMoniker (L"TestObject", &l_spMoniker);
			if (FAILED (l_hr)) _com_issue_error (l_hr);

// The GetObject macro business re the Win32 ::GetObjectA / ::GetObjectW function
// interferes with us trying to call the IRunningObjectTable::GetObject method
// so let's get rid of the macro.
#ifdef GETOBJECT
#undef GETOBJECT
#endif

			IUnknownPtr l_spUnknown;
			l_hr = l_spRunningObjectTable->GetObject (l_spMoniker, &l_spUnknown);
			if (FAILED (l_hr)) _com_issue_error (l_hr);

			TestObjectSvrLib::ITestObjectPtr l_spTestObject (l_spUnknown);
			if (l_spTestObject) {

				DumpProxyBlanket (
					l_spTestObject.GetInterfacePtr (),
					_T("Proxy object security settings before calling CoSetProxyBlanket():"));

				l_spTestObject->DumpToken ();

				TestObjectSvrLib::ITestObjectPtr l_spTestObjectCopy;
				l_hr = CoCopyProxy (l_spTestObject.GetInterfacePtr (), reinterpret_cast<IUnknown**>(&l_spTestObjectCopy));
				if (FAILED (l_hr)) _com_issue_error (l_hr);

				DWORD l_dwAuthnSvc = 0;
				DWORD l_dwAuthzSvc = 0;
				DWORD l_dwAuthnLevel = 0;
				DWORD l_dwImpLevel = 0;
				DWORD l_dwCapabilities = 0;

				// Retrieve the current proxy blanket settings on our proxy object.
				l_hr = CoQueryProxyBlanket (
					l_spTestObjectCopy,
					&l_dwAuthnSvc,
					&l_dwAuthzSvc,
					NULL,
					&l_dwAuthnLevel,
					&l_dwImpLevel,
					NULL,
					&l_dwCapabilities);
				if (FAILED (l_hr)) _com_issue_error (l_hr);

				// Set a different impersonation level on our proxy object.
				l_hr = CoSetProxyBlanket (
					l_spTestObjectCopy,
					l_dwAuthnSvc,
					l_dwAuthzSvc,
					NULL,
					l_dwAuthnLevel,
					RPC_C_IMP_LEVEL_DELEGATE,
					NULL,
					l_dwCapabilities);
				if (FAILED (l_hr)) _com_issue_error (l_hr);

				DumpProxyBlanket (
					l_spTestObjectCopy.GetInterfacePtr (),
					_T("Proxy object security settings after calling CoSetProxyBlanket():"));

				l_spTestObjectCopy->DumpToken ();
			}
		}
		catch (const _com_error& _ce) {
			(void) _ftprintf (stderr, _T("_com_error exception caught - HRESULT is 0x%08X\n"), _ce.Error ());

			try {
				// Try to get rich error information first - via IErrorInfo::GetDescription.
				_bstr_t l_sbstrDescription = _ce.Description ();
				if (l_sbstrDescription.length () > 0) {
					(void) _ftprintf (stderr, _T("Description: \"%s\"\n"), static_cast<LPCTSTR>(l_sbstrDescription));
				}
				else {
					// Failing that, fall back on a lookup of the error code - via FormatMessage().
					LPCTSTR l_lpszErrorMessage = _ce.ErrorMessage ();
					if (l_lpszErrorMessage != NULL) {
						(void) _ftprintf (stderr, _T("ErrorMessage: \"%s\"\n"), l_lpszErrorMessage);
					}
				}
			}
			catch (const _com_error&) {
			}

			l_iResult = EXIT_FAILURE;
		}

		CoUninitialize ();
	}
	catch (const _com_error& _ce) {
		(void) _ftprintf (stderr, _T("CoInitialize() failed - HRESULT is 0x%08X\n"), _ce.Error ());
		l_iResult = EXIT_FAILURE;
	}

	return l_iResult;
}
