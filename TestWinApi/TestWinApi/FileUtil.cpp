#include "FileUtil.h"

#ifdef WIN32
#include <windows.h>
#include <io.h>
#include <direct.h>
#include <process.h>
#pragma warning(disable : 4996)
#else
#include <unistd.h>
#include <stddef.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/stat.h>
#endif

#include <sys/stat.h>

/*
struct stat 
{
    _dev_t     st_dev;        //�ļ����ڴ����������� 
    _ino_t     st_ino;        //inode��FAT��NTFS�ļ�ϵͳ������ 
    unsigned short st_mode;   //�ļ����ļ��еı�־ 
    short      st_nlink;      //��NTFSϵͳ��ͨ��Ϊ1 
    short      st_uid;        //UNIXϵͳ��Ϊuserid��windows��Ϊ0 
    short      st_gid;        //UNIXϵͳ��Ϊgroupid��windows��Ϊ0 
    _dev_t     st_rdev;       //�������ţ���st_dev��ͬ 
    _off_t     st_size;       //�ļ��ֽ��� 
    time_t st_atime;          //�ϴη���ʱ�� 
    time_t st_mtime;          //�ϴ��޸�ʱ�� 
    time_t st_ctime;          //����ʱ�� 
};
*/


bool FileUtil::Exist(const string &path)
{
#ifdef WIN32
    int code = _access(path.c_str(), 0);
#else
    int code = access(path.c_str(), F_OK);
#endif
    return code == 0;
}

int FileUtil::IsFileOrDir(const string &path)
{
    struct stat st;
    if (stat(path.c_str(), &st) == 0)
    {
        if (st.st_mode & S_IFDIR)
        {
            return FU_DIR;
        }
        else if (st.st_mode & S_IFREG)
        {
            return FU_FILE;
        }
        else
        {
            return FU_UNKNOWN;
        }
    }
    else
    {
        return FU_NONEXIST;
    }
}

bool FileUtil::MakeDir(const string &path)
{
    if (Exist(path))
    {
        return true;
    }

#ifdef WIN32
    int code = _mkdir(path.c_str());
#else
    int code = mkdir(path.c_str(), S_IRWXU | S_IRWXG | S_IRWXO);
#endif
    return code == 0;
}

bool FileUtil::MakeDirs(const string &path)
{
    size_t pos = 0;
    size_t len = path.size();
    while (pos < len)
    {
        pos = path.find_first_of("\\/", pos);
        string dir = path.substr(0, pos);
        if (!Exist(dir))
        {
            if (!MakeDir(dir))
            {
                cout << "create path failed, " << dir.c_str() << endl;
                return false;
            }
        }

        if (pos < len)
        {
            ++pos;
        }
        else
        {
            break;
        }
    }

    return true;
}

bool FileUtil::SplitPath(const string &filePath, string& fileDir, string& fileName)
{
    int fileType = IsFileOrDir(filePath);
    if (fileType != FU_DIR && fileType != FU_FILE)
    {
        return false;
    }

    if (fileType == FU_DIR)
    {
        fileDir = filePath;
        fileName.clear();
        return true;
    }

    size_t pos = filePath.find_last_of("\\/");
    if (pos != string::npos)
    {
        fileDir = filePath.substr(0, pos);
        fileName = filePath.substr(pos + 1);
    }
    else
    {
        fileDir.clear();
        fileName = filePath;
    }

    return true;
}