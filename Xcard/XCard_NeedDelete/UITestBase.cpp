#include "stdafx.h"
#include "UITestBase.h"

CUITestBase::CUITestBase(void)
{
	m_bRunning = false;
}

CUITestBase::~CUITestBase(void)
{
}

void CUITestBase::SetUp()
{
	m_bRunning = true;
}

void CUITestBase::TearDown()
{
	m_bRunning = false;
}

bool CUITestBase::IsRunning()
{
	return m_bRunning;
}
