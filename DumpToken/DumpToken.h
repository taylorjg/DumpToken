#ifndef __DUMPTOKEN_H__
#define __DUMPTOKEN_H__

#include <windows.h>

extern void DumpToken (HANDLE p_hToken, BOOL p_bDumpLinkedToken);
extern void DumpProxyBlanket (IUnknown* p_pUnknown, LPCTSTR p_lpszLabel);
extern void DumpClientBlanket ();

#endif
