
// ToolDlg.cpp : ʵ���ļ�
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


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CToolDlg �Ի���




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


// CToolDlg ��Ϣ�������

BOOL CToolDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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



//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CToolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CToolDlg::OnBnClickedBtnDataIn()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
}


void CToolDlg::OnBnClickedBtnManage()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
}


void CToolDlg::OnBnClickedBtnAnlyse()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
}


void CToolDlg::OnBnClickedBtnOutput()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
}


void CToolDlg::OnBnClickedBtnAnlyse2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
}


void CToolDlg::OnBnClickedBtnTest()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
}


void CToolDlg::OnBnClickedBtnAnalyse2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CAnalyse2Dlg dlg(m_CurrentConnect);
	dlg.DoModal();
}


void CToolDlg::OnBnClickedBtnSetConnect()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CFileDialog OpenDlg(true,L".mdb",L"",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,L"Access�ļ�|*.mdb|�����ļ�|*.*|",NULL);
	if(OpenDlg.DoModal()==IDOK)
	{
		CString str=OpenDlg.GetPathName();
		this->m_CurrentConnect=str;UpdateData(false);
	}
}


void CToolDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	
	CDialogEx::OnLButtonDown(nFlags, point);
}


BOOL CAboutDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CToolDlg::OnBnClickedBtnInputCordata()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	//UpdateData(false);	
}


void CToolDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDataInDlg dlg(this);
	dlg.DoModal();
	UpdateData(false);
}


void CToolDlg::OnBnClickedMbtnInputcoor()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDataInDlg dlg;
	dlg.m_OperateType=1;
	dlg.DoModal();
}


void CToolDlg::OnBnClickedMbtnManage()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(m_CurrentConnect.IsEmpty())
	{
		CFileDialog OpenDlg(true,L".mdb",L"",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,L"Access�ļ�|*.mdb|�����ļ�|*.*|",NULL);
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CToolDlg::OnBnClickedMbtnAnalyse()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	if(!m_CurrentConnect.IsEmpty())
	{
		CAnalyseDlg dlg(m_CurrentConnect);
		dlg.DoModal();
	}
	else
	{
		CFileDialog OpenDlg(true,L".mdb",L"",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,L"Access�ļ�|*.mdb|�����ļ�|*.*|",NULL);
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(!m_CurrentConnect.IsEmpty())
	{
		CAnalyse2Dlg dlg(m_CurrentConnect);
		dlg.DoModal();
	}
	else
	{
		CFileDialog OpenDlg(true,L".mdb",L"",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,L"Access�ļ�|*.mdb|�����ļ�|*.*|",NULL);
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	static CDataOutputDlg dlg(this->m_CurrentConnect);
	dlg.DoModal();
	
}


void CToolDlg::OnBnClickedMbtnBatch()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CManageDlg dlg(m_CurrentConnect);
	dlg.DoModal();
}
