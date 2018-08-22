// DataManageDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Tool.h"
#include "DataManageDlg.h"
#include "afxdialogex.h"

#define WM_SELECT_ZK WM_USER + 1

CString GetYear(CString str)
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
	return strYear;
}

CString GetMouth(CString str)
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
	return strMouth;
}

CString GetDay(CString str)
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
	return strDay;
}
// CDataManageDlg 对话框
CString _sql(CString str)
{
	if(str.IsEmpty())
		return L"NULL";
	else
		return L"'"+str+L"'";
}

IMPLEMENT_DYNAMIC(CDataManageDlg, CDialogEx)

CDataManageDlg::CDataManageDlg(CString str,CWnd* pParent /*=NULL*/)
	: CDialogEx(CDataManageDlg::IDD, pParent)
{
	m_FilePath=str;
	m_edt1 = _T("");
	m_edt12 = _T("");
	m_edt10 = _T("");
	m_edt11 = _T("");
	m_edt13 = _T("");
	m_edt14 = _T("");
	m_edt15 = _T("");
	m_edt16 = _T("");
	m_edt17 = _T("");
	m_edt18 = _T("");
	m_edt19 = _T("");
	m_edt2 = _T("");
	m_edt21 = _T("");
	m_edt3 = _T("");
	m_edt4 = _T("");
	m_edt5 = _T("");
	m_edt6 = _T("");
	m_edt7 = _T("");
	m_edt8 = _T("");
	m_edt9 = _T("");
	m_edtx = _T("");
	m_edty = _T("");
	m_edtz = _T("");
	m_edtday =1;
	m_edt20 = _T("");
	m_edtdepth = _T("");
	m_edtzk = _T("");
	m_edtyear = _T("");
	m_edtmouth = _T("");
	m_edt22 = _T("");
	m_edtday = 1;
	m_IsConnected=false;
	m_IsEditable=false;
}

CDataManageDlg::~CDataManageDlg()
{
}

void CDataManageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDT_1, m_edt1);

	DDX_Text(pDX, IDC_EDT_12, m_edt12);
	DDX_Text(pDX, IDC_EDT_10, m_edt10);
	DDX_Text(pDX, IDC_EDT_11, m_edt11);
	DDX_Text(pDX, IDC_EDT_13, m_edt13);
	DDX_Text(pDX, IDC_EDT_14, m_edt14);
	DDX_Text(pDX, IDC_EDT_15, m_edt15);
	DDX_Text(pDX, IDC_EDT_16, m_edt16);
	DDX_Text(pDX, IDC_EDT_17, m_edt17);
	DDX_Text(pDX, IDC_EDT_18, m_edt18);
	DDX_Text(pDX, IDC_EDT_19, m_edt19);
	DDX_Text(pDX, IDC_EDT_2, m_edt2);
	//  DDX_Control(pDX, IDC_EDT_20, m_edt20);
	DDX_Text(pDX, IDC_EDT_21, m_edt21);
	DDX_Text(pDX, IDC_EDT_3, m_edt3);
	DDX_Text(pDX, IDC_EDT_4, m_edt4);
	DDX_Text(pDX, IDC_EDT_5, m_edt5);
	DDX_Text(pDX, IDC_EDT_6, m_edt6);
	//  DDX_Control(pDX, IDC_EDT_7, m_edt7);
	DDX_Text(pDX, IDC_EDT_7, m_edt7);
	DDX_Text(pDX, IDC_EDT_8, m_edt8);
	DDX_Text(pDX, IDC_EDT_9, m_edt9);
	DDX_Text(pDX, IDC_EDIT_X, m_edtx);
	DDX_Text(pDX, IDC_EDIT_Y, m_edty);
	DDX_Text(pDX, IDC_EDIT_Z, m_edtz);
	//  DDX_Control(pDX, IDC_EDT_DAY, m_edtday);
	//  DDX_Text(pDX, IDC_EDT_DAY, m_edtday);
	DDX_Text(pDX, IDC_EDT_20, m_edt20);
	DDX_Text(pDX, IDC_EDIT_H, m_edtdepth);
	DDX_CBString(pDX, IDC_COM_ZK, m_edtzk);
	DDX_CBString(pDX, IDC_COMYEAR, m_edtyear);
	DDX_CBString(pDX, IDC_COM_MOUTH, m_edtmouth);
	DDX_Text(pDX, IDC_EDT_22, m_edt22);
	DDX_Control(pDX, IDC_SPIN1, m_spin1);
	DDX_Text(pDX, IDC_EDT_DAY, m_edtday);
	DDV_MinMaxInt(pDX, m_edtday, 1, 31);
}


BEGIN_MESSAGE_MAP(CDataManageDlg, CDialogEx)
	ON_WM_RBUTTONDOWN()
	ON_BN_CLICKED(IDC_BTN_FIND, &CDataManageDlg::OnBnClickedBtnFind)
	ON_CBN_SELCHANGE(IDC_COM_ZK, &CDataManageDlg::OnCbnSelchangeComZk)
	ON_CBN_SELCHANGE(IDC_COMYEAR, &CDataManageDlg::OnCbnSelchangeComyear)
	ON_CBN_SELCHANGE(IDC_COM_MOUTH, &CDataManageDlg::OnCbnSelchangeComMouth)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, &CDataManageDlg::OnDeltaposSpin1)
	ON_BN_CLICKED(IDC_BTN_MODIFY, &CDataManageDlg::OnBnClickedBtnModify)
	ON_BN_CLICKED(IDC_BTN_SAVE, &CDataManageDlg::OnBnClickedBtnSave)
	ON_BN_CLICKED(IDC_BTN_DELETE, &CDataManageDlg::OnBnClickedBtnDelete)
	ON_MESSAGE(WM_SELECT_ZK,OnSelectZk)
	ON_BN_CLICKED(IDC_BTN_NEXT, &CDataManageDlg::OnBnClickedBtnNext)
END_MESSAGE_MAP()


// CDataManageDlg 消息处理程序


BOOL CDataManageDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	((CComboBox*)(GetDlgItem(IDC_COMYEAR)))->AddString(L"2010");
	((CComboBox*)(GetDlgItem(IDC_COMYEAR)))->AddString(L"2011");
	((CComboBox*)(GetDlgItem(IDC_COMYEAR)))->AddString(L"2012");
	((CComboBox*)(GetDlgItem(IDC_COMYEAR)))->AddString(L"2013");
	((CComboBox*)(GetDlgItem(IDC_COMYEAR)))->AddString(L"2014");
	((CComboBox*)(GetDlgItem(IDC_COMYEAR)))->AddString(L"2015");
	for(int i=0;i<12;i++)
	{
		CString strMouth;
		strMouth.Format(L"%d",i+1);
		((CComboBox*)(GetDlgItem(IDC_COM_MOUTH)))->InsertString(-1,strMouth);
	}
	((CComboBox*)(GetDlgItem(IDC_COM_MOUTH)))->SetCurSel(4);
	// TODO:  在此添加额外的初始化
	try
	{
		CString strConnection;
		strConnection.Format(L"Provider=Microsoft.Jet.OLEDB.4.0;Data Source=%s;",this->m_FilePath);
		m_conn.SetConnectionString(strConnection);
		if(m_conn.Open(L"",L"",L"",ConnectOption::adConnectUnspecified))
		{
			m_IsConnected=true;
			m_cmd.SetActiveConnection(m_conn);
			m_cmd.SetCommandText(L"SELECT DISTINCT GCJIA FROM TB1");
			m_cmd.ExecuteQuery(CommandTypeEnum::adCmdText,m_rst);
			while(!m_rst.rstEOF())
			{
				CString str=m_rst.GetString(0);
				((CComboBox*)(GetDlgItem(IDC_COM_ZK)))->InsertString(-1,str);
				m_rst.MoveNext();
			}
			((CComboBox*)(GetDlgItem(IDC_COM_ZK)))->SetCurSel(0);
			this->SetFirstDateByZk();
			this->SetZkInfo();
		}
		else
		{
			AfxMessageBox(L"打开数据库失败！");
		}
		
	}
	catch(_com_error e)
	{
		CString errormessage;
		errormessage.Format(L"连接数据库失败!\r\n错误信息:%s",e.ErrorMessage());
		AfxMessageBox(errormessage);///显示错误信息
	}

	
	m_spin1.SetBuddy(GetDlgItem(IDC_EDT_DAY));
	m_spin1.SetRange(1,30);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDataManageDlg::SetEdtState(BOOL b)
{
	((CEdit*)(GetDlgItem(IDC_EDT_1)))->SetReadOnly(b);
	((CEdit*)(GetDlgItem(IDC_EDT_2)))->SetReadOnly(b);
	((CEdit*)(GetDlgItem(IDC_EDT_3)))->SetReadOnly(b);
	((CEdit*)(GetDlgItem(IDC_EDT_4)))->SetReadOnly(b);
	((CEdit*)(GetDlgItem(IDC_EDT_5)))->SetReadOnly(b);
	((CEdit*)(GetDlgItem(IDC_EDT_6)))->SetReadOnly(b);
	((CEdit*)(GetDlgItem(IDC_EDT_7)))->SetReadOnly(b);
	((CEdit*)(GetDlgItem(IDC_EDT_8)))->SetReadOnly(b);
	((CEdit*)(GetDlgItem(IDC_EDT_9)))->SetReadOnly(b);
	((CEdit*)(GetDlgItem(IDC_EDT_10)))->SetReadOnly(b);
	((CEdit*)(GetDlgItem(IDC_EDT_11)))->SetReadOnly(b);
	((CEdit*)(GetDlgItem(IDC_EDT_12)))->SetReadOnly(b);
	((CEdit*)(GetDlgItem(IDC_EDT_13)))->SetReadOnly(b);
	((CEdit*)(GetDlgItem(IDC_EDT_14)))->SetReadOnly(b);
	((CEdit*)(GetDlgItem(IDC_EDT_15)))->SetReadOnly(b);
	((CEdit*)(GetDlgItem(IDC_EDT_16)))->SetReadOnly(b);
	((CEdit*)(GetDlgItem(IDC_EDT_17)))->SetReadOnly(b);
	((CEdit*)(GetDlgItem(IDC_EDT_18)))->SetReadOnly(b);
	((CEdit*)(GetDlgItem(IDC_EDT_19)))->SetReadOnly(b);
	((CEdit*)(GetDlgItem(IDC_EDT_20)))->SetReadOnly(b);
	((CEdit*)(GetDlgItem(IDC_EDT_21)))->SetReadOnly(b);
	((CEdit*)(GetDlgItem(IDC_EDT_22)))->SetReadOnly(b);
	this->m_IsEditable=!b;
}

void CDataManageDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//this->SetEdtState(0);
	CDialogEx::OnRButtonDown(nFlags, point);
}

void CDataManageDlg::OnBnClickedBtnFind()
{
	// TODO: 在此添加控件通知处理程序代码

	UpdateData(true);
	if(m_edtzk.IsEmpty() || m_edtyear.IsEmpty() || m_edtmouth.IsEmpty())
	{
		AfxMessageBox(L"请选择钻孔编号和日期！");
		return;
	}
	
	CString strSql[4];
	CString strTime;
	strTime.Format(L"%s/%s/%d",m_edtyear,m_edtmouth,m_edtday);
	strSql[0].Format(L"SELECT BJ,CCH,CCI,LLPL,BX,DYM FROM TB1 WHERE GCJIA='%s' AND [TIME]=#%s#",m_edtzk,strTime);
	strSql[1].Format(L"SELECT CL,PH,SAND,MAXTEM,MINTEM,YZ,TY FROM TB2 WHERE GCJIA='%s' AND [TIME]=#%s#",m_edtzk,strTime);
	strSql[2].Format(L"SELECT [3MCDB],[15MCDB],BGWZ,SGWZ,JDLY FROM TB3 WHERE GCJIA='%s' AND [TIME]=#%s#",m_edtzk,strTime);
	strSql[3].Format(L"SELECT WATER,WATERA,GAS,GASA FROM TB4 WHERE GCJIA='%s' AND [TIME]=#%s#",m_edtzk,strTime);

	CString strValue[22];
	try
	{
		m_cmd.SetCommandText(strSql[0]);
		m_cmd.ExecuteQuery(CommandTypeEnum::adCmdText,m_rst);
		int i=0;
		for(i=0;i<6;i++)
			strValue[i]=m_rst.GetString(i);

		m_cmd.SetCommandText(strSql[1]);
		m_cmd.ExecuteQuery(CommandTypeEnum::adCmdText,m_rst);
		for(i=0;i<7;i++)
			strValue[i+6]=m_rst.GetString(i);

		m_cmd.SetCommandText(strSql[2]);
		m_cmd.ExecuteQuery(CommandTypeEnum::adCmdText,m_rst);
		for(i=0;i<5;i++)
			strValue[i+13]=m_rst.GetString(i);

		m_cmd.SetCommandText(strSql[3]);
		m_cmd.ExecuteQuery(CommandTypeEnum::adCmdText,m_rst);
		for(i=0;i<4;i++)
			strValue[i+18]=m_rst.GetString(i);
	}
	catch(_com_error e)
	{
		CString errorMessage;
		errorMessage.Format(L"读取数据错误!\r\n错误信息:%s",e.ErrorMessage());
		MessageBox(L"查询错误！没有当日的数据记录。",L"提示");
		CString strNull[22];
		this->SetValue(strNull,22);
		UpdateData(false);
		return;
	}
	this->SetValue(strValue,22);
	UpdateData(false);
	this->SetEdtState(1);
}

void CDataManageDlg::SetValue(CString *pStr,int num)
{
	m_edt1=pStr[0];
	m_edt2=pStr[1];
	m_edt3=pStr[2];
	m_edt4=pStr[3];
	m_edt5=pStr[4];
	m_edt6=pStr[5];
	m_edt7=pStr[6];
	m_edt8=pStr[7];
	m_edt9=pStr[8];
	m_edt10=pStr[9];
	m_edt11=pStr[10];
	m_edt12=pStr[11];
	m_edt13=pStr[12];
	m_edt14=pStr[13];
	m_edt15=pStr[14];
	m_edt16=pStr[15];
	m_edt17=pStr[16];
	m_edt18=pStr[17];
	m_edt19=pStr[18];
	m_edt20=pStr[19];
	m_edt21=pStr[20];
	m_edt22=pStr[21];
}

void CDataManageDlg::OnCbnSelchangeComZk()
{
	// TODO: 在此添加控件通知处理程序代码
	this->PostMessage(WM_SELECT_ZK);
}

void CDataManageDlg::OnCbnSelchangeComyear()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	((CComboBox*)GetDlgItem(IDC_COMYEAR))->GetWindowText(str);
}

void CDataManageDlg::OnCbnSelchangeComMouth()
{
	// TODO: 在此添加控件通知处理程序代码
	
}

void CDataManageDlg::OnDeltaposSpin1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	if(pNMUpDown->iDelta == -1) // 如果此值为-1 , 说明点击了Spin的往下的箭头
	{
		m_edtday--;
	}
	else if(pNMUpDown->iDelta == 1) // 如果此值为1, 说明点击了Spin的往上的箭头
	{
		m_edtday++;
	}
	if(m_edtday<1)
		m_edtday=31;
	if( m_edtday>31)
		m_edtday=1;
	UpdateData(false);
	*pResult = 0;
}

void CDataManageDlg::OnBnClickedBtnModify()
{
	// TODO: 在此添加控件通知处理程序代码
	this->SetEdtState(0);
}

void CDataManageDlg::OnBnClickedBtnSave()
{
	// TODO: 在此添加控件通知处理程序代码
	if(!this->m_IsEditable)
		return;

	UpdateData(true);
	CString strSql[4];
	CString strTime;
	strTime.Format(L"%s/%s/%d",m_edtyear,m_edtmouth,m_edtday);
	strSql[0].Format(L"UPDATE TB1 SET BJ=%s,CCH=%s,CCI=%s,LLPL=%s,BX=%s,DYM=%s WHERE GCJIA='%s' AND [TIME]=#%s#",
		_sql(m_edt1),_sql(m_edt2),_sql(m_edt3),_sql(m_edt4),_sql(m_edt5),_sql(m_edt6),m_edtzk,strTime);
	strSql[1].Format(L"UPDATE TB2 SET CL=%s,PH=%s,SAND=%s,MAXTEM=%s,MINTEM=%s,YZ=%s,TY=%s WHERE GCJIA='%s' AND [TIME]=#%s#",
		_sql(m_edt7),_sql(m_edt8),_sql(m_edt9),_sql(m_edt10),_sql(m_edt11),_sql(m_edt12),_sql(m_edt13),m_edtzk,strTime);
	strSql[2].Format(L"UPDATE TB3 SET [3MCDB]=%s,[15MCDB]=%s,BGWZ=%s,SGWZ=%s,JDLY=%s WHERE GCJIA='%s' AND [TIME]=#%s#",
		_sql(m_edt14),_sql(m_edt15),_sql(m_edt16),_sql(m_edt17),_sql(m_edt18),m_edtzk,strTime);
	strSql[3].Format(L"UPDATE TB4 SET WATER=%s,WATERA=%s,GAS=%s,GASA=%s WHERE GCJIA='%s' AND [TIME]=#%s#",
		_sql(m_edt19),_sql(m_edt20),_sql(m_edt21),_sql(m_edt22),m_edtzk,strTime);
	try
	{
		m_cmd.SetCommandText(strSql[0]);
		m_cmd.ExecuteQuery(CommandTypeEnum::adCmdText,m_rst);
		
		m_cmd.SetCommandText(strSql[1]);
		m_cmd.ExecuteQuery(CommandTypeEnum::adCmdText,m_rst);
		
		m_cmd.SetCommandText(strSql[2]);
		m_cmd.ExecuteQuery(CommandTypeEnum::adCmdText,m_rst);
		
		m_cmd.SetCommandText(strSql[3]);
		m_cmd.ExecuteQuery(CommandTypeEnum::adCmdText,m_rst);

		AfxMessageBox(L"保存成功！");
		this->SetEdtState(1);
	}
	catch(_com_error e)
	{
		CString errormessage;
		errormessage.Format(L"保存数据失败!\r\n错误信息:%s",e.ErrorMessage());
		AfxMessageBox(errormessage);///显示错误信息
	}
}

void CDataManageDlg::OnBnClickedBtnDelete()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strTime;
	strTime.Format(L"%s/%s/%d",m_edtyear,m_edtmouth,m_edtday);
	CString strSql;
	for(int i=0;i<4;i++)
	{
		strSql.Format(L"DELETE FROM TB%d WHERE GCJIA='%s' AND [TIME]=#%s#",i+1,m_edtzk,strTime);
		m_cmd.SetCommandText(strSql);
		MRecordset rst;
		long rows=0;
		int flag=m_cmd.ExecuteUpdate(rows,CommandTypeEnum::adCmdText,rst);
	}
	CString strNull[22];
	this->SetValue(strNull,22);
	UpdateData(false);
	CString strMsg;
	strMsg.Format(L"日期:%s,钻井:%s\r\n记录已删除！",strTime,m_edtzk);
	MessageBox(strMsg,L"提示",MB_ICONEXCLAMATION);
}

LRESULT CDataManageDlg::OnSelectZk(WPARAM wParam, LPARAM lParam)
{
	this->SetFirstDateByZk();
	this->SetZkInfo();
	return 0;
}

void CDataManageDlg::SetZkInfo()
{
	CString strSql;
	strSql.Format(L"SELECT ZKX,ZKY,ZKZ,ZKDEP FROM ZKTB1 WHERE GCJIA='%s'",m_edtzk);
	MRecordset rst;
	m_cmd.SetCommandText(strSql);
	m_cmd.ExecuteQuery(CommandTypeEnum::adCmdText,rst);
	int recordcount=rst.GetRecordCount();
	if(recordcount)
	{
		m_edtx=rst.GetString(0);
		m_edty=rst.GetString(1);
		m_edtz=rst.GetString(2);
		m_edtdepth=rst.GetString(3);
	}
	else
	{
		m_edtx=L"";
		m_edty=L"";
		m_edtz=L"";
		m_edtdepth=L"";
	}
	UpdateData(false);
}

void CDataManageDlg::SetFirstDateByZk()
{
	UpdateData(true);
	UpdateData(false);
	CString strSql;
	strSql.Format(L"SELECT [TIME] FROM TB1 WHERE GCJIA='%s' ORDER BY [TIME]",m_edtzk);
	m_cmd.SetCommandText(strSql);
	MRecordset rst;
	m_cmd.ExecuteQuery(CommandTypeEnum::adCmdText,rst);
	CString strTime=rst.GetString(0);
	CString strYear=GetYear(strTime);
	CString strMouth=GetMouth(strTime);
	CString strDay=GetDay(strTime);
	((CComboBox*)(GetDlgItem(IDC_COMYEAR)))->SelectString(-1,strYear);
	((CComboBox*)(GetDlgItem(IDC_COM_MOUTH)))->SelectString(-1,strMouth);
	((CEdit*)(GetDlgItem(IDC_EDT_DAY)))->SetWindowText(strDay);
	UpdateData(true);
}

void CDataManageDlg::OnBnClickedBtnNext()
{
	// TODO: 在此添加控件通知处理程序代码
	m_edtday++;
	int y=_wtoi(m_edtyear);
	int m=_wtoi(m_edtmouth);
	if(m==12 && m_edtday>31)
	{
		y++;
		m_edtyear.Format(L"%d",y);
		m_edtmouth.Format(L"%d",1);
		m_edtday=1;
	}
	else if((m_edtday>31 && m%2==1) || (m_edtday>29 && y%4==0 && m==2) ||(m_edtday>28 && y%4!=0 && m==2) || 
		(m_edtday>30 && m%2==0 && m!=2))
	{
		int m=_wtoi(m_edtmouth);
		m++;
		m_edtmouth.Format(L"%d",m);
		m_edtday=1;
	}
	UpdateData(false);
	this->OnBnClickedBtnFind();

}
