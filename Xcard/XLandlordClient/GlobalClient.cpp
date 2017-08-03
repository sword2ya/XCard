#include "StdAfx.h"
#include "GlobalClient.h"

IGlobalClient* g_pGlobalClient = NULL;


CGlobalClient::CGlobalClient(void)
{
	m_eRunState = eClientRunState_NotRun;
}

CGlobalClient::~CGlobalClient(void)
{
	if (m_eRunState == eClientRunState_Running)
	{
		Stop();
	}
}

void CGlobalClient::Release()
{
	delete this;
}

bool CGlobalClient::Init(const TGlobalClientInitParam* pstInitParam)
{
	m_stInitParam = *pstInitParam;
	if (!m_stInitParam.pSocketSystem->Create())
	{
		return false;
	}
	if (!m_oMainTimer.Create())
	{
		Error("MainTimer´´½¨Ê§°Ü");
		return false;
	}
	return true;
}

bool CGlobalClient::Start()
{
	if (!m_oServerTerminal.Create(m_stInitParam.pSocketSystem, m_stInitParam.szIp, m_stInitParam.dwPort))
	{
		return false;
	}
	m_oMessageHandlerRegister.InitMessageHandlers();
	m_eRunState = eClientRunState_Running;
	return true;
}

bool CGlobalClient::Stop()
{
	m_oMessageHandlerRegister.UnInitMessageHandlers();
	m_eRunState = eClientRunState_NotRun;
	return true;
}

EClientRunState CGlobalClient::GetRunState()
{
	return m_eRunState;
}

basetools::ITimerAxis* CGlobalClient::GetTimerAxis()
{
	return m_stInitParam.pTimerAxis;
}

ISystemAPI* CGlobalClient::GetSystemAPI()
{
	return m_stInitParam.pSystemAPI;
}

ILoginManager* CGlobalClient::GetLoginManager()
{
	return &m_oLoginManager;
}

CServerTerminal* CGlobalClient::GetServerTerminal()
{
	return &m_oServerTerminal;
}

IMessageDispatcher* CGlobalClient::GetMessageDispatcher()
{
	return &m_oMsgDispatcher;
}
