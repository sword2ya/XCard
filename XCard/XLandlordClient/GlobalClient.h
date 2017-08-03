#pragma once
#include "IGlobalClient.h"
#include "ServerTerminal.h"
#include "MainTimer.h"
#include "LoginManager.h"
#include "MessageHandlerRegister.h"

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
	virtual ILoginManager* GetLoginManager() ;
	virtual CServerTerminal* GetServerTerminal();
	virtual IMessageDispatcher* GetMessageDispatcher();


private:
	EClientRunState m_eRunState;
	TGlobalClientInitParam m_stInitParam;
	CServerTerminal m_oServerTerminal;
	CMainTimer m_oMainTimer;
	CLoginManager m_oLoginManager;
	CMessageDispatcher m_oMsgDispatcher;
	CMessageHandlerRegister m_oMessageHandlerRegister;
};
