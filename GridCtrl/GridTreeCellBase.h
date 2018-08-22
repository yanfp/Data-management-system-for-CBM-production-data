/*****************************************************************************
    COPYRIGHT (C) 2000-2001, Ken Bertelson <kbertelson@yahoo.com>


*****************************************************************************/
#if !defined(AFX_GridTreeCellBase_H__97838AF2_EBD9_11D3_B75D_00C04F6A7AE6__INCLUDED_)
#define AFX_GridTreeCellBase_H__97838AF2_EBD9_11D3_B75D_00C04F6A7AE6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GridCell.h"
#include "TreeColumn.h"

// Place these Grid Cells in a column in a grid to
//  create a tree control
//##ModelId=4D42239B021B
class CGridTreeCellBase : public CGridCellBase
{
    DECLARE_DYNCREATE(CGridTreeCellBase)

// Construction/Destruction
public:
	//##ModelId=4D42239B021D
    CGridTreeCellBase();
	//##ModelId=4D42239B021E
    virtual ~CGridTreeCellBase();

    // initial setup for each cell
	//##ModelId=4D42239B022A
    void SetTreeColumn( CTreeColumn* pTreeColumn)
        { ASSERT( pTreeColumn != NULL); m_pTreeColumn = pTreeColumn; }
	//##ModelId=4D42239B022C
    CTreeColumn* GetTreeColumn() { return m_pTreeColumn; }

	//##ModelId=4D42239B022D
    void SetLevel( UCHAR ucLevel)
        { ASSERT( ucLevel < 0x7F); m_ucLevelAndHide &= 0x80; m_ucLevelAndHide |= ucLevel; }
	//##ModelId=4D42239B022F
    UCHAR GetLevel() { return UCHAR( m_ucLevelAndHide & 0x7F ); }

	//##ModelId=4D42239B023A
    void SetViewable( BOOL bViewable)
        { bViewable ? m_ucLevelAndHide |= 0x80 : m_ucLevelAndHide &= 0x7F; }
	//##ModelId=4D42239B023C
    BOOL IsViewable() { return (m_ucLevelAndHide & 0x80) == 0x80; }

    // used only when communicating with CGridTreeCtrl
	//##ModelId=4D42239B023D
    void SetLevelAndHide( UCHAR ucLevelAndHide) { m_ucLevelAndHide = ucLevelAndHide; }
	//##ModelId=4D42239B023F
    UCHAR GetLevelAndHide() { return m_ucLevelAndHide; }

	//##ModelId=4D42239B0334
    typedef enum
    {
        TREE_IMAGE_FOLDER_OPEN,
        TREE_IMAGE_FOLDER_CLOSED,
        TREE_IMAGE_DOCUMENT,

        TREE_IMAGE_FENCE      // ** don't delete or move from end
    }   TREE_IMAGE;  // defines how Tree will use image list

// base Attributes
public:
    // use base class for SetState(DWORD nState);
    // use base class for GetState();
	//##ModelId=4D42239B0240
    virtual void SetGrid(CGridCtrl* /* pGrid */) {};
	//##ModelId=4D42239B0249
    virtual CGridCtrl* GetGrid() const
        {   ASSERT( m_pTreeColumn != NULL);
            return m_pTreeColumn->GetGrid(); }

	//##ModelId=4D42239B024B
    virtual void SetText(LPCTSTR /* szText */) { ASSERT( FALSE); }   // must override
	//##ModelId=4D42239B024E
    virtual LPCTSTR  GetText() const      { ASSERT( FALSE); return NULL; } // must override

	//##ModelId=4D42239B0250
    virtual void SetImage(int nImage) { ASSERT( nImage <= USHRT_MAX); m_sImage = (short)nImage; }
	//##ModelId=4D42239B0253
    virtual int      GetImage() const     { return m_sImage;  }

    // let the CGridTreeCtrl maintain a single instance of the following:
	//##ModelId=4D42239B025A
    virtual void SetData(LPARAM lParam)
        { if( m_pTreeColumn != NULL) m_pTreeColumn->SetParam( lParam); }
	//##ModelId=4D42239B025D
    virtual void SetFormat(DWORD nFormat)
        { if( m_pTreeColumn != NULL) m_pTreeColumn->SetFormat( nFormat); }
	//##ModelId=4D42239B0260
    virtual void SetTextClr(COLORREF clr)
        { if( m_pTreeColumn != NULL) m_pTreeColumn->SetFgClr( clr); }
	//##ModelId=4D42239B0263
    virtual void SetBackClr(COLORREF clr)
        { if( m_pTreeColumn != NULL) m_pTreeColumn->SetBkClr( clr); }
	//##ModelId=4D42239B0269
    virtual void SetFont(const LOGFONT* plf)
    {
        if( m_pTreeColumn != NULL)
        {
            m_pTreeColumn->SetFont( plf);

            // Calculate the default tree indentation
            CWindowDC dc(NULL);
            CFont font;
            font.CreateFontIndirect(plf);
            CFont* pOldFont = dc.SelectObject(&font);
            TEXTMETRIC tm;
            dc.GetTextMetrics(&tm);
            dc.SelectObject(pOldFont);

            m_pTreeColumn->SetDefTreeIndent( tm.tmHeight+tm.tmExternalLeading);    // so can draw square box

        }
    }

	//##ModelId=4D42239B026C
    virtual void SetMargin( UINT nMargin)
        { if( m_pTreeColumn != NULL) m_pTreeColumn->GetGrid()->SetDefCellMargin( nMargin); }
	//##ModelId=4D42239B026F
    virtual void SetCoords( int nRow, int nCol) { m_iRow = nRow; m_iCol = nCol; }
	//##ModelId=4D42239B0273
    virtual CPoint GetCoords() const { return CPoint( m_iCol, m_iRow); }

	//##ModelId=4D42239B0275
    virtual LPARAM   GetData() const
        {
            if( m_pTreeColumn != NULL)
                return m_pTreeColumn->GetParam();
            return 0;
        }
	//##ModelId=4D42239B0279
    virtual DWORD    GetFormat() const
        {
            if( m_pTreeColumn != NULL)
                return m_pTreeColumn->GetFormat();
            return 0;
        }
	//##ModelId=4D42239B027B
    virtual COLORREF GetTextClr() const
        {
            if( m_pTreeColumn != NULL)
                return m_pTreeColumn->GetFgClr();
            return CLR_DEFAULT;
        }
	//##ModelId=4D42239B027D
    virtual COLORREF GetBackClr() const
        {
            if( m_pTreeColumn != NULL)
                return m_pTreeColumn->GetBkClr();
            return CLR_DEFAULT;
        }
	//##ModelId=4D42239B027F
    virtual LOGFONT* GetFont() const
        {
            if( m_pTreeColumn != NULL)
                return m_pTreeColumn->GetFont();
            return NULL;
        }

	//##ModelId=4D42239B0281
    virtual CFont*  GetFontObject() const
        {
            // If the default font is specified, use the default cell implementation
            if (GetFont() == NULL)
            {
                CGridDefaultCell *pDefaultCell = (CGridDefaultCell*) GetDefaultCell();
                if (!pDefaultCell)
                    return NULL;

                return pDefaultCell->GetFontObject();
            }
            else
            {
                static CFont Font;
                Font.DeleteObject();
                Font.CreateFontIndirect(GetFont());
                return &Font;
            }
        }

	//##ModelId=4D42239B0283
    virtual UINT     GetMargin() const
        {
            if( m_pTreeColumn != NULL)
                return m_pTreeColumn->GetGrid()->GetDefCellMargin();
            return 0;
        }

	//##ModelId=4D42239B0288
    virtual BOOL IsDefaultFont() const
        {
            if( m_pTreeColumn != NULL)
                return m_pTreeColumn->IsDefaultFont();
            return TRUE;
        }

	//##ModelId=4D42239B028A
    virtual void Reset();
	//##ModelId=4D42239B028C
    virtual BOOL IsEditing() const { return m_ucEditing; }

	//##ModelId=4D42239B028E
    virtual void operator=(CGridCellBase& cell)
    {
        CGridCellBase::operator=( cell);
    }

// editing cells
public:
	//##ModelId=4D42239B0291
    virtual BOOL Draw(CDC* pDC, int nRow, int nCol, CRect rect, BOOL bEraseBkgnd = TRUE);
	//##ModelId=4D42239B029D
    BOOL DrawTreeCell(CDC* pDC, int nRow, int nCol, CRect* prect, BOOL bEraseBkgnd);
	//##ModelId=4D42239B02A7
    virtual BOOL GetTextRect( LPRECT pRect);    // i/o:  i=dims of cell rect; o=dims of text rect
	//##ModelId=4D42239B02AA
    virtual CSize GetCellExtent(CDC* pDC);

    // override the following
	//##ModelId=4D42239B02AD
    virtual BOOL PrintCell(CDC* pDC, int nRow, int nCol, CRect rect);

// tree drawing
protected:

	//##ModelId=4D42239B02BB
    void TreeGetBoxRelCoords(CRect* apRect);      // returns: relative coordinates

	//##ModelId=4D42239B02BD
    int GetTreeIndent();
    // returns:  device units to indent within a cell for a tree at this level

	//##ModelId=4D42239B02C6
    BOOL TreeHitPlusMinus(  CPoint aPointMouse); // relative coordinates of mouse click
    // returns:  T=hit a plus or minus;  F=Missed it or tree cell has no plus or minus

	//##ModelId=4D42239B02C8
    void TreeDrawGraphic(CDC* apDC,      // current CDC
                         CRect aRect);   // coordinates of bounding cell rectangle

    // helpers to assure that I don't draw outside of my rectangle
	//##ModelId=4D42239B02CB
    BOOL TryMoveTo( const CRect& aRect, CDC* apDC, int aX, int aY)
    {
        CRect rectMargin( aRect);
        rectMargin.InflateRect( GetMargin(), GetMargin() );
        if( rectMargin.PtInRect( CPoint( aX, aY ))  )
        {
            apDC->MoveTo( aX, aY);
            return TRUE;
        }
        return FALSE;
    }

	//##ModelId=4D42239B02D8
    BOOL TryLineTo( const CRect& aRect, CDC* apDC, int aX, int aY)
    {
        CRect rectMargin( aRect);
        rectMargin.InflateRect( GetMargin(), GetMargin() );
        if( rectMargin.PtInRect( CPoint( aX, aY ))  )
        {
            apDC->LineTo( aX, aY);
            return TRUE;
        }
        return FALSE;
    }

// editing cells
public:
	//##ModelId=4D42239B02DD
    virtual BOOL Edit(  int /* nRow */, int /* nCol */, CRect /* rect */, CPoint /* point */,
                        UINT /* nID */, UINT /* nChar */) { ASSERT( FALSE); return FALSE;}
	//##ModelId=4D42239B02E7
    virtual void EndEdit() {};
protected:
	//##ModelId=4D42239B02E9
    virtual void OnEndEdit() {};

protected:
	//##ModelId=4D42239B02EB
    virtual void OnClick( CPoint PointCellRelative);
	//##ModelId=4D42239B02EE
    virtual void OnClickDown( CPoint PointCellRelative);
	//##ModelId=4D42239B02F5
    virtual void OnRClick( CPoint PointCellRelative);
	//##ModelId=4D42239B02F8
    virtual void OnDblClick( CPoint PointCellRelative);

protected:
	//##ModelId=4D42239B0305
    UCHAR    m_ucEditing;   // Cell being edited?
	//##ModelId=4D42239B0306
    UCHAR    m_ucLevelAndHide;  // high-order bit tells if cell is viewable or hidden;
                                //  rest tell the tree level of this cell
	//##ModelId=4D42239B0307
    short    m_sImage;      // Index of the list view item’s icon
	//##ModelId=4D42239B0308
    int      m_iRow;        // Each cell needs to know position relative to neighbor cells
	//##ModelId=4D42239B0309
    int      m_iCol;

	//##ModelId=4D42239B0316
    CTreeColumn* m_pTreeColumn; // contains collection of cells plus access to parent grid control
};


#endif // !defined(AFX_GridTreeCellBase_H__97838AF2_EBD9_11D3_B75D_00C04F6A7AE6__INCLUDED_)
