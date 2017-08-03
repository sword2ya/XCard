#include "StdAfx.h"
#include "LoginManager.h"
#include "IServerTerminal.h"
#include "IGlobalClient.h"

using namespace csmsg;

CLoginManager::CLoginManager(void)
{
	m_dwLoginUserData = 0;
	m_bDoingLogin = false;
}

CLoginManager::~CLoginManager(void)
{
}

bool CLoginManager::RequestLogin( const char* szUserName, const char* szPsw )
{
	if (m_bDoingLogin)
	{
		return false;
	}
	csmsg::TCSMessage stMsg;
	stMsg.set_emsgid(csmsg::eMsgID_LoginReq);

	csmsg::TMSG_LOGIN_REQ *pLoginReq = stMsg.mutable_stloginreq();
	pLoginReq->set_strusername(szUserName, strlen(szUserName));
	pLoginReq->set_strpassword(szPsw, strlen(szPsw));
	pLoginReq->set_nuserdata(++m_dwLoginUserData);

	IServerTerminal* pServerTerminal = g_pGlobalClient->GetServerTerminal();
	bool bSend = pServerTerminal->Send(&stMsg);
	if (bSend)
	{
		m_strPsw = szPsw;
		m_strUserName = szUserName;
		m_bDoingLogin = true;
		ActiveOverTimeCheck(true);
	}
	return bSend;
}

void CLoginManager::AddLoginCallback( ILoginCallback* pLoginCallback )
{
	if (NULL != pLoginCallback)
	{
		m_setLoginCallback.insert(pLoginCallback);
	}
}

void CLoginManager::RemoveLoginCallback( ILoginCallback* pLoginCallback )
{
	m_setLoginCallback.erase(pLoginCallback);
}

void CLoginManager::OnTimer( int iEventID )
{
	ResetLoginStatu();

	for (TSet_LoginCallback::iterator it = m_setLoginCallback.begin(); it != m_setLoginCallback.end(); ++it)
	{
		ILoginCallback* pLoginCallback = *it;
		ILoginCallback::TLoginData stLoginData;
		stLoginData.szActorName[0] = 0;
		stLoginData.szUserName[0] = 0;
		stLoginData.nActorID = 0;
		stLoginData.nUserID = 0;
		pLoginCallback->OnLoginRsp(ILoginCallback::eLoginErr_OverTime, &stLoginData);
	}
}

ILoginCallback* CLoginManager::GetFirstLoginCallback()
{
	if (m_setLoginCallback.empty())
	{
		return NULL;
	}
	m_itLoginCallback = m_setLoginCallback.begin();
	return *m_itLoginCallback;
}

ILoginCallback* CLoginManager::GetNextLoginCallback()
{
	if (++m_itLoginCallback == m_setLoginCallback.end())
	{
		return NULL;
	}
	return *m_itLoginCallback;
}

const char* CLoginManager::GetUserName() const
{
	return m_strUserName.c_str();
}

const char* CLoginManager::GetPsw() const
{
	return m_strPsw.c_str();
}

DWORD CLoginManager::GetLoginUserData() const
{
	return m_dwLoginUserData;
}

bool CLoginManager::IsDoingLogin() const
{
	return m_bDoingLogin;
}

void CLoginManager::ResetLoginStatu()
{
	m_bDoingLogin = false;
	ActiveOverTimeCheck(false);
}

void CLoginManager::ActiveOverTimeCheck( bool bActive )
{
	ITimerAxis* pTimerAxis = g_pGlobalClient->GetTimerAxis();
	if (bActive)
	{
		pTimerAxis->SetTimer(this, eTimerID_CheckOverTime, 5000, __FUNCTION__);
	}
	else
	{
		pTimerAxis->KillTimer(this, eTimerID_CheckOverTime);
	}
}
