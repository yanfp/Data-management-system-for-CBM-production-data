#include "StdAfx.h"
#include "MyFunction.h"


MyFunction::MyFunction(void)
{
}


MyFunction::~MyFunction(void)
{
}

int MyFunction::GetYear(CString str)
{
	int len=str.GetLength();
	int pos1=-1,pos2=-1;
	for(int i=0;i<len;i++)
	{
		if(pos1!=-1 && str.GetAt(i)=='/')
		{
			pos2=i;
			break;
		}
		if(str.GetAt(i)=='/')
			pos1=i;
	}
	CString strYear=str.Left(pos1);
	return _wtoi(strYear);
}

int MyFunction::GetMonth(CString str)
{
	int len=str.GetLength();
	int pos1=-1,pos2=-1;
	for(int i=0;i<len;i++)
	{
		if(pos1!=-1 && str.GetAt(i)=='/')
		{
			pos2=i;
			break;
		}
		if(str.GetAt(i)=='/')
			pos1=i;
	}
	CString strTemp=str.Right(str.GetLength()-pos1-1);
	CString strMouth=strTemp.Left(pos2-pos1-1);
	return _wtoi(strMouth);
}


int MyFunction::GetDay(CString str)
{
	int len=str.GetLength();
	int pos1=-1,pos2=-1;
	for(int i=0;i<len;i++)
	{
		if(pos1!=-1 && str.GetAt(i)=='/')
		{
			pos2=i;
			break;
		}
		if(str.GetAt(i)=='/')
			pos1=i;
	}
	CString strDay=str.Right(str.GetLength()-pos2-1);
	return _wtoi(strDay);
}