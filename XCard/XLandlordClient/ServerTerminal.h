#pragma once
#include "MessageDispatcher.h"
#include "IServerTerminal.h"

class CServerTerminal : public ITimerSink , public IClientSocketSink , public IServerTerminal
{
	enum ETimerID 
	{
		eTimerID_Conn, 
	};
public:
	CServerTerminal(void);
	~CServerTerminal(void);

	bool Create(ISocketSystem* pSocketSys, const char* szIp, DWORD dwPort );

public: // IServerTerminal
	virtual bool Send(csmsg::TCSMessage* pMsg);

public: // ITiemrSink
	virtual void OnTimer(int iEventID);

public: // IClientSocketSink
	// ���յ�����
	virtual void OnRecv(IClientSocket *pClientSocket, LPCSTR Buf, int nLen) ;
	// �Ͽ����ӻص�,һ���Ƿ���˶Ͽ�
	virtual void OnCloseConnect(IClientSocket *pClientSocket) ;
	// ���ӻص�
	virtual void OnConnect(IClientSocket *pClientSocket) ;
	// ���Ӵ���
	virtual void OnConnectError(IClientSocket *pClientSocket, int nErrorCode) ;
private:
	void _ActiveConnectTimer(bool bActive, DWORD dwInterval=1000);
	void _HandlerConnectTimer();

private:
	IClientSocket *m_pClientSocket;
	string m_strIp;
	DWORD m_dwPort;
};
