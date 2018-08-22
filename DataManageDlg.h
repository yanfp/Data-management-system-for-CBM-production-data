#pragma once
#include "MConnection.h"
#include "MCommand.h"
#include "MRecordset.h"
#include "OdbcExcel.h"


// CDataManageDlg 对话框

class CDataManageDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDataManageDlg)

public:
	CDataManageDlg(CString,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDataManageDlg();

// 对话框数据
	enum { IDD = IDD_DLG_MANAGEDATA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_edt1;
	CString m_edt12;
	CString m_edt10;
	CString m_edt11;
	CString m_edt13;
	CString m_edt14;
	CString m_edt15;
	CString m_edt16;
	CString m_edt17;
	CString m_edt18;
	CString m_edt19;
	CString m_edt2;
	CString m_edt21;
	CString m_edt3;
	CString m_edt4;
	CString m_edt5;
	CString m_edt6;
	CString m_edt7;
	CString m_edt8;
	CString m_edt9;
	CString m_edtx;
	CString m_edty;
	CString m_edtz;

	CString m_edt20;
	CString m_edtdepth;
	CString m_edtzk;
	CString m_edtyear;
	CString m_edtmouth;
	CString m_edt22;
	int m_edtday;

public:
	CString m_FilePath;
	virtual BOOL OnInitDialog();
	void SetEdtState(BOOL);
	void SetValue(CString*,int);
public:
	MConnection m_conn;
	MCommand m_cmd;
	MRecordset m_rst;

	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedBtnFind();
	
	afx_msg void OnCbnSelchangeComZk();
	afx_msg void OnCbnSelchangeComyear();
	afx_msg void OnCbnSelchangeComMouth();
	CSpinButtonCtrl m_spin1;
	afx_msg void OnDeltaposSpin1(NMHDR *pNMHDR, LRESULT *pResult);
public:
	BOOL m_IsConnected;
	afx_msg void OnBnClickedBtnModify();
	afx_msg void OnBnClickedBtnSave();
private:
	BOOL m_IsEditable;
public:
	afx_msg void OnBnClickedBtnDelete();
	void SetFirstDateByZk();
	afx_msg LRESULT OnSelectZk(WPARAM wParam, LPARAM lParam);
    void SetZkInfo();
	afx_msg void OnBnClickedBtnNext();
};
