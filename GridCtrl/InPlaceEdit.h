//////////////////////////////////////////////////////////////////////
// InPlaceEdit.h : header file
//
// MFC Grid Control - inplace editing class
//
// Written by Chris Maunder <cmaunder@mail.com>
// Copyright (c) 1998-2000. All Rights Reserved.
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
// For use with CGridCtrl v2.10+
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INPLACEEDIT_H__ECD42821_16DF_11D1_992F_895E185F9C72__INCLUDED_)
#define AFX_INPLACEEDIT_H__ECD42821_16DF_11D1_992F_895E185F9C72__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

//##ModelId=4D42239B017E
class CInPlaceEdit : public CEdit
{
// Construction
public:
	//##ModelId=4D42239B018F
    CInPlaceEdit(CWnd* pParent, CRect& rect, DWORD dwStyle, UINT nID,
                 int nRow, int nColumn, CString sInitText, UINT nFirstChar);

// Attributes
public:
 
// Operations
public:
	//##ModelId=4D42239B0198
     void EndEdit();
 
// Overrides
     // ClassWizard generated virtual function overrides
     //{{AFX_VIRTUAL(CInPlaceEdit)
	public:
	//##ModelId=4D42239B0199
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	//##ModelId=4D42239B01A0
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL
 
// Implementation
public:
	//##ModelId=4D42239B01A2
     virtual ~CInPlaceEdit();
 
// Generated message map functions
protected:
    //{{AFX_MSG(CInPlaceEdit)
	//##ModelId=4D42239B01A4
    afx_msg void OnKillFocus(CWnd* pNewWnd);
	//##ModelId=4D42239B01A7
    afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//##ModelId=4D42239B01AF
    afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//##ModelId=4D42239B01B4
	afx_msg UINT OnGetDlgCode();
	//}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
	//##ModelId=4D42239B01B6
    int     m_nRow;
	//##ModelId=4D42239B01BD
    int     m_nColumn;
	//##ModelId=4D42239B01BE
    CString m_sInitText;
	//##ModelId=4D42239B01BF
    UINT    m_nLastChar;
	//##ModelId=4D42239B01DC
    BOOL    m_bExitOnArrows;
	//##ModelId=4D42239B01DD
    CRect   m_Rect;
};
 
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INPLACEEDIT_H__ECD42821_16DF_11D1_992F_895E185F9C72__INCLUDED_)
