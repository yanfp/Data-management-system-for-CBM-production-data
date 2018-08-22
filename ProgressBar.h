#pragma once


// CProgressBar

class CProgressBar : public CEdit
{
	DECLARE_DYNAMIC(CProgressBar)

public:
	CProgressBar();
	virtual ~CProgressBar();

protected:
	DECLARE_MESSAGE_MAP()
	int m_rate;
public:
	void UpdateRate(float rate);

};


