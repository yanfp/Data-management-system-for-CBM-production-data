///////////////////////////////////////////////////////////////////////
// CellRange.h: header file
//
// MFC Grid Control - interface for the CCellRange class.
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

#if !defined(AFX_CELLRANGE_H__F86EF761_725A_11D1_ABBA_00A0243D1382__INCLUDED_)
#define AFX_CELLRANGE_H__F86EF761_725A_11D1_ABBA_00A0243D1382__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// The code contained in this file is based on the original
// WorldCom Grid control written by Joe Willcoxson,
//      mailto:chinajoe@aol.com
//      http://users.aol.com/chinajoe

//##ModelId=4D4223CD016F
class CCellID
{    
// Attributes
public:
    int row, col;

// Operations
public:
	//##ModelId=4D4223CD0170
    CCellID(int nRow = -1, int nCol = -1) : row(nRow), col(nCol) {}

	//##ModelId=4D4223CD0173
    int IsValid() const { return (row >= 0 && col >= 0); }
	//##ModelId=4D4223CD017E
    int operator==(const CCellID& rhs)    { return (row == rhs.row && col == rhs.col); }
	//##ModelId=4D4223CD0180
    int operator!=(const CCellID& rhs)    { return !operator==(rhs); }
};

//##ModelId=4D4223CD018E
class CCellRange
{ 
public:
    
	//##ModelId=4D4223CD018F
    CCellRange(int nMinRow = -1, int nMinCol = -1, int nMaxRow = -1, int nMaxCol = -1)
    {
        Set(nMinRow, nMinCol, nMaxRow, nMaxCol);
    }

	//##ModelId=4D4223CD01A1
    void Set(int nMinRow = -1, int nMinCol = -1, int nMaxRow = -1, int nMaxCol = -1);
    
	//##ModelId=4D4223CD01A6
    int  IsValid() const;
	//##ModelId=4D4223CD01AE
    int  InRange(int row, int col) const;
	//##ModelId=4D4223CD01B2
    int  InRange(const CCellID& cellID) const;
	//##ModelId=4D4223CD01B5
    int  Count() { return (m_nMaxRow - m_nMinRow + 1) * (m_nMaxCol - m_nMinCol + 1); }
    
	//##ModelId=4D4223CD01B6
    CCellID  GetTopLeft() const;
	//##ModelId=4D4223CD01BD
    CCellRange  Intersect(const CCellRange& rhs) const;
    
	//##ModelId=4D4223CD01C0
    int GetMinRow() const {return m_nMinRow;}
	//##ModelId=4D4223CD01C2
    void SetMinRow(int minRow) {m_nMinRow = minRow;}
    
	//##ModelId=4D4223CD01C4
    int GetMinCol() const {return m_nMinCol;}
	//##ModelId=4D4223CD01C6
    void SetMinCol(int minCol) {m_nMinCol = minCol;}
    
	//##ModelId=4D4223CD01CC
    int GetMaxRow() const {return m_nMaxRow;}
	//##ModelId=4D4223CD01CE
    void SetMaxRow(int maxRow) {m_nMaxRow = maxRow;}
    
	//##ModelId=4D4223CD01D0
    int GetMaxCol() const {return m_nMaxCol;}
	//##ModelId=4D4223CD01D2
    void SetMaxCol(int maxCol) {m_nMaxCol = maxCol;}

	//##ModelId=4D4223CD01D4
    int GetRowSpan() const {return m_nMaxRow - m_nMinRow + 1;}
	//##ModelId=4D4223CD01DD
    int GetColSpan() const {return m_nMaxCol - m_nMinCol + 1;}
    
	//##ModelId=4D4223CD01DF
    void operator=(const CCellRange& rhs);
	//##ModelId=4D4223CD01E1
    int  operator==(const CCellRange& rhs);
	//##ModelId=4D4223CD01E3
    int  operator!=(const CCellRange& rhs);
    
protected:
	//##ModelId=4D4223CD01E5
    int m_nMinRow;
	//##ModelId=4D4223CD01EC
    int m_nMinCol;
	//##ModelId=4D4223CD01ED
    int m_nMaxRow;
	//##ModelId=4D4223CD01EE
    int m_nMaxCol;
};

//##ModelId=4D4223CD01A1
inline void CCellRange::Set(int minRow, int minCol, int maxRow, int maxCol)
{
     m_nMinRow = minRow;
     m_nMinCol = minCol;
     m_nMaxRow = maxRow;
     m_nMaxCol = maxCol;
}

//##ModelId=4D4223CD01DF
inline void CCellRange::operator=(const CCellRange& rhs)
{
    Set(rhs.m_nMinRow, rhs.m_nMinCol, rhs.m_nMaxRow, rhs.m_nMaxCol);
}

//##ModelId=4D4223CD01E1
inline int CCellRange::operator==(const CCellRange& rhs)
{
     return ((m_nMinRow == rhs.m_nMinRow) && (m_nMinCol == rhs.m_nMinCol) &&
             (m_nMaxRow == rhs.m_nMaxRow) && (m_nMaxCol == rhs.m_nMaxCol));
}

//##ModelId=4D4223CD01E3
inline int CCellRange::operator!=(const CCellRange& rhs)
{
     return !operator==(rhs);
}

//##ModelId=4D4223CD01A6
inline int CCellRange::IsValid() const
{
     return (m_nMinRow >= 0 && m_nMinCol >= 0 && m_nMaxRow >= 0 && m_nMaxCol >= 0 &&
             m_nMinRow <= m_nMaxRow && m_nMinCol <= m_nMaxCol);
}

//##ModelId=4D4223CD01AE
inline int CCellRange::InRange(int row, int col) const
{
     return (row >= m_nMinRow && row <= m_nMaxRow && col >= m_nMinCol && col <= m_nMaxCol);
}

//##ModelId=4D4223CD01B2
inline int CCellRange::InRange(const CCellID& cellID) const
{
     return InRange(cellID.row, cellID.col);
}

//##ModelId=4D4223CD01B6
inline CCellID CCellRange::GetTopLeft() const
{
     return CCellID(m_nMinRow, m_nMinCol);
}

//##ModelId=4D4223CD01BD
inline CCellRange CCellRange::Intersect(const CCellRange& rhs) const
{
     return CCellRange(max(m_nMinRow,rhs.m_nMinRow), max(m_nMinCol,rhs.m_nMinCol),
                       min(m_nMaxRow,rhs.m_nMaxRow), min(m_nMaxCol,rhs.m_nMaxCol));
}

#endif // !defined(AFX_CELLRANGE_H__F86EF761_725A_11D1_ABBA_00A0243D1382__INCLUDED_)
