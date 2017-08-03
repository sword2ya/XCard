#include "StdAfx.h"
#include "LoginTest.h"
#include "ILoginManager.h"

using namespace csmsg;

namespace 
{
	class CLoginTest_LoginCallback : public ILoginCallback
	{
	public:
		CLoginTest_LoginCallback()
		{
			m_bRecvCall = false;
		}
	public: // ILoginCallback
		virtual bool OnLoginRsp(int nErrCode, const TLoginData* pstLoginData )
		{
			m_bRecvCall = true;
			m_stLoginData = *pstLoginData;
			m_nErrCode = nErrCode;
			return true;
		}
	public:
		bool IsRecvCall()
		{
			return m_bRecvCall;
		}

		int GetErrCode()
		{
			return m_nErrCode;
		}

		const TLoginData* GetLoginData()
		{
			return &m_stLoginData;
		}
	private:
		TLoginData m_stLoginData;
		int m_nErrCode;
		bool m_bRecvCall;
	};

}

CLoginTest::CLoginTest(void)
{
}

CLoginTest::~CLoginTest(void)
{
}

void CLoginTest::SetUp()
{
	CTestBase::SetUp();
	CServerCommonPart* pServerCommonPart = static_cast<CServerCommonPart*>(s_pServerSession->GetPartByID(eServerPart_Common));
	ASSERT_NE((CServerCommonPart*)NULL, pServerCommonPart );

	pServerCommonPart->ClearLoginReq();

	X_ResetLoginManager();
}


// 测试客户端能正常发送登录请求
void CLoginTest::Test_01()
{
	const char* szUserName = "user";
	const char* szPsw = "psw";
	ASSERT_TRUE(X_RequestLogin(szUserName, szPsw));
	
	CServerCommonPart* pServerCommonPart = static_cast<CServerCommonPart*>(s_pServerSession->GetPartByID(eServerPart_Common));
	ASSERT_NE((CServerCommonPart*)NULL, pServerCommonPart );
	ASSERT_EQ( 1, pServerCommonPart->GetLoginReqCount());
	string strUserName, strPsw;
	DWORD dwUserData = 0;

	ASSERT_TRUE(pServerCommonPart->GetLoginReqByIndex(0, strUserName, strPsw, dwUserData));
	ASSERT_STREQ(strUserName.c_str(), szUserName);
	ASSERT_STREQ(strPsw.c_str(), szPsw);



}

// 测试正常发送登录请求，服务器回复后，能触发回调
void CLoginTest::Test_02()
{
	CLoginTest_LoginCallback oLoginCallback;
	X_SetLoginCallback(&oLoginCallback);
	Test_01();
	
	CServerCommonPart* pServerCommonPart = static_cast<CServerCommonPart*>(s_pServerSession->GetPartByID(eServerPart_Common));
	ASSERT_NE((CServerCommonPart*)NULL, pServerCommonPart );

	string strUserName, strPsw;
	DWORD dwUserData = 0;
	ASSERT_TRUE(pServerCommonPart->GetLoginReqByIndex(0, strUserName, strPsw, dwUserData));
	
	__RspLogin(dwUserData, 0);

	ASSERT_TRUE(oLoginCallback.IsRecvCall());
	X_RemoveLoginCallback(&oLoginCallback);
}

// 测试发送登录请求后，服务器不回复，会触发超时回调
void CLoginTest::Test_03()
{
	CLoginTest_LoginCallback oLoginCallback;
	X_SetLoginCallback(&oLoginCallback);
	CServerCommonPart* pServerCommonPart = static_cast<CServerCommonPart*>(s_pServerSession->GetPartByID(eServerPart_Common));
	ASSERT_NE((CServerCommonPart*)NULL, pServerCommonPart );


	const char* szUserName = "user";
	const char* szPsw = "psw";
	ASSERT_TRUE(X_RequestLogin(szUserName, szPsw));

	const int nOverTimeVal = 10*1000;
	_PushTick(nOverTimeVal);

	ASSERT_TRUE(oLoginCallback.IsRecvCall());
	ASSERT_EQ(oLoginCallback.GetErrCode(), ILoginCallback::eLoginErr_OverTime);
	X_RemoveLoginCallback(&oLoginCallback);

}

bool CLoginTest::X_RequestLogin( const char* szUserName, const char* szPsw )
{
	ILoginManager* pLoginMgr = s_pGlobalClient->GetLoginManager();
	if (NULL == pLoginMgr)
	{
		return false;
	}
	return pLoginMgr->RequestLogin(szUserName, szPsw);
}


void CLoginTest::X_SetLoginCallback( ILoginCallback* pLoginCallback )
{
	ILoginManager* pLoginMgr = s_pGlobalClient->GetLoginManager();
	if (NULL == pLoginMgr)
	{
		return;
	}
	pLoginMgr->AddLoginCallback(pLoginCallback);
}

void CLoginTest::X_RemoveLoginCallback( ILoginCallback* pLoginCallback )
{
	ILoginManager* pLoginMgr = s_pGlobalClient->GetLoginManager();
	if (NULL == pLoginMgr)
	{
		return;
	}
	pLoginMgr->RemoveLoginCallback(pLoginCallback);
}

void CLoginTest::X_ResetLoginManager()
{
	ILoginManager* pLoginMgr = s_pGlobalClient->GetLoginManager();
	ASSERT_NE((ILoginManager*)NULL, pLoginMgr);
	pLoginMgr->ResetLoginStatu();
}

bool CLoginTest::__RspLogin( DWORD dwUserData, int nErrCode )
{
	g_stMessagePackage.set_emsgid(eMsgID_LoginRsp);
	csmsg::TMSG_LOGIN_RSP *pstLoginRsp = g_stMessagePackage.mutable_stloginrsp();
	pstLoginRsp->set_nuserdata(dwUserData);
	pstLoginRsp->set_nerrcode(nErrCode);

	bool bSend = s_pServerSession->SendToClient(&g_stMessagePackage);
	g_stMessagePackage.Clear();
	return bSend;
}

ADDCASE(CLoginTest, Test_01);
ADDCASE(CLoginTest, Test_02);
ADDCASE(CLoginTest, Test_03);
