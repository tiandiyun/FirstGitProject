// Redis_PTR.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
/*
#include <hiredis.h> //ͷ�ļ������ļ����·���ı�
#include <Win32_Interop\win32fixes.h> //ͷ�ļ������ļ����·���ı�
#pragma comment(lib,"hiredis.lib")
#pragma comment(lib,"Win32_Interop.lib")*/


int _tmain(int argc, _TCHAR* argv[])
{
	/*redisContext *redis = redisConnect("127.0.0.1", 6379);
	if (redis == NULL || redis->err) {
		if (redis) {
			printf("Error: %s\n", redis->errstr);
			// handle error
		}
		else {
			printf("Can't allocate redis context\n");
		}
	}
	else {
		printf("connect successed!");
	}
	redisReply *reply;

	/ * PING server * /
	reply = (redisReply *)redisCommand(redis, "PING");
	printf("PING: %s\n", reply->str);
	freeReplyObject(reply);

	reply = (redisReply *)redisCommand(redis, "SET %b %b", "foo", (size_t)3, "ss", (size_t)2);
	printf("foo: %s\n", reply->str);
	freeReplyObject(reply);
	redisFree(redis);
	system("pause");*/

	return 0;
}

