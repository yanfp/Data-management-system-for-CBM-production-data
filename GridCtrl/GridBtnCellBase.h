/*****************************************************************************
    COPYRIGHT (C) 2000-2001, Ken Bertelson <kbertelson@yahoo.com>


*****************************************************************************/
#if !defined(AFX_GridBtnCellBase_H__97838AF2_EBD9_11D3_B75D_00C04F6A7AE6__INCLUDED_)
#define AFX_GridBtnCellBase_H__97838AF2_EBD9_11D3_B75D_00C04F6A7AE6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GridCell.h"
#include "BtnDataBase.h"

//##ModelId=4D4223CC02B7
class CGridBtnCellBase : public CGridCellBase
{
    friend class CGridTreeBtnCell;
    DECLARE_DYNCREATE(CGridBtnCellBase)

// Construction/Destruction
public:
	//##ModelId=4D4223CC02B9
    CGridBtnCellBase();
	//##ModelId=4D4223CC02D6
    virtual ~CGridBtnCellBase();

	//##ModelId=4D4223CC02E6
    void SetBtnDataBase( CBtnDataBase* pBtnDataBase)
        {
            ASSERT( pBtnDataBase);
            m_pBtnDataBase = pBtnDataBase;
        }
	//##ModelId=4D4223CC02E8
    CBtnDataBase* GetBtnDataBase() { return m_pBtnDataBase; }

public:
    // structs used when manipulating buttons
	//##ModelId=4D4223CD00F2
    typedef enum
    {
        CTL_ALIGN_CENTER,
        CTL_ALIGN_LEFT,
        CTL_ALIGN_RIGHT,

        CTL_ALIGN_FENCE     // ** don't delete or remove from last in list
    }   CTL_ALIGN;  // how is DrawFrameControl() aligned?

	//##ModelId=4D4223CD00F4
    typedef struct
    {
        int iWidth;             // Fixed width of button; if 0, size to cell width
        short sState;           // e.g. DFCS_PUSHED | DFCS_BUTTONCHECK
        unsigned char ucIsMbrRadioGrp : 1;  // T=btn is member of a radio group
        unsigned char ucAlign : 7;  // how control image is aligned
        unsigned char ucType;   // type of control to draw  e.g. DFC_BUTTON

    }   STRUCT_DRAWCTL; // used with win32's DrawFrameControl() to place an image
                        //  of a windows control within a cell

	//##ModelId=4D4223CC02E9
    BOOL SetupBtns(  int aiWhich,        // zero-based index of image to draw
                     UINT auiType,       // type of frame control to draw e.g. DFC_BUTTON
                     UINT auiState,      // like DrawFrameControl()'s nState  e.g. DFCS_BUTTONCHECK
                     CGridBtnCellBase::CTL_ALIGN aAlign,   // horizontal alignment of control image
                     int aiWidth,        // fixed width of control or 0 for size-to-fit
                     BOOL abIsMbrRadioGrp,   // T=btn is member of a radio group
                     const char* apszText);   // Text to insert centered in button; if NULL no text
    // returns:  success / failure


// for drawing things like buttons and check marks within a cell
//  you can have more than one control per cell
public:
	//##ModelId=4D4223CC0305
    virtual short GetDrawCtlNbr() { return m_sNbrDrawCtls; }
	//##ModelId=4D4223CC0307
    virtual short GetLastCtlClicked() { return m_sLastCtlClicked; }

	//##ModelId=4D4223CC0316
    virtual unsigned char GetDrawCtlNbrMax() { return 0; }

	//##ModelId=4D4223CC0318
    virtual UINT GetDrawCtlType( int /* aiWhich */)
        { ASSERT( FALSE); return 0; }

	//##ModelId=4D4223CC031B
    virtual void SetDrawCtlType( int /* aiWhich */, UINT /* auiType */)
        { ASSERT( FALSE); }

	//##ModelId=4D4223CC031F
    virtual UINT GetDrawCtlState( int /* aiWhich */)
        { ASSERT( FALSE); return 0; }

	//##ModelId=4D4223CC0326
    virtual void SetDrawCtlState( int /* aiWhich */, UINT /* auiState */)
        { ASSERT( FALSE); }

	//##ModelId=4D4223CC032A
    virtual int GetDrawCtlWidth( int /* aiWhich */)
        { ASSERT( FALSE); return -1; }

	//##ModelId=4D4223CC032D
    virtual void SetDrawCtlWidth( int /* aiWhich */, int /* aiWidth */)
        { ASSERT( FALSE); }

	//##ModelId=4D4223CC0334
    virtual CTL_ALIGN GetDrawCtlAlign( int /* aiWhich */)
        { ASSERT( FALSE); return CTL_ALIGN_FENCE; }

	//##ModelId=4D4223CC0337
    virtual void SetDrawCtlAlign( int /* aiWhich */, CTL_ALIGN /* aucAlign */)
        { ASSERT( FALSE); }

	//##ModelId=4D4223CC033B
    virtual const char* GetDrawCtlBtnText( int /* aiWhich */)
        { ASSERT( FALSE); return NULL; }

	//##ModelId=4D4223CC0345
    virtual void SetDrawCtlBtnText( int /* aiWhich */, const char* /* apszText */)
        { ASSERT( FALSE); }

	//##ModelId=4D4223CC0349
    virtual BOOL GetDrawCtlIsMbrRadioGrp( int /* aiWhich */)
        { ASSERT( FALSE); return FALSE; }

	//##ModelId=4D4223CC034C
    virtual void SetDrawCtlIsMbrRadioGrp( int /* aiWhich */, BOOL /* abOn */)
        { ASSERT( FALSE); }


// base Attributes
public:
	//##ModelId=4D4223CC0353
    virtual void SetDrawCtlNbr( short asNbr)
        { ASSERT( (int)asNbr <= GetDrawCtlNbrMax());
          m_sNbrDrawCtls = asNbr; }

	//##ModelId=4D4223CC0356
    virtual void SetText(LPCTSTR szText)
        { if( m_pBtnDataBase) m_pBtnDataBase->SetText( m_iRow, m_iCol, szText); }

	//##ModelId=4D4223CC0359
    virtual void SetImage(int nImage)
        { if( m_pBtnDataBase) m_pBtnDataBase->SetImage(m_iRow, m_iCol, nImage); }

	//##ModelId=4D4223CC0363
    virtual void SetData(LPARAM lParam)
        { if( m_pBtnDataBase) m_pBtnDataBase->SetData(m_iRow, m_iCol, lParam); }

	//##ModelId=4D4223CC0366
    virtual void SetFormat(DWORD nFormat)
        { if( m_pBtnDataBase) m_pBtnDataBase->SetFormat(m_iRow, m_iCol, nFormat); }

	//##ModelId=4D4223CC0369
    virtual void SetTextClr(COLORREF clr)
        { if( m_pBtnDataBase) m_pBtnDataBase->SetTextClr(m_iRow, m_iCol, clr); }

	//##ModelId=4D4223CC036C
    virtual void SetBackClr(COLORREF clr)
        { if( m_pBtnDataBase) m_pBtnDataBase->SetBackClr(m_iRow, m_iCol, clr); }

	//##ModelId=4D4223CC0372
    virtual void SetFont(const LOGFONT* plf)
        { if( m_pBtnDataBase) m_pBtnDataBase->SetFont(m_iRow, m_iCol, plf); }

	//##ModelId=4D4223CC0375
    virtual void SetMargin( UINT nMargin)
        { if( m_pBtnDataBase) m_pBtnDataBase->SetMargin(m_iRow, m_iCol, nMargin); }

	//##ModelId=4D4223CC0378
    virtual void SetCoords( int nRow, int nCol) { m_iRow = nRow; m_iCol = nCol; }
	//##ModelId=4D4223CC037C
    virtual CPoint GetCoords() { return CPoint( m_iCol, m_iRow); }

	//##ModelId=4D4223CC0382
    virtual void SetGrid(CGridCtrl* pGrid)
        { if( m_pBtnDataBase) m_pBtnDataBase->SetGrid( pGrid); }

	//##ModelId=4D4223CC0385
    virtual void SetEditWnd(CWnd* pEditWnd)
        { if( m_pBtnDataBase) m_pBtnDataBase->SetEditWnd(pEditWnd); }


	//##ModelId=4D4223CC0388
    virtual LPCTSTR  GetText() const
        {
            if( m_pBtnDataBase)
                return m_pBtnDataBase->GetText(m_iRow, m_iCol);
            return NULL;
        }

	//##ModelId=4D4223CC038A
    virtual LPCTSTR  GetTipText();// may override TitleTip return

	//##ModelId=4D4223CC0393
    virtual int GetImage() const
        {
            if( m_pBtnDataBase)
                return m_pBtnDataBase->GetImage(m_iRow, m_iCol);
            return -1;
        }

	//##ModelId=4D4223CC0395
    virtual LPARAM GetData() const
        {
            if( m_pBtnDataBase)
                return m_pBtnDataBase->GetData(m_iRow, m_iCol);
            return 0;
        }

	//##ModelId=4D4223CC0397
    virtual DWORD GetFormat() const
        {
            if( m_pBtnDataBase)
                return m_pBtnDataBase->GetFormat(m_iRow, m_iCol);
            return 0;
        }

	//##ModelId=4D4223CC0399
    virtual COLORREF GetTextClr() const
        {
            if( m_pBtnDataBase)
                return m_pBtnDataBase->GetTextClr(m_iRow, m_iCol);
            return CLR_DEFAULT;
        }

	//##ModelId=4D4223CC039B
    virtual COLORREF GetBackClr() const
        {
            if( m_pBtnDataBase)
                return m_pBtnDataBase->GetBackClr(m_iRow, m_iCol);
            return CLR_DEFAULT;
        }

	//##ModelId=4D4223CC039D
    virtual LOGFONT* GetFont() const
        {
            if( m_pBtnDataBase)
                return m_pBtnDataBase->GetFont(m_iRow, m_iCol);
            return NULL;
        }

	//##ModelId=4D4223CC03A1
    virtual CFont* GetFontObject() const
        {
            if( m_pBtnDataBase)
                return m_pBtnDataBase->GetFontObject(m_iRow, m_iCol);
            return NULL;
        }

	//##ModelId=4D4223CC03A3
    virtual UINT GetMargin() const
        {
            if( m_pBtnDataBase)
                return m_pBtnDataBase->GetMargin(m_iRow, m_iCol);
            return 0;
        }

	//##ModelId=4D4223CC03A5
    virtual CGridCtrl* GetGrid() const
        {
            if( m_pBtnDataBase)
                return m_pBtnDataBase->GetGrid();
            return NULL;
        }

	//##ModelId=4D4223CC03A7
    virtual CWnd* GetEditWnd() const
        {
            if( m_pBtnDataBase)
                return m_pBtnDataBase->GetEditWnd();
            return NULL;
        }


	//##ModelId=4D4223CC03A9
    virtual void Reset();
	//##ModelId=4D4223CC03B2
    virtual BOOL IsEditing() const { return m_ucEditing; }

	//##ModelId=4D4223CC03C1
    virtual void operator=(CGridCellBase& cell)
    {
        CGridCellBase::operator=( cell);
    }

// editing cells
public:
	//##ModelId=4D4223CC03C4
    virtual BOOL Draw(CDC* pDC, int nRow, int nCol, CRect rect, BOOL bEraseBkgnd = TRUE);
	//##ModelId=4D4223CC03D0
    BOOL DrawBtnCell(CDC* pDC, int nRow, int nCol, CRect* prect, BOOL bEraseBkgnd);
	//##ModelId=4D4223CD0007
    virtual BOOL GetTextRect( LPRECT pRect);    // i/o:  i=dims of cell rect; o=dims of text rect
	//##ModelId=4D4223CD0017
    virtual BOOL GetTipTextRect( LPRECT pRect); // may override for btns, etc.
	//##ModelId=4D4223CD001A
    virtual CSize GetCellExtent(CDC* pDC);

    // override the following
	//##ModelId=4D4223CD001D
    virtual BOOL PrintCell(CDC* pDC, int nRow, int nCol, CRect rect);

// editing cells
public:
	//##ModelId=4D4223CD002C
    virtual BOOL Edit(  int nRow, int nCol, CRect rect, CPoint point,
                        UINT nID, UINT nChar);
	//##ModelId=4D4223CD0046
    virtual void EndEdit();
protected:
	//##ModelId=4D4223CD0048
    virtual void OnEndEdit();

protected:
	//##ModelId=4D4223CD0055
    virtual void OnClick( CPoint PointCellRelative);
	//##ModelId=4D4223CD0065
    virtual void OnClickDown( CPoint PointCellRelative);
	//##ModelId=4D4223CD0075
    virtual void OnRClick( CPoint PointCellRelative);
	//##ModelId=4D4223CD0084
    virtual void OnDblClick( CPoint PointCellRelative);

protected:
	//##ModelId=4D4223CD0087
    BOOL ClickedCellCtl(  UINT uMsg,      // Command that invoked.  e.g. WM_LBUTTONDOWN
                          int aiWhich);   // zero-based index of image to draw
    // returns:  T=redraw occurred / F=no redraw

	//##ModelId=4D4223CD0096
    BOOL ProcessCtlClick(   UINT uMsg,              // Command that invoked.  e.g. WM_LBUTTONDOWN
                            const CPoint& arPoint); // point to check for hit
    // returns:  T=hit a control / F=no control hit

	//##ModelId=4D4223CD00A4
    int RelPointInCtl(    const CPoint& arPoint);  // Relative point coords
    // returns:  Index of control that this point is within bounds of or -1 if no control matches

	//##ModelId=4D4223CD00A6
    BOOL CalcDrawCtlRects(CRect* apRect,    // returns:  CRects with coordinates
                                            //  last entry has optional leftover rect
                                            //  available for text, etc.
                  int aiNbrRectEntries,     // nbr of Rects in above array
                  const CRect& arRectCell); // cell rectangle to work with

	//##ModelId=4D4223CD00B3
    BOOL HasCellText();
    // returns:  F=auto-size buttons, only

	//##ModelId=4D4223CD00B4
    int HotKeyBtnMatch( char acHotKey); // hot key character
    // returns:  index of button or -1 if no hot key matches

protected:
	//##ModelId=4D4223CD00B6
    short    m_sLastCtlClicked; // what control was last clicked?
	//##ModelId=4D4223CD00C3
    short    m_sNbrDrawCtls;// how many controls?

	//##ModelId=4D4223CD00C4
    int      m_iRow;        // Each cell needs to know position
	//##ModelId=4D4223CD00C5
    int      m_iCol;

	//##ModelId=4D4223CD00C6
    UCHAR    m_ucEditing;   // Cell being edited?

	//##ModelId=4D4223CD00D3
    CBtnDataBase* m_pBtnDataBase;   // contains data common to this instance of the grid as well
                                    //  as a reference to the grid, too

	//##ModelId=4D4223CD00D7
    static CString m_strTipText;    // may have special title tip - note only 1 tip at a time
};


#endif // !defined(AFX_GridBtnCellBase_H__97838AF2_EBD9_11D3_B75D_00C04F6A7AE6__INCLUDED_)
