#pragma once 

namespace basetools
{
	class ITimerAxis;
}

class ISystemAPI;
class IServerTerminal;
class ILoginManager;
class IMessageDispatcher;

enum EClientRunState
{
	eClientRunState_NotRun,
	eClientRunState_Running, 
};

struct TGlobalClientInitParam
{
	socketsystem::ISocketSystem *pSocketSystem;
	basetools::ITimerAxis* pTimerAxis;
	ISystemAPI* pSystemAPI;
	char szIp[32];
	DWORD dwPort;

	TGlobalClientInitParam()
	{
		memset(this, 0, sizeof(TGlobalClientInitParam));
	}
};


class IGlobalClient 
{
public:
	
	virtual void Release() = NULL;

	virtual bool Init(const TGlobalClientInitParam* pstInitParam) = NULL;
	
	virtual bool Start() = NULL; 

	virtual bool Stop() = NULL;

	virtual EClientRunState GetRunState() = NULL;

	virtual basetools::ITimerAxis* GetTimerAxis() = NULL;

	virtual ISystemAPI* GetSystemAPI() = NULL; 

	virtual ILoginManager* GetLoginManager() = NULL;

	virtual IServerTerminal* GetServerTerminal() = NULL;

	virtual IMessageDispatcher* GetMessageDispatcher() = NULL;
};