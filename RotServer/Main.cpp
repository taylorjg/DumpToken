#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <comdef.h>

#include "..\DumpToken\DumpToken.h"

#import "..\TestObjectSvr\Debug\TestObjectSvr.tlb"

static HANDLE g_hStopEvent = NULL;

// _com_error exception caught - HRESULT is 0x80004015
// ErrorMessage: "The class is configured to run as a security id different from the caller"
//
// Customise the AccessPermission (self-relative SECURITY_DESCRIPTOR) using DCOMCnfg :-
//
// SELF
// SYSTEM
// Everyone
//
// Windows Registry Editor Version 5.00
//
// [HKEY_CLASSES_ROOT\AppID\RotServer.exe]
// @="RotServer"
// "AppID"="{B30BF967-CFC2-4bdf-9BA9-4568D8B4A45D}"
//
// [HKEY_CLASSES_ROOT\AppID\{B30BF967-CFC2-4bdf-9BA9-4568D8B4A45D}]
// "AccessPermission"=hex:01,00,04,80,58,00,00,00,68,00,00,00,00,00,00,00,14,00,\
//  00,00,02,00,44,00,03,00,00,00,00,00,14,00,03,00,00,00,01,01,00,00,00,00,00,\
//  01,00,00,00,00,00,00,14,00,07,00,00,00,01,01,00,00,00,00,00,05,0a,00,00,00,\
//  00,00,14,00,03,00,00,00,01,01,00,00,00,00,00,05,12,00,00,00,01,02,00,00,00,\
//  00,00,05,20,00,00,00,20,02,00,00,01,02,00,00,00,00,00,05,20,00,00,00,20,02,\
//  00,00
// @="RotServer"
// "RunAs"="Interactive User"


//*****************************************************************************
//* Function Name: ConsoleCtrlHandler
//*   Description: 
//*****************************************************************************
static BOOL WINAPI ConsoleCtrlHandler (DWORD p_dwCtrlType)
{
	BOOL l_bResult = FALSE;

	if (p_dwCtrlType == CTRL_C_EVENT) {
		(void) _tprintf (_T("CTRL_C_EVENT seen.\n"));
		if (!SetEvent (g_hStopEvent)) {
			DWORD l_dwLastError = GetLastError ();
			(void) _ftprintf (stderr, _T("SetEvent() failed with %ld\n"), l_dwLastError);
		}
		l_bResult = TRUE;
	}

	return l_bResult;
}


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
			// Create a stop event
			// Set a console control handler
			// - in the handler, set the stop event
			// Create an instance of CLSID_TestObject and register it in the ROT
			// Enter a loop calling MsgWaitForMultipleObjects()
			// - need to pump messages in a COM STA
			// - exit the loop when the stop event is signalled
			// Cleanup

			HANDLE l_hToken = NULL;

			if (OpenProcessToken (GetCurrentProcess (), TOKEN_QUERY | TOKEN_QUERY_SOURCE, &l_hToken))
			{
				DumpToken (l_hToken, TRUE);

				(void)CloseHandle (l_hToken);
				l_hToken = NULL;
			}
			else
			{
				DWORD l_dwLastError = GetLastError ();
				(void) _ftprintf (stderr, _T("OpenProcessToken() failed with %ld\n"), l_dwLastError);
				_com_issue_error (HRESULT_FROM_WIN32 (l_dwLastError));
			}

			g_hStopEvent = CreateEvent (NULL, TRUE, FALSE, NULL);
			if (g_hStopEvent == NULL) {
				DWORD l_dwLastError = GetLastError ();
				(void) _ftprintf (stderr, _T("CreateEvent() failed with %ld\n"), l_dwLastError);
				_com_issue_error (HRESULT_FROM_WIN32 (l_dwLastError));
			}

			// Before setting the console control handler to handle CTRL+C,
			// make a call with a 1st param of NULL and a 2nd param of FALSE to
			// ensure that CTRL+C signals are not being ignored by this process.
			if (!SetConsoleCtrlHandler (NULL, FALSE)) {
				DWORD l_dwLastError = GetLastError ();
				(void) _ftprintf (stderr, _T("SetConsoleCtrlHandler() failed with %ld\n"), l_dwLastError);
				_com_issue_error (HRESULT_FROM_WIN32 (l_dwLastError));
			}

			if (!SetConsoleCtrlHandler (ConsoleCtrlHandler, TRUE)) {
				DWORD l_dwLastError = GetLastError ();
				(void) _ftprintf (stderr, _T("SetConsoleCtrlHandler() failed with %ld\n"), l_dwLastError);
				_com_issue_error (HRESULT_FROM_WIN32 (l_dwLastError));
			}

			TestObjectSvrLib::ITestObjectPtr l_spTestObject;
			l_hr = l_spTestObject.CreateInstance (__uuidof (TestObjectSvrLib::TestObject));
			if (FAILED (l_hr)) _com_issue_error (l_hr);

			IMonikerPtr l_spMoniker;
			l_hr = CreateFileMoniker (L"TestObject", &l_spMoniker);
			if (FAILED (l_hr)) _com_issue_error (l_hr);

			IRunningObjectTablePtr l_spRunningObjectTable;
			l_hr = GetRunningObjectTable (0, &l_spRunningObjectTable);
			if (FAILED (l_hr)) _com_issue_error (l_hr);

			DWORD l_dwRunningObjectTableCookie = 0;
			DWORD l_dwFlags = ROTFLAGS_REGISTRATIONKEEPSALIVE | ROTFLAGS_ALLOWANYCLIENT;

			l_hr = l_spRunningObjectTable->Register (l_dwFlags, l_spTestObject, l_spMoniker, &l_dwRunningObjectTableCookie);
			if (FAILED (l_hr)) _com_issue_error (l_hr);

			(void) _tprintf (_T("l_dwRunningObjectTableCookie: %ld (0x%08lX)\n"), l_dwRunningObjectTableCookie, l_dwRunningObjectTableCookie);

			for (;;) {
				DWORD l_dwWaitResult = MsgWaitForMultipleObjects (1, &g_hStopEvent, FALSE, INFINITE, QS_ALLEVENTS);

				if (l_dwWaitResult == WAIT_FAILED) {
					DWORD l_dwLastError = GetLastError ();
					(void) _ftprintf (stderr, _T("MsgWaitForMultipleObjects() failed with %ld\n"), l_dwLastError);
					_com_issue_error (HRESULT_FROM_WIN32 (l_dwLastError));
				}

				if (l_dwWaitResult == WAIT_OBJECT_0) {
					(void) _tprintf (_T("Stop event is signalled - exiting.\n"));
					break;
				}

				for (;;) {
					MSG l_Msg = {0};
					BOOL l_bPeekMessage = ::PeekMessage (&l_Msg, NULL, 0, 0, PM_REMOVE);

					if (!l_bPeekMessage)
						break;

					LONG l_lResult = ::DispatchMessage (&l_Msg);
				}
			}

			l_hr = l_spRunningObjectTable->Revoke (l_dwRunningObjectTableCookie);
			if (FAILED (l_hr)) _com_issue_error (l_hr);
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

	if (g_hStopEvent != NULL) {
		CloseHandle (g_hStopEvent);
		g_hStopEvent = NULL;
	}

	return l_iResult;
}
