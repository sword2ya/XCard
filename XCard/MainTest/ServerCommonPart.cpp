#include "StdAfx.h"
#include "ServerCommonPart.h"
#include "ServerSession.h"

using namespace csmsg;

CServerCommonPart::CServerCommonPart(void)
{
	m_pServerSession = NULL;
}

CServerCommonPart::~CServerCommonPart(void)
{
}

void CServerCommonPart::HandlerMsg(const csmsg::TCSMessage* pMsg )
{
	csmsg::ECSMessageID eMsgID = pMsg->emsgid();
	switch (eMsgID)
	{
	case eMsgID_LoginReq:
		__HandlerLoginReq(pMsg);
	}

}

bool CServerCommonPart::Create( CServerSession* pServerSession )
{
	if (NULL == pServerSession)
	{
		return false;
	}
	m_pServerSession = pServerSession;
	return true;
}



size_t CServerCommonPart::GetLoginReqCount()
{
	return m_vtLoginReq.size();
}

bool CServerCommonPart::GetLoginReqByIndex( size_t nIdx, string& strUserName, string& strPsw, DWORD& dwUserData )
{
	if (nIdx >= m_vtLoginReq.size())
	{
		return false;
	}
	TLoginReq &stLoginReq = m_vtLoginReq[nIdx];
	strUserName = stLoginReq.strUserName;
	strPsw = stLoginReq.strPsw;
	dwUserData = stLoginReq.dwUserData;
	return true;
}

void CServerCommonPart::ClearLoginReq()
{
	m_vtLoginReq.clear();
}

void CServerCommonPart::__HandlerLoginReq( const csmsg::TCSMessage* pMsg )
{
	if (!pMsg->has_stloginreq())
	{
		Error(__FUNCTION__<<" 登录请求结构未定义");
		return;
	}
	const csmsg::TMSG_LOGIN_REQ& stLoginReq = pMsg->stloginreq();

	const string& strUserName = stLoginReq.strusername();
	const string& strPsw = stLoginReq.strpassword();
	int nUserData = stLoginReq.nuserdata();
	
	TLoginReq stLoginData;
	stLoginData.strUserName = strUserName;
	stLoginData.strPsw = strPsw;
	stLoginData.dwUserData = nUserData;

	m_vtLoginReq.push_back(stLoginData);
}
