// SetTimeDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Tool.h"
#include "SetTimeDlg.h"
#include "afxdialogex.h"

#include "MyFunction.h"
// CSetTimeDlg 对话框

IMPLEMENT_DYNAMIC(CSetTimeDlg, CDialogEx)

CSetTimeDlg::CSetTimeDlg(CString StartTime,CString EndTime,CWnd* pParent)
	: CDialogEx(CSetTimeDlg::IDD, pParent)
{
	this->m_strStartTime=StartTime;
	this->m_strEndTime=EndTime;
}

CSetTimeDlg::~CSetTimeDlg()
{
}

void CSetTimeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_StartTimeCtrl);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, m_EndTimeCtrl);
}


BEGIN_MESSAGE_MAP(CSetTimeDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CSetTimeDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CSetTimeDlg 消息处理程序


void CSetTimeDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	this->m_StartTimeCtrl.GetWindowTextW(m_strStartTime);
	this->m_EndTimeCtrl.GetWindowTextW(m_strEndTime);
	CDialogEx::OnOK();
}


BOOL CSetTimeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	MyFunction fun;
	CTime t1(fun.GetYear(m_strStartTime),fun.GetMonth(m_strStartTime),fun.GetDay(m_strStartTime),0,0,0);
	CTime t2(fun.GetYear(m_strEndTime),fun.GetMonth(m_strEndTime),fun.GetDay(m_strEndTime),0,0,0);
	this->m_StartTimeCtrl.SetTime(&t1);
	this->m_EndTimeCtrl.SetTime(&t2);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
