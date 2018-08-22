#pragma once
#include "struct.h"

// CPicStatic2

class CPicStatic2 : public CStatic
{
	DECLARE_DYNAMIC(CPicStatic2)

public:
	CPicStatic2();
	virtual ~CPicStatic2();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

public:
	Zk_Value* Search(int y);

	CDialog m_TipWnd;
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();

	void ShowTip(CPoint point);
};


