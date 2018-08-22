// ManageDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Tool.h"
#include "ManageDlg.h"
#include "afxdialogex.h"
//#include ".\GridCtrl_src\GridCtrl.h"
#include "GridCtrl\GridCellCheck.h"

// CManageDlg �Ի���

IMPLEMENT_DYNAMIC(CManageDlg, CDialogEx)

CManageDlg::CManageDlg(CString str,CWnd* pParent /*=NULL*/)
	: CDialogEx(CManageDlg::IDD, pParent)
{
	m_pGridCtrl=NULL;
	m_FilePath=str;
	m_RecordCount = 0;
}

CManageDlg::~CManageDlg()
{
	delete m_pGridCtrl;
}

void CManageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	//DDX_Control(pDX, IDC_STATIC_DATA, m_GridCtrl);
	DDX_Control(pDX, IDC_COM_ZK, m_ComboxZk);
	DDX_Text(pDX, IDC_EDIT_COUNT, m_RecordCount);
}


BEGIN_MESSAGE_MAP(CManageDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CManageDlg::OnBnClickedButton1)
	ON_CBN_SELCHANGE(IDC_COM_ZK, &CManageDlg::OnCbnSelchangeComZk)
	ON_BN_CLICKED(IDC_BTN_SELECTALL, &CManageDlg::OnBnClickedBtnSelectall)
	ON_BN_CLICKED(IDC_BTN_SELECT_CANCEL, &CManageDlg::OnBnClickedBtnSelectCancel)
	ON_BN_CLICKED(IDC_BTN_DELETE_SELECTED, &CManageDlg::OnBnClickedBtnDeleteSelected)
END_MESSAGE_MAP()


// CManageDlg ��Ϣ�������


void CManageDlg::OnBnClickedButton1()
{
	int count=m_pGridCtrl->GetSelectedCount()/23;
	//CCellRange cellRange=m_pGridCtrl->GetSelectedCellRange();
	//m_pGridCtrl->ClearCells(cellRange);
	//m_pGridCtrl->RedrawWindow();
	CGridCellCheck* pCheck=(CGridCellCheck*)m_pGridCtrl->GetCell(3,0);
	BOOL b=pCheck->GetCheck();
	CString str;
	str.Format(L"%d",count);
	MessageBox(str);
	
}


BOOL CManageDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	if(this->m_pGridCtrl==NULL)
		m_pGridCtrl=new CGridCtrl();
	else
		return TRUE;
	
	if(this->ConnectAccess(m_FilePath))
	{
		m_cmd.SetActiveConnection(m_conn);
		m_cmd.SetCommandText(L"SELECT DISTINCT GCJIA FROM TB4");
		m_cmd.ExecuteQuery(CommandTypeEnum::adCmdText,m_rst);
		int ZkNumber=m_rst.GetRecordCount();
		while(!m_rst.rstEOF())
		{
			CString str=m_rst.GetString(0);
			((CComboBox*)(GetDlgItem(IDC_COM_ZK)))->InsertString(-1,str);
			m_rst.MoveNext();
		}
	}

	CRect rect;
	(GetDlgItem(IDC_STATIC_DATA))->GetWindowRect(rect);
	this->ScreenToClient(&rect);
	m_pGridCtrl->Create(rect,this,IDC_STATIC_DATA);
	m_pGridCtrl->SetEditable(true);
	m_pGridCtrl->EnableDragAndDrop(TRUE);
	//m_pGridCtrl->AutoSize();  
    m_pGridCtrl->SetColumnCount(24); //��ʼ��Ϊ11��
	m_pGridCtrl->SetFixedRowCount(1);
	m_pGridCtrl->SetFixedColumnCount(1);
	CString field[24]={L"��¼",L"ʱ��",L"�þ�",L"���",L"���",L"��������",L"��Ч",L"��Һ��",L"������",L"PH",L"��ɳ",
		L"����¶�",L"����¶�",L"����",L"��ѹ",L"3#ú�㶥��",L"15#ú�㶥��",L"�ù�λ��",L"ɸ��λ��",
		L"������ѹ",L"��ˮ��",L"�ۼƲ�ˮ��",L"������",L"�ۼ�������"};
	for(int i=0;i<24;i++)
	{
		m_pGridCtrl->SetItemText(0,i,field[i]);
	}
	m_pGridCtrl->AutoSizeColumns();
	m_pGridCtrl->SetRowResize(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

BOOL CManageDlg::ConnectAccess(CString str)
{
	try
	{
		CString strConnection;
		strConnection.Format(L"Provider=Microsoft.Jet.OLEDB.4.0;Data Source=%s;",this->m_FilePath);
		m_conn.SetConnectionString(strConnection);
		if(m_conn.Open(L"",L"",L"",ConnectOption::adConnectUnspecified))
		{
			return TRUE;
		}
	}
	catch(_com_error e)
	{
		CString errorMessage;
		errorMessage.Format(L"�������ݿ�ʧ��!\r\n������Ϣ:%s",e.ErrorMessage());
		MessageBox(L"��ʾ",errorMessage);
		return FALSE;
	}
}

void CManageDlg::ClearRows()
{
	int Count=m_pGridCtrl->GetRowCount();
	for(int i=0;i<Count-1;i++)
		m_pGridCtrl->DeleteRow(1);
}

void CManageDlg::OnCbnSelchangeComZk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->ClearRows();
	this->UpdateDataOnZkChange();
	//this->m_pGridCtrl->RedrawWindow();
	this->m_pGridCtrl->Invalidate();
}


void CManageDlg::UpdateDataOnZkChange()
{
	CString strZk;
	m_ComboxZk.GetWindowText(strZk);

	CString strSql;
	strSql.Format(L"SELECT * FROM TB1 WHERE GCJIA='%s'",strZk);
	m_cmd.SetCommandText(strSql);
	m_cmd.ExecuteQuery(CommandTypeEnum::adCmdText,m_rst);
	this->m_RecordCount=m_rst.GetRecordCount();
	UpdateData(false);
	int row=m_pGridCtrl->GetRowCount();
	while(!m_rst.rstEOF())
	{
		CString str[7];
		CString strId;
		//strId.Format(L"%d",row);
		m_pGridCtrl->InsertRow(strId);
		m_pGridCtrl->SetCellType(row,0,RUNTIME_CLASS(CGridCellCheck));
		for(int i=0;i<7;i++)
		{
			str[i]=m_rst.GetString(i+1);
			m_pGridCtrl->SetItemText(row,i+1,str[i]);
		}
		row++;
		m_rst.MoveNext();
	}
	
	
	strSql.Format(L"SELECT * FROM TB2 WHERE GCJIA='%s'",strZk);
	m_cmd.SetCommandText(strSql);
	m_cmd.ExecuteQuery(CommandTypeEnum::adCmdText,m_rst);
	int rows=1;
	while(!m_rst.rstEOF())
	{
		CString str[7];
		CString strId;
		
		for(int i=0;i<7;i++)
		{
			str[i]=m_rst.GetString(i+2);
			m_pGridCtrl->SetItemText(rows,i+8,str[i]);
		}
		rows++;
		m_rst.MoveNext();
	}

	strSql.Format(L"SELECT * FROM TB3 WHERE GCJIA='%s'",strZk);
	m_cmd.SetCommandText(strSql);
	m_cmd.ExecuteQuery(CommandTypeEnum::adCmdText,m_rst);
	rows=1;
	while(!m_rst.rstEOF())
	{
		CString str[5];
		for(int i=0;i<5;i++)
		{
			str[i]=m_rst.GetString(i+2);
			m_pGridCtrl->SetItemText(rows,i+15,str[i]);
		}
		rows++;
		m_rst.MoveNext();
	}

	strSql.Format(L"SELECT * FROM TB4 WHERE GCJIA='%s'",strZk);
	m_cmd.SetCommandText(strSql);
	m_cmd.ExecuteQuery(CommandTypeEnum::adCmdText,m_rst);
	rows=1;
	while(!m_rst.rstEOF())
	{
		CString str[4];
		CString strId;
		
		
		for(int i=0;i<4;i++)
		{
			str[i]=m_rst.GetString(i+2);
			m_pGridCtrl->SetItemText(rows,i+20,str[i]);
		}
		rows++;
		m_rst.MoveNext();
	}

	m_pGridCtrl->AutoSizeColumns();
	m_pGridCtrl->SetColumnWidth(0,35);
}

void CManageDlg::OnBnClickedBtnSelectall()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int RowCount=m_pGridCtrl->GetRowCount();
	for(int i=1;i<RowCount;i++)
	{
		((CGridCellCheck*)m_pGridCtrl->GetCell(i,0))->SetCheck();
	}
}


void CManageDlg::OnBnClickedBtnSelectCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int RowCount=m_pGridCtrl->GetRowCount();
	for(int i=1;i<RowCount;i++)
	{
		((CGridCellCheck*)m_pGridCtrl->GetCell(i,0))->SetCheck(0);
	}
}


BOOL CManageDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if(pMsg->message==WM_CHAR)
	{
		//MessageBox(L"1");
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CManageDlg::OnBnClickedBtnDeleteSelected()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strZk;m_ComboxZk.GetWindowText(strZk);
	CString strMsg;
	strMsg.Format(L"��ɾ���꾮���Ϊ%s��%d������\r\n�Ƿ������",strZk,this->GetSelectedCount());
	if(MessageBox(strMsg,L"��ʾ",MB_YESNO|MB_ICONEXCLAMATION )==IDNO)
	{
		return;
	}

	int RowCount=m_pGridCtrl->GetRowCount();
	CString strSql[4];
	int NumOfRowsDeleted=0;
	for(int i=1;i<RowCount;i++)
	{
		BOOL bIsSelected=((CGridCellCheck*)m_pGridCtrl->GetCell(i,0))->GetCheck();
		if(bIsSelected)
		{
			CString strTime=((CGridCell*)m_pGridCtrl->GetCell(i,1))->GetText();
			for(int j=0;j<4;j++)
			{
				strSql[j].Format(L"DELETE FROM TB%d WHERE GCJIA='%s' AND [TIME]=#%s#",j+1,strZk,strTime);
				m_cmd.SetCommandText(strSql[j]);
				long rows=0;
				try{
					m_cmd.ExecuteUpdate(rows,CommandTypeEnum::adCmdText,m_rst);
				}catch(_com_error e)
				{
					CString errorMessage;
					errorMessage.Format(L"�������ݿ�ʧ��!\r\n������Ϣ:%s",e.ErrorMessage());
					MessageBox(L"��ʾ",errorMessage);
					return ;
				}
			}
			NumOfRowsDeleted++;
			//m_pGridCtrl->DeleteRow(i-NumOfRowsDeleted-1);
		}
	}
	MessageBox(L"ɾ���ɹ���",L"��ʾ");
	//this->m_pGridCtrl->Refresh();
	this->ClearRows();
	this->UpdateDataOnZkChange();
}

int CManageDlg::GetSelectedCount()
{
	int SelectedRows=0;
	int RowCount=m_pGridCtrl->GetRowCount();
	for(int i=1;i<RowCount;i++)
	{
		BOOL bIsSelected=((CGridCellCheck*)m_pGridCtrl->GetCell(i,0))->GetCheck();
		if(bIsSelected)
			SelectedRows++;
	}
	return SelectedRows;
}
