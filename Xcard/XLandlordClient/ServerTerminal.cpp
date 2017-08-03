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
		Error("����ClientSocketʧ��");
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
		Error(__FUNCTION__<<" ��ϢΪ��");
		return false;
	}
	try
	{
		if (!pMsg->SerializeToString(&strBuf))
		{
			Error(__FUNCTION__<<" ��Ϣ���л�ʧ��");
			return false;
		}
	}
	catch (exception* e)
	{
		Error(__FUNCTION__<<" ��Ϣ���л��쳣���쳣��Ϣ��"<<e->what());
		return false;
	}
	catch(...)
	{
		Error(__FUNCTION__<<" ��Ϣ���л��쳣��δ֪�쳣��Ϣ");
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
		Error(__FUNCTION__<<" ����ʶ�����Ϣ��");
		return;
	}
	IMessageDispatcher* pMsgDispatcher = g_pGlobalClient->GetMessageDispatcher();
	pMsgDispatcher->HandlerMessage(&stMsg);
}

void CServerTerminal::OnCloseConnect( IClientSocket *pClientSocket )
{
	Trace("CServerTerminal::OnCloseConnect�Ѿ��رպͷ�����������");
}

void CServerTerminal::OnConnect( IClientSocket *pClientSocket )
{
	Trace("CServerTerminal::OnCloseConnect�Ѿ����ӷ������� ip="<< m_strIp << " port="<<m_dwPort);

}

void CServerTerminal::OnConnectError( IClientSocket *pClientSocket, int nErrorCode )
{
	Warning("CServerTerminal::OnCloseConnect���ӷ�������err="<< nErrorCode);
	_ActiveConnectTimer(true);
}

void CServerTerminal::_ActiveConnectTimer(bool bActive, DWORD dwInterval)
{
	ITimerAxis* pTimerAxis = g_pGlobalClient->GetTimerAxis();
	if (bActive)
	{
		if (!pTimerAxis->SetTimer(this, eTimerID_Conn, dwInterval, __FUNCTION__))
		{
			Error("CServerTerminal::_ActiveConnectTimer ��ʱ������ʧ��");
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
