#pragma once
#include "struct.h"


class CPicStatic : public CStatic
{
	DECLARE_DYNAMIC(CPicStatic)

public:
	CPicStatic();
	virtual ~CPicStatic();
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

public:
	CToolTipCtrl m_ToolTip;
	CDialog m_TipWnd;
	Name_Value *m_pNV;
	Name_Value* Search(int,int);
	void ShowTip(int x);
	afx_msg void OnMouseLeave();

	Name_Value* FindByBinary(Name_Value *pnv,int key,int low,int high,double xper);
};


