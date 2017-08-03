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

bool CServerTerminal::Send( csmsg::TCSMessage* pMsg )
{
	std::string strBuf;

	if (NULL == pMsg)
	{
		Error(__FUNCTION__<<" 消息为空");
		return false;
	}
	try
	{
		if (!pMsg->SerializeToString(&strBuf))
		{
			Error(__FUNCTION__<<" 消息序列化失败");
			return false;
		}
	}
	catch (exception* e)
	{
		Error(__FUNCTION__<<" 消息序列化异常，异常信息："<<e->what());
		return false;
	}
	catch(...)
	{
		Error(__FUNCTION__<<" 消息序列化异常，未知异常信息");
		return false;
	}


	return (bool)m_pClientSocket->Send(strBuf.c_str(), strBuf.size());
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
	static csmsg::TCSMessage stMsg;
	static std::string strBuf(Buf, Buf+nLen);
	if (!stMsg.ParseFromString(strBuf))
	{
		Error(__FUNCTION__<<" 不可识别的消息包");
		return;
	}
	IMessageDispatcher* pMsgDispatcher = g_pGlobalClient->GetMessageDispatcher();
	pMsgDispatcher->HandlerMessage(&stMsg);
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
