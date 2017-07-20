
#ifndef __IAppStatistics_h__
#define __IAppStatistics_h__


//统计接口
class IAppStatistics
{
public:
	//是否取统计描述名字
	virtual BOOL IsGetDescName() = NULL;
	//设置统计项描述名
	virtual BOOL SetDescName(int nKey,int nSubKey,const char* szDescName) = NULL;
	//设置数据类型，1累加型，2当前值型
	virtual BOOL SetDataType(int nKey,int nSubKey,int nDataType) = NULL;
	//设置统计项值
	virtual BOOL SetStatisticsVal(int nKey,int nSubKey,__int64 i64Val) = NULL;
	//设置数据时间
	virtual void SetDataTime(time_t tCurTime) = NULL;

};


#endif //