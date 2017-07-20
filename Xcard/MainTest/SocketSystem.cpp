#include "StdAfx.h"
#include "SocketSystem.h"

CSocketSystem::CSocketSystem(void)
{
	m_bCreated = false;
	m_dwMaxSocketID = 0;
	m_pServerSession = NULL;
}

CSocketSystem::~CSocketSystem(void)
{
	typedef vector<CClientSocket*> TVec_ClientSocket;
	TVec_ClientSocket vtClientSockets;

	TMap_ClientSocket::iterator it = m_mapClientSocket.begin();
	for (; it != m_mapClientSocket.end(); ++it)
	{
		vtClientSockets.push_back(it->second);
	}
	TVec_ClientSocket::iterator it2 = vtClientSockets.begin();
	for (; it2 != vtClientSockets.end(); ++it)
	{
		(*it2)->Release();
	}

}

BOOL CSocketSystem::Create( DWORD dwMaxClientSocket /*= 128 */ )
{
	m_bCreated = true;
	return TRUE;
}

void CSocketSystem::Release()
{
	delete this;
}

IServerSocket* CSocketSystem::CreateServerSocket( EN_VERSION enVersion /*= VER_1 */ )
{
	return NULL;
}

IClientSocket* CSocketSystem::CreateClientSocket( EN_VERSION enVersion /*= VER_1 */ )
{
	if (m_bCreated)
	{
		DWORD dwSocketID = AllocSocketID();
		m_mapClientSocket[dwSocketID] = new CClientSocket;
		CClientSocket *pClientSocket = m_mapClientSocket[dwSocketID];
		pClientSocket->SetSocketID(dwSocketID);
		pClientSocket->SetSocketSystem(this);
		pClientSocket->SetServerSession(m_pServerSession);
		return pClientSocket;
	}
	return NULL;
}

BOOL CSocketSystem::ProcessSocketMsg( BOOL bOnlyPushClient /*= FALSE */ )
{
	return TRUE;
}

BOOL CSocketSystem::PopSocketSysLog( int &iLogLevel, char *pBuffer, int iLen )
{
	return TRUE;
}

const TSocketLimit & CSocketSystem::GetClientSocketLimit()
{
	return m_stSocketLimit;
}

void CSocketSystem::SetClientSocketLimit( const TSocketLimit &stLimit )
{
	m_stSocketLimit = stLimit;
	return;
}

void CSocketSystem::DisableAllLog()
{
	return;
}

void CSocketSystem::ModifyLogLevel( LOG_LEVEL enLV, BOOL bEnable )
{
	return ;
}

BOOL CSocketSystem::IsLogLevelEnable( LOG_LEVEL enLV )
{
	return TRUE;
}

DWORD CSocketSystem::AllocSocketID()
{
	while (m_mapClientSocket.find(++m_dwMaxSocketID) != m_mapClientSocket.end() && m_dwMaxSocketID != 0 )
	{
	}
	return m_dwMaxSocketID;
}


void CSocketSystem::RemoveClientSocket( DWORD dwSocketID )
{
	m_mapClientSocket.erase(dwSocketID);
}

void CSocketSystem::SetServerSession( CServerSession* pServerSession )
{
	m_pServerSession = pServerSession;
}

IClientSocket* CSocketSystem::GetClientSocket( DWORD dwSocketID ) const
{
	TMap_ClientSocket::const_iterator it = m_mapClientSocket.find(dwSocketID);
	if (it == m_mapClientSocket.end())
	{
		return NULL;
	}
	return it->second;
}
