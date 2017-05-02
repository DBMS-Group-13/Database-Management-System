#include "StdAfx.h"
#include "CAppException.h"

//	构造函数
CAppException::CAppException(CString strError)
{
    m_strError = strError;
    m_nCode = 0;
}

// 析构函数
CAppException::~CAppException(void)
{
}

/************************************************************************
[函数名称]	GetErrorMessage
[功能]	获取错误信息
[参数]	void
[返回值]	CString:异常信息
************************************************************************/
CString CAppException::GetErrorMessage()
{
    return m_strError;
}
