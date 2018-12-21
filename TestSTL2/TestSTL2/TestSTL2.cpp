// TestSTL2.cpp : 定义控制台应用程序的入口点。
//

#pragma warning(disable : 4996)

#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <unordered_set>
#include <functional>
#include <clocale>
#include <sstream>
#include <windows.h>   
#include <dbghelp.h>  
#include <thread>
#include <memory>
#include <array>
#pragma comment( lib, "dbghelp" )  

#include "RandomChoice.h"

#define _ARR_SIZE(x) (sizeof(x) / sizeof(x[0]))


template<typename T>
void PrintElements(T c)
{
    for (const auto& d : c)
    {
        std::cout << d << " ";
    }
    std::cout << std::endl;
}

void TestFill()
{
    std::vector <int> V;
    int n, startpos, endpos, paint;

    std::cin >> n;
    V.resize(n);
    while (std::cin >> startpos >> endpos >> paint)
    {
        fill(V.begin() + startpos - 1, V.begin() + endpos, paint);
        for_each(V.begin(), V.end(), [](int &elem){std::cout << elem << " "; });
        std::cout << std::endl;
    }
}

void TestFillN()
{
    std::vector<int> v1{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    std::fill_n(v1.begin(), 0, -1);

    std::copy(begin(v1), end(v1), std::ostream_iterator<int>(std::cout, ", "));
    std::cout << "\n";
}


void TestContainerInsert()
{
    std::list<int> digits;
    for (int i = 0; i < 5; ++i)
    {
        digits.push_back(i);
    }

    auto it = digits.begin();
    ++it;

    digits.insert(it, 9);

    for (int n : digits)
        std::cout << n << ' ';
    std::cout << '\n';
}

void TestEachInserter()
{
    std::vector<int> vecSrc;
    std::list<int> vecDest;

    for (std::vector<int>::size_type i = 0; i < 3; ++i)
    {
        vecSrc.push_back(i);
    }

    copy(vecSrc.begin(), vecSrc.end(), std::back_inserter(vecDest));
    PrintElements(vecDest);

    copy(vecSrc.begin(), vecSrc.end(), std::front_inserter(vecDest));
    PrintElements(vecDest);

    copy(vecSrc.begin(), vecSrc.end(), std::inserter(vecDest, ++vecDest.begin()));
    PrintElements(vecDest);
}

void TestAutoAdd()
{
    int a = 0;
    int b = (++a) + (++a) + (++a);
    std::cout << "prep auto add, a: " << a << ", b: " << b << std::endl;

    a = 0;
    b = (a++) + (a++) + (a++);
    std::cout << "post auto add, a: " << a << ", b: " << b << std::endl;
}

class A
{
public:
    A(int v=100) : param1(v)
    {
        std::cout << "A()" << std::endl;
    }

    A(const A& a) : param1(a.param1)
    {
        std::cout << "A(&)" << std::endl;
    }

    A(const A&& a)
    {
        std::cout << "A(const A&& a)" << std::endl;
    }

    A& operator=(const A& a)
    {
        std::cout << "operator=" << std::endl;
        return *this;
    }

    /*A& operator=(const A&& a)
    {
        std::cout << "A& operator=(const A&& a)" << std::endl;
        return *this;
    }*/

    int operator-(const A& a)
    {
        return 0;
    }

    ~A()
    {
        std::cout << "~A()" << std::endl;
    }

    A& Show()
    {
        std::cout << "Show(): " << param1 << std::endl;
        return *this;
    }

    static A CreateA()
    {
        A a;
        return a;
    }

    void SetParam1(int v) { param1 = param1; }

    int GetParam1() { return param1; }

private:
    int param1;
};

A GetA()
{
    A a;
    std::cout << "GetA()" << std::endl;
    return a;
}

void TestTempRef()
{
    /*A a = A::CreateA();
    a.Show();*/

    //const A& a = A::CreateA().Show();

   /* int i(3);
    A a1 = A::CreateA();*/

    A a1, a2;
    std::cout << a1 - a2;
    a2 = std::move(a1);
    
    /*A a1 = GetA();*/

    system("pause");
}

char* getTempCharPtr()
{
    return "fssdf";
}

void TestGetTempChar()
{
    char* pc = getTempCharPtr();
    const char* cpc = getTempCharPtr();
    int i = 0;
}

std::string GetTempString()
{
    std::string test = "test";
    return test;
}

void TestMapEmplace()
{
    /*A a;
    std::map<int, A> aMap;
    auto result = aMap.emplace(1, a);
    printf("emplace result: %d\n", result.second);

    result = aMap.emplace(1, a);
    printf("emplace result: %d\n", result.second);

    const auto& it = aMap.begin();*/
    std::map<int, int> tmpMap;
    int& v1 = tmpMap[1];
    v1 = 2;

    printf("==============================");
}

void TestArray()
{
    int a[3][8];
    int* ap = a[0];
    for (int i = 0; i < _ARR_SIZE(a) * _ARR_SIZE(a[0]); *ap++ = i++);
    std::cout << a[2][9] << std::endl;

    //auto aType = decltype(a); 
    auto aTypeName = typeid(a).name();
    std::cout << aTypeName << std::endl;

    int(*p)[8] = a;
    std::cout << int(p + 1) << " - " << int(p) << " = " << (int(p + 1) - int(p)) << std::endl;
}


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
struct base;
void HandleData(const base* baseData)
{
    std::cout << typeid(*baseData).name() << std::endl;
}

struct base
{
    base()
    {
        std::cout << "base()" << std::endl;
    }

    base(void* srcData, unsigned int size)
    {
        data = new char[size];
        memcpy_s(data, size, srcData, size);
    }

    ~base()
    {
        if (data)
        {
            delete[] data;
        }
    }

    void* data{ nullptr };
};

struct Derive1 : base
{
    Derive1(void* srcData, unsigned int size) : base(srcData, size) {};

    static void read(void* srcData, unsigned int size)
    {
        Derive1 child(srcData, size);
        std::cout << child.a << std::endl;
        HandleData(&child);
    };

    int a{ 1 };
};

struct Derive2 : base
{
    Derive2(void* srcData, unsigned int size) : base(srcData, size) {};

    static void read(void* srcData, unsigned int size)
    {
        Derive2 child(srcData, size);
        std::cout << child.b << std::endl;
        HandleData(&child);
    };

    int b{ 2 };
};

void TestBind()
{
    std::map<int, std::function<void(void*, unsigned int)>> funcMap;
    funcMap[1] = Derive1::read;
    funcMap[2] = Derive2::read;
    
    int data = 5;
    funcMap[1](&data, sizeof(data));
    funcMap[2](&data, sizeof(data));
}

void TestStrFunc()
{
    /*char string[20] = "Hello there, honey.";
    char* ans;
    ans = strpbrk(string, "aeiou");*/

    /*char str[] = "y129th";
    char accept[] = "1234567890";
    int i = strspn(str, accept);
    printf("str 前 %d 个字符都属于 accept\n", i);

    int ni = strcspn(str, accept);*/

    char str[] = "now # is the time for all # good men to come to the # aid of their country";
    char delims[] = "#!~-_";
    char *result = NULL;
    result = strtok(str, delims);
    while (result != NULL) 
    {
        printf("result is \"%s\"\n", result);
        result = strtok(NULL, delims);
    }

    system("pause");
}

void TestListSort()
{
    std::list<int> numList;
    for (int i = 0; i < 10; ++i)
    {
        numList.push_back(rand() % 10);
    }

    numList.sort([](int l, int r)
    {
        if (l < r)
        {
            return true;
        }
        
        return false;

    });
}


//************************************
// Returns:   void
// Qualifier: 不完整初始化
//************************************
void TestInitialize()
{
    //int a[2][3];
    int b[2][3] = { 0 };
    int c[2][3] = { {1, 2, 3} };

    struct sta 
    {
        int a;
        int b[3];
    } ;

    //struct sta sa;
    struct sta sb = { 0 };

    system("pause");
}

struct strc
{
    char a;
    //char b[4];
    int b;
    short c;
};

void TestStruct()
{
    std::cout << sizeof(strc) << std::endl;
}

void TestMapOverFlow()
{
    std::map<unsigned char, int> srcMap;
    srcMap[1] = 10;

    int key = 0x101;
    
    auto it = srcMap.find(key);
    if (it != srcMap.end())
    {
        std::cout << it->second << std::endl;
    }
}

void TestContainerAddSelf()
{
    std::map<int, int> digitMap;
    digitMap[0] = 0;
    std::cout << "before self add, digitMap[0]= " << digitMap[0] << std::endl;

    digitMap[0]++;
    std::cout << "after self add, digitMap[0]= " << digitMap[0] << std::endl;
}

void TestIO()
{
    /*for (int i = 0; i < 10; ++i)
    {
        const char* tmpName = tmpnam(NULL);
        std::cout << tmpName << std::endl;
    }
    
    char tmpName[L_tmpnam];
    auto rslt = tmpnam(tmpName);
    std::cout << tmpName << std::endl;*/

    /*FILE* fp = tmpfile();
    fputs("temp file test", fp);
    rewind(fp);
    char buffer[20];
    fgets(buffer, sizeof(buffer), fp);
    std::cout << buffer << std::endl;*/

    /*double not_a_number = std::log(-1.0);
    if (errno == EDOM) {
        std::perror("log(-1) failed");
    }*/

    /*char buffer[BUFSIZ];
    gets(buffer);
    std::cout << buffer << std::endl;

    const char* tmp = "hello \n world.";
    puts(tmp);*/

    const char *fname = tmpnam(nullptr);
    FILE* fp = fopen(fname, "w");

    {
        fputs("haha", fp);
        fclose(fp);

        fp = fopen(fname, "r");
        rewind(fp);
    }

    char c = fgetc(fp);
    if (ferror(fp))
    {
        printf("读取文件：%s 时发生错误\n", fname);
    }

    clearerr(fp);
    if (ferror(fp))
    {
        printf("读取文件：%s 时发生错误\n", fname);
    }

    if (!feof(fp))
    {
        c = fgetc(fp);
    }

    perror("io error");
    std::cout << "error code: " << errno << std::endl;

    fclose(fp);

    system("pause");
}

void TestFloat()
{
    std::cout << "FLT_RADIX: " << FLT_RADIX << std::endl;
    std::cout << "FLT_MIN_EXP: " << FLT_MIN_EXP << std::endl;
    std::cout << "FLT_MIN: " << FLT_MIN << std::endl;
    std::cout << "FLT_MAX: " << FLT_MAX << std::endl;
    std::cout << "FLT_DIG: " << FLT_DIG << std::endl;
    std::cout << "FLT_MANT_DIG: " << FLT_MANT_DIG << std::endl;
    std::cout << "FLT_ROUNDS: " << FLT_ROUNDS << std::endl;

    /*float f = 12345678.11111;
    printf("%f\n", f);

    float f2 = 0.88889;
    float fSum = f + f2;
    float f3 = 0.1 * 0.1;
    std::cout << f + f2 << std::endl;

    f = 3.1415926;
    std::cout << f << std::endl;

    f = 0 * 0.1;
    std::cout << f << std::endl;*/

    float x = 3.4f, y = -4.3f;
    float z = static_cast<float>(copysign(x, y));
    std::cout << "z = copysign(x, y):  " << z << std::endl;
    std::cout << "logb(8): " << logb(8) << std::endl;
}

void TestRandom()
{
    for (int i = 0; i < 10; ++i)
    {
        std::cout << rand() % 1000 << ", ";
    }
    std::cout << std::endl;
}

void PrintTraceback()
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
    
    std::stringstream info;
    for (USHORT i = 0; i < frames; ++i) 
    {
        SymFromAddr(process, (DWORD64)(backTrace[i]), NULL, symbol);
        info << frames - i - 1 << ": " << symbol->Name << " - " << (std::ios::hex | std::ios::showbase) << symbol->Address << std::endl;
    }
    std::cout << info.str();
    free(symbol);
}


class StaticA
{
public:
    StaticA(int id)
    {
        printf("A(): %d\n", id);
        Sleep(5000);
    }

    ~StaticA()
    {
        printf("~A()\n");
    }
};

void CreateStaticA(int id)
{
    static StaticA a(id);
    printf("CreateStaticA Over : %d\n", id);
}

void TestMultiThreadStatic()
{
    std::thread t1(CreateStaticA, 1);
    std::thread t2(CreateStaticA, 2);
    t1.join();
    t2.join();
}

void TestOverRide(std::map<int, int> mm)
{
    std::cout << "TestOverRide(std::map<int, int> mm)" << std::endl;
}

void TestOverRide(std::map<float, float> mm)
{
    std::cout << "TestOverRide(std::map<float, float> mm)" << std::endl;
    
    char* p = nullptr;
    char c = *p;
    std::cout << c << std::endl;
}

struct DataProbCoeff : public ObjWithWT<UINT32>
{
    int       value{ 0 };
};
using ProbCoeffVec = std::vector<DataProbCoeff>;

void TestRandomChoice()
{
    std::vector<DataProbCoeff> coeffs;
    for (int i = 0; i < 10; ++i)
    {
        DataProbCoeff coeff;
        coeff.value = i + 1;
        coeff.weight = RangeRndI(1, 10);
        coeffs.push_back(coeff);
    }

    const DataProbCoeff* coeff = RandomChoiceUInt32WT<DataProbCoeff, ProbCoeffVec>(coeffs);
    std::cout << "choose coeff: " << coeff->value << std::endl;
}

void TestTypeId()
{
    A a;
    const std::type_info& info = typeid(a);
}

void TestDelSharePtr()
{
    int* a = new int;
    *a = 10;

    std::shared_ptr<int> pa(a);
    std::cout << pa.use_count() << std::endl;

    delete a;
    a = nullptr;

    std::cout << pa.use_count() << std::endl;
}

void TestMap()
{
    /*std::map<int, int> intMap;
    std::map<float, float> floatMap;
    TestOverRide(intMap);
    TestOverRide(floatMap);*/

    /*std::map<int, int> intMap;
    intMap[0] -= 10;*/

    /*std::map<std::string, std::string> kv;
    kv["aa"] = "aa";
    kv["bb"] = "bb";
    kv["cc"] = "cc";
    std::cout << kv["cc"] << std::endl;*/

    std::array<std::shared_ptr<A>, 5> AMap;
    
    AMap[0] = std::shared_ptr<A>(new A(10));
    AMap[1] = std::shared_ptr<A>(new A(20));
    std::cout << "-------------" << std::endl;

    for (std::shared_ptr<A>& a : AMap)
    {
        if (a)
        {
            a = nullptr;
        }
    }
    
}

int _tmain(int argc, _TCHAR* argv[])
{
    

    /*TestTypeId();*/

    /*TestDelSharePtr();*/

    TestMap();

    /*TestTempRef();*/

    

    system("pause"); 
    return EXIT_SUCCESS;
}

