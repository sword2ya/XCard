#pragma once
#include "UITestBase.h"

class __CUITest_ObjectFactoryHelper_Base 
{
public:
	virtual CUITestBase* CreateTest() = 0;
};

template<class CTestClass>
class __CUITest_ObjectFactoryHelper : public __CUITest_ObjectFactoryHelper_Base
{
public:
	virtual CUITestBase* CreateTest() {return new CTestClass;}
};



class CUITestObjectFactory
{
	typedef map<string, __CUITest_ObjectFactoryHelper_Base*> TMap_TestClass;
	typedef vector<__CUITest_ObjectFactoryHelper_Base*> TVec_TestClass;
public:
	CUITestObjectFactory(void);
	~CUITestObjectFactory(void);

	void RegisterTestClass(const char* szTestName,  __CUITest_ObjectFactoryHelper_Base* pTestObj);
	size_t DoFilter(const char* szFilterName);	// ���˲�������������һ�εĹ��˽��
	CUITestBase *CreateTestObj(size_t nFilterIdx);	// ���ݹ��˽���������������Զ���

private:
	TMap_TestClass m_mapTestClass;
	TVec_TestClass m_vtFilterTestClass;
	
};

