#ifndef APPEXCEPTION_H
#define APPEXCEPTION_H
#pragma once
#include<QString>
/************************************************
[类名]	CAppException
[功能]	自定义异常类、异常处理
************************************************/
class AppException
{
public:
    //构造函数
    AppException(QString strError);
    //析构函数
    ~AppException(void);

public:
    // 获取错误信息
    QString GetErrorMessage();

private:
    QString m_strError;	//	错误信息
    int m_nCode;		//	错误数
};

#endif // APPEXCEPTION_H
