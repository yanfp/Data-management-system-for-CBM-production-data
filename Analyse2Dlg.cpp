// Analyse2Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Tool.h"
#include "Analyse2Dlg.h"
#include "afxdialogex.h"
#include <math.h>

double GetIntergerNumber(double a)
{
	int i=0;
	while(a/pow(10.0,i)>1)
	{
		i++;
	}
	int b=(int)(a/pow(10.0,i-2));
	return (b+1)*pow(10.0,i-2);
}

CString GetFieldFromCaption(CString str)
{
	if(str==L"累计排气量")
		return L"GASA";
	else
		return L"GAS";
}
// CAnalyse2Dlg 对话框

IMPLEMENT_DYNAMIC(CAnalyse2Dlg, CDialogEx)

CAnalyse2Dlg::CAnalyse2Dlg(CString str,CWnd* pParent /*=NULL*/)
	: CDialogEx(CAnalyse2Dlg::IDD, pParent)
{
	m_FilePath=str;
	m_NumberOfZk=0;
	m_MaxValueStr = _T("");
	m_pNames=NULL;
	m_zk = _T("");
	m_data = _T("");
	m_pZKValue=NULL;
	m_IsInited=false;
	//  m_ZKCount = 0;
	m_NumberOfZk = 0;
	m_CurrentIndex=0;

	m_BrushColor=RGB(255,0,0);
}

CAnalyse2Dlg::~CAnalyse2Dlg()
{
	if(m_pNames)
		delete [] m_pNames;
	if(m_pZKValue)
		delete [] m_pZKValue;
}

void CAnalyse2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_STATIC_MAX, m_MaxValueStr);
	DDX_CBString(pDX, IDC_COM_ZK, m_zk);
	DDX_CBString(pDX, IDC_COM_DATA, m_data);
	//  DDX_Text(pDX, IDC_EDIT_ZK_COUNT, m_ZKCount);
	DDX_Text(pDX, IDC_EDIT_ZK_COUNT, m_NumberOfZk);
	DDX_Control(pDX, IDC_COMBO2, m_CurrentDiaplayComBox);
	DDX_Control(pDX, IDC_STATIC_PIC, m_PicStatic);
}


BEGIN_MESSAGE_MAP(CAnalyse2Dlg, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COM_ZK, &CAnalyse2Dlg::OnCbnSelchangeComZk)
	ON_WM_TIMER()
	ON_WM_PAINT()
	ON_CBN_SELCHANGE(IDC_COMBO2, &CAnalyse2Dlg::OnCbnSelchangeCombo2)
	ON_CBN_SELCHANGE(IDC_COM_DATA, &CAnalyse2Dlg::OnCbnSelchangeComData)
END_MESSAGE_MAP()


// CAnalyse2Dlg 消息处理程序


BOOL CAnalyse2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  在此添加额外的初始化
	CComboBox* pComboBox=(CComboBox*)(GetDlgItem(IDC_COM_ZK));
	pComboBox->InsertString(-1,L"SN");
	pComboBox->InsertString(-1,L"TS");
	pComboBox->InsertString(-1,L"SX");
	pComboBox->InsertString(-1,L"ZY");
	pComboBox->SelectString(0,L"SX");
	CComboBox* pComboBox2=(CComboBox*)(GetDlgItem(IDC_COM_DATA));
	pComboBox2->InsertString(-1,L"排气量");
	pComboBox2->InsertString(-1,L"累计排气量");
	pComboBox2->SelectString(-1,L"排气量");
	UpdateData(true);

	CString strConnection;
	strConnection.Format(L"Provider=Microsoft.Jet.OLEDB.4.0;Data Source=%s;",m_FilePath);
	m_conn.SetConnectionString(strConnection);
	if(m_conn.Open(L"",L"",L"",ConnectOption::adConnectUnspecified))
	{
		m_cmd.SetActiveConnection(m_conn);
		CString strSql=L"SELECT DISTINCT GCJIA FROM TB4 WHERE GCJIA LIKE '"+m_zk+L"\%'";
		//strSql.Format(L"SELECT DISTINCT GCJIA FROM TB4 WHERE GCJIA LIKE '%s-\%'",m_zk);
		m_cmd.SetCommandText(strSql);
		MRecordset rst;
		if(!m_cmd.ExecuteQuery(CommandTypeEnum::adCmdText,rst))
		{
			MessageBox(L"查询错误！",L"提示");
			return TRUE;
		}
		
		m_NumberOfZk=rst.GetRecordCount();
		m_pNames=new CString[m_NumberOfZk];
		int i=0;
		while(!rst.rstEOF())
		{
			m_pNames[i++]=rst.GetString((long)0);
			rst.MoveNext();
		}
	}
	Zk_Value* pZKValue=this->CalculateGasProOfEveryZk();
	this->DrawHistogram(m_NumberOfZk,pZKValue);


	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CAnalyse2Dlg::DrawHistogram(int NumberOfZk,Zk_Value *pZV)
{
	int NumberOfFifty=NumberOfZk/50;
	int last=NumberOfZk%50;
	int dispalyNumber=NumberOfZk<50?NumberOfZk:50;
	if(NumberOfFifty==m_CurrentIndex)
		dispalyNumber=last;
	Zk_Value zkvalue[50];
	for(int a=0;a<dispalyNumber;a++)
	{
		zkvalue[a].m_ZkName=pZV[m_CurrentIndex*50+a].m_ZkName;
		zkvalue[a].m_Value=pZV[m_CurrentIndex*50+a].m_Value;
	}
	double Max=zkvalue[0].m_Value;
	for(int k=0;k<dispalyNumber;k++)
	{
		Max=zkvalue[k].m_Value>Max?zkvalue[k].m_Value:Max;
	}

	CDC* pDC=this->GetPicDC();
	CPen pen(0,0,RGB(0,0,0));
	CBrush brush(m_BrushColor);
	CFont font;
	font.CreatePointFont(70,L"Arial");
	CPen *pOldPen=pDC->SelectObject(&pen);
	CBrush *pOldBrush=pDC->SelectObject(&brush);
	CFont *pOldFont=pDC->SelectObject(&font);
	pDC->SetBkMode(TRANSPARENT);
	/***************画柱状图********************/
	CRect PicRect=this->GetPicRect();
	int Width=PicRect.Width();
	int Height=PicRect.Height();
	double yPer=(Height-10)/(dispalyNumber-1);
	double m=GetIntergerNumber(Max);
	m_MaxValueStr.Format(L"%0.0lf m^3",m);
	double xPer=(Width-10)/m;
	for(int i=0;i<dispalyNumber;i++)
	{
		int x=(int)(xPer*zkvalue[i].m_Value);
		int y=(int)(yPer*i);
		CRect rect(0,y,x,y+10);
		pDC->Rectangle(rect);
		CString strValue;
		strValue.Format(L"%0.2lf",pZV[i].m_Value);
		//pDC->TextOut(x,y-15,strValue);
		pDC->TextOut(x,y,zkvalue[i].m_ZkName);
	}
	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBrush);
	pDC->SelectObject(pOldFont);
	UpdateData(false);
	
}

void CAnalyse2Dlg::DrawNameText(int NumberOfZk,Zk_Value *pZV)
{
	
}

CRect CAnalyse2Dlg::GetPicRect()
{
	CRect r;
	GetDlgItem(IDC_STATIC_PIC)->GetWindowRect(r);
	this->ScreenToClient(r);
	return r;
}

CRect CAnalyse2Dlg::GetNameRect()
{
	CRect r;
	//GetDlgItem(IDC_STATIC_NAME)->GetWindowRect(r);
	this->ScreenToClient(r);
	return r;
}

CDC* CAnalyse2Dlg::GetPicDC()
{
	return GetDlgItem(IDC_STATIC_PIC)->GetDC();
}

Zk_Value* CAnalyse2Dlg::CalculateGasProOfEveryZk()
{
	Zk_Value *pData=new Zk_Value[m_NumberOfZk];
	CString strSql;
	if(this->m_data==L"排气量")
	{
		m_BrushColor=RGB(255,0,0);
		for(int i=0;i<m_NumberOfZk;i++)
		{	
			strSql.Format(L"SELECT AVG(GAS) FROM TB4 WHERE GCJIA='%s'",m_pNames[i]);
			m_cmd.SetCommandText(strSql);
			MRecordset rst;
			m_cmd.ExecuteQuery(CommandTypeEnum::adCmdText,rst);
			pData[i].m_ZkName=m_pNames[i];
			double value=_wtof(rst.GetString((long)0));
			pData[i].m_Value=value;
		}
	}
	if(this->m_data==L"累计排气量")
	{
		m_BrushColor=RGB(0,0,255);
		for(int i=0;i<m_NumberOfZk;i++)
		{
			CString strSql;
			strSql.Format(L"SELECT TOP 1 GASA FROM TB4 WHERE GCJIA='%s' ORDER BY [TIME] DESC",m_pNames[i]);
			m_cmd.SetCommandText(strSql);
			MRecordset rst;
			m_cmd.ExecuteQuery(CommandTypeEnum::adCmdText,rst);
			pData[i].m_ZkName=m_pNames[i];
			double value=_wtof(rst.GetString((long)0));
			pData[i].m_Value=value;
		}
	}
	this->m_pZKValue=pData;
	return pData;
}

void CAnalyse2Dlg::GetNamesOfZks()
{
	UpdateData(true);
	if(m_pNames)
	{
		delete [] m_pNames;
	}
	CString strSql;
	strSql=L"SELECT DISTINCT GCJIA FROM TB4 WHERE GCJIA LIKE '"+m_zk+L"\%'";
	m_cmd.SetCommandText(strSql);
	m_cmd.ExecuteQuery(CommandTypeEnum::adCmdText,m_rst);


	m_NumberOfZk=m_rst.GetRecordCount();
	m_pNames=new CString[m_NumberOfZk];
	int i=0;
	MRecordset rstTemp;
	while(!m_rst.rstEOF())
	{
		CString Sql;
		Sql.Format(L"SELECT AVG(%s) FROM TB4 WHERE GCJIA='%s' AND GAS>0",GetFieldFromCaption(m_data),m_rst.GetString(0));
		m_cmd.SetCommandText(Sql);
		m_cmd.ExecuteQuery(CommandTypeEnum::adCmdText,rstTemp);
		CString strAvg=rstTemp.GetString(0);
		double avg=_wtof(strAvg);
		if(avg>0)
		{
			m_pNames[i++]=m_rst.GetString(0);
		}
		m_rst.MoveNext();
	}
	m_NumberOfZk=i;
}

void CAnalyse2Dlg::OnCbnSelchangeComZk()
{
	// TODO: 在此添加控件通知处理程序代码
	
	this->Invalidate();
	this->GetNamesOfZks();
	this->SetDisplayFun(this->m_NumberOfZk);
	this->m_CurrentDiaplayComBox.SetCurSel(0);m_CurrentIndex=0;
	this->SetTimer(1,300,0);
	
}

void CAnalyse2Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(nIDEvent==1)
	{
		this->DrawHistogram(this->m_NumberOfZk,CalculateGasProOfEveryZk());
		KillTimer(1);
	}
	CDialogEx::OnTimer(nIDEvent);
}

void CAnalyse2Dlg::SetDisplayFun(int num)
{	
	this->m_CurrentDiaplayComBox.ResetContent();
	int arrayNum=num/50;
	int i=0;
	for(i=0;i<arrayNum;i++)
	{
		CString str;
		str.Format(L"%d~%d",i*50+1,(i+1)*50);
		this->m_CurrentDiaplayComBox.InsertString(-1,str);
	}
	if(num>i*50)
	{
		CString str2;
		str2.Format(L"%d~%d",i*50+1,num);
		this->m_CurrentDiaplayComBox.InsertString(-1,str2);
	}
}

void CAnalyse2Dlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
	if(!this->m_IsInited)
	{
		this->OnCbnSelchangeComZk();
		this->m_IsInited=true;
	}
}

void CAnalyse2Dlg::OnCbnSelchangeCombo2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_CurrentIndex=this->m_CurrentDiaplayComBox.GetCurSel();
	this->Invalidate();
	this->SetTimer(1,300,0);
}

void CAnalyse2Dlg::OnCbnSelchangeComData()
{
	// TODO: 在此添加控件通知处理程序代码((
	UpdateData(true);
}
