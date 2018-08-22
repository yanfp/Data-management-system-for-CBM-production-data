#pragma once
class MyFunction
{
public:
	MyFunction(void);
	~MyFunction(void);

	int GetYear(CString str);
	int GetMonth(CString str);
	int GetDay(CString str);

	int CompareTime(CString s1,CString s2)
	{
		int y1=this->GetYear(s1);
		int m1=this->GetMonth(s1);
		int d1=this->GetDay(s1);
		int y2=this->GetYear(s2);
		int m2=this->GetMonth(s2);
		int d2=this->GetDay(s2);
		if(y1>y2)
			return 1;
		else if(y1==y2)
		{
			if(m1>m2)
				return 1;
			else if(m1==m2)
			{
				if(d1>d2)
					return 1;
				else if(d1==d2)
					return 0;
				else
					return -1;
			}
			else
				return -1;
		}
		else
			return -1;
	}

	CString CTimeToCString(CTime t)
	{
		int y=t.GetYear();
		int m=t.GetMonth();
		int d=t.GetDay();
		CString str;
		str.Format(L"%d/%d/%d",y,m,d);
		return str;
	}

	CTime CStringToCTime(CString str)
	{
		CTime t(this->GetYear(str),this->GetMonth(str),this->GetDay(str),0,0,0);
		return t;
	}
};
