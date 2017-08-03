#pragma once
#include "ServerSession.h"
#include "BasetoolsLoader.h"



typedef CServerSession* (*InitServerSessionFunc)();

class CTestBase :public testing::Test
{
public:
	CTestBase(void);
	~CTestBase(void);

	static void SetUpTestCase();
	static void TearDownTestCase();
	static CServerSession* DefaultInitServerSession();

protected:
	static bool InitParam();
	static void UnInitParam();

	static void _PushTick(DWORD dwMsec);

protected: // 以下函数直接调用客户端函数

protected:
	static CModalLoader s_ML_LandlordClient;
	static IGlobalClient* s_pGlobalClient;
	static TGlobalClientInitParam s_stGlobalClientParam;
	static CServerSession* s_pServerSession;
	static InitServerSessionFunc s_fnInitServerSessionFunc;
	static CBasetoolsLoader s_oBasetoolsLoader;
};


#define ADDCASE(test_fixture, test_name) TEST_F(test_fixture, test_name ){ test_name();}