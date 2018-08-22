// ChangeLineDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Tool.h"
#include "ChangeLineDlg.h"
#include "afxdialogex.h"


// CChangeLineDlg �Ի���

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


// CChangeLineDlg ��Ϣ�������


void CChangeLineDlg::OnBnClickedApply()
{
	UpdateData(true);
	this->m_pMainWnd->m_LineType=this->m_LineStyle;
	this->m_pMainWnd->m_LineWidth=this->m_LineWidth;
	this->m_pMainWnd->m_LineColor=this->m_ColorBtn.GetColor();
	this->m_pMainWnd->OnSelchangeComData();
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CChangeLineDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
		this->m_LineStyleComboBox.SelectString(0,L"ʵ��---------");
	if(m_LineStyle==1)
		this->m_LineStyleComboBox.SelectString(0,L"����- - - - -");
	if(m_LineStyle==2)
		this->m_LineStyleComboBox.SelectString(0,L"ʵ��.........");
	m_ColorBtn.SetColor(this->m_LineColor);
	UpdateData(false);
}

BOOL CChangeLineDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CComboBox* pComboBox=(CComboBox*)GetDlgItem(IDC_COM_LINESTYLE);
	pComboBox->InsertString(-1,L"ʵ��---------");
	pComboBox->InsertString(-1,L"����- - - - -");
	pComboBox->InsertString(-1,L"����.........");
	pComboBox->SelectString(0,L"ʵ��---------");

	this->InitCurrentSet();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CChangeLineDlg::OnCbnSelchangeComLinestyle()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str;
	this->m_LineStyleComboBox.GetWindowTextW(str);
	if(str==L"ʵ��---------")
		m_LineStyle=0;
	if(str==L"����- - - - -")
		m_LineStyle=1;
	if(str==L"����.........")
		m_LineStyle=2;
}


void CChangeLineDlg::OnEnChangeEditLinewidth()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�
	UpdateData(true);
	if(m_LineWidth>5)
		m_LineWidth=5;
	UpdateData(false);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


LRESULT CChangeLineDlg::OnNcHitTest(CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	return HTCAPTION ;
	return CDialogEx::OnNcHitTest(point);
}
