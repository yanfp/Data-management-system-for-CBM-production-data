/////////////////////////////////////////////////////////////////////////////
// GridCellBase.h : header file
//
// MFC Grid Control - Grid cell base class header file
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
// For use with CGridCtrl v2.22
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRIDCELLBASE_H__519FA702_722C_11D1_ABBA_00A0243D1382__INCLUDED_)
#define AFX_GRIDCELLBASE_H__519FA702_722C_11D1_ABBA_00A0243D1382__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CGridCtrl;

// Cell states
#define GVIS_FOCUSED            0x0001
#define GVIS_SELECTED           0x0002
#define GVIS_DROPHILITED        0x0004
#define GVIS_READONLY           0x0008
#define GVIS_FIXED              0x0010
#define GVIS_FIXEDROW           0x0020
#define GVIS_FIXEDCOL           0x0040
#define GVIS_MODIFIED           0x0080

// Cell data mask
#define GVIF_TEXT               LVIF_TEXT
#define GVIF_IMAGE              LVIF_IMAGE
#define GVIF_PARAM              LVIF_PARAM
#define GVIF_STATE              LVIF_STATE
#define GVIF_BKCLR              (GVIF_STATE<<1)
#define GVIF_FGCLR              (GVIF_STATE<<2)
#define GVIF_FORMAT             (GVIF_STATE<<3)
#define GVIF_FONT               (GVIF_STATE<<4)
#define GVIF_MARGIN             (GVIF_STATE<<5)
#define GVIF_ALL                (GVIF_TEXT|GVIF_IMAGE|GVIF_PARAM|GVIF_STATE|GVIF_BKCLR|GVIF_FGCLR| \
                                 GVIF_FORMAT|GVIF_FONT|GVIF_MARGIN)

// Used for Get/SetItem calls.
//##ModelId=4D4223CB03B6
typedef struct _GV_ITEM {
    int      row,col;     // Row and Column of item
    UINT     mask;        // Mask for use in getting/setting cell data
    UINT     nState;      // cell state (focus/hilighted etc)
    DWORD    nFormat;     // Format of cell
    int      iImage;      // index of the list view item’s icon
    COLORREF crBkClr;     // Background colour (or CLR_DEFAULT)
    COLORREF crFgClr;     // Forground colour (or CLR_DEFAULT)
    LPARAM   lParam;      // 32-bit value to associate with item
    LOGFONT  lfFont;      // Cell font
    UINT     nMargin;     // Internal cell margin
    CString  strText;     // Text in cell
} GV_ITEM;


// Each cell contains one of these. Fields "row" and "column" are not stored since we
// will usually have acces to them in other ways, and they are an extra 8 bytes per
// cell that is probably unnecessary.

//##ModelId=4D4223CC0017
class CGridCellBase : public CObject
{
    friend class CGridCtrl;
    DECLARE_DYNCREATE(CGridCellBase)

// Construction/Destruction
public:
	//##ModelId=4D4223CC0019
    CGridCellBase();
	//##ModelId=4D4223CC0027
    virtual ~CGridCellBase();

// Attributes
public:
    // can't do pure virtual because of DECLARE_DYNCREATE requirement
    //  use ASSERT() to require that programmer overrides all that should
    //  be pure virtuals

	//##ModelId=4D4223CC0036
    virtual void SetText(LPCTSTR /* szText */)              { ASSERT( FALSE);    }
	//##ModelId=4D4223CC0039
    virtual void SetImage(int /* nImage */)                 { ASSERT( FALSE);    }
	//##ModelId=4D4223CC003C
    virtual void SetData(LPARAM /* lParam */)               { ASSERT( FALSE);    }
	//##ModelId=4D4223CC0046
    virtual void SetState(DWORD nState)                     { m_nState = nState; }
	//##ModelId=4D4223CC0049
    virtual void SetFormat(DWORD /* nFormat */)             { ASSERT( FALSE);    }
	//##ModelId=4D4223CC004C
    virtual void SetTextClr(COLORREF /* clr */)             { ASSERT( FALSE);    }
	//##ModelId=4D4223CC0055
    virtual void SetBackClr(COLORREF /* clr */)             { ASSERT( FALSE);    }
	//##ModelId=4D4223CC0058
    virtual void SetFont(const LOGFONT* /* plf */)          { ASSERT( FALSE);    }
	//##ModelId=4D4223CC005B
    virtual void SetMargin( UINT /* nMargin */)             { ASSERT( FALSE);    }
	//##ModelId=4D4223CC005E
    virtual void SetGrid(CGridCtrl* /* pGrid */)            { ASSERT( FALSE);    }
	//##ModelId=4D4223CC0061
    virtual void SetCoords( int /* nRow */, int /* nCol */) { ASSERT( FALSE);    }

	//##ModelId=4D4223CC0066
    virtual LPCTSTR  GetText() const                        { ASSERT( FALSE); return NULL;  }
	//##ModelId=4D4223CC0068
    virtual LPCTSTR  GetTipText() const                     { return GetText();             } // may override TitleTip return
	//##ModelId=4D4223CC006A
    virtual int      GetImage() const                       { ASSERT( FALSE); return -1;    }
	//##ModelId=4D4223CC006C
    virtual LPARAM   GetData() const                        { ASSERT( FALSE); return 0;     }
	//##ModelId=4D4223CC0075
    virtual DWORD    GetState() const                       { return m_nState;              }
	//##ModelId=4D4223CC0077
    virtual DWORD    GetFormat() const                      { ASSERT( FALSE); return 0;     }
	//##ModelId=4D4223CC0079
    virtual COLORREF GetTextClr() const                     { ASSERT( FALSE); return 0;     }
	//##ModelId=4D4223CC007B
    virtual COLORREF GetBackClr() const                     { ASSERT( FALSE); return 0;     }
	//##ModelId=4D4223CC007D
    virtual LOGFONT* GetFont() const                        { ASSERT( FALSE); return NULL;  }
	//##ModelId=4D4223CC007F
    virtual CFont*   GetFontObject() const                  { ASSERT( FALSE); return NULL;  }
	//##ModelId=4D4223CC0081
    virtual CGridCtrl* GetGrid() const                      { ASSERT( FALSE); return NULL;  }
	//##ModelId=4D4223CC0084
    virtual CWnd*    GetEditWnd() const                     { ASSERT( FALSE); return NULL;  }
	//##ModelId=4D4223CC0086
    virtual UINT     GetMargin() const                      { ASSERT( FALSE); return 0;     }

	//##ModelId=4D4223CC0088
    virtual CGridCellBase* GetDefaultCell() const;

	//##ModelId=4D4223CC0094
    virtual BOOL IsDefaultFont() const                      { ASSERT( FALSE); return FALSE; }
	//##ModelId=4D4223CC0096
    virtual BOOL IsEditing() const                          { ASSERT( FALSE); return FALSE; }
	//##ModelId=4D4223CC0098
    virtual BOOL IsFocused()  const                         { return (m_nState & GVIS_FOCUSED);  }
	//##ModelId=4D4223CC009A
    virtual BOOL IsFixed()    const                         { return (m_nState & GVIS_FIXED);    }
	//##ModelId=4D4223CC009C
    virtual BOOL IsFixedCol() const                         { return (m_nState & GVIS_FIXEDCOL); }
	//##ModelId=4D4223CC009E
    virtual BOOL IsFixedRow() const                         { return (m_nState & GVIS_FIXEDROW); }
	//##ModelId=4D4223CC00A5
    virtual BOOL IsSelected() const                         { return (m_nState & GVIS_SELECTED); }
	//##ModelId=4D4223CC00A7
    virtual BOOL IsReadOnly() const                         { return (m_nState & GVIS_READONLY); }
	//##ModelId=4D4223CC00A9
    virtual BOOL IsModified() const                         { return (m_nState & GVIS_MODIFIED); }
	//##ModelId=4D4223CC00AB
    virtual BOOL IsDropHighlighted() const                  { return (m_nState & GVIS_DROPHILITED); }

// Operators
public:
	//##ModelId=4D4223CC00AD
    virtual void operator=(const CGridCellBase& cell);

// Operations
public:
	//##ModelId=4D4223CC00B3
    virtual void Reset();

	//##ModelId=4D4223CC00C3
    virtual BOOL Draw(CDC* pDC, int nRow, int nCol, CRect rect, BOOL bEraseBkgnd = TRUE);
	//##ModelId=4D4223CC00D2
    virtual BOOL GetTextRect( LPRECT pRect);    // i/o:  i=dims of cell rect; o=dims of text rect
	//##ModelId=4D4223CC00D5
    virtual BOOL GetTipTextRect( LPRECT pRect) { return GetTextRect( pRect); }  // may override for btns, etc.
	//##ModelId=4D4223CC00E2
    virtual CSize GetTextExtent(LPCTSTR str, CDC* pDC = NULL);
	//##ModelId=4D4223CC00E6
    virtual CSize GetCellExtent(CDC* pDC);

    // Editing
	//##ModelId=4D4223CC00E9
    virtual BOOL Edit( int /* nRow */, int /* nCol */, CRect /* rect */, CPoint /* point */, 
                       UINT /* nID */, UINT /* nChar */) { ASSERT( FALSE); return FALSE;}
	//##ModelId=4D4223CC00F4
	virtual BOOL ValidateEdit(LPCTSTR str);
	//##ModelId=4D4223CC00F7
    virtual void EndEdit() {}

    // EFW - Added to print cells properly
	//##ModelId=4D4223CC00F9
    virtual BOOL PrintCell(CDC* pDC, int nRow, int nCol, CRect rect);

    // add additional protected grid members required of cells
	//##ModelId=4D4223CC0101
    LRESULT SendMessageToParent(int nRow, int nCol, int nMessage);

protected:
	//##ModelId=4D4223CC0105
    virtual void OnEndEdit();
	//##ModelId=4D4223CC0107
    virtual void OnMouseEnter();
	//##ModelId=4D4223CC0112
    virtual void OnMouseOver();
	//##ModelId=4D4223CC0114
    virtual void OnMouseLeave();
	//##ModelId=4D4223CC0116
    virtual void OnClick( CPoint PointCellRelative);
	//##ModelId=4D4223CC0123
    virtual void OnClickDown( CPoint PointCellRelative);
	//##ModelId=4D4223CC0126
    virtual void OnRClick( CPoint PointCellRelative);
	//##ModelId=4D4223CC0132
    virtual void OnDblClick( CPoint PointCellRelative);
	//##ModelId=4D4223CC0135
    virtual BOOL OnSetCursor();

protected:
	//##ModelId=4D4223CC0140
    DWORD    m_nState;      // Cell state (selected/focus etc)
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRIDCELLBASE_H__519FA702_722C_11D1_ABBA_00A0243D1382__INCLUDED_)
