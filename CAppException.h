#ifndef CAPPEXCEPTION_H
#define CAPPEXCEPTION_H
#pragma once
#include "afx.h"

/************************************************
[类名]	CAppException
[功能]	自定义异常类、异常处理
************************************************/
class CAppException
{
public:
    //构造函数
    CAppException(CString strError);
    //析构函数
    ~CAppException(void);

public:
    // 获取错误信息
    CString GetErrorMessage();

private:
    CString m_strError;	//	错误信息
    int m_nCode;		//	错误数
};

