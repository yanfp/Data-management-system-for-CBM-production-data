#pragma once

#include "MConnection.h"
#include "MCommand.h"
#include "MRecordset.h"
#include "PicStatic.h"

#define WM_DRAWLINE WM_USER + 1

// CAnalyseDlg �Ի���
class CAnalyseDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAnalyseDlg)

public:
	CAnalyseDlg(CString str,CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAnalyseDlg();

// �Ի�������
	enum { IDD = IDD_DLG_ANALYSE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
private:
	CString m_FilePath;
public:
	MConnection m_conn;
	MCommand m_cmd;
	MRecordset m_rst;
	virtual BOOL OnInitDialog();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSelchangeComData();
	afx_msg LRESULT OnDrawLine(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnZkSelectChange(WPARAM wParam, LPARAM lParam);
	void ReadAndDraw(CDC *pDC,CPen*);
	CString m_Data;
	CString m_zk;

	double GetMaxValue(CString);

	CString GetFirstDate();
	CString GetLastDate();

	CRect GetPicRect();
	double m_MaxValue;
	
	CString m_StartDate;
	CString m_EndDate;
	afx_msg void OnPaint();
	CPicStatic m_PicStatic;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CToolTipCtrl m_ToolTip;
	BOOL m_IsConnected;
	void CreateToolTip();
	Name_Value *m_pNameValue;
	BOOL m_IsSelected;
	double m_xInterval;
	int m_RecordCount;

	void Read();//��ȡ����
	void Draw(CDC *pDC,CPen*);//��������ͼ
	afx_msg void OnCbnSelchangeComZk();

	BOOL m_IsInited;
	afx_msg void OnBnClickedBtnToExcel();

	//������Excel�ļ�
	CString CreateExcelFile();
	BOOL m_IsDrawn;
	afx_msg void OnBnClickedBtnChangeLineStyle();

	//������ʽ��
	int m_LineType;
	int m_LineWidth;
	COLORREF m_LineColor;
	CDateTimeCtrl m_StartTimeCtrl;
	CDateTimeCtrl m_EndTimeCtrl;
	afx_msg void OnBnClickedBtnUpdate();

	BOOL m_IsUpdated;
	afx_msg void OnDtnDatetimechangeDatetimepicker1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDtnDatetimechangeDatetimepicker2(NMHDR *pNMHDR, LRESULT *pResult);
};


