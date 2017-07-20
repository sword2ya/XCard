/********************************************************************
	created:	2011/09/11  22:31
	file base:	IAppConfig
	file ext:	h
	author:		
	
	purpose:	应用程序配置接口. 应用程序可以通过这个接口, 读取到配置文件(ini文件)中的信息
*********************************************************************/



#ifndef __IAPPCONFIG_H__
#define __IAPPCONFIG_H__



class IAppConfig
{
public:
	//  设置/获取字符串配置
	virtual LPCSTR GetString(LPCSTR szKey, LPCSTR szDefault = "") = 0;
	virtual void SetString(LPCSTR szKey, LPCSTR szValue) = 0;
	
	//  设置/获取整数配置
	virtual int GetInt(LPCSTR szKey, int iDefault = 0) = 0;
	virtual void SetInt(LPCSTR szKey, int iValue) = 0;

	//  设置/获取浮点型配置
	virtual float GetFloat(LPCSTR szKey, float fDefault = 0.f) = 0;
	virtual void SetFloat(LPCSTR szKey, float fValue) = 0;
};


#endif 