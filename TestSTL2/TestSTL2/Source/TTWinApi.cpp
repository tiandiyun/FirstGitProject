#include "TTWinApi.h"
#include <iostream>
#include <sstream>
#include <windows.h>   
#include <dbghelp.h>  
#include <cassert>

#pragma comment( lib, "dbghelp" )  

void PrintTraceback()
{
	const UINT maxSymName = 512;
	const ULONG framesToSkip = 0;
	const ULONG framesToCapture = 100;

	HANDLE process = GetCurrentProcess();
	SymInitialize(process, NULL, TRUE);

	UINT size = sizeof(SYMBOL_INFO) + maxSymName * sizeof(TCHAR);
	SYMBOL_INFO* symbol = (SYMBOL_INFO*)malloc(size);
	if (!symbol)
	{
		return;
	}
	memset(symbol, 0, size);

	symbol->MaxNameLen = maxSymName - 1;
	symbol->SizeOfStruct = sizeof(SYMBOL_INFO);

	void* backTrace[framesToCapture]{};
	ULONG backTraceHash = 0;
	const USHORT frames = CaptureStackBackTrace(framesToSkip, framesToCapture, backTrace, &backTraceHash);

	std::stringstream info;
	for (USHORT i = 0; i < frames; ++i)
	{
		SymFromAddr(process, (DWORD64)(backTrace[i]), NULL, symbol);
		info << frames - i - 1 << ": " << symbol->Name << " - " << (std::ios::hex | std::ios::showbase) << symbol->Address << std::endl;
	}
	std::cout << info.str();
	free(symbol);
}