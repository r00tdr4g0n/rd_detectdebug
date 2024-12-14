#include "pch.h"
#include "DetectDebug.h"

BOOL CheckSpecificByte(BYTE a_specificByte, PVOID a_pFunc, SIZE_T a_funcSize)
{
	PBYTE p = (PBYTE)a_pFunc;

	for (INT i = 0; ; i++) {
		// Break on RET(0xC3) if we don't know size of function
		if (((a_funcSize > 0) && (i >= a_funcSize)) ||
			((0 == a_funcSize) && (0xC3 == p[i]))) {
			break;
		}

		if (a_specificByte == p[i]) {
			return TRUE;
		}
	}

	return FALSE;
}

BOOL CheckBeingDebugged()
{
	PVOID pPEB = NULL;
	BOOL bResult = FALSE;

#ifdef _WIN64
	pPEB = (PVOID)__readgsqword(0x60);
#else
	__asm {
		mov eax, fs: [0x30]
		mov pPEB, eax
	}
#endif

	if (pPEB && *((PBYTE)pPEB + 0x02)) {
		bResult = TRUE;
	}

	return bResult;
}

BOOL CheckDebugPrograms()
{
	const TCHAR* pPrograms[] = {
		_T("ollyDbg"),
		_T("x64dbg"),
		_T("x32dbg"),
		_T("ida"),
		_T("windbg")
	};

	int count = sizeof(pPrograms) / sizeof(TCHAR*);

	for (int i = 0; i < count; i++) {
		if (FindWindow(NULL, pPrograms[i])) {
			return TRUE;
		}
	}

	return FALSE;
}

BOOL IsDebugged()
{
	BOOL bResult = FALSE;

	return bResult;
}