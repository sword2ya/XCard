#pragma once
#include "IGlobalClient.h"
#include "ServerTerminal.h"
#include "MainTimer.h"

class CGlobalClient : public IGlobalClient
{
public:
	CGlobalClient(void);
	~CGlobalClient(void);

	virtual void Release();
	virtual bool Init(const TGlobalClientInitParam* pstInitParam) ;
	virtual bool Start() ;
	virtual bool Stop() ;
	virtual EClientRunState GetRunState();
	virtual basetools::ITimerAxis* GetTimerAxis() ;
	
	virtual ISystemAPI* GetSystemAPI();


	

private:
	EClientRunState m_eRunState;
	TGlobalClientInitParam m_stInitParam;
	CServerTerminal m_oServerTerminal;
	CMainTimer m_oMainTimer;
};
