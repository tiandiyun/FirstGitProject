#pragma once


#ifdef CALC_EXPORTS
#define CALC_API __declspec (dllexport)
#else
#define CALC_API __declspec (dllimport)
#endif


extern "C" CALC_API int CExpData;
extern "C" CALC_API int __cdecl CAddCdecl(int a, int b);
extern "C" CALC_API int __stdcall CAddStdCall(int a, int b);
extern "C" CALC_API int __fastcall CAddFastCall(int a, int b);

extern CALC_API int CppExpData;
extern CALC_API int __cdecl CppAddCdecl(int a, int b);
extern CALC_API int __stdcall CppAddStdCall(int a, int b);
extern CALC_API int __fastcall CppAddFastCall(int a, int b);

