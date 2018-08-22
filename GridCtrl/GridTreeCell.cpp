/*****************************************************************************
    COPYRIGHT (C) 2000-2001, Ken Bertelson <kbertelson@yahoo.com>


*****************************************************************************/
#include "stdafx.h"
#include "GridTreeCell.h"

#include "GridCtrl.h"
#include "InPlaceEdit.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CGridTreeCell, CGridTreeCellBase)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//##ModelId=4D42239B0343
CGridTreeCell::CGridTreeCell()
    : CGridTreeCellBase()
{
}

//##ModelId=4D42239B0344
CGridTreeCell::~CGridTreeCell()
{
}

//##ModelId=4D42239B034B
void CGridTreeCell::Reset()
{
    m_strText.Empty();
}

//##ModelId=4D42239B0350
BOOL CGridTreeCell::Edit(int nRow, int nCol, CRect rect, CPoint /* point */, UINT nID, UINT nChar)
{
    ASSERT( m_pTreeColumn != NULL);
    DWORD dwStyle = ES_LEFT;
    if (GetFormat() & DT_RIGHT)
        dwStyle = ES_RIGHT;
    else if (GetFormat() & DT_CENTER)
        dwStyle = ES_CENTER;

    m_ucEditing = TRUE;

    // InPlaceEdit auto-deletes itself
    CGridCtrl* pGrid = GetGrid();
    m_pTreeColumn->SetEditWnd( new CInPlaceEdit(pGrid, rect, dwStyle, nID, nRow, nCol, GetText(), nChar) );

    return TRUE;
}

//##ModelId=4D42239B0359
void CGridTreeCell::EndEdit()
{
    CWnd* pEditWnd = m_pTreeColumn->GetEditWnd();
    if (pEditWnd)
        ((CInPlaceEdit*)(pEditWnd))->EndEdit();

    m_pTreeColumn->SetEditWnd( NULL);
}

//##ModelId=4D42239B035A
void CGridTreeCell::OnEndEdit()
{
    EndEdit();
    m_ucEditing = FALSE;
}

