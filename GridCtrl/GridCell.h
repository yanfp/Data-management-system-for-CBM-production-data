/////////////////////////////////////////////////////////////////////////////
// GridCell.h : header file
//
// MFC Grid Control - Grid cell class header file
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
// For use with CGridCtrl v2.20
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRIDCELL_H__519FA702_722C_11D1_ABBA_00A0243D1382__INCLUDED_)
#define AFX_GRIDCELL_H__519FA702_722C_11D1_ABBA_00A0243D1382__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CGridCtrl;
#include "GridCellBase.h"

// Each cell contains one of these. Fields "row" and "column" are not stored since we
// will usually have acces to them in other ways, and they are an extra 8 bytes per
// cell that is probably unnecessary.

//##ModelId=4D4223CC015F
class CGridCell : public CGridCellBase
{
    friend class CGridCtrl;
    DECLARE_DYNCREATE(CGridCell)

// Construction/Destruction
public:
	//##ModelId=4D4223CC0161
    CGridCell();
	//##ModelId=4D4223CC0162
    virtual ~CGridCell();

// Attributes
public:
	//##ModelId=4D4223CC016F
    void operator=(const CGridCell& cell);

	//##ModelId=4D4223CC0171
    virtual void  SetText(LPCTSTR szText)        { m_strText = szText;  }                       
	//##ModelId=4D4223CC0174
    virtual void  SetImage(int nImage)           { m_nImage = nImage;   }                        
	//##ModelId=4D4223CC0177
    virtual void  SetData(LPARAM lParam)         { m_lParam = lParam;   }      
	//##ModelId=4D4223CC017A
    virtual void  SetGrid(CGridCtrl* pGrid)      { m_pGrid = pGrid;     }                          
    // virtual void SetState(const DWORD nState);  -  use base class version   
	//##ModelId=4D4223CC017E
    virtual void  SetFormat(DWORD nFormat)       { m_nFormat = nFormat; }                      
	//##ModelId=4D4223CC0181
    virtual void  SetTextClr(COLORREF clr)       { m_crFgClr = clr;     }                          
	//##ModelId=4D4223CC0184
    virtual void  SetBackClr(COLORREF clr)       { m_crBkClr = clr;     }                          
	//##ModelId=4D4223CC018E
    virtual void  SetFont(const LOGFONT* plf);
	//##ModelId=4D4223CC0191
    virtual void  SetMargin(UINT nMargin)        { m_nMargin = nMargin; }
	//##ModelId=4D4223CC0194
    virtual CWnd* GetEditWnd() const             { return m_pEditWnd;   }
	//##ModelId=4D4223CC0196
    virtual void  SetCoords( int /* nRow */, int /* nCol */) {}  // don't need to know the row and
                                                                // column for base implementation

	//##ModelId=4D4223CC019A
    virtual LPCTSTR     GetText() const             { return (m_strText.IsEmpty())? _T("") : m_strText; }
	//##ModelId=4D4223CC019F
    virtual int         GetImage() const            { return m_nImage;  }
	//##ModelId=4D4223CC01A1
    virtual LPARAM      GetData() const             { return m_lParam;  }
	//##ModelId=4D4223CC01A3
    virtual CGridCtrl*  GetGrid() const             { return m_pGrid;   }
    // virtual DWORD    GetState() const - use base class
	//##ModelId=4D4223CC01A5
    virtual DWORD       GetFormat() const;
	//##ModelId=4D4223CC01A7
    virtual COLORREF    GetTextClr() const          { return m_crFgClr; } // TODO: change to use default cell
	//##ModelId=4D4223CC01AE
    virtual COLORREF    GetBackClr() const          { return m_crBkClr; }
	//##ModelId=4D4223CC01B0
    virtual LOGFONT*    GetFont() const;
	//##ModelId=4D4223CC01B2
    virtual CFont*      GetFontObject() const;
	//##ModelId=4D4223CC01B4
    virtual UINT        GetMargin() const;

	//##ModelId=4D4223CC01B6
    virtual BOOL        IsEditing() const           { return m_bEditing; }
	//##ModelId=4D4223CC01B8
    virtual BOOL        IsDefaultFont() const       { return (m_plfFont == NULL); }
	//##ModelId=4D4223CC01BA
    virtual void        Reset();

// editing cells
public:
	//##ModelId=4D4223CC01BE
    virtual BOOL Edit(int nRow, int nCol, CRect rect, CPoint point, UINT nID, UINT nChar);
	//##ModelId=4D4223CC01C6
    virtual void EndEdit();
protected:
	//##ModelId=4D4223CC01C8
    virtual void OnEndEdit();

protected:
	//##ModelId=4D4223CC01CC
    CString    m_strText;      // Cell text (or binary data if you wish...)
	//##ModelId=4D4223CC01CD
    LPARAM     m_lParam;       // 32-bit value to associate with item
	//##ModelId=4D4223CC01CE
    int        m_nImage;       // Index of the list view item’s icon
	//##ModelId=4D4223CC01DC
    DWORD      m_nFormat;
	//##ModelId=4D4223CC01DD
    COLORREF   m_crFgClr;
	//##ModelId=4D4223CC01DE
    COLORREF   m_crBkClr;
	//##ModelId=4D4223CC01E0
    LOGFONT*   m_plfFont;
	//##ModelId=4D4223CC01EC
    UINT       m_nMargin;

	//##ModelId=4D4223CC01ED
    BOOL       m_bEditing;     // Cell being edited?

	//##ModelId=4D4223CC01EF
    CGridCtrl* m_pGrid;        // Parent grid control
	//##ModelId=4D4223CC01FC
    CWnd*      m_pEditWnd;
};

// This class is for storing grid default values. It's a little heavy weight, so
// don't use it in bulk 
//##ModelId=4D4223CC020B
class CGridDefaultCell : public CGridCell
{
    DECLARE_DYNCREATE(CGridDefaultCell)

// Construction/Destruction
public:
	//##ModelId=4D4223CC020D
    CGridDefaultCell();
	//##ModelId=4D4223CC020E
    virtual ~CGridDefaultCell();

public:
	//##ModelId=4D4223CC0210
    virtual DWORD GetStyle() const                      { return m_dwStyle;      }
	//##ModelId=4D4223CC021C
    virtual void  SetStyle(DWORD dwStyle)               { m_dwStyle = dwStyle;   }
	//##ModelId=4D4223CC021F
    virtual int   GetWidth() const                      { return m_Size.cx;      }
	//##ModelId=4D4223CC0221
    virtual int   GetHeight() const                     { return m_Size.cy;      }
	//##ModelId=4D4223CC0223
    virtual void  SetWidth(int nWidth)                  { m_Size.cx = nWidth;    }
	//##ModelId=4D4223CC022A
    virtual void  SetHeight(int nHeight)                { m_Size.cy = nHeight;   }

    // Disable these properties
	//##ModelId=4D4223CC022D
    virtual void     SetData(LPARAM /*lParam*/)             { ASSERT(FALSE);         }      
	//##ModelId=4D4223CC0230
    virtual void     SetState(DWORD /*nState*/)             { ASSERT(FALSE);         }
	//##ModelId=4D4223CC0233
    virtual DWORD    GetState() const                       { return CGridCell::GetState()|GVIS_READONLY; }
	//##ModelId=4D4223CC0235
    virtual void     SetCoords( int /*row*/, int /*col*/)   { ASSERT(FALSE);         }
	//##ModelId=4D4223CC023A
    virtual void     SetFont(const LOGFONT* /*plf*/);
	//##ModelId=4D4223CC023D
    virtual LOGFONT* GetFont() const;   
	//##ModelId=4D4223CC023F
    virtual CFont*   GetFontObject() const;

protected:
	//##ModelId=4D4223CC0241
    CSize m_Size;       // Default Size
	//##ModelId=4D4223CC024A
    CFont m_Font;       // Cached font
	//##ModelId=4D4223CC024E
    DWORD m_dwStyle;    // Cell Style - unused
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRIDCELL_H__519FA702_722C_11D1_ABBA_00A0243D1382__INCLUDED_)
