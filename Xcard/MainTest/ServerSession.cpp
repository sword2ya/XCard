#include "StdAfx.h"
#include "ServerSession.h"
#include "ClientSocket.h"

CServerSession::CServerSession(void)
{
	m_dwClientSocketID = 0;
	m_fnClientConnectHandler = NULL;
}

CServerSession::~CServerSession(void)
{
}

void CServerSession::OnClientConnect( CClientSocket* pClientSocket, const char* szIp, DWORD dwPort )
{
	if (m_fnClientConnectHandler != NULL )
	{
		if (m_fnClientConnectHandler(pClientSocket, szIp, dwPort))
		{
			m_dwClientSocketID = pClientSocket->GetSocketID();
		}
	}
	else
	{
		m_dwClientSocketID = pClientSocket->GetSocketID();
		IClientSocketSink* pSink = pClientSocket->GetClientSocketSink();
		if (NULL != pSink)
		{
			pSink->OnConnect(pClientSocket);
		}
	}
}

bool CServerSession::IsClientConnected()
{
	return m_dwClientSocketID != 0;
}

ClientConnectHandler CServerSession::SetConnectHandler( ClientConnectHandler fnConnectHandler )
{
	ClientConnectHandler fnOldHandler = m_fnClientConnectHandler;
	m_fnClientConnectHandler = fnConnectHandler;
	return fnOldHandler;
}

DWORD CServerSession::GetClientSocketID() const
{
	return m_dwClientSocketID;
}

void CServerSession::SetClientSocketID(DWORD dwSocketID)
{
	m_dwClientSocketID = dwSocketID;
}
