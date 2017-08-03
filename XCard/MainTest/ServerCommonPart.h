#pragma once
#include "ServerPart.h"

class CServerCommonPart : public IServerPart
{
	struct TLoginReq 
	{
		string strUserName;
		string strPsw;
		DWORD dwUserData;
	};
	typedef vector<TLoginReq> TVec_LoginReq;

public:
	CServerCommonPart(void);
	~CServerCommonPart(void);

public: // IServerPart
	virtual void HandlerMsg(const csmsg::TCSMessage* pMsg);
	virtual bool Create(CServerSession* pServerSession);

public:
	size_t GetLoginReqCount();
	bool GetLoginReqByIndex(size_t nIdx, string& strUserName, string& strPsw, DWORD& dwUserData);
	void ClearLoginReq();


private:
	void __HandlerLoginReq(const csmsg::TCSMessage* pMsg);

private:
	CServerSession* m_pServerSession;
	TVec_LoginReq m_vtLoginReq;	// 尚未处理的登录请求
};
