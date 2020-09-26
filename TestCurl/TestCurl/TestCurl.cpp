// TestCurl.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "curl.h"
#include <iostream>
#include <sstream>

#pragma warning(disable:4996)

using namespace std;


//这个函数为CURLOPT_HEADERFUNCTION参数构造
/* 从http头部获取文件size*/
size_t GetContentLengthFunc(void *ptr, size_t size, size_t nmemb, void *stream) 
{
	int r;
	long len = 0;
	char* cptr = (char*)ptr;
	
	/* _snscanf() is Win32 specific */
	//r = _snscanf(cptr, size * nmemb, "Content-Length: %ld\n", &len);
	r = sscanf(cptr, "Content-Length: %ld\n", &len);
	if (r && stream) /* Microsoft: we don't read the specs */
		*((long *)stream) = len;

	return size * nmemb;
}

size_t WriteCallback(void *ptr, size_t size, size_t nmemb, void *stream)
{
	char* cptr = (char*)ptr;
	stringstream& ss = *(stringstream*)stream;
	ss << cptr;
	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	char path[256] = { 0 };
	GetCurrentDirectory(256, path);

	curl_global_init(CURL_GLOBAL_ALL);

	cout << curl_version() << endl;

	CURL* curlHandle = curl_easy_init();
	do 
	{
		if (!curlHandle)
		{
			break;
		}

		long filesize = 0;
		stringstream ss;

		curl_easy_setopt(curlHandle, CURLOPT_HEADERFUNCTION, GetContentLengthFunc);
		curl_easy_setopt(curlHandle, CURLOPT_HEADERDATA, &filesize);
		curl_easy_setopt(curlHandle, CURLOPT_WRITEDATA, &ss);
		curl_easy_setopt(curlHandle, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curlHandle, CURLOPT_URL, "https://www.baidu.com/");
		CURLcode code = curl_easy_perform(curlHandle);
		cout << "curl code " << code << endl;
		cout << ss.str();

		curl_easy_cleanup(curlHandle);
	} while (0);

	curl_global_cleanup();

	system("pause");
	return 0;
}

