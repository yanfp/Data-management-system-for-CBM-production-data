// ChangeLineDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Tool.h"
#include "ChangeLineDlg.h"
#include "afxdialogex.h"


// CChangeLineDlg 对话框

IMPLEMENT_DYNAMIC(CChangeLineDlg, CDialogEx)

CChangeLineDlg::CChangeLineDlg(CWnd* pParent,int ls,int lw,COLORREF color)
	: CDialogEx(CChangeLineDlg::IDD, pParent)
{
	m_pMainWnd=(CAnalyseDlg*)pParent;
	m_LineStyle = ls;
	m_LineWidth = lw;
	m_LineColor=color;
}

CChangeLineDlg::~CChangeLineDlg()
{
}

void CChangeLineDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_CBIndex(pDX, IDC_COM_LINESTYLE, m_LineStyle);
	DDX_Text(pDX, IDC_EDIT_LINEWIDTH, m_LineWidth);
	DDV_MinMaxInt(pDX, m_LineWidth, 0, 5);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON1, m_ColorBtn);
	DDX_Control(pDX, IDC_COM_LINESTYLE, m_LineStyleComboBox);
}


BEGIN_MESSAGE_MAP(CChangeLineDlg, CDialogEx)
	ON_BN_CLICKED(ID_APPLY, &CChangeLineDlg::OnBnClickedApply)
	ON_BN_CLICKED(IDOK, &CChangeLineDlg::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_COM_LINESTYLE, &CChangeLineDlg::OnCbnSelchangeComLinestyle)
	ON_EN_CHANGE(IDC_EDIT_LINEWIDTH, &CChangeLineDlg::OnEnChangeEditLinewidth)
	ON_WM_NCHITTEST()
END_MESSAGE_MAP()


// CChangeLineDlg 消息处理程序


void CChangeLineDlg::OnBnClickedApply()
{
	UpdateData(true);
	this->m_pMainWnd->m_LineType=this->m_LineStyle;
	this->m_pMainWnd->m_LineWidth=this->m_LineWidth;
	this->m_pMainWnd->m_LineColor=this->m_ColorBtn.GetColor();
	this->m_pMainWnd->OnSelchangeComData();
	// TODO: 在此添加控件通知处理程序代码
}


void CChangeLineDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	this->m_pMainWnd->m_LineType=this->m_LineStyle;
	this->m_pMainWnd->m_LineWidth=this->m_LineWidth;
	this->m_pMainWnd->m_LineColor=this->m_ColorBtn.GetColor();
	this->m_pMainWnd->OnSelchangeComData();
	CDialogEx::OnOK();
}

void CChangeLineDlg::InitCurrentSet()
{
	if(m_LineStyle==0)
		this->m_LineStyleComboBox.SelectString(0,L"实线---------");
	if(m_LineStyle==1)
		this->m_LineStyleComboBox.SelectString(0,L"虚线- - - - -");
	if(m_LineStyle==2)
		this->m_LineStyleComboBox.SelectString(0,L"实线.........");
	m_ColorBtn.SetColor(this->m_LineColor);
	UpdateData(false);
}

BOOL CChangeLineDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CComboBox* pComboBox=(CComboBox*)GetDlgItem(IDC_COM_LINESTYLE);
	pComboBox->InsertString(-1,L"实线---------");
	pComboBox->InsertString(-1,L"虚线- - - - -");
	pComboBox->InsertString(-1,L"点线.........");
	pComboBox->SelectString(0,L"实线---------");

	this->InitCurrentSet();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CChangeLineDlg::OnCbnSelchangeComLinestyle()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	this->m_LineStyleComboBox.GetWindowTextW(str);
	if(str==L"实线---------")
		m_LineStyle=0;
	if(str==L"虚线- - - - -")
		m_LineStyle=1;
	if(str==L"点线.........")
		m_LineStyle=2;
}


void CChangeLineDlg::OnEnChangeEditLinewidth()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	UpdateData(true);
	if(m_LineWidth>5)
		m_LineWidth=5;
	UpdateData(false);
	// TODO:  在此添加控件通知处理程序代码
}


LRESULT CChangeLineDlg::OnNcHitTest(CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	return HTCAPTION ;
	return CDialogEx::OnNcHitTest(point);
}
