#pragma once
struct Table_Sheet
{
	int m_NumberOfSheet;
	CString m_Str[5];
	Table_Sheet(int num)
	{
		this->m_NumberOfSheet=num;
	}
	~Table_Sheet()
	{
		
	}
};
#include "ToolDlg.h"
#include "ProgressBar.h"
// CDataInDlg 对话框
class CDataInDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDataInDlg)

public:
	CDataInDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDataInDlg();

// 对话框数据
	enum { IDD = IDD_DLG_INPUTDATA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnOpenfile();
	afx_msg void OnBnClickedBtnSavefile();
	afx_msg void OnBnClickedBtnDo();
	afx_msg void OnBnClickedBtnCancel();
	virtual BOOL OnInitDialog();

	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
public:
	void DataWarehousing(CString strExcel,CString strAccess);
	void DataWarehousing2(CString strExcel,CString strAccess);
	
	CToolDlg* m_pParentWnd;
public:
	CProgressCtrl m_ProgressControl;
	int CheckExcel(CString);
	int CheckAccess(CString);
	CString m_ExcelName;
	CString m_CurrentSheetName;
	CString m_strCurrentRecord;
public:
	int m_OperateType;
	void InputCoorData(CString strExcel,CString strAccess);
};
