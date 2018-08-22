/*****************************************************************************
    COPYRIGHT (C) 2000-2001, Ken Bertelson <kbertelson@yahoo.com>


*****************************************************************************/
#if !defined(AFX_TREECOLUMN_H__55D4E2A3_EDF9_11D3_B75E_00C04F6A7AE6__INCLUDED_)
#define AFX_TREECOLUMN_H__55D4E2A3_EDF9_11D3_B75E_00C04F6A7AE6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GridCtrl.h"

//##ModelId=4D42239A0337
class CTreeColumn
{
public:
	//##ModelId=4D42239A0338
    CTreeColumn();
	//##ModelId=4D42239A0343
    virtual ~CTreeColumn();

// accessors
public:
	//##ModelId=4D42239A0345
    virtual void SetFormat(DWORD nFormat) { m_nFormat = nFormat; }
	//##ModelId=4D42239A0353
    virtual DWORD GetFormat() const { return m_nFormat; }

	//##ModelId=4D42239A0355
    virtual void SetBkClr(COLORREF crBkClr) { m_crBkClr = crBkClr; }
	//##ModelId=4D42239A0358
    virtual COLORREF GetBkClr() const { return m_crBkClr; }

	//##ModelId=4D42239A035A
    virtual void SetFgClr(COLORREF crFgClr) { m_crFgClr = crFgClr; }
	//##ModelId=4D42239A035D
    virtual COLORREF GetFgClr() const { return m_crFgClr; }

	//##ModelId=4D42239A0363
    virtual void SetParam(LPARAM lParam) { m_lParam = lParam; }
	//##ModelId=4D42239A0366
    virtual LPARAM GetParam() const { return m_lParam; }

	//##ModelId=4D42239A0368
    virtual void SetFont(const LOGFONT* plf)
    {
        // One Tree Column will serve multiple cells, so setting fonts can be tricky
        // since there is wonderful scope for overwriting one's self. Let's be cautious.
        if (plf == NULL)
        {
            delete m_plfFont;
            m_plfFont = NULL;
        }
        else
        {
            static LOGFONT lf;
            memcpy(&lf, plf, sizeof(LOGFONT));
            if (!m_plfFont)
                m_plfFont = new LOGFONT;
            if (m_plfFont)
                memcpy(m_plfFont, &lf, sizeof(LOGFONT)); 
        }
    }

	//##ModelId=4D42239A036B
    virtual LOGFONT* GetFont() const
    {
        if (m_plfFont)
            return (LOGFONT*) m_plfFont; 
        else
            return GetGrid()->GetDefaultCell(FALSE, FALSE)->GetFont();
    }

	//##ModelId=4D42239A036D
    virtual void SetAllowDraw(BOOL bAllowDraw) { m_bAllowDraw = bAllowDraw; }
	//##ModelId=4D42239A0372
    virtual BOOL GetAllowDraw() const { return m_bAllowDraw; }

	//##ModelId=4D42239A0374
    virtual void SetEditWnd(CWnd* pEditWnd) { m_pEditWnd = pEditWnd; }
	//##ModelId=4D42239A0377
    virtual CWnd* GetEditWnd() const const { return m_pEditWnd; }

	//##ModelId=4D42239A0379
    virtual void SetGrid(CGridCtrl* pGrid) { m_pGrid = pGrid; }
	//##ModelId=4D42239A037C
    virtual CGridCtrl* GetGrid() const { return m_pGrid; }

	//##ModelId=4D42239A037E
    virtual void SetColumnWithTree( int iColumnWithTree) { m_iColumnWithTree = iColumnWithTree; }
	//##ModelId=4D42239A0382
    virtual int GetColumnWithTree() const { return m_iColumnWithTree; }

	//##ModelId=4D42239A0384
    virtual void SetDefTreeIndent( int nDefTreeIndent) { m_nDefTreeIndent = nDefTreeIndent; }
	//##ModelId=4D42239A0387
    virtual int GetDefTreeIndent() const { return m_nDefTreeIndent; }

	//##ModelId=4D42239A0389
    virtual void SetFixedRowCount( int iFixedRowCount) { m_iFixedRowCount = iFixedRowCount; }
	//##ModelId=4D42239A038C
    virtual int GetFixedRowCount() const { return m_iFixedRowCount; }

	//##ModelId=4D42239A038E
    virtual void SetRowCount( int iRowCount) { m_iRowCount = iRowCount; }
	//##ModelId=4D42239A0394
    virtual int GetRowCount() const { return m_iRowCount; }

// tree column operations
public:
	//##ModelId=4D42239A0396
    BOOL TreeSetup( CGridCtrl* apGridCtrl,  // tree acts on a column in this grid
                    int aiColumn,       // which column has tree
                    int aiTotalRows,    // total number of rows in the
                                        //  tree if totally expanded
                    int aiFixedRowCount,// Set fixed row count now, too
                                        //  Grid total rows=aiTotalRows+aiFixedRowCount
                    const unsigned char* apucTreeLevelAry,    // Tree Level data array --
                                                     //  must have aiTotalRows of entries
                    BOOL abShowTreeLines,   // T=show tree (not grid) lines; F=no tree lines
                    BOOL abUseImages,  // T=use 1st 3 images from already set image list
                                        //  to display folder graphics
                    CRuntimeClass* apRuntimeClass = NULL);
                                        // can use your special
                                        //  CGridTreeCellBase-derived class
    // returns:  success / fail

	//##ModelId=4D42239A03A1
    int InsertTreeBranch(  
                   const unsigned char* apucTreeLevelAry,    // Tree Level data array --
                                       //  must have aiNbrElements of entries
                   int aiNbrElements,  // NUmber of tree elements to add
                   int aiRow,      // insert tree elements beginning at this row
                                   //  If -1, append to end; If 0, Insert
                                   //  at top no matter how many fixed rows
                   BOOL abRedraw); // T=redraw; F=don't
    // returns:  row where elements inserted; -1 on error

	//##ModelId=4D42239A03B1
    int DeleteTreeBranch( int aiRow,        // Row that the tree branch begins on
                          BOOL abRedraw);   // T=redraw; F=don't
    // returns:  nbr of rows deleted

	//##ModelId=4D42239A03B4
    void SetTreeUsesImages( BOOL abUseImages);   // T=use images
	//##ModelId=4D42239A03C0
    BOOL GetTreeUsesImages() const              { return m_bTreeUsesImages; }

	//##ModelId=4D42239A03C2
    int GetTreeUsesNbrImages() const;

	//##ModelId=4D42239A03C4
    void SetTreeLines( BOOL abShowTreeLines);   // T=show tree lines
	//##ModelId=4D42239A03C6
    BOOL GetTreeLines() const                   { return m_bShowTreeLines; }

	//##ModelId=4D42239A03C8
    void     SetTreeLineColor(COLORREF clr)       { m_crTreeLineColour = clr;         }
	//##ModelId=4D42239A03CA
    COLORREF GetTreeLineColor() const             { return m_crTreeLineColour;        }

	//##ModelId=4D42239A03D1
    unsigned char GetTreeLevel(  int aiRow);  // row
    // returns:  tree level, =0 if invalid input
	//##ModelId=4D42239A03D3
    BOOL IsTreeRowDisplayed(  int aiRow);  // row
    // returns:  T=tree row is displayed
	//##ModelId=4D42239A03D5
    unsigned char GetLevelAndHide( int aiRow); // row

	//##ModelId=4D42239A03E0
    void TreeRefreshRows();

	//##ModelId=4D42239A03E1
    void TreeDataPrepOutline(unsigned char aucLevel, // level to display >= 0x80 displays all
                             int aiIndex,            // Index to tree display data to modify
                             int aiNbrElements);     // nbr of elements in tree display data

	//##ModelId=4D42239A03E5
    void TreeDisplayOutline( unsigned char aucLevel );    // level to display >= 0x80 displays all

	//##ModelId=4D42239A03E7
    void TreeDataExpandOneLevel( int aiGridRow);

	//##ModelId=4D42239B0007
    void TreeDataCollapseAllSubLevels( int aiGridRow);

	//##ModelId=4D42239B0009
    void TreeExpandCollapseToggle( int aiGridRow); // Grid row of node to toggle

	//##ModelId=4D42239B000B
    BOOL TreeCellHasPlusMinus(   int aiRow,          // row of Cell to check
                                 BOOL* apbIsPlus,    // returns:  T=Is a plus
                                 BOOL* apbIsMinus,   // returns:  T=Is a minus
                                 BOOL* apbIsLastLeaf);// returns:  T=Is Last Leaf
    // returns:  T=cell has a plus or minus;  F=not

	//##ModelId=4D42239B0010
    virtual BOOL IsDefaultFont() const       { return (m_plfFont == NULL); }

// let the CGridTreeCtrl maintain a single instance of the following
//  on the behalf of the expected column of CGridTreeCell's
protected:
	//##ModelId=4D42239B0012
    DWORD    m_nFormat;     // Cell format
	//##ModelId=4D42239B0084
    COLORREF m_crBkClr;     // Background colour (or CLR_DEFAULT)
	//##ModelId=4D42239B0085
    COLORREF m_crFgClr;     // Forground colour (or CLR_DEFAULT)
	//##ModelId=4D42239B0094
    LPARAM   m_lParam;      // 32-bit value to associate with item
	//##ModelId=4D42239B0096
    LOGFONT *m_plfFont;     // Cell font

	//##ModelId=4D42239B009A
    BOOL m_bAllowDraw;  // private switch to turn off / on drawing
	//##ModelId=4D42239B00A5
    CWnd* m_pEditWnd;   // can edit only 1 at a time
	//##ModelId=4D42239B00AA
    CGridCtrl* m_pGrid;
	//##ModelId=4D42239B00B4
    CRuntimeClass* m_pRuntimeClassTreeCell;

    // tree column properties
	//##ModelId=4D42239B00B8
    int m_iColumnWithTree;
	//##ModelId=4D42239B00C3
    int m_nDefTreeIndent;
	//##ModelId=4D42239B00C4
    BOOL m_bShowTreeLines;
	//##ModelId=4D42239B00C5
    BOOL m_bTreeUsesImages;
	//##ModelId=4D42239B00D2
    COLORREF m_crTreeLineColour;
	//##ModelId=4D42239B00D3
    int m_iFixedRowCount;
	//##ModelId=4D42239B00E2
    int m_iRowCount;

};

#endif // !defined(AFX_TREECOLUMN_H__55D4E2A3_EDF9_11D3_B75E_00C04F6A7AE6__INCLUDED_)
