#pragma once
class OdbcExcel
{
public:
	OdbcExcel(void);
	~OdbcExcel(void);
private:
	CDatabase m_db;
public:
	bool Connect(CString str);
	CDatabase* GetDb();
	void Close();
	
};