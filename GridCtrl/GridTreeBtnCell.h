/*****************************************************************************
    COPYRIGHT (C) 2000-2001, Ken Bertelson <kbertelson@yahoo.com>


*****************************************************************************/
#if !defined(AFX_GRIDTREEBTNCELL_H__00C20285_F376_11D3_B761_00C04F6A7AE6__INCLUDED_)
#define AFX_GRIDTREEBTNCELL_H__00C20285_F376_11D3_B761_00C04F6A7AE6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GridTreeCell.h"
#include "GridBtnCell.h"

//##ModelId=4D42239B0372
class CGridTreeBtnCell : public CGridTreeCell
{
    DECLARE_DYNCREATE(CGridTreeBtnCell)
public:
	//##ModelId=4D42239B0374
    CGridTreeBtnCell();
	//##ModelId=4D42239B0382
    virtual ~CGridTreeBtnCell();

// base Attributes
public:
	//##ModelId=4D42239B0384
    virtual void Reset();

	//##ModelId=4D42239B0386
    virtual void operator=(CGridCellBase& cell)
    {
        CGridTreeCellBase::operator=( cell);
    }

	//##ModelId=4D42239B0389
    virtual void operator=(CGridTreeCell& cell)
    {
        SetTreeColumn(cell.GetTreeColumn());    // set before copy operation or
                                                //  else font copy won't happen

        CGridTreeCellBase::operator=( (CGridCellBase&)cell);
        m_GridBtnCell = (CGridCellBase&)cell;

        CPoint pointCoords = cell.GetCoords();
        SetCoords( pointCoords.y, pointCoords.x);
        m_GridBtnCell.SetCoords( pointCoords.y, pointCoords.x);

        SetLevelAndHide( cell.GetLevelAndHide());
    }

	//##ModelId=4D42239B038C
    virtual void operator=(CGridTreeBtnCell& cell)
    {
        SetTreeColumn(cell.GetTreeColumn());    // set before copy operation or
                                                //  else font copy won't happen

        CGridTreeCellBase::operator=( (CGridCellBase&)cell);
        m_GridBtnCell = (CGridCellBase&)cell;

        CPoint pointCoords = cell.GetCoords();
        SetCoords( pointCoords.y, pointCoords.x);
        m_GridBtnCell.SetCoords( pointCoords.y, pointCoords.x);

        SetLevelAndHide( cell.GetLevelAndHide());
        SetBtnDataBase( cell.GetBtnDataBase());
    }

// base attributes
	//##ModelId=4D42239B038F
    virtual void SetText(LPCTSTR szText);

// editing cells
public:
	//##ModelId=4D42239B0394
    virtual BOOL Draw(CDC* pDC, int nRow, int nCol, CRect rect, BOOL bEraseBkgnd = TRUE);
	//##ModelId=4D42239B039B
    virtual BOOL GetTextRect( LPRECT pRect);    // i/o:  i=dims of cell rect; o=dims of text rect
	//##ModelId=4D42239B039E
    virtual CSize GetCellExtent(CDC* pDC);

// editing cells
public:
	//##ModelId=4D42239B03A3
    BOOL Edit(int nRow, int nCol, CRect rect, CPoint point, UINT nID, UINT nChar);
	//##ModelId=4D42239B03AA
    virtual void EndEdit();
protected:
	//##ModelId=4D42239B03AC
    virtual void OnEndEdit();

protected:
	//##ModelId=4D42239B03B1
    virtual void OnClick( CPoint PointCellRelative);
	//##ModelId=4D42239B03B4
    virtual void OnClickDown( CPoint PointCellRelative);
	//##ModelId=4D42239B03B7
    virtual void OnRClick( CPoint PointCellRelative);
	//##ModelId=4D42239B03BA
    virtual void OnDblClick( CPoint PointCellRelative);

/*****************************************************************************
"Button" inteface begins here
*****************************************************************************/
public:
	//##ModelId=4D42239B03C1
    void SetBtnDataBase( CBtnDataBase* pBtnDataBase)
        { m_GridBtnCell.SetBtnDataBase( pBtnDataBase); }
	//##ModelId=4D42239B03C3
    CBtnDataBase* GetBtnDataBase()
        { return m_GridBtnCell.GetBtnDataBase(); }

	//##ModelId=4D42239B03C4
    BOOL SetupBtns(  int aiWhich,        // zero-based index of image to draw
                     UINT auiType,       // type of frame control to draw e.g. DFC_BUTTON
                     UINT auiState,      // like DrawFrameControl()'s nState  e.g. DFCS_BUTTONCHECK
                     CGridBtnCellBase::CTL_ALIGN aAlign,   // horizontal alignment of control image
                     int aiWidth,        // fixed width of control or 0 for size-to-fit
                     BOOL abIsMbrRadioGrp,   // T=btn is member of a radio group
                     const char* apszText)   // Text to insert centered in button; if NULL no text
    // returns:  success / failure
    {
        return m_GridBtnCell.SetupBtns(
                                    aiWhich,
                                    auiType,
                                    auiState,
                                    aAlign,
                                    aiWidth,
                                    abIsMbrRadioGrp,
                                    apszText);
    }


// for drawing things like buttons and check marks within a cell
//  you can have more than one control per cell
public:
	//##ModelId=4D42239B03D1
    virtual short GetDrawCtlNbr()
        { return m_GridBtnCell.GetDrawCtlNbr(); }

	//##ModelId=4D42239B03D3
    virtual short GetLastCtlClicked()
        { return m_GridBtnCell.GetLastCtlClicked(); }

	//##ModelId=4D42239B03D5
    virtual unsigned char GetDrawCtlNbrMax()
        { return m_GridBtnCell.GetDrawCtlNbrMax(); }

	//##ModelId=4D42239B03D7
    virtual UINT GetDrawCtlType( int aiWhich)
        { return m_GridBtnCell.GetDrawCtlType( aiWhich); }

	//##ModelId=4D42239B03DA
    virtual void SetDrawCtlType( int aiWhich, UINT auiType)
        { m_GridBtnCell.SetDrawCtlType( aiWhich, auiType); }

	//##ModelId=4D42239B03E0
    virtual UINT GetDrawCtlState( int aiWhich)
        { return m_GridBtnCell.GetDrawCtlState( aiWhich); }

	//##ModelId=4D42239B03E3
    virtual void SetDrawCtlState( int aiWhich, UINT auiState)
        { m_GridBtnCell.SetDrawCtlState( aiWhich, auiState); }

	//##ModelId=4D42239B03E7
    virtual int GetDrawCtlWidth( int aiWhich)
        { return m_GridBtnCell.GetDrawCtlWidth( aiWhich); }

	//##ModelId=4D42239B03EA
    virtual void SetDrawCtlWidth( int aiWhich, int aiWidth)
        { m_GridBtnCell.SetDrawCtlWidth( aiWhich, aiWidth); }

	//##ModelId=4D42239B03EE
    virtual CGridBtnCellBase::CTL_ALIGN GetDrawCtlAlign( int aiWhich)
        { return m_GridBtnCell.GetDrawCtlAlign( aiWhich); }

	//##ModelId=4D42239C0009
    virtual void SetDrawCtlAlign( int aiWhich, CGridBtnCellBase::CTL_ALIGN aucAlign)
        { m_GridBtnCell.SetDrawCtlAlign( aiWhich, aucAlign); }

	//##ModelId=4D42239C000D
    virtual const char* GetDrawCtlBtnText( int aiWhich)
        { return m_GridBtnCell.GetDrawCtlBtnText( aiWhich); }

	//##ModelId=4D42239C0010
    virtual void SetDrawCtlBtnText( int aiWhich, const char* apszText)
        { m_GridBtnCell.SetDrawCtlBtnText( aiWhich, apszText); }

	//##ModelId=4D42239C0014
    virtual BOOL GetDrawCtlIsMbrRadioGrp( int aiWhich)
        { return m_GridBtnCell.GetDrawCtlIsMbrRadioGrp( aiWhich); }

	//##ModelId=4D42239C0019
    virtual void SetDrawCtlIsMbrRadioGrp( int aiWhich, BOOL abOn)
        { m_GridBtnCell.SetDrawCtlIsMbrRadioGrp( aiWhich, abOn); }

/*****************************************************************************
"Button" inteface ends here
*****************************************************************************/


protected:
	//##ModelId=4D42239C001E
    CGridBtnCell m_GridBtnCell; // provides button capabilities
};

#endif // !defined(AFX_GRIDTREEBTNCELL_H__00C20285_F376_11D3_B761_00C04F6A7AE6__INCLUDED_)
