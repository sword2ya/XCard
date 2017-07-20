#pragma once
#include "isystemapi.h"

class CSystemAPI :
	public ISystemAPI
{
public:
	CSystemAPI(void);
	~CSystemAPI(void);

	virtual void Release();
	virtual DWORD GetTickCount() ;

	virtual time_t time( time_t *t ) ;

public:
	void SetTickCount(DWORD dwTick);
	void SetTime(time_t nTime);

private:
	DWORD m_dwCurTick;
	time_t m_nCurTime;

};
