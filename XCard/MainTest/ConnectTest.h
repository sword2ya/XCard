#pragma once 
#include "TestBase.h"

// Test1.正常连接测试
// Test2. 重连测试，连接后断开连接
class CTest_ConnectTest_1 : public CTestBase
{
public:
	void Test_1();
	void Test_2();

};
ADDCASE(CTest_ConnectTest_1, Test_1)
ADDCASE(CTest_ConnectTest_1, Test_2)



// 重连测试：第一次连接失败，第二次连接成功
class CTest_ConnectTest_2 : public CTestBase 
{
public:
	static bool ClientConnectHandler(CClientSocket* pClientSocket, const char* szIp, DWORD dwPort);
	static void SetUpTestCase();
	static CServerSession* InitServerSession();

private:
	static size_t s_nConnectCount;
};

