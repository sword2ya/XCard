#include "stdafx.h"
#include "UITestManager.h"
#include "UITest_CCard.h"


CUITestManager g_oUITestManager;

CUITestManager::CUITestManager(void)
{
	m_nCurTestIdx = 0xffffffff;
	m_bRunning = false;
}

CUITestManager::~CUITestManager(void)
{
	_StopCurObj();
}

void CUITestManager::Start()
{
	if (m_bRunning)
	{
		return;
	}
	if (m_vtTestObjs.empty())
	{
		return;
	}
	m_bRunning = true;
	m_nCurTestIdx = 0;
	_TestCurObj();
}

void CUITestManager::Stop()
{
	if (!m_bRunning)
	{
		return;
	}
	_StopCurObj();
	m_bRunning = false;
}

void CUITestManager::AddTestObj( CUITestBase * pTestObj )
{
	m_vtTestObjs.push_back(pTestObj);
}

bool CUITestManager::Next()
{
	if (!HasMore())
	{
		return false;
	}
	_StopCurObj();
	++m_nCurTestIdx;
	_TestCurObj();
	return true;
}

bool CUITestManager::HasMore()
{
	return _IsValid(m_nCurTestIdx+1);
}

bool CUITestManager::HasPre()
{
	return m_nCurTestIdx > 0 && _IsValid(m_nCurTestIdx-1);;
}

bool CUITestManager::Pre()
{
	if (!HasPre())
	{
		return false;
	}
	_StopCurObj();
	--m_nCurTestIdx;
	_TestCurObj();
	return true;
}

bool CUITestManager::IsRunning()
{
	return m_bRunning;
}

CUITestObjectFactory* CUITestManager::GetTestObjectFactory()
{
	return &m_oTestObjectFactory;
}

void CUITestManager::_TestCurObj()
{
	if (m_vtTestObjs.empty() || m_nCurTestIdx >= m_vtTestObjs.size())
	{
		return;
	}
	CUITestBase* pTestObj = m_vtTestObjs[m_nCurTestIdx];
	if (NULL != pTestObj && !pTestObj->IsRunning())
	{
		pTestObj->SetUp();
	}
}

void CUITestManager::_StopCurObj()
{
	if (_IsValid(m_nCurTestIdx))
	{
		CUITestBase* pTestObj = m_vtTestObjs[m_nCurTestIdx];
		if (NULL != pTestObj && pTestObj->IsRunning())
		{
			pTestObj->TearDown();
		}
	}
}

bool CUITestManager::_IsValid( size_t nIdx )
{
	return !m_vtTestObjs.empty() && nIdx < m_vtTestObjs.size();
}


