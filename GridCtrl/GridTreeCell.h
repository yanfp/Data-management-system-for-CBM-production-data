/*****************************************************************************
    COPYRIGHT (C) 2000-2001, Ken Bertelson <kbertelson@yahoo.com>


*****************************************************************************/
#if !defined(AFX_GRIDTREECELL_H__97838AF2_EBD9_11D3_B75D_00C04F6A7AE6__INCLUDED_)
#define AFX_GRIDTREECELL_H__97838AF2_EBD9_11D3_B75D_00C04F6A7AE6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GridTreeCellBase.h"

// Place these Grid Cells in a column in a grid to
//  create a tree control
//##ModelId=4D42239B0336
class CGridTreeCell : public CGridTreeCellBase
{
    DECLARE_DYNCREATE(CGridTreeCell)

// Construction/Destruction
public:
	//##ModelId=4D42239B0343
    CGridTreeCell();
	//##ModelId=4D42239B0344
    virtual ~CGridTreeCell();


// base Attributes
public:
	//##ModelId=4D42239B0346
    virtual void SetText(LPCTSTR szText) { m_strText = szText; }
	//##ModelId=4D42239B0349
    virtual LPCTSTR  GetText() const      { return (m_strText.IsEmpty())? _T("") : m_strText; }

	//##ModelId=4D42239B034B
    virtual void Reset();

	//##ModelId=4D42239B034D
    virtual void operator=(CGridCellBase& cell)
    {
        CGridTreeCellBase::operator=( cell);
    }


// editing cells
public:
	//##ModelId=4D42239B0350
    BOOL Edit(int nRow, int nCol, CRect rect, CPoint /* point */, UINT nID, UINT nChar);
	//##ModelId=4D42239B0359
    void EndEdit();
protected:
	//##ModelId=4D42239B035A
    void OnEndEdit();

protected:
	//##ModelId=4D42239B035B
    CString  m_strText;     // Cell text (or binary data if you wish...)
};


#endif // !defined(AFX_GRIDTREECELL_H__97838AF2_EBD9_11D3_B75D_00C04F6A7AE6__INCLUDED_)
