// TestObject.h : Declaration of the CTestObject

#pragma once
#include "resource.h"       // main symbols

#include "TestObjectSvr_i.h"


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif



// CTestObject

class ATL_NO_VTABLE CTestObject :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CTestObject, &CLSID_TestObject>,
	public ISupportErrorInfo,
	public IDispatchImpl<ITestObject, &IID_ITestObject, &LIBID_TestObjectSvrLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CTestObject()
	{
		(void) _tprintf (_T("CTestObject::CTestObject - 0x%08X\n"), this);
	}

	~CTestObject()
	{
		(void) _tprintf (_T("CTestObject::~CTestObject - 0x%08X\n"), this);
	}

DECLARE_REGISTRY_RESOURCEID(IDR_TESTOBJECT)

BEGIN_COM_MAP(CTestObject)
	COM_INTERFACE_ENTRY(ITestObject)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// ISupportErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ITestObject
public:
	STDMETHOD(DumpToken)(void);

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

private:
};

OBJECT_ENTRY_AUTO(__uuidof(TestObject), CTestObject)
