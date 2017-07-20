#include "StdAfx.h"
#include "SystemAPI.h"

CSystemAPI::CSystemAPI(void)
{
	m_dwCurTick = 100;
	m_nCurTime = 100;
}

CSystemAPI::~CSystemAPI(void)
{
}

void CSystemAPI::Release()
{
	delete this;
}

DWORD CSystemAPI::GetTickCount()
{
	return m_dwCurTick;
}

time_t CSystemAPI::time( time_t *t )
{
	return m_nCurTime;
}

void CSystemAPI::SetTickCount( DWORD dwTick )
{
	m_dwCurTick = dwTick;
}

void CSystemAPI::SetTime( time_t nTime )
{
	m_nCurTime = nTime;
}
