// AnalyseDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Tool.h"
#include "AnalyseDlg.h"
#include "afxdialogex.h"
#include "OdbcExcel.h"
#include "ChangeLineDlg.h"
#include "SetTimeDlg.h"

#include "MyFunction.h"

#define WM_ZKSELECTCHANGE WM_USER+2
/*******************************************/
CString GetNameFromCaption(CString str)
{
	/*CString str[22]={L"�þ�",L"���",L"���",L"��������",L"��Ч",L"��Һ��",L"������",L"PH",L"��ɳ",
		L"����¶�",L"����¶�",L"����",L"��ѹ",L"3#ú�㶥��",L"15#ú�㶥��",L"�ù�λ��",L"ɸ��λ��",
		L"������ѹ",L"��ˮ��",L"�ۼƲ�ˮ��",L"������",L"�ۼ�������"};*/
	if(str==L"�þ�")
		return L"BJ";
	if(str==L"���")
		return L"CCH";
	if(str==L"���")
		return L"CCI";
	if(str==L"��������")
		return L"LLPL";
	if(str==L"��Ч")
		return L"BX";
	if(str==L"��Һ��")
		return L"DYM";
	if(str==L"������")
		return L"CL";
	if(str==L"PH")
		return L"PH";
	if(str==L"��ɳ")
		return L"SAND";
	if(str==L"����¶�")
		return L"MAXTEM";
	if(str==L"����¶�")
		return L"MINTEM";
	if(str==L"����")
		return L"YZ";
	if(str==L"��ѹ")
		return L"TY";
	if(str==L"3#ú�㶥��")
		return L"[3MCDB]";
	if(str==L"15#ú�㶥��")
		return L"[15MCDB]";
	if(str==L"�ù�λ��")
		return L"BGWZ";
	if(str==L"ɸ��λ��")
		return L"SGWZ";
	if(str==L"������ѹ")
		return L"JDLY";
	if(str==L"��ˮ��")
		return L"WATER";
	if(str==L"�ۼƲ�ˮ��")
		return L"WATERA";
	if(str==L"������")
		return L"GAS";
	if(str==L"�ۼ�������")
		return L"GASA";
}

CString GetTableNameFromCaption(CString str)
{
	if(str==L"�þ�"||str==L"���"||str==L"���"||str==L"��������"||str==L"��Ч"||str==L"��Һ��")
		return L"TB1";
	
	if(str==L"������"||str==L"PH"||str==L"��ɳ"||str==L"����¶�"||str==L"����¶�"||str==L"����"||str==L"��ѹ")
		return L"TB2";
	
	if(str==L"3#ú�㶥��"||str==L"15#ú�㶥��"||str==L"�ù�λ��"||str==L"ɸ��λ��"||str==L"������ѹ")
		return L"TB3";
	
	if(str==L"��ˮ��"||str==L"�ۼƲ�ˮ��"||str==L"������"||str==L"�ۼ�������")
		return L"TB4";
	

}

/*******************************************/

// CAnalyseDlg �Ի���
IMPLEMENT_DYNAMIC(CAnalyseDlg, CDialogEx)


CAnalyseDlg::CAnalyseDlg(CString str,CWnd* pParent /*=NULL*/)
	: CDialogEx(CAnalyseDlg::IDD, pParent)
{
	this->m_FilePath=str;
	m_Data = _T("");
	m_zk = _T("");
	m_MaxValue = 0.0;
	m_StartDate = _T("");
	m_EndDate = _T("");
	m_IsConnected=false;
	m_pNameValue=NULL;
	m_RecordCount=0;
	m_IsSelected=false;
	m_RecordCount = 0;
	m_IsInited=false;
	m_IsDrawn=false;
	m_LineType=0;
	m_LineWidth=0;
	m_LineColor=RGB(0,0,255);
	m_IsUpdated=false;
}

CAnalyseDlg::~CAnalyseDlg()
{
	delete [] m_pNameValue;
}

void CAnalyseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_CBString(pDX, IDC_COM_DATA, m_Data);
	DDX_CBString(pDX, IDC_COM_ZK, m_zk);
	DDX_Text(pDX, IDC_STATIC_MAX, m_MaxValue);
	DDX_Text(pDX, IDC_STATIC_STARTDATE, m_StartDate);
	DDX_Text(pDX, IDC_STATIC_ENDDATE, m_EndDate);
	//  DDX_Control(pDX, IDC_STATIC_PIC, m_PicStatic);
	DDX_Control(pDX, IDC_STATIC_PIC, m_PicStatic);
	DDX_Text(pDX, IDC_EDIT_COUNT, m_RecordCount);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_StartTimeCtrl);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, m_EndTimeCtrl);
}

BEGIN_MESSAGE_MAP(CAnalyseDlg, CDialogEx)
	ON_WM_RBUTTONDOWN()
	ON_CBN_SELCHANGE(IDC_COM_DATA, &CAnalyseDlg::OnSelchangeComData)
	ON_WM_PAINT()
	ON_WM_PAINT()
	ON_MESSAGE(WM_DRAWLINE, OnDrawLine) 
	ON_MESSAGE(WM_ZKSELECTCHANGE, OnZkSelectChange) 
	ON_WM_TIMER()
	ON_CBN_SELCHANGE(IDC_COM_ZK, &CAnalyseDlg::OnCbnSelchangeComZk)
	ON_BN_CLICKED(IDC_BTN_TO_EXCEL, &CAnalyseDlg::OnBnClickedBtnToExcel)
	ON_BN_CLICKED(IDC_BTN_CHANGE_LINE_STYLE, &CAnalyseDlg::OnBnClickedBtnChangeLineStyle)
	ON_BN_CLICKED(IDC_BTN_UPDATE, &CAnalyseDlg::OnBnClickedBtnUpdate)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER1, &CAnalyseDlg::OnDtnDatetimechangeDatetimepicker1)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER2, &CAnalyseDlg::OnDtnDatetimechangeDatetimepicker2)
END_MESSAGE_MAP()

// CAnalyseDlg ��Ϣ�������


BOOL CAnalyseDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	try
	{
		CString strConnection;
		strConnection.Format(L"Provider=Microsoft.Jet.OLEDB.4.0;Data Source=%s;",m_FilePath);
		m_conn.SetConnectionString(strConnection);
		if(m_conn.Open(L"",L"",L"",ConnectOption::adConnectUnspecified))
		{
			m_cmd.SetActiveConnection(m_conn);
			m_cmd.SetCommandText(L"SELECT DISTINCT GCJIA FROM TB1");//
			m_cmd.ExecuteQuery(CommandTypeEnum::adCmdText,m_rst);
			int NumberOfZk=m_rst.GetRecordCount();
			int i=0;
			while(!m_rst.rstEOF())
			{
				CString str=m_rst.GetString(0);
				((CComboBox*)(GetDlgItem(IDC_COM_ZK)))->InsertString(-1,str);
				m_rst.MoveNext();
			}
			((CComboBox*)(GetDlgItem(IDC_COM_ZK)))->SetCurSel(0);
			m_IsConnected=true;
		}
		else
		{
			AfxMessageBox(L"�����ݿ�ʧ�ܣ�");
		}
		
	}
	catch(_com_error e)
	{
		CString errormessage;
		errormessage.Format(L"��ȡʧ��!\r\n������Ϣ:%s",e.ErrorMessage());
		AfxMessageBox(errormessage);///��ʾ������Ϣ
	}
	CString str[19]={L"�þ�",L"���",L"���",L"��������",L"��Ч",L"��Һ��",L"������",L"PH",
		L"����¶�",L"����¶�",L"��ѹ",L"3#ú�㶥��",L"15#ú�㶥��",L"ɸ��λ��",
		L"������ѹ",L"��ˮ��",L"�ۼƲ�ˮ��",L"������",L"�ۼ�������"};
	for(int i=0;i<19;i++)
	{
		((CComboBox*)GetDlgItem(IDC_COM_DATA))->InsertString(-1,str[i]);
	}
	this->CreateToolTip();//������ʾ
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CAnalyseDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	
	this->Invalidate();
	CDC* pDC=this->GetDC();
	pDC->MoveTo(0,0);
	pDC->LineTo(100,100);
	CDialogEx::OnRButtonDown(nFlags, point);
}

void CAnalyseDlg::OnSelchangeComData()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);	
	if(m_IsSelected)
		delete [] m_pNameValue;
	this->Read();
	this->Invalidate();
	//m_IsDrawn=false;
	SetTimer(1,500,0);
	m_IsSelected=true;
}

void CAnalyseDlg::ReadAndDraw(CDC *pDC,CPen *pPen)
{
	CString sObj=GetNameFromCaption(m_Data);
	CString sTable=GetTableNameFromCaption(m_Data);

	try
	{
		CString strSql;
		strSql.Format(L"SELECT [TIME],%s FROM %s WHERE GCJIA='%s'",sObj,sTable,m_zk);
		m_cmd.SetCommandText(strSql);
		m_cmd.ExecuteQuery(CommandTypeEnum::adCmdText,m_rst);
		int RecordCount=m_rst.GetRecordCount();
		m_RecordCount=RecordCount;
		m_pNameValue=new Name_Value[RecordCount];
		CRect rect=this->GetPicRect();
		double xper=((double)rect.Width()-10)/RecordCount;
		m_xInterval=xper;
		double MaxValue=this->GetMaxValue(m_Data);
		double yper=((double)rect.Height()-5)/MaxValue;
		this->m_MaxValue=MaxValue;
		pDC->MoveTo(0,rect.bottom-4);
		this->m_StartDate=this->GetFirstDate();
		this->m_EndDate=this->GetLastDate();
		CPen *pOldPen=pDC->SelectObject(pPen);
		int i=1;
		while(!m_rst.rstEOF())
		{
			m_pNameValue[i-1].m_str=m_rst.GetString(0);
			CString str=m_rst.GetString(1);
			double value=_wtof(str);
			m_pNameValue[i-1].m_value=value;
			m_pNameValue[i-1].m_x=(int)(xper*i);
			pDC->LineTo((int)(xper*i),(int)(rect.Height()-yper*value-4));
			m_rst.MoveNext();
			i++;
		}
		pDC->SelectObject(pOldPen);
	}
	catch(_com_error e)
	{
		CString errormessage;
		errormessage.Format(L"��ȡ���ݴ���!\r\n������Ϣ:%s",e.ErrorMessage());
		AfxMessageBox(errormessage);///��ʾ������Ϣ
	}
	UpdateData(false);
}

double CAnalyseDlg::GetMaxValue(CString str)
{
	
	if(str==L"��ɳ")
		return 0.0;
	CString sObj=GetNameFromCaption(str);
	CString sTable=GetTableNameFromCaption(m_Data);
	//ȡ���ֵ
	CString SqlMax;
	SqlMax.Format(L"SELECT max(%s) FROM %s WHERE GCJIA='%s'",sObj,sTable,m_zk);
	m_cmd.SetCommandText(SqlMax);
	MRecordset mrs;
	m_cmd.ExecuteQuery(CommandTypeEnum::adCmdText,mrs);
	CString strMax=mrs.GetString(0);
	double maxValue=_wtof(strMax);
	return maxValue;
}

CString CAnalyseDlg::GetFirstDate()
{
	CString sObj=GetNameFromCaption(m_Data);
	CString sTable=GetTableNameFromCaption(m_Data);
	//ȡ��һ����¼����
	CString SqlTop;
	SqlTop.Format(L"SELECT TOP 1 [TIME] FROM %s WHERE GCJIA='%s' ORDER BY [TIME]",sTable,m_zk);
	m_cmd.SetCommandText(SqlTop);
	MRecordset mrs;
	m_cmd.ExecuteQuery(CommandTypeEnum::adCmdText,mrs);
	CString strTopTime=mrs.GetString(0);
	return strTopTime;
}

CString CAnalyseDlg::GetLastDate()
{
	CString sObj=GetNameFromCaption(m_Data);
	CString sTable=GetTableNameFromCaption(m_Data);
	//ȡ���һ���¼����
	CString SqlBot;
	SqlBot.Format(L"SELECT TOP 1 [TIME] FROM %s WHERE GCJIA='%s' ORDER BY [TIME] DESC",sTable,m_zk);
	m_cmd.SetCommandText(SqlBot);
	MRecordset mrs;
	m_cmd.ExecuteQuery(CommandTypeEnum::adCmdText,mrs);
	CString strBotTime=mrs.GetString(0);
	return strBotTime;
}

CRect CAnalyseDlg::GetPicRect()
{
	CRect r;
	CStatic* pSta=((CStatic*)GetDlgItem(IDC_STATIC_PIC));
	pSta->GetWindowRect(r);
	return r;
	CRect rect;
	rect.right=r.Width();
	rect.bottom=r.Height();
	return rect;
}

void CAnalyseDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
	if(!m_IsInited)
	{
		MRecordset rst;
		m_cmd.SetCommandText(L"SELECT TOP 1 GCJIA FROM TB4 WHERE GAS>0");
		m_cmd.ExecuteQuery(CommandTypeEnum::adCmdText,rst);
		this->m_zk=rst.GetString((long)0);
		((CComboBox*)GetDlgItem(IDC_COM_DATA))->SelectString(-1,L"������");
		UpdateData(false);
		this->OnSelchangeComData();
		m_IsInited=true;
	}
}

LRESULT CAnalyseDlg::OnDrawLine(WPARAM wParam, LPARAM lParam)
{
	CDC *pDC=m_PicStatic.GetDC();;
	CPen pen(m_LineType,m_LineWidth,m_LineColor);
	this->Draw(pDC,&pen);
	return 0;
}

void CAnalyseDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(nIDEvent==1)
	{
		this->PostMessage(WM_DRAWLINE);
		KillTimer(1);
	}
	if(nIDEvent==2)
	{
		KillTimer(2);
		MessageBox(L"��ʼʱ�����ô���!",L"��ʾ");
		
	}
	CDialogEx::OnTimer(nIDEvent);
}

void CAnalyseDlg::CreateToolTip()
{
	m_ToolTip.Create(this);  
	m_ToolTip.AddTool(GetDlgItem(IDC_STATIC_PIC),L"��ͼ����" ); //IDC_BUTTONΪ��Ҫ�����ʾ��Ϣ�İ�ť��ID
	m_ToolTip.SetDelayTime(200); //�����ӳ�
	m_ToolTip.SetTipTextColor(RGB(0,0,255) ); //������ʾ�ı�����ɫ
	m_ToolTip.SetTipBkColor( RGB(255,255,255)); //������ʾ��ı�����ɫ
	m_ToolTip.Activate(TRUE); //�����Ƿ�������ʾ

}

void CAnalyseDlg::Read()
{
	CString sObj=GetNameFromCaption(m_Data);
	CString sTable=GetTableNameFromCaption(m_Data);
	try
	{
		this->m_StartDate=this->GetFirstDate();
		this->m_EndDate=this->GetLastDate();
		if(this->m_IsUpdated)
		{
			this->m_StartTimeCtrl.GetWindowTextW(this->m_StartDate);
			this->m_EndTimeCtrl.GetWindowTextW(this->m_EndDate);
		}
		CString strSql;
		strSql.Format(L"SELECT [TIME],%s FROM %s WHERE GCJIA='%s' AND [TIME] BETWEEN #%s# AND #%s#",
			sObj,sTable,m_zk,m_StartDate,m_EndDate);
		m_cmd.SetCommandText(strSql);
		m_cmd.ExecuteQuery(CommandTypeEnum::adCmdText,m_rst);
		int RecordCount=m_rst.GetRecordCount();
		m_RecordCount=RecordCount;
		m_pNameValue=new Name_Value[RecordCount];
		CRect rect=this->GetPicRect();
		double xper=((double)rect.Width()-1)/RecordCount;
		m_xInterval=xper;
		double MaxValue=this->GetMaxValue(m_Data);
		this->m_MaxValue=MaxValue;
		int i=0;
		while(!m_rst.rstEOF())
		{
			m_pNameValue[i].m_str=m_rst.GetString(0);
			CString str=m_rst.GetString(1);
			double value=_wtof(str);
			m_pNameValue[i].m_value=value;
			m_pNameValue[i].m_x=(int)(xper*i+0.5);
			m_rst.MoveNext();
			i++;
		}
	}
	catch(_com_error e)
	{
		CString errormessage;
		errormessage.Format(L"��ȡ���ݴ���!\r\n������Ϣ:%s",e.ErrorMessage());
		AfxMessageBox(errormessage);///��ʾ������Ϣ
	}
	MyFunction fun;
	CTime t1(fun.GetYear(m_StartDate),fun.GetMonth(m_StartDate),fun.GetDay(m_StartDate),0,0,0);
	CTime t2(fun.GetYear(m_EndDate),fun.GetMonth(m_EndDate),fun.GetDay(m_EndDate),0,0,0);
	this->m_StartTimeCtrl.SetTime(&t1);
	this->m_EndTimeCtrl.SetTime(&t2);
}

void DrawPoint(CDC *pDC,int x,int y,COLORREF color)
{

	for(int i=-1;i<2;i++)
	{
		for(int j=-1;j<2;j++)
		{
			pDC->SetPixel(x+i,y+j,color);
		}
	}
}

void CAnalyseDlg::Draw(CDC *pDC,CPen* pPen)
{
	UpdateData(false);

	this->m_StartDate=this->GetFirstDate();
	this->m_EndDate=this->GetLastDate();

	CPen *pOldPen=pDC->SelectObject(pPen);
	CRect rect=this->GetPicRect();
	this->ScreenToClient(&rect);
	if(m_RecordCount==0)
		return;
	else if(m_MaxValue==0)
	{
		pDC->MoveTo(0,rect.Height()-4);
		pDC->MoveTo(rect.Width()-3,rect.Height()-4);
		return;
	}
	else
	{
		CDC *pParentDC=this->GetDC();
		pParentDC->SetBkMode(TRANSPARENT);
		double MaxValue=this->GetMaxValue(m_Data);
		double yper=((double)rect.Height()-3)/MaxValue;
		int x=m_pNameValue[0].m_x;
		int y=(int)(rect.Height()-yper*m_pNameValue[0].m_value-2);
		pDC->MoveTo(x,y);
		for(int i=0;i<m_RecordCount;i++)
		{
			x=m_pNameValue[i].m_x;
			y=(int)(rect.Height()-yper*m_pNameValue[i].m_value-2);
			pDC->LineTo(x,y);
			DrawPoint(pDC,x,y,m_LineColor);
		}
	}
	pDC->SelectObject(pOldPen);
	this->m_IsDrawn=true;
}

void CAnalyseDlg::OnCbnSelchangeComZk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->m_IsUpdated=false;
	this->Invalidate();
	this->m_MaxValue=0;
	this->m_StartDate=L"";
	this->m_EndDate=L"";
	((CComboBox*)(GetDlgItem(IDC_COM_ZK)))->GetWindowText(m_zk);
	UpdateData(false);
	UpdateData(true);
	((CComboBox*)(GetDlgItem(IDC_COM_DATA)))->SetCurSel(-1);
	//this->PostMessage(WM_ZKSELECTCHANGE);
}

LRESULT CAnalyseDlg::OnZkSelectChange(WPARAM wParam, LPARAM lParam)
{
	UpdateData(false);
	return 0;
}

CString CAnalyseDlg::CreateExcelFile()
{
	CFileDialog SaveDlg(false,L".xls",m_zk,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,L"Excel�ļ�|*.xls|�����ļ�|*.*|",NULL);
	if(SaveDlg.DoModal()==IDOK)
	{
		CString str=SaveDlg.GetPathName();
		CString strFileName=SaveDlg.GetFileName();
		int pos=str.ReverseFind('\\');
		CString strPos=str.Left(pos);
		CFileFind FileFind;
		if(FileFind.FindFile(L"ExcelTemp.xls"))
		{
			CString NewExcelFile=strPos+L"\\"+strFileName;
			if(!CopyFile(L"ExcelTemp.xls",NewExcelFile,false))
			{
				int errorId=::GetLastError();
				CString strMessage;
				strMessage.Format(L"����Excel�ļ�ʧ�ܣ�������룺%d",errorId);
				MessageBox(strMessage);
				return L"";
			}
			return NewExcelFile;
		}
		else
		{
			MessageBox(L"δ�ҵ�Excelģ���ļ���");
			return L"";
		}
	}
	else
	{
		return L"";
	}

}

void CAnalyseDlg::OnBnClickedBtnToExcel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	if(this->m_Data==L"")
		return;
	CString StartTime,EndTime;
	this->m_StartTimeCtrl.GetWindowTextW(StartTime);
	this->m_EndTimeCtrl.GetWindowTextW(EndTime);
	CSetTimeDlg SetTimeDlg(StartTime,EndTime);
	if(SetTimeDlg.DoModal()==IDOK)
	{
		StartTime=SetTimeDlg.m_strStartTime;
		EndTime=SetTimeDlg.m_strEndTime;
	}
	else
		return;

	CString ExcelFileName=CreateExcelFile();
	if(ExcelFileName==L"")
		return;

	CDatabase database;
	CString strDriver=L"Microsoft Excel Driver (*.xls)";
	CString strDsn;
	strDsn.Format(L"ODBC;DRIVER={%s};FIRSTROWHASNAMES=1;READONLY=FALSE;DBQ=%s",strDriver,ExcelFileName);
	if(database.Open(NULL,false,false,strDsn))
	{
		CString strSql4;
		strSql4.Format(L"SELECT [TIME],GAS,WATER FROM TB4 WHERE GCJIA='%s' AND [TIME] BETWEEN #%s# AND #%s#",m_zk,StartTime,EndTime);
		m_cmd.SetCommandText(strSql4);
		MRecordset rst;
		m_cmd.ExecuteQuery(CommandTypeEnum::adCmdText,rst);
		CString strValue[9];
		while(!rst.rstEOF())
		{
			MRecordset rstTemp;
			strValue[0]=rst.GetString((long)0);
			strValue[1]=rst.GetString((long)1);
			strValue[2]=rst.GetString((long)2);
			CString strSql1;
			strSql1.Format(L"SELECT CCI,DYM FROM TB1 WHERE GCJIA='%s' AND [TIME]=#%s#",m_zk,strValue[0]);
			m_cmd.SetCommandText(strSql1);
			m_cmd.ExecuteQuery(CommandTypeEnum::adCmdText,rstTemp);
			strValue[3]=rstTemp.GetString((long)0);
			strValue[4]=rstTemp.GetString((long)1);

			CString strSql2;
			strSql2.Format(L"SELECT TY FROM TB2 WHERE GCJIA='%s' AND [TIME]=#%s#",m_zk,strValue[0]);
			m_cmd.SetCommandText(strSql2);
			m_cmd.ExecuteQuery(CommandTypeEnum::adCmdText,rstTemp);
			strValue[5]=rstTemp.GetString((long)0);

			CString strSql3;
			strSql3.Format(L"SELECT [3MCDB],[15MCDB],JDLY FROM TB3 WHERE GCJIA='%s' AND [TIME]=#%s#",m_zk,strValue[0]);
			m_cmd.SetCommandText(strSql3);
			m_cmd.ExecuteQuery(CommandTypeEnum::adCmdText,rstTemp);
			strValue[6]=rstTemp.GetString((long)0);
			strValue[7]=rstTemp.GetString((long)1);
			strValue[8]=rstTemp.GetString((long)2);

			double gas=_wtof(strValue[1]);
			double water=_wtof(strValue[2]);
			double cc=_wtof(strValue[3]);
			double dym=_wtof(strValue[4]);
			double ty=_wtof(strValue[5]);
			double mcdb3=_wtof(strValue[6]);
			double mcdb15=_wtof(strValue[7]);
			double jdly=_wtof(strValue[8]);

			CString strExcelSql;
			strExcelSql.Format(L"INSERT INTO [�Ų�����$](ʱ��,[������(m3/d)],[��ˮ��(m3/d)],[���(n/min)],[��Һ��(m)],[��ѹ(Mpa)],[3ú�㶥��(m)],[15ú�㶥��(m)],[������ѹ(Mpa)]) VALUES('%s',%0.2lf,%0.2lf,%0.2lf,%0.2lf,%0.2lf,%0.2lf,%0.2lf,%0.2lf)",
				strValue[0],gas,water,cc,dym,ty,mcdb3,mcdb15,jdly);
			database.ExecuteSQL(strExcelSql);
			rst.MoveNext();
		}
	}
	else
	{
		MessageBox(L"��Excel����");
		return;
	}
	database.Close();
	if(MessageBox(L"������ɣ� �Ƿ�򿪣�",L"��ʾ",MB_YESNO)==IDYES)
	{
		::ShellExecute(this->m_hWnd,L"open",ExcelFileName,L"",L"",SW_NORMAL);
	}
}


void CAnalyseDlg::OnBnClickedBtnChangeLineStyle()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CChangeLineDlg dlg(this,this->m_LineType,this->m_LineWidth,this->m_LineColor);
	dlg.DoModal();
}


void CAnalyseDlg::OnBnClickedBtnUpdate()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strStartTime,strEndTime;
	this->m_StartTimeCtrl.GetWindowTextW(strStartTime);
	this->m_EndTimeCtrl.GetWindowTextW(strEndTime);
	MyFunction fun;
	if(fun.CompareTime(strStartTime,strEndTime)>=0)
	{
		MessageBox(L"����ʱ�����",L"��ʾ");
		CTime t=fun.CStringToCTime(this->m_EndDate);
		this->m_EndTimeCtrl.SetTime(&t);
		return;
	}


	this->m_IsUpdated=true;
	this->OnSelchangeComData();
}


void CAnalyseDlg::OnDtnDatetimechangeDatetimepicker1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CTime currentTime=CTime::GetCurrentTime();
	CString strStartTime;
	this->m_StartTimeCtrl.GetWindowTextW(strStartTime);
	MyFunction fun;
	CString strCurrentTime=fun.CTimeToCString(currentTime);
	if(fun.CompareTime(strStartTime,strCurrentTime)>=0)
	{
		this->SetTimer(2,300,0);
		CTime t=fun.CStringToCTime(this->m_StartDate);
		this->m_StartTimeCtrl.SetTime(&t);	
	}

	*pResult = 0;
}


void CAnalyseDlg::OnDtnDatetimechangeDatetimepicker2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}
