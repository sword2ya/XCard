#pragma once

class CServerTerminal : public ITimerSink , public IClientSocketSink 
{
	enum ETimerID 
	{
		eTimerID_Conn, 
	};
public:
	CServerTerminal(void);
	~CServerTerminal(void);

	bool Create(ISocketSystem* pSocketSys, const char* szIp, DWORD dwPort );

public: // ITiemrSink
	virtual void OnTimer(int iEventID);

public: // IClientSocketSink
	// 接收到数据
	virtual void OnRecv(IClientSocket *pClientSocket, LPCSTR Buf, int nLen) ;
	// 断开连接回调,一般是服务端断开
	virtual void OnCloseConnect(IClientSocket *pClientSocket) ;
	// 连接回调
	virtual void OnConnect(IClientSocket *pClientSocket) ;
	// 连接错误
	virtual void OnConnectError(IClientSocket *pClientSocket, int nErrorCode) ;
private:
	void _ActiveConnectTimer(bool bActive, DWORD dwInterval=1000);
	void _HandlerConnectTimer();

private:
	IClientSocket *m_pClientSocket;
	string m_strIp;
	DWORD m_dwPort;
};
