#pragma once 
#include "TestBase.h"

// Test1.�������Ӳ���
// Test2. �������ԣ����Ӻ�Ͽ�����
class CTest_ConnectTest_1 : public CTestBase
{
public:
	void Test_1();
	void Test_2();

};
ADDCASE(CTest_ConnectTest_1, Test_1)
ADDCASE(CTest_ConnectTest_1, Test_2)



// �������ԣ���һ������ʧ�ܣ��ڶ������ӳɹ�
class CTest_ConnectTest_2 : public CTestBase 
{
public:
	static bool ClientConnectHandler(CClientSocket* pClientSocket, const char* szIp, DWORD dwPort);
	static void SetUpTestCase();
	static CServerSession* InitServerSession();

private:
	static size_t s_nConnectCount;
};

