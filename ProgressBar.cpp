// ProgressBar.cpp : 实现文件
//

#include "stdafx.h"
#include "Tool.h"
#include "ProgressBar.h"


// CProgressBar

IMPLEMENT_DYNAMIC(CProgressBar, CEdit)

CProgressBar::CProgressBar()
{

}

CProgressBar::~CProgressBar()
{
}


BEGIN_MESSAGE_MAP(CProgressBar, CEdit)
END_MESSAGE_MAP()



// CProgressBar 消息处理程序
void CProgressBar::UpdateRate(float rate)
{
	CRect rect;
	this->GetWindowRect(rect);
	int height=rect.Height();
	int width=rect.Width();
	int current=width*rate;
	CRect r(0,0,current,height-5);
	CDC* pDC=this->GetDC();
	pDC->FillRect(r,&CBrush(RGB(0,200,40)));
}

