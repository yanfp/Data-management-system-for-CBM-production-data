#pragma once


// CTableSheetsDlg �Ի���

class CTableSheetsDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTableSheetsDlg)

public:
	CTableSheetsDlg(CString str,CStringArray &strArray,CWnd* pParent=NULL);   // ��׼���캯��
	virtual ~CTableSheetsDlg();

// �Ի�������
	enum { IDD = IDD_DLG_TABLESHEET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListBox m_ListCtrl;
	CString m_strExcel;
	CStringArray m_SheetArray;
	afx_msg void OnBnClickedBtnRemove();
};
