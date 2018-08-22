//////////////////////////////////////////////////////////////////////
// GridDropTarget.h : header file
//
// MFC Grid Control - Drag/Drop target implementation
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

#if !defined(AFX_GRIDDROPTARGET_H__5C610981_BD36_11D1_97CD_00A0243D1382__INCLUDED_)
#define AFX_GRIDDROPTARGET_H__5C610981_BD36_11D1_97CD_00A0243D1382__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


#include <afxole.h>

class CGridCtrl;

/////////////////////////////////////////////////////////////////////////////
// CGridDropTarget command target

//##ModelId=4D42239C0027
class CGridDropTarget : public COleDropTarget
{
public:
	//##ModelId=4D42239C0029
    CGridDropTarget();
	//##ModelId=4D42239C002A
    virtual ~CGridDropTarget();

// Attributes
public:
	//##ModelId=4D42239C002D
    CGridCtrl* m_pGridCtrl;
	//##ModelId=4D42239C0031
    BOOL       m_bRegistered;

// Operations
public:
	//##ModelId=4D42239C0036
    BOOL Register(CGridCtrl *pGridCtrl);
	//##ModelId=4D42239C0038
    virtual void Revoke();

	//##ModelId=4D42239C003A
    BOOL        OnDrop(CWnd* pWnd, COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point);
	//##ModelId=4D42239C003F
    DROPEFFECT  OnDragEnter(CWnd* pWnd, COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
	//##ModelId=4D42239C004A
    void        OnDragLeave(CWnd* pWnd);
	//##ModelId=4D42239C004C
    DROPEFFECT  OnDragOver(CWnd* pWnd, COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
	//##ModelId=4D42239C0055
    DROPEFFECT  OnDragScroll(CWnd* pWnd, DWORD dwKeyState, CPoint point);

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CGridDropTarget)
    //}}AFX_VIRTUAL

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(CGridDropTarget)
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRIDDROPTARGET_H__5C610981_BD36_11D1_97CD_00A0243D1382__INCLUDED_)
