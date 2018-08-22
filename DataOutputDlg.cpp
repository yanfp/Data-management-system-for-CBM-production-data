// DataOutputDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Tool.h"
#include "DataOutputDlg.h"
#include "afxdialogex.h"
#include "MConnection.h"
#include "MCommand.h"
#include "MRecordset.h"
#include <iostream>
#include <fstream>
using namespace std;
// CDataOutputDlg 对话框

IMPLEMENT_DYNAMIC(CDataOutputDlg, CDialogEx)

CDataOutputDlg::CDataOutputDlg(CString str,CWnd* pParent /*=NULL*/)
	: CDialogEx(CDataOutputDlg::IDD, pParent)
	, m_strAccess(_T(""))
	, m_strPetrel(_T(""))
{
	m_strAccess=str;
	m_NumberOfZK=0;
	m_pZKValue=NULL;
	this->m_strAccess=str;
	m_CurrentProcess = _T("Process");
	m_IsOutputZeroZk=true;
}

CDataOutputDlg::~CDataOutputDlg()
{
	if(m_pZKValue)
		delete [] m_pZKValue;
}

void CDataOutputDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_PROGRESS1, m_ProgressControl);
	DDX_Text(pDX, IDC_EDT_ACCESS, m_strAccess);
	DDX_Text(pDX, IDC_EDT_PETREL, m_strPetrel);
	DDX_Text(pDX, IDC_STATIC_PROCESS, m_CurrentProcess);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_StartDateCtrl);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, m_EndDateCtrl);
	DDX_Control(pDX, IDC_CHK_OUTPUT_ZERO, m_OutputZeroChkbtn);
	DDX_Control(pDX, IDC_CHK_SET_TIMELIMIT, m_SetTinelimitChkBtn);
	DDX_Control(pDX, IDC_COM_DATA, m_OutPutDataComboBox);
}


BEGIN_MESSAGE_MAP(CDataOutputDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_OPENFILE, &CDataOutputDlg::OnBnClickedBtnOpenfile)
	ON_BN_CLICKED(IDC_BTN_SAVEFILE, &CDataOutputDlg::OnBnClickedBtnSavefile)
	ON_BN_CLICKED(IDC_BTN_OUTPUT, &CDataOutputDlg::OnBnClickedBtnOutput)
	
	
	ON_BN_CLICKED(IDC_CHK_OUTPUT_ZERO, &CDataOutputDlg::OnBnClickedChkOutputZero)
	ON_BN_CLICKED(IDC_CHK_SET_TIMELIMIT, &CDataOutputDlg::OnBnClickedChkSetTimelimit)
END_MESSAGE_MAP()


// CDataOutputDlg 消息处理程序
BOOL CDataOutputDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CTime t1(2014,1,1,0,0,0);
	CTime t2(2015,12,31,0,0,0);
	this->m_StartDateCtrl.SetTime(&t1);
	this->m_EndDateCtrl.SetTime(&t2);
	this->m_StartDateCtrl.EnableWindow(0);
	this->m_EndDateCtrl.EnableWindow(0);
	this->m_OutputZeroChkbtn.SetCheck(1);
	this->m_OutPutDataComboBox.InsertString(-1,L"平均产气量");
	this->m_OutPutDataComboBox.InsertString(-1,L"平均产水量");
	this->m_OutPutDataComboBox.SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CDataOutputDlg::OnBnClickedBtnOpenfile()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog OpenDlg(true,L".mdb",L"",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,L"Access文件|*.mdb|所有文件|*.*|",NULL);
	if(OpenDlg.DoModal()==IDOK)
	{
		CString str=OpenDlg.GetPathName();
		m_strAccess=str;UpdateData(false);
	}
}

void CDataOutputDlg::OnBnClickedBtnSavefile()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog OpenDlg(true,L".txt",L"",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,L"TXT文件|*.txt|所有文件|*.*|",NULL);
	if(OpenDlg.DoModal()==IDOK)
	{
		CString str=OpenDlg.GetPathName();
		((CEdit*)GetDlgItem(IDC_EDT_PETREL))->SetWindowTextW(str);
	}
}


void CDataOutputDlg::WriteToFile(ZKValue *pzv,int num,CString FilePath)
{
	m_ProgressControl.SetRange(0,num-1);
	CFile mFile;
	if(!mFile.Open(FilePath, CFile::modeCreate|CFile::modeWrite))
	{
		AfxMessageBox(L"写入数据失败");
		return;
	}
	mFile.Write("钻井编号",strlen("钻井编号"));
	mFile.Write(" ",strlen(" "));
	CString strData;
	this->m_OutPutDataComboBox.GetWindowTextW(strData);
	if(strData==L"平均产气量")
		mFile.Write("平均产气量",strlen("平均产气量"));
	else
		mFile.Write("平均产水量",strlen("平均产水量"));
	mFile.Write(" ",strlen(" "));
	mFile.Write("钻井x坐标",strlen("钻井x坐标"));
	mFile.Write(" ",strlen(" "));
	mFile.Write("钻井y坐标",strlen("钻井y坐标"));
	mFile.Write(" ",strlen(" "));
	mFile.Write("钻井z坐标",strlen("钻井z坐标"));
	mFile.Write("\r\n",strlen("\r\n"));
	for(int i=0;i<num;i++)
	{
		if(!this->m_IsOutputZeroZk && pzv[i].m_value==0.0)
		{
			continue;
		}
		if(pzv[i].m_x==0.0 && pzv[i].m_ZK.Find(L"SX")>=0)
		{
			continue;
		}
		int flag=pzv[i].m_ZK.Find(L"TS")+pzv[i].m_ZK.Find(L"ZY")+pzv[i].m_ZK.Find(L"SN");
		if(pzv[i].m_x==0.0 && flag>-3)
		{
			MessageBox(pzv[i].m_ZK+L"没有坐标数据");
			continue;
		}
		if(pzv[i].m_value>2000)
		{
			continue;
		}
		CString str=pzv[i].m_ZK;
		char nameStr[30];
		int len1=wcstombs(nameStr,str,30);
		mFile.Write(nameStr,len1);
		mFile.Write(" ",strlen(" "));

		double value=pzv[i].m_value;
		char valueStr[20];
		int len2=sprintf(valueStr,"%lf",value);
		mFile.Write(&valueStr,len2);
		mFile.Write(" ",strlen(" "));

		double x=pzv[i].m_x;
		double y=pzv[i].m_y;
		double z=pzv[i].m_z;
		char cor[20];
		int len3=sprintf(cor,"%lf",x);
		mFile.Write(&cor,len3);
		mFile.Write(" ",strlen(" "));
		len3=sprintf(cor,"%lf",y);
		mFile.Write(&cor,len3);
		mFile.Write(" ",strlen(" "));
		len3=sprintf(cor,"%lf",z);
		mFile.Write(&cor,len3);

		mFile.Write("\r\n",strlen("\r\n"));
		m_ProgressControl.SetPos(i);
		
	}
	mFile.Close();
	MessageBox(L"数据输出完成！",L"提示");
	this->PostMessage(WM_CLOSE);
}


void CDataOutputDlg::OnBnClickedBtnOutput()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	if(this->m_strAccess==L"" || this->m_strPetrel==L"")
	{
		MessageBox(L"请选择文件路径!",L"提示");
		return;
	}
	this->DataOutput(m_strAccess,m_strPetrel);
}


void CDataOutputDlg::DataOutput(CString strAccess,CString strPetrel)
{
	MConnection conn;
	MCommand cmd;
	MRecordset rst;
	CString strConn;
	strConn.Format(L"Provider=Microsoft.Jet.OLEDB.4.0;Data Source=%s;",strAccess);
	conn.SetConnectionString(strConn);
	if(conn.Open(L"",L"",L"",ConnectOption::adConnectUnspecified))
	{
		this->m_CurrentProcess=L"计算平均采气量...";UpdateData(false);
		cmd.SetActiveConnection(conn);
		CString strSql;
		cmd.SetCommandText(L"SELECT DISTINCT GCJIA FROM TB4");
		try{
			cmd.ExecuteQuery(CommandTypeEnum::adCmdText,rst);
		}catch(_com_error e)
		{
			CString strError;
			strError.Format(L"错误信息：%s",e.ErrorMessage());
			MessageBox(strError,L"提示");
			return;
		}
		m_NumberOfZK=rst.GetRecordCount();
		m_ProgressControl.SetRange(0,m_NumberOfZK*2);
		m_pZKValue=new ZKValue[m_NumberOfZK];
		int i=0;
		while(!rst.rstEOF())
		{	
			CString str=rst.GetString(0);
			m_pZKValue[i++].m_ZK=str;
			rst.MoveNext();
			m_ProgressControl.SetPos(i);
		}
		for(int j=0;j<m_NumberOfZK;j++)
		{
			CString strSql2;
			CString strData;
			this->m_OutPutDataComboBox.GetWindowTextW(strData);
			if(strData==L"平均产气量")
				strData=L"GAS";
			else
				strData=L"WATER";
			if(this->m_SetTinelimitChkBtn.GetCheck())
			{
				CString strStartTime,strEndTime;
				this->m_StartDateCtrl.GetWindowTextW(strStartTime);
				this->m_EndDateCtrl.GetWindowTextW(strEndTime);
				strSql2.Format(L"SELECT AVG(%s),COUNT(*) FROM TB4 WHERE GCJIA='%s' AND GAS>0 AND [TIME] BETWEEN #%s# AND #%s#",
					strData,m_pZKValue[j].m_ZK,strStartTime,strEndTime);
			}
			else
			{
				strSql2.Format(L"SELECT AVG(%s),COUNT(*) FROM TB4 WHERE GCJIA='%s' AND GAS>0",strData,m_pZKValue[j].m_ZK);
			}
			cmd.SetCommandText(strSql2);
			try{
				cmd.ExecuteQuery(CommandTypeEnum::adCmdText,rst);
				m_pZKValue[j].m_value=_wtof(rst.GetString(0));
				m_pZKValue[j].m_dayNumber=_wtof(rst.GetString(1));
			}catch(_com_error e)
			{
				CString strMessage;
				strMessage.Format(L"钻井%s计算产气量错误！",m_pZKValue[j].m_ZK);
				MessageBox(strMessage,L"提示");
				continue;
			}

			MRecordset rstTemp;
			CString strSelectXY;
			strSelectXY.Format(L"SELECT ZKX,ZKY,ZKZ FROM ZKTB1 WHERE GCJIA='%s'",m_pZKValue[j].m_ZK);
			cmd.SetCommandText(strSelectXY);
			try{
				cmd.ExecuteQuery(CommandTypeEnum::adCmdText,rstTemp);
				m_pZKValue[j].m_x=_wtof(rstTemp.GetString(0));
				m_pZKValue[j].m_y=_wtof(rstTemp.GetString(1));
				m_pZKValue[j].m_z=_wtof(rstTemp.GetString(2));
			}catch(_com_error e)
			{
				CString strMessage;
				strMessage.Format(L"钻井%s查询坐标错误！",m_pZKValue[j].m_ZK);
				//MessageBox(strMessage,L"提示");
				continue;
			}
			m_ProgressControl.SetPos(m_NumberOfZK+j);
		}
	}
	else
	{
		MessageBox(L"数据库打开错误！",L"提示");
		return;
	}
	this->m_CurrentProcess=L"计算结果输出...";UpdateData(false);
	this->WriteToFile(m_pZKValue,m_NumberOfZK,strPetrel);
}

void CDataOutputDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	this->UpdateData(true);
}


void CDataOutputDlg::OnBnClickedChkOutputZero()
{
	// TODO: 在此添加控件通知处理程序代码
	this->m_IsOutputZeroZk=this->m_OutputZeroChkbtn.GetCheck();
}


void CDataOutputDlg::OnBnClickedChkSetTimelimit()
{
	// TODO: 在此添加控件通知处理程序代码
	BOOL b=this->m_SetTinelimitChkBtn.GetCheck();
	this->m_StartDateCtrl.EnableWindow(b);
	this->m_EndDateCtrl.EnableWindow(b);
}



