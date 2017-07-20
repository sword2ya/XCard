#include "stdafx.h"
#include "UITestObjectFactory.h"

CUITestObjectFactory::CUITestObjectFactory(void)
{
}

CUITestObjectFactory::~CUITestObjectFactory(void)
{
	TMap_TestClass::iterator it = m_mapTestClass.begin();
	for (; it != m_mapTestClass.end(); ++it)
	{
		if (NULL != it->second)
		{
			delete it->second;
		}
	}
	m_mapTestClass.clear();
}

void CUITestObjectFactory::RegisterTestClass( const char* szTestName, __CUITest_ObjectFactoryHelper_Base* pTestObj )
{
	m_mapTestClass[string(szTestName)] = pTestObj;
}

size_t CUITestObjectFactory::DoFilter( const char* szFilterName )
{
	m_vtFilterTestClass.clear();
	TMap_TestClass::iterator it = m_mapTestClass.begin();
	for (; it != m_mapTestClass.end(); ++it)
	{
		if (NULL == szFilterName || szFilterName[0] == 0)
		{
			m_vtFilterTestClass.push_back(it->second);
		}
		else if (it->first.find_first_of(szFilterName) != string::npos)
		{
			m_vtFilterTestClass.push_back(it->second);
		}
	}
	return m_vtFilterTestClass.size();
}

CUITestBase * CUITestObjectFactory::CreateTestObj( size_t nFilterIdx )
{
	if ( m_vtFilterTestClass.empty() || nFilterIdx >= m_vtFilterTestClass.size() )
	{
		return NULL;
	}
	return m_vtFilterTestClass[nFilterIdx]->CreateTest();
}
