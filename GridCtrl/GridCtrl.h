/////////////////////////////////////////////////////////////////////////////
// GridCtrl.h : header file
//
// MFC Grid Control - main header
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

#if !defined(AFX_GRIDCTRL_H__519FA702_722C_11D1_ABBA_00A0243D1382__INCLUDED_)
#define AFX_GRIDCTRL_H__519FA702_722C_11D1_ABBA_00A0243D1382__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "CellRange.h"
#include "GridCell.h"
#include <afxtempl.h>


///////////////////////////////////////////////////////////////////////////////////
// Defines - these determine the features (and the final size) of the final code
///////////////////////////////////////////////////////////////////////////////////

//#define GRIDCONTROL_NO_TITLETIPS   // Do not use titletips for cells with large data
//#define GRIDCONTROL_NO_DRAGDROP    // Do not use OLE drag and drop
//#define GRIDCONTROL_NO_CLIPBOARD   // Do not use clipboard routines

#ifdef _WIN32_WCE
#   define GRIDCONTROL_NO_TITLETIPS   // Do not use titletips for cells with large data
#   define GRIDCONTROL_NO_DRAGDROP    // Do not use OLE drag and drop
#   define GRIDCONTROL_NO_CLIPBOARD   // Do not use clipboard routines
#   define GRIDCONTROL_NO_PRINTING    // Do not use printing routines
#   ifdef WCE_NO_PRINTING
#       define _WIN32_WCE_NO_PRINTING
#   endif
#   ifdef WCE_NO_CURSOR
#       define _WIN32_WCE_NO_CURSOR
#   endif
#endif  // _WIN32_WCE

// Use this as the classname when inserting this control as a custom control
// in the MSVC++ dialog editor
#define GRIDCTRL_CLASSNAME    _T("MFCGridCtrl")  // Window class name
#define IDC_INPLACE_CONTROL   8                  // ID of inplace edit controls


///////////////////////////////////////////////////////////////////////////////////
// Conditional includes
///////////////////////////////////////////////////////////////////////////////////

#ifndef GRIDCONTROL_NO_TITLETIPS
#   include "TitleTip.h"
#endif

#ifndef GRIDCONTROL_NO_DRAGDROP
#   include "GridDropTarget.h"
#   undef GRIDCONTROL_NO_CLIPBOARD     // Force clipboard functions on
#endif

#ifndef GRIDCONTROL_NO_CLIPBOARD
#   include <afxole.h>
#endif


///////////////////////////////////////////////////////////////////////////////////
// Helper functions
///////////////////////////////////////////////////////////////////////////////////

// Handy functions
#define IsSHIFTpressed() ( (GetKeyState(VK_SHIFT) & (1 << (sizeof(SHORT)*8-1))) != 0   )
#define IsCTRLpressed()  ( (GetKeyState(VK_CONTROL) & (1 << (sizeof(SHORT)*8-1))) != 0 )

// Backwards compatibility for pre 2.20 grid versions
#define DDX_GridControl(pDX, nIDC, rControl)  DDX_Control(pDX, nIDC, rControl)     


///////////////////////////////////////////////////////////////////////////////////
// Structures
///////////////////////////////////////////////////////////////////////////////////

// This structure sent to Grid's parent in a WM_NOTIFY message
//##ModelId=4D42239C0094
typedef struct tagNM_GRIDVIEW {
    NMHDR hdr;
    int   iRow;
    int   iColumn;
} NM_GRIDVIEW;

// This is sent to the Grid from child in-place edit controls
//##ModelId=4D42239C00A5
typedef struct tagGV_DISPINFO {
    NMHDR   hdr;
    GV_ITEM item;
} GV_DISPINFO;

// This is sent to the Grid from child in-place edit controls
//##ModelId=4D42239C00B4
typedef struct tagGV_CACHEHINT {
    NMHDR      hdr;
    CCellRange range;
} GV_CACHEHINT;

// storage typedef for each row in the grid
//##ModelId=4D42239C00D2
typedef CTypedPtrArray<CObArray, CGridCellBase*> GRID_ROW;

// For virtual mode callback
//##ModelId=4D42239C00E3
typedef BOOL (CALLBACK* GRIDCALLBACK)(GV_DISPINFO *, LPARAM);

///////////////////////////////////////////////////////////////////////////////////
// Defines
///////////////////////////////////////////////////////////////////////////////////

// Grid line/scrollbar selection
#define GVL_NONE                0L      // Neither
#define GVL_HORZ                1L      // Horizontal line or scrollbar
#define GVL_VERT                2L      // Vertical line or scrollbar
#define GVL_BOTH                3L      // Both

// Autosizing option
#define GVS_DEFAULT             0
#define GVS_HEADER              1       // Size using column fixed cells data only
#define GVS_DATA                2       // Size using column non-fixed cells data only
#define GVS_BOTH                3       // Size using column fixed and non-fixed

// Cell Searching options
#define GVNI_FOCUSED            0x0001
#define GVNI_SELECTED           0x0002
#define GVNI_DROPHILITED        0x0004
#define GVNI_READONLY           0x0008
#define GVNI_FIXED              0x0010
#define GVNI_MODIFIED           0x0020

#define GVNI_ABOVE              LVNI_ABOVE
#define GVNI_BELOW              LVNI_BELOW
#define GVNI_TOLEFT             LVNI_TOLEFT
#define GVNI_TORIGHT            LVNI_TORIGHT
#define GVNI_ALL                (LVNI_BELOW|LVNI_TORIGHT|LVNI_TOLEFT)
#define GVNI_AREA               (LVNI_BELOW|LVNI_TORIGHT)

// Hit test values (not yet implemented)
#define GVHT_DATA               0x0000
#define GVHT_TOPLEFT            0x0001
#define GVHT_COLHDR             0x0002
#define GVHT_ROWHDR             0x0004
#define GVHT_COLSIZER           0x0008
#define GVHT_ROWSIZER           0x0010
#define GVHT_LEFT               0x0020
#define GVHT_RIGHT              0x0040
#define GVHT_ABOVE              0x0080
#define GVHT_BELOW              0x0100

// Messages sent to the grid's parent (More will be added in future)
#define GVN_BEGINDRAG           LVN_BEGINDRAG        // LVN_FIRST-9
#define GVN_BEGINLABELEDIT      LVN_BEGINLABELEDIT   // LVN_FIRST-5
#define GVN_BEGINRDRAG          LVN_BEGINRDRAG
#define GVN_COLUMNCLICK         LVN_COLUMNCLICK
#define GVN_DELETEITEM          LVN_DELETEITEM
#define GVN_ENDLABELEDIT        LVN_ENDLABELEDIT     // LVN_FIRST-6
#define GVN_SELCHANGING         LVN_ITEMCHANGING
#define GVN_SELCHANGED          LVN_ITEMCHANGED
#define GVN_GETDISPINFO         LVN_GETDISPINFO 
#define GVN_ODCACHEHINT         LVN_ODCACHEHINT 

class CGridCtrl;

/////////////////////////////////////////////////////////////////////////////
// CGridCtrl window

//##ModelId=4D42239E0130
class CGridCtrl : public CWnd
{
    DECLARE_DYNCREATE(CGridCtrl)
    friend class CGridCell;
    friend class CGridCellBase;

// Construction
public:
	//##ModelId=4D42239E0140
    CGridCtrl(int nRows = 0, int nCols = 0, int nFixedRows = 0, int nFixedCols = 0);

	//##ModelId=4D42239E03D0
    BOOL Create(const RECT& rect, CWnd* parent, UINT nID,
                DWORD dwStyle = WS_CHILD | WS_BORDER | WS_TABSTOP | WS_VISIBLE);

///////////////////////////////////////////////////////////////////////////////////
// Attributes
///////////////////////////////////////////////////////////////////////////////////
public:
	//##ModelId=4D42239F0259
    int  GetRowCount() const                    { return m_nRows; }
	//##ModelId=4D42239F0269
    int  GetColumnCount() const                 { return m_nCols; }
	//##ModelId=4D42239F0278
    int  GetFixedRowCount() const               { return m_nFixedRows; }
	//##ModelId=4D42239F027A
    int  GetFixedColumnCount() const            { return m_nFixedCols; }
	//##ModelId=4D42239F0288
    BOOL SetRowCount(int nRows = 10);
	//##ModelId=4D42239F0372
    BOOL SetColumnCount(int nCols = 10);
	//##ModelId=4D4223A00055
    BOOL SetFixedRowCount(int nFixedRows = 1);
	//##ModelId=4D4223A00140
    BOOL SetFixedColumnCount(int nFixedCols = 1);

	//##ModelId=4D4223A0022A
    int  GetRowHeight(int nRow) const;
	//##ModelId=4D4223A00288
    BOOL SetRowHeight(int row, int height);
	//##ModelId=4D4223A002F5
    int  GetColumnWidth(int nCol) const;
	//##ModelId=4D4223A00363
    BOOL SetColumnWidth(int col, int width);

	//##ModelId=4D4223A003C0
    BOOL GetCellOrigin(int nRow, int nCol, LPPOINT p);
	//##ModelId=4D4223A100D2
    BOOL GetCellOrigin(const CCellID& cell, LPPOINT p);
	//##ModelId=4D4223A101BD
    BOOL GetCellRect(int nRow, int nCol, LPRECT pRect);
	//##ModelId=4D4223A102A7
    BOOL GetCellRect(const CCellID& cell, LPRECT pRect);

	//##ModelId=4D4223A103A1
    BOOL GetTextRect(const CCellID& cell, LPRECT pRect);
	//##ModelId=4D4223A200B3
    BOOL GetTextRect(int nRow, int nCol, LPRECT pRect);

	//##ModelId=4D4223A2019E
    CCellID GetCellFromPt(CPoint point, BOOL bAllowFixedCellCheck = TRUE);

	//##ModelId=4D4223A202C6
    int  GetFixedRowHeight() const;
	//##ModelId=4D4223A20334
    int  GetFixedColumnWidth() const;
	//##ModelId=4D4223A20392
    long GetVirtualWidth() const;
	//##ModelId=4D4223A30027
    long GetVirtualHeight() const;

	//##ModelId=4D4223A30094
    CSize GetTextExtent(int nRow, int nCol, LPCTSTR str);
    // EFW - Get extent of current text in cell
	//##ModelId=4D4223A30098
    inline CSize GetCellTextExtent(int nRow, int nCol)  { return GetTextExtent(nRow, nCol, GetItemText(nRow,nCol)); }

	//##ModelId=4D4223A300A6
    void     SetGridBkColor(COLORREF clr)         { m_crGridBkColour = clr;           }
	//##ModelId=4D4223A300B3
    COLORREF GetGridBkColor() const               { return m_crGridBkColour;          }
	//##ModelId=4D4223A300C3
    void     SetGridLineColor(COLORREF clr)       { m_crGridLineColour = clr;         }
	//##ModelId=4D4223A300C5
    COLORREF GetGridLineColor() const             { return m_crGridLineColour;        }

	//##ModelId=4D4223A300D3
	void	 SetTitleTipBackClr(COLORREF clr = CLR_DEFAULT) { m_crTTipBackClr = clr;  }
	//##ModelId=4D4223A300E2
	COLORREF GetTitleTipBackClr()				            { return m_crTTipBackClr; }
	//##ModelId=4D4223A300F2
	void	 SetTitleTipTextClr(COLORREF clr = CLR_DEFAULT) { m_crTTipTextClr = clr;  }
	//##ModelId=4D4223A300F4
	COLORREF GetTitleTipTextClr()				            { return m_crTTipTextClr; }

    // ***************************************************************************** //
    // These have been deprecated. Use GetDefaultCell and then set the colors
	//##ModelId=4D4223A30101
    void     SetTextColor(COLORREF clr)      { m_cellDefault.SetTextClr(clr);        }
	//##ModelId=4D4223A30111
    COLORREF GetTextColor()                  { return m_cellDefault.GetTextClr();    }
	//##ModelId=4D4223A30112
    void     SetTextBkColor(COLORREF clr)    { m_cellDefault.SetBackClr(clr);        }
	//##ModelId=4D4223A30121
    COLORREF GetTextBkColor()                { return m_cellDefault.GetBackClr();    }
	//##ModelId=4D4223A30130
    void     SetFixedTextColor(COLORREF clr) { m_cellFixedRowDef.SetTextClr(clr); 
                                               m_cellFixedColDef.SetTextClr(clr); 
                                               m_cellFixedRowColDef.SetTextClr(clr); }
	//##ModelId=4D4223A30132
    COLORREF GetFixedTextColor() const       { return m_cellFixedRowDef.GetTextClr(); }
	//##ModelId=4D4223A30140
    void     SetFixedBkColor(COLORREF clr)   { m_cellFixedRowDef.SetBackClr(clr); 
                                               m_cellFixedColDef.SetBackClr(clr); 
                                               m_cellFixedRowColDef.SetBackClr(clr); }
	//##ModelId=4D4223A3014F
    COLORREF GetFixedBkColor() const         { return m_cellFixedRowDef.GetBackClr(); }
	//##ModelId=4D4223A30151
    void     SetGridColor(COLORREF clr)      { SetGridLineColor(clr);                }
	//##ModelId=4D4223A30160
    COLORREF GetGridColor()                  { return GetGridLineColor();            }
	//##ModelId=4D4223A3016F
    void     SetBkColor(COLORREF clr)        { SetGridBkColor(clr);                  }
	//##ModelId=4D4223A30171
    COLORREF GetBkColor()                    { return GetGridBkColor();              }

	//##ModelId=4D4223A3017E
    void     SetDefCellMargin( int nMargin)  { m_cellDefault.SetMargin(nMargin); 
                                               m_cellFixedRowDef.SetMargin(nMargin); 
                                               m_cellFixedColDef.SetMargin(nMargin); 
                                               m_cellFixedRowColDef.SetMargin(nMargin); }
	//##ModelId=4D4223A3018E
    int      GetDefCellMargin() const        { return m_cellDefault.GetMargin();     }

	//##ModelId=4D4223A30190
    int      GetDefCellHeight() const        { return m_cellDefault.GetHeight();     }
	//##ModelId=4D4223A3019F
    void     SetDefCellHeight(int nHeight)   { m_cellDefault.SetHeight(nHeight); 
                                               m_cellFixedRowDef.SetHeight(nHeight); 
                                               m_cellFixedColDef.SetHeight(nHeight); 
                                               m_cellFixedRowColDef.SetHeight(nHeight); }
	//##ModelId=4D4223A301AD
    int      GetDefCellWidth() const         { return m_cellDefault.GetWidth();     }
	//##ModelId=4D4223A301BD
    void     SetDefCellWidth(int nWidth)     { m_cellDefault.SetWidth(nWidth); 
                                               m_cellFixedRowDef.SetWidth(nWidth); 
                                               m_cellFixedColDef.SetWidth(nWidth); 
                                               m_cellFixedRowColDef.SetWidth(nWidth); }

    // ***************************************************************************** //

	//##ModelId=4D4223A301BF
    int GetSelectedCount() const                  { return m_SelectedCellMap.GetCount(); }

	//##ModelId=4D4223A301CC
    CCellID SetFocusCell(CCellID cell);
	//##ModelId=4D4223A30353
    CCellID SetFocusCell(int nRow, int nCol);
	//##ModelId=4D4223A400F2
    CCellID GetFocusCell() const                  { return m_idCurrentCell;           }


	//##ModelId=4D4223A40101
    void SetVirtualMode(BOOL bVirtual);
	//##ModelId=4D4223A4014F
    BOOL GetVirtualMode() const                   { return m_bVirtualMode;            }
	//##ModelId=4D4223A40151
    void SetCallbackFunc(GRIDCALLBACK pCallback, 
                         LPARAM lParam)           { m_pfnCallback = pCallback; m_lParam = lParam; }
	//##ModelId=4D4223A4015F
    GRIDCALLBACK GetCallbackFunc()                { return m_pfnCallback;             }


	//##ModelId=4D4223A40160
    void SetImageList(CImageList* pList)          { m_pImageList = pList;             }
	//##ModelId=4D4223A4016F
    CImageList* GetImageList() const              { return m_pImageList;              }

	//##ModelId=4D4223A40171
    void SetGridLines(int nWhichLines = GVL_BOTH);
	//##ModelId=4D4223A401BD
    int  GetGridLines() const                     { return m_nGridLines;              }
	//##ModelId=4D4223A401CC
    void SetEditable(BOOL bEditable = TRUE)       { m_bEditable = bEditable;          }
	//##ModelId=4D4223A401CE
    BOOL IsEditable() const                       { return m_bEditable;               }
	//##ModelId=4D4223A401DC
    void SetListMode(BOOL bEnableListMode = TRUE);
	//##ModelId=4D4223A4021B
    BOOL GetListMode() const                      { return m_bListMode;               }
	//##ModelId=4D4223A4022B
    void SetSingleRowSelection(BOOL bSing = TRUE) { m_bSingleRowSelection = bSing;    }
	//##ModelId=4D4223A4023A
    BOOL GetSingleRowSelection()                  { return m_bSingleRowSelection & m_bListMode; }
	//##ModelId=4D4223A4023B
    void SetSingleColSelection(BOOL bSing = TRUE) { m_bSingleColSelection = bSing;    }
	//##ModelId=4D4223A40249
    BOOL GetSingleColSelection()                  { return m_bSingleColSelection;     }
	//##ModelId=4D4223A4024A
    void EnableSelection(BOOL bEnable = TRUE)     { ResetSelectedRange(); m_bEnableSelection = bEnable; ResetSelectedRange(); }
	//##ModelId=4D4223A40259
    BOOL IsSelectable() const                     { return m_bEnableSelection;        }
	//##ModelId=4D4223A4025B
    void SetFixedColumnSelection(BOOL bSelect)    { m_bFixedColumnSelection = bSelect;}
	//##ModelId=4D4223A40269
    BOOL GetFixedColumnSelection()                { return m_bFixedColumnSelection;   }
	//##ModelId=4D4223A4026A
    void SetFixedRowSelection(BOOL bSelect)       { m_bFixedRowSelection = bSelect;   }
	//##ModelId=4D4223A40278
    BOOL GetFixedRowSelection()                   { return m_bFixedRowSelection;      }
	//##ModelId=4D4223A40279
    void EnableDragAndDrop(BOOL bAllow = TRUE)    { m_bAllowDragAndDrop = bAllow;     }
	//##ModelId=4D4223A40289
    BOOL GetDragAndDrop() const                   { return m_bAllowDragAndDrop;       }
	//##ModelId=4D4223A40298
    void SetRowResize(BOOL bResize = TRUE)        { m_bAllowRowResize = bResize;      }
	//##ModelId=4D4223A4029A
    BOOL GetRowResize() const                     { return m_bAllowRowResize;         }
	//##ModelId=4D4223A402A7
    void SetColumnResize(BOOL bResize = TRUE)     { m_bAllowColumnResize = bResize;   }
	//##ModelId=4D4223A402A9
    BOOL GetColumnResize() const                  { return m_bAllowColumnResize;      }
	//##ModelId=4D4223A402B7
    void SetHeaderSort(BOOL bSortOnClick = TRUE)  { m_bSortOnClick = bSortOnClick;    }
	//##ModelId=4D4223A402B9
    BOOL GetHeaderSort() const                    { return m_bSortOnClick;            }
	//##ModelId=4D4223A402C7
    void SetHandleTabKey(BOOL bHandleTab = TRUE)  { m_bHandleTabKey = bHandleTab;     }
	//##ModelId=4D4223A402D6
    BOOL GetHandleTabKey() const                  { return m_bHandleTabKey;           }
	//##ModelId=4D4223A402D8
    void SetDoubleBuffering(BOOL bBuffer = TRUE)  { m_bDoubleBuffer = bBuffer;        }
	//##ModelId=4D4223A402E7
    BOOL GetDoubleBuffering() const               { return m_bDoubleBuffer;           }
	//##ModelId=4D4223A402F5
    void EnableTitleTips(BOOL bEnable = TRUE)     { m_bTitleTips = bEnable;           }
	//##ModelId=4D4223A402F7
    BOOL GetTitleTips()                           { return m_bTitleTips;              }
	//##ModelId=4D4223A40305
    void SetSortColumn(int nCol);
	//##ModelId=4D4223A40353
    int  GetSortColumn() const                    { return m_nSortColumn;             }
	//##ModelId=4D4223A40363
    void SetSortAscending(BOOL bAscending)        { m_bAscending = bAscending;        }
	//##ModelId=4D4223A40372
    BOOL GetSortAscending() const                 { return m_bAscending;              }
	//##ModelId=4D4223A40374
    void SetTrackFocusCell(BOOL bTrack)           { m_bTrackFocusCell = bTrack;       }
	//##ModelId=4D4223A40383
    BOOL GetTrackFocusCell()                      { return m_bTrackFocusCell;         }
	//##ModelId=4D4223A40392
    void SetFrameFocusCell(BOOL bFrame)           { m_bFrameFocus = bFrame;           }
	//##ModelId=4D4223A40394
    BOOL GetFrameFocusCell()                      { return m_bFrameFocus;             }
	//##ModelId=4D4223A403A1
    void SetAutoSizeStyle(int nStyle = GVS_BOTH)  { m_nAutoSizeColumnStyle = nStyle;  }
	//##ModelId=4D4223A403A3
    int  GetAutoSizeStyle()                       { return m_nAutoSizeColumnStyle; }

	//##ModelId=4D4223A403B1
    void EnableHiddenColUnhide(BOOL bEnable = TRUE){ m_bHiddenColUnhide = bEnable;    }
	//##ModelId=4D4223A403B3
    BOOL GetHiddenColUnhide()                     { return m_bHiddenColUnhide;        }
	//##ModelId=4D4223A403C0
    void EnableHiddenRowUnhide(BOOL bEnable = TRUE){ m_bHiddenRowUnhide = bEnable;    }
	//##ModelId=4D4223A403C2
    BOOL GetHiddenRowUnhide()                     { return m_bHiddenRowUnhide;        }

	//##ModelId=4D4223A403D0
    void EnableColumnHide(BOOL bEnable = TRUE)    { m_bAllowColHide = bEnable;        }
	//##ModelId=4D4223A403E0
    BOOL GetColumnHide()                          { return m_bAllowColHide;           }
	//##ModelId=4D4223A403E1
    void EnableRowHide(BOOL bEnable = TRUE)       { m_bAllowRowHide = bEnable;        }
	//##ModelId=4D4223A50007
    BOOL GetRowHide()                             { return m_bAllowRowHide;           }

///////////////////////////////////////////////////////////////////////////////////
// default Grid cells. Use these for setting default values such as colors and fonts
///////////////////////////////////////////////////////////////////////////////////
public:
	//##ModelId=4D4223A50008
    CGridCellBase* GetDefaultCell(BOOL bFixedRow, BOOL bFixedCol) const;

///////////////////////////////////////////////////////////////////////////////////
// Grid cell Attributes
///////////////////////////////////////////////////////////////////////////////////
public:
	//##ModelId=4D4223A50018
    CGridCellBase* GetCell(int nRow, int nCol) const;   // Get the actual cell!

	//##ModelId=4D4223A50027
    void SetModified(BOOL bModified = TRUE, int nRow = -1, int nCol = -1);
	//##ModelId=4D4223A50084
    BOOL GetModified(int nRow = -1, int nCol = -1);
	//##ModelId=4D4223A500E2
    BOOL IsCellFixed(int nRow, int nCol);

	//##ModelId=4D4223A50121
    BOOL   SetItem(const GV_ITEM* pItem);
	//##ModelId=4D4223A5019E
    BOOL   GetItem(GV_ITEM* pItem);
	//##ModelId=4D4223A5022A
    BOOL   SetItemText(int nRow, int nCol, LPCTSTR str);
    // The following was virtual. If you want to override, use 
    //  CGridCellBase-derived class's GetText() to accomplish same thing
	//##ModelId=4D4223A502B7
    CString GetItemText(int nRow, int nCol) const;

    // EFW - 06/13/99 - Added to support printf-style formatting codes.
    // Also supports use with a string resource ID
#if !defined(_WIN32_WCE) || (_WIN32_WCE >= 210)
	//##ModelId=4D4223A502C6
    BOOL   SetItemTextFmt(int nRow, int nCol, LPCTSTR szFmt, ...);
	//##ModelId=4D4223A50343
    BOOL   SetItemTextFmtID(int nRow, int nCol, UINT nID, ...);
#endif

	//##ModelId=4D4223A503B1
    BOOL   SetItemData(int nRow, int nCol, LPARAM lParam);
	//##ModelId=4D4223A60055
    LPARAM GetItemData(int nRow, int nCol) const;
	//##ModelId=4D4223A600E2
    BOOL   SetItemImage(int nRow, int nCol, int iImage);
	//##ModelId=4D4223A6015F
    int    GetItemImage(int nRow, int nCol) const;
	//##ModelId=4D4223A601DC
    BOOL   SetItemState(int nRow, int nCol, UINT state);
	//##ModelId=4D4223A60259
    UINT   GetItemState(int nRow, int nCol) const;
	//##ModelId=4D4223A602C6
    BOOL   SetItemFormat(int nRow, int nCol, UINT nFormat);
	//##ModelId=4D4223A60334
    UINT   GetItemFormat(int nRow, int nCol) const;
	//##ModelId=4D4223A603B1
    BOOL   SetItemBkColour(int nRow, int nCol, COLORREF cr = CLR_DEFAULT);
	//##ModelId=4D4223A70036
    COLORREF GetItemBkColour(int nRow, int nCol) const;
	//##ModelId=4D4223A700A4
    BOOL   SetItemFgColour(int nRow, int nCol, COLORREF cr = CLR_DEFAULT);
	//##ModelId=4D4223A70111
    COLORREF GetItemFgColour(int nRow, int nCol) const;
	//##ModelId=4D4223A7017E
    BOOL SetItemFont(int nRow, int nCol, const LOGFONT* lf);
	//##ModelId=4D4223A701EC
    const LOGFONT* GetItemFont(int nRow, int nCol);

	//##ModelId=4D4223A70249
    BOOL IsItemEditing(int nRow, int nCol);

	//##ModelId=4D4223A702B7
    BOOL SetCellType(int nRow, int nCol, CRuntimeClass* pRuntimeClass);
	//##ModelId=4D4223A70372
    BOOL SetDefaultCellType( CRuntimeClass* pRuntimeClass);

///////////////////////////////////////////////////////////////////////////////////
// Operations
///////////////////////////////////////////////////////////////////////////////////
public:
	//##ModelId=4D4223A80036
    int  InsertColumn(LPCTSTR strHeading, UINT nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE,
                      int nColumn = -1);
	//##ModelId=4D4223A800F2
    int  InsertRow(LPCTSTR strHeading, int nRow = -1);
	//##ModelId=4D4223A801BD
    BOOL DeleteColumn(int nColumn);
	//##ModelId=4D4223A80269
    BOOL DeleteRow(int nRow);
	//##ModelId=4D4223A80305
    BOOL DeleteNonFixedRows();
	//##ModelId=4D4223A803A1
    BOOL DeleteAllItems();

	//##ModelId=4D4223A90055
	void ClearCells(CCellRange Selection);

	//##ModelId=4D4223A901BD
    BOOL AutoSizeRow(int nRow, BOOL bResetScroll = TRUE);
	//##ModelId=4D4223A9021B
    BOOL AutoSizeColumn(int nCol, UINT nAutoSizeStyle = GVS_DEFAULT, BOOL bResetScroll = TRUE);
	//##ModelId=4D4223A90278
    void AutoSizeRows();
	//##ModelId=4D4223A902C6
    void AutoSizeColumns(UINT nAutoSizeStyle = GVS_DEFAULT);
	//##ModelId=4D4223A90324
    void AutoSize(UINT nAutoSizeStyle = GVS_DEFAULT);
	//##ModelId=4D4223A90372
    void ExpandColumnsToFit(BOOL bExpandFixed = TRUE);
	//##ModelId=4D4223A903C0
    void ExpandLastColumn();
	//##ModelId=4D4223AA0027
    void ExpandRowsToFit(BOOL bExpandFixed = TRUE);
	//##ModelId=4D4223AA0075
    void ExpandToFit(BOOL bExpandFixed = TRUE);

	//##ModelId=4D4223AA00C3
    void Refresh();
	//##ModelId=4D4223AA0111
    void AutoFill();   // Fill grid with blank cells

	//##ModelId=4D4223AA019E
    void EnsureVisible(CCellID &cell)       { EnsureVisible(cell.row, cell.col); }
	//##ModelId=4D4223AA01AD
    void EnsureVisible(int nRow, int nCol);
	//##ModelId=4D4223AA01EC
    BOOL IsCellVisible(int nRow, int nCol);
	//##ModelId=4D4223AA022A
    BOOL IsCellVisible(CCellID cell);
	//##ModelId=4D4223AA0269
    BOOL IsCellEditable(int nRow, int nCol) const;
	//##ModelId=4D4223AA02A7
    BOOL IsCellEditable(CCellID &cell) const;
	//##ModelId=4D4223AA02E6
    BOOL IsCellSelected(int nRow, int nCol) const;
	//##ModelId=4D4223AA0324
    BOOL IsCellSelected(CCellID &cell) const;

    // SetRedraw stops/starts redraws on things like changing the # rows/columns
    // and autosizing, but not for user-intervention such as resizes
	//##ModelId=4D4223AA0363
    void SetRedraw(BOOL bAllowDraw, BOOL bResetScrollBars = FALSE);
	//##ModelId=4D4223AB0111
    BOOL RedrawCell(int nRow, int nCol, CDC* pDC = NULL);
	//##ModelId=4D4223AB02A7
    BOOL RedrawCell(const CCellID& cell, CDC* pDC = NULL);
	//##ModelId=4D4223AC0055
    BOOL RedrawRow(int row);
	//##ModelId=4D4223AC01EC
    BOOL RedrawColumn(int col);

#ifndef _WIN32_WCE
	//##ModelId=4D4223AC0372
    BOOL Save(LPCTSTR filename);
	//##ModelId=4D4223AC0374
    BOOL Load(LPCTSTR filename);
#endif

///////////////////////////////////////////////////////////////////////////////////
// Cell Ranges
///////////////////////////////////////////////////////////////////////////////////
 public:
	//##ModelId=4D4223AC0383
    CCellRange GetCellRange() const;
	//##ModelId=4D4223AD0094
    CCellRange GetSelectedCellRange() const;
	//##ModelId=4D4223AD018E
    void SetSelectedRange(const CCellRange& Range, BOOL bForceRepaint = FALSE, BOOL bSelectCells = TRUE);
	//##ModelId=4D4223AD0305
    void SetSelectedRange(int nMinRow, int nMinCol, int nMaxRow, int nMaxCol,
                          BOOL bForceRepaint = FALSE, BOOL bSelectCells = TRUE);
	//##ModelId=4D4223AE00A4
    BOOL IsValid(int nRow, int nCol) const;
	//##ModelId=4D4223AE023A
    BOOL IsValid(const CCellID& cell) const;
	//##ModelId=4D4223AE03E0
    BOOL IsValid(const CCellRange& range) const;

///////////////////////////////////////////////////////////////////////////////////
// Clipboard, drag and drop, and cut n' paste operations
///////////////////////////////////////////////////////////////////////////////////
#ifndef GRIDCONTROL_NO_CLIPBOARD
	//##ModelId=4D4223AF018E
    virtual void CutSelectedText();
	//##ModelId=4D4223AF02E6
    virtual COleDataSource* CopyTextFromGrid();
	//##ModelId=4D4223B00055
    virtual BOOL PasteTextToGrid(CCellID cell, COleDataObject* pDataObject);
#endif

#ifndef GRIDCONTROL_NO_DRAGDROP
 public:
	//##ModelId=4D4223B0019E
    void OnBeginDrag();
	//##ModelId=4D4223B002D6
    DROPEFFECT OnDragEnter(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
	//##ModelId=4D4223B10017
    DROPEFFECT OnDragOver(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
	//##ModelId=4D4223B1015F
    void OnDragLeave();
	//##ModelId=4D4223B10288
    BOOL OnDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point);
#endif

#ifndef GRIDCONTROL_NO_CLIPBOARD
	//##ModelId=4D4223B103B1
    virtual void OnEditCut();
	//##ModelId=4D4223B200F2
    virtual void OnEditCopy();
	//##ModelId=4D4223B2022A
    virtual void OnEditPaste();
#endif
	//##ModelId=4D4223B20343
    virtual void OnEditSelectAll();

///////////////////////////////////////////////////////////////////////////////////
// Misc.
///////////////////////////////////////////////////////////////////////////////////
public:
	//##ModelId=4D4223B30084
    CCellID GetNextItem(CCellID& cell, int nFlags) const;

	//##ModelId=4D4223B30121
	BOOL SortItems(int nCol, BOOL bAscending, LPARAM data = 0);
	//##ModelId=4D4223B301AD
    BOOL SortTextItems(int nCol, BOOL bAscending, LPARAM data = 0);
	//##ModelId=4D4223B3023A
    BOOL SortItems(PFNLVCOMPARE pfnCompare, int nCol, BOOL bAscending, LPARAM data = 0);

	//##ModelId=4D4223B303B1
	void SetCompareFunction(PFNLVCOMPARE pfnCompare);

	// in-built sort functions
	//##ModelId=4D4223B40055
	static int CALLBACK pfnCellTextCompare(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
	//##ModelId=4D4223B400E2
	static int CALLBACK pfnCellNumericCompare(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);

///////////////////////////////////////////////////////////////////////////////////
// Printing
///////////////////////////////////////////////////////////////////////////////////
#if !defined(_WIN32_WCE_NO_PRINTING) && !defined(GRIDCONTROL_NO_PRINTING)
public:
	//##ModelId=4D4223B4016F
    void Print();

    // EFW - New printing support functions
	//##ModelId=4D4223B4017E
    void EnableWysiwygPrinting(BOOL bEnable = TRUE) { m_bWysiwygPrinting = bEnable;     }
	//##ModelId=4D4223B40180
    BOOL GetWysiwygPrinting()                       { return m_bWysiwygPrinting;        }

	//##ModelId=4D4223B40181
    void SetShadedPrintOut(BOOL bEnable = TRUE)     {   m_bShadedPrintOut = bEnable;    }
	//##ModelId=4D4223B4018E
    BOOL GetShadedPrintOut(void)                    {   return m_bShadedPrintOut;       }

    // Use -1 to have it keep the existing value
	//##ModelId=4D4223B40190
    void SetPrintMarginInfo(int nHeaderHeight, int nFooterHeight,
        int nLeftMargin, int nRightMargin, int nTopMargin,
        int nBottomMargin, int nGap);

	//##ModelId=4D4223B401AD
    void GetPrintMarginInfo(int &nHeaderHeight, int &nFooterHeight,
        int &nLeftMargin, int &nRightMargin, int &nTopMargin,
        int &nBottomMargin, int &nGap);

///////////////////////////////////////////////////////////////////////////////////
// Printing overrides for derived classes
///////////////////////////////////////////////////////////////////////////////////
public:
	//##ModelId=4D4223B401BD
    virtual void OnBeginPrinting(CDC *pDC, CPrintInfo *pInfo);
	//##ModelId=4D4223B401CC
    virtual void OnPrint(CDC *pDC, CPrintInfo *pInfo);
	//##ModelId=4D4223B401DD
    virtual void OnEndPrinting(CDC *pDC, CPrintInfo *pInfo);

#endif // #if !defined(_WIN32_WCE_NO_PRINTING) && !defined(GRIDCONTROL_NO_PRINTING)

// Implementation
public:
	//##ModelId=4D4223B401EC
    virtual ~CGridCtrl();

protected:
	//##ModelId=4D4223B50094
    BOOL RegisterWindowClass();
	//##ModelId=4D4223B50315
    BOOL Initialise();
	//##ModelId=4D4223B6019E
    void SetupDefaultCells();

	//##ModelId=4D4223B70027
    LRESULT SendMessageToParent(int nRow, int nCol, int nMessage) const;
	//##ModelId=4D4223B70298
    LRESULT SendDisplayRequestToParent(GV_DISPINFO* pDisplayInfo) const;
	//##ModelId=4D4223B80121
    LRESULT SendCacheHintToParent(const CCellRange& range) const;

	//##ModelId=4D4223B80382
    BOOL InvalidateCellRect(const int row, const int col);
	//##ModelId=4D4223B803B1
    BOOL InvalidateCellRect(const CCellID& cell);
	//##ModelId=4D4223B90007
    BOOL InvalidateCellRect(const CCellRange& cellRange);
	//##ModelId=4D4223B90036
    void EraseBkgnd(CDC* pDC);

	//##ModelId=4D4223B90288
    BOOL GetCellRangeRect(const CCellRange& cellRange, LPRECT lpRect);

	//##ModelId=4D4223B90372
    BOOL SetCell(int nRow, int nCol, CGridCellBase* pCell);

	//##ModelId=4D4223B90376
    int  SetMouseMode(int nMode) { int nOldMode = m_MouseMode; m_MouseMode = nMode; return nOldMode; }
	//##ModelId=4D4223B90378
    int  GetMouseMode() const    { return m_MouseMode; }

	//##ModelId=4D4223B90383
    BOOL MouseOverRowResizeArea(CPoint& point);
	//##ModelId=4D4223BA00B3
    BOOL MouseOverColumnResizeArea(CPoint& point);

	//##ModelId=4D4223BA01CC
    CCellID GetTopleftNonFixedCell(BOOL bForceRecalculation = FALSE);
	//##ModelId=4D4223BA02D6
    CCellRange GetUnobstructedNonFixedCellRange(BOOL bForceRecalculation = FALSE);
	//##ModelId=4D4223BA03E0
    CCellRange GetVisibleNonFixedCellRange(LPRECT pRect = NULL, BOOL bForceRecalculation = FALSE);

	//##ModelId=4D4223BB0101
    BOOL IsVisibleVScroll() { return ( (m_nBarState & GVL_VERT) > 0); } 
	//##ModelId=4D4223BB0102
    BOOL IsVisibleHScroll() { return ( (m_nBarState & GVL_HORZ) > 0); }
	//##ModelId=4D4223BB0103
    void ResetSelectedRange();
	//##ModelId=4D4223BB020B
    void ResetScrollBars();
	//##ModelId=4D4223BB02F5
    void EnableScrollBars(int nBar, BOOL bEnable = TRUE);
	//##ModelId=4D4223BC0007
    int  GetScrollPos32(int nBar, BOOL bGetTrackPos = FALSE);
	//##ModelId=4D4223BC0111
    BOOL SetScrollPos32(int nBar, int nPos, BOOL bRedraw = TRUE);

	//##ModelId=4D4223BC020B
    BOOL SortTextItems(int nCol, BOOL bAscending, int low, int high);
	//##ModelId=4D4223BC0210
    BOOL SortItems(PFNLVCOMPARE pfnCompare, int nCol, BOOL bAscending, LPARAM data,
                   int low, int high);

	//##ModelId=4D4223BC0298
    CPoint GetPointClicked(int nRow, int nCol, const CPoint& point);

	//##ModelId=4D4223BC02C6
	void ValidateAndModifyCellContents(int nRow, int nCol, LPCTSTR strText);

// Overrrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CGridCtrl)
    protected:
	//##ModelId=4D4223BD0036
    virtual void PreSubclassWindow();
    //}}AFX_VIRTUAL

protected:
#if !defined(_WIN32_WCE_NO_PRINTING) && !defined(GRIDCONTROL_NO_PRINTING)
    // Printing
	//##ModelId=4D4223BD02A7
	virtual void PrintFixedRowCells(int nStartColumn, int nStopColumn, int& row, CRect& rect,
                                    CDC *pDC, BOOL& bFirst);
	//##ModelId=4D4223BD02BA
    virtual void PrintColumnHeadings(CDC *pDC, CPrintInfo *pInfo);
	//##ModelId=4D4223BD02C6
    virtual void PrintHeader(CDC *pDC, CPrintInfo *pInfo);
	//##ModelId=4D4223BD02CA
    virtual void PrintFooter(CDC *pDC, CPrintInfo *pInfo);
	//##ModelId=4D4223BD02D9
    virtual void PrintRowButtons(CDC *pDC, CPrintInfo* /*pInfo*/);
#endif

#ifndef GRIDCONTROL_NO_DRAGDROP
    // Drag n' drop
	//##ModelId=4D4223BD02E6
    virtual CImageList* CreateDragImage(CPoint *pHotSpot);    // no longer necessary
#endif

    // Mouse Clicks
	//##ModelId=4D4223BD02E9
    virtual void  OnFixedColumnClick(CCellID& cell);
	//##ModelId=4D4223BD02EC
    virtual void  OnFixedRowClick(CCellID& cell);

    // Editing
	//##ModelId=4D4223BD02F6
    virtual void  OnEditCell(int nRow, int nCol, CPoint point, UINT nChar);
	//##ModelId=4D4223BD0305
    virtual void  OnEndEditCell(int nRow, int nCol, CString str);
	//##ModelId=4D4223BD030A
	virtual BOOL  ValidateEdit(int nRow, int nCol, LPCTSTR str);
	//##ModelId=4D4223BD0315
    virtual void  EndEditing();

    // Drawing
	//##ModelId=4D4223BD0317
    virtual void  OnDraw(CDC* pDC);

    // CGridCellBase Creation and Cleanup
	//##ModelId=4D4223BE00F2
    virtual CGridCellBase* CreateCell(int nRow, int nCol);
	//##ModelId=4D4223BE019E
    virtual void DestroyCell(int nRow, int nCol);

// Attributes
protected:
    // General attributes
    COLORREF    m_crFixedTextColour, m_crFixedBkColour;
    COLORREF    m_crGridBkColour, m_crGridLineColour;
    COLORREF    m_crWindowText, m_crWindowColour, m_cr3DFace,     // System colours
                m_crShadow;
    COLORREF    m_crTTipBackClr, m_crTTipTextClr;                 // Titletip colours - FNA
    
	//##ModelId=4D4223BE023A
    BOOL        m_bVirtualMode;
	//##ModelId=4D4223BE0249
    LPARAM      m_lParam;                                           // lParam for callback
	//##ModelId=4D4223BE025A
    GRIDCALLBACK m_pfnCallback;                                     // The callback function

	//##ModelId=4D4223BE025E
    int         m_nGridLines;
	//##ModelId=4D4223BE0269
    BOOL        m_bEditable;
	//##ModelId=4D4223BE026A
    BOOL        m_bModified;
	//##ModelId=4D4223BE026B
    BOOL        m_bAllowDragAndDrop;
	//##ModelId=4D4223BE0278
    BOOL        m_bListMode;
	//##ModelId=4D4223BE0279
    BOOL        m_bSingleRowSelection;
	//##ModelId=4D4223BE027A
    BOOL        m_bSingleColSelection;
	//##ModelId=4D4223BE0288
    BOOL        m_bAllowDraw;
	//##ModelId=4D4223BE0289
    BOOL        m_bEnableSelection;
    BOOL        m_bFixedRowSelection, m_bFixedColumnSelection;
	//##ModelId=4D4223BE028A
    BOOL        m_bSortOnClick;
	//##ModelId=4D4223BE0298
    BOOL        m_bHandleTabKey;
	//##ModelId=4D4223BE0299
    BOOL        m_bDoubleBuffer;
	//##ModelId=4D4223BE029A
    BOOL        m_bTitleTips;
	//##ModelId=4D4223BE02A7
    int         m_nBarState;
	//##ModelId=4D4223BE02A8
    BOOL        m_bWysiwygPrinting;
    BOOL        m_bHiddenColUnhide, m_bHiddenRowUnhide;
    BOOL        m_bAllowColHide, m_bAllowRowHide;
	//##ModelId=4D4223BE02A9
    BOOL        m_bAutoSizeSkipColHdr;
	//##ModelId=4D4223BE02B7
    BOOL        m_bTrackFocusCell;
	//##ModelId=4D4223BE02B8
    BOOL        m_bFrameFocus;
	//##ModelId=4D4223BE02B9
    UINT        m_nAutoSizeColumnStyle;

    // Cell size details
    int         m_nRows, m_nFixedRows, m_nCols, m_nFixedCols;
    CUIntArray  m_arRowHeights, m_arColWidths;
    int         m_nVScrollMax, m_nHScrollMax;

    // Fonts and images
	//##ModelId=4D4223BE02C7
    CRuntimeClass*   m_pRtcDefault; // determines kind of Grid Cell created by default
	//##ModelId=4D4223BE02CC
    CGridDefaultCell m_cellDefault;  // "default" cell. Contains default colours, font etc.
    CGridDefaultCell m_cellFixedColDef, m_cellFixedRowDef, m_cellFixedRowColDef;
	//##ModelId=4D4223BE02D1
    CFont       m_PrinterFont;  // for the printer
	//##ModelId=4D4223BE02D7
    CImageList* m_pImageList;

    // Cell data
	//##ModelId=4D4223BE02DC
    CTypedPtrArray<CObArray, GRID_ROW*> m_RowData;

    // Mouse operations such as cell selection
	//##ModelId=4D4223BE02E6
    int         m_MouseMode;
    BOOL        m_bLMouseButtonDown, m_bRMouseButtonDown;
    CPoint      m_LeftClickDownPoint, m_LastMousePoint;
    CCellID     m_LeftClickDownCell, m_SelectionStartCell;
    CCellID     m_idCurrentCell, m_idTopLeftCell;
	//##ModelId=4D4223BE02E7
    int         m_nTimerID;
	//##ModelId=4D4223BE02E8
    int         m_nTimerInterval;
	//##ModelId=4D4223BE02F5
    int         m_nResizeCaptureRange;
    BOOL        m_bAllowRowResize, m_bAllowColumnResize;
	//##ModelId=4D4223BE02F6
    int         m_nRowsPerWheelNotch;
    CMap<DWORD,DWORD, CCellID, CCellID&> m_SelectedCellMap, m_PrevSelectedCellMap;

#ifndef GRIDCONTROL_NO_TITLETIPS
	//##ModelId=4D4223BE02F8
    CTitleTip   m_TitleTip;             // Title tips for cells
#endif

    // Drag and drop
	//##ModelId=4D4223BE0306
    CCellID     m_LastDragOverCell;
#ifndef GRIDCONTROL_NO_DRAGDROP
	//##ModelId=4D4223BE030B
    CGridDropTarget m_DropTarget;       // OLE Drop target for the grid
#endif

    // Printing information
	//##ModelId=4D4223BE0315
    CSize       m_CharSize;
	//##ModelId=4D4223BE0316
    int         m_nPageHeight;
    CSize       m_LogicalPageSize,      // Page size in gridctrl units.
                m_PaperSize;            // Page size in device units.
    // additional properties to support Wysiwyg printing
	//##ModelId=4D4223BE0317
    int         m_nPageWidth;
	//##ModelId=4D4223BE0324
    int         m_nPrintColumn;
	//##ModelId=4D4223BE0325
    int         m_nCurrPrintRow;
	//##ModelId=4D4223BE0334
    int         m_nNumPages;
	//##ModelId=4D4223BE0335
    int         m_nPageMultiplier;

    // sorting
	//##ModelId=4D4223BE0336
    int          m_bAscending;
	//##ModelId=4D4223BE0343
    int          m_nSortColumn;
	//##ModelId=4D4223BE0345
	PFNLVCOMPARE m_pfnCompare;

    // EFW - Added to support shaded/unshaded printout.  If true, colored
    // cells will print as-is.  If false, all text prints as black on white.
	//##ModelId=4D4223BE0349
    BOOL        m_bShadedPrintOut;

    // EFW - Added support for user-definable margins.  Top and bottom are in 
    // lines.  Left, right, and gap are in characters (avg width is used).
    int         m_nHeaderHeight, m_nFooterHeight, m_nLeftMargin,
                m_nRightMargin, m_nTopMargin, m_nBottomMargin, m_nGap;

protected:
	//##ModelId=4D4223BE0353
    void SelectAllCells();
	//##ModelId=4D4223BF00D2
    void SelectColumns(CCellID currentCell, BOOL bForceRedraw=FALSE, BOOL bSelectCells=TRUE);
	//##ModelId=4D4223BF0249
    void SelectRows(CCellID currentCell, BOOL bForceRedraw=FALSE, BOOL bSelectCells=TRUE);
	//##ModelId=4D4223BF03C0
    void SelectCells(CCellID currentCell, BOOL bForceRedraw=FALSE, BOOL bSelectCells=TRUE);
	//##ModelId=4D4223C00140
    void OnSelecting(const CCellID& currentCell);

    // Generated message map functions
    //{{AFX_MSG(CGridCtrl)
	//##ModelId=4D4223C002A7
    afx_msg void OnPaint();
	//##ModelId=4D4223C10111
    afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//##ModelId=4D4223C102F5
    afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//##ModelId=4D4223C200E2
    afx_msg void OnSize(UINT nType, int cx, int cy);
	//##ModelId=4D4223C20343
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//##ModelId=4D4223C20363
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//##ModelId=4D4223C20382
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//##ModelId=4D4223C203C0
    afx_msg void OnTimer(UINT nIDEvent);
	//##ModelId=4D4223C3020B
    afx_msg UINT OnGetDlgCode();
	//##ModelId=4D4223C40075
    afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//##ModelId=4D4223C402A7
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	//##ModelId=4D4223C500E2
    afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//##ModelId=4D4223C502E6
    afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//##ModelId=4D4223C50324
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//##ModelId=4D4223C601CC
    afx_msg void OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//##ModelId=4D4223C70017
    afx_msg void OnUpdateEditSelectAll(CCmdUI* pCmdUI);
    //}}AFX_MSG
#ifndef _WIN32_WCE_NO_CURSOR
	//##ModelId=4D4223C7015F
    afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
#endif
#ifndef _WIN32_WCE
	//##ModelId=4D4223C70259
    afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//##ModelId=4D4223C70278
    afx_msg void OnRButtonUp(UINT nFlags, CPoint point);    // EFW - Added
	//##ModelId=4D4223C70298
    afx_msg void OnSysColorChange();
#endif
#ifndef _WIN32_WCE_NO_CURSOR
	//##ModelId=4D4223C80121
    afx_msg void OnCaptureChanged(CWnd *pWnd);
#endif
#ifndef GRIDCONTROL_NO_CLIPBOARD
	//##ModelId=4D4223C80392
    afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	//##ModelId=4D4223C900E2
    afx_msg void OnUpdateEditCut(CCmdUI* pCmdUI);
	//##ModelId=4D4223C9022A
    afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
#endif
#if (_MFC_VER >= 0x0421) || (_WIN32_WCE >= 210)
	//##ModelId=4D4223C90363
    afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);
#endif
#if !defined(_WIN32_WCE) && (_MFC_VER >= 0x0421)
	//##ModelId=4D4223CA01EC
    afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
#endif
	//##ModelId=4D4223CA022A
    afx_msg LRESULT OnSetFont(WPARAM hFont, LPARAM lParam);
	//##ModelId=4D4223CA0315
    afx_msg LRESULT OnGetFont(WPARAM hFont, LPARAM lParam);
	//##ModelId=4D4223CB0027
    afx_msg void OnEndInPlaceEdit(NMHDR* pNMHDR, LRESULT* pResult);
    DECLARE_MESSAGE_MAP()

	//##ModelId=4D4223CB0259
    enum eMouseModes { MOUSE_NOTHING, MOUSE_SELECT_ALL, MOUSE_SELECT_COL, MOUSE_SELECT_ROW,
                       MOUSE_SELECT_CELLS, MOUSE_SCROLLING_CELLS,
                       MOUSE_OVER_ROW_DIVIDE, MOUSE_SIZING_ROW,
                       MOUSE_OVER_COL_DIVIDE, MOUSE_SIZING_COL,
		//##ModelId=4D4223CB0269
                       MOUSE_PREPARE_EDIT,
#ifndef GRIDCONTROL_NO_DRAGDROP
                       MOUSE_PREPARE_DRAG, MOUSE_DRAGGING
#endif
    };
};

// Returns the default cell implementation for the given grid region
//##ModelId=4D4223A50008
inline CGridCellBase* CGridCtrl::GetDefaultCell(BOOL bFixedRow, BOOL bFixedCol) const
{ 
    if (bFixedRow && bFixedCol) return (CGridCellBase*) &m_cellFixedRowColDef;
    if (bFixedRow)              return (CGridCellBase*) &m_cellFixedRowDef;
    if (bFixedCol)              return (CGridCellBase*) &m_cellFixedColDef;
    return (CGridCellBase*) &m_cellDefault;
}

//##ModelId=4D4223A50018
inline CGridCellBase* CGridCtrl::GetCell(int nRow, int nCol) const
{
    if (nRow < 0 || nRow >= m_nRows || nCol < 0 || nCol >= m_nCols) 
        return NULL;

    if (GetVirtualMode())
    {
        CGridCellBase* pCell = GetDefaultCell(nRow < m_nFixedRows, nCol < m_nFixedCols);
        static GV_DISPINFO gvdi;
        gvdi.item.row     = nRow;
        gvdi.item.col     = nCol;
        gvdi.item.mask    = 0xFFFFFFFF;
        gvdi.item.nState  = 0;
        gvdi.item.nFormat = pCell->GetFormat();
        gvdi.item.iImage  = pCell->GetImage();
        gvdi.item.crBkClr = pCell->GetBackClr();
        gvdi.item.crFgClr = pCell->GetTextClr();
        gvdi.item.lParam  = pCell->GetData();
        memcpy(&gvdi.item.lfFont, pCell->GetFont(), sizeof(LOGFONT));
        gvdi.item.nMargin = pCell->GetMargin();
        gvdi.item.strText.Empty();

        // Fix the state bits
        if (IsCellSelected(nRow, nCol))   gvdi.item.nState |= GVIS_SELECTED;
        if (nRow < GetFixedRowCount())    gvdi.item.nState |= (GVIS_FIXED | GVIS_FIXEDROW);
        if (nCol < GetFixedColumnCount()) gvdi.item.nState |= (GVIS_FIXED | GVIS_FIXEDCOL);
        if (GetFocusCell() == CCellID(nRow, nCol)) gvdi.item.nState |= GVIS_FOCUSED;
        
        if (m_pfnCallback)
            m_pfnCallback(&gvdi, m_lParam);
        else
            SendDisplayRequestToParent(&gvdi);

        static CGridCell cell;
        cell.SetState(gvdi.item.nState);
        cell.SetFormat(gvdi.item.nFormat);
        cell.SetImage(gvdi.item.iImage);
        cell.SetBackClr(gvdi.item.crBkClr);
        cell.SetTextClr(gvdi.item.crFgClr);
        cell.SetData(gvdi.item.lParam);
        cell.SetFont(&(gvdi.item.lfFont));
        cell.SetMargin(gvdi.item.nMargin);
        cell.SetText(gvdi.item.strText);
        cell.SetGrid((CGridCtrl*)this);

        return (CGridCellBase*) &cell;
    }

    GRID_ROW* pRow = m_RowData[nRow];
    if (!pRow) return NULL;
    return pRow->GetAt(nCol);
}

//##ModelId=4D4223B90372
inline BOOL CGridCtrl::SetCell(int nRow, int nCol, CGridCellBase* pCell)
{
    if (GetVirtualMode())
        return FALSE;

    if (nRow < 0 || nRow >= m_nRows || nCol < 0 || nCol >= m_nCols) 
        return FALSE;

    GRID_ROW* pRow = m_RowData[nRow];
    if (!pRow) return FALSE;

    pCell->SetCoords( nRow, nCol); 
    pRow->SetAt(nCol, pCell);

    return TRUE;
}

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRIDCTRL_H__519FA702_722C_11D1_ABBA_00A0243D1382__INCLUDED_)
