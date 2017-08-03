#include "StdAfx.h"
#include "MainTimer.h"
#include "IGlobalClient.h"
#include "isystemapi.h"

using basetools::ITimerAxis;

CMainTimer::CMainTimer(void)
{
}

CMainTimer::~CMainTimer(void)
{
}

bool CMainTimer::Create()
{
	ITimerAxis* pTimerAxis = g_pGlobalClient->GetTimerAxis();
	ISystemAPI* pSystemAPI = g_pGlobalClient->GetSystemAPI();
	DWORD dwCurTick = pSystemAPI->GetTickCount();
	pTimerAxis->SetCurrentTick(dwCurTick);

	m_oTimer.setInterval(16);
	connect(&m_oTimer, SIGNAL(timeout()), this, SLOT(slot_PushTick()));
	m_oTimer.start();
	return true;	
}

void CMainTimer::slot_PushTick()
{
	ITimerAxis* pTimerAxis = g_pGlobalClient->GetTimerAxis();
	ISystemAPI* pSystemAPI = g_pGlobalClient->GetSystemAPI();
	DWORD dwCurTick = pSystemAPI->GetTickCount();
	if (dwCurTick != pTimerAxis->GetCurrentTick())
	{
		pTimerAxis->SetCurrentTick(dwCurTick);
		pTimerAxis->CheckTimer();
	}
}
