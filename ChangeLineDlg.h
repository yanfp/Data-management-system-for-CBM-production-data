#pragma once

#include "AnalyseDlg.h"
// CChangeLineDlg �Ի���

class CChangeLineDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CChangeLineDlg)

public:
	CChangeLineDlg(CWnd* pParent,int,int,COLORREF);   // ��׼���캯��
	virtual ~CChangeLineDlg();

// �Ի�������
	enum { IDD = IDD_DLG_CHANGELINE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()


public:
	CAnalyseDlg* m_pMainWnd;
	int m_LineStyle;
	int m_LineWidth;
	COLORREF m_LineColor;
	afx_msg void OnBnClickedApply();
	afx_msg void OnBnClickedOk();
	CMFCColorButton m_ColorBtn;
	virtual BOOL OnInitDialog();
	CComboBox m_LineStyleComboBox;

	void InitCurrentSet();
	afx_msg void OnCbnSelchangeComLinestyle();
	afx_msg void OnEnChangeEditLinewidth();
	afx_msg LRESULT OnNcHitTest(CPoint point);
};
