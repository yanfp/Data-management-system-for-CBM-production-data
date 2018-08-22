#pragma once
#include "afxdtctl.h"


// CSetTimeDlg 对话框

class CSetTimeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSetTimeDlg)

public:
	CSetTimeDlg(CString s1,CString s2,CWnd* pParent=NULL);   // 标准构造函数
	virtual ~CSetTimeDlg();

// 对话框数据
	enum { IDD = IDD_DLG_SETTIME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CDateTimeCtrl m_StartTimeCtrl;
	CDateTimeCtrl m_EndTimeCtrl;
	afx_msg void OnBnClickedOk();

	CString m_strStartTime;
	CString m_strEndTime;
	virtual BOOL OnInitDialog();
};
