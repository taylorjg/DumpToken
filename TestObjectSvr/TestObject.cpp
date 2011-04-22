#include "stdafx.h"
#include "TestObject.h"
#include "..\DumpToken\DumpToken.h"

//*****************************************************************************
//* Function Name: InterfaceSupportsErrorInfo
//*   Description: 
//*****************************************************************************
STDMETHODIMP CTestObject::InterfaceSupportsErrorInfo (REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ITestObject
	};

	for (int i = 0; i < sizeof (arr) / sizeof (*arr); i++)
	{
		if (InlineIsEqualGUID (*arr[i], riid))
			return S_OK;
	}

	return S_FALSE;
}


//*****************************************************************************
//* Function Name: DumpToken
//*   Description: 
//*****************************************************************************
STDMETHODIMP CTestObject::DumpToken (void)
{
	(void) _tprintf (_T("CTestObject::DumpToken\n"));

	DumpClientBlanket ();

	HRESULT l_hr = CoImpersonateClient ();

	if (SUCCEEDED (l_hr)) {
		HANDLE l_hToken = NULL;

		if (OpenThreadToken (GetCurrentThread (), TOKEN_QUERY | TOKEN_QUERY_SOURCE, TRUE, &l_hToken))
		{
			::DumpToken (l_hToken, TRUE);

			(void)CloseHandle (l_hToken);
			l_hToken = NULL;
		}
		else
		{
			DWORD l_dwLastError = GetLastError ();
			(void) _ftprintf (stderr, _T("OpenThreadToken() failed with %ld\n"), l_dwLastError);
		}
	}
	else {
		(void) _ftprintf (stderr, _T("CoImpersonateClient() failed with 0x%08lX\n"), l_hr);
	}

	return S_OK;
}
