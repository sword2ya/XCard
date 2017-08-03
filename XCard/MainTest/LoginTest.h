#pragma once
#include "TestBase.h"

class ILoginCallback;

class CLoginTest : public CTestBase
{
public:
	CLoginTest(void);
	~CLoginTest(void);

	void SetUp();

public:
	void Test_01();
	void Test_02();
	void Test_03();

private:
	bool X_RequestLogin(const char* szUserName, const char* szPsw);
	void X_SetLoginCallback(ILoginCallback* pLoginCallback);
	void X_RemoveLoginCallback(ILoginCallback* pLoginCallback);

	void X_ResetLoginManager();

private:
	bool __RspLogin(DWORD dwUserData, int nErrCode);
};
