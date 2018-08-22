#include "StdAfx.h"
#include "OdbcExcel.h"

OdbcExcel::OdbcExcel(void)
{
}


OdbcExcel::~OdbcExcel(void)
{
}

CString GetExcelDriver()
{
	char szBuf[2001];
    WORD cbBufMax = 2000;
    WORD cbBufOut;
    char *pszBuf = szBuf;
    CString sDriver;
    // 获取已安装驱动的名称(涵数在odbcinst.h里)
    if (!SQLGetInstalledDrivers((LPWSTR)szBuf, cbBufMax, &cbBufOut))
        return L"";
    
    // 检索已安装的驱动是否有Excel...
    do
    {
        if (strstr(pszBuf, "Excel") != 0)
        {
            //发现 !
            sDriver = CString(pszBuf);
            break;
        }
        pszBuf = strchr(pszBuf, '\0') + 1;
    }
    while (pszBuf[1] != '\0');
    return sDriver;
}

bool OdbcExcel::Connect(CString str)
{
	CString strDsn;
	CString strDriver;
	//strDriver=GetExcelDriver();
	strDriver=L"Microsoft Excel Driver (*.xls)";
	strDsn.Format(L"ODBC;DRIVER={%s};DBQ=%s",strDriver,str);
	if(m_db.Open(NULL,false,false,strDsn))
	{
		return true;
	}
	else
	{
		return false;
	}
}

CDatabase* OdbcExcel::GetDb()
{
	if(m_db.IsOpen())
		return &m_db;
	else
		return NULL;
}

void OdbcExcel::Close()
{
	this->m_db.Close();
}
