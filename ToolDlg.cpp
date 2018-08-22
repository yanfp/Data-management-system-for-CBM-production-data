
// ToolDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Tool.h"
#include "ToolDlg.h"
#include "afxdialogex.h"

#include "DataInDlg.h"
#include "DataManageDlg.h"
#include "AnalyseDlg.h"
#include "DataOutputDlg.h"
#include "ManageDlg.h"
#include "Analyse2Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CToolDlg 对话框




CToolDlg::CToolDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CToolDlg::IDD, pParent)
{
	m_DbFilePath=L"";
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_CurrentConnect = _T("");
}

void CToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CURRENT, m_CurrentConnect);
	DDX_Control(pDX, IDC_MBTN_INPUT, m_BtnDataIn);
	DDX_Control(pDX, IDC_MBTN_INPUTCOOR, m_BtnInputCoorData);
	DDX_Control(pDX, IDC_MBTN_ANALYSE, m_BtnAna);
	DDX_Control(pDX, IDC_MBTN_ANALYSE2, m_BtnAna2);
	DDX_Control(pDX, IDC_MBTN_OUTPUT, m_BtnOutput);
	DDX_Control(pDX, IDC_MBTN_MANAGE, m_BtnManage);
	DDX_Control(pDX, IDC_MBTN_BATCH, m_BtnManage2);
	//  DDX_Control(pDX, IDC_MBTN_INPUT, m_MBtnDataIn);
}

BEGIN_MESSAGE_MAP(CToolDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_DATA_IN, &CToolDlg::OnBnClickedBtnDataIn)
	
	ON_BN_CLICKED(IDC_BTN_MANAGE, &CToolDlg::OnBnClickedBtnManage)
	ON_BN_CLICKED(IDC_BTN_ANLYSE, &CToolDlg::OnBnClickedBtnAnlyse)
	ON_BN_CLICKED(IDC_BTN_OUTPUT, &CToolDlg::OnBnClickedBtnOutput)
	ON_BN_CLICKED(IDC_BTN_ANALYSE2, &CToolDlg::OnBnClickedBtnAnlyse2)
	ON_BN_CLICKED(IDC_BTN_TEST, &CToolDlg::OnBnClickedBtnTest)
	ON_BN_CLICKED(IDC_BTN_ANALYSE2, &CToolDlg::OnBnClickedBtnAnalyse2)
	ON_BN_CLICKED(IDC_BTN_SET_CONNECT, &CToolDlg::OnBnClickedBtnSetConnect)
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_BTN_INPUT_CORDATA, &CToolDlg::OnBnClickedBtnInputCordata)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_MBTN_INPUT, &CToolDlg::OnBnClickedMbtnInput)
	ON_BN_CLICKED(IDC_MBTN_INPUTCOOR, &CToolDlg::OnBnClickedMbtnInputcoor)
	ON_BN_CLICKED(IDC_MBTN_MANAGE, &CToolDlg::OnBnClickedMbtnManage)
	ON_BN_CLICKED(IDC_BTN_MANAGE2, &CToolDlg::OnBnClickedBtnManage2)
	ON_BN_CLICKED(IDC_MBTN_ANALYSE, &CToolDlg::OnBnClickedMbtnAnalyse)
	ON_BN_CLICKED(IDC_MBTN_ANALYSE2, &CToolDlg::OnBnClickedMbtnAnalyse2)
	ON_BN_CLICKED(IDC_MBTN_OUTPUT, &CToolDlg::OnBnClickedMbtnOutput)
	ON_BN_CLICKED(IDC_MBTN_BATCH, &CToolDlg::OnBnClickedMbtnBatch)
END_MESSAGE_MAP()


// CToolDlg 消息处理程序

BOOL CToolDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CToolDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}



//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CToolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CToolDlg::OnBnClickedBtnDataIn()
{
	// TODO: 在此添加控件通知处理程序代码
	
}


void CToolDlg::OnBnClickedBtnManage()
{
	// TODO: 在此添加控件通知处理程序代码
	
}


void CToolDlg::OnBnClickedBtnAnlyse()
{
	// TODO: 在此添加控件通知处理程序代码
	
}


void CToolDlg::OnBnClickedBtnOutput()
{
	// TODO: 在此添加控件通知处理程序代码
	
}


void CToolDlg::OnBnClickedBtnAnlyse2()
{
	// TODO: 在此添加控件通知处理程序代码
	
}


void CToolDlg::OnBnClickedBtnTest()
{
	// TODO: 在此添加控件通知处理程序代码
	
}


void CToolDlg::OnBnClickedBtnAnalyse2()
{
	// TODO: 在此添加控件通知处理程序代码
	CAnalyse2Dlg dlg(m_CurrentConnect);
	dlg.DoModal();
}


void CToolDlg::OnBnClickedBtnSetConnect()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog OpenDlg(true,L".mdb",L"",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,L"Access文件|*.mdb|所有文件|*.*|",NULL);
	if(OpenDlg.DoModal()==IDOK)
	{
		CString str=OpenDlg.GetPathName();
		this->m_CurrentConnect=str;UpdateData(false);
	}
}


void CToolDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	
	CDialogEx::OnLButtonDown(nFlags, point);
}


BOOL CAboutDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CToolDlg::OnBnClickedBtnInputCordata()
{
	// TODO: 在此添加控件通知处理程序代码
	
	//UpdateData(false);	
}


void CToolDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
	CDC *pDC=this->GetDC();
	CPen pen(0,0,RGB(155,155,155));
	CPen* pOldPen=pDC->SelectObject(&pen);
	this->DrawLine(pDC);
	pDC->SelectObject(pOldPen);
}

void CToolDlg::DrawLine(CDC *pDC)
{
	CRect r[7];
	this->m_BtnDataIn.GetWindowRect(r[0]);
	this->m_BtnManage.GetWindowRect(r[1]);
	this->m_BtnAna.GetWindowRect(r[2]);
	this->m_BtnOutput.GetWindowRect(r[3]);
	this->m_BtnInputCoorData.GetWindowRect(r[4]);
	this->m_BtnManage2.GetWindowRect(r[5]);
	this->m_BtnAna2.GetWindowRect(r[6]);
	CPoint pt[7];
	for(int i=0;i<7;i++)
	{
		this->ScreenToClient(r[i]);
		pt[i].x=r[i].left;
		pt[i].y=(r[i].top+r[i].bottom)/2;
	}
	pDC->MoveTo(pt[0].x-30,pt[0].y);
	pDC->LineTo(pt[3].x-30,pt[3].y);

	for(int j=0;j<4;j++)
	{
		pDC->MoveTo(pt[j].x-30,pt[j].y);
		pDC->LineTo(pt[j].x,pt[j].y);
	}
	for(int k=0;k<3;k++)
	{
		pDC->MoveTo(r[k].right,pt[k].y);
		pDC->LineTo(pt[k+4].x,pt[k+4].y);
	}
}

void CToolDlg::OnBnClickedMbtnInput()
{
	// TODO: 在此添加控件通知处理程序代码
	CDataInDlg dlg(this);
	dlg.DoModal();
	UpdateData(false);
}


void CToolDlg::OnBnClickedMbtnInputcoor()
{
	// TODO: 在此添加控件通知处理程序代码
	CDataInDlg dlg;
	dlg.m_OperateType=1;
	dlg.DoModal();
}


void CToolDlg::OnBnClickedMbtnManage()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_CurrentConnect.IsEmpty())
	{
		CFileDialog OpenDlg(true,L".mdb",L"",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,L"Access文件|*.mdb|所有文件|*.*|",NULL);
		if(OpenDlg.DoModal()==IDOK)
		{
			CString str=OpenDlg.GetPathName();
			CDataManageDlg dlg(str);
			dlg.DoModal();
			if(dlg.m_IsConnected)
			{
				this->m_CurrentConnect=str;
				UpdateData(false);
			}
		}
	}
	else
	{
		CDataManageDlg dlg(m_CurrentConnect);
		dlg.DoModal();
	}
}


void CToolDlg::OnBnClickedBtnManage2()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CToolDlg::OnBnClickedMbtnAnalyse()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	if(!m_CurrentConnect.IsEmpty())
	{
		CAnalyseDlg dlg(m_CurrentConnect);
		dlg.DoModal();
	}
	else
	{
		CFileDialog OpenDlg(true,L".mdb",L"",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,L"Access文件|*.mdb|所有文件|*.*|",NULL);
		if(OpenDlg.DoModal()==IDOK)
		{
			CString str=OpenDlg.GetPathName();
			CAnalyseDlg dlg(str);
			dlg.DoModal();
			if(dlg.m_IsConnected)
				this->m_CurrentConnect=str;
			UpdateData(false);
		}
	}
}


void CToolDlg::OnBnClickedMbtnAnalyse2()
{
	// TODO: 在此添加控件通知处理程序代码
	if(!m_CurrentConnect.IsEmpty())
	{
		CAnalyse2Dlg dlg(m_CurrentConnect);
		dlg.DoModal();
	}
	else
	{
		CFileDialog OpenDlg(true,L".mdb",L"",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,L"Access文件|*.mdb|所有文件|*.*|",NULL);
		if(OpenDlg.DoModal()==IDOK)
		{
			CString str=OpenDlg.GetPathName();
			CAnalyse2Dlg dlg(str);
			dlg.DoModal();
			this->m_CurrentConnect=str;
			UpdateData(false);
		}
	}
}


void CToolDlg::OnBnClickedMbtnOutput()
{
	// TODO: 在此添加控件通知处理程序代码
	static CDataOutputDlg dlg(this->m_CurrentConnect);
	dlg.DoModal();
	
}


void CToolDlg::OnBnClickedMbtnBatch()
{
	// TODO: 在此添加控件通知处理程序代码
	CManageDlg dlg(m_CurrentConnect);
	dlg.DoModal();
}
