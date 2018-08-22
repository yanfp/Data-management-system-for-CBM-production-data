/*****************************************************************************
    COPYRIGHT (C) 2000-2001, Ken Bertelson <kbertelson@yahoo.com>


*****************************************************************************/
#if !defined(AFX_BtnDataBase_H__937E4923_EF80_11D3_B75F_00C04F6A7AE6__INCLUDED_)
#define AFX_BtnDataBase_H__937E4923_EF80_11D3_B75F_00C04F6A7AE6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GridCtrl.h"

//##ModelId=4D4223CD020B
class CBtnDataBase
{
public:
	//##ModelId=4D4223CD020C
	CBtnDataBase();
	//##ModelId=4D4223CD020D
	virtual ~CBtnDataBase();

// Attributes
public:
	//##ModelId=4D4223CD020F
    virtual void SetText(int /* nRow */, int /* nCol */, LPCTSTR szText)    { m_strText = szText; }
	//##ModelId=4D4223CD0214
    virtual void SetImage(int /* nRow */, int /* nCol */, int nImage)       { m_nImage = nImage; }
	//##ModelId=4D4223CD021F
    virtual void SetData(int /* nRow */, int /* nCol */, LPARAM lParam)     { m_lParam = lParam; }
	//##ModelId=4D4223CD0224
    virtual void SetFormat(int /* nRow */, int /* nCol */, DWORD nFormat)   { m_nFormat = nFormat; }
	//##ModelId=4D4223CD022B
    virtual void SetTextClr(int /* nRow */, int /* nCol */, COLORREF clr)   { m_crFgClr = clr; }
	//##ModelId=4D4223CD0230
    virtual void SetBackClr(int /* nRow */, int /* nCol */, COLORREF clr)   { m_crBkClr = clr; }
	//##ModelId=4D4223CD0235
    virtual void SetFont(int /* nRow */, int /* nCol */, const LOGFONT* plf)
        {
            delete m_plfFont;
            if (plf != NULL)
            {
                m_plfFont = new LOGFONT;
                if (m_plfFont) 
                    memcpy(m_plfFont, plf, sizeof(LOGFONT)); 
            }
            else
                m_plfFont = NULL;
        }
	//##ModelId=4D4223CD023B
    virtual void SetMargin(int /* nRow */, int /* nCol */, UINT nMargin)    { m_nMargin = nMargin; }
	//##ModelId=4D4223CD0240
    virtual void SetGrid(CGridCtrl* pGrid)                                  { m_pGrid = pGrid; }
	//##ModelId=4D4223CD0243
    virtual void SetEditWnd(CWnd* pEditWnd)                                 { m_pEditWnd = pEditWnd; }

	//##ModelId=4D4223CD024B
    virtual LPCTSTR  GetText(int /* nRow */, int /* nCol */) const
        { return (m_strText.IsEmpty())? _T("") : m_strText; }
	//##ModelId=4D4223CD024F
    virtual int      GetImage(int /* nRow */, int /* nCol */) const      { return m_nImage;  }
	//##ModelId=4D4223CD0253
    virtual LPARAM   GetData(int /* nRow */, int /* nCol */) const       { return m_lParam;  }
	//##ModelId=4D4223CD0257
    virtual DWORD    GetFormat(int /* nRow */, int /* nCol */) const     { return m_nFormat; }
	//##ModelId=4D4223CD025B
    virtual COLORREF GetTextClr(int /* nRow */, int /* nCol */) const    { return m_crFgClr; }
	//##ModelId=4D4223CD025F
    virtual COLORREF GetBackClr(int /* nRow */, int /* nCol */) const    { return m_crBkClr; }
	//##ModelId=4D4223CD0263
    virtual LOGFONT* GetFont(int /* nRow */, int /* nCol */) const
        {
            if (m_plfFont)
                return (LOGFONT*) m_plfFont; 
            else
                return GetGrid()->GetDefaultCell(FALSE, FALSE)->GetFont();
        }
	//##ModelId=4D4223CD0267
    virtual CFont*  GetFontObject(int nRow, int nCol) const
        {
            static CFont Font;
            Font.DeleteObject();
            Font.CreateFontIndirect(GetFont(nRow,nCol));
            return &Font;
        }
	//##ModelId=4D4223CD026B
    virtual UINT     GetMargin(int /* nRow */, int /* nCol */) const     { return m_nMargin; }
	//##ModelId=4D4223CD026F
    virtual CGridCtrl* GetGrid() const                                   { return m_pGrid;   }
	//##ModelId=4D4223CD0271
    virtual CWnd*    GetEditWnd() const                                  { return m_pEditWnd; }

	//##ModelId=4D4223CD0273
    virtual BOOL IsDefaultFont() const       { return (m_plfFont == NULL); }

protected:
	//##ModelId=4D4223CD0278
    CString  m_strText;     // Cell text (or binary data if you wish...)

	//##ModelId=4D4223CD0279
    DWORD    m_nFormat;     // Cell format
	//##ModelId=4D4223CD027A
    int      m_nImage;      // Index of the list view item’s icon
	//##ModelId=4D4223CD027B
    COLORREF m_crBkClr;     // Background colour (or CLR_DEFAULT)
	//##ModelId=4D4223CD0288
    COLORREF m_crFgClr;     // Forground colour (or CLR_DEFAULT)
	//##ModelId=4D4223CD0289
    LPARAM   m_lParam;      // 32-bit value to associate with item
	//##ModelId=4D4223CD028B
    LOGFONT *m_plfFont;     // Cell font
	//##ModelId=4D4223CD0298
    UINT     m_nMargin;     // Internal cell margin

	//##ModelId=4D4223CD029A
    CGridCtrl* m_pGrid;     // Parent grid control
	//##ModelId=4D4223CD029F
    CWnd* m_pEditWnd;
};

#endif // !defined(AFX_BtnDataBase_H__937E4923_EF80_11D3_B75F_00C04F6A7AE6__INCLUDED_)
