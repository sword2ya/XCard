#pragma once
#include "iloginmanager.h"

class CLoginManager :
	public ILoginManager , public ITimerSink 
{
	enum ETimerID
	{
		eTimerID_CheckOverTime, 
	};

	typedef set<ILoginCallback*> TSet_LoginCallback;
public:
	CLoginManager(void);
	~CLoginManager(void);

public:	// ILoginManager
	virtual bool RequestLogin(const char* szUserName, const char* szPsw);
	virtual void AddLoginCallback(ILoginCallback* pLoginCallback);
	virtual void RemoveLoginCallback(ILoginCallback* pLoginCallback);
	virtual void ResetLoginStatu();

public: // ITimerSink 
	virtual void OnTimer(int iEventID);

public:
	ILoginCallback* GetFirstLoginCallback();
	ILoginCallback* GetNextLoginCallback();
	const char* GetUserName() const;
	const char* GetPsw() const;
	DWORD GetLoginUserData() const;
	bool IsDoingLogin() const;

	void ActiveOverTimeCheck(bool bActive);// 开启或关闭超时检测

private:
	TSet_LoginCallback m_setLoginCallback;
	TSet_LoginCallback::iterator m_itLoginCallback;
	string m_strUserName;
	string m_strPsw;
	DWORD m_dwLoginUserData;
	bool m_bDoingLogin;	// 是否正在操作登录

};
