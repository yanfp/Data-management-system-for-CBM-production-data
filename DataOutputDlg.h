#pragma once

#include "ProgressBar.h"
// CDataOutputDlg 对话框
struct ZKValue
{
	CString m_ZK;
	double m_value;
	double m_x;
	double m_y;
	double m_z;
	int m_dayNumber;
	ZKValue()
	{
		m_ZK=L"";
		m_value=0.0;
		m_dayNumber=0;
		m_x=0;
		m_y=0;
		m_z=0;
	}
};


class CDataOutputDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDataOutputDlg)

public:
	CDataOutputDlg(CString,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDataOutputDlg();

// 对话框数据
	enum { IDD = IDD_DLG_OUTPUT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	
	afx_msg void OnBnClickedBtnOpenfile();
	afx_msg void OnBnClickedBtnSavefile();
	afx_msg void OnBnClickedBtnOutput();
	CProgressCtrl m_ProgressControl;
	
	void DataOutput(CString,CString);
	CString m_FilePath;
	int m_NumberOfZK;
	ZKValue *m_pZKValue;
	afx_msg void OnBnClickedButton2();
	CString m_strAccess;
	CString m_strPetrel;
	CString m_CurrentProcess;
	void WriteToFile(ZKValue *pzv,int num,CString FilePath);


	BOOL m_IsOutputZeroZk;
	CDateTimeCtrl m_StartDateCtrl;
	CDateTimeCtrl m_EndDateCtrl;
	CButton m_OutputZeroChkbtn;
	CButton m_SetTinelimitChkBtn;
	afx_msg void OnBnClickedChkOutputZero();
	afx_msg void OnBnClickedChkSetTimelimit();
	virtual BOOL OnInitDialog();
	CComboBox m_OutPutDataComboBox;
};
