#include "StdAfx.h"
#include "ServerTerminal.h"
#include "IGlobalClient.h"


CServerTerminal::CServerTerminal(void)
{
	m_pClientSocket = NULL;
	m_dwPort = 0;
}

CServerTerminal::~CServerTerminal(void)
{
	if (NULL != m_pClientSocket)
	{
		m_pClientSocket->Release();
		m_pClientSocket = NULL;
	}
	_ActiveConnectTimer(false);
}

bool CServerTerminal::Create( ISocketSystem* pSocketSys, const char* szIp, DWORD dwPort )
{
	m_pClientSocket = pSocketSys->CreateClientSocket();
	if (NULL == m_pClientSocket)
	{
		Error("创建ClientSocket失败");
		return false;
	}
	m_pClientSocket->setSocketSink(this);
	m_strIp = szIp;
	m_dwPort = dwPort;
	_HandlerConnectTimer();
	return true;
}

void CServerTerminal::OnTimer( int iEventID )
{
	if (iEventID == eTimerID_Conn)
	{
		_ActiveConnectTimer(false);
		_HandlerConnectTimer();
	}
}

void CServerTerminal::OnRecv( IClientSocket *pClientSocket, LPCSTR Buf, int nLen )
{

}

void CServerTerminal::OnCloseConnect( IClientSocket *pClientSocket )
{
	Trace("CServerTerminal::OnCloseConnect已经关闭和服务器的连接");
}

void CServerTerminal::OnConnect( IClientSocket *pClientSocket )
{
	Trace("CServerTerminal::OnCloseConnect已经连接服务器。 ip="<< m_strIp << " port="<<m_dwPort);

}

void CServerTerminal::OnConnectError( IClientSocket *pClientSocket, int nErrorCode )
{
	Warning("CServerTerminal::OnCloseConnect连接发生错误，err="<< nErrorCode);
	_ActiveConnectTimer(true);
}

void CServerTerminal::_ActiveConnectTimer(bool bActive, DWORD dwInterval)
{
	ITimerAxis* pTimerAxis = g_pGlobalClient->GetTimerAxis();
	if (bActive)
	{
		if (!pTimerAxis->SetTimer(this, eTimerID_Conn, dwInterval, __FUNCTION__))
		{
			Error("CServerTerminal::_ActiveConnectTimer 定时器创建失败");
		}
	}
	else 
	{
		pTimerAxis->KillTimer(this, eTimerID_Conn);
	}
}

void CServerTerminal::_HandlerConnectTimer()
{
	if (m_pClientSocket != NULL)
	{
		m_pClientSocket->Connect(m_strIp.c_str(), m_dwPort);
	}
}
