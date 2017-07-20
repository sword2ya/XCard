#pragma once
#include "ClientSocket.h"

class CServerSession;

class CSocketSystem : public socketsystem::ISocketSystem
{
	typedef map<DWORD, CClientSocket*> TMap_ClientSocket;

public:
	CSocketSystem(void);
	~CSocketSystem(void);

	virtual BOOL Create( DWORD dwMaxClientSocket = 128 );

	virtual void Release() ;

	virtual IServerSocket* CreateServerSocket( EN_VERSION enVersion = VER_1 ) ;

	virtual IClientSocket* CreateClientSocket( EN_VERSION enVersion = VER_1 ) ;

	virtual BOOL ProcessSocketMsg( BOOL bOnlyPushClient = FALSE );

	virtual BOOL PopSocketSysLog( int &iLogLevel, char *pBuffer, int iLen );

	virtual const TSocketLimit & GetClientSocketLimit();

	virtual void SetClientSocketLimit( const TSocketLimit &stLimit );

	virtual void DisableAllLog();

	virtual void ModifyLogLevel( LOG_LEVEL enLV, BOOL bEnable );

	virtual BOOL IsLogLevelEnable( LOG_LEVEL enLV );

public:
	void RemoveClientSocket(DWORD dwSocketID);
	void SetServerSession(CServerSession* pServerSession);
	IClientSocket* GetClientSocket(DWORD dwSocketID) const ;

private:
	DWORD AllocSocketID();

private:
	socketsystem::TSocketLimit m_stSocketLimit;
	bool m_bCreated;
	TMap_ClientSocket m_mapClientSocket;
	DWORD m_dwMaxSocketID;
	CServerSession *m_pServerSession;
};
