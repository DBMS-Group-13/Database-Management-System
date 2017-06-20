#include "appexception.h"

//	构造函数
AppException::AppException(QString strError)
{
    m_strError = strError;
    m_nCode = 0;
}

// 析构函数
AppException::~AppException(void)
{
}

/************************************************************************
[函数名称]	GetErrorMessage
[功能]	获取错误信息
[参数]	void
[返回值]	CString:异常信息
************************************************************************/
QString AppException::GetErrorMessage()
{
    return m_strError;
}
