// AnalyseDlg.cpp : 实现文件
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
	/*CString str[22]={L"泵径",L"冲程",L"冲次",L"理论排量",L"泵效",L"动液面",L"氯离子",L"PH",L"含沙",
		L"最高温度",L"最低温度",L"油嘴",L"套压",L"3#煤层顶板",L"15#煤层顶板",L"泵挂位置",L"筛管位置",
		L"井底流压",L"产水量",L"累计产水量",L"排气量",L"累计排气量"};*/
	if(str==L"泵径")
		return L"BJ";
	if(str==L"冲程")
		return L"CCH";
	if(str==L"冲次")
		return L"CCI";
	if(str==L"理论排量")
		return L"LLPL";
	if(str==L"泵效")
		return L"BX";
	if(str==L"动液面")
		return L"DYM";
	if(str==L"氯离子")
		return L"CL";
	if(str==L"PH")
		return L"PH";
	if(str==L"含沙")
		return L"SAND";
	if(str==L"最高温度")
		return L"MAXTEM";
	if(str==L"最低温度")
		return L"MINTEM";
	if(str==L"油嘴")
		return L"YZ";
	if(str==L"套压")
		return L"TY";
	if(str==L"3#煤层顶板")
		return L"[3MCDB]";
	if(str==L"15#煤层顶板")
		return L"[15MCDB]";
	if(str==L"泵挂位置")
		return L"BGWZ";
	if(str==L"筛管位置")
		return L"SGWZ";
	if(str==L"井底流压")
		return L"JDLY";
	if(str==L"产水量")
		return L"WATER";
	if(str==L"累计产水量")
		return L"WATERA";
	if(str==L"排气量")
		return L"GAS";
	if(str==L"累计排气量")
		return L"GASA";
}

CString GetTableNameFromCaption(CString str)
{
	if(str==L"泵径"||str==L"冲程"||str==L"冲次"||str==L"理论排量"||str==L"泵效"||str==L"动液面")
		return L"TB1";
	
	if(str==L"氯离子"||str==L"PH"||str==L"含沙"||str==L"最高温度"||str==L"最低温度"||str==L"油嘴"||str==L"套压")
		return L"TB2";
	
	if(str==L"3#煤层顶板"||str==L"15#煤层顶板"||str==L"泵挂位置"||str==L"筛管位置"||str==L"井底流压")
		return L"TB3";
	
	if(str==L"产水量"||str==L"累计产水量"||str==L"排气量"||str==L"累计排气量")
		return L"TB4";
	

}

/*******************************************/

// CAnalyseDlg 对话框
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

// CAnalyseDlg 消息处理程序


BOOL CAnalyseDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
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
			AfxMessageBox(L"打开数据库失败！");
		}
		
	}
	catch(_com_error e)
	{
		CString errormessage;
		errormessage.Format(L"读取失败!\r\n错误信息:%s",e.ErrorMessage());
		AfxMessageBox(errormessage);///显示错误信息
	}
	CString str[19]={L"泵径",L"冲程",L"冲次",L"理论排量",L"泵效",L"动液面",L"氯离子",L"PH",
		L"最高温度",L"最低温度",L"套压",L"3#煤层顶板",L"15#煤层顶板",L"筛管位置",
		L"井底流压",L"产水量",L"累计产水量",L"排气量",L"累计排气量"};
	for(int i=0;i<19;i++)
	{
		((CComboBox*)GetDlgItem(IDC_COM_DATA))->InsertString(-1,str[i]);
	}
	this->CreateToolTip();//创建提示
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CAnalyseDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	
	this->Invalidate();
	CDC* pDC=this->GetDC();
	pDC->MoveTo(0,0);
	pDC->LineTo(100,100);
	CDialogEx::OnRButtonDown(nFlags, point);
}

void CAnalyseDlg::OnSelchangeComData()
{
	// TODO: 在此添加控件通知处理程序代码
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
		errormessage.Format(L"读取数据错误!\r\n错误信息:%s",e.ErrorMessage());
		AfxMessageBox(errormessage);///显示错误信息
	}
	UpdateData(false);
}

double CAnalyseDlg::GetMaxValue(CString str)
{
	
	if(str==L"含沙")
		return 0.0;
	CString sObj=GetNameFromCaption(str);
	CString sTable=GetTableNameFromCaption(m_Data);
	//取最大值
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
	//取第一条记录日期
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
	//取最后一天记录日期
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
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
	if(!m_IsInited)
	{
		MRecordset rst;
		m_cmd.SetCommandText(L"SELECT TOP 1 GCJIA FROM TB4 WHERE GAS>0");
		m_cmd.ExecuteQuery(CommandTypeEnum::adCmdText,rst);
		this->m_zk=rst.GetString((long)0);
		((CComboBox*)GetDlgItem(IDC_COM_DATA))->SelectString(-1,L"排气量");
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
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(nIDEvent==1)
	{
		this->PostMessage(WM_DRAWLINE);
		KillTimer(1);
	}
	if(nIDEvent==2)
	{
		KillTimer(2);
		MessageBox(L"起始时间设置错误!",L"提示");
		
	}
	CDialogEx::OnTimer(nIDEvent);
}

void CAnalyseDlg::CreateToolTip()
{
	m_ToolTip.Create(this);  
	m_ToolTip.AddTool(GetDlgItem(IDC_STATIC_PIC),L"绘图区域" ); //IDC_BUTTON为你要添加提示信息的按钮的ID
	m_ToolTip.SetDelayTime(200); //设置延迟
	m_ToolTip.SetTipTextColor(RGB(0,0,255) ); //设置提示文本的颜色
	m_ToolTip.SetTipBkColor( RGB(255,255,255)); //设置提示框的背景颜色
	m_ToolTip.Activate(TRUE); //设置是否启用提示

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
		errormessage.Format(L"读取数据错误!\r\n错误信息:%s",e.ErrorMessage());
		AfxMessageBox(errormessage);///显示错误信息
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
	// TODO: 在此添加控件通知处理程序代码
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
	CFileDialog SaveDlg(false,L".xls",m_zk,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,L"Excel文件|*.xls|所有文件|*.*|",NULL);
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
				strMessage.Format(L"创建Excel文件失败！错误代码：%d",errorId);
				MessageBox(strMessage);
				return L"";
			}
			return NewExcelFile;
		}
		else
		{
			MessageBox(L"未找到Excel模板文件！");
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
	// TODO: 在此添加控件通知处理程序代码
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
			strExcelSql.Format(L"INSERT INTO [排采数据$](时间,[产气量(m3/d)],[产水量(m3/d)],[冲次(n/min)],[动液面(m)],[套压(Mpa)],[3煤层顶板(m)],[15煤层顶板(m)],[井底流压(Mpa)]) VALUES('%s',%0.2lf,%0.2lf,%0.2lf,%0.2lf,%0.2lf,%0.2lf,%0.2lf,%0.2lf)",
				strValue[0],gas,water,cc,dym,ty,mcdb3,mcdb15,jdly);
			database.ExecuteSQL(strExcelSql);
			rst.MoveNext();
		}
	}
	else
	{
		MessageBox(L"打开Excel错误！");
		return;
	}
	database.Close();
	if(MessageBox(L"导出完成！ 是否打开？",L"提示",MB_YESNO)==IDYES)
	{
		::ShellExecute(this->m_hWnd,L"open",ExcelFileName,L"",L"",SW_NORMAL);
	}
}


void CAnalyseDlg::OnBnClickedBtnChangeLineStyle()
{
	// TODO: 在此添加控件通知处理程序代码
	CChangeLineDlg dlg(this,this->m_LineType,this->m_LineWidth,this->m_LineColor);
	dlg.DoModal();
}


void CAnalyseDlg::OnBnClickedBtnUpdate()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strStartTime,strEndTime;
	this->m_StartTimeCtrl.GetWindowTextW(strStartTime);
	this->m_EndTimeCtrl.GetWindowTextW(strEndTime);
	MyFunction fun;
	if(fun.CompareTime(strStartTime,strEndTime)>=0)
	{
		MessageBox(L"设置时间错误！",L"提示");
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
	// TODO: 在此添加控件通知处理程序代码
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
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}
