
#ifndef __IAppStatistics_h__
#define __IAppStatistics_h__


//ͳ�ƽӿ�
class IAppStatistics
{
public:
	//�Ƿ�ȡͳ����������
	virtual BOOL IsGetDescName() = NULL;
	//����ͳ����������
	virtual BOOL SetDescName(int nKey,int nSubKey,const char* szDescName) = NULL;
	//�����������ͣ�1�ۼ��ͣ�2��ǰֵ��
	virtual BOOL SetDataType(int nKey,int nSubKey,int nDataType) = NULL;
	//����ͳ����ֵ
	virtual BOOL SetStatisticsVal(int nKey,int nSubKey,__int64 i64Val) = NULL;
	//��������ʱ��
	virtual void SetDataTime(time_t tCurTime) = NULL;

};


#endif //