// PicStatic2.cpp : 实现文件
//

#include "stdafx.h"
#include "Tool.h"
#include "PicStatic2.h"

#include "Analyse2Dlg.h"
// CPicStatic2

IMPLEMENT_DYNAMIC(CPicStatic2, CStatic)

CPicStatic2::CPicStatic2()
{

}

CPicStatic2::~CPicStatic2()
{

}


BEGIN_MESSAGE_MAP(CPicStatic2, CStatic)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSELEAVE()
END_MESSAGE_MAP()



// CPicStatic2 消息处理程序


void CPicStatic2::ShowTip(CPoint point)
{
	Zk_Value* pzk=this->Search(point.y);
	if(pzk)
	{
		if(!m_TipWnd.m_hWnd)
		{
			m_TipWnd.Create(IDD_DLG_TIP,this);	
		}
		m_TipWnd.ShowWindow(SW_SHOW);
		CRect rect;
		this->GetWindowRect(&rect);
		m_TipWnd.SetWindowPos(&wndTop,rect.left+point.x,rect.top+point.y,0,0,SWP_NOSIZE);

		CString strTime,strValue;
		strTime.Format(L"钻井：%s",pzk->m_ZkName);
		strValue.Format(L"数值：%0.1f",pzk->m_Value);
		m_TipWnd.SetDlgItemText(IDC_STATIC_TIME,strTime);
		m_TipWnd.SetDlgItemText(IDC_STATIC_VALUE,strValue);
	}
	else
	{
		if(m_TipWnd.m_hWnd)
			m_TipWnd.PostMessageW(WM_CLOSE);
	}
}

void CPicStatic2::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	this->ShowTip(point);

	CStatic::OnLButtonDown(nFlags, point);
}

Zk_Value* CPicStatic2::Search(int y)
{
	Zk_Value zk;
	CAnalyse2Dlg* pMain=(CAnalyse2Dlg*)this->GetParent();
	int count=pMain->m_NumberOfZk;
	int group=pMain->m_CurrentIndex;
	CRect r=pMain->GetPicRect();
	int index=y/10;
	if((group+1)*50<count)
	{
		return &(pMain->m_pZKValue[group*50+index]);
	}
	else
	{
		int last=count-group*50;
		double yPer=(r.Height()-10)/(last-1);
		index=y/yPer;
		if(y>index*yPer && y<index*yPer+10)
			return &(pMain->m_pZKValue[group*50+index]);
		else
			return NULL;
	}
}

void CPicStatic2::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//this->ShowTip(point);

	TRACKMOUSEEVENT tme;   
	tme.cbSize=sizeof(TRACKMOUSEEVENT); 
	tme.dwFlags=TME_LEAVE;   
	tme.hwndTrack=this->m_hWnd;  
	::_TrackMouseEvent(&tme);

	CStatic::OnMouseMove(nFlags, point);
}


void CPicStatic2::OnMouseLeave()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CRect r1;
	this->GetWindowRect(r1);
	CPoint pt;
	::GetCursorPos(&pt);
	BOOL b=r1.PtInRect(pt);
	if(!b && m_TipWnd.m_hWnd && m_TipWnd.IsWindowVisible())
		this->m_TipWnd.ShowWindow(SW_HIDE);
	CStatic::OnMouseLeave();
}
