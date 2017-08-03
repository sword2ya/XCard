#include "StdAfx.h"
#include "ServerSession.h"
#include "ClientSocket.h"
#include "SocketSystem.h"

CServerSession::CServerSession(void)
{
	m_dwClientSocketID = 0;
	m_fnClientConnectHandler = NULL;
	__InitServerPart();
	m_pSocketSystem = NULL;
}

CServerSession::~CServerSession(void)
{
}

bool CServerSession::Create()
{
	for (int i = 0; i < _countof(m_arrServerPart); ++i)
	{
		IServerPart* pServerPart = m_arrServerPart[i];
		if (NULL == pServerPart)
		{
			Error(__FUNCTION__<<" 部件为空，部件ID："<<i);
			return false;
		}
		if (!pServerPart->Create(this))
		{
			Error(__FUNCTION__<<" 部件创建失败，部件ID："<<i);
			return false;
		}
	}
	return true;
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

void CServerSession::HandleRecvData( LPCSTR szBuf, size_t nBufSize )
{
	static csmsg::TCSMessage stMsg;
	string strBuf(szBuf, szBuf+nBufSize);
	if (!stMsg.ParseFromString(strBuf))
	{
		Error(__FUNCTION__<<" 解包失败");
		return;
	}
	for (int i = 0; i < _countof(m_arrServerPart); ++i)
	{
		IServerPart* pServerPart = m_arrServerPart[i];
		if (NULL != pServerPart)
		{
			pServerPart->HandlerMsg(&stMsg);
		}
	}
}

bool CServerSession::SendToClient(const csmsg::TCSMessage *pCSMsg )
{
	if (0 == m_dwClientSocketID || NULL == m_pSocketSystem)
	{
		return false;
	}
	CClientSocket* pClientSocket = static_cast<CClientSocket*>(m_pSocketSystem->GetClientSocket(m_dwClientSocketID));
	if (NULL == pClientSocket)
	{
		return false;
	}
	IClientSocketSink* pSocketSink = pClientSocket->GetClientSocketSink();
	if (NULL == pSocketSink)
	{
		return false;
	}
	
	string strData;
	if (!pCSMsg->SerializeToString(&strData))
	{
		return false;
	}
	pSocketSink->OnRecv(pClientSocket, strData.c_str(), strData.size());
	return true;
}

IServerPart* CServerSession::GetPartByID( EServerPart eServerPart )
{
	if (eServerPart < 0 || eServerPart >= eServerPart_Count)
	{
		return NULL;
	}
	return m_arrServerPart[eServerPart];
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

void CServerSession::SetSocketSystem( CSocketSystem* pSocketSystem )
{
	m_pSocketSystem = pSocketSystem;
}

void CServerSession::__InitServerPart()
{
	memset(m_arrServerPart, 0, sizeof(m_arrServerPart));
	m_arrServerPart[eServerPart_Common] = &m_oServerCommonPart;
}
