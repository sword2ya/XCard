#include "stdafx.h"
#include "ConnectTest.h"
#include "ClientSocket.h"
#include "SocketSystem.h"


void CTest_ConnectTest_1::Test_1()
{
	ASSERT_TRUE(s_pServerSession->IsClientConnected());
}

void CTest_ConnectTest_1::Test_2()
{
	DWORD dwClientSocketID = s_pServerSession->GetClientSocketID();
	CSocketSystem* pSocketSys = static_cast<CSocketSystem*>(s_stGlobalClientParam.pSocketSystem);
	IClientSocket* pClientSocket = pSocketSys->GetClientSocket(dwClientSocketID);
	ASSERT_TRUE(NULL != pClientSocket);
	CClientSocket* pClientSocket2 = static_cast<CClientSocket*>(pClientSocket);
	pClientSocket2->TriggerErr();
	ASSERT_FALSE(s_pServerSession->IsClientConnected());
	_PushTick(2000);
	ASSERT_TRUE(s_pServerSession->IsClientConnected());
}



size_t CTest_ConnectTest_2::s_nConnectCount = 0;

void CTest_ConnectTest_2::SetUpTestCase()
{
	s_fnInitServerSessionFunc = InitServerSession;
	CTestBase::SetUpTestCase();
}

CServerSession* CTest_ConnectTest_2::InitServerSession()
{
	CServerSession* pServerSession = new CServerSession;
	if ( NULL == pServerSession || !pServerSession->Create())
	{
		delete pServerSession;
		return NULL;
	}
	pServerSession->SetConnectHandler(ClientConnectHandler);
	return pServerSession;
}

bool CTest_ConnectTest_2::ClientConnectHandler(CClientSocket* pClientSocket, const char* szIp, DWORD dwPort)
{
	IClientSocketSink* pSocketSink = pClientSocket->GetClientSocketSink();
	if (s_nConnectCount == 0)
	{
		if (NULL != pSocketSink)
		{
			pSocketSink->OnConnectError(pClientSocket, 1);
		}
		++s_nConnectCount;
		return false;
	}
	else
	{
		if (NULL != pSocketSink)
		{
			pSocketSink->OnConnect(pClientSocket);
		}
		return true;
	}
}


TEST_F(CTest_ConnectTest_2, Test )
{
	ASSERT_FALSE(s_pServerSession->IsClientConnected());
	_PushTick(5000);
	ASSERT_TRUE(s_pServerSession->IsClientConnected());
}


