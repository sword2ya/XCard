#include "StdAfx.h"
#include "ClientSocket.h"
#include "SocketSystem.h"
#include "ServerSession.h"

CClientSocket::CClientSocket(void)
{
	m_pSocketSystem = NULL;
	m_dwSocketID = 0;
	m_pServerSession = NULL;
	m_pClientSocketSink = NULL;
}

CClientSocket::~CClientSocket(void)
{
	if (NULL != m_pSocketSystem)
	{
		m_pSocketSystem->RemoveClientSocket(m_dwSocketID);
	}
}

void CClientSocket::Release()
{
	delete this;
}

BOOL CClientSocket::Connect( LPCSTR szServerIP, int iServerPort )
{
	if (NULL != m_pServerSession)
	{
		m_pServerSession->OnClientConnect(this, szServerIP, iServerPort);
		return TRUE;
	}
	return FALSE;
}

void CClientSocket::CloseConnect()
{
	return;
}

BOOL CClientSocket::Send( LPCSTR Buf, int nLen )
{
	return TRUE;
}

BOOL CClientSocket::SendRaw( LPCSTR Buf, int nLen )
{
	return TRUE;
}

DWORD CClientSocket::GetSocketID()
{
	return m_dwSocketID;
}

void CClientSocket::setSocketSink( IClientSocketSink* pSink )
{
	m_pClientSocketSink = pSink;
	return;
}

BOOL CClientSocket::isConnected()
{
	return FALSE;
}

BOOL CClientSocket::isConnecting()
{
	return TRUE;
}

void CClientSocket::SetPackageRule( IPackageRule *pCustomRule )
{
	return;
}

IPackageRule * CClientSocket::GetPackageRule()
{
	return NULL;
}

void CClientSocket::SetSocketID( DWORD dwSocketID )
{
	m_dwSocketID = dwSocketID;
}

void CClientSocket::SetSocketSystem( CSocketSystem* pSocketSys )
{
	m_pSocketSystem = pSocketSys;
}

void CClientSocket::SetServerSession( CServerSession* pServerSession )
{
	m_pServerSession = pServerSession;
}

IClientSocketSink* CClientSocket::GetClientSocketSink() const
{
	return m_pClientSocketSink;
}

void CClientSocket::TriggerErr()
{
	if (NULL != m_pClientSocketSink)
	{
		m_pClientSocketSink->OnConnectError(this, 1);
	}
	m_pServerSession->SetClientSocketID(0);
}
