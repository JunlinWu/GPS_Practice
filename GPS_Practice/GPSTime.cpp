class CGpsTime 
{
public:
    //## Constructors (generated)//## Destructor (generated)
	CGpsTime();
	CGpsTime (const CGpsTime& gtGpsTime);
	~CGpsTime();
	
	//输入
	int InitgGpsTime(int nGpsWeek, double dGpsSecond);//使用GPS周和秒初始化//in GPST
	int InitgGpsTime (int nYear, int nMounth, int nDay, int nHour, int nMinute, double dSecond);//in GPST
	int GetWeek () const{return m_nWeek;};
	double GetWeekSecond () const{return m_dWeekSecond;};
		
private: //## implementation
    // Data Members for Class Attributes
	//GPST
	int m_nWeek;
	double m_dWeekSecond;	
};


//从年 月 日 转换为GPS 周秒
int CGpsTime::InitgGpsTime (int nYear, int nMounth, int nDay, int nHour, int nMinute, double dSecond)
{
	int DayofMonth = 0;
	int DayofYear = 0;
	int weekno = 0;
	int dayofweek;
	int m;
	if (nYear < 1980 || nMounth < 1 || nMounth > 12 || nDay < 1 || nDay > 31)  return -1;
	//计算从1980年到当前的前一年的天数
	for( m = 1980 ; m < nYear ; m++ )
	{
		if ( (m%4 == 0 && m%100 != 0) || (m%400 == 0) ) 
		{
			DayofYear += 366;
		}
		else
			DayofYear += 365;
	}
	//计算当前一年内从元月到当前前一月的天数
	for( m = 1;m < nMounth; m++)
	{
		if(m==1 || m==3 || m==5 || m==7 || m==8 || m==10 || m==12)
			DayofMonth += 31;
		else if (m==4 || m==6 || m==9 || m==11) 
			DayofMonth += 30;
		else if (m ==2)
		{
			if ( (nYear%4 == 0 && nYear%100 != 0) || (nYear%400 == 0) )
				DayofMonth += 29;
			else 
				DayofMonth += 28;
				
		}
	}
	DayofMonth = DayofMonth + nDay - 6;//加上当月天数/减去1980年元月的6日		
	weekno = (DayofYear + DayofMonth) / 7;//计算GPS周
	dayofweek = (DayofYear + DayofMonth) % 7;
	//计算GPS 周秒时间
	m_dWeekSecond = dayofweek*86400 + nHour*3600 + nMinute*60 + dSecond;
	m_nWeek = weekno;

	return weekno;
}