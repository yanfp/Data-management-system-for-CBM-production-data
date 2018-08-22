#if !defined(AFX_GRIDCELLCHECK_H__ECD42822_16DF_11D1_992F_895E185F9C72__INCLUDED_)
#define AFX_GRIDCELLCHECK_H__ECD42822_16DF_11D1_992F_895E185F9C72__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// GridCellCheck.h : header file
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
// For use with CGridCtrl v2.22+
//
//////////////////////////////////////////////////////////////////////


#include "GridCell.h"


//##ModelId=4D4223CB0382
class CGridCellCheck : public CGridCell
{
    friend class CGridCtrl;
    DECLARE_DYNCREATE(CGridCellCheck)

public:
	//##ModelId=4D4223CB0393
    CGridCellCheck();

public:
	//##ModelId=4D4223CB0394
	BOOL SetCheck(BOOL bChecked = TRUE);
	//##ModelId=4D4223CB0396
	BOOL GetCheck();

// Operations
	//##ModelId=4D4223CB0397
	virtual CSize GetCellExtent(CDC* pDC);
	//##ModelId=4D4223CB039A
    virtual void OnClick( CPoint PointCellRelative);
	//##ModelId=4D4223CB03A1
    virtual BOOL GetTextRect( LPRECT pRect);

protected:
	//##ModelId=4D4223CB03A4
	CRect GetCheckPlacement();

	//##ModelId=4D4223CB03A5
    virtual BOOL Draw(CDC* pDC, int nRow, int nCol, CRect rect, BOOL bEraseBkgnd = TRUE);

protected:
	//##ModelId=4D4223CB03B4
    BOOL  m_bChecked;
	//##ModelId=4D4223CB03B5
    CRect m_Rect;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRIDCELLCHECK_H__ECD42822_16DF_11D1_992F_895E185F9C72__INCLUDED_)
