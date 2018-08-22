#pragma once


// CTableSheetsDlg 对话框

class CTableSheetsDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTableSheetsDlg)

public:
	CTableSheetsDlg(CString str,CStringArray &strArray,CWnd* pParent=NULL);   // 标准构造函数
	virtual ~CTableSheetsDlg();

// 对话框数据
	enum { IDD = IDD_DLG_TABLESHEET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListBox m_ListCtrl;
	CString m_strExcel;
	CStringArray m_SheetArray;
	afx_msg void OnBnClickedBtnRemove();
};
