#pragma once

#include <windows.h>
#include <dbghelp.h>  
#pragma comment( lib, "dbghelp" )

static void PrintTraceback()
{
    {
        const UINT maxSymName = 512;
        const ULONG framesToSkip = 0;
        const ULONG framesToCapture = 100;

        HANDLE process = GetCurrentProcess();
        SymInitialize(process, NULL, TRUE);

        UINT size = sizeof(SYMBOL_INFO) + maxSymName * sizeof(TCHAR);
        SYMBOL_INFO* symbol = (SYMBOL_INFO *)malloc(size);
        memset(symbol, 0, size);

        symbol->MaxNameLen = maxSymName - 1;
        symbol->SizeOfStruct = sizeof(SYMBOL_INFO);

        void* backTrace[framesToCapture]{};
        ULONG backTraceHash = 0;
        const USHORT frames = CaptureStackBackTrace(framesToSkip, framesToCapture, backTrace, &backTraceHash);
        for (USHORT i = 0; i < frames; ++i)
        {
            SymFromAddr(process, (DWORD64)(backTrace[i]), NULL, symbol);
            printf("%i: %s - 0x%0X\n", frames - i - 1, symbol->Name, symbol->Address);
        }

        free(symbol);
    }
}

void TestTraceStack();