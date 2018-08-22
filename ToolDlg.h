
// ToolDlg.h : ͷ�ļ�
//
#include "MConnection.h"
#include "MCommand.h"
#include "MRecordset.h"
#pragma once


// CToolDlg �Ի���
class CToolDlg : public CDialogEx
{
// ����
public:
	CToolDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TOOL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
//	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnDataIn();
//	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedBtnManage();

public:
	CString m_DbFilePath;
	afx_msg void OnBnClickedBtnAnlyse();
	CString m_CurrentConnect;
	afx_msg void OnBnClickedBtnOutput();
	afx_msg void OnBnClickedBtnAnlyse2();
	afx_msg void OnBnClickedBtnTest();
	afx_msg void OnBnClickedBtnAnalyse2();
	afx_msg void OnBnClickedBtnSetConnect();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedBtnInputCordata();
	afx_msg void OnPaint();
	CMFCButton m_BtnDataIn;
	CMFCButton m_BtnInputCoorData;
	CMFCButton m_BtnAna;
	CMFCButton m_BtnAna2;
	CMFCButton m_BtnOutput;
	CMFCButton m_BtnManage;
	CMFCButton m_BtnManage2;

	void DrawLine(CDC *pDC);
//	CMFCButton m_MBtnDataIn;
	afx_msg void OnBnClickedMbtnInput();
	afx_msg void OnBnClickedMbtnInputcoor();
	afx_msg void OnBnClickedMbtnManage();
	afx_msg void OnBnClickedBtnManage2();
	afx_msg void OnBnClickedMbtnAnalyse();
	afx_msg void OnBnClickedMbtnAnalyse2();
	afx_msg void OnBnClickedMbtnOutput();
	afx_msg void OnBnClickedMbtnBatch();
};
