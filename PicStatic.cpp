// PicStatic.cpp : 实现文件
//

#include "stdafx.h"
#include "Tool.h"
#include "PicStatic.h"
#include "AnalyseDlg.h"
#include  <math.h>


IMPLEMENT_DYNAMIC(CPicStatic, CStatic)

CPicStatic::CPicStatic()
{
	m_pNV=NULL;
}

CPicStatic::~CPicStatic()
{
}

BEGIN_MESSAGE_MAP(CPicStatic, CStatic)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_PAINT()
	ON_WM_MOUSELEAVE()
END_MESSAGE_MAP()
// CPicStatic 消息处理程序






void CPicStatic::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CAnalyseDlg *pMain=(CAnalyseDlg*)GetParent();
	this->ShowTip(point.x);
	//this->m_TipWnd.ShowWindow(SW_HIDE);
	CStatic::OnLButtonDown(nFlags, point);
}

void CPicStatic::ShowTip(int x)
{
	CAnalyseDlg *pMain=(CAnalyseDlg*)GetParent();
	if(pMain->m_IsSelected && pMain->m_IsDrawn)
	{
		int count=pMain->m_RecordCount;
		Name_Value *pnv=Search(x,count);
		if(pnv)
		{
			if(!m_TipWnd.m_hWnd)
				m_TipWnd.Create(IDD_DLG_TIP,this);
			if(!m_TipWnd.IsWindowVisible())
				m_TipWnd.ShowWindow(SW_SHOW);
			CRect rect;
			this->GetWindowRect(&rect);
			m_TipWnd.SetWindowPos(&wndTop,x+rect.left,rect.Height()-pnv->m_value/pMain->m_MaxValue*rect.Height()+rect.top,0,0,SWP_NOSIZE);

			CString strTime,strValue;
			strTime.Format(L"时间：%s",pnv->m_str);
			strValue.Format(L"值：%0.2f",pnv->m_value);
			m_TipWnd.SetDlgItemText(IDC_STATIC_TIME,strTime);
			m_TipWnd.SetDlgItemText(IDC_STATIC_VALUE,strValue);
		}
	}

}

void CPicStatic::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CAnalyseDlg *pMain=(CAnalyseDlg*)GetParent();
	if(m_pNV==NULL)
		m_pNV=pMain->m_pNameValue;	
	this->ShowTip(point.x);

	//监控鼠标离开   
	TRACKMOUSEEVENT tme;   
	tme.cbSize=sizeof(TRACKMOUSEEVENT); 
	tme.dwFlags=TME_LEAVE;   
	tme.hwndTrack=this->m_hWnd;  
	::_TrackMouseEvent(&tme);


	CStatic::OnMouseMove(nFlags, point);
}

Name_Value* CPicStatic::FindByBinary(Name_Value *pnv,int key,int low,int high,double xper)
{
	if(key<=0)
		return &pnv[0];
	if(key>=xper*(high-1))
		return &pnv[high-1];
	int mid=(low+high)/2;
	int left=low,right=high;
	int StopFlag=0;
	while(left<right && (abs(pnv[mid].m_x-key)>xper))
	{
		if(key<pnv[mid].m_x)
			right=mid;
		else if(key>pnv[mid].m_x)
			left=mid;
		mid=(left+right)/2;

		StopFlag++;
		if(StopFlag>1000)
		{
			return NULL;
		}
	}
	if(abs(pnv[mid].m_x-key)<=xper)
		return &pnv[mid];
	return NULL;
/*	if(fabs(double(pnv[mid].m_x-key))<=xper)
		return &pnv[mid];
	else if(key<pnv[mid].m_x)
		return FindByBinary(pnv,key,low,mid-1,xper);
	else
		return FindByBinary(pnv,key,mid,high,xper);*/
}

Name_Value* CPicStatic::Search(int x,int count)
{
	CAnalyseDlg *pMain=(CAnalyseDlg*)GetParent();
	if(pMain->m_MaxValue)
		return FindByBinary(pMain->m_pNameValue,x,0,count,pMain->m_xInterval);
	else
		return NULL;
}

void CPicStatic::OnMouseLeave()
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
