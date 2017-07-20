#pragma once

class ISystemAPI 
{
public:
	virtual void Release() = NULL;
	virtual DWORD GetTickCount() = NULL;
	virtual time_t time(time_t *t ) = NULL;
};