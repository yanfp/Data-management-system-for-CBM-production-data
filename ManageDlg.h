#pragma once
#include "afxwin.h"
#include "GridCtrl/GridCtrl.h"
//#include "gridctrl\gridctrl.h"
//#include ".\GridCtrl_src\GridCtrl.h"
#include "MConnection.h"
#include "MCommand.h"
#include "MRecordset.h"
// CManageDlg 对话框

class CManageDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CManageDlg)

public:
	CManageDlg(CString,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CManageDlg();

// 对话框数据
	enum { IDD = IDD_DLG_MANAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	//CGridCtrl m_GridCtrl;
	afx_msg void OnBnClickedButton1();
	CGridCtrl* m_pGridCtrl;
	virtual BOOL OnInitDialog();

public:
	MConnection m_conn;
	MCommand m_cmd;
	MRecordset m_rst;
	CString m_FilePath;

	BOOL ConnectAccess(CString);//连接数据库
	afx_msg void OnCbnSelchangeComZk();
	CComboBox m_ComboxZk;

	void UpdateDataOnZkChange();
	afx_msg void OnBnClickedBtnSelectall();
	afx_msg void OnBnClickedBtnSelectCancel();
	int m_RecordCount;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedBtnDeleteSelected();
	void ClearRows();

	int GetSelectedCount();
};
