#pragma once

class CSocketSystem;
class CServerSession;



class CClientSocket : public socketsystem::IClientSocket
{
public:
	CClientSocket(void);
	~CClientSocket(void);

	virtual void Release() ;

	virtual BOOL Connect( LPCSTR szServerIP, int iServerPort ) ;

	virtual void CloseConnect();

	virtual BOOL Send( LPCSTR Buf, int nLen );

	virtual BOOL SendRaw( LPCSTR Buf, int nLen );

	virtual DWORD GetSocketID();

	virtual void setSocketSink( IClientSocketSink* pSink );

	virtual BOOL isConnected();

	virtual BOOL isConnecting();

	virtual void SetPackageRule( IPackageRule *pCustomRule );

	virtual IPackageRule * GetPackageRule();
	
public:
	void SetSocketID(DWORD dwSocketID);
	void SetSocketSystem(CSocketSystem* pSocketSys);
	void SetServerSession(CServerSession* pServerSession);
	IClientSocketSink* GetClientSocketSink() const;
	void TriggerErr();


private:
	DWORD m_dwSocketID;
	CSocketSystem* m_pSocketSystem;
	CServerSession* m_pServerSession;
	IClientSocketSink* m_pClientSocketSink;
};
