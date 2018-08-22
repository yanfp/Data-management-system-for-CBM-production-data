// SetTimeDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Tool.h"
#include "SetTimeDlg.h"
#include "afxdialogex.h"

#include "MyFunction.h"
// CSetTimeDlg �Ի���

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


// CSetTimeDlg ��Ϣ�������


void CSetTimeDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->m_StartTimeCtrl.GetWindowTextW(m_strStartTime);
	this->m_EndTimeCtrl.GetWindowTextW(m_strEndTime);
	CDialogEx::OnOK();
}


BOOL CSetTimeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	MyFunction fun;
	CTime t1(fun.GetYear(m_strStartTime),fun.GetMonth(m_strStartTime),fun.GetDay(m_strStartTime),0,0,0);
	CTime t2(fun.GetYear(m_strEndTime),fun.GetMonth(m_strEndTime),fun.GetDay(m_strEndTime),0,0,0);
	this->m_StartTimeCtrl.SetTime(&t1);
	this->m_EndTimeCtrl.SetTime(&t2);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
