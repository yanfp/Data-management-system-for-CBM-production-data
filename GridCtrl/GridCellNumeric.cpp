// GridCellNumeric.cpp: implementation of the CGridCellNumeric class.
//
// Written by Andrew Truckle [ajtruckle@wsatkins.co.uk]
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GridCellNumeric.h"
#include "inplaceedit.h"
#include "GridCtrl.h"

IMPLEMENT_DYNCREATE(CGridCellNumeric, CGridCell)

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

// Create a control to do the editing
//##ModelId=4D4223CB0279
BOOL CGridCellNumeric::Edit(int nRow, int nCol, CRect rect, CPoint /* point */, UINT nID, UINT nChar)
{
    m_bEditing = TRUE;
    
    // CInPlaceEdit auto-deletes itself
    m_pEditWnd = new CInPlaceEdit(GetGrid(), rect, /*GetStyle() |*/ ES_NUMBER, nID, nRow, nCol,
		GetText(), nChar);

    return TRUE;
}

// Cancel the editing.
//##ModelId=4D4223CB0281
void CGridCellNumeric::EndEdit()
{
    if (m_pEditWnd)
        ((CInPlaceEdit*)m_pEditWnd)->EndEdit();
}

