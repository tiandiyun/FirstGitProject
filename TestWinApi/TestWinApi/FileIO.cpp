#include "stdafx.h"
#include "FileIO.h"
#include <windows.h>
#include <io.h>
#include <direct.h>

void DirectoryCheck()
{
    char curPath[MAX_PATH] = { 0 };
    GetCurrentDirectory(MAX_PATH, curPath);

    int strLen = strlen(curPath);
    const char *dirName = "\\DDzRobotLog\\";
    strncpy_s(curPath + strLen, sizeof(curPath) - strLen - 1, dirName, strlen(dirName));

    int rslt = _access(curPath, 0);
    if (0 != rslt)
    {
        rslt = _mkdir(curPath);
    }
}
