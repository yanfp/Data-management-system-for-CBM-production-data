#pragma once
#include <afx.h>

struct Name_Value
{
	CString m_str;
	int m_x;
	double m_value;
};

struct Zk_Value
{
	CString m_ZkName;
	double m_Value;
	Zk_Value& operator =(const Zk_Value& zk)
	{
		this->m_ZkName=zk.m_ZkName;
		this->m_Value=zk.m_Value;
		return *this;
	}
};