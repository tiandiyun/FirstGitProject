#pragma once


void TestDecltype();

void TestDeclval();


template<typename T, bool B> struct enable_if_;
template<typename T> struct is_arithmetic_;

template<typename T, bool B> 
struct enable_if_ 
{
    typedef T type;
};

template<typename T> struct enable_if_<T, false> 
{
};

template<typename T>
struct is_arithmetic_ 
{
    enum { value = false };
};

template<>
struct is_arithmetic_<int> 
{
    enum { value = true };
};

template<typename T>
typename enable_if_<T, is_arithmetic_<T>::value>::type add(T &t1, T &t2) 
{
    return t1 + t2;
}

void TestTypeInfer();


template<typename T>
struct BaseTemplate
{
    T   t;
};

template<>
struct BaseTemplate<int>
{
    float f;
};

void TestTemplate();

void TestRefByRef();

void TestRefWrapper();

void TestRefWrapCopy();

void RefWarpperSort();