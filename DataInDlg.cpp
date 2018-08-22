



// DataInDlg.cpp : ʵ���ļ�
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
// CDataInDlg �Ի���

IMPLEMENT_DYNAMIC(CDataInDlg, CDialogEx)

Table_Sheet GetTableSheet(CString str)
{
	if(str==L"1����5��-������������ݱ�.xls")
	{
		Table_Sheet ts(4);
		ts.m_Str[0]=L"���������1����ͣ������";
		ts.m_Str[1]=L"���������1������������";
		ts.m_Str[2]=L"���������5������1-10��";
		ts.m_Str[3]=L"���������5������11-12��";
		return ts;
	}
	else if(str==L"2��-���ز��������ݱ�2015.xls")
	{
		Table_Sheet ts(1);
		ts.m_Str[0]=L"���ز�����2��";
		return ts;
	}
	else if(str==L"3��-���ز��������ݱ�2015.xls")
	{
		Table_Sheet ts(1);
		ts.m_Str[0]=L"���ز�����3��";
		return ts;
	}
	else if(str==L"��ׯ��������2015.11.12���ݱ�.xls")
	{
		Table_Sheet ts(4);
		ts.m_Str[0]=L"��ׯ��������������Ŀ(��̽��";
		ts.m_Str[1]=L"��ׯ��������������̽��������ú�㣩";
		ts.m_Str[2]=L"��ׯ����������Ӫ��Ŀ����̽��";
		ts.m_Str[3]=L"��ׯ����������Ӫ��Ŀ��������ú�㣩";
		return ts;
	}
	else if(str==L"��ׯ������2������.xls")
	{
		Table_Sheet ts(1);
		ts.m_Str[0]=L"��ׯ����������";
		return ts;
	}
	else if(str==L"��ׯ������5������.xls")
	{
		Table_Sheet ts(1);
		ts.m_Str[0]=L"��ׯ����������";
		return ts;
	}
	else
	{
		Table_Sheet ts(1);
		ts.m_Str[0]=L"�Ų�����";
		return ts;
	}
}

void GetExcelSheets(CString strExcel,CStringArray& SheetArray)
{
	//CStringArray SheetArray;
	CApplication ExcelApp;
	//����Excel 2000������(����Excel)   
    if (!ExcelApp.CreateDispatch(_T("Excel.Application"),NULL))   
    {   
        AfxMessageBox(_T("����Excel����ʧ��,�����û�а�װEXCEL������!"));   
        return;  
    }  
    ExcelApp.put_DisplayAlerts(FALSE);
	CString ExcelFile=strExcel;  
    CWorkbooks WorkBooks;   
    CWorkbook WorkBook;   
    CWorksheets WorkSheets;   
    CWorksheet WorkSheet;   
    CRange        ExcelRange; 
	//����ģ���ļ��������ĵ�   
    WorkBooks.AttachDispatch(ExcelApp.get_Workbooks(),true);   
    LPDISPATCH lpDis = NULL;  
    lpDis = WorkBooks.Add(COleVariant(strExcel));   
	
    if (lpDis)  
    {  
        WorkBook.AttachDispatch(lpDis);   
        //�õ�Worksheets   
        WorkSheets.AttachDispatch(WorkBook.get_Worksheets(),true);   
          
        //��¼�򿪵��ļ�����  
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
// CDataInDlg ��Ϣ�������


void CDataInDlg::OnBnClickedBtnOpenfile()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CFileDialog OpenDlg(true,L".xls",L"",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,L"Excel�ļ�|*.xls|�����ļ�|*.*|",NULL);
	if(OpenDlg.DoModal()==IDOK)
	{
		CString str=OpenDlg.GetPathName();
		((CEdit*)GetDlgItem(IDC_EDT_EXCEL))->SetWindowTextW(str);
		m_ExcelName=OpenDlg.GetFileName();
	}
}


void CDataInDlg::OnBnClickedBtnSavefile()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CFileDialog OpenDlg(true,L".mdb",L"",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,L"Access�ļ�|*.mdb|�����ļ�|*.*|",NULL);
	if(OpenDlg.DoModal()==IDOK)
	{
		CString str=OpenDlg.GetPathName();
		((CEdit*)GetDlgItem(IDC_EDT_ACCESS))->SetWindowTextW(str);
	}
}

//��ʽ��VALUES����
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

//����ʱ�亯��
CString SimplifyTime(CString str)
{
	int pos=str.ReverseFind(' ');
	return str.Left(pos);
}

int GetRecordCount(CDatabase *pDb)
{
	CRecordset Rs(pDb);
	CString strSql=L"SELECT COUNT(*) FROM [��ׯ����������Ӫ��Ŀ��������ú�㣩$]";
	Rs.Open(CRecordset::forwardOnly,strSql,CRecordset::readOnly);
	CString strCount;
	Rs.GetFieldValue((short)0,strCount);
	return _wtoi(strCount.GetBuffer(strCount.GetLength()));
}

int GetRecordCount(CDatabase *pDb,CString SheetName)
{
	CRecordset Rs(pDb);
	CString strSql=L"SELECT COUNT(*) FROM [��ׯ����������Ӫ��Ŀ��������ú�㣩$]";
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
		MessageBox(L"Excel���ݴ���",L"��ʾ");
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
				m_ProgressControl.SetRange(0,(short)RecordCount*0.99);//����������

				CString strSql=L"SELECT * FROM [��ׯ����������Ӫ��Ŀ��������ú�㣩$]";
				strSql.Format(L"SELECT * FROM [%s$A:X]",ts.m_Str[sheetNum]);
				//ִ�в�ѯ���
				if(!rs.Open(CRecordset::forwardOnly,strSql,CRecordset::readOnly))
				{
					MessageBox(L"��ȡExcel�����ݴ���",L"��ʾ");
					return;
				}
				int filedCount=24;
				rs.MoveNext();
				rs.MoveNext();
				rs.MoveNext();
				if(ts.m_Str[sheetNum]==L"�Ų�����")
					rs.MoveNext();
				float CurrentRecort=0;
				//����Excel����д��Access��
				while(!rs.IsEOF())
				{
					try
					{
						/*********ȡ��ÿһ����¼���ֶ�************/
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
						errormessage.Format(L"��ȡ����ʧ��!\r\n������Ϣ:%s",e.ErrorMessage());
						AfxMessageBox(errormessage);///��ʾ������Ϣ
						return;
					}
					if(str[0]==L"" || str[1]==L"")//�����׺ź�ʱ��Ϊ�գ�������һ����
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
							strMessage.Format(L"��¼%s,%sд�����\r\n",SimplifyTime(str[0]),str[1]);
							CString errorMessage;
							errorMessage.Format(L"������Ϣ:%s\r\n\r\n",e.ErrorMessage());
							if(MessageBox(strMessage+errorMessage+L"�Ƿ������",L"����",MB_ICONINFORMATION|MB_YESNO)==IDNO)
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
			AfxMessageBox(L"Access���ݿ��ļ�����ʧ�ܣ�");
			return;
		}
		rs.Close();
		oe.Close();
		if(AfxMessageBox(L"���ݵ�����ϣ�")==IDOK)
		{
			this->PostMessageW(WM_CLOSE);
			this->m_pParentWnd->m_CurrentConnect=strAccess;
		}
	}
	else
	{
		AfxMessageBox(L"Excel�ļ���ʧ�ܣ�");
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
				m_ProgressControl.SetRange(0,(int)RecordCount*0.99);//����������

				CString strSql=L"SELECT * FROM [��ׯ����������Ӫ��Ŀ��������ú�㣩$]";
				strSql.Format(L"SELECT * FROM [%s$A:X]",CurSheetName);
				//ִ�в�ѯ���
				if(!rs.Open(CRecordset::forwardOnly,strSql,CRecordset::readOnly))
				{
					MessageBox(L"��ȡExcel�����ݴ���",L"��ʾ");
					return;
				}
				int filedCount=24;
				rs.MoveNext();
				rs.MoveNext();
				rs.MoveNext();
				if(CurSheetName==L"�Ų�����")
					rs.MoveNext();
				float CurrentRecort=0;
				//����Excel����д��Access��
				while(!rs.IsEOF())
				{
					try
					{
						/*********ȡ��ÿһ����¼���ֶ�************/
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
						errormessage.Format(L"��ȡ����ʧ��!\r\n������Ϣ:%s",e.ErrorMessage());
						AfxMessageBox(errormessage);///��ʾ������Ϣ
						return;
					}
					if(str[0]==L"" || str[1]==L"")//�����׺ź�ʱ��Ϊ�գ�������һ����
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
							strMessage.Format(L"��¼%s,%sд�����\r\n",SimplifyTime(str[0]),str[1]);
							CString errorMessage;
							errorMessage.Format(L"������Ϣ:%s\r\n\r\n",e.ErrorMessage());
							if(MessageBox(strMessage+errorMessage+L"�Ƿ������",L"����",MB_ICONINFORMATION|MB_YESNO)==IDNO)
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
			AfxMessageBox(L"Access���ݿ��ļ�����ʧ�ܣ�");
			return;
		}
		rs.Close();
		oe.Close();
		if(AfxMessageBox(L"���ݵ�����ϣ�")==IDOK)
		{
			this->PostMessageW(WM_CLOSE);
			this->m_pParentWnd->m_CurrentConnect=strAccess;
		}
	}
	else
	{
		AfxMessageBox(L"Excel�ļ���ʧ�ܣ�");
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
		m_ProgressControl.SetRange(0,RecordCount-2);//����������
		CRecordset rs(oe.GetDb());
		CString strSql=L"SELECT * FROM [��ׯ����������Ӫ��Ŀ��������ú�㣩$]";
		//ִ�в�ѯ���
		rs.Open(CRecordset::forwardOnly,strSql,CRecordset::readOnly);
		int pos=0;
		while(!rs.IsBOF())
		{
			CString str1,str2;
			rs.GetFieldValue((short)0,str1);
			rs.GetFieldValue(1,str2);
			if(str1==L"ʱ��" && str2==L"����")
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
			errormessage.Format(L"Access���ݿ����!\r\n������Ϣ:%s",e.ErrorMessage());
			AfxMessageBox(errormessage);///��ʾ������Ϣ
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->PostMessage(WM_CLOSE);
}

BOOL CDataInDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	((CButton*)GetDlgItem(IDC_BTN_OPENFILE))->GetFocus();
	((CEdit*)GetDlgItem(IDC_EDT_ACCESS))->GetFocus();
	if(this->m_OperateType==1)
		SetWindowTextW(L"¼����������");
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CDataInDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	
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
		AfxMessageBox(L"Excel���ݴ���");
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
				p->pProgressCtrl->SetRange(0,(int)RecordCount*0.99);//����������

				CString strSql=L"SELECT * FROM [��ׯ����������Ӫ��Ŀ��������ú�㣩$]";
				strSql.Format(L"SELECT * FROM [%s$]",ts.m_Str[sheetNum]);
				//ִ�в�ѯ���
				if(!rs.Open(CRecordset::forwardOnly,strSql,CRecordset::readOnly))
				{
					//MessageBox(L"��ȡExcel�����ݴ���",L"��ʾ");
					return;
				}
				int filedCount=24;
				rs.MoveNext();
				rs.MoveNext();
				rs.MoveNext();
				if(ts.m_Str[sheetNum]==L"�Ų�����")
					rs.MoveNext();
				float CurrentRecort=0;
				//����Excel����д��Access��
				while(!rs.IsEOF())
				{
					try
					{
						/*********ȡ��ÿһ����¼���ֶ�************/
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
						errormessage.Format(L"��ȡ����ʧ��!\r\n������Ϣ:%s",e.ErrorMessage());
						AfxMessageBox(errormessage);///��ʾ������Ϣ
						return;
					}
					if(str[0]==L"" || str[1]==L"")//�����׺ź�ʱ��Ϊ�գ�������һ����
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
							strMessage.Format(L"��¼%s,%sд�����\r\n",SimplifyTime(str[0]),str[1]);
							CString errorMessage;
							errorMessage.Format(L"������Ϣ:%s\r\n\r\n",e.ErrorMessage());
							//if(MessageBox(strMessage+errorMessage+L"�Ƿ������",L"����",MB_ICONINFORMATION|MB_YESNO)==IDNO)
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
			AfxMessageBox(L"Access���ݿ��ļ�����ʧ�ܣ�");
			return;
		}
		rs.Close();
		oe.Close();
		if(AfxMessageBox(L"���ݵ�����ϣ�")==IDOK)
		{
			p->pWnd->PostMessageW(WM_CLOSE);
			//p.pWnd->m_pParentWnd->m_CurrentConnect=p.strAccess;
		}
	}
	else
	{
		AfxMessageBox(L"Excel�ļ���ʧ�ܣ�");
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
			MessageBox(L"��ȡExcel���ݴ���",L"��ʾ");
			return;
		}
		MConnection conn;//�������Ӷ���
		MCommand cmd;//�����������
		MRecordset rst;//�����¼������
		CString strConnection;//�����ַ���
		strConnection.Format(L"Provider=Microsoft.Jet.OLEDB.4.0;Data Source=%s;",strAccess);//��ʽ���ַ���
		conn.SetConnectionString(strConnection);//Ϊ���Ӷ������������ַ���
		if(!conn.Open(L"",L"",L"",ConnectOption::adConnectUnspecified))//��Access�ļ�
		{
			MessageBox(L"����Access����",L"��ʾ");
			return;
		}
		
		this->m_CurrentSheetName=sheetName;
		int RecordCount=GetRecordCount(&database,sheetName);
		this->m_ProgressControl.SetRange(0,RecordCount);
		int CurrentRecord=0;
		CString strInsertSql;
		cmd.SetActiveConnection(conn);//�����Ӷ���
		long rows=0;//Ӱ������
		while(!recordset.IsEOF())
		{
			CString value[4];
			for(int i=0;i<4;i++)
			{
				recordset.GetFieldValue(i,value[i]);
			}
			strInsertSql.Format(L"INSERT INTO ZKTB1(GCJIA,ZKX,ZKY,ZKZ) VALUES('%s',%s,%s,%s)",value[0],value[1],value[2],value[3]);
			cmd.SetCommandText(strInsertSql);//���������ַ�����INSERT��䣩
			try
			{
				cmd.ExecuteUpdate(rows,CommandTypeEnum::adCmdText,rst);//ִ�в���������������ֵ����¼������
				CurrentRecord++;
			}
			catch(_com_error e)
			{
				CString strMessage;
				strMessage.Format(L"�꾮%sд�����\r\n",value[0]);
				CString errorMessage;
				errorMessage.Format(L"������Ϣ:%s\r\n\r\n",e.ErrorMessage());
				if(MessageBox(strMessage+errorMessage+L"�Ƿ������",L"����",MB_ICONINFORMATION|MB_YESNO)==IDNO)
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
		MessageBox(L"����¼�����",L"��ʾ");
	}
}

void CDataInDlg::OnBnClickedBtnDo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strExcel,strAccess;
	GetDlgItemText(IDC_EDT_EXCEL,strExcel);
	GetDlgItemText(IDC_EDT_ACCESS,strAccess);
	if(strExcel.IsEmpty() || strAccess.IsEmpty())
	{
		AfxMessageBox(L"�������ļ�·����");
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