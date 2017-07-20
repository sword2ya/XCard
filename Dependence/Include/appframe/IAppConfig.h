/********************************************************************
	created:	2011/09/11  22:31
	file base:	IAppConfig
	file ext:	h
	author:		
	
	purpose:	Ӧ�ó������ýӿ�. Ӧ�ó������ͨ������ӿ�, ��ȡ�������ļ�(ini�ļ�)�е���Ϣ
*********************************************************************/



#ifndef __IAPPCONFIG_H__
#define __IAPPCONFIG_H__



class IAppConfig
{
public:
	//  ����/��ȡ�ַ�������
	virtual LPCSTR GetString(LPCSTR szKey, LPCSTR szDefault = "") = 0;
	virtual void SetString(LPCSTR szKey, LPCSTR szValue) = 0;
	
	//  ����/��ȡ��������
	virtual int GetInt(LPCSTR szKey, int iDefault = 0) = 0;
	virtual void SetInt(LPCSTR szKey, int iValue) = 0;

	//  ����/��ȡ����������
	virtual float GetFloat(LPCSTR szKey, float fDefault = 0.f) = 0;
	virtual void SetFloat(LPCSTR szKey, float fValue) = 0;
};


#endif 