/*****************************************************************************
    COPYRIGHT (C) 2000-2001, Ken Bertelson <kbertelson@yahoo.com>


*****************************************************************************/
#if !defined(AFX_GRIDBTNCELL_H__937E4927_EF80_11D3_B75F_00C04F6A7AE6__INCLUDED_)
#define AFX_GRIDBTNCELL_H__937E4927_EF80_11D3_B75F_00C04F6A7AE6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GridBtnCellBase.h"

//##ModelId=4D4223CD0101
class CGridBtnCell : public CGridBtnCellBase
{
    DECLARE_DYNCREATE(CGridBtnCell)
public:
	//##ModelId=4D4223CD0111
    CGridBtnCell();
	//##ModelId=4D4223CD0112
    virtual ~CGridBtnCell();

	//##ModelId=4D4223CD0114
    virtual void Reset();

	//##ModelId=4D4223CD0116
    virtual void operator=(CGridCellBase& cell)
    {
        CGridBtnCellBase::operator=( cell);
    }

public:
	//##ModelId=4D4223CD0119
    virtual void SetText(LPCTSTR szText)    { m_strText = szText; }
	//##ModelId=4D4223CD011C
    virtual LPCTSTR  GetText() const        { return (m_strText.IsEmpty())? _T("") : m_strText; }

	//##ModelId=4D4223CD011E
    virtual void SetFormat(DWORD nFormat)   { m_nFormat = nFormat; }
	//##ModelId=4D4223CD0123
    virtual DWORD GetFormat() const         { return m_nFormat; }



// for drawing things like buttons and check marks within a cell
//  you can have more than one control per cell
public:
	//##ModelId=4D4223CD0125
    virtual unsigned char GetDrawCtlNbrMax() { return NBR_CTLS; }

	//##ModelId=4D4223CD0127
    UINT GetDrawCtlType( int aiWhich)
        { ASSERT( aiWhich < GetDrawCtlNbrMax());
          return (UINT)(DrawCtl[ aiWhich].ucType); }

	//##ModelId=4D4223CD0129
    void SetDrawCtlType( int aiWhich, UINT auiType)
        { ASSERT( aiWhich < GetDrawCtlNbrMax());
          DrawCtl[ aiWhich].ucType = (unsigned char)auiType; }

	//##ModelId=4D4223CD0132
    UINT GetDrawCtlState( int aiWhich)
        { ASSERT( aiWhich < GetDrawCtlNbrMax());
          return (UINT)(DrawCtl[ aiWhich].sState); }

	//##ModelId=4D4223CD0134
    void SetDrawCtlState( int aiWhich, UINT auiState)
        { ASSERT( aiWhich < GetDrawCtlNbrMax());
          ASSERT( auiState < USHRT_MAX);
          DrawCtl[ aiWhich].sState = (short)auiState; }

	//##ModelId=4D4223CD0137
    int GetDrawCtlWidth( int aiWhich)
        { ASSERT( aiWhich < GetDrawCtlNbrMax());
          return DrawCtl[ aiWhich].iWidth; }

	//##ModelId=4D4223CD0139
    void SetDrawCtlWidth( int aiWhich, int aiWidth)
        { ASSERT( aiWhich < GetDrawCtlNbrMax());
          DrawCtl[ aiWhich].iWidth = aiWidth; }

	//##ModelId=4D4223CD0141
    CTL_ALIGN GetDrawCtlAlign( int aiWhich)
        { ASSERT( aiWhich < GetDrawCtlNbrMax());
          return (CTL_ALIGN) DrawCtl[ aiWhich].ucAlign; }

	//##ModelId=4D4223CD0143
    void SetDrawCtlAlign( int aiWhich, CTL_ALIGN aucAlign)
        { ASSERT( aiWhich < GetDrawCtlNbrMax());
          ASSERT( aucAlign < CTL_ALIGN_FENCE);
          DrawCtl[ aiWhich].ucAlign = (unsigned char)aucAlign; }

	//##ModelId=4D4223CD0146
    const char* GetDrawCtlBtnText( int aiWhich)
        { ASSERT( aiWhich < GetDrawCtlNbrMax());
          if( strBtnAry[ aiWhich].IsEmpty())
              return NULL;
          return (char*)LPCTSTR(strBtnAry[ aiWhich]); }

	//##ModelId=4D4223CD0148
    void SetDrawCtlBtnText( int aiWhich, const char* apszText)
        { ASSERT( aiWhich < GetDrawCtlNbrMax());
          if( apszText == NULL)
              strBtnAry[ aiWhich].Empty();
          strBtnAry[ aiWhich] = apszText; }

	//##ModelId=4D4223CD014F
    BOOL GetDrawCtlIsMbrRadioGrp( int aiWhich)
        { ASSERT( aiWhich < GetDrawCtlNbrMax());
          return (BOOL)DrawCtl[ aiWhich].ucIsMbrRadioGrp; }

	//##ModelId=4D4223CD0151
    void SetDrawCtlIsMbrRadioGrp( int aiWhich, BOOL abOn)
        { ASSERT( aiWhich < GetDrawCtlNbrMax());
          DrawCtl[ aiWhich].ucIsMbrRadioGrp = abOn ? 1 : 0;}

protected:
	//##ModelId=4D4223CD0154
    CString  m_strText;     // Cell text (or binary data if you wish...)
	//##ModelId=4D4223CD0155
    DWORD m_nFormat;
    enum { NBR_CTLS = 4};

	//##ModelId=4D4223CD0160
    STRUCT_DRAWCTL DrawCtl[ NBR_CTLS]; // Stores draw control information
	//##ModelId=4D4223CD0164
    CString strBtnAry[ NBR_CTLS];         // button text -- for push buttons
};

#endif // !defined(AFX_GRIDBTNCELL_H__937E4927_EF80_11D3_B75F_00C04F6A7AE6__INCLUDED_)
