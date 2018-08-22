



// DataInDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Tool.h"
#include "DataInDlg.h"
#include "afxdialogex.h"

#include "MConnection.h"
#include "MCommand.h"
#include "MRecordset.h"
#include "OdbcExcel.h"

#include "CApplication.h"
#include "CRange.h"
#include "CWorkbook.h"
#include "CWorkbooks.h"
#include "CWorksheet.h"
#include "CWorksheets.h"

#include "TableSheetsDlg.h"
//#include "OdbcExcel.h"
// CDataInDlg 对话框

IMPLEMENT_DYNAMIC(CDataInDlg, CDialogEx)

Table_Sheet GetTableSheet(CString str)
{
	if(str==L"1区、5区-海则采气区数据表.xls")
	{
		Table_Sheet ts(4);
		ts.m_Str[0]=L"海则采气区1区关停井数据";
		ts.m_Str[1]=L"海则采气区1区生产井数据";
		ts.m_Str[2]=L"海则采气区5区数据1-10月";
		ts.m_Str[3]=L"海则采气区5区数据11-12月";
		return ts;
	}
	else if(str==L"2区-固县采气区数据表2015.xls")
	{
		Table_Sheet ts(1);
		ts.m_Str[0]=L"固县采气区2区";
		return ts;
	}
	else if(str==L"3区-固县采气区数据表2015.xls")
	{
		Table_Sheet ts(1);
		ts.m_Str[0]=L"固县采气区3区";
		return ts;
	}
	else if(str==L"柿庄北采气区2015.11.12数据表.xls")
	{
		Table_Sheet ts(4);
		ts.m_Str[0]=L"柿庄北采气区合作项目(勘探）";
		ts.m_Str[1]=L"柿庄北采气区合作勘探（长子深煤层）";
		ts.m_Str[2]=L"柿庄北采气区自营项目（勘探）";
		ts.m_Str[3]=L"柿庄北采气区自营项目（长子深煤层）";
		return ts;
	}
	else if(str==L"柿庄采气区2区数据.xls")
	{
		Table_Sheet ts(1);
		ts.m_Str[0]=L"柿庄采气区二区";
		return ts;
	}
	else if(str==L"柿庄采气区5区数据.xls")
	{
		Table_Sheet ts(1);
		ts.m_Str[0]=L"柿庄采气区五区";
		return ts;
	}
	else
	{
		Table_Sheet ts(1);
		ts.m_Str[0]=L"排采数据";
		return ts;
	}
}

void GetExcelSheets(CString strExcel,CStringArray& SheetArray)
{
	//CStringArray SheetArray;
	CApplication ExcelApp;
	//创建Excel 2000服务器(启动Excel)   
    if (!ExcelApp.CreateDispatch(_T("Excel.Application"),NULL))   
    {   
        AfxMessageBox(_T("创建Excel服务失败,你可能没有安装EXCEL，请检查!"));   
        return;  
    }  
    ExcelApp.put_DisplayAlerts(FALSE);
	CString ExcelFile=strExcel;  
    CWorkbooks WorkBooks;   
    CWorkbook WorkBook;   
    CWorksheets WorkSheets;   
    CWorksheet WorkSheet;   
    CRange        ExcelRange; 
	//利用模板文件建立新文档   
    WorkBooks.AttachDispatch(ExcelApp.get_Workbooks(),true);   
    LPDISPATCH lpDis = NULL;  
    lpDis = WorkBooks.Add(COleVariant(strExcel));   
	
    if (lpDis)  
    {  
        WorkBook.AttachDispatch(lpDis);   
        //得到Worksheets   
        WorkSheets.AttachDispatch(WorkBook.get_Worksheets(),true);   
          
        //记录打开的文件名称  
		int SheetCount=WorkSheets.get_Count();
		CWorksheet sheet;  
		for(int i=1;i<=SheetCount;i++)
		{
			sheet.AttachDispatch(WorkSheets.get_Item(COleVariant((long)i)),true);  
			CString name = sheet.get_Name();  
			SheetArray.Add(name);
		}
		sheet.ReleaseDispatch();  
    }  
	WorkSheet.ReleaseDispatch(); 
	WorkSheets.ReleaseDispatch(); 
	WorkBook.ReleaseDispatch();   
    WorkBooks.ReleaseDispatch();  
	ExcelApp.Quit();  
    ExcelApp.ReleaseDispatch();  
    ExcelApp=NULL;  
}

CDataInDlg::CDataInDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDataInDlg::IDD, pParent)
{
	m_pParentWnd=(CToolDlg*)pParent;
	m_ExcelName=L"";
	m_CurrentSheetName = _T("Sheet Name");
	m_strCurrentRecord = _T("Record");
	m_OperateType=0;
}

CDataInDlg::~CDataInDlg()
{
}

void CDataInDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_EDT_PROGRESS, m_ProgressCtrl);
	DDX_Control(pDX, IDC_PROGRESS1, m_ProgressControl);
	DDX_Text(pDX, IDC_STATIC_SHEETNAME, m_CurrentSheetName);
	//  DDX_Control(pDX, IDC_STATIC_RECORD, m_StrCurrentRecord);
	DDX_Text(pDX, IDC_STATIC_RECORD, m_strCurrentRecord);
}


BEGIN_MESSAGE_MAP(CDataInDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_OPENFILE, &CDataInDlg::OnBnClickedBtnOpenfile)
	ON_BN_CLICKED(IDC_BTN_SAVEFILE, &CDataInDlg::OnBnClickedBtnSavefile)
	ON_BN_CLICKED(IDC_BTN_DO, &CDataInDlg::OnBnClickedBtnDo)
	ON_BN_CLICKED(IDC_BTN_CANCEL, &CDataInDlg::OnBnClickedBtnCancel)
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()
// CDataInDlg 消息处理程序


void CDataInDlg::OnBnClickedBtnOpenfile()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog OpenDlg(true,L".xls",L"",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,L"Excel文件|*.xls|所有文件|*.*|",NULL);
	if(OpenDlg.DoModal()==IDOK)
	{
		CString str=OpenDlg.GetPathName();
		((CEdit*)GetDlgItem(IDC_EDT_EXCEL))->SetWindowTextW(str);
		m_ExcelName=OpenDlg.GetFileName();
	}
}


void CDataInDlg::OnBnClickedBtnSavefile()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog OpenDlg(true,L".mdb",L"",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,L"Access文件|*.mdb|所有文件|*.*|",NULL);
	if(OpenDlg.DoModal()==IDOK)
	{
		CString str=OpenDlg.GetPathName();
		((CEdit*)GetDlgItem(IDC_EDT_ACCESS))->SetWindowTextW(str);
	}
}

//格式化VALUES函数
CString FormatValuesString(CString *pStr,int num)
{
	CString str;
	for(int i=0;i<num;i++)
	{
		if(pStr[i]!=L"")
		{	
			if(i!=num-1)
				str.AppendFormat(L"'%s',",pStr[i]);
			else
				str.AppendFormat(L"'%s'",pStr[i]);
		}
		else
		{
			if(i!=num-1)
				str.AppendFormat(L"%s,",L"NULL");
			else
				str.AppendFormat(L"%s",L"NULL");
		}
	}
	return str;
}

//化简时间函数
CString SimplifyTime(CString str)
{
	int pos=str.ReverseFind(' ');
	return str.Left(pos);
}

int GetRecordCount(CDatabase *pDb)
{
	CRecordset Rs(pDb);
	CString strSql=L"SELECT COUNT(*) FROM [柿庄北采气区自营项目（长子深煤层）$]";
	Rs.Open(CRecordset::forwardOnly,strSql,CRecordset::readOnly);
	CString strCount;
	Rs.GetFieldValue((short)0,strCount);
	return _wtoi(strCount.GetBuffer(strCount.GetLength()));
}

int GetRecordCount(CDatabase *pDb,CString SheetName)
{
	CRecordset Rs(pDb);
	CString strSql=L"SELECT COUNT(*) FROM [柿庄北采气区自营项目（长子深煤层）$]";
	strSql.Format(L"SELECT COUNT(*) FROM [%s$]",SheetName);
	Rs.Open(CRecordset::forwardOnly,strSql,CRecordset::readOnly);
	CString strCount;
	Rs.GetFieldValue((short)0,strCount);
	Rs.Close();
	return _wtoi(strCount.GetBuffer(strCount.GetLength()));

}

//int TestRecordCount=0;
void CDataInDlg::DataWarehousing2(CString strExcel,CString strAccess)
{
	Table_Sheet ts=GetTableSheet(m_ExcelName);
	if(ts.m_NumberOfSheet<1)
	{
		MessageBox(L"Excel数据错误！",L"提示");
		return;
	}
	OdbcExcel oe;
	if(oe.Connect(strExcel))
	{
		CRecordset rs(oe.GetDb());
		CString str[24];
		MConnection conn;
		CString strConnection;
		strConnection.Format(L"Provider=Microsoft.Jet.OLEDB.4.0;Data Source=%s;",strAccess);
		conn.SetConnectionString(strConnection);
		//if(!CheckAccess(strAccess))
		//	return;
		if(conn.Open(L"",L"",L"",ConnectOption::adConnectUnspecified))
		{	
			MCommand cmd;
			MRecordset mrs;
			cmd.SetActiveConnection(conn);
			for(int sheetNum=0;sheetNum<ts.m_NumberOfSheet;sheetNum++)
			{
				this->m_CurrentSheetName.Format(L"[%s$] (%d/%d)",ts.m_Str[sheetNum],sheetNum+1,ts.m_NumberOfSheet);UpdateData(false);
				int RecordCount=GetRecordCount(oe.GetDb(),ts.m_Str[sheetNum]);
				m_ProgressControl.SetRange(0,(short)RecordCount*0.99);//进度条设置

				CString strSql=L"SELECT * FROM [柿庄北采气区自营项目（长子深煤层）$]";
				strSql.Format(L"SELECT * FROM [%s$A:X]",ts.m_Str[sheetNum]);
				//执行查询语句
				if(!rs.Open(CRecordset::forwardOnly,strSql,CRecordset::readOnly))
				{
					MessageBox(L"读取Excel表数据错误！",L"提示");
					return;
				}
				int filedCount=24;
				rs.MoveNext();
				rs.MoveNext();
				rs.MoveNext();
				if(ts.m_Str[sheetNum]==L"排采数据")
					rs.MoveNext();
				float CurrentRecort=0;
				//遍历Excel数据写入Access中
				while(!rs.IsEOF())
				{
					try
					{
						/*********取出每一条记录的字段************/
						rs.GetFieldValue((short)0,str[0]);
						rs.GetFieldValue(1,str[1]);
						for(int i=2;i<24;i++)
						{
							rs.GetFieldValue(i,str[i]);
						}
						/******************************/
					}
					catch(_com_error e)
					{
						CString errormessage;
						errormessage.Format(L"读取数据失败!\r\n错误信息:%s",e.ErrorMessage());
						AfxMessageBox(errormessage);///显示错误信息
						return;
					}
					if(str[0]==L"" || str[1]==L"")//如果钻孔号和时间为空，跳到下一个表
					{
						m_ProgressControl.SetPos(RecordCount);
						break;
					}

					CString strSql;
					int i=0;
					/*TB1*/
					CString tb1Values[8];
					tb1Values[0]=str[1];
					tb1Values[1]=SimplifyTime(str[0]);
					for(i=2;i<8;i++)
						tb1Values[i]=str[i];
					/**************/

					CString tb2Values[9];
					tb2Values[0]=str[1];
					tb2Values[1]=SimplifyTime(str[0]);
					for(i=2;i<9;i++)
					{
						tb2Values[i]=str[i+6];
					}

					CString tb3Values[7];
					tb3Values[0]=str[1];
					tb3Values[1]=SimplifyTime(str[0]);
					for(i=2;i<7;i++)
						tb3Values[i]=str[i+13];

					CString tb4Values[6];
					tb4Values[0]=str[1];
					tb4Values[1]=SimplifyTime(str[0]);
					for(i=2;i<6;i++)
						tb4Values[i]=str[i+18];

					CString TbSql[4];
					TbSql[0]=L"INSERT INTO TB1(GCJIA,[TIME],BJ,CCH,CCI,LLPL,BX,DYM) VALUES("+FormatValuesString(tb1Values,8)+L")";
					TbSql[1]=L"INSERT INTO TB2(GCJIA,[TIME],CL,PH,SAND,MAXTEM,MINTEM,YZ,TY) VALUES("+FormatValuesString(tb2Values,9)+L")";
					TbSql[2]=L"INSERT INTO TB3(GCJIA,[TIME],3MCDB,15MCDB,BGWZ,SGWZ,JDLY) VALUES("+FormatValuesString(tb3Values,7)+L")";
					TbSql[3]=L"INSERT INTO TB4(GCJIA,[TIME],WATER,WATERA,GAS,GASA) VALUES("+FormatValuesString(tb4Values,6)+L")";
				
					//TestRecordCount++;
					for(int j=0;j<4;j++)
					{
						try
						{
							cmd.SetCommandText(TbSql[j]);
							long rows=0;
							cmd.ExecuteUpdate(rows,CommandTypeEnum::adCmdText,mrs);
							//cmd.Release();
						}catch(_com_error e)
						{
							CString strMessage;
							strMessage.Format(L"记录%s,%s写入错误！\r\n",SimplifyTime(str[0]),str[1]);
							CString errorMessage;
							errorMessage.Format(L"错误信息:%s\r\n\r\n",e.ErrorMessage());
							if(MessageBox(strMessage+errorMessage+L"是否继续？",L"错误",MB_ICONINFORMATION|MB_YESNO)==IDNO)
								return;
						}
					}
					rs.MoveNext();
					m_ProgressControl.SetPos(++CurrentRecort);
					this->m_strCurrentRecord.Format(L"%0.0f/%d",CurrentRecort,RecordCount-3);UpdateData(false);
				}
				rs.Close();
			}
		}
		else
		{
			AfxMessageBox(L"Access数据库文件连接失败！");
			return;
		}
		rs.Close();
		oe.Close();
		if(AfxMessageBox(L"数据导入完毕！")==IDOK)
		{
			this->PostMessageW(WM_CLOSE);
			this->m_pParentWnd->m_CurrentConnect=strAccess;
		}
	}
	else
	{
		AfxMessageBox(L"Excel文件打开失败！");
		return;
	}

}

void CopyCStringArray(CStringArray &a1,CStringArray& a2)
{
	int count=a1.GetSize();
	a2.RemoveAll();
	for(int i=0;i<count;i++)
	{
		a2.Add(a1.GetAt(i));
	}
}

void CDataInDlg::DataWarehousing(CString strExcel,CString strAccess)
{
	CStringArray SheetNames;
	GetExcelSheets(strExcel,SheetNames);
	CTableSheetsDlg tsDlg(m_ExcelName,SheetNames);
	if(tsDlg.DoModal()==IDOK)
	{
		CopyCStringArray(tsDlg.m_SheetArray,SheetNames);
	}
	else
		return;
	
	OdbcExcel oe;
	if(oe.Connect(strExcel))
	{	
		CRecordset rs(oe.GetDb());
		CString str[24];
		MConnection conn;
		CString strConnection;
		strConnection.Format(L"Provider=Microsoft.Jet.OLEDB.4.0;Data Source=%s;",strAccess);
		conn.SetConnectionString(strConnection);
		//if(!CheckAccess(strAccess))
		//	return;
		if(conn.Open(L"",L"",L"",ConnectOption::adConnectUnspecified))
		{	
			MCommand cmd;
			MRecordset mrs;
			cmd.SetActiveConnection(conn);
			int SheetCount=SheetNames.GetSize();
			for(int sheetNum=0;sheetNum<SheetCount;sheetNum++)
			{
				CString CurSheetName=SheetNames.GetAt(sheetNum);
				this->m_CurrentSheetName.Format(L"[%s$] (%d/%d)",CurSheetName,sheetNum+1,SheetCount);UpdateData(false);
				int RecordCount=GetRecordCount(oe.GetDb(),CurSheetName);
				m_ProgressControl.SetRange(0,(int)RecordCount*0.99);//进度条设置

				CString strSql=L"SELECT * FROM [柿庄北采气区自营项目（长子深煤层）$]";
				strSql.Format(L"SELECT * FROM [%s$A:X]",CurSheetName);
				//执行查询语句
				if(!rs.Open(CRecordset::forwardOnly,strSql,CRecordset::readOnly))
				{
					MessageBox(L"读取Excel表数据错误！",L"提示");
					return;
				}
				int filedCount=24;
				rs.MoveNext();
				rs.MoveNext();
				rs.MoveNext();
				if(CurSheetName==L"排采数据")
					rs.MoveNext();
				float CurrentRecort=0;
				//遍历Excel数据写入Access中
				while(!rs.IsEOF())
				{
					try
					{
						/*********取出每一条记录的字段************/
						rs.GetFieldValue((short)0,str[0]);
						rs.GetFieldValue(1,str[1]);
						for(int i=2;i<24;i++)
						{
							rs.GetFieldValue(i,str[i]);
						}
						/******************************/
					}
					catch(_com_error e)
					{
						CString errormessage;
						errormessage.Format(L"读取数据失败!\r\n错误信息:%s",e.ErrorMessage());
						AfxMessageBox(errormessage);///显示错误信息
						return;
					}
					if(str[0]==L"" || str[1]==L"")//如果钻孔号和时间为空，跳到下一个表
					{
						m_ProgressControl.SetPos(RecordCount);
						break;
					}

					CString strSql;
					int i=0;
					/*TB1*/
					CString tb1Values[8];
					tb1Values[0]=str[1];
					tb1Values[1]=SimplifyTime(str[0]);
					for(i=2;i<8;i++)
						tb1Values[i]=str[i];
					/**************/

					CString tb2Values[9];
					tb2Values[0]=str[1];
					tb2Values[1]=SimplifyTime(str[0]);
					for(i=2;i<9;i++)
					{
						tb2Values[i]=str[i+6];
					}

					CString tb3Values[7];
					tb3Values[0]=str[1];
					tb3Values[1]=SimplifyTime(str[0]);
					for(i=2;i<7;i++)
						tb3Values[i]=str[i+13];

					CString tb4Values[6];
					tb4Values[0]=str[1];
					tb4Values[1]=SimplifyTime(str[0]);
					for(i=2;i<6;i++)
						tb4Values[i]=str[i+18];

					CString TbSql[4];
					TbSql[0]=L"INSERT INTO TB1(GCJIA,[TIME],BJ,CCH,CCI,LLPL,BX,DYM) VALUES("+FormatValuesString(tb1Values,8)+L")";
					TbSql[1]=L"INSERT INTO TB2(GCJIA,[TIME],CL,PH,SAND,MAXTEM,MINTEM,YZ,TY) VALUES("+FormatValuesString(tb2Values,9)+L")";
					TbSql[2]=L"INSERT INTO TB3(GCJIA,[TIME],3MCDB,15MCDB,BGWZ,SGWZ,JDLY) VALUES("+FormatValuesString(tb3Values,7)+L")";
					TbSql[3]=L"INSERT INTO TB4(GCJIA,[TIME],WATER,WATERA,GAS,GASA) VALUES("+FormatValuesString(tb4Values,6)+L")";
				
					//TestRecordCount++;
					for(int j=0;j<4;j++)
					{
						try
						{
							cmd.SetCommandText(TbSql[j]);
							long rows=0;
							cmd.ExecuteUpdate(rows,CommandTypeEnum::adCmdText,mrs);
							//cmd.Release();
						}catch(_com_error e)
						{
							CString strMessage;
							strMessage.Format(L"记录%s,%s写入错误！\r\n",SimplifyTime(str[0]),str[1]);
							CString errorMessage;
							errorMessage.Format(L"错误信息:%s\r\n\r\n",e.ErrorMessage());
							if(MessageBox(strMessage+errorMessage+L"是否继续？",L"错误",MB_ICONINFORMATION|MB_YESNO)==IDNO)
							{
								//this->m_CurrentSheetName=L"CurrentSheetName";
								//this->m_strCurrentRecord=L"Record";UpdateData(false);
								return;
							}
						}
					}
					rs.MoveNext();
					m_ProgressControl.SetPos(++CurrentRecort);
					this->m_strCurrentRecord.Format(L"%0.0f/%d",CurrentRecort,RecordCount-3);UpdateData(false);
				}
				rs.Close();
			}
		}
		else
		{
			AfxMessageBox(L"Access数据库文件连接失败！");
			return;
		}
		rs.Close();
		oe.Close();
		if(AfxMessageBox(L"数据导入完毕！")==IDOK)
		{
			this->PostMessageW(WM_CLOSE);
			this->m_pParentWnd->m_CurrentConnect=strAccess;
		}
	}
	else
	{
		AfxMessageBox(L"Excel文件打开失败！");
		return;
	}

}

int CDataInDlg::CheckExcel(CString str)
{
	Table_Sheet ts=GetTableSheet(m_ExcelName);
	OdbcExcel oe;
	if(oe.Connect(str))
	{
		int RecordCount=GetRecordCount(oe.GetDb());
		m_ProgressControl.SetRange(0,RecordCount-2);//进度条设置
		CRecordset rs(oe.GetDb());
		CString strSql=L"SELECT * FROM [柿庄北采气区自营项目（长子深煤层）$]";
		//执行查询语句
		rs.Open(CRecordset::forwardOnly,strSql,CRecordset::readOnly);
		int pos=0;
		while(!rs.IsBOF())
		{
			CString str1,str2;
			rs.GetFieldValue((short)0,str1);
			rs.GetFieldValue(1,str2);
			if(str1==L"时间" && str2==L"井号")
			{
				return pos;
			}
			rs.MoveNext();
			pos++;
		}
		return -1;
	}
	else
	{
		return -1;
	}
}

int CDataInDlg::CheckAccess(CString strAccess)
{
	MConnection conn;
	MCommand cmd;
	MRecordset mrs;
	CString strConnection;
	strConnection.Format(L"Provider=Microsoft.Jet.OLEDB.4.0;Data Source=%s;",strAccess);
	conn.SetConnectionString(strConnection);
	if(conn.Open(L"",L"",L"",ConnectOption::adConnectUnspecified))
	{	
		cmd.SetActiveConnection(conn);
		CString str[4]={L"DELETE FROM TB1",L"DELETE FROM TB2",L"DELETE FROM TB3",L"DELETE FROM TB4"};
		int flag=0;
		try{
			for(int i=0;i<4;i++)
			{
				cmd.SetCommandText(str[i]);
				long rows=0;
				if(cmd.ExecuteUpdate(rows,CommandTypeEnum::adCmdText,mrs))
					flag++;
			}
		}catch(_com_error e)
		{
			CString errormessage;
			errormessage.Format(L"Access数据库错误!\r\n错误信息:%s",e.ErrorMessage());
			AfxMessageBox(errormessage);///显示错误信息
			return 0;
		}

		if(flag==4)
			return 1;
	}
	else
		return 0;
}

void CDataInDlg::OnBnClickedBtnCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	this->PostMessage(WM_CLOSE);
}

BOOL CDataInDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	((CButton*)GetDlgItem(IDC_BTN_OPENFILE))->GetFocus();
	((CEdit*)GetDlgItem(IDC_EDT_ACCESS))->GetFocus();
	if(this->m_OperateType==1)
		SetWindowTextW(L"录入坐标数据");
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDataInDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	
	CDialogEx::OnRButtonDown(nFlags, point);
}

struct ParaStruct
{
	CString strExcelName;
	CString strExcel;
	CString strAccess;
	CProgressCtrl *pProgressCtrl;
	CString *pCurrentSheetName;
	CWnd* pWnd;
	CString* pCurrentRecord;
	ParaStruct()
	{
		pProgressCtrl=NULL;
		pCurrentSheetName=NULL;
		pWnd=NULL;
		pCurrentRecord=NULL;
	}
};

void DataInput(ParaStruct* p)
{
	
	Table_Sheet ts=GetTableSheet(p->strExcelName);
	if(ts.m_NumberOfSheet<1)
	{
		AfxMessageBox(L"Excel数据错误！");
		return;
	}
	OdbcExcel oe;
	if(oe.Connect(p->strExcel))
	{
		
		CRecordset rs(oe.GetDb());

		CString str[24];
		MConnection conn;
		CString strConnection;
		strConnection.Format(L"Provider=Microsoft.Jet.OLEDB.4.0;Data Source=%s;",p->strAccess);
		conn.SetConnectionString(strConnection);
		//if(!CheckAccess(strAccess))
		//	return;
		if(conn.Open(L"",L"",L"",ConnectOption::adConnectUnspecified))
		{	
			MCommand cmd;
			MRecordset mrs;
			cmd.SetActiveConnection(conn);
			for(int sheetNum=0;sheetNum<ts.m_NumberOfSheet;sheetNum++)
			{
				p->pCurrentSheetName->Format(L"[%s$] (%d/%d)",ts.m_Str[sheetNum],sheetNum+1,ts.m_NumberOfSheet);p->pWnd->UpdateData(false);
				int RecordCount=GetRecordCount(oe.GetDb(),ts.m_Str[sheetNum]);
				p->pProgressCtrl->SetRange(0,(int)RecordCount*0.99);//进度条设置

				CString strSql=L"SELECT * FROM [柿庄北采气区自营项目（长子深煤层）$]";
				strSql.Format(L"SELECT * FROM [%s$]",ts.m_Str[sheetNum]);
				//执行查询语句
				if(!rs.Open(CRecordset::forwardOnly,strSql,CRecordset::readOnly))
				{
					//MessageBox(L"读取Excel表数据错误！",L"提示");
					return;
				}
				int filedCount=24;
				rs.MoveNext();
				rs.MoveNext();
				rs.MoveNext();
				if(ts.m_Str[sheetNum]==L"排采数据")
					rs.MoveNext();
				float CurrentRecort=0;
				//遍历Excel数据写入Access中
				while(!rs.IsEOF())
				{
					try
					{
						/*********取出每一条记录的字段************/
						rs.GetFieldValue((short)0,str[0]);
						rs.GetFieldValue(1,str[1]);

						for(int i=2;i<24;i++)
						{
							rs.GetFieldValue(i,str[i]);
						}
						/******************************/
					}
					catch(_com_error e)
					{
						CString errormessage;
						errormessage.Format(L"读取数据失败!\r\n错误信息:%s",e.ErrorMessage());
						AfxMessageBox(errormessage);///显示错误信息
						return;
					}
					if(str[0]==L"" || str[1]==L"")//如果钻孔号和时间为空，跳到下一个表
					{
						p->pProgressCtrl->SetPos(RecordCount);
						break;
					}

					CString strSql;
					int i=0;
					/*TB1*/
					CString tb1Values[8];
					tb1Values[0]=str[1];
					tb1Values[1]=SimplifyTime(str[0]);
					for(i=2;i<8;i++)
						tb1Values[i]=str[i];
					/**************/

					CString tb2Values[9];
					tb2Values[0]=str[1];
					tb2Values[1]=SimplifyTime(str[0]);
					for(i=2;i<9;i++)
					{
						tb2Values[i]=str[i+6];
					}

					CString tb3Values[7];
					tb3Values[0]=str[1];
					tb3Values[1]=SimplifyTime(str[0]);
					for(i=2;i<7;i++)
						tb3Values[i]=str[i+13];

					CString tb4Values[6];
					tb4Values[0]=str[1];
					tb4Values[1]=SimplifyTime(str[0]);
					for(i=2;i<6;i++)
						tb4Values[i]=str[i+18];

					CString TbSql[4];
					TbSql[0]=L"INSERT INTO TB1(GCJIA,[TIME],BJ,CCH,CCI,LLPL,BX,DYM) VALUES("+FormatValuesString(tb1Values,8)+L")";
					TbSql[1]=L"INSERT INTO TB2(GCJIA,[TIME],CL,PH,SAND,MAXTEM,MINTEM,YZ,TY) VALUES("+FormatValuesString(tb2Values,9)+L")";
					TbSql[2]=L"INSERT INTO TB3(GCJIA,[TIME],3MCDB,15MCDB,BGWZ,SGWZ,JDLY) VALUES("+FormatValuesString(tb3Values,7)+L")";
					TbSql[3]=L"INSERT INTO TB4(GCJIA,[TIME],WATER,WATERA,GAS,GASA) VALUES("+FormatValuesString(tb4Values,6)+L")";
				
					//TestRecordCount++;
					for(int j=0;j<4;j++)
					{
						try
						{
							cmd.SetCommandText(TbSql[j]);
							long rows=0;
							cmd.ExecuteUpdate(rows,CommandTypeEnum::adCmdText,mrs);
							//cmd.Release();
						}catch(_com_error e)
						{
							CString strMessage;
							strMessage.Format(L"记录%s,%s写入错误！\r\n",SimplifyTime(str[0]),str[1]);
							CString errorMessage;
							errorMessage.Format(L"错误信息:%s\r\n\r\n",e.ErrorMessage());
							//if(MessageBox(strMessage+errorMessage+L"是否继续？",L"错误",MB_ICONINFORMATION|MB_YESNO)==IDNO)
								return;
						}
					}
					rs.MoveNext();
					p->pProgressCtrl->SetPos(++CurrentRecort);
					p->pCurrentRecord->Format(L"%0.0f/%d",CurrentRecort,RecordCount-3);p->pWnd->UpdateData(false);
				}
				rs.Close();
			}
		}
		else
		{
			AfxMessageBox(L"Access数据库文件连接失败！");
			return;
		}
		rs.Close();
		oe.Close();
		if(AfxMessageBox(L"数据导入完毕！")==IDOK)
		{
			p->pWnd->PostMessageW(WM_CLOSE);
			//p.pWnd->m_pParentWnd->m_CurrentConnect=p.strAccess;
		}
	}
	else
	{
		AfxMessageBox(L"Excel文件打开失败！");
		return;
	}
}

UINT WorkThread(LPVOID pParam) 
{ 
	DataInput((ParaStruct*)pParam);
    return  0 ; 
} 

void CDataInDlg::InputCoorData(CString strExcel,CString strAccess)
{
	CDatabase database;
	CString strDriver=L"Microsoft Excel Driver (*.xls)";
	CString strDsn;
	strDsn.Format(L"ODBC;DRIVER={%s};FIRSTROWHASNAMES=1;DBQ=%s",strDriver,strExcel);
	if(database.Open(NULL,false,false,strDsn))
	{
		CStringArray strArray;
		GetExcelSheets(strExcel,strArray);
		CString sheetName=strArray.GetAt(0);;
		CRecordset recordset(&database);
		CString strSql;
		strSql.Format(L"SELECT * FROM [%s$]",sheetName);
		if(!recordset.Open(CRecordset::forwardOnly,strSql,CRecordset::readOnly))
		{
			MessageBox(L"读取Excel数据错误",L"提示");
			return;
		}
		MConnection conn;//定义连接对象
		MCommand cmd;//定义操作对象
		MRecordset rst;//定义记录集对象
		CString strConnection;//连接字符串
		strConnection.Format(L"Provider=Microsoft.Jet.OLEDB.4.0;Data Source=%s;",strAccess);//格式化字符串
		conn.SetConnectionString(strConnection);//为连接对象设置连接字符串
		if(!conn.Open(L"",L"",L"",ConnectOption::adConnectUnspecified))//打开Access文件
		{
			MessageBox(L"连接Access错误！",L"提示");
			return;
		}
		
		this->m_CurrentSheetName=sheetName;
		int RecordCount=GetRecordCount(&database,sheetName);
		this->m_ProgressControl.SetRange(0,RecordCount);
		int CurrentRecord=0;
		CString strInsertSql;
		cmd.SetActiveConnection(conn);//绑定连接对象
		long rows=0;//影响行数
		while(!recordset.IsEOF())
		{
			CString value[4];
			for(int i=0;i<4;i++)
			{
				recordset.GetFieldValue(i,value[i]);
			}
			strInsertSql.Format(L"INSERT INTO ZKTB1(GCJIA,ZKX,ZKY,ZKZ) VALUES('%s',%s,%s,%s)",value[0],value[1],value[2],value[3]);
			cmd.SetCommandText(strInsertSql);//设置命令字符串（INSERT语句）
			try
			{
				cmd.ExecuteUpdate(rows,CommandTypeEnum::adCmdText,rst);//执行插入操作并将结果赋值给记录集对象
				CurrentRecord++;
			}
			catch(_com_error e)
			{
				CString strMessage;
				strMessage.Format(L"钻井%s写入错误！\r\n",value[0]);
				CString errorMessage;
				errorMessage.Format(L"错误信息:%s\r\n\r\n",e.ErrorMessage());
				if(MessageBox(strMessage+errorMessage+L"是否继续？",L"错误",MB_ICONINFORMATION|MB_YESNO)==IDNO)
				{
					//this->m_CurrentSheetName=L"CurrentSheetName";
					//this->m_strCurrentRecord=L"Record";UpdateData(false);
					return;
				}
			}
			CString strCurRecord;
			strCurRecord.Format(L"%d/%d",CurrentRecord,RecordCount);
			this->m_strCurrentRecord=strCurRecord;UpdateData(false);
			this->m_ProgressControl.SetPos(CurrentRecord);
			recordset.MoveNext();
		}
		recordset.Close();
		MessageBox(L"数据录入完成",L"提示");
	}
}

void CDataInDlg::OnBnClickedBtnDo()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strExcel,strAccess;
	GetDlgItemText(IDC_EDT_EXCEL,strExcel);
	GetDlgItemText(IDC_EDT_ACCESS,strAccess);
	if(strExcel.IsEmpty() || strAccess.IsEmpty())
	{
		AfxMessageBox(L"请设置文件路径！");
	}
	else
	{
		if(this->m_OperateType==0)
			DataWarehousing(strExcel,strAccess);
		if(this->m_OperateType==1)
			this->InputCoorData(strExcel,strAccess);
	}
}

/*		ParaStruct p;
		p.pCurrentRecord=&m_strCurrentRecord;
		p.pCurrentSheetName=&m_CurrentSheetName;
		p.pProgressCtrl=&m_ProgressControl;
		p.pWnd=this;
		p.strAccess=strAccess;
		p.strExcel=strExcel;
		p.strExcelName=m_ExcelName;
		AfxBeginThread(WorkThread,&p);
*/