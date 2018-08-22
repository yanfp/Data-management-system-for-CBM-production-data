// TableSheetsDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Tool.h"
#include "TableSheetsDlg.h"
#include "afxdialogex.h"


// CTableSheetsDlg 对话框

IMPLEMENT_DYNAMIC(CTableSheetsDlg, CDialogEx)

CTableSheetsDlg::CTableSheetsDlg(CString str,CStringArray &strArray,CWnd* pParent /*=NULL*/)
	: CDialogEx(CTableSheetsDlg::IDD, pParent)
{
	m_strExcel = _T("");
	this->m_strExcel=str;
	int SheetCount=strArray.GetSize();
	for(int i=0;i<SheetCount;i++)
		this->m_SheetArray.Add(strArray.GetAt(i));
}

CTableSheetsDlg::~CTableSheetsDlg()
{
}

void CTableSheetsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_SHEETS, m_ListCtrl);
	DDX_Text(pDX, IDC_STATIC_EXCEL, m_strExcel);
}


BEGIN_MESSAGE_MAP(CTableSheetsDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_REMOVE, &CTableSheetsDlg::OnBnClickedBtnRemove)
END_MESSAGE_MAP()


// CTableSheetsDlg 消息处理程序


BOOL CTableSheetsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	int count=this->m_SheetArray.GetSize();
	for(int i=0;i<count;i++)
	{
		CString str;
		str.Format(L"[ %s ]",m_SheetArray.GetAt(i));
		this->m_ListCtrl.InsertString(-1,str);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CTableSheetsDlg::OnBnClickedBtnRemove()
{
	// TODO: 在此添加控件通知处理程序代码
	int i=m_ListCtrl.GetCurSel();
	if(i==LB_ERR)
		return;
	this->m_ListCtrl.DeleteString(i);
	this->m_SheetArray.RemoveAt(i);
}
