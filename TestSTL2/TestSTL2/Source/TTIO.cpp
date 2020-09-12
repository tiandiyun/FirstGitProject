#include "TTIO.h"
#include <iostream>
#include <ostream>
#include <wtypes.h>
#include <fstream>
#include <iomanip>
#include "../Util/UtilFunction.h"

#pragma warning(disable : 4996)

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

	const char* fname = tmpnam(nullptr);
	if (!fname)
	{
		return;
	}

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

template<class outstream>
void OutStream(outstream &os)
{
	os << "first line" << std::endl;
	os << std::setiosflags(std::ios::left) << std::setw(20) << "second line:";
	for (size_t i = 0; i < 10; i++)
	{
		os << i;
		if (i != 9)
		{
			os << ",";
		}
	}
	os << std::endl;
	os << "------------------------------------------------------------" << std::endl;
}

void StreamRelate(int outtype)
{
	if (outtype)
	{
		OutStream(std::cout);
	}
	else
	{
		char curPath[MAX_PATH];
		GetCurrentDirectory(MAX_PATH, curPath);

		std::string outFile = curPath;
		outFile += "\\out.log";

		std::ofstream ofile(outFile, std::ios::app);
		OutStream(ofile);
		ofile.close();
	}
}
