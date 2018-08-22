#if !defined(AFX_GRIDCELLCOMBO_H__ECD42822_16DF_11D1_992F_895E185F9C72__INCLUDED_)
#define AFX_GRIDCELLCOMBO_H__ECD42822_16DF_11D1_992F_895E185F9C72__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// GridCellCombo.h : header file
//
// MFC Grid Control - Grid combo cell class header file
//
// Written by Chris Maunder <chris@codeproject.com>
// Copyright (c) 1998-2005. All Rights Reserved.
//
// This code may be used in compiled form in any way you desire. This
// file may be redistributed unmodified by any means PROVIDING it is 
// not sold for profit without the authors written consent, and 
// providing that this notice and the authors name and all copyright 
// notices remains intact. 
//
// An email letting me know how you are using it would be nice as well. 
//
// This file is provided "as is" with no expressed or implied warranty.
// The author accepts no liability for any damage/loss of business that
// this product may cause.
//
// For use with CGridCtrl v2.10
//
//////////////////////////////////////////////////////////////////////


#include "GridCell.h"


//##ModelId=4D4223CB0288
class CGridCellCombo : public CGridCell
{
    friend class CGridCtrl;
    DECLARE_DYNCREATE(CGridCellCombo)

public:
	//##ModelId=4D4223CB0299
    CGridCellCombo();

// editing cells
public:
	//##ModelId=4D4223CB029A
    virtual BOOL  Edit(int nRow, int nCol, CRect rect, CPoint point, UINT nID, UINT nChar);
	//##ModelId=4D4223CB02A2
    virtual CWnd* GetEditWnd() const;
	//##ModelId=4D4223CB02A7
    virtual void  EndEdit();

// Operations
public:
	//##ModelId=4D4223CB02A9
	virtual CSize GetCellExtent(CDC* pDC);

// CGridCellCombo specific calls
public:
	//##ModelId=4D4223CB02AC
    void  SetOptions(const CStringArray& ar);
	//##ModelId=4D4223CB02AE
    void  SetStyle(DWORD dwStyle)           { m_dwStyle = dwStyle; }
	//##ModelId=4D4223CB02B0
    DWORD GetStyle()                        { return m_dwStyle;    }

protected:
	//##ModelId=4D4223CB02B1
    virtual BOOL Draw(CDC* pDC, int nRow, int nCol, CRect rect, BOOL bEraseBkgnd = TRUE);

	//##ModelId=4D4223CB02BD
    CStringArray m_Strings;
	//##ModelId=4D4223CB02C6
    DWORD        m_dwStyle;
};



/////////////////////////////////////////////////////////////////////////////
// CComboEdit window

#define IDC_COMBOEDIT 1001

//##ModelId=4D4223CB02C7
class CComboEdit : public CEdit
{
// Construction
public:
	//##ModelId=4D4223CB02D7
	CComboEdit();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CComboEdit)
	//##ModelId=4D4223CB02D8
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	//##ModelId=4D4223CB02DB
	virtual ~CComboEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CComboEdit)
	//##ModelId=4D4223CB02E6
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	//##ModelId=4D4223CB02E9
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//##ModelId=4D4223CB02F8
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CInPlaceList window

//##ModelId=4D4223CB0315
class CInPlaceList : public CComboBox
{
    friend class CComboEdit;

// Construction
public:
	//##ModelId=4D4223CB0317
	CInPlaceList(CWnd* pParent,         // parent
                 CRect& rect,           // dimensions & location
                 DWORD dwStyle,         // window/combobox style
                 UINT nID,              // control ID
                 int nRow, int nColumn, // row and column
                 COLORREF crFore, COLORREF crBack,  // Foreground, background colour
				 CStringArray& Items,   // Items in list
                 CString sInitText,     // initial selection
				 UINT nFirstChar);      // first character to pass to control

// Attributes
public:
	//##ModelId=4D4223CB032A
   CComboEdit m_edit;  // subclassed edit control

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInPlaceList)
	protected:
	//##ModelId=4D4223CB032E
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
public:
	//##ModelId=4D4223CB0334
	virtual ~CInPlaceList();
	//##ModelId=4D4223CB0336
    void EndEdit();

protected:
	//##ModelId=4D4223CB0337
    int GetCorrectDropWidth();

// Generated message map functions
protected:
	//{{AFX_MSG(CInPlaceList)
	//##ModelId=4D4223CB0338
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	//##ModelId=4D4223CB0345
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//##ModelId=4D4223CB034A
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	//##ModelId=4D4223CB0357
	afx_msg void OnDropdown();
	//##ModelId=4D4223CB0359
	afx_msg UINT OnGetDlgCode();
	//##ModelId=4D4223CB0364
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	//}}AFX_MSG
	//afx_msg void OnSelendOK();

	DECLARE_MESSAGE_MAP()

private:
	//##ModelId=4D4223CB0368
	int		 m_nNumLines;
	//##ModelId=4D4223CB0369
	CString  m_sInitText;
	//##ModelId=4D4223CB0372
	int		 m_nRow;
	//##ModelId=4D4223CB0373
	int		 m_nCol;
	//##ModelId=4D4223CB0374
 	UINT     m_nLastChar; 
	//##ModelId=4D4223CB0375
	BOOL	 m_bExitOnArrows; 
    COLORREF m_crForeClr, m_crBackClr;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRIDCELLCOMBO_H__ECD42822_16DF_11D1_992F_895E185F9C72__INCLUDED_)
