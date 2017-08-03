#pragma once
#include "ServerCommonPart.h"

class CClientSocket;
class CSocketSystem;

typedef bool (*ClientConnectHandler)(CClientSocket* pClientSocket, const char* szIp, DWORD dwPort);

class CServerSession
{
public:
	CServerSession(void);
	~CServerSession(void);

	bool Create();
	void OnClientConnect(CClientSocket* pClientSocket, const char* szIp, DWORD dwPort);
	void HandleRecvData(LPCSTR szBuf, size_t nBufSize );
	bool SendToClient(const csmsg::TCSMessage *pCSMsg);
	IServerPart* GetPartByID(EServerPart eServerPart);
	
public:
	bool IsClientConnected();
	ClientConnectHandler SetConnectHandler(ClientConnectHandler fnConnectHandler);
	DWORD GetClientSocketID() const;
	void SetClientSocketID(DWORD dwSocketID);
	void SetSocketSystem(CSocketSystem* pSocketSystem);

private:
	void __InitServerPart();

private:
	DWORD m_dwClientSocketID;
	ClientConnectHandler m_fnClientConnectHandler;
	IServerPart* m_arrServerPart[eServerPart_Count];

	CServerCommonPart m_oServerCommonPart;
	CSocketSystem* m_pSocketSystem;
	
		
};
