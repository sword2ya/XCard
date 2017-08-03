#include "StdAfx.h"
#include "TestBase.h"
#include "SocketSystem.h"
#include "SystemAPI.h"
#include "appframe/basetools/ITimerHelper.h"
#include "ILoginManager.h"

CModalLoader CTestBase::s_ML_LandlordClient;
IGlobalClient* CTestBase::s_pGlobalClient = NULL;
CServerSession* CTestBase::s_pServerSession = NULL;
TGlobalClientInitParam CTestBase::s_stGlobalClientParam;
InitServerSessionFunc CTestBase::s_fnInitServerSessionFunc = CTestBase::DefaultInitServerSession;
CBasetoolsLoader CTestBase::s_oBasetoolsLoader;


CTestBase::CTestBase(void)
{
}

CTestBase::~CTestBase(void)
{
}

void CTestBase::SetUpTestCase()
{
	ASSERT_TRUE(NULL != s_fnInitServerSessionFunc);
	s_pServerSession = s_fnInitServerSessionFunc();
	ASSERT_TRUE(NULL != s_pServerSession);

	ASSERT_TRUE( s_ML_LandlordClient.LoadModal("XLandlordClient.dll")) << s_ML_LandlordClient.GetErrorMsg();
	void* p = s_ML_LandlordClient.GetInterface("IGlobalClient");
	ASSERT_NE((void*)NULL, p);
	s_pGlobalClient = (IGlobalClient*)p;
	ASSERT_TRUE( InitParam());
	ASSERT_TRUE( s_pGlobalClient->Init(&s_stGlobalClientParam));
	ASSERT_TRUE ( s_pGlobalClient->Start());
	//ASSERT_TRUE(s_pServerSession->IsClientConnected());
}

void CTestBase::TearDownTestCase()
{
	if (NULL != s_pGlobalClient)
	{
		if ( eClientRunState_Running == s_pGlobalClient->GetRunState())
		{
			s_pGlobalClient->Stop();
		}
		s_pGlobalClient->Release();
		s_pGlobalClient = NULL;
	}
	if (NULL != s_pServerSession)
	{
		delete s_pServerSession;
		s_pServerSession = NULL;
	}
	UnInitParam();
}

bool CTestBase::InitParam()
{
	if (!s_oBasetoolsLoader.Create())
	{
		return false;
	}

	CSocketSystem* pSocketSys = new CSocketSystem;
	pSocketSys->SetServerSession(s_pServerSession);
	s_pServerSession->SetSocketSystem(pSocketSys);
	s_stGlobalClientParam.pSocketSystem = pSocketSys;
	s_stGlobalClientParam.pSystemAPI = new CSystemAPI;
	s_stGlobalClientParam.pTimerAxis = s_oBasetoolsLoader.LoadTimerAxis();
	if (NULL == s_stGlobalClientParam.pTimerAxis)
	{
		return false;
	}
	return true;
}

void CTestBase::UnInitParam()
{
	SafeRelease(s_stGlobalClientParam.pSocketSystem);
	SafeRelease(s_stGlobalClientParam.pSystemAPI);
	SafeRelease(s_stGlobalClientParam.pTimerAxis);
	s_oBasetoolsLoader.Close();
}

void CTestBase::_PushTick(DWORD dwMsec)
{
	CSystemAPI* pSystemApi = static_cast<CSystemAPI*>(s_stGlobalClientParam.pSystemAPI);
	DWORD dwCurTick = pSystemApi->GetTickCount();
	time_t nCurTime = pSystemApi->time(NULL);

	pSystemApi->SetTickCount(dwCurTick + dwMsec);
	pSystemApi->SetTime(nCurTime + dwMsec/1000);
	
	s_stGlobalClientParam.pTimerAxis->SetCurrentTick(pSystemApi->GetTickCount());
	s_stGlobalClientParam.pTimerAxis->CheckTimer();
}

CServerSession* CTestBase::DefaultInitServerSession()
{
	CServerSession* pServerSession = new CServerSession;
	if (NULL == pServerSession || !pServerSession->Create())
	{
		return NULL;
	}
	return pServerSession;
}

