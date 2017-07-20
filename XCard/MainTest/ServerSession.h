#pragma once

class CClientSocket;

typedef bool (*ClientConnectHandler)(CClientSocket* pClientSocket, const char* szIp, DWORD dwPort);

class CServerSession
{
public:
	CServerSession(void);
	~CServerSession(void);

	void OnClientConnect(CClientSocket* pClientSocket, const char* szIp, DWORD dwPort);
	

public:
	bool IsClientConnected();
	ClientConnectHandler SetConnectHandler(ClientConnectHandler fnConnectHandler);
	DWORD GetClientSocketID() const;
	void SetClientSocketID(DWORD dwSocketID);

private:
	DWORD m_dwClientSocketID;
	ClientConnectHandler m_fnClientConnectHandler;
		
};
