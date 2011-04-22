// dllmain.h : Declaration of module class.

class CTestObjectSvrModule : public CAtlDllModuleT< CTestObjectSvrModule >
{
public :
	DECLARE_LIBID(LIBID_TestObjectSvrLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_TESTOBJECTSVR, "{AC223EAF-F069-4ED9-A6DB-B0E712076666}")
};

extern class CTestObjectSvrModule _AtlModule;
