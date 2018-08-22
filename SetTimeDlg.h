#pragma once
#include "afxdtctl.h"


// CSetTimeDlg �Ի���

class CSetTimeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSetTimeDlg)

public:
	CSetTimeDlg(CString s1,CString s2,CWnd* pParent=NULL);   // ��׼���캯��
	virtual ~CSetTimeDlg();

// �Ի�������
	enum { IDD = IDD_DLG_SETTIME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CDateTimeCtrl m_StartTimeCtrl;
	CDateTimeCtrl m_EndTimeCtrl;
	afx_msg void OnBnClickedOk();

	CString m_strStartTime;
	CString m_strEndTime;
	virtual BOOL OnInitDialog();
};
