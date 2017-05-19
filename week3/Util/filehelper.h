#ifndef FILEHELPER_H
#define FILEHELPER_H
#include<QString>

class FileHelper
{
public:
    // 创建文件,QString 为文件相对路径
    static bool CreateNewFile(const QString strFileName);
    // 检测文件是否存在，QString为文件相对路径
    static bool IsValidFile(const QString strPath);
    static bool IsValidFolder(const QString strPath);
};

#endif // FILEHELPER_H
