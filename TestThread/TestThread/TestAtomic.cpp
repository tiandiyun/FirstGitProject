#include "stdafx.h"
#include "TestAtomic.h"
#include <atomic>

void TestAtomicExchange()
{
	/*int expected = 1;
	std::atomic<int> a = 1;
	bool r = a.compare_exchange_weak(expected, 3);*/

	//��Ϊcompare_exchange_weak()���ԡ�αʧ�ܡ�����������ͨ��ʹ��һ��ѭ����

	bool expected = false;
	std::atomic<bool> b = true; // ����Щʲô
	while (!b.compare_exchange_weak(expected, true) && !expected);


	//����������У�ѭ����expected��ֵʼ����false����ʾcompare_exchange_weak()��Ī����ʧ�ܡ�
}