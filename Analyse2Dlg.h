#pragma once
#include "afxwin.h"
#include "MConnection.h"
#include "MCommand.h"
#include "MRecordset.h"

#include "PicStatic2.h"

// CAnalyse2Dlg 对话框

class CAnalyse2Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAnalyse2Dlg)

public:
	CAnalyse2Dlg(CString str,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAnalyse2Dlg();

// 对话框数据
	enum { IDD = IDD_DLG_ANALYSE2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

public:
	void DrawHistogram(int NumberOfZk,Zk_Value *pZV);
	CRect GetPicRect();
	CDC* GetPicDC();

	CRect GetNameRect();
	void DrawNameText(int NumberOfZk,Zk_Value *pZV);
	CString m_MaxValueStr;

	Zk_Value* CalculateGasProOfEveryZk();
	void GetNamesOfZks();
	CString *m_pNames;
	//int m_NumberOfZk;
	CString m_FilePath;

	MConnection m_conn;
	MRecordset m_rst;
	MCommand m_cmd;
	afx_msg void OnCbnSelchangeComZk();
	CString m_zk;
	CString m_data;

	Zk_Value* m_pZKValue;
	
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnPaint();

	BOOL m_IsInited;
//	int m_ZKCount;
	int m_NumberOfZk;

	void SetDisplayFun(int);
	CComboBox m_CurrentDiaplayComBox;
	afx_msg void OnCbnSelchangeCombo2();
	int m_CurrentIndex;
	afx_msg void OnCbnSelchangeComData();

	COLORREF m_BrushColor;
	CPicStatic2 m_PicStatic;
};
