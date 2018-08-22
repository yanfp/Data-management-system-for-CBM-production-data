/////////////////////////////////////////////////////////////////////////////
// Titletip.h : header file
//
// MFC Grid Control - cell titletips
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

#if !defined(AFX_TITLETIP_H__C7165DA1_187F_11D1_992F_895E185F9C72__INCLUDED_)
#define AFX_TITLETIP_H__C7165DA1_187F_11D1_992F_895E185F9C72__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define TITLETIP_CLASSNAME _T("ZTitleTip")

/////////////////////////////////////////////////////////////////////////////
// CTitleTip window

//##ModelId=4D42239B00F2
class CTitleTip : public CWnd
{
// Construction
public:
	//##ModelId=4D42239B00F4
	CTitleTip();
	//##ModelId=4D42239B0101
	virtual ~CTitleTip();
	//##ModelId=4D42239B0103
	virtual BOOL Create( CWnd *pParentWnd);

// Attributes
public:
	//##ModelId=4D42239B0106
    void SetParentWnd(CWnd* pParentWnd)  { m_pParentWnd = pParentWnd; }
	//##ModelId=4D42239B0108
    CWnd* GetParentWnd()                 { return m_pParentWnd;       }

// Operations
public:
	//##ModelId=4D42239B0109
	void Show(CRect rectTitle, LPCTSTR lpszTitleText, 
              int xoffset = 0, LPRECT lpHoverRect = NULL, 
              const LOGFONT* lpLogFont = NULL,
              COLORREF crTextClr = CLR_DEFAULT, COLORREF crBackClr = CLR_DEFAULT);
	//##ModelId=4D42239B0115
    void Hide();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTitleTip)
	public:
	//##ModelId=4D42239B0116
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//##ModelId=4D42239B0119
	virtual BOOL DestroyWindow();
	//}}AFX_VIRTUAL

// Implementation
protected:
	//##ModelId=4D42239B0122
	CWnd  *m_pParentWnd;
	//##ModelId=4D42239B0126
	CRect  m_rectTitle;
	//##ModelId=4D42239B0127
    CRect  m_rectHover;
	//##ModelId=4D42239B0128
    DWORD  m_dwLastLButtonDown;
	//##ModelId=4D42239B0130
    DWORD  m_dwDblClickMsecs;
	//##ModelId=4D42239B0131
    BOOL   m_bCreated;

	// Generated message map functions
protected:
	//{{AFX_MSG(CTitleTip)
	//##ModelId=4D42239B0132
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TITLETIP_H__C7165DA1_187F_11D1_992F_895E185F9C72__INCLUDED_)
