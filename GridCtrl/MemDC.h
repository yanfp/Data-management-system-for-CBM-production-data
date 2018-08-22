#if !defined(AFX_MEMDC_H__CA1D3541_7235_11D1_ABBA_00A0243D1382__INCLUDED_)
#define AFX_MEMDC_H__CA1D3541_7235_11D1_ABBA_00A0243D1382__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// MemDC.h : header file
//

//////////////////////////////////////////////////
// MCMemDC - memory DC
//
// Author: Keith Rule
// Email:  keithr@europa.com
// Copyright 1996-1997, Keith Rule
//
// You may freely use or modify this code provided this
// Copyright is included in all derived versions.
//
// History - 10/3/97 Fixed scrolling bug.
//                   Added print support.
//           25 feb 98 - fixed minor assertion bug
//
// This class implements a memory Device Context

//##ModelId=4D42239B0140
class MCMemDC : public CDC
{
public:

    // constructor sets up the memory DC
	//##ModelId=4D42239B0142
    MCMemDC(CDC* pDC) : CDC()
    {
        ASSERT(pDC != NULL);

        m_pDC = pDC;
        m_pOldBitmap = NULL;
#ifndef WCE_NO_PRINTING
        m_bMemDC = !pDC->IsPrinting();
#else
        m_bMemDC = FALSE;
#endif

        if (m_bMemDC)    // Create a Memory DC
        {
            pDC->GetClipBox(&m_rect);
            CreateCompatibleDC(pDC);
            m_bitmap.CreateCompatibleBitmap(pDC, m_rect.Width(), m_rect.Height());
            m_pOldBitmap = SelectObject(&m_bitmap);
#ifndef _WIN32_WCE
            SetWindowOrg(m_rect.left, m_rect.top);
#endif
            // EFW - Bug fix - Fill background in case the user has overridden
            // WM_ERASEBKGND.  We end up with garbage otherwise.
            // CJM - moved to fix a bug in the fix.
            FillSolidRect(m_rect, pDC->GetBkColor());
        }
        else        // Make a copy of the relevent parts of the current DC for printing
        {
#if !defined(_WIN32_WCE) || ((_WIN32_WCE > 201) && !defined(WCE_NO_PRINTING))
            m_bPrinting = pDC->m_bPrinting;
#endif
            m_hDC       = pDC->m_hDC;
            m_hAttribDC = pDC->m_hAttribDC;
        }

    }

    // Destructor copies the contents of the mem DC to the original DC
	//##ModelId=4D42239B014F
    ~MCMemDC()
    {
        if (m_bMemDC)
        {
            // Copy the offscreen bitmap onto the screen.
            m_pDC->BitBlt(m_rect.left, m_rect.top, m_rect.Width(), m_rect.Height(),
                          this, m_rect.left, m_rect.top, SRCCOPY);

            //Swap back the original bitmap.
            SelectObject(m_pOldBitmap);
        } else {
            // All we need to do is replace the DC with an illegal value,
            // this keeps us from accidently deleting the handles associated with
            // the CDC that was passed to the constructor.
            m_hDC = m_hAttribDC = NULL;
        }
    }

    // Allow usage as a pointer
	//##ModelId=4D42239B0150
    MCMemDC* operator->() {return this;}
        
    // Allow usage as a pointer
	//##ModelId=4D42239B0151
    operator MCMemDC*() {return this;}

private:
	//##ModelId=4D42239B0153
    CBitmap  m_bitmap;      // Offscreen bitmap
	//##ModelId=4D42239B0160
    CBitmap* m_pOldBitmap;  // bitmap originally found in MCMemDC
	//##ModelId=4D42239B0165
    CDC*     m_pDC;         // Saves CDC passed in constructor
	//##ModelId=4D42239B016F
    CRect    m_rect;        // Rectangle of drawing area.
	//##ModelId=4D42239B0170
    BOOL     m_bMemDC;      // TRUE if CDC really is a Memory DC.
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MEMDC_H__CA1D3541_7235_11D1_ABBA_00A0243D1382__INCLUDED_)
