#ifndef FILE_UTIL_H_
#define FILE_UTIL_H_

#include <iostream>

using namespace std;

class FileUtil
{
public:
    enum FUCODE
    {
        FU_UNKNOWN = -2,
        FU_NONEXIST = -1,
        FU_FILE = 0,
        FU_DIR
    };

    static bool Exist(const string& path);

    static int  IsFileOrDir(const string &path);

    static bool MakeDir(const string &path);

    static bool MakeDirs(const string &path);

    static bool SplitPath(const string &filePath, string& fileDir, string& fileName);

    static bool CurrentDirectory(string &path);
   
    static void PathJoin(string &path, const string &subpath);
};


#endif // FILE_UTIL_H_
